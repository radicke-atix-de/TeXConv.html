# `date +%F`

VERSION=dev
PROGNAME=texconv


OUTPUT_BUILD = ./${PROGNAME}-${VERSION}



.PHONY:   AUTHORS all archive clean  install rpm

all: dist


# Install all dracut modules
install:
	echo "yet does not implement"
	
# remove modules 
uninstall: 
	echo "yet does not implement"



# cleaning the build-tmp-files
clean:
	#rm -f *~
	#rm -f *.rpm
	$(RM) -r $(OUTPUT_BUILD)

# creake a bz2-achiv
archive: ../${PROGNAME}-$(VERSION).tar.bz2


# create distrebut-build
dist: AUTHORS 
	mkdir $(OUTPUT_BUILD)
	#cp ./GPL*.txt $(OUTPUT_BUILD)
	cp ./README* $(OUTPUT_BUILD)
	cp ./Makefile $(OUTPUT_BUILD)
	cp ./AUTHORS $(OUTPUT_BUILD)
	#cp ./COPYING $(OUTPUT_BUILD)


# create tar-file
tar: dist
	# with build-date
	tar -cvjf ./${PROGNAME}-$(VERSION)_`date +%F`.tar.bz2 $(OUTPUT_BUILD)
	tar -cvjf ./${PROGNAME}-$(VERSION).tar.bz2 $(OUTPUT_BUILD)

# create rpms
rpm: tar
	#rpmbuild -v \
	#-ba ${PROGNAME}.spec


# create a file with autors from git log.
AUTHORS:
	git shortlog  --numbered --summary -e |while read a rest; do echo $$rest;done > ./AUTHORS



