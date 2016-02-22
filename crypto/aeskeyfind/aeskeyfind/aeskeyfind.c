// AESKeyFinder 1.0 (2008-07-18)
// By Nadia Heninger and Ariel Feldman

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

extern char *optarg;
extern int optind, opterr, optopt;
#include <getopt.h>

#ifdef __FreeBSD__
#include <err.h>
#else
#define err(x,y) { perror(y); exit(x); }
#endif

#include "util.h"
#include "aes.h"

#define DEFAULT_THRESHOLD 10
static long int gThreshold = DEFAULT_THRESHOLD;
static int gVerbose = 0;
static int gProgress = 1;

// Print a key, assuming the key schedule starts at map[0].  
// num_bits should be 128 or 256 
// if gVerbose is on it will print the entire key schedule as well 
// as the constraints--the XOR of words that should XOR to 0
static void print_key(uint32_t* map, int num_bits, size_t address)
{
    if (gVerbose) {
        printf("FOUND POSSIBLE %d-BIT KEY AT BYTE %zx \n\n", num_bits, address);
        printf("KEY: ");
    }

    int num_words = num_bits/32;
    for (int col = 0; col < num_words; col++)
        print_word(map[col]);
    printf("\n");


    if (gVerbose) {
        printf("\n");
        printf("EXTENDED KEY: \n");

        int num_roundkeys = 0;
        if (num_bits == 256) num_roundkeys = 15;
        if (num_bits == 128) num_roundkeys = 11;
        for (int row=0; row<num_roundkeys; row++) {
            for (int column = 0; column<4; column++) {
                print_word(map[(4*row+column)]);
            }
            printf("\n");
        }

        printf("\n");
        printf("CONSTRAINTS ON ROWS:\n");

        for (int row=1; row<num_roundkeys; row++) {
            for (int column = 0; column<num_words; column++) {
                if (num_bits == 256 && row == 7 && column >= 4) break;
                if (column==0)
                    print_word(key_core(map[num_words*row-1],row) ^
                            map[num_words*(row-1)] ^
                            map[num_words*row]);
                else if (column == 4)
                    print_word(sbox_bytes(map[num_words*row+3]) ^
                            map[num_words*(row-1)+4] ^
                            map[num_words*row+4]);
                else
                    print_word(map[num_words*row+column-1] ^
                            map[num_words*(row-1)+column] ^
                            map[num_words*row + column]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

// Simple entropy test
//
// Returns true if the 176 bytes starting at location bmap[i] contain
// more than 8 repeats of any byte.  This is a primitive measure of
// entropy, but it works well enough.  The function keeps track of a
// sliding window of byte counts.
static int entropy(const uint8_t* bmap, int i)
{
    static int new_call = 1;
    static int byte_freq[256] = {0};
    if (new_call) {
        for (int i=0; i<176; i++) byte_freq[bmap[i]]++;
        new_call = 0;
    }

    int test = 0;
    for (int b=0; b<=0xFF; b++) {
        if (byte_freq[b] > 8) {
            test = 1;
            break;
        }
    }
    byte_freq[bmap[i]]--;
    byte_freq[bmap[i+176]]++;
    return test;
}

// Prints info about the program's command line options
static void usage()
{
    fprintf(stderr, "Usage: aeskeyfind [OPTION]... MEMORY-IMAGE\n"
			"Locates scheduled 128-bit and 256-bit AES keys in MEMORY-IMAGE.\n"
			"\n"
			"\t-v\t\tverbose output -- prints the extended keys and \n"
            "\t\t\tthe constraints on the rows of the key schedule\n"
			"\t-q\t\tdon't display a progress bar\n"
			"\t-t THRESHOLD\tsets the maximum number of bit errors allowed \n"
            "\t\t\tin a candidate key schedule (default = %d)\n"
			"\t-h\t\tdisplays this help message\n", DEFAULT_THRESHOLD);
}

// Prints the progress to stderr
static void print_progress(size_t percent)
{
    fprintf(stderr, "Keyfind progress: %zu%%\r", percent);
}

// The core key finding loop
//
// Searches for AES keys in memory image bmap with starting offsets up
// to last; prints any keys found
static void find_keys(const uint8_t* bmap, size_t last)
{
    size_t percent = 0;
    const size_t increment = last / 100;

    if (gProgress)
        print_progress(percent);

    for (size_t i = 0; i < last; i++) {
        if (entropy(bmap,i)) continue;

        uint32_t* map = (uint32_t*)&(bmap[i]);

        // Check distance from 256-bit AES key
        int xor_count_256 = 0;
        for (size_t row = 1; row < 8; row++) {
            for (size_t column = 0; column < 8; column++) {
                if (row == 7 && column == 4) break;
                if (column == 0)
                    xor_count_256 += popcount(key_core(map[8*row-1],row) ^
                            map[8*(row-1)] ^
                            map[8*row]);
                else if (column == 4)
                    xor_count_256 += popcount(sbox_bytes(map[8*row+3])^
                            map[8*(row-1)+4] ^
                            map[8*row+4]);
                else
                    xor_count_256 += popcount(map[8*row+column-1] ^
                            map[8*(row-1)+column] ^
                            map[8*row + column]);
            }
	    if (xor_count_256 > gThreshold)
	      break;
        }
        if (xor_count_256 <= gThreshold)
            print_key(map,256,i);

        // Check distance from 128-bit AES key
        int xor_count_128 = 0;
        for (size_t row = 1; row < 11; row++) {
            for (size_t column = 0; column < 4; column++) {
                if (column == 0)
                    xor_count_128 += popcount(key_core(map[4*row-1],row) ^
                            map[4*(row-1)] ^
                            map[4*row]);
                else
                    xor_count_128 += popcount((map[4*row + column-1] ^
                            map[4*(row-1)+column]) ^
                            map[4*row + column]);
            }
	    if (xor_count_128 > gThreshold)
	      break;
        }
        if (xor_count_128 < gThreshold)
            print_key(map,128,i);

        if (gProgress) {
            size_t pct = (increment > 0) ? i / increment : i * 100 / last;
            if (pct > percent) {
                percent = pct;
                print_progress(percent);
            }
        }
    }

    if (gProgress) {
        print_progress(100);
        fprintf(stderr, "\n");
    }
}

// Memory maps filename and return a pointer on success, setting len
// to the length of the file (does not return on error)
unsigned char *map_file(char *filename, unsigned int *len) {
  int fd = open(filename, O_RDONLY);
  if (fd < 0)
    err(1, "image open failed");

  struct stat st;
  if (fstat(fd, &st) != 0)
    err(1, "image fstat failed");

  unsigned char *map;
  map = (unsigned char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED)
    err(1, "image mmap failed");

  *len = st.st_size;
  return map;
}

int main(int argc, char * argv[])
{
    int ch = -1;
    while ((ch = getopt(argc, argv, "hvqt:")) != -1) {
        switch(ch) {
            case 'v':
                gVerbose = 1;
                break;
            case 'q':
                gProgress = 0;
                break;
            case 't':
                {
                    errno = 0;
                    char* endptr = NULL;
                    gThreshold = strtol(optarg, &endptr, 10);
                    if (gThreshold < 0 || errno != 0 || endptr == optarg) {
                        fprintf(stderr, "invalid threshold\n");
                        usage();
                        exit(1);
                    }
                }
                break;
            case '?':
            case 'h':
            default:
                usage();
                exit(1);
        }
    }

    argc -= optind;
    argv += optind;

    if (argc != 1) {
        usage();
        exit(1);
    }

    unsigned int len;
    unsigned char *image = map_file(argv[0], &len);
    if (len < 240) {
        fprintf(stderr, "memory image too small\n");
        exit(1);
    }

    find_keys(image, len - 240);

    return 0;
}
