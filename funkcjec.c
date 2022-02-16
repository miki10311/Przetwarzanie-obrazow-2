#include"funkcje.h"
/* tutaj sa funkcje do przetwarzanie obrazka PPM - kolor czerwony */

/* zmienna szarosci jest tutaj liczba odcieni danego koloru */


/* Negatyw */
void negatywc (ob *obraz)
{
  int i,j;                                                       /* sa tutaj dwie petle for, ktore sprawiaja, ze kazdy element zapisany w  */
  for (i=0;i<obraz->wymy;i++)                                    /* tablicy zmieni swoja wartosc zgodnie z definicja tworzenia negatywu,   */
  for (j=0;j<obraz->wymx;j++)                                    /* a wiec im 'bielszy' jest element tym bedzie 'ciemniejszy' po wykonaniu */
  obraz->czer[i][j]=obraz->szarosci-obraz->czer[i][j];           /* funkcji. Ta zmiana jest zobrazowana w 4 linijce kodu funkji */ 
}


/* Progowanie */
void progowaniec (ob *obraz,int prog)
{
 int i,j;
 for (i=0;i<obraz->wymy;i++)
 for (j=0;j<obraz->wymx;j++)
  if(obraz->czer[i][j]<=obraz->szarosci*prog/100.0)             /* ten if sprawdza, czy dany piksel jest pod czy nad podanym progiem w %     */
  {          
    obraz->czer[i][j]=0;                                        /* kazda wartosc, ktora jest pod progiem dostaje wartosc 0, a kazda, ktora   */
  }                                                             /* jest nad progiem otrzymuje wartosc rowna maksymalnemu odcieniowi szarosci */
  else
  {
    obraz->czer[i][j]=obraz->szarosci;
  }
}


/* Polprogowanie czerni */
void pol_prog_czernic (ob *obraz,int progc)
{
 int i,j;
 for (i=0; i<obraz->wymy; i++)
 for (j=0; j<obraz->wymx; j++)
  if (obraz->czer[i][j]<=obraz->szarosci*progc/100.0)               /* ten if sprawdza, czy dany piksel jest pod czy nad podanym progiem w %     */
  {          
      obraz->czer[i][j]=0;                                          /* kazda wartosc, ktora jest pod progiem dostaje wartosc 0                   */
  }                                                  
}


/* Polprogowanie bieli */
void pol_prog_bielic (ob *obraz,int progb)
{
 int i,j;
 for (i=0; i<obraz->wymy; i++)
 for (j=0; j<obraz->wymx; j++)
  if (obraz->czer[i][j]>=obraz->szarosci*progb/100.0)               /* ten if sprawdza, czy dany piksel jest pod czy nad podanym progiem w %     */
  {          
      obraz->czer[i][j]=obraz->szarosci;                            /* kazda wartosc, ktora jest nad progiem dostaje wartosc maks liczby odcieni */
  }                                                              
}


/* Zmiana poziomow */
void zmiana_poziomowc (ob *obraz,int czern,int biel)
{
  int i,j;
  int cz,bie;

  cz=obraz->szarosci*czern/100.0;                            /* przedstawienie danych w % */
  bie=obraz->szarosci*biel/100.0;
                                                             /* w podanym warunku sa rozwazone wszystkie przypadki tworzenia nowych poziomow  */
  for (i=0; i<obraz->wymy; i++)                              /* bieli i czerni w programie, podane w pliku z informacjami do tego zadania     */
  for (j=0; j<obraz->wymx; j++)
  {
    if (obraz->czer[i][j]<=cz)                                             
    {                                                        /* wartosci ponizej nowej wartosci czerni otrzymuja wartosc 0 */
      obraz->czer[i][j]=0;                                                
    }     
    else if (cz<obraz->czer[i][j] && obraz->czer[i][j]<bie)  /* wartosci posrednie sa rozciagane na wszystkie poziomy szarosci zawarte w obrazie*/
    {
      obraz->czer[i][j]=(obraz->czer[i][j]-cz)*(obraz->szarosci/(bie-cz));
    }
    else                                                     /* wartosci powyzej nowej wartosci bieli otrzymaja wartosc */
      obraz->czer[i][j]=obraz->szarosci;                     /* maksymalna dla danego programu */
  }
}


/* Rozmywanie poziome */
void rozm_poziomec (ob *obraz)
{
  int i,j;
  for (i=1; i<obraz->wymy-1; i++)     /* w tym miejscu '-1' oraz 'i=1' i 'j=1' w petli, bo w przeciwnym wypadku przejdziemy poza zakres */
  for (j=1; j<obraz->wymx-1; j++)     /* tablicy (segmentation fault), a 1 piksel doda tylko ramke o grubosci 1 piksela */
      obraz->czer[i][j]=(obraz->czer[i-1][j]+obraz->czer[i][j]+obraz->czer[i+1][j])/3;
}


/* Rozmywanie pionowe */
void rozm_pionowec (ob *obraz)
{
  int i,j;
  for (i=0; i<obraz->wymy-1; i++)     /* w tym miejscu '-1' w petli, bo w przeciwnym wypadku przejdziemy poza zakres    */
  for (j=0; j<obraz->wymx-1; j++)     /* tablicy (segmentation fault), a 1 piksel doda tylko ramke o grubosci 1 piksela */
      obraz->czer[i][j]=(obraz->czer[i][j-1]+obraz->czer[i][j]+obraz->czer[i][j+1])/3;
}


/* Konturowanie */
void konturowaniec (ob *obraz) 
{
  int i,j;
  for (i=0;i<obraz->wymy-1;i++)       /* w tym miejscu '-1' w petli, bo w przeciwnym wypadku przejdziemy poza zakres    */
  for (j=0;j<obraz->wymx-1;j++)       /* tablicy (segmentation fault), a 1 piksel doda tylko ramke o grubosci 1 piksela */
      obraz->czer[i][j]=abs(obraz->czer[i+1][j]-obraz->czer[i][j])+abs(obraz->czer[i][j+1]-obraz->czer[i][j]);
}                                                                    /* 'abs' z biblioteki matematycznej to modul */


/* Korekcja gamma */
void kor_gammac (ob *obraz,double gamma)
{
  int i,j;
  double max=obraz->czer[0][0];       /* szukamy wartosci maksymalnej */

  for (i=0; i<obraz->wymy; i++)
  for (j=0; j<obraz->wymx; j++)
  {
      if (max<obraz->czer[i][j])
          max=obraz->czer[i][j];
  }

  double a,b,x;                        /* zmienne pomocnicze, uzyte do realizacji wzoru podanego na stronie kursu */
  for (i=0; i<obraz->wymy-1; i++)                                                   
  for (j=0; j<obraz->wymx-1; j++)
  {                                                   
    a=(obraz->czer[i][j])/max;
    b=(1.0)/gamma;                     /* 1.0 w tym miejscu na wszelki wypadek aby uniknac bledow rzutowania        */
    x=pow(a,b);                        /* pow z biblioteki matematycznej oznacza podnoszenie wartosci a do potegi b */
      
    obraz->czer[i][j]=x*max;
  }
} 


/* Rozciaganie hitogramu */
void histogramc (ob *obraz)                                                 /* moze byc nie zawsze widoczne, bo ta operacja ma sens gdy nie w pelni jest */
{                                                                           /* wykorzystywany zakres odcieni szarosci obrazka */
  int i,j;
  int min=obraz->czer[0][0],max=obraz->czer[0][0];                          /* inicjuje w ten sposob, aby potem porownywac z kazdym innym elementem */
                                                                            /* w ten sposob unikam bledow wartosci skrajnych */
  for (i=0; i<obraz->wymy; i++)
  for (j=0; j<obraz->wymx; j++)
  {
      if (min>obraz->czer[i][j])                                            /* szukanie wartosci minimalnej i maksymalnej odcieni szarosci w calym obrazku */
          min=obraz->czer[i][j];

      if (max<obraz->czer[i][j])
          max=obraz->czer[i][j];
  }
  for (i=0; i<obraz->wymy; i++)
  for (j=0; j<obraz->wymx; j++)
      obraz->czer[i][j]=(obraz->czer[i][j]-min)*(obraz->szarosci/(max-min));      /* rozciaganie wartosci wszystkich pikseli (o ile ma to sens) do wartosci bardziej */
}                                                                                 /* wysrodkowanych; w pelni wykorzystujcych zadeklarowane moliwosci obrazka */
