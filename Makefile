LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds the TRD"
	@echo ""
	@echo "Available commands are:"
	@echo "	make trd          - to build the TRD"
	@echo "	make clean        - to clean up the build process"
	@echo "	make deepclean    - to clean up and remove *.pdf"
	@echo "	make help         - to show this information"
#	@echo "	make showexcluded	- to show files that are not included in the doc"
	@echo ""
	@echo "For more information see the file 'doc/README'"

trd: build
	$(LATEXCMD) content/trd.tex && $(LATEXCMD) content/trd.tex
	cp build/trd.pdf trd.pdf

clean:
	cd build && rm -f trd.aux trd.log trd.tmp trd.toc trd.pdf trd.ptc

deepclean: clean
	rm -f trd.pdf

build:
	mkdir -p build/
