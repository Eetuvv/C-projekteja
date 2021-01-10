#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* nimi;
    char* osoite;
    char* puhNro;
    struct Node* next;
};

void menu(){
    printf("Mita tehdaan seuraavaksi?\n\n");
    printf("1 = Henkilotiedon lisays\n");
    printf("2 = Henkilotietojen tulostus\n");
    printf("3 = Kaikkien henkilotietojen poisto\n");
    printf("0 = Lopetus\n");
}

struct Node* luoUusiNode(char* nimi, char* osoite, char* puhNro) {
    struct Node* uusiNode = NULL;
    uusiNode = (struct Node*)malloc(sizeof(struct Node));

    uusiNode->nimi = nimi;
    uusiNode->osoite = osoite;
    uusiNode->puhNro = puhNro;
    uusiNode->next = NULL;

    return uusiNode;
}

char *kysyNimi() {
    char* nimi = malloc(25);
    printf("Anna henkilon nimi: >");
    while (fgetc(stdin) != '\n');
    fgets(nimi, 25, stdin);

    int len = strlen(nimi);
    if(nimi[len-1] == '\n') { //Poista rivinvaihto
        nimi[len-1] = '\0';
    }
    return nimi;
}

char *kysyOsoite() {
    char *osoite = malloc(30);
    printf("Anna henkilon osoite: >");
    fgets(osoite, 30, stdin);

    int len = strlen(osoite);
    if(osoite[len-1] == '\n') { //Poista rivinvaihto
        osoite[len-1] = '\0';
    }
    return osoite;
}

char *kysyPuhNro() {
    char *puhNro = malloc(25);
    printf("Anna henkilon puhelinnumero: >");

    fgets(puhNro, 25, stdin);

    int len = strlen(puhNro);
    if(puhNro[len-1] == '\n') { //Poista rivinvaihto
        puhNro[len-1] = '\0';
    }
    return puhNro;
}

void tulostaLista(struct Node* n){
    if (n == NULL) {
        printf("Lista on tyhja!\n");
        return;
    }
    printf("Listassa on seuraavat alkiot: \n");

    while (1) {
        printf("[%s : %s : %s]",n->nimi, n->osoite, n->puhNro);
        printf(" -> ");
        n = n->next;
        if (n == NULL) {
            printf("NULL\n\n");
            break;
        }
    }
}

int main(void) {
    struct Node* head = NULL;
    struct Node* temp;

    int valinta;
    char* nimi;
    char* osoite;
    char* puhNro;

    while(valinta != 0) {
        menu();
        scanf("%d",&valinta);
        printf("Valintasi:");

        switch (valinta) {
        case 1:
            nimi = kysyNimi();
            osoite = kysyOsoite();
            puhNro = kysyPuhNro();

            temp = luoUusiNode(nimi,osoite,puhNro);

            temp->next = head;
            head = temp;
            break;
        case 2:
            tulostaLista(head);
            break;
        case 3:
            head = NULL;
            break;
        case 0:
            break;
        default:
            break;
        }
    }
    return 0;
}
