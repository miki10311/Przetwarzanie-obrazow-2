#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"struktura.h"

/* podane naglowki odwoluja sie do funkcji, ktore wykonuja operacje na pliku PPM - kolor zielony */



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
void negatywz (ob *obraz);




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
void progowaniez (ob *obraz,int prog);




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
void pol_prog_czerniz (ob *obraz,int progc);




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
void pol_prog_bieliz (ob *obraz,int progb);




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
void zmiana_poziomowz (ob *obraz,int czern,int biel);




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
void rozm_pionowez (ob *obraz);




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
void rozm_poziomez (ob *obraz);




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
void konturowaniez (ob *obraz);




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
void kor_gammaz (ob *obraz,double gamma);




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
void histogramz (ob *obraz);
