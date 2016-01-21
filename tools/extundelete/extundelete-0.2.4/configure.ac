#                                               -*- Autoconf -*-
# Process this file with "./autogen.sh" to produce a configure script.

AC_PREREQ(2.59)
m4_ifval(m4_esyscmd([printf %s $EU_VER]),
[m4_define(EU_VERSION, m4_esyscmd([printf $EU_VER])) ],
[m4_define(EU_VERSION, m4_esyscmd([git describe --tags| tr -d '\010-\012'])) ])
AC_INIT(extundelete, EU_VERSION, extundelete.sourceforge.net)
echo "Configuring ${PACKAGE_STRING}"
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/extundelete.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs and options necessary during compilation.
CFLAGS=$CFLAGS
CXXFLAGS=$CXXFLAGS
AC_PROG_CXX
AC_PROG_CC

AC_LANG([C])
AX_CHECK_COMPILER_FLAGS([-g], [EU_CFLAGS="$EU_CFLAGS -g"], [EU_CFLAGS="$EU_CFLAGS"])
AX_CHECK_COMPILER_FLAGS([-O2], [EU_CFLAGS="$EU_CFLAGS -O2"], [EU_CFLAGS="$EU_CFLAGS"])
AX_CHECK_COMPILER_FLAGS([-std=c99], [EU_WCFLAGS="$EU_WCFLAGS -std=c99"], [EU_WCFLAGS="$EU_WCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wall], [EU_WCFLAGS="$EU_WCFLAGS -Wall"], [EU_WCFLAGS="$EU_WCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-W], [EU_WCFLAGS="$EU_WCFLAGS -W"], [EU_WCFLAGS="$EU_WCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-pedantic], [EU_SCFLAGS="$EU_SCFLAGS -pedantic"], [EU_SCFLAGS="$EU_SCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wredundant-decls], [EU_SCFLAGS="$EU_SCFLAGS -Wredundant-decls"], [EU_SCFLAGS="$EU_SCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wshadow], [EU_SCFLAGS="$EU_SCFLAGS -Wshadow"], [EU_SCFLAGS="$EU_SCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wpointer-arith], [EU_SCFLAGS="$EU_SCFLAGS -Wpointer-arith"], [EU_SCFLAGS="$EU_SCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wwrite-strings], [EU_SCFLAGS="$EU_SCFLAGS -Wwrite-strings"], [EU_SCFLAGS="$EU_SCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Winit-self], [EU_SCFLAGS="$EU_SCFLAGS -Winit-self"], [EU_SCFLAGS="$EU_SCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wconversion], [EU_SCFLAGS="$EU_SCFLAGS -Wconversion"], [EU_SCFLAGS="$EU_SCFLAGS"])
AX_CHECK_COMPILER_FLAGS([-pg], [EU_CPROF="-pg"], [EU_CPROF=""])
AX_CHECK_COMPILER_FLAGS([-O3], [EU_OPTFLAGS="$EU_OPTFLAGS -O3"], [EU_OPTFLAGS="$EU_OPTFLAGS"])

AC_LANG([C++])
AX_CHECK_COMPILER_FLAGS([-g], [EU_CXXFLAGS="$EU_CXXFLAGS -g"], [EU_CXXFLAGS="$EU_CXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-O2], [EU_CXXFLAGS="$EU_CXXFLAGS -O2"], [EU_CXXFLAGS="$EU_CXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-std=c++0x], [EU_WCXXFLAGS="$EU_WCXXFLAGS -std=c++0x"], [EU_WCXXFLAGS="$EU_WCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-std=c++11], [EU_WCXXFLAGS="$EU_WCXXFLAGS -std=c++11"], [EU_WCXXFLAGS="$EU_WCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-W], [EU_WCXXFLAGS="$EU_WCXXFLAGS -W"], [EU_WCXXFLAGS="$EU_WCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wall], [EU_WCXXFLAGS="$EU_WCXXFLAGS -Wall"], [EU_WCXXFLAGS="$EU_WCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-std=c++0x -pedantic], [EU_SCXXFLAGS="$EU_SCXXFLAGS -pedantic"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-std=c++11 -pedantic], [EU_SCXXFLAGS="$EU_SCXXFLAGS -pedantic"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wredundant-decls], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Wredundant-decls"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wshadow], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Wshadow"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wpointer-arith], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Wpointer-arith"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wwrite-strings], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Wwrite-strings"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Woverloaded-virtual], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Woverloaded-virtual"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Weffc++], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Weffc++"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Winit-self], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Winit-self"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-Wconversion], [EU_SCXXFLAGS="$EU_SCXXFLAGS -Wconversion"], [EU_SCXXFLAGS="$EU_SCXXFLAGS"])
AX_CHECK_COMPILER_FLAGS([-pg], [EU_CXXPROF="-pg"], [EU_CXXPROF=""])
AX_CHECK_COMPILER_FLAGS([-O3], [EU_OPTXXFLAGS="$EU_OPTXXFLAGS -O3"], [EU_OPTXXFLAGS="$EU_OPTXXFLAGS"])


AC_LANG([C])
AC_SUBST([EU_CFLAGS])
AC_SUBST([EU_WCFLAGS])
AC_SUBST([EU_SCFLAGS])
AC_SUBST([EU_OPTFLAGS])
AC_SUBST([EU_CXXFLAGS])
AC_SUBST([EU_WCXXFLAGS])
AC_SUBST([EU_SCXXFLAGS])
AC_SUBST([EU_OPTXXFLAGS])

# Checks for libraries.
AC_CHECK_LIB([ext2fs], [ext2fs_bmap], [],[
           AC_MSG_ERROR([Can't find ext2fs library])] )
AC_CHECK_FUNCS([ext2fs_get_generic_bitmap_start ext2fs_inode_table_loc ext2fs_extent_open2 ext2fs_blocks_count ext2fs_get_array ext2fs_get_generic_bmap_start ext2fs_test_block_bitmap2 ext2fs_bmap2 ext2fs_test_block_bitmap2 ext2fs_group_of_blk2 ext2fs_read_dir_block3 ext2fs_test_inode_bitmap2])
AC_CHECK_LIB([com_err], [com_err], [],[
           AC_MSG_ERROR([Can't find com_err library])] )

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdint.h string.h unistd.h utime.h sys/types.h getopt.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_SYS_LARGEFILE
AC_CHECK_TYPES([blk64_t], [], [], [#include <ext2fs/ext2fs.h>])
AC_C_BIGENDIAN()

# Checks for library functions.
AC_FUNC_MEMCMP
AC_FUNC_STAT
AC_CHECK_FUNCS([memset mkdir strerror strtol strtoul])

echo "Writing generated files to disk"
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
