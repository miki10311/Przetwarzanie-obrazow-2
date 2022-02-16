#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"struktura.h"

/* podane naglowki odwoluja sie do funkcji, ktore wykonuja operacje na pliku PPM - kolor niebieski */



/***********************************************************/
/* Funkcja wykonuje negatyw                                */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PPM          */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void negatywn (ob *obraz);




/***********************************************************/
/* Funkcja wykonuje progowanie                             */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/*   prog - wartosc progu podana przez uzytkownika         */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PPM i prog   */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void progowanien (ob *obraz,int prog);




/***********************************************************/
/* Funkcja wykonuje polprogowanie czerni                   */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/*   progc - wartosc progu podana przez uzytkownika        */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PPM i progc  */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void pol_prog_czernin (ob *obraz,int progc);




/***********************************************************/
/* Funkcja wykonuje polprogowanie bieli                    */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/*   progb - wartosc progu podana przez uzytkownika        */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PPM i progb  */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void pol_prog_bielin (ob *obraz,int progb);




/****************************************************************/
/* Funkcja wykonuje zmiane poziomow                             */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/*   czern - zmiana poziomu czerni w %                          */
/*   biel - zmiana poziomu bieli w %                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PPM, czern i biel */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void zmiana_poziomown (ob *obraz,int czern,int biel);




/****************************************************************/
/* Funkcja wykonuje rozmywanie pionowe                          */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PPM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void rozm_pionowen (ob *obraz);




/****************************************************************/
/* Funkcja wykonuje rozmywanie poziome                          */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PPM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void rozm_poziomen (ob *obraz);




/****************************************************************/
/* Funkcja wykonuje konturowanie                                */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PPM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void konturowanien (ob *obraz);




/****************************************************************/
/* Funkcja wykonuje korekcje gamma                              */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/*   gamma - wspolczynnik gamma                                 */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PPM i gamma       */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void kor_gamman (ob *obraz,double gamma);




/****************************************************************/
/* Funkcja wykonuje rozciaganie histogramu                      */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PPM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void histogramn (ob *obraz);
