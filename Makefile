# `date +%F`

VERSION=dev
PROGNAME=texconv

BUILDDIR=/BUILD
OUTPUT_BUILD = .$(BUILDDIR)/$(PROGNAME)-$(VERSION)ls
CC = g++
CPPFLAGS = -Wall -Werror -pedantic  -lboost_regex

LIBS = -L/usr/lib/

SOURCE = ./src/main.cpp
OBJECTS =  main.o  TexParser.o



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
	$(CC) -o $@  $^


main.o: ./src/main.cpp
	$(CC) $(CPPFLAGS)  -o $@ -c $^ $(LIBS)


TexParser.o: ./src/TexParser.cpp
	$(CC) $(CPPFLAGS)  -o $@ -c $^ $(LIBS)






# Install all dracut modules
install:
	echo "yet does not implement"
	
# remove modules 
uninstall: 
	echo "yet does not implement"



# cleaning the build-tmp-files
clean-all:
	$(RM) -f *~
	#rm -f *.rpm
	$(RM) -r .$(BUILDDIR)
	$(RM) -f $(OBJECTS)
	$(RM) -f $(PROGNAME)


# cleaning the build-tmp-files
clean:
	#rm -f *.rpm
	$(RM) -r .$(BUILDDIR)

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






