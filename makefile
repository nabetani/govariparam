run : main a.clang.out a.gcc9.out
	echo go
	./main 10000000 | tail -2
	echo
	echo clang
	./a.clang.out  10000000 | tail -4
	echo
	echo gcc9
	./a.gcc9.out  10000000 | tail -4

main: main.go makefile
	go build main.go

a.clang.out : makefile main.cpp
	clang++ -std=c++17 -O2 -Wall main.cpp -o a.clang.out

a.gcc9.out : makefile main.cpp
	g++-9 -std=c++17 -O2 -Wall main.cpp -o a.gcc9.out
