#include"podstawa.h"

int czytaj(FILE *plik_we,ob *obrazy)
{
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if (plik_we==NULL)
  {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byc P2 lub P3 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ((buf[0]!='P') || (buf[1]!='2' && buf[1]!='3') || koniec)        /* Czy jest magiczne "P2" lub "P3"? */
  {
    fprintf(stderr,"Blad: To nie jest plik PGM, ani PPM\n");          /* znak dla P2 i P3 */
    return(0);
  }

  obrazy->znak=buf[1]; /* Przechowywanie magicznego znaku obrazka w strukturze */

  /* Pominiecie komentarzy */
  do
  {
    if ((znak=fgetc(plik_we))=='#')            /* Czy linia rozpoczyna sie od znaku '#'? */
    {
      if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Przeczytaj ja do bufora                */
	    koniec=1;                                /* Zapamietaj ewentualny koniec danych    */
    }
    else
    {
      ungetc(znak,plik_we);                    /* Gdy przeczytany znak z poczatku linii */
    }                                          /* nie jest '#' zwroc go                 */
  }while (znak=='#' && !koniec);               /* Powtarzaj dopoki sa linie komentarza  */
                                               /* i nie nastapil koniec danych          */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&obrazy->wymx,&obrazy->wymy,&obrazy->szarosci)!=3) /* Poprzez odcienie szarosci sa tutaj rozumiane rowniez odcienie innych kolorow */
  {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);                                 /* Brak liczby odcieni */
  }


  /* Tablica dynamiczna do przechowywania obrazka */
  obrazy->tab=malloc(obrazy->wymy*sizeof(int*));         /* Rezerwowanie miejsca w pamieci na obrazek */
  for (i=0;i<obrazy->wymy;i++)
  {
    obrazy->tab[i]=malloc(obrazy->wymx*sizeof(int));
  }



  /* Pobranie obrazu i zapisanie w tablicy */
  /* Dla obrazu P2 */
  if(obrazy->znak=='2')                  
  {
    for (i=0;i<obrazy->wymy;i++)
    {
      for (j=0;j<obrazy->wymx;j++)
      {
        if (fscanf(plik_we,"%d",&(obrazy->tab[i][j]))!=1)
        {
          fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
          return(0);
        }
      }
    }
    return obrazy->wymx* obrazy->wymy;   /* Czytanie zakonczone sukcesem */
  }                                      /* Zworc liczbe pikseli */
  /* Dla obrazu P3 */
  else
  {
    obrazy->czer=malloc(obrazy->wymy*sizeof(int*));     /* Tworzenie trzech roznych tablic dynamicznych na kolory RGB */
    obrazy->ziel=malloc(obrazy->wymy*sizeof(int*));
    obrazy->nieb=malloc(obrazy->wymy*sizeof(int*));

    for (i=0;i<obrazy->wymy;i++)
    {
      obrazy->czer[i]=malloc(obrazy->wymx*sizeof(int));
      obrazy->ziel[i]=malloc(obrazy->wymx*sizeof(int));
      obrazy->nieb[i]=malloc(obrazy->wymx*sizeof(int));
    }

    for (i=0;i<obrazy->wymy;i++)
    {
      for (j=0;j<obrazy->wymx;j++)
      {                                  /* Pobieranie kolejnych informacji o kolorach do trzech roznych tablic dynamicznych */
        if (fscanf(plik_we,"%d %d %d",&(obrazy->czer[i][j]),&(obrazy->ziel[i][j]),&(obrazy->nieb[i][j]))!=3)
        {
          fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
          return(0);
        }
      }
    }
  }
  return obrazy->wymx* obrazy->wymy;   /* Czytanie zakonczone sukcesem */
}                                      /* Zwroc liczbe pikseli */






void wyswietl(char *n_pliku) 
{
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}







void zapis (FILE* plik,ob *obrazy)
{

  if(obrazy->znak=='2')
  {
  fprintf (plik, "P2\n");                                        /* Wypisanie do pliku znaku magicznego w 1 linijce */
  fprintf (plik, "%d %d\n",obrazy->wymx, obrazy->wymy);          /* Wypisanie do pliku wymiarow obrazka w 2 linijce */
  fprintf (plik, "%d\n", obrazy->szarosci);                      /* Wypisanie do pliku liczby mowiacej o ilosci odcieni szarosci   */
    int i,j;
    for (i=0;i<obrazy->wymy;i++)                                 /* Wypisywanie do pliku informacji o kolorze kolejnych pikseli,   */
    {                                                            /* za pomoca zwykej petli for */
      for (j=0; j< obrazy->wymx; j++)                            /* Bardzo wazna w tym miejscu jest spacja po '%d', gdyz bez niej  */
      fprintf (plik, "%d ", obrazy->tab[i][j]);                  /* nie bedzie odstepu pomiedzy kolejnymi informacjami o pikselach */
    }                                                            /* i obrazek nie wyswietli sie poprawnie */
  }
  else
  {
  fprintf (plik, "P3\n");                                        /* Wypisanie do pliku znaku magicznego w 1 linijce */
  fprintf (plik, "%d %d\n",obrazy->wymx, obrazy->wymy);          /* Wypisanie do pliku wymiarow obrazka w 2 linijce */
  fprintf (plik, "%d\n", obrazy->szarosci);                      /* Wypisanie do pliku liczby mowiacej o ilosci odcieni kolorow (zmienna szarosci) */
  int i,j;
  for (i=0;i<obrazy->wymy;i++)
    {
      for (j=0; j< obrazy->wymx; j++)
      fprintf (plik, "%d %d %d ", obrazy->czer[i][j],obrazy->ziel[i][j],obrazy->nieb[i][j]);
    }                                                            /* Wypisywanie do pliku informacji o kolorze kolejnych pikseli */
  }
}
