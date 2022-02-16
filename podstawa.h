#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"funkcje.h"

#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */




/***********************************************************/
/* Funkcja odczytuje obrazek                               */
/* Argumenty funkcji:                                      */
/*   plik_we - uchwyt do pliku, ktory ma byc odczytany     */
/*   obrazy - zmienna odwolujaca sie do struktury obraz,   */
/*            gdzie zapisuje kolejne informacje o obrazku  */
/* PRE:                                                    */
/*      obrazek w formacie PGM lub PPM                     */
/* POST:                                                   */
/*      obrazek gotowy do edycji                           */
/***********************************************************/
int czytaj(FILE *plik_we,ob *obrazy);



/***********************************************************/
/* Funkcja wyswietla obrazek za pomoca programu display    */
/* Argumenty funkcji:                                      */
/*   n_pliku - nazwa pliku                                 */
/* PRE:                                                    */
/*      poprawna nazwa pliku do wyswietlenia               */
/* POST:                                                   */
/*      wyswietlenie pliku                                 */
/***********************************************************/
void wyswietl(char *n_pliku);



/**************************************************************/
/* Funkcja zapisuje obrazek                                   */
/* Argumenty funkcji:                                         */
/*  plik - uchwyt do pliku, w ktorym ma byc zapisany obraz    */
/*  obrazy - zmienna odwolujaca sie do struktury obraz,       */
/*           gdzie zapisuje kolejne informacje o obrazku      */
/* PRE:                                                       */
/*      informacje o obrazku przechowywane w strukturze obraz */
/* POST:                                                      */
/*      zapisany obrazek                                      */
/**************************************************************/
void zapis (FILE* plik,ob *obrazy);