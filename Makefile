# `date +%F`

VERSION=dev
PROGNAME=texconv

BUILDDIR=/BUILD
OUTPUT_BUILD = .$(BUILDDIR)/$(PROGNAME)-$(VERSION)
DOCS=./docs
TESTFILES=./testfiles

CP=cp
CC = g++
CPPFLAGS = -Wall -Werror -pedantic 


LIBS = -lboost_regex


SOURCE = ./src/main.cpp
OBJECTS =  main.o  TexParser.o



.PHONY:   AUTHORS all archive clean  install rpm

all: dist

# create distrebut-build
dist: $(DOCS) AUTHORS $(PROGNAME)
	mkdir .$(BUILDDIR)
	mkdir $(OUTPUT_BUILD)
	#$(CP) ./GPL*.txt $(OUTPUT_BUILD)
	$(CP) ./README* $(OUTPUT_BUILD)
	$(CP) ./Makefile $(OUTPUT_BUILD)
	$(CP) ./AUTHORS $(OUTPUT_BUILD)
	$(CP) -r $(DOCS)  $(OUTPUT_BUILD)
	#cp ./COPYING $(OUTPUT_BUILD)


# create a file with autors from git log.
AUTHORS:
	git shortlog  --numbered --summary -e | while read a rest; do echo $$rest;done > ./AUTHORS


$(PROGNAME) : $(OBJECTS)
	$(CC) -o $@  $^ $(LIBS)


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
	$(RM) -r $(DOCS)
	$(RM) -r ./*.aux
	$(RM) -r ./*.out
	$(RM) -r ./*.pdf
	$(RM) -r ./*.toc
	$(RM) -r ./*.log


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

$(DOCS): 
	doxygen ./Doxyfile

tex-test:
	pdflatex $(TESTFILES)/simple_tex_document.tex
	pdflatex $(TESTFILES)/simple_tex_document.tex






