package main

import (
	"fmt"
	"os"
	"strconv"
	"time"
)

func vari6(n ...uintptr) uintptr {
	return n[0] + n[1] + n[2] + n[3] + n[4] + n[5]
}

func fixed6(a, b, c, d, e, f uintptr) uintptr {
	return a + b + c + d + e + f
}

func benchV(title string, num uintptr, proc func(n ...uintptr) uintptr) {
	t0 := time.Now()
	sum := uintptr(0)
	for i := uintptr(0); i < num; i++ {
		sum += proc(i&1, i&2, i&4, i&8, i&16, i&32)
	}
	t1 := time.Now()
	fmt.Println(title, t1.Sub(t0), sum)
}

func benchF(title string, num uintptr, proc func(a, b, c, d, e, f uintptr) uintptr) {
	t0 := time.Now()
	sum := uintptr(0)
	for i := uintptr(0); i < num; i++ {
		sum += proc(i&1, i&2, i&4, i&8, i&16, i&32)
	}
	t1 := time.Now()
	fmt.Println(title, t1.Sub(t0), sum)
}

func main() {
	num, err := strconv.ParseInt(os.Args[1], 10, 64)
	if err != nil {
		panic(err)
	}
	for i := 0; i < 3; i++ {
		benchV("vari", uintptr(num), vari6)
		benchF("fixed", uintptr(num), fixed6)
	}
}
