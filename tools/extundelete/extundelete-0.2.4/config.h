/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to 1 if the system has the type `blk64_t'. */
#define HAVE_BLK64_T 1

/* Define to 1 if you have the `ext2fs_blocks_count' function. */
#define HAVE_EXT2FS_BLOCKS_COUNT 1

/* Define to 1 if you have the `ext2fs_bmap2' function. */
#define HAVE_EXT2FS_BMAP2 1

/* Define to 1 if you have the `ext2fs_extent_open2' function. */
#define HAVE_EXT2FS_EXTENT_OPEN2 1

/* Define to 1 if you have the `ext2fs_get_array' function. */
#define HAVE_EXT2FS_GET_ARRAY 1

/* Define to 1 if you have the `ext2fs_get_generic_bitmap_start' function. */
#define HAVE_EXT2FS_GET_GENERIC_BITMAP_START 1

/* Define to 1 if you have the `ext2fs_get_generic_bmap_start' function. */
#define HAVE_EXT2FS_GET_GENERIC_BMAP_START 1

/* Define to 1 if you have the `ext2fs_group_of_blk2' function. */
#define HAVE_EXT2FS_GROUP_OF_BLK2 1

/* Define to 1 if you have the `ext2fs_inode_table_loc' function. */
#define HAVE_EXT2FS_INODE_TABLE_LOC 1

/* Define to 1 if you have the `ext2fs_read_dir_block3' function. */
#define HAVE_EXT2FS_READ_DIR_BLOCK3 1

/* Define to 1 if you have the `ext2fs_test_block_bitmap2' function. */
#define HAVE_EXT2FS_TEST_BLOCK_BITMAP2 1

/* Define to 1 if you have the `ext2fs_test_inode_bitmap2' function. */
#define HAVE_EXT2FS_TEST_INODE_BITMAP2 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `com_err' library (-lcom_err). */
#define HAVE_LIBCOM_ERR 1

/* Define to 1 if you have the `ext2fs' library (-lext2fs). */
#define HAVE_LIBEXT2FS 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Define to 1 if `stat' has the bug that it succeeds when given the
   zero-length file name argument. */
/* #undef HAVE_STAT_EMPTY_STRING_BUG */

/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strtol' function. */
#define HAVE_STRTOL 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

/* Define to 1 if `lstat' dereferences a symlink specified with a trailing
   slash. */
#define LSTAT_FOLLOWS_SLASHED_SYMLINK 1

/* Name of package */
#define PACKAGE "extundelete"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "extundelete.sourceforge.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "extundelete"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "extundelete 0.2.4"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "extundelete"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.2.4"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.2.4"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
