# `date +%F`

VERSION=dev
PROGNAME=texconv

BUILDDIR=/BUILD
OUTPUT_BUILD = .$(BUILDDIR)/$(PROGNAME)-$(VERSION)
LEXSOURCE=./src/lex
CC = g++
LEX     = flex
LFLAGS  = -d -v -+
YACC    = bison -y
YFLAGS  = -d

YYCCODE = latex2html.yy.c
OBJECTS = latex2html.o



.PHONY:   AUTHORS all archive clean  install rpm

all: dist

# create distrebut-build
dist: AUTHORS $(PROGNAME)
	mkdir .$(BUILDDIR)
	mkdir $(OUTPUT_BUILD)
	#cp ./GPL*.txt $(OUTPUT_BUILD)
	cp ./README* $(OUTPUT_BUILD)
	cp ./Makefile $(OUTPUT_BUILD)
	cp ./AUTHORS $(OUTPUT_BUILD)
	#cp ./COPYING $(OUTPUT_BUILD)


# create a file with autors from git log.
AUTHORS:
	git shortlog  --numbered --summary -e | while read a rest; do echo $$rest;done > ./AUTHORS


$(PROGNAME) : $(OBJECTS)
	$(CC) -o $@  $(LDFLAGS) $^


latex2html.o: latex2html.yy.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $^



latex2html.yy.c: $(LEXSOURCE)/latex2html.l
	$(LEX) $(LFLAGS)  -o $@ $^




# Install all dracut modules
install:
	echo "yet does not implement"
	
# remove modules 
uninstall: 
	echo "yet does not implement"



# cleaning the build-tmp-files
clean:
	$(RM) -f *~
	#rm -f *.rpm
	$(RM) -r .$(BUILDDIR)
	$(RM) -f $(YYCCODE)
	$(RM) -f $(OBJECTS)

# creake a bz2-achiv
archive: ../$(PROGNAME)-$(VERSION).tar.bz2




# create tar-file
tar: dist
	# with build-date
	tar -cvjf ./$(PROGNAME)-$(VERSION)_`date +%F`.tar.bz2 $(OUTPUT_BUILD)
	tar -cvjf ./$(PROGNAME)-$(VERSION).tar.bz2 $(OUTPUT_BUILD)

# create rpms
rpm: tar
	#rpmbuild -v \
	#-ba ${PROGNAME}.spec






