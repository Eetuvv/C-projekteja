#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

char ruutu[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
void aloitaPeli(void);
void ruudukko(void);
void arvoVuoro(void);

void peliOhje(void);
void teeSiirto(void);

bool onkoTaynna(void);
bool onkoVoittaja(void);
void kukaVoitti(void);

int lueKokonaisluku(void);

bool vuoro; /* True = Pelaaja1:n vuoro, False = Pelaaja2:n vuoro */

int main(void) {
    char merkki[2];

    peliOhje();

    printf("Paina enter aloittaaksesi: ");
    scanf("%c",&merkki);

    aloitaPeli();

    return 0;
}

void peliOhje(void) {

    printf("Tervetuloa Ristinolla-peliin!\n");
    printf("Tassa pelissa sinun tulee valita ruudukosta ruutu valilta 1-9\n");
    printf("ja yrittaa saada kolme samaa merkkia perakkain.\n\n");

    printf("1|2|3\n");

    printf("_|_|_\n");

    printf("4|5|6\n");
    printf("_|_|_\n");
    printf("7|8|9\n");

    printf("\n\n");
}
void aloitaPeli(void){

    printf("\n-------------RISTINOLLA----------\n\n\n");

    arvoVuoro();

    while (1) {

        ruudukko();

        if (onkoTaynna() == 0 && onkoVoittaja() == 0) {
            teeSiirto();
        } else if (onkoTaynna() == 1 && onkoVoittaja() == 0) {
            printf("Peli paattyi tasapeliin!\n");
            break;
        } else {
            kukaVoitti();
            break;
        }
    }

}
void arvoVuoro(void) {

    printf("---------Arvotaan aloittaja!---------\n\n\n");

    srand(time(NULL));
    int aloittaja = rand()%2;

    if (aloittaja == 1) {
        printf("          Pelaaja 1 aloittaa!\n\n");
        vuoro = true;
    } else {
        printf("          Pelaaja2 aloittaa!\n\n");
        vuoro = false;
    }
    printf("\n");
}

void teeSiirto(void) {
    int luku;

    if(vuoro == true) {

        while (1) {

            printf("Pelaaja 1: Syota ruutu valilta (1-9): ");
            luku = lueKokonaisluku();

            while (luku <=0 || luku >=10) {
                printf("Luku pitaa olla valilta 1-9, syota uusi luku: ");
                luku = lueKokonaisluku();
            }
            if (ruutu[luku] == ' ') {
                ruutu[luku] = 'X';
                vuoro = false;
                break;
            } else {
                printf("Ruutu %d on jo pelattu.\n",luku);
            }
        }

    } else if (vuoro == false) {

        while (1) {

            printf("Pelaaja 2: Syota ruutu valilta (1-9): ");
            luku = lueKokonaisluku();

            while (luku <=0 || luku >=10) {
                printf("Luku pitaa olla valilta 1-9, syota uusi luku: ");
                luku = lueKokonaisluku();
            }


            if (ruutu[luku] == ' ') {
                ruutu[luku] = 'O';
                vuoro = true;
                break;
            } else {
                printf("Ruutu %d on jo pelattu.\n",luku);
            }

        }
    }

    printf("\n");
}
void ruudukko(void) {

    printf("Pelaaja 1: X         Pelaaja 2: O \n\n\n");

    printf("              %c|%c|%c\n",ruutu[1],ruutu[2],ruutu[3]);

    printf("              _|_|_\n");

    printf("              %c|%c|%c\n",ruutu[4],ruutu[5],ruutu[6]);
    printf("              _|_|_\n");
    printf("              %c|%c|%c\n",ruutu[7],ruutu[8],ruutu[9]);
}
int lueKokonaisluku(void){

   int luku;
   char merkki;
   int status;

   while((status = scanf("%d%c", &luku, &merkki))==0  || (2 == status && merkki != '\n') ){
      while(fgetc(stdin) != '\n');
      printf("Et syottanyt kokonaislukua, syota kokonaisluku: ");
   }

   return luku;
}

bool onkoTaynna(void) {

    int ruudut = 0;

    for (int i = 1; i <= 9; i++) {
        if (ruutu[i] != ' ') {
            ruudut++;
        } else {
            ruudut+=0;
        }
    }

    if (ruudut == 9) {
        return true;
    } else {
        return false;
    }
}

bool onkoVoittaja(void) {

    if(ruutu[1] != ' ' && ruutu[2] != ' ' && ruutu[3] != ' '
       && ruutu[1] == ruutu[2] && ruutu[2] == ruutu[3]) {
           return true;
    } else if (ruutu[4] != ' ' && ruutu[5] != ' ' && ruutu[6] != ' '
        && ruutu[4] == ruutu[5] && ruutu[5] == ruutu[6]) {
            return true;
    } else if (ruutu[7] != ' ' && ruutu[6] != ' ' && ruutu[7] != ' '
        && ruutu[7] == ruutu[8] && ruutu[5] == ruutu[9]) {
            return true;
    } else if (ruutu[1] != ' ' && ruutu[5] != ' ' && ruutu[9] != ' '
        && ruutu[1] == ruutu[5] && ruutu[5] == ruutu[9]) {
            return true;
    } else if (ruutu[7] != ' ' && ruutu[5] != ' ' && ruutu[3] != ' '
        && ruutu[7] == ruutu[5] && ruutu[5] == ruutu[3]) {
            return true;
    } else if (ruutu[1] != ' ' && ruutu[4] != ' ' && ruutu[7] != ' '
        && ruutu[1] == ruutu[4] && ruutu[4] == ruutu[7]) {
            return true;
    } else if (ruutu[2] != ' ' && ruutu[5] != ' ' && ruutu[8] != ' '
        && ruutu[2] == ruutu[5] && ruutu[5] == ruutu[8]) {
            return true;
    } else if (ruutu[3] != ' ' && ruutu[6] != ' ' && ruutu[9] != ' '
        && ruutu[3] == ruutu[6] && ruutu[6] == ruutu[9]) {
            return true;
    } else {
        return false;
    }
}

void kukaVoitti(void) {

    printf("Peli paattyi!\n");

    if (vuoro == 1) {
        printf("Voittaja on pelaaja 2!\n");
    } else {
        printf("Voittaja on pelaaja 1!\n");
    }
}
