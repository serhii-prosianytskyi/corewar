.name "test1"
.comment "test1test1"

l2:	add	r1,r2,r3
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
