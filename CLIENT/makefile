FLAGS = -std=c++11 -O3

test: CLIENT.cpp CLIENT.h
	g++ -o CLIENT ${FLAGS} -LWIN32  CLIENT.CPP CLIENT.h -lwsock32 -lws2_32