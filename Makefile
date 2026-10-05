all:
	g++ -o test.exe game/main.cpp motor/input.cpp motor/log.cpp -Wall -Wextra -std=c++11 -O0
