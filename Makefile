SRCS=$(shell find tex/)

build/main.pdf: $(SRCS) Makefile scl.yaml clean
	mkdir -p build/
	python gen.py > build/code.tex
	cp tex/* build/
	cd build && xelatex main.tex
	cd build && xelatex main.tex


.PHONY: clean check
check:
	true # code valid check

clean:
	rm -rf build/