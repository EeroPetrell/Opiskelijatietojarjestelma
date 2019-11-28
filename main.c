#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct opiskelija {
  long long int opiskelijanumero;
  char sukunimi[20];
  char etunimi[20];
  int pisteet[6];
};


struct opiskelija *lisaaOpiskelija(struct opiskelija *opiskelijat, char *opiskelijanumeroOSOITIN, char *sukunimi, char *etunimi) {

  int listanPituus = 0;
  while (1) {
    if (opiskelijat[listanPituus].opiskelijanumero == 0)
      break;
    listanPituus++;
  }
  listanPituus++;

  struct opiskelija *taydennettyOpiskelijat = realloc(opiskelijat, (listanPituus + 1) * sizeof(struct opiskelija));
  if (taydennettyOpiskelijat == NULL)
    return NULL;

  long long int opiskelijanumero;
  sscanf(opiskelijanumeroOSOITIN, "%lli", &opiskelijanumero);
  if (sizeof(opiskelijanumero) != sizeof(opiskelijanumeroOSOITIN)) {
    printf("EI-NUMEERINEN OPISKELIJANUMERO\n");
    return opiskelijat;
  }

  if (opiskelijanumero == 0) {
    printf("Opiskelijanumero 0 on varattu ohjelman omaan käyttöön.\nValitse toinen opiskelijanumero.\n");
    return opiskelijat;
  }

  for (int i = 0; i < listanPituus; i++) {
    if (taydennettyOpiskelijat[i].opiskelijanumero == opiskelijanumero) {
      printf("OPISKELIJANUMERO ON JO TIEDOSTOSSA\n");
      return opiskelijat;
    }
  }

  taydennettyOpiskelijat[listanPituus - 1].opiskelijanumero = opiskelijanumero;
  strcpy(taydennettyOpiskelijat[listanPituus - 1].etunimi, etunimi);
  strcpy(taydennettyOpiskelijat[listanPituus - 1].sukunimi, sukunimi);
  taydennettyOpiskelijat[listanPituus - 1].pisteet[0] = 0;
  taydennettyOpiskelijat[listanPituus - 1].pisteet[1] = 0;
  taydennettyOpiskelijat[listanPituus - 1].pisteet[2] = 0;
  taydennettyOpiskelijat[listanPituus - 1].pisteet[3] = 0;
  taydennettyOpiskelijat[listanPituus - 1].pisteet[4] = 0;
  taydennettyOpiskelijat[listanPituus - 1].pisteet[5] = 0;

  taydennettyOpiskelijat[listanPituus].opiskelijanumero = 0;//opiskelijanumeroa 0 käytetään lopetusmerkkinä

  return taydennettyOpiskelijat;
}


int paivitaPisteet(struct opiskelija *opiskelijat, char *opiskelijanumeroOSOITIN, char *kierrosOSOITIN, char *pisteetOSOITIN) {

  long long int opiskelijanumero;
  int kierros, pisteet;
  int paluuarvo1 = sscanf(opiskelijanumeroOSOITIN, "%lli", &opiskelijanumero);
  int paluuarvo2 = sscanf(kierrosOSOITIN, "%d", &kierros);
  int paluuarvo3 = sscanf(pisteetOSOITIN, "%d", &pisteet);

  if (paluuarvo1 != 1)
    return -4;

  if (paluuarvo2 != 1)
    return -5;

  if (paluuarvo3 != 1)
    return -6;

  if (opiskelijanumero == 0)
    return -1;

  int listanKoko;
  for (listanKoko = 0; opiskelijat[listanKoko].opiskelijanumero != 0; listanKoko++);

  int etsittavaOpiskelija = -1;
  int i = 0;
  while (i < listanKoko) {
    if (opiskelijat[i].opiskelijanumero == opiskelijanumero)
      etsittavaOpiskelija = i;
    i++;
  }

  if (etsittavaOpiskelija == -1)
    return -1;

  if (kierros > 6)
    return -2;

  if (kierros < 1)
    return -3;

  opiskelijat[etsittavaOpiskelija].pisteet[kierros - 1] += pisteet;
  return 1;
}


int laskePisteet(struct opiskelija *opiskelijat, int indeksi) {
  //Toimii apufunktiona järjestämiselle
  int summa = 0;
  for (int i = 0; i < 6; i++) {
    summa += opiskelijat[indeksi].pisteet[i];
  }
  return summa;
}


int etsiSuurimmanIndeksiAlkaen(struct opiskelija *opiskelijat, int indeksiAlkaen) {
  //Toimii apufunktiona järjestämiselle
  int listanKoko;
  for (listanKoko = 0; opiskelijat[listanKoko].opiskelijanumero != 0; listanKoko++);

  int suurinPistemaara = laskePisteet(opiskelijat, indeksiAlkaen);
  int suurimmanIndeksi = indeksiAlkaen;

  while (indeksiAlkaen < listanKoko) {
    if (laskePisteet(opiskelijat, indeksiAlkaen) > suurinPistemaara) {
      suurinPistemaara = laskePisteet(opiskelijat, indeksiAlkaen);
      suurimmanIndeksi = indeksiAlkaen;
    }
    indeksiAlkaen++;
  }
  return suurimmanIndeksi;
}


void vaihdaOpiskelijatKeskenaan(struct opiskelija *opiskelijat, int a, int b) {
  //Toimii apufunktiona järjestämiselle
  //a ja b keskenään paikkaa vaihtavien opiskelijoiden indeksit
  if (a != b) {
    long long int numero = opiskelijat[a].opiskelijanumero;
    char sukunimi[20];
    strcpy(sukunimi, opiskelijat[a].sukunimi);
    char etunimi[20];
    strcpy(etunimi, opiskelijat[a].etunimi);
    int kierros1 = opiskelijat[a].pisteet[0];
    int kierros2 = opiskelijat[a].pisteet[1];
    int kierros3 = opiskelijat[a].pisteet[2];
    int kierros4 = opiskelijat[a].pisteet[3];
    int kierros5 = opiskelijat[a].pisteet[4];
    int kierros6 = opiskelijat[a].pisteet[5];

    opiskelijat[a].opiskelijanumero = opiskelijat[b].opiskelijanumero;
    strcpy(opiskelijat[a].sukunimi, opiskelijat[b].sukunimi);
    strcpy(opiskelijat[a].etunimi, opiskelijat[b].etunimi);
    opiskelijat[a].pisteet[0] = opiskelijat[b].pisteet[0];
    opiskelijat[a].pisteet[1] = opiskelijat[b].pisteet[1];
    opiskelijat[a].pisteet[2] = opiskelijat[b].pisteet[2];
    opiskelijat[a].pisteet[3] = opiskelijat[b].pisteet[3];
    opiskelijat[a].pisteet[4] = opiskelijat[b].pisteet[4];
    opiskelijat[a].pisteet[5] = opiskelijat[b].pisteet[5];

    opiskelijat[b].opiskelijanumero = numero;
    strcpy(opiskelijat[b].sukunimi, sukunimi);
    strcpy(opiskelijat[b].etunimi, etunimi);
    opiskelijat[b].pisteet[0] = kierros1;
    opiskelijat[b].pisteet[1] = kierros2;
    opiskelijat[b].pisteet[2] = kierros3;
    opiskelijat[b].pisteet[3] = kierros4;
    opiskelijat[b].pisteet[4] = kierros5;
    opiskelijat[b].pisteet[5] = kierros6;
  }
}


void jarjestaOpiskelijat(struct opiskelija *opiskelijat) {
  //Toimii apufunktiona tulostamiselle
  int listanKoko, i = 0;
  for (listanKoko = 0; opiskelijat[listanKoko].opiskelijanumero != 0; listanKoko++);

  while (i < listanKoko) {
    int vaihdettava = etsiSuurimmanIndeksiAlkaen(opiskelijat, i);
    vaihdaOpiskelijatKeskenaan(opiskelijat, i, vaihdettava);
    i++;
  }
}


int tulostaTilanne(struct opiskelija *opiskelijat) {

  jarjestaOpiskelijat(opiskelijat);

  int listanKoko;
  for (listanKoko = 0; opiskelijat[listanKoko].opiskelijanumero != 0; listanKoko++);

  if (listanKoko == 0) {
    printf("Ei tallennettuja opiskelijoita\n");
    return -1;
  }

  int i = 0;
  while (i < listanKoko) {
    printf("%-7lli %-12s %-8s %3d %3d %3d %3d %3d %3d  %4d\n", opiskelijat[i].opiskelijanumero, opiskelijat[i].sukunimi, opiskelijat[i].etunimi,
    opiskelijat[i].pisteet[0], opiskelijat[i].pisteet[1], opiskelijat[i].pisteet[2], opiskelijat[i].pisteet[3], opiskelijat[i].pisteet[4],
    opiskelijat[i].pisteet[5], laskePisteet(opiskelijat, i));
    i++;
  }
  return 1;
}


int tallennaTulokset(struct opiskelija *opiskelijat, char *tiedostonimi) {

  jarjestaOpiskelijat(opiskelijat);
  FILE *tulokset = fopen(tiedostonimi, "w");

  int listanKoko;
  for (listanKoko = 0; opiskelijat[listanKoko].opiskelijanumero != 0; listanKoko++);

  if (listanKoko == 0) {
    printf("Ei tallennettuja opiskelijoita\n");
    return -1;
  }

  for (int i = 0; i < listanKoko; i++) {
    fprintf(tulokset, "%-7lli %-12s %-8s %-3d %-3d %-3d %-3d %-3d %-3d  %4d\n", opiskelijat[i].opiskelijanumero, opiskelijat[i].sukunimi, opiskelijat[i].etunimi,
    opiskelijat[i].pisteet[0], opiskelijat[i].pisteet[1], opiskelijat[i].pisteet[2], opiskelijat[i].pisteet[3], opiskelijat[i].pisteet[4],
    opiskelijat[i].pisteet[5], laskePisteet(opiskelijat, i));
  }
  fclose(tulokset);
  return 1;
}


struct opiskelija *lataaTulokset(struct opiskelija *opiskelijat, char *tiedostonimi) {

  FILE *tulokset = fopen(tiedostonimi, "r");
  if (!tulokset) {
    printf("TIEDOSTOA EI LÖYDY\n");
    return opiskelijat;
  }

  char opiskelijanumero[8], sukunimi[20], etunimi[20], kierros1[4], kierros2[4], kierros3[4], kierros4[4], kierros5[4], kierros6[4];
  opiskelijat[0].opiskelijanumero = 0; //"nollaa" listan. realloc ensimmäisen lisaaOpiskelija-funktion suorituksessa hoitaa todellisen muistivarauksen muutoksen

  while (1) {

    int i = 0;
    char syote[101];
    while (i < 100) {
      fscanf(tulokset, "%c",&syote[i]);
      if (syote[i] == '\n')
        break;
      i++;
    }
    syote[i] = '\0';

    if (feof(tulokset))
      break;

    int parsittu = sscanf(syote, "%s %s %s %s %s %s %s %s %s",
    opiskelijanumero, sukunimi, etunimi, kierros1, kierros2, kierros3, kierros4, kierros5, kierros6);

    if (parsittu != 9) {
      printf("VIRHEELLINEN TIEDOSTO\n");
      return NULL;
    }

    opiskelijat = lisaaOpiskelija(opiskelijat, opiskelijanumero, sukunimi, etunimi);
    if (opiskelijat == NULL) {
      printf("MUISTIVIRHE\n");
      return NULL;
    }

    paivitaPisteet(opiskelijat, opiskelijanumero, "1", kierros1);
    paivitaPisteet(opiskelijat, opiskelijanumero, "2", kierros2);
    paivitaPisteet(opiskelijat, opiskelijanumero, "3", kierros3);
    paivitaPisteet(opiskelijat, opiskelijanumero, "4", kierros4);
    paivitaPisteet(opiskelijat, opiskelijanumero, "5", kierros5);
    paivitaPisteet(opiskelijat, opiskelijanumero, "6", kierros6);
  }

  fclose(tulokset);
  printf("Tulokset ladattu\n");
  return opiskelijat;
}


void nimienTarkistus(struct opiskelija *opiskelijat) {

}


int main(void) {

  struct opiskelija *opiskelijat;
  opiskelijat = malloc(sizeof(struct opiskelija));
  if (opiskelijat == NULL) {
    printf("MUISTINVARAUSVIRHE\n");
    return 0;
  }

  opiskelijat[0].opiskelijanumero = 0; //opiskelijanumeroa 0 käytetään lopetusmerkkinä

  char komento;
  char syote1[20], syote2[20], syote3[20];
  /*Esitellään neljä muuttuja käyttäjän syötteen lukemiseen: "komento"
  ensimmäistä merkkiä varten, kolme muuta vaihtuviin tarkoituksiin
  funktioiden parametrien antamiseksi.*/

  int virheita = 0;
  int paluuarvo;
  int listanKoko = 0;

  printf("\nTällä demo-ohjelmalla käsitellään opiskelijatietoja kuvitteellisella yliopistokurssilla.\n\
Jokaisella kurssin opiskelijalla on kuusinumeroinen opiskelijnumero, suku- ja etunimet sekä kurssipisteitä kuudelta erilliseltä kierrokselta.\n\n\
Ohjelmaa käytetään seuraavin komennoin (syötä komento + paina enter):\n\
A opiskelijanumero sukunimi etunimi       -   lisää uusi opiskelija\n\
U opiskelijanumero kierrosnumero pisteet  -   lisää opiskelijalle pisteitä\n\
L                                         -   tulosta tiedot päätteelle\n\
W luotavan tiedoston nimi                 -   tallenna tiedot tiedostoon\n\
O ladattavan tiedoston nimi               -   lataa tiedot tiedostosta (tulee sijaita samassa kansiossa ohjelman kanssa)\n\
Q                                         -   sulje ohjelma (tallentamattomat tiedot häviävät)\n");

  while (1) {

    printf("\n");

    int i = 0;
    char syote[81];
    while (i < 80) {
      scanf("%c",&syote[i]);
      if (syote[i] == '\n')
        break;
      i++;
    }
    syote[i] = '\0';

    int parsittu = sscanf(syote, "%c %s %s %s", &komento, syote1, syote2, syote3);

    if (parsittu == -1) {
      printf("TYHJÄ SYÖTE\n");
      continue;
    } else if (komento == 'Q') {
      free(opiskelijat);
      break;
    }

    switch(komento) {

      case 'A': //opiskelijan lisäys
        if (parsittu != 4) {
          printf("VAJAA SYÖTE - SYÖTÄ OPISKELIJANUMERO SEKÄ SUKU- JA ETUNIMI\n");
          break;
        }
        opiskelijat = lisaaOpiskelija(opiskelijat, syote1, syote2, syote3);
        if (opiskelijat == NULL) {
          printf("MUISTIVIRHE\n");
        } else {
          int listanKokoEnnenLisaysta = listanKoko;
          for (listanKoko = 0; opiskelijat[listanKoko].opiskelijanumero != 0; listanKoko++);
          if (listanKoko != listanKokoEnnenLisaysta) {
            printf("Opiskelija lisätty\n");
          }
        }
        break;

      case 'U': //pisteiden lisäys
        if (parsittu != 4) {
          printf("VAJAA SYÖTE - SYÖTÄ OPISKELIJANUMERO, KIERROKSEN NUMERO JA PISTEET\n");
          break;
        }
        paluuarvo = paivitaPisteet(opiskelijat, syote1, syote2, syote3);
        if (paluuarvo == -1) {
          printf("OPISKELIJANUMEROA EI LÖYDY\n");
        } else if (paluuarvo == -2) {
          printf("LIIAN SUURI KIERROKSEN NUMERO\n");
        } else if (paluuarvo == -3) {
          printf("LIIAN PIENI KIERROKSEN NUMERO\n");
        } else if (paluuarvo == -4) {
          printf("EI-NUMEERINEN OPISKELIJANUMERO\n");
        } else if (paluuarvo == -5) {
          printf("EI-NUMEERINEN KIERROKSEN NUMERO\n");
        } else if (paluuarvo == -6) {
          printf("EI-NUMEERINEN PISTEMÄÄRÄ\n");
        } else {
          printf("Pisteet lisätty\n");
        }
        break;

      case 'L': //tietojen tulostus näytölle
        tulostaTilanne(opiskelijat);
        break;

      case 'W': //tietojen tallennus tiedostoon
        if (parsittu < 2) {
          printf("VAJAA SYÖTE - SYÖTÄ MYÖS LUOTAVAN TIEDOSTON NIMI\n");
          break;
        }
        paluuarvo = tallennaTulokset(opiskelijat, syote1);
        if (paluuarvo == 1)
          printf("Tulokset tallennettu\n");
        break;

      case 'O': //tietojen lataus tiedostosta
        if (parsittu < 2) {
          printf("VAJAA SYÖTE - SYÖTÄ MYÖS LADATTAVAN TIEDOSTON NIMI\n");
          break;
        }
        opiskelijat = lataaTulokset(opiskelijat, syote1);
        break;

      default:
        printf("VIRHEELLINEN SYÖTE\n");
        virheita++;
        if (virheita == 8)
          printf("Mitä jos vaikka lukisit käyttöohjeen?\n");
        break;
    }
  }
}
