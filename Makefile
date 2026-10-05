all:
	g++ -o test.exe game/main.cpp motor/render.cpp motor/log.cpp -Wall -Wextra -std=c++11 -O0
