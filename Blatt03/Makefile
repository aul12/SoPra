DOT=dot
LATEXMK=latexmk
INKSCAPE=inkscape

all: anwendungsfall.pdf zustandsdiagramm.pdf main.tex
	$(LATEXMK) -silent -pdf main.tex

anwendungsfall.pdf: anwendungsfall.dot spieler.png
	$(DOT) -Tpdf -o anwendungsfall.pdf anwendungsfall.dot

zustandsdiagramm.pdf: zustandsdiagramm.dot
	$(DOT) -Tpdf -o zustandsdiagramm.pdf zustandsdiagramm.dot

spieler.png: spieler.svg
	$(INKSCAPE) -w 450 -h 750 -e spieler.png spieler.svg

clean:
	$(LATEXMK) -c
	rm *.pdf
	rm spieler.png
