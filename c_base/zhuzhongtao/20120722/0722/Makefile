all	:
	./a.out |\
	/usr/ucb/tbl |\
	/usr/ucb/pic |\
	/usr/ucb/eqn |\
	/usr/ucb/troff -ms |\
	/usr/ucb/dpost > doc.ps

view	:
	evince doc.ps &

clean	:
	rm -f doc.ps
