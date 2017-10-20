.name "test2"
.comment "test2"

l2:	ld 10,r2
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
