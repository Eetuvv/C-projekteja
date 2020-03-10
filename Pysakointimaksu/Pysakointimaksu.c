#include <stdio.h>
#include <string.h>

#define korkeus 3
#define leveys 3

double laskeParkkimaksu(double aika);

/*Luodaan kaksiulotteinen taulukko johon luvut tallennetaan*/
/*Tassa tapauksessa tallennetaan kolmen asiakkaan tiedot*/
double taulukko[korkeus][leveys];

int main(void) {

    int asiakas = 1;
    double tunnit;
    int i = 1;
    int y = 0;

    /*Silmukassa tallennetaan taulukkoon asiakasnumero, pysaköintiaika ja laskettu veloitus*/
    while (i <= 3) {

        int x = 0;

        taulukko[y][x] = asiakas;
        x++;

        printf("Syota  %d. asiakkaan pysakointiaika tunteina: \n",asiakas);
        scanf("%lf",&tunnit);

        taulukko[y][x] = tunnit;

        x++;
        taulukko[y][x] = laskeParkkimaksu(tunnit);

        y++;
        asiakas++;
        i++;
    }

    double tunnitSumma,laskutusSumma;

    printf("Asiakas     Tunnit     Veloitus\n");

    /* Kaydaan kaksiulotteinen taulukko lapi kahden silmukan avulla ja tulostetaan luvut*/
    for (int i = 0; i < korkeus; i++) {
        for (int x = 0; x < leveys; x++) {
            if (x==0) {
                printf("%d",(int)taulukko[i][x]);
                printf("           ");
            } else if (x!=0) {
                printf("%0.1f",taulukko[i][x]);
                printf("        ");

                if(x==1) {
                    tunnitSumma+= taulukko[i][x];
                }
                if (x==2) {
                    laskutusSumma+= taulukko[i][x];
                }
            }
        }
        printf("\n");
    }

    printf("YHTEENSA:   %0.1f        %0.1f",tunnitSumma,laskutusSumma);
}

/*Lasketaan parkkimaksu aika-muuttujanavulla*/
double laskeParkkimaksu(double aika) {

    if (aika <=3) {
        return 2;
    } else if (aika >3 && aika <24) {
        return (aika * 0.5) + 0.5;
    } else if (aika >=24) {
        return 10;
    }
}

