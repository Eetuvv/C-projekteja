/*Pankkiautomaatti*/
/*Tekij� Eetu V��n�nen*/

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

/* Main funktiossa kutsutaan ensin funktiota kysyTilinumero, jonka avulla kysytaan k�ytt�j�lt� tilinumero.
   T�m�n j�lkeen kutsutaan kysyPin funktiota, joka kysyy k�ytt�jlt� PIN-koodin. Jos PIN-koodi on oikein,
   k�ynnistet��n k�ytt�liittym� kutsumalla kaynnistaKayttoliittyma-funtiota.
*/
int main(void) {

    kysyTilinumero();

    kysyPin();

    kaynnistaKayttoliittyma();

    return 0;
}
/*
Funktio tulostaSaldo tulostaa tilin saldon kokonaislukuna
Funktio on void-tyyppinen, eik� palauta mit��n, eik� my�sk��n tarvitse parametreja.
*/
void tulostaSaldo(void) {
    printf("Tilisi saldo on %d euroa\n",saldo);
}
/*
Funkrio talletaRahaa tallettaa tilille k�ytt�j�n sy�tt�m�n summan. Summa sy�tet��n kokonaislukuna.
Funktio on void-tyyppinen, eik� palauta mit��n, eik� my�sk��n tarvitse parametreja.
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
Funktio nostaRahaa nostaa tililta k�yttaj�n syott�m�n summan. Mik�li tilin saldo on suurempi tai sama
kuin summa, tilin saldosta v�hennet��n summma ja tulostetaan nostettu summa seka tilin t�m�nhetkinen saldo.
Funktio on void-tyyppinen, eik� palauta mit��n, eik� my�sk��n tarvitse parametreja.
*/
void nostaRahaa(void) {
    int summa;

    printf("Syota nostettava summa, summan tulee olla vahintaan 20 euroa.\n");
    summa = lueKokonaisluku();

/*Tarkistetaan, onko tilill� riitt�v�sti rahaa summan nostamiseen.*/
    if(onkoSaldoa(summa)) {

        /*Jos summa on tasan jaollinen 50:lla, annetaan summa pelkast��n 50:n euron setelein�.*/
        if(summa % 50 == 0) {
            saldo-=summa;
            paivitaSaldo();
            printf("Nostit %d euroa %d x 50:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,(summa/50),saldo);

            /*Jos summa voidaan antaa 50:n sek� 20:n euron setelein�*/
        } else if ((summa %50) %20 == 0 && summa > 100) {
            saldo-=summa;
            paivitaSaldo();
            printf("Nostit %d euroa %d x 50:n euron ja %d x 20:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,((summa-(summa%50)) / 50), (summa%50 / 20),saldo);

            /*Jos summaa ei mene tasan jaettaessa 50:lla ja 20:lla, niin annetaan suurin osa summasta 20:n euron setelein�,
              ja loppuosa 50:n euron setelein�.*/
        } else if (summa % 50 % 20 % 10 == 0 && summa > 100) {
            saldo-=summa;
            paivitaSaldo();

            int viisikymppiset = (summa - (summa % 50)) /50 - 1;
            int kaksikymppiset = (summa - viisikymppiset * 50) / 20;

            printf("Nostit %d euroa %d x 50:n euron ja %d x 20:n euron seteleina. Tilisi saldo on nyt %d euroa.\n",summa,viisikymppiset,kaksikymppiset,saldo);

            /*Jos summa on alle 100 euroa, ja se menee tasan jaettaessa 20:lla, annetaan summa 20:n euron setelein�.*/
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
Funktio lueKokonaisluku tarkistaa, ett� k�ytt�j�n sy�tt�m� luku on kokonaisluku.
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
Funktio kysyTilinumero kysyy k�ytt�j�lt� tilinumeron. Tilinumeron perusteella etsit��n tiedostoa muodossa *k�ytt�j�n sy�te*.tili, eli
esimerkiksi jos k�ytt�j� sy�tt�� tilinumeroksi 12345, etsit��n tiedostoa nimelt� 12345.tili. Jos sen niminen tiedosto l�ytyy, se avataan
ja sielt� luetaan PIN-koodi ja saldo jotka talletetaan muuttujiin.
Funktio on void-tyyppinen, eik� palauta mit��n, eik� my�sk��n tarvitse parametreja.
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
Funktio kysyPin kysyy k�ytt�j�lt� PIN-koodia. K�ytt�j�n sy�tt�m�� PIN-koodia verrataan tiedostosta luettuun PIN-koodiin
ja jos se t�sm��, poistutaan funktiosta. Jos se ei t�sm��, kysyt��n PIN-koodia uudestaan. K�ytt�j�ll� on kolme yrityst�
k�yt�ss��n. Jos kolmannellakaan kerralla PIN-koodi ei ole oikea, poistutaan ohjelmasta.
Funktio on void-tyyppinen, eik� palauta mit��n, eik� my�sk��n tarvitse parametreja.
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
Funktio paivitaSaldo p�ivitt�� .tili-tiedostoon uuden saldon.
Ensin muutetaan globaali muuttuja int tilinro merkkijonoksi, johon liitet��n per��n .tili, ja n�in
avataan tili muokkausta varten. Tiliin p�ivitet��n sama vanha tilinumero ja  uusi saldo k�ytt�m�ll� hyv�ksi globaalia saldo-muuttujaa.
Funktio ei palauta mit��n, silla se on void-tyyppinen.
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
Funktio kaynnistaKayttoliittyma k�ynnist�� pankkiautomaatin k�ytt�liittym�n. K�ytt�liittym�n komennot on toutettu k�ytt�m�ll� switch-valintarakennetta.
K�ytt�liittym� sis�lt�� seuraavat komennot:
0. Poistu - poistuu k�ytt�liittym�st�. 1. - Talleta rahaa - kutsuu talletaRahaa-funktiota.
2. Nosta rahaa - kutsuu nostaRahaa-funktiota. 3. - N�yt� tilin saldo - kutsuu tulostaSaldo-funktiota.
Jos k�ytt�j� sy�tt�� komennon, joka ei ole mik��n yll� mainituista, tulostetaan ett� komento on v��r�.
Funktio on void-tyyppinen, eik� palauta mit��n, eik� my�sk��n tarvitse parametreja.
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
