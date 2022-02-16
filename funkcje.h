#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"struktura.h"

/* podane naglowki odwoluja sie do funkcji, ktore wykonuja operacje na pliku PGM oraz konwersje pliku PPM na PGM */

/***********************************************************/
/* Funkcja wykonuje konwersje obrazow PPM na PGM           */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PPM          */
/* POST:                                                   */
/*      obrazek w formacie PGM                             */
/***********************************************************/
void konwersja (ob *obrazpgm);




/***********************************************************/
/* Funkcja wykonuje negatyw                                */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PGM          */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void negatyw (ob *obrazpgm);




/***********************************************************/
/* Funkcja wykonuje progowanie                             */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/*   prog - wartosc progu podana przez uzytkownika         */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PGM i prog   */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void progowanie (ob *obrazpgm,int prog);




/***********************************************************/
/* Funkcja wykonuje polprogowanie czerni                   */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/*   progc - wartosc progu podana przez uzytkownika        */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PGM i progc  */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void pol_prog_czerni (ob *obrazpgm,int progc);




/***********************************************************/
/* Funkcja wykonuje polprogowanie bieli                    */
/* Argumenty funkcji:                                      */
/*   obraz - struktura z informacjami o wywolanych opcjach */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury */
/*             obraz                                       */
/*   progb - wartosc progu podana przez uzytkownika        */
/* PRE:                                                    */
/*      poprawnie wczytany obrazek w formacie PGM i progb  */
/* POST:                                                   */
/*      obrazek przetworzony wedlug wzoru                  */
/***********************************************************/
void pol_prog_bieli (ob *obrazpgm,int progb);




/****************************************************************/
/* Funkcja wykonuje zmiane poziomow                             */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/*   czern - zmiana poziomu czerni w %                          */
/*   biel - zmiana poziomu bieli w %                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PGM, czern i biel */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void zmiana_poziomow (ob *obrazpgm,int czern,int biel);




/****************************************************************/
/* Funkcja wykonuje rozmywanie pionowe                          */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PGM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void rozm_pionowe (ob *obrazpgm);




/****************************************************************/
/* Funkcja wykonuje rozmywanie poziome                          */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PGM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void rozm_poziome (ob *obrazpgm);




/****************************************************************/
/* Funkcja wykonuje konturowanie                                */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PGM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void konturowanie (ob *obrazpgm);




/****************************************************************/
/* Funkcja wykonuje korekcje gamma                              */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/*   gamma - wspolczynnik gamma                                 */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PGM i gamma       */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void kor_gamma (ob *obrazpgm,double gamma);




/****************************************************************/
/* Funkcja wykonuje rozciaganie histogramu                      */
/* Argumenty funkcji:                                           */
/*   obraz - struktura z informacjami o wywolanych opcjach      */
/*   orazpgm - zmienna typu ob odwolujaca sie do struktury      */
/*             obraz                                            */
/* PRE:                                                         */
/*      poprawnie wczytany obrazek w formacie PGM               */
/* POST:                                                        */
/*      obrazek przetworzony wedlug wzoru                       */
/****************************************************************/
void histogram (ob *obrazpgm);
