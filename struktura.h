#ifndef struktura_h
#define struktura_h


#include<stdio.h>

struct obraz
{
    int wymx;      /* wymiary obrazka */
    int wymy;
    int szarosci;  /* liczba odcieni szarosci lub liczba odcieni danego koloru */
    int **tab;     /* tablica uzywana do przechowywania obrazka PGM */
    char znak;     /* zmienna przechowujaca znak obrazka */
    int **czer;    /* tablice przechowujace informacje o kolorach pikseli w obrazku PPM */
    int **ziel;
    int **nieb;
};
typedef struct obraz ob;     /* definiujemy typ zmiennej odwolujacej sie do danej struktury */


#endif