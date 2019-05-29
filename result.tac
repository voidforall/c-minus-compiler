Fun :
	BeginFunc;
	t0 = 1;
	t1 = t0 * elem_size(b);
	t2 = &b + t1;
	t0 = 2;
	t1 = t0 * elem_size(b);
	t3 = &b + t1;
	t0 = *t3;
	t1 = 2;
	t3 = t1;
	t1 = t0 + t3;
	*t2 = t1;
	t0 = a;
	t1 = t0;
	t0 = 1;
	t2 = t0;
	t0 = t1 == t2;
	If_false t0 GOTO L0;
	t0 = 2;
	t1 = t0 * elem_size(b);
	t2 = &b + t1;
	t0 = 3;
	*t2 = t0;
	GOTO L1;
L0: 
	t0 = 2;
	t1 = t0 * elem_size(b);
	t2 = &b + t1;
	t0 = 3;
	*t2 = t0;
L1: 
	t0 = 0;
	Return t0;
	EndFunc;
