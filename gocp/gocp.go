package main

import (
	"flag"
	"io"
	"os"
)

var sinfile = flag.String("infile", "", "Input file path")
var soutfile = flag.String("outfile", "", "Input Your Age")

func main() {
	flag.Parse()
	if len(*sinfile) == 0 || len(*soutfile) == 0 {
		return
	}
	fin, err := os.Open(*sinfile)
	if err != nil {
		return
	}
	fout, err := os.Create(*soutfile)
	io.Copy(fout, fin)
	return
}
