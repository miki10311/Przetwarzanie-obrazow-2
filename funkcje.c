#include"funkcje.h"
/* Funkcje odpowiadajace za przetwarzanie obrazow PGM oraz funkcja kowersji do szarosci */

/* Konwersja */
void konwersja (ob *obrazpgm)
{
  int i,j;
  obrazpgm->znak='2';                                            /* zmiana magicznego znaku obrazka na P2 */

  /* Tablica dynamiczna do przechowywania obrazka */
  obrazpgm->tab=malloc(obrazpgm->wymy*sizeof(int*));             /* deklarowanie dwuwymiarowej tablicy dynamicznej */
  for (i=0;i<obrazpgm->wymy;i++)                                 /* 'obrazpgm' to nazwa zmiennej */
  {
    obrazpgm->tab[i]=malloc(obrazpgm->wymx*sizeof(int));
  }

  for (i=0;i<obrazpgm->wymy;i++)
  for (j=0;j<obrazpgm->wymx;j++)
  obrazpgm->tab[i][j]=(obrazpgm->czer[i][j]+obrazpgm->nieb[i][j]+obrazpgm->ziel[i][j])/3;
}                                                                /* zapisanie obrazka wedlug wzoru podanego na stronie kursu */




/* Negatyw */
void negatyw (ob *obrazpgm)
{
  int i,j;                                                       /* sa tutaj dwie petle for, ktore sprawiaja, ze kazdy element zapisany w  */
  for (i=0;i<obrazpgm->wymy;i++)                                 /* tablicy zmieni swoja wartosc zgodnie z definicja tworzenia negatywu,   */
  for (j=0;j<obrazpgm->wymx;j++)                                 /* a wiec im 'bielszy' jest element tym bedzie 'ciemniejszy' po wykonaniu */
  obrazpgm->tab[i][j]=obrazpgm->szarosci-obrazpgm->tab[i][j];    /* funkcji. Ta zmiana jest zobrazowana w 4 linijce kodu funkji */ 
}


/* Progowanie */
void progowanie (ob *obrazpgm,int prog)
{
 int i,j;
 for (i=0;i<obrazpgm->wymy;i++)
 for (j=0;j<obrazpgm->wymx;j++)
  if(obrazpgm->tab[i][j]<=obrazpgm->szarosci*prog/100.0)        /* ten if sprawdza, czy dany piksel jest pod czy nad podanym progiem w %     */
  {          
    obrazpgm->tab[i][j]=0;                                      /* kazda wartosc, ktora jest pod progiem dostaje wartosc 0, a kazda, ktora   */
  }                                                             /* jest nad progiem otrzymuje wartosc rowna maksymalnemu odcieniowi szarosci */
  else
  {
    obrazpgm->tab[i][j]=obrazpgm->szarosci;
  }
}


/* Polprogowanie czerni */
void pol_prog_czerni (ob *obrazpgm,int progc)
{
 int i,j;
 for (i=0; i<obrazpgm->wymy; i++)
 for (j=0; j<obrazpgm->wymx; j++)
  if (obrazpgm->tab[i][j]<=obrazpgm->szarosci*progc/100.0)               /* ten if sprawdza, czy dany piksel jest pod czy nad podanym progiem w %     */
  {          
      obrazpgm->tab[i][j]=0;                                             /* kazda wartosc, ktora jest pod progiem dostaje wartosc 0                   */
  }                                                  
}


/* Polprogowanie bieli */
void pol_prog_bieli (ob *obrazpgm,int progb)
{
 int i,j;
 for (i=0; i<obrazpgm->wymy; i++)
 for (j=0; j<obrazpgm->wymx; j++)
  if (obrazpgm->tab[i][j]>=obrazpgm->szarosci*progb/100.0)               /* ten if sprawdza, czy dany piksel jest pod czy nad podanym progiem w %     */
  {          
      obrazpgm->tab[i][j]=obrazpgm->szarosci;                            /* kazda wartosc, ktora jest nad progiem dostaje wartosc maks liczby odcieni */
  }                                                              
}


/* Zmiana poziomow */
void zmiana_poziomow (ob *obrazpgm,int czern,int biel)
{
  int i,j;
  int cz,bie;

  cz=obrazpgm->szarosci*czern/100.0;                            /* przedstawienie danych w % */
  bie=obrazpgm->szarosci*biel/100.0;
                                                                /* w podanym warunku sa rozwazone wszystkie przypadki tworzenia nowych poziomow  */
  for (i=0; i<obrazpgm->wymy; i++)                              /* bieli i czerni w programie, podane w pliku z informacjami do tego zadania     */
  for (j=0; j<obrazpgm->wymx; j++)
  {
    if (obrazpgm->tab[i][j]<=cz)                                             
    {                                                           /* wartosci ponizej nowej wartosci czerni otrzymuja wartosc 0 */
      obrazpgm->tab[i][j]=0;                                                
    }     
    else if (cz<obrazpgm->tab[i][j] && obrazpgm->tab[i][j]<bie) /* wartosci posrednie sa rozciagane na wszystkie poziomy szarosci zawarte w obrazie */
    {
      obrazpgm->tab[i][j]=(obrazpgm->tab[i][j]-cz)*(obrazpgm->szarosci/(bie-cz));
    }
    else                                                        /* wartosci powyzej nowej wartosci bieli otrzymaja wartosc */
      obrazpgm->tab[i][j]=obrazpgm->szarosci;                   /* maksymalna dla danego programu */
  }
}


/* Rozmywanie poziome */
void rozm_poziome (ob *obrazpgm)
{
  int i,j;
  for (i=1; i<obrazpgm->wymy-1; i++)     /* w tym miejscu '-1' oraz 'i=1' i 'j=1' w petli, bo w przeciwnym wypadku przejdziemy poza zakres */
  for (j=1; j<obrazpgm->wymx-1; j++)     /* tablicy (segmentation fault), a 1 piksel doda tylko ramke o grubosci 1 piksela */
      obrazpgm->tab[i][j]=(obrazpgm->tab[i-1][j]+obrazpgm->tab[i][j]+obrazpgm->tab[i+1][j])/3;
}


/* Rozmywanie pionowe */
void rozm_pionowe (ob *obrazpgm)
{
  int i,j;
  for (i=0; i<obrazpgm->wymy-1; i++)     /* w tym miejscu '-1' w petli, bo w przeciwnym wypadku przejdziemy poza zakres    */
  for (j=0; j<obrazpgm->wymx-1; j++)     /* tablicy (segmentation fault), a 1 piksel doda tylko ramke o grubosci 1 piksela */
      obrazpgm->tab[i][j]=(obrazpgm->tab[i][j-1]+obrazpgm->tab[i][j]+obrazpgm->tab[i][j+1])/3;
}


/* Konturowanie */
void konturowanie (ob *obrazpgm) 
{
  int i,j;
  for (i=0;i<obrazpgm->wymy-1;i++)       /* w tym miejscu '-1' w petli, bo w przeciwnym wypadku przejdziemy poza zakres    */
  for (j=0;j<obrazpgm->wymx-1;j++)       /* tablicy (segmentation fault), a 1 piksel doda tylko ramke o grubosci 1 piksela */
      obrazpgm->tab[i][j]=abs(obrazpgm->tab[i+1][j]-obrazpgm->tab[i][j])+abs(obrazpgm->tab[i][j+1]-obrazpgm->tab[i][j]);
}                                                                    /* 'abs' z biblioteki matematycznej to modul */


/* Korekcja gamma */
void kor_gamma (ob *obrazpgm,double gamma)
{
  int i,j;
  double max=obrazpgm->tab[0][0];       /* szukamy wartosci maksymalnej */

  for (i=0; i<obrazpgm->wymy; i++)
  for (j=0; j<obrazpgm->wymx; j++)
  {
      if (max<obrazpgm->tab[i][j])
          max=obrazpgm->tab[i][j];
  }

  double a,b,x;                        /* zmienne pomocnicze, uzyte do realizacji wzoru podanego na stronie kursu */
  for (i=0; i<obrazpgm->wymy-1; i++)                                                   
  for (j=0; j<obrazpgm->wymx-1; j++)
  {                                                   
    a=(obrazpgm->tab[i][j])/max;
    b=(1.0)/gamma;                     /* 1.0 w tym miejscu na wszelki wypadek aby uniknac bledow rzutowania        */
    x=pow(a,b);                        /* pow z biblioteki matematycznej oznacza podnoszenie wartosci a do potegi b */
      
    obrazpgm->tab[i][j]=x*max;
  }
} 


/* Rozciaganie hitogramu */
void histogram (ob *obrazpgm)                                                 /* moze byc nie zawsze widoczne, bo ta operacja ma sens gdy nie w pelni jest */
{                                                                             /* wykorzystywany zakres odcieni szarosci obrazka */
  int i,j;
  int min=obrazpgm->tab[0][0],max=obrazpgm->tab[0][0];                        /* inicjuje w ten sposob, aby potem porownywac z kazdym innym elementem */
                                                                              /* w ten sposob unikam bledow wartosci skrajnych */
  for (i=0; i<obrazpgm->wymy; i++)
  for (j=0; j<obrazpgm->wymx; j++)
  {
      if (min>obrazpgm->tab[i][j])                                            /* szukanie wartosci minimalnej i maksymalnej odcieni szarosci w calym obrazku */
          min=obrazpgm->tab[i][j];

      if (max<obrazpgm->tab[i][j])
          max=obrazpgm->tab[i][j];
  }
  for (i=0; i<obrazpgm->wymy; i++)
  for (j=0; j<obrazpgm->wymx; j++)
      obrazpgm->tab[i][j]=(obrazpgm->tab[i][j]-min)*(obrazpgm->szarosci/(max-min));      /* rozciaganie wartosci wszystkich pikseli (o ile ma to sens) do wartosci bardziej */
}                                                                                        /* wysrodkowanych; w pelni wykorzystujcych zadeklarowane moliwosci obrazka */
