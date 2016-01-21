#! /bin/sh

# Clean up the package directories
make -s maintainer-clean 2> /dev/null ||
  rm -f aclocal.m4 config.h.in

# Rebuild the automatically generated files
EU_VER=$1 autoreconf -i -f

# Make configure run silently
sed -e 's,^silent=$,silent=yes,' configure > configure.new
mv configure.new configure
chmod u+x configure

# Remove cache files
rm -rf autom4te.cache
