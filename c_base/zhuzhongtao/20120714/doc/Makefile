DISTFLAGS = -q -dBATCH -dNOPAUSE -sDEVICE=pdfwrite \
	-sProcessColorModel=DeviceGray -dPDFSETTINGS=/prepress
CRYPT = -sOwnerPassword="`dd if=/dev/random bs=12 count=1 2>/dev/null | \
	md5sum | awk '{ print $$1 }'` " -dEncryptionR=3 \
	-dKeyLength=128 -dPermissions=-300

.SUFFIXES: .tr .ps .pdf

.tr.ps:
	rm -f $@; trap "rm -f $$$$.ps" 0 2 3; \
		/usr/ucb/tbl $< |\
		/usr/ucb/pic |\
		/usr/ucb/troff -ms |\
		/usr/ucb/dpost > $$$$.ps && mv $$$$.ps $@
#		tbl $< | troff | dpost >$$$$.ps && mv $$$$.ps $@

.ps.pdf:
	gs -sOutputFile=$@ $(DISTFLAGS) -f $<

all:  doc
doc: doc.ps doc1.ps doc2.ps

view:
	evince doc*.ps &

clean:
	rm -f doc*.ps doc.pdf core log *~

mrproper: clean
