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




// Fonction de trouver une solution optimale dans le cadre du problème du set cover
// Renvoie l'ensemble de solution de type {1, 0, 1} => SOUS ENSEMBLES 1 et 3

void setCover(int** ensembles, int nbU, int nbS){

    //Création d'une matrice de 0 stockant les lignes déjà utilisés
    int* solution;
    int ** used;
    solution = (int *) malloc(sizeof(int)*nbU);

    used = (int **) malloc(sizeof(int *) * nbS);

    for (int i = 0; i < nbU; ++i) {
        used[i] = (int *) malloc(sizeof(int) * nbU);
        for (int j = 0; j < nbS; ++j) {
            used[i][j] = 0;
        }
    }




}

//Fonction permettant d'ajouter une ligne visité à la matrice
int addToUsed(int** visite, int **ligne, int numLigne, int nbU){
    /*int zero = 0;
    int line, column;

    Obtention de la ligne a ajouter
    for(int i = 0; i < nbS; ++i) {
        for (int j = 0; j < nbU; ++j) {
            if (visite[i][j] != 0) {
                zero = 1;
                line = i;
                column = j;
            }
        }

        }*/

    // Ajout à la matrice la ligne visité.
            for (int j = 0; j < nbU; ++j)
                    visite[numLigne][j] = ligne[0][j];
            return numLigne;
}


//Fonction permettant de vérifier si une ligne a déjà été visité
int alreadyVisited(int** visite, int **ligne, int nbU, int nbS){
    int same = 0;
    for(int i = 0; i < nbS; ++i) {
        for (int j = 0; j < nbU; ++j) {
            if (visite[i][j] == ligne[0][j])
                same = 1;
            else
                same = 0;
        }
        if(same == 1) return 1;
    }
    return same;
}

/*int goodToAdd(int** visite, int **ligne, int nbU, int nbS){
    if (!alreadyVisited(visite, ligne, nbU, nbS))
        addToUsed()
}

int resolvedOrNot(){

}*/

/*int verifPresent(int *ligne, int idcSolution){
    for (int i = 0; i < ; ++i) {
        if(ligne[i] == )
    }
    return 0;
}*/

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




