AM_CFLAGS = -DPROG="\"$(PACKAGE)\"" -DVERSION="\"$(VERSION)\""

bin_PROGRAMS = extundelete

extundelete_CFLAGS = @EU_CFLAGS@ @EU_WCFLAGS@ $(AM_CFLAGS)
extundelete_CXXFLAGS = @EU_CXXFLAGS@ @EU_WCXXFLAGS@ $(AM_CFLAGS)
extundelete_SOURCES = extundelete.cc  cli.cc block.c  insertionops.cc  block.h  extundelete.h  extundelete-priv.h  jfs_compat.h  kernel-jbd.h

EXTRA_PROGRAMS = extundelete-prof  extundelete-nodebug  extundelete-strict

extundelete_prof_CFLAGS = $(extundelete_CFLAGS) @EU_CPROF@
extundelete_prof_CXXFLAGS = $(extundelete_CXXFLAGS) @EU_CXXPROF@
extundelete_prof_SOURCES = $(extundelete_SOURCES)
extundelete_prof_LDFLAGS = -pg

extundelete_nodebug_CFLAGS = -DNDEBUG @EU_OPTFLAGS@ @EU_WCFLAGS@  $(AM_CFLAGS)
extundelete_nodebug_CXXFLAGS = -DNDEBUG @EU_OPTXXFLAGS@ @EU_WCXXFLAGS@ $(AM_CFLAGS)
extundelete_nodebug_SOURCES = $(extundelete_SOURCES)

extundelete_strict_CFLAGS = $(extundelete_CFLAGS) @EU_SCFLAGS@
extundelete_strict_CXXFLAGS = $(extundelete_CXXFLAGS) @EU_SCXXFLAGS@
extundelete_strict_SOURCES = $(extundelete_SOURCES)

profile:	extundelete-prof
	-mv extundelete-prof extundelete

nodebug:	extundelete-nodebug
	-mv extundelete-nodebug extundelete

strict:	extundelete-strict
	-mv extundelete-strict extundelete


clean-local:
	-rm -f $(EXTRA_PROGRAMS)

maintainer-clean-local:
	-rm -f Makefile.in

.PHONY:	profile nodebug strict clean-local extundelete maintainer-clean-local
