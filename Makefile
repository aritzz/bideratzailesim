CC=gcc
CFLAGS=-I./src

all: clean bideratzailea

bideratzailea: src/bideratzailea.o src/bideratzea.o
	@$(CC) -o bideratzailea src/bideratzailea.o src/bideratzea.o
	@echo Konpilazioa bukatuta, exekutagarria direktorioan eskuragarri duzu

clean:
	@rm -f bideratzailea
	@rm -f src/*.o
	@echo Exekutagarri eta objetu fitxategi guztiak ezabatu dira
