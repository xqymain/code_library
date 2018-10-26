SRCS=$(shell find src/) $(shell find tex/)

build/main.pdf: $(SRCS) Makefile scl.yaml clean update
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

update:
	cd src/ && rm * -rf
	cd src/ && git submodule init && git submodule update --remote
	cd src/ACM-Code-Library/ && rm -rf .idea/ cmake-build-debug/ .git/ && rm -f .gitignore README.md CMakeLists.txt
	cd src/ && mv ACM-Code-Library/* ./ && rm -rf ACM-Code-Library
