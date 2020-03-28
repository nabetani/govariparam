all : a.clang.out a.gcc9.out


a.clang.out : makefile main.cpp
	clang++ -std=c++17 -O2 -Wall main.cpp -o a.clang.out

a.gcc9.out : makefile main.cpp
	g++-9 -std=c++17 -O2 -Wall main.cpp -o a.gcc9.out
