# `date +%F`
# error-No: date +%Y%M%d%H%M%S

VERSION=dev
PROGNAME=texconv

BUILDDIR=./BUILD
OUTPUT_BUILD = $(BUILDDIR)/$(PROGNAME)-$(VERSION)
DOCS=./docs
TESTFILES=./testfiles

CP=cp
CC = g++
CPPFLAGS = -Wall -Werror -pedantic 


LIBS = -lboost_regex


SOURCES = ./src/main.cpp \
./src/PrintElementTree.cpp \
./src/TexDocElement.cpp \
./src/BTreePars/BTree.cpp \
./src/BTreePars/BTreeElement.cpp \
./src/BTreePars/BTreePrint.cpp \
./src/BTreePars/PrintBTree.cpp \
./src/pars/BeginEndElementParser.cpp \
./src/pars/CutOut.cpp \
./src/pars/DocumentclassParser.cpp \
./src/pars/DocumentParser.cpp \
./src/pars/InputParser.cpp \
./src/pars/NewcommandParser.cpp \
./src/pars/SectionParser.cpp \
./src/pars/SimpleElementParser.cpp \
./src/pars/TexParser.cpp 

OBJECTS =  ./src/main.o \
./src/PrintElementTree.o \
./src/TexDocElement.o \
./src/BTreePars/BTree.o \
./src/BTreePars/BTreeElement.o \
./src/BTreePars/PrintBTree.o \
./src/pars/BeginEndElementParser.o \
./src/BTreePars/BTreePrint.o \
./src/pars/CutOut.o \
./src/pars/DocumentclassParser.o \
./src/pars/DocumentParser.o \
./src/pars/InputParser.o \
./src/pars/NewcommandParser.o \
./src/pars/SectionParser.o \
./src/pars/SimpleElementParser.o \
./src/pars/TexParser.o



.PHONY:   AUTHORS all archive bin-test  clean clean-all install rpm tex-test

all: dist

# create distrebut-build
dist: $(DOCS) AUTHORS $(PROGNAME)
	if [ ! -d $(BUILDDIR) ] ; then mkdir $(BUILDDIR) ; fi
	if [ ! -d $(OUTPUT_BUILD)  ] ; then mkdir $(OUTPUT_BUILD) ; fi
	#$(CP) ./GPL*.txt $(OUTPUT_BUILD)
	$(CP) ./README* $(OUTPUT_BUILD)
	$(CP) ./Makefile $(OUTPUT_BUILD)
	$(CP) ./AUTHORS $(OUTPUT_BUILD)
	$(CP) -r $(DOCS)  $(OUTPUT_BUILD)
	#cp ./COPYING $(OUTPUT_BUILD)


# create a file with autors from git log.
AUTHORS:
	git shortlog  --numbered --summary -e | while read a rest; do echo $$rest;done > ./AUTHORS



$(PROGNAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJECTS) $(LIBS)


%.o: %.cpp
	$(CC) $(CPPFLAGS) -c ./$< -o ./$@


# cleaning the build-tmp-files
clean:
	#rm -f *.rpm
	$(RM) -r $(BUILDDIR)

# cleaning the build-tmp-files
clean-all:
	$(RM) -f *~
	#rm -f *.rpm
	$(RM) -r $(BUILDDIR)
	$(RM) -f $(OBJECTS)
	$(RM) -f $(PROGNAME)
	$(RM) -r $(DOCS)
	$(RM) -r ./*.aux
	$(RM) -r ./*.out
	$(RM) -r ./*.pdf
	$(RM) -r ./*.toc
	$(RM) -r ./*.log

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

# Install all dracut modules
install:
	echo "yet does not implement"

# remove modules
uninstall:
	echo "yet does not implement"

# simple function check of bin-file.
bin-test:
	./texconv --help
	./texconv pars --input=./testfiles/simple_tex_document.tex --output=./muell.html
	./texconv doctree -v --input=./testfiles/simple_tex_document.tex | cat > ./out.txt

bin-gdb:
	gdb ./texconv

# test the LateX exsample
tex-test:
	pdflatex $(TESTFILES)/simple_tex_document.tex
	pdflatex $(TESTFILES)/simple_tex_document.tex






