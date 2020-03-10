/*Pankkiautomaatti*/
/*Tekijä Eetu Väänänen*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void tulostaSaldo(void);
void talletaRahaa(void);
void nostaRahaa(void);

void kysyPin(void);
void kysyTilinumero(void);
void kaynnistaKayttoliittyma(void);
void paivitaSaldo(void);

int lueKokonaisluku(void);
bool onkoSaldoa(int summa);

int saldo,tilinro,pinkoodi;

FILE* tiedosto;

/* Main funktiossa kutsutaan ensin funktiota kysyTilinumero, jonka avulla kysytaan käyttäjältä tilinumero.
   Tämän jälkeen kutsutaan kysyPin funktiota, joka kysyy käyttäjltä PIN-koodin. Jos PIN-koodi on oikein,
   käynnistetään käyttöliittymä kutsumalla kaynnistaKayttoliittyma-funtiota.
*/
int main(void) {

    kysyTilinumero();

    kysyPin();

    kaynnistaKayttoliittyma();

    return 0;
}
/*
Funktio tulostaSaldo tulostaa tilin saldon kokonaislukuna
Funktio on void-tyyppinen, eikä palauta mitään, eikä myöskään tarvitse parametreja.
*/
void tulostaSaldo(void) {
    printf("Tilisi saldo on %d euroa\n",saldo);
}
/*
Funkrio talletaRahaa tallettaa tilille käyttäjän syöttämän summan. Summa syötetään kokonaislukuna.
Funktio on void-tyyppinen, eikä palauta mitään, eikä myöskään tarvitse parametreja.
*/
void talletaRahaa(void) {
    int summa;

    printf("Syota talletettava summa: \n");
    summa = lueKokonaisluku();

    if (summa < 0) {
        printf("Summan pitaa olla positiviinen!\n");
    } else {
        saldo+=summa;
        paivitaSaldo();
        printf("Talletit %d euroa, tilisi saldo on nyt %d euroa.\n",summa,saldo);
    }
}

/*Funktio onkoSaldoa on Boolean-tyyppinen ja se ottaa parametrina kokonaisluvun ja tarkistaa, onko tilin saldo sama tai suurempi kuin
annettu luku. Jos se on, palautetaan true. Muuten palautetaan false.
*/
bool onkoSaldoa(int summa) {

    if (saldo - summa >= 0 && summa <=1000 && summa >=0) {
        return true;
    } else {
        return false;
    }
}

/*
Funktio nostaRahaa nostaa tililta käyttajän syottämän summan. Mikäli tilin saldo on suurempi tai sama
kuin summa, tilin saldosta vähennetään summma ja tulostetaan nostettu summa seka tilin tämänhetkinen saldo.
Funktio on void-tyyppinen, eikä palauta mitään, eikä myöskään tarvitse parametreja.
*/
void nostaRahaa(void) {
    int summa;

    printf("Syota nostettava summa, summan tulee olla vahintaan 20 euroa.\n");
    summa = lueKokonaisluku();

/*Tarkistetaan, onko tilillä riittävästi rahaa summan nostamiseen.*/
    if(onkoSaldoa(summa)) {

        /*Jos summa on tasan jaollinen 50:lla, annetaan summa pelkastään 50:n euron seteleinä.*/
        if(summa % 50 == 0) {
            saldo-=summa;
            paivitaSaldo();
            printf("Nostit %d euroa %d x 50:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,(summa/50),saldo);

            /*Jos summa voidaan antaa 50:n sekä 20:n euron seteleinä*/
        } else if ((summa %50) %20 == 0 && summa > 100) {
            saldo-=summa;
            paivitaSaldo();
            printf("Nostit %d euroa %d x 50:n euron ja %d x 20:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,((summa-(summa%50)) / 50), (summa%50 / 20),saldo);

            /*Jos summaa ei mene tasan jaettaessa 50:lla ja 20:lla, niin annetaan suurin osa summasta 20:n euron seteleinä,
              ja loppuosa 50:n euron seteleinä.*/
        } else if (summa % 50 % 20 % 10 == 0 && summa > 100) {
            saldo-=summa;
            paivitaSaldo();

            int viisikymppiset = (summa - (summa % 50)) /50 - 1;
            int kaksikymppiset = (summa - viisikymppiset * 50) / 20;

            printf("Nostit %d euroa %d x 50:n euron ja %d x 20:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,viisikymppiset,kaksikymppiset,saldo);

            /*Jos summa on alle 100 euroa, ja se menee tasan jaettaessa 20:lla, annetaan summa 20:n euron seteleinä.*/
        } else if (summa % 20 == 0 && summa < 100) {
            saldo-=summa;
            paivitaSaldo();
            printf("Nostit %d euroa %d x 20:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,(summa / 20),saldo);

            /*Jos summa on 70 tai 90 euroa*/
        } else if (summa == 70 && summa < 100 || summa == 90 && summa < 100) {
            saldo-=summa;
            paivitaSaldo();
            printf("Nostit %d euroa %d x 50:n euron ja %d x 20:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,1,(summa-50) / 20,saldo);

            /*Jos summa ei ole jaettavissa 20:n tai 50:n euron seteleina*/
        } else {
            printf("Automaatissa on vain 20:n ja 50:n euron seteleita, joten summan\n"
                   "pitaa olla joko 20 euroa, 40 euroa tai enemman, 10:n euron valein.\n"
                   "Suurin kertanosto on 1000 euroa.\n");
        }
        /*Jos summa on yli 1000 euroa*/
    } else if (summa > 1000) {
        printf("Automaatista voi nostaa enintaan 1000 euroa kerralla!\n");

        /*Jos summa on negatiivinen*/
    } else if (summa < 0) {
        printf("Summan pitaa olla positiivinen!\n");

        /*Jos tililla ei ole riittavasti saldoa.*/
    } else {
        printf("Tilillasi ei ole tarpeeksi rahaa!\n");
    }
}
/*
Funktio lueKokonaisluku tarkistaa, että käyttäjän syöttämä luku on kokonaisluku.
Funktio on int-tyyppinen ja palauttaa kokonaisluvun.
*/
int lueKokonaisluku(void){

   int luku,status;
   char s;

   while((status = scanf("%d%c", &luku, &s))==0  || (2 == status && s != '\n') ){
      while( fgetc(stdin) != '\n');
      printf("Et syottanyt kokonaislukua, syota kokonaisluku: ");
   }
   return luku;
}

/*
Funktio kysyTilinumero kysyy käyttäjältä tilinumeron. Tilinumeron perusteella etsitään tiedostoa muodossa *käyttäjän syöte*.tili, eli
esimerkiksi jos käyttäjä syöttää tilinumeroksi 12345, etsitään tiedostoa nimeltä 12345.tili. Jos sen niminen tiedosto löytyy, se avataan
ja sieltä luetaan PIN-koodi ja saldo jotka talletetaan muuttujiin.
Funktio on void-tyyppinen, eikä palauta mitään, eikä myöskään tarvitse parametreja.
*/
void kysyTilinumero(void) {
    printf("Tervetuloa pankkiautomaattiin!\n\n");

    while (1) {
        printf("Syota tilinumero: \n");

        char tilinumero[20];

        tilinro = lueKokonaisluku();
        char lukujono[25];

        sprintf(lukujono, "%d",tilinro);
        strcpy(tilinumero,lukujono);

        char teksti[20] = ".tili";
        strcat(tilinumero,teksti);

        tiedosto = fopen(tilinumero,"r");

        if(tiedosto == NULL) {
            printf("Tilia ei voida avata.(Vaara tilinumero?)\n");
        } else {
            fscanf(tiedosto, "%d&d",&pinkoodi);

            while(!feof(tiedosto)) {
                fscanf(tiedosto, "%d%d",&saldo);
            }
            fclose(tiedosto);
            break;
        }
    }
}
/*
Funktio kysyPin kysyy käyttäjältä PIN-koodia. Käyttäjän syöttämää PIN-koodia verrataan tiedostosta luettuun PIN-koodiin
ja jos se täsmää, poistutaan funktiosta. Jos se ei täsmää, kysytään PIN-koodia uudestaan. Käyttäjällä on kolme yritystä
käytössään. Jos kolmannellakaan kerralla PIN-koodi ei ole oikea, poistutaan ohjelmasta.
Funktio on void-tyyppinen, eikä palauta mitään, eikä myöskään tarvitse parametreja.
*/
void kysyPin(void) {
    int syotettyPinkoodi;
    int yritykset = 3;

    printf("Tili loytyi.\n");

    while (1) {
        printf("Syota PIN-koodi: ");
        syotettyPinkoodi = lueKokonaisluku();

        if (syotettyPinkoodi == pinkoodi) {
            break;
        } else {
            yritykset--;
            if(yritykset !=0) {
                printf("Vaara PIN-koodi. Syota PIN-koodi uudestaan. Yrityksia jaljella: %d\n",yritykset);
            } else {
                printf("Liian monta vaaraa PIN-koodia. Yrita uudelleen myohemmin.\n");
                exit(0);
            }
        }
    }
}
/*
Funktio paivitaSaldo päivittää .tili-tiedostoon uuden saldon.
Ensin muutetaan globaali muuttuja int tilinro merkkijonoksi, johon liitetään perään .tili, ja näin
avataan tili muokkausta varten. Tiliin päivitetään sama vanha tilinumero ja  uusi saldo käyttämällä hyväksi globaalia saldo-muuttujaa.
Funktio ei palauta mitään, silla se on void-tyyppinen.
*/
void paivitaSaldo(void) {

    char lukujono[20];

    sprintf(lukujono, "%d",tilinro);
    char teksti[20] = ".tili";
    strcat(lukujono,teksti);
    tiedosto = fopen(lukujono,"w");

    if (tiedosto == NULL) {
        printf("Tilin paivitykessa tapahtui virhe.\n");
    } else {
        fprintf(tiedosto, "%d\n%d\n",pinkoodi,saldo);
        fclose(tiedosto);
    }
}


/*
Funktio kaynnistaKayttoliittyma käynnistää pankkiautomaatin käyttöliittymän. Käyttöliittymän komennot on toutettu käyttämällä switch-valintarakennetta.
Käyttöliittymä sisältää seuraavat komennot:
0. Poistu - poistuu käyttöliittymästä. 1. - Talleta rahaa - kutsuu talletaRahaa-funktiota.
2. Nosta rahaa - kutsuu nostaRahaa-funktiota. 3. - Näytä tilin saldo - kutsuu tulostaSaldo-funktiota.
Jos käyttäjä syöttää komennon, joka ei ole mikään yllä mainituista, tulostetaan että komento on väärä.
Funktio on void-tyyppinen, eikä palauta mitään, eikä myöskään tarvitse parametreja.
*/
void kaynnistaKayttoliittyma(void) {

    bool lopetus;
    int komento;

    printf("\nTervetuloa!\n\n");

    printf("Komennot: \n"
               "0. Poistu \n"
               "1. Talleta rahaa\n"
               "2. Nosta rahaa\n"
               "3. Nayta tilin saldo\n");

    while (!lopetus) {

            printf("Syota komento: ");
            komento = lueKokonaisluku();

            switch(komento) {
                case 0:
                    printf("Tervetuloa uudelleen!\n");
                    lopetus = true;
                    break;

                case 1:
                    talletaRahaa();
                    break;

                case 2:
                    nostaRahaa();
                   break;

                case 3:
                   tulostaSaldo();
                   break;

                default:
                    printf("Vaara komento! Komennon pitaa olla valilla 0-4. Yrita uudestaan.\n");
                    break;
            }
    }
}
