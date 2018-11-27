DOT=dot
LATEXMK=latexmk

all: klassendiagrammFlappyWizard.pdf klassendiagrammHighscoreServer.pdf
	$(LATEXMK) -pdf main.tex

klassendiagrammHighscoreServer.pdf: klassendiagrammHighscoreServer.dot
	$(DOT) -Tpdf -o klassendiagrammHighscoreServer.pdf klassendiagrammHighscoreServer.dot

klassendiagrammFlappyWizard.pdf: klassendiagrammFlappyWizard.dot
	$(DOT) -Tpdf -o klassendiagrammFlappyWizard.pdf klassendiagrammFlappyWizard.dot

clean:
	$(LATEXMK) -c
	rm *.pdf
