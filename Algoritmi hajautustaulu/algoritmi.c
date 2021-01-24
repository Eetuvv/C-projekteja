#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> //tolower-funktiota varten
#include <time.h>

#define TAULUNKOKO 1000000

struct Sanakirja { //Tietue, jossa avain-arvo parit
    char *avain;
    int arvo;
};

struct sanat { //Tietue, jota käytetään uuden taulukon luomiseen ja järjestämiseen
    char *mki;
    int luku;
};

clock_t start,end;

struct Sanakirja* hashTaulu[TAULUNKOKO]; //Tehdään hash-taulukko, johon lisätään sanakirja-rakenteita joissa avain ja arvo
struct Sanakirja* sana;  //Alustetaan sanakirja-rakenteen mukainen apumuuttuja
int count; //Tähän lasketaan sanojen määrä

void lisaa(char *avain);
unsigned int haeTiiviste(char *avain);
void tulostaSanatJarjestyksessa();
int partition(struct sanat[], int alku, int loppu);
void quicksort(struct sanat[], int alku, int loppu);


unsigned int haeTiiviste(char *avain) {
    //Laskee tiivisteen avaimelle. Käydään läpi merkkijonon merkit, ja kerrotaan tiviiste-muuttuja alkuvulla ja lisätään siihen vielä kirjainta vastaava arvo,
    //jotta pienennetään törmäysten todennäköisyyttä. Lopulta muodostetaan hash-arvo, joka saadaan laskemalla jakojäännös jakamalla laskettu tiiviste-muuttuja taulukon koolla.
    //Tiivisteelle käytetään unsigned-tyyppistä kokonaislukua, jotta mahdollisia negatiivisia lukuja ei oteta huomioon.

    //Funktio löytyi stackoverflowsta
    unsigned int tiiviste = 0;
    for (int i = 0; avain[i]; i++) {
        tiiviste = 31*tiiviste + avain[i];
    }

    return tiiviste % TAULUNKOKO;
}


void lisaa(char *avain) {

    struct Sanakirja *sana = (struct Sanakirja*) malloc(sizeof(struct Sanakirja));//Varataan tilaa mallocilla Sanakirja-oliolle

    sana->arvo = 1;  //Laitetaan arvoksi 1, ja avaimeksi parametrina saatu avain
    sana->avain = avain;

    int hashArvo = haeTiiviste(avain);  //Lasketaan tiiviste avaimelle

    if (hashTaulu[hashArvo] != NULL) {

        if(!strcmp(hashTaulu[hashArvo]->avain, sana->avain)) {  //Jos avain löytyy jo taulukosta, kasvatetaan sen arvoa yhdellä.

            hashTaulu[hashArvo]->arvo += sana->arvo;
            return;
        }
    }

    while(hashTaulu[hashArvo] != NULL) {  //Etsitään taulukosta tyhjää kohtaa, kunnes sellainen löydetään (kun taulukon indeksin arvo on NULL)

        hashArvo++;

        hashArvo %= TAULUNKOKO;
    }

    hashTaulu[hashArvo] = sana; //Lisätään hash-taulukkoon muuttuja sana, jolla on avain ja arvo, kun tyhjä kohta on löydetty.
    count+=1;
}


int partition(struct sanat arr[], int p, int r) { //Quicksort-algoritmin lajittelu-osa

    struct sanat *tmp = (struct sanat*)malloc(sizeof(struct sanat));

    int x = arr[r].luku;
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (arr[j].luku >= x) {
            i+=1;
            tmp->mki = arr[i].mki;
            tmp->luku = arr[i].luku;

            arr[i].mki = arr[j].mki;
            arr[i].luku = arr[j].luku;

            arr[j].mki = tmp->mki;
            arr[j].luku = tmp->luku;
        }
    }

    tmp->luku = arr[i+1].luku;
    tmp->mki = arr[i+1].mki;

    arr[i+1].luku = arr[r].luku;
    arr[i+1].mki = arr[r].mki;

    arr[r].mki = tmp->mki;
    arr[r].luku = tmp->luku;

    return i + 1;
}

void quicksort(struct sanat arr[], int p, int r) { //Luentodiojen mukainen quicksort-algoritmi
    int q;
    if (p < r) {
        q = partition(arr, p, r);
        quicksort(arr, p, q-1);
        quicksort(arr, q+1, r);
    }
}

void tulostaSanatJarjestyksessa() {

    //Kopioidaan hajautustaulusta arvot uuteen taulukkoon ja järjestetään uuden taulukon arvot quicksortilla laskevaan järjestykseen

    struct sanat taulu[count];

    int j = 0;
    for (int i = 0; i < TAULUNKOKO; i++) {
        if (hashTaulu[i] != NULL && hashTaulu[i]->arvo >1) {
            taulu[j].mki = hashTaulu[i]->avain;
            taulu[j].luku = hashTaulu[i]->arvo;
            j++;
        }
    }

    quicksort(taulu,0, j);

    for (int i = 0; i < 100; i++) {

        printf("%s %d \n", taulu[i].mki, taulu[i].luku);
    }
}

int main(void) {


    FILE *tiedosto;

    //Aloitetaan suoritukseen kuluvan ajan mittaaminen tässä
    start = clock();
    printf("Suoritetaan algoritmi WarPeace-tekstitiedostolle.\n");
    printf("-------------------------------------------------\n");

    tiedosto = fopen("WarPeace.txt","r"); //Luettava tiedosto
    char sana[500];
    char *uusisana;

    while((fscanf(tiedosto, " %500[a-zA-Z']%*[^a-zA-Z'] ", sana) == 1)) {  //Käydään tekstitiedosto läpi, ja karsitaan sanoista pois kaikki ylimääräiset merkit.

        uusisana = strdup(sana); //Kopioidaan sana uuteen muuttujaan null-terminoituna.
        for (int i = 0; uusisana[i]; i++) {
            uusisana[i] = tolower(uusisana[i]);  //Muutetaan kaikki kirjaimet pieniksi
        }
        lisaa(uusisana);
    }

    free(uusisana);

    fclose(tiedosto);
    tulostaSanatJarjestyksessa();

    //Suorituksen mittaaminen päättyy tähän
    end = clock();
    double totalTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nAikaa suoritukseen kului: %1f sekuntia\n",totalTime);

    return 0;
}
