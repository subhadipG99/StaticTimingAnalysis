
sta:	RdCkt.cpp ReadLib.h ReadLibFunc.h
	g++ -std=c++11 -O2 RdCkt.cpp -o sta

clean:
	rm *.o sta
