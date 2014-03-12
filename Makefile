all: check
	./gentex.py > code.tex
	xelatex main.tex
	xelatex main.tex

.PHONY: clean check
check:
	true # code valid check

clean:
	rm -f main.pdf main.aux main.log
