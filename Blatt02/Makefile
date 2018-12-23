DOT=dot
LATEXMK=latexmk

all: uml.pdf
	$(LATEXMK) -silent -pdf main.tex

uml.pdf: uml.dot
	$(DOT) -Tpdf -o uml.pdf uml.dot

clean:
	$(LATEXMK) -c
	rm *.pdf
