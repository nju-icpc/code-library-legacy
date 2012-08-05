all:
	./gentex.py > code.tex
	xelatex main.tex
	xelatex main.tex
clean:
	rm -f main.pdf main.aux main.log
