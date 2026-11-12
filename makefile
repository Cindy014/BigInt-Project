main: main.C BigIntpro.o
	g++ -o main main.C BigIntpro.o
BigIntpro.o: BigIntpro.C BigIntpro.h
	g++ -c -o BigIntpro.o BigIntpro.C