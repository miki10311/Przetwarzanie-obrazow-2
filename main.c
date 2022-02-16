#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"podstawa.h"
#include"funkcje.h"
#include"funkcjec.h"
#include"funkcjez.h"
#include"funkcjen.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************************************/
/* Ten fragment kodu jest inspirowany kodem pomocniczym udostepnionym na stronie kursu */

#define OK 0                     /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct
{
    FILE *plik_we, *plik_wy;                             /* uchwyty do pliku wej. i wyj. */
    int negatyw,progowanie,konturowanie,wyswietlenie,pol_prog_czerni,pol_prog_bieli,zmiana_poziomow,rozm_poziome,rozm_pionowe,kor_gamma,histogram;      /* opcje przetwarzania */
    int w_progu, progc, progb, czern, biel;              /* wartosci potrzebne dla niektorych funkcji */
    double gamma;
    char kolor;                                          /* zmienna przechowujaca kolor, ktory ma byc edytowany */
    char *nazwa;                                         /* zmienna przechowujaca nazwe pliku */
} w_opcje;

/***********************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor       */
/* Argumenty funkcji:                                      */
/*   wybor - struktura z informacjami o wywolanych opcjach */
/* PRE:                                                    */
/*      poprawnie zainicjowany argument wybor (!=NULL)     */
/* POST:                                                   */
/*      "wyzerowana" struktura wybor wybranych opcji       */
/***********************************************************/

void wyzeruj_opcje(w_opcje *wybor)
{
    wybor->plik_we=NULL;
    wybor->plik_wy=NULL;
    wybor->negatyw=0;
    wybor->konturowanie=0;
    wybor->progowanie=0;
    wybor->wyswietlenie=0;
    wybor->pol_prog_czerni=0;
    wybor->pol_prog_bieli=0;
    wybor->zmiana_poziomow=0;
    wybor->rozm_poziome=0;
    wybor->rozm_pionowe=0;
    wybor->kor_gamma=0;
    wybor->histogram=0;
    // zerujemy cala strukture na wszelki wypadek ze wzgledu na pamiec smieciowa
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu:                                   */
/*   program {[-i nazwa] [-o nazwa] [-m kolor] [-p liczba] [-pc liczba] */
/*   [-pb liczba] [-g liczba] [-z liczba liczba] [-n] [-rx] [-ry] [-k]  */
/*   [-h] [-d]}                                                         */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybor, do tego ustawia na 1 pola, ktore            */
/*	poprawnie wystapily w linii wywolania programu,                     */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;         */
/*	zwraca wartosc OK, gdy wywolanie bylo poprawne                      */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                         */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int opcje (int argc, char **argv, w_opcje *wybor)
{
    int i;                       
    int  prog, progc, progb, czern, biel;  /* wartosci potrzebne w niektorych funkcjach */
    double gamma;
    char *nazwa_pliku_we, *nazwa_pliku_wy; /* zmienne przechowujace nazwy plikow wejsciowego i wyjsciowego */

    wyzeruj_opcje(wybor);                  /* wywolanie funkcji wyzerowania opcji  */
    wybor->plik_wy=stdout;                 /* na wypadek gdy nie podano opcji "-o" */

    for (i=1; i<argc; i++)
    {
        if (argv[i][0] != '-')             /* blad: to nie jest opcja - brak znaku "-" */
            return B_NIEPOPRAWNAOPCJA;
        

        switch (argv[i][1])
        {

        //wczytywanie pliku
        case 'i':                          /* opcja z nazwa pliku wejsciowego */
        {
            if (++i<argc)                  /* wczytujemy kolejny argument jako nazwe pliku */
            {
                nazwa_pliku_we=argv[i];
                if (strcmp(nazwa_pliku_we,"-")==0)       /* gdy nazwa jest "-"        */
                    wybor->plik_we=stdin;                /* ustwiamy wejscie na stdin */
                else                                     /* otwieramy wskazany plik   */
                    wybor->plik_we=fopen(nazwa_pliku_we,"r");
            }
            else
                return B_BRAKNAZWY;                      /* blad: brak nazwy pliku */
            break;
        }
        
        //zapisywanie pliku
        case 'o':                           /* opcja z nazwa pliku wyjsciowego */
        {
            if (++i<argc)                   /* wczytujemy kolejny argument jako nazwe pliku */
            {
                nazwa_pliku_wy=argv[i];
                wybor->nazwa=argv[i];
                if (strcmp(nazwa_pliku_wy,"-")==0)       /* gdy nazwa jest "-"         */
                    wybor->plik_wy=stdout;               /* ustwiamy wyjscie na stdout */
                else                                     /* otwieramy wskazany plik    */
                    wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
            }
            else
                return B_BRAKNAZWY;                      /* blad: brak nazwy pliku */
            break;
        }

        //wybor koloru do edycji
        case 'm':
        {
            if (++i<argc && (argv[i][0]=='r' || argv[i][0]=='b' || argv[i][0]=='g' || argv[i][0]=='s'))
            {
                wybor->kolor=argv[i][0];     /* wczytujemy kolejny argument jako wartosc koloru */
            }
            else if (argv[i][0]=='-')
                return B_BRAKWARTOSCI;       /* blad: brak wartosci koloru */
            else 
                return B_NIEPOPRAWNAOPCJA;
            break;
        }

        //wyswietlenie obrazu
        case 'd':
        {
            wybor->wyswietlenie=1;           /* zmiana wartosci na 1, co spowoduje wykonanie */
            break;
        }
        
        //progowania
        case 'p':
        {
            if (argv[i][2]=='c')                 /* wartosc progowania czerni */
            {
                if (++i<argc)                    /* wczytujemy kolejny argument jako wartosc progu */
                {
                    if (sscanf(argv[i],"%d",&progc)==1)
                    {
                        wybor->pol_prog_czerni=1;   /* zmiana wartosci na 1, co spowoduje wykonanie */
                        wybor->progc=progc;
                    }
                    else
                        return B_BRAKWARTOSCI;       /* blad: brak wartosci progu */
                }
                else
                    return B_BRAKWARTOSCI;       /* blad: brak wartosci progu */
            }
            else if (argv[i][2]=='b')            /* wartosc progowania bieli */
            {
                if (++i<argc)                    /* wczytujemy kolejny argument jako wartosc progu */
                {
                    if (sscanf(argv[i],"%d",&progb)==1)
                    {
                        wybor->pol_prog_bieli=1;     /* zmiana wartosci na 1, co spowoduje wykonanie */
                        wybor->progb=progb;
                    }
                    else
                        return B_BRAKWARTOSCI;       /* blad: brak wartosci progu */
                }
                else
                    return B_BRAKWARTOSCI;       /* blad: brak wartosci progu */
            }
            else if (argv[i][2]==0)
            {
                if (++i<argc)                    /* wczytujemy kolejny argument jako wartosc progu */
                {
                    if (sscanf(argv[i],"%d",&prog)==1)
                    {
                        wybor->progowanie=1;         /* zmiana wartosci na 1, co spowoduje wykonanie */
                        wybor->w_progu=prog;
                    }
                    else
                        return B_BRAKWARTOSCI;        /* blad: brak wartosci progu */
                }
                else
                    return B_BRAKWARTOSCI;                /* blad: brak wartosci */
            }
            break;
        }
        
        
        //negatyw
        case 'n':
        {
            wybor->negatyw=1;         /* zmiana wartosci na 1, co spowoduje wykonanie */
            break;
        }
        
        
        //konturowanie
        case 'k':
        {
            wybor->konturowanie=1;     /* zmiana wartosci na 1, co spowoduje wykonanie */
            break;
        }
        
        //zmiana poziomow
        case 'z':
        {
            if (++i<argc && argv[i][2]!='-')
            {
                if (sscanf(argv[i],"%d",&czern)==1)
                {
                    wybor->czern=czern; /* wczytujemy kolejny argument jako wartosc czerni */
                }
                else
                    return B_BRAKWARTOSCI;
            }

            if (++i<argc)
            {
                if (sscanf(argv[i],"%d",&biel)==1)
                {
                    wybor->biel=biel;   /* wczytujemy kolejny argument jako wartosc bieli */
                }
                else
                    return B_BRAKWARTOSCI;
            }

            wybor->zmiana_poziomow=1;   /* zmiana wartosci na 1, co spowoduje wykonanie  */
            break;
        }
        
        //rozmywanie poziomow
        case 'r':
        {
            if (argv[i][2]=='x')
            {
                wybor->rozm_poziome=1;   /* zmiana wartosci na 1, co spowoduje wykonanie */
            }
            else if (argv[i][2]=='y')
            {
                wybor->rozm_pionowe=1;   /* zmiana wartosci na 1, co spowoduje wykonanie */
            }
            else
                return B_NIEPOPRAWNAOPCJA;
            break;
        }
        
        //korekcja gamma
        case 'g':
        {
            if (++i<argc)
            {
                if (sscanf(argv[i],"%lf",&gamma)==1)
                {
                    wybor->kor_gamma=1;  /* zmiana wartosci na 1, co spowoduje wykonanie  */
                    wybor->gamma=gamma;  /* wczytujemy kolejny argument jako wartosc gamma */
                }
                else
                    return B_BRAKWARTOSCI;
            }
            else
                return B_BRAKWARTOSCI;
            break;
        }

        //rozciaganie histogramu
        case 'h':
        {
            wybor->histogram=1;          /* zmiana wartosci na 1, co spowoduje wykonanie  */
            break;
        }
        
        default:
            return B_NIEPOPRAWNAOPCJA;

        } /*koniec switch */
    }     /* koniec for   */

    if (wybor->plik_we!=NULL)       /* ok: wej. strumien danych zainicjowany */
        return OK;
    else
        return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}


/*******************************************************************/
/* Funkcja rozpoznaje argumenty wywolania opcji i wykonuje na nich */
/* operacje odwolujac sie do struktury obraz                       */
/* Argumenty funkcji:                                              */
/*         wybor - struktura z informacjami o wywolanych opcjach   */
/* PRE:                                                            */
/*    poprawnie wczytane opcje, aby mozna bylo odpowiednio dobrac  */
/*    argumenty                                                    */
/* POST:                                                           */
/*    funkcja wykonuje wskazane operacje na odpowiednich formatach */
/*    formatach obrazkow i odpowiednich kolorach (dla formatu PPM) */
/*                                                                 */
/*    dzieki strukturze obraz funkcja ma dostep do obrazka i       */
/*    zmienia go poprzez odwolania do odpowiednich funkji          */
/*******************************************************************/

void argumenty(w_opcje *wybor)
{
    ob obraz;                                    /* zmienna odwolujaca sie do struktury z pliku struktura.h */

    czytaj(wybor->plik_we,&obraz);                      
    fclose(wybor->plik_we); 


    if(wybor->kolor == 's')                      /* dla kolor == s jest wykonywana funkcja konwersji */
    {
        if(obraz.znak != '2')
        {
            konwersja(&obraz);
        }
        else
        {
            printf("Nie wykonano konwersji, podales obrazek PGM \n");
        }                                       /* warunek na wypadek checi uzytkownika do wykonania konwersji na szarym obrazku */
    }


    if(wybor->negatyw)                          /* sprawdzenie wyboru uzytkownika */
    {
        if(obraz.znak == '2')                   /* wykonanie funkcji ponizej dla obrazku PGM */
        {
            negatyw(&obraz);
        }
        else                                    /* wykonanie funkcji ponizej dla obrazku PPM */
        {                                       /* jezeli nie podamy dla ktorego koloru chcemy wykonac operacje, to operacje wykonuja sie dla wszystkich kolorow */
            if(wybor->kolor == 'r')
            negatywc(&obraz);                   /* funkcja dla koloru czerwonego (nazwa zakonczona na litere c) */
            else if(wybor->kolor == 'g')
            negatywz(&obraz);                   /* funkcja dla koloru zielonego (nazwa zakonczona na litere z) */
            else if(wybor->kolor == 'b')
            negatywn(&obraz);                   /* funkcja dla koloru niebieskiego (nazwa zakonczona na litere n) */
            else
            {
                negatywc(&obraz);
                negatywz(&obraz);
                negatywn(&obraz);
            }
        }
    }
    /* Powyzsze komentarze odnosza sie do kazdej opcji znajdujacych sie wewnatrz funkcji argumenty */


    if(wybor->konturowanie)
    {
        if(obraz.znak == '2')
        {
            konturowanie(&obraz);
        }
        else
        {
            if(wybor->kolor == 'r')
            konturowaniec(&obraz);
            else if(wybor->kolor == 'g')
            konturowaniez(&obraz);
            else if(wybor->kolor == 'b')
            konturowanien(&obraz);
            else
            {
                konturowaniec(&obraz);
                konturowaniez(&obraz);
                konturowanien(&obraz);
            }
        }
    }


    if(wybor->progowanie)
    {
        if(obraz.znak == '2')
        {
            if (wybor->w_progu<=100 && wybor->w_progu>=0)              /* Warunek wynikajacy z podawania progu w procentach */
            {
                progowanie(&obraz,wybor->w_progu);
            }
            else
            {
                printf("Nie wykonano progowania, zla wartosc progu \n");
            }
        }
        else
        {
            if (wybor->w_progu<=100 && wybor->w_progu>=0)              /* Warunek wynikajacy z podawania progu w procentach */
            {
                if(wybor->kolor == 'r')
                progowaniec(&obraz,wybor->w_progu);
                else if(wybor->kolor == 'g')
                progowaniez(&obraz,wybor->w_progu);
                else if(wybor->kolor == 'b')
                progowanien(&obraz,wybor->w_progu);
                else
                {
                    progowaniec(&obraz,wybor->w_progu);
                    progowaniez(&obraz,wybor->w_progu);
                    progowanien(&obraz,wybor->w_progu);
                }
            }
            else
            {
                printf("Nie wykonano progowania, zla wartosc progu \n");
            }
        }
    }


    if(wybor->pol_prog_czerni)
    {
        if(obraz.znak == '2')
        {
            if (wybor->progc<=100 && wybor->progc>=0)              /* Warunek wynikajacy z podawania progu w procentach */
            {
                pol_prog_czerni(&obraz,wybor->progc);
            }
            else
            {
                printf("Nie wykonano progowania, zla wartosc progu czerni \n");
            }
        }
        else
        {
            if (wybor->progc<=100 && wybor->progc>=0)              /* Warunek wynikajacy z podawania progu w procentach */
            {
                if(wybor->kolor == 'r')
                pol_prog_czernic(&obraz,wybor->progc);
                else if(wybor->kolor == 'g')
                pol_prog_czerniz(&obraz,wybor->progc);
                else if(wybor->kolor == 'b')
                pol_prog_czernin(&obraz,wybor->progc);
                else
                {
                    pol_prog_czernic(&obraz,wybor->progc);
                    pol_prog_czerniz(&obraz,wybor->progc);
                    pol_prog_czernin(&obraz,wybor->progc);
                }
            }
            else
            {
                printf("Nie wykonano progowania, zla wartosc progu czerni \n");
            }
        }
    }


    if(wybor->pol_prog_bieli)
    {
        if(obraz.znak == '2')
        {
            if (wybor->progb<=100 && wybor->progb>=0)              /* Warunek wynikajacy z podawania progu w procentach */
            {
            pol_prog_bieli(&obraz,wybor->progb);
            }
            else
            {
                printf("Nie wykonano progowania, zla wartosc progu bieli \n");
            }
        }
        else
        {
            if (wybor->progb<=100 && wybor->progb>=0)              /* Warunek wynikajacy z podawania progu w procentach */
            {
                if(wybor->kolor == 'r')
                pol_prog_bielic(&obraz,wybor->progb);
                else if(wybor->kolor == 'g')
                pol_prog_bieliz(&obraz,wybor->progb);
                else if(wybor->kolor == 'b')
                pol_prog_bielin(&obraz,wybor->progb);
                else
                {
                    pol_prog_bielic(&obraz,wybor->progb);
                    pol_prog_bieliz(&obraz,wybor->progb);
                    pol_prog_bielin(&obraz,wybor->progb);
                }
            }
            else
            {
                printf("Nie wykonano progowania, zla wartosc progu bieli \n");
            }
        }
    }


    if(wybor->zmiana_poziomow)
    {
        if(obraz.znak == '2')
        {
            if ((wybor->czern>=0 && wybor->czern<=100) && (wybor->biel>=0 && wybor->biel<=100) && wybor->czern<wybor->biel)
            {                                                           /* Warunki wynikajace z wlasnosci zmiany poziomow */
                zmiana_poziomow(&obraz,wybor->czern,wybor->biel);
            }
            else
            {
                printf("Nie wykonano zmiany poziomow, nie spelnasz co najmniej jednego z warunkow:\n1. czern i biel naleza do przedzialu (0,100)\n2. czern < biel \n");
            }
        }
        else
        {
            if ((wybor->czern>=0 && wybor->czern<=100) && (wybor->biel>=0 && wybor->biel<=100) && wybor->czern<wybor->biel)
            {                                                           /* Warunki wynikajace z wlasnosci zmiany poziomow */
                if(wybor->kolor == 'r')
                zmiana_poziomowc(&obraz,wybor->czern,wybor->biel);
                else if(wybor->kolor == 'g')
                zmiana_poziomowz(&obraz,wybor->czern,wybor->biel);
                else if(wybor->kolor == 'b')
                zmiana_poziomown(&obraz,wybor->czern,wybor->biel);
                else
                {
                    zmiana_poziomowc(&obraz,wybor->czern,wybor->biel);
                    zmiana_poziomowz(&obraz,wybor->czern,wybor->biel);
                    zmiana_poziomown(&obraz,wybor->czern,wybor->biel);
                }
            }
            else
            {
                printf("Nie wykonano zmiany poziomow, nie spelnasz co najmniej jednego z warunkow:\n1. czern i biel naleza do przedzialu (0,100)\n2. czern < biel \n");
            }
        }
    }


    if(wybor->rozm_poziome)
    {
        if(obraz.znak == '2')
        {
            rozm_poziome(&obraz);
        }
        else
        {
            if(wybor->kolor == 'r')
            rozm_poziomec(&obraz);
            else if(wybor->kolor == 'g')
            rozm_poziomez(&obraz);
            else if(wybor->kolor == 'b')
            rozm_poziomen(&obraz);
            else
            {
                rozm_poziomec(&obraz);
                rozm_poziomez(&obraz);
                rozm_poziomen(&obraz);
            }
        }
    }


    if(wybor->rozm_pionowe)
    {
        if(obraz.znak == '2')
        {
            rozm_pionowe(&obraz);
        }
        else
        {
            if(wybor->kolor == 'r')
            rozm_pionowec(&obraz);
            else if(wybor->kolor == 'g')
            rozm_pionowez(&obraz);
            else if(wybor->kolor == 'b')
            rozm_pionowen(&obraz);
            else
            {
                rozm_pionowec(&obraz);
                rozm_pionowez(&obraz);
                rozm_pionowen(&obraz);
            }
        }
    }


    if(wybor->kor_gamma)
    {
        if(obraz.znak == '2')
        {
            if (wybor->gamma>=0)               /* Warunek wynikajacy z wlasnosci korekcji gamma */
            {
                kor_gamma(&obraz,wybor->gamma);
            }
            else
            {
                printf("Nie wykonano korekcji gamma, zla wartosc wspolczynnika \n");
            }
        }
        else
        {
            if (wybor->gamma>=0)               /* Warunek wynikajacy z wlasnosci korekcji gamma */
            {
                if(wybor->kolor == 'r')
                kor_gammac(&obraz,wybor->gamma);
                else if(wybor->kolor == 'g')
                kor_gammaz(&obraz,wybor->gamma);
                else if(wybor->kolor == 'b')
                kor_gamman(&obraz,wybor->gamma);
                else
                {
                    kor_gammac(&obraz,wybor->gamma);
                    kor_gammaz(&obraz,wybor->gamma);
                    kor_gamman(&obraz,wybor->gamma);
                }
            }
            else
            {
                printf("Nie wykonano korekcji gamma, zla wartosc wspolczynnika \n");
            }
        }
    }


    if(wybor->histogram)
    {
        if(obraz.znak == '2')
        {
            histogram(&obraz);
        }
        else
        {
            if(wybor->kolor == 'r')
            histogramc(&obraz);
            else if(wybor->kolor == 'g')
            histogramz(&obraz);
            else if(wybor->kolor == 'b')
            histogramn(&obraz);
            else
            {
                histogramc(&obraz);
                histogramz(&obraz);
                histogramn(&obraz);
            }
        }
    }


    zapis(wybor->plik_wy,&obraz);                                
    fclose(wybor->plik_wy);

    if(wybor->wyswietlenie)
    {
        wyswietl(wybor->nazwa);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************************************/

/* Funkcja glowna */
int main(int argc, char **argv)
{
    int blad;                                     /* zmienna przechowujaca informacje o bledzie */
    w_opcje wybor;                                /* odwolanie do struktury wybor */
    if((blad=opcje(argc,argv,&wybor))==0)         /* sprawdzenie bledow */
        argumenty(&wybor);  
    else
        printf("Blad\nKod bledu: %d \n", blad);  /* wyswietlenie komunikatu o bledzie */
    return 0;
}
