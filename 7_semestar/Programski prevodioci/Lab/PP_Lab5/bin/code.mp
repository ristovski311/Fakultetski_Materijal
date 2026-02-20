main()
{
	boolean prom0;
	boolean prom1;
	int prom2;
	int prom3;
	real prom4;
	real prom5;

	prom2 := 10;
	prom3 := #23;
	prom0 := true;
	prom1 := false;
	prom4 := 10.4;
	prom5 := 0.4E4;
	
	if(prom2 > prom3):
	{
		int var3;
		var3 := 3
	}
	elif(prom0):
	{
		real prom6;
		prom6 := 3.1
	}
	elif(prom4 <> prom5):
	{
		real prom7;
		prom7 := 3.14
	}
	else:
	{
		real prom8;
		prom8 := 3.1415
	};
	prom2 := 4
}