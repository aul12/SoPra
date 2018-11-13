DOT=dot
LATEXMK=latexmk

all: anwendungsfall.pdf zustandsdiagramm.pdf main.tex
	$(LATEXMK) -pdf main.tex

anwendungsfall.pdf: anwendungsfall.dot
	$(DOT) -Tpdf -o anwendungsfall.pdf anwendungsfall.dot

zustandsdiagramm.pdf: zustandsdiagramm.dot
	$(DOT) -Tpdf -o zustandsdiagramm.pdf zustandsdiagramm.dot

clean:
	$(LATEXMK) -c
	rm *.pdf
