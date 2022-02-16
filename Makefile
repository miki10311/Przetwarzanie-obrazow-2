all:
	clear
	/bin/sh instrukcja.sh
	gcc -Wall -pedantic funkcje.c funkcje.h podstawa.c podstawa.h struktura.h main.c funkcjec.c funkcjec.h funkcjez.c funkcjez.h funkcjen.c funkcjen.h -lm

