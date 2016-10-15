all:
	./gentex.py > code.tex
	xelatex main.tex
	xelatex main.tex

.PHONY: clean check
check:
	true # code valid check

clean:
	rm -f main.pdf *.aux *.log *.toc
