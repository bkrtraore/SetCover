#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/unistd.h>
#define FICHIER "cover.txt"

/* Le fichier cover.txt
    6 => nb éléments S
    7 => nb éléments U
    1001001
    1001000
    0001101
    0010110
    0110011
    0100001
*/

// Retourne un nombre au hasard entre 0 et la valeur max du domaine U
int nbHasard(int nbU){
    srand(time(NULL));
    return rand()%nbU;
}

int getNbS(){
    FILE *fichier = NULL;
    fichier = fopen(FICHIER, "r");
    if (fichier == NULL){
        printf("Le fichier choisi n'a pas pu être lu");
        return 0;
    }
    int nbS;
    fscanf(fichier, "%d", &nbS);
    fclose(fichier);
    return nbS;
}

int getNbU() {
    FILE *fichier = NULL;
    fichier = fopen(FICHIER,"r");
    if (fichier == NULL) {
        printf("Le fichier choisi n'a pas pu être lu");
        return 0;
    }
    int nbU, nbS;

    fscanf(fichier, "%d", &nbS);
    fscanf(fichier, "%d", &nbU);
    fclose(fichier);
    return nbU;
}



int** getValues() {
    FILE *fichier = NULL;
    fichier = fopen(FICHIER, "r");
    if (fichier == NULL){
        printf("Le fichier choisi n'a pas pu être lu");
        return NULL;
    }

    int nbU, nbS;
    int **ensembles;
    char c;

    fscanf(fichier, "%d", &nbS);
    fscanf(fichier, "%d", &nbU);
    fgetc(fichier);
    fgetc(fichier);

    ensembles = (int **) malloc(sizeof(int *) * nbS);
    for (int i = 0; i < nbU; ++i) {
        ensembles[i] = (int *) malloc(sizeof(int) * nbU);
    }

    for (int i = 0; i < nbS; ++i) {
        for (int j = 0; j < nbU; ++j) {
            c = fgetc(fichier);
            if (c == '0')
                ensembles[i][j] = 0;
            else if (c =='1')
                ensembles[i][j] = 1;
        }
        // Permet le saut de ligne entre chaque lecture d'ensemble
        char buffer[100];
        fgets(buffer, 100, fichier);

    }
    fclose(fichier);
    return ensembles;
}




// Fonction récursive permettant de trouver une solution optimale dans le cadre du problème du set cover

void setCover(int** ensembles, int nbU, int nbS){
    /*
     * Soit je garde la matrice des ensembles et me débrouille avec
     * en créant un tableau de taille nbS permettant de garder en mémoire les solutions visités
     */

    //Soit je recrée des tableaux unidimensionnels pour chacune des solution allant de 0 à nbS

}

int main() {

    int nbS = getNbS();
    int nbU = getNbU();
    int** ensembles = getValues();

    printf("Nombre d'ensembles : %d\nNombre d'éléments à couvrir : %d\n", nbS, nbU);
    printf("Les ensembles sont les suivants :\n");
    for (int i = 0; i < nbS; ++i) {
        for (int j = 0; j < nbU; ++j) {
            printf("%d", ensembles[i][j]);
        }
        printf("\n");
    }
    return 0;
}




