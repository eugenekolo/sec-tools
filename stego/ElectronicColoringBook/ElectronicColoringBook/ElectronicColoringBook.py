#!/usr/bin/env python

# See usage and examples on the project page:
# https://doegox.github.io/ElectronicColoringBook/
# This toy is released under the WTFPL
# (Do What the Fuck You Want to Public License).
# Copyright (C) 2014 Philippe Teuwen <phil teuwen org>

import sys
import math
import random
from PIL import Image
import colorsys
import operator
from optparse import OptionParser

options = OptionParser(usage='%prog [options] file',
                       description='Colorize data file according '
                       'to repetitive chunks, typical in ECB encrypted data')
options.add_option('-c', '--colors', type='int',
                   default=16, help='Number of colors to use, default=16')
options.add_option('-P', '--palette',
                   help='Provide list of colors to be used, as hex byte '
                   'indexes to a rainbow palette or as RGB palette')
options.add_option('-b', '--blocksize', type='int',
                   default=16, help='Blocksize to consider, in bytes, '
                   'default=16')
options.add_option('-g', '--groups', type=int, default=1,
                   help='Groups of N blocks e.g. when blocksize is not '
                   'multiple of underlying data, default=1')
options.add_option('-r', '--ratio', help='Ratio of output image, e.g. -r 4:3')
options.add_option('-x', '--width', type='float', help='Width of output image, '
                   'can be float e.g. to ignore line PNG-filter byte')
options.add_option('-y', '--height', type='int', help='Height of output image')
options.add_option('-s', '--sampling', type='int', default=1000,
                   help='Sampling when guessing image size. Smaller is slower '
                   'but more precise, default=1000')
options.add_option('-m', '--maxratio', type='int', default=3,
                   help='Max ratio to test when guessing image size. '
                   'E.g. default=3 means testing ratios from 1:3 to 3:1')
options.add_option('-o', '--offset', type='float', default=0,
                   help='Offset to skip original header in number of blocks, '
                   'can be float')
options.add_option('-f', '--flip', action="store_true",
                   default=False, help='Flip image top<>bottom')
options.add_option('-p', '--pixelwidth', type='int', default=1,
                   help='How many bytes per pixel in the original image')
options.add_option('-R', '--raw', action="store_true",
                   default=False, help='Display raw image in 256 colors')
options.add_option('-S', '--save', action="store_true",
                   default=False, help='Save a copy of the produced image')
options.add_option('-O', '--output', help='Change default output location '
                   'prefix, e.g. -O /tmp/mytest. Implies -S')
options.add_option('-D', '--dontshow', action="store_true",
                   default=False, help='Don\'t display image')


def histogram(data, blocksize):
    d = {}
    for k in range(len(data) / blocksize):
        block = data[k * blocksize:(k + 1) * blocksize].encode('hex')
        if block not in d:
            d[block] = 1
        else:
            d[block] += 1
    return sorted(d.iteritems(), key=operator.itemgetter(1), reverse=True)

opts, args = options.parse_args()
if len(args) < 1:
    options.print_help()
    sys.exit()

if opts.colors != 16 and opts.palette:
    # Testing against default values to guess if user mixed options...
    print "Please don't mix -c with -C!"
    sys.exit()

palette = None
if opts.palette:
    if '#' in opts.palette:
        opts.colors = len(opts.palette) / 7
        palette = []
        for rgb in opts.palette.split('#')[1:]:
            palette.extend(
                [int(rgb[:2], 16), int(rgb[2:4], 16), int(rgb[4:], 16)])
        opts.palette = ''.join(["%02X" % i for i in range(opts.colors)])
    else:
        opts.colors = len(opts.palette) / 2

if opts.colors < 2:
    print "Please choose at least two colors"
    sys.exit()

if opts.width is not None and opts.height is not None:
    print "Please indicate only -x or -y, not both!"
    sys.exit()

if opts.ratio is not None and (opts.width is not None or
                               opts.height is not None):
    print "Please don't mix -r with -x or -y!"
    sys.exit()

if opts.raw is True and (opts.colors != 16 or opts.blocksize != 16 or
                         opts.groups != 1 or opts.palette):
    # Testing against default values to guess if user mixed options...
    print "Please don't mix -R with -b, -c, -C or -g!"
    sys.exit()

if opts.output:
    opts.save = True

with open(args[0], 'rb') as f:
    f.read(int(round(opts.offset * opts.blocksize)))
    ciphertext = f.read()

if opts.raw:
    # Create smooth palette
    N = 256
    HSV_tuples = [(x * 1.0 / N, 0.8, 0.8) for x in range(N)]
    RGB_tuples = [colorsys.hsv_to_rgb(*x) for x in HSV_tuples]
    p = []
    for rgb in RGB_tuples:
        p.extend(rgb)         # rainbow
    p = [int(pp * 255) for pp in p]
    out = ciphertext[::opts.pixelwidth]
else:
    histo = histogram(ciphertext, opts.blocksize)
    # Cut histo to those we need to colorize
    histo = histo[:(opts.colors - 1) * opts.groups]
    # Cut histo to discard singletons
    histo = [x for x in histo if x[1] > 1]
    # Cut histo to keep exact multiple of group
    histo = histo[:len(histo) / opts.groups * opts.groups]
    if not histo:
        raise NameError("Did not find any single match :-(")

    # Construct palette with black & white at extremities
    N = 254
    HSV_tuples = [(x * 1.0 / N, 0.8, 0.8) for x in range(N)]
    RGB_tuples = [colorsys.hsv_to_rgb(*x) for x in HSV_tuples]
    if palette:
        p = palette
    else:
        p = [1, 1, 1]               # white
        for rgb in RGB_tuples:
            p.extend(rgb)         # rainbow
        p.extend([0, 0, 0])     # black
        p = [int(pp * 255) for pp in p]
    # Show palette:
    # j=Image.fromstring('P', (256, 256),
    #     ''.join([chr(a) for a in range(256)]*256))
    # j.putpalette(p)
    # j.show()

    # Let's use random colors = random refs to the colormap...
    colormap = {}
    for i in range(len(histo) / opts.groups):
        if i == 0:
            if opts.palette:
                color = int(opts.palette[:2], 16)
            else:
                color = 0  # white
        else:
            if opts.palette:
                color = int(opts.palette[i * 2:i * 2 + 2], 16)
            else:
                color = random.randint(1, 254)
        for g in range(opts.groups):
            gi = (i * opts.groups) + g
            colormap[histo[gi][0]] = chr(color)
            print "%s %10s #%02X" % (histo[gi][0], histo[gi][1], color),
            print "-> #%02X #%02X #%02X" % (p[color * 3],
                                            p[(color * 3) + 1],
                                            p[(color * 3) + 2])
    blocksleft = len(ciphertext) / opts.blocksize - \
        reduce(lambda x, y: x + y, [n for (t, n) in histo])
    # All other blocks will be painted in black:
    if opts.palette:
        color = int(opts.palette[-2:], 16)
    else:
        color = 255
    print "%s %10i #%02X" % ("*" * len(histo[0][0]), blocksleft, color),
    print "-> #%02X #%02X #%02X" % (p[color * 3],
                                    p[(color * 3) + 1],
                                    p[(color * 3) + 2])

    # Construct output stream
    out = ""
    outlenfloat = 0.0
    for i in range(len(ciphertext) / opts.blocksize):
        token = ciphertext[
            i * opts.blocksize:(i + 1) * opts.blocksize].encode('hex')
        if token in colormap:
            byte = colormap[token]
        else:
            byte = chr(color)
        out += byte * (opts.blocksize / opts.pixelwidth)
        outlenfloat += float(opts.blocksize) / opts.pixelwidth
        if outlenfloat >= len(out) + 1:
            out += byte

if opts.width is None and opts.height is None and opts.ratio is None:
    print "Trying to guess ratio between",
    print "1:%i and %i:1 ..." % (opts.maxratio, opts.maxratio)

    sq = int(math.sqrt(len(out)))
    r = {}
    print "Width: from %i to %i" % (sq / opts.maxratio, sq * opts.maxratio)
    print "Sampling: %i" % opts.sampling
    print "Progress:",
    for i in range(sq / opts.maxratio, sq * opts.maxratio):
        if i % 100 == 0:
            print i,
            sys.stdout.flush()
        A = out[:-i:opts.sampling]
        B = out[i::opts.sampling]
        # How many matches?
# Shall we skip matches between black blocks?
#        m=reduce(lambda x,y: x+y,[x and x==y for (x,y) in zip(A,B)])
        m = reduce(lambda x, y: x + y, [x == y for (x, y) in zip(A, B)])
        r[i] = float(m) / (len(A))
    print ""
    r = sorted(r.iteritems(), key=operator.itemgetter(1), reverse=True)
    opts.width = r[0][0]

if opts.ratio is not None:
    # Compute ratio
    ratio = tuple([int(x) for x in opts.ratio.split(':')])
    l = len(out)
    x = math.sqrt(float(ratio[0]) / ratio[1] * l)
    y = x / ratio[0] * ratio[1]
    xy = (int(x), int(y))

if opts.width is not None:
    if int(opts.width) != opts.width:
        # Fractional width, little trick...
        out2=""
        frac=opts.width-int(opts.width)
        acc=0
        miss=0
        print "frac", frac
        for i in range(len(out) / int(opts.width)):
            line=out[i*int(opts.width):(i+1)*int(opts.width)]
            acc+=frac
            if acc > 1:
                acc-=1
                out2+=line[:-1]
                miss+=1
            else:
                out2+=line
        out=out2+("\xff"*miss)
    xy = (int(opts.width), len(out) / int(opts.width))

if opts.height is not None:
    xy = (len(out) / opts.height, opts.height)

print "Size: ", repr(xy)

# Create image from output stream & ratio
i = Image.fromstring('P', xy, out)
i.putpalette(p)

if opts.flip:
    i = i.transpose(Image.FLIP_TOP_BOTTOM)
if opts.save:
    if not opts.output:
        opts.output = args[0]
    if opts.raw:
        suffix = ".raw_p%i" % opts.pixelwidth
    else:
        suffix = ".b%i_p%i_c%i" % (
            opts.blocksize, opts.pixelwidth, opts.colors)
        if opts.groups != 1:
            suffix += "_g%i" % opts.groups
    if opts.offset != 0:
        suffix += "_o%s" % repr(opts.offset)
    if opts.width is not None:
        suffix += "_x%s_y%i" % (repr(opts.width), xy[1])
    else:
        suffix += "_x%i_y%i" % xy
    print "Saving output into " + opts.output + suffix + '.png'
    i.save(opts.output + suffix + '.png')
if not opts.dontshow:
    i.show()
