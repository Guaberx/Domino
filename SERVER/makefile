FLAGS = -std=c++11 -O3

test: SERVER.cpp SERVER.h
	g++ -o SERVER ${FLAGS} -LWIN32  SERVER.cpp SERVER.h -lwsock32 -lws2_32