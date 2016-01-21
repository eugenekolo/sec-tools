SUBDIRS = src
AM_MAKEFLAGS = -s
EXTRA_DIST = LICENSE README autogen.sh

profile:
	$(MAKE) RECURSIVE_TARGETS=profile-recursive $(AM_MAKEFLAGS) $(@:profile=profile-recursive)

nodebug:
	$(MAKE) RECURSIVE_TARGETS=nodebug-recursive $(AM_MAKEFLAGS) $(@:nodebug=nodebug-recursive)

strict:
	$(MAKE) RECURSIVE_TARGETS=strict-recursive $(AM_MAKEFLAGS) $(@:strict=strict-recursive)

profile-am: Makefile config.h
nodebug-am: Makefile config.h
strict-am: Makefile config.h

release: clean
	-rm -f aclocal.m4
	-touch -r config.h.in aclocal.m4
	$(MAKE) $(AM_MAKEFLAGS) $(@:release=dist-bzip2)
	-echo "Generated release of $(PACKAGE_STRING)"

clean-local:
	-rm -f config.h.in~
	-rm -rf autom4te.cache

maintainer-clean-local:
	-rm -f aclocal.m4 config.h.in Makefile.in configure
	-rm -f compile depcomp install-sh missing

.PHONY:	profile profile-am nodebug nodebug-am strict strict-am release clean-local maintainer-clean-local
