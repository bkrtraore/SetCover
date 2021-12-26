#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FICHIER "cover.txt"

/* Le fichier cover.txt
    6 => nb éléments S(A,B,C,D,E,F)
    7 => nb éléments U(1-7)
    A 1001001 => {1,4,7}
    B 1001000 => {1,4}
    C 0001101 => {4,5,7}
    D 0010110 => {3,5,6}
    E 0110011 => {2,3,6,7}
    F 0100001 => {2,7}
*/

// tab[ligne][colonne]

int getNbS()
{
    FILE *fichier = NULL;
    fichier = fopen(FICHIER, "r");
    if (fichier == NULL)
    {
        printf("Le fichier choisi n'a pas pu être lu");
        return 0;
    }
    int nbS;
    fscanf(fichier, "%d", &nbS);
    fclose(fichier);
    return nbS;
}

int getNbU()
{
    FILE *fichier = NULL;
    fichier = fopen(FICHIER, "r");
    if (fichier == NULL)
    {
        printf("Le fichier choisi n'a pas pu être lu");
        return 0;
    }
    int nbU, nbS;

    fscanf(fichier, "%d", &nbS);
    fscanf(fichier, "%d", &nbU);
    fclose(fichier);
    return nbU;
}

int **getValues()
{
    FILE *fichier = NULL;
    fichier = fopen(FICHIER, "r");
    if (fichier == NULL)
    {
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

    ensembles = (int **)malloc(sizeof(int *) * nbS);
    for (int i = 0; i < nbU; ++i)
    {
        ensembles[i] = (int *)malloc(sizeof(int) * nbU);
    }

    for (int i = 0; i < nbS; ++i)
    {
        for (int j = 0; j < nbU; ++j)
        {
            c = fgetc(fichier);
            if (c == '0')
                ensembles[i][j] = 0;
            else if (c == '1')
                ensembles[i][j] = 1;
        }
        // Permet le saut de ligne entre chaque lecture d'ensemble
        char buffer[100];
        fgets(buffer, 100, fichier);
    }
    fclose(fichier);
    return ensembles;
}

// Vérifie si un tableau est complètement couvert
int covered(int *couverture, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        if (couverture[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Fonction permettant de  trouver une solution dans le cadre du problème du set cover
// Renvoie l'ensemble de solution de type {1, 0, 1} => SOUS ENSEMBLES 1 et 3

int *setCoverGlouton(int **ensembles, int nbU, int nbS)
{
    // Tableaux de couverture (valeurs) et de solution (Sous-ensembles)

    int *couverture;
    int *solution;
    int *sousEnsemble;
    int *used;
    int idcSE; //Indice sous ensemble

    //Tableau indiquant si l'état de couverture
    couverture = (int *)malloc(sizeof(int) * nbU);
    solution = (int *)malloc(sizeof(int) * nbU);
    sousEnsemble = (int *)malloc(sizeof(int) * nbU);
    //Tableau indiquant si le tableau ou SE a été utilisé
    used = (int *)malloc(sizeof(int) * nbU);

    for (int i = 0; i < nbU; ++i)
    {
        couverture[i] = 0;
        solution[i] = 0;
        used[i] = 0;
    }

    while (!covered(couverture, nbU)) {
        //Flag indiquant la pertinence du SE à ajouter à la couverture
        int flag = 0;
        /**
        * Prendre un SE au hasard
        * Vérifier si il a pas déjà été lue
        * Vérifier sa pertinence si OK =>
        * Ajouter à la liste des SE au tableau solution
        * Ajouter les valeurs du SE au tableau couverture
        **/

        // => Verifie si le SE donnée au hasard permet ce couvrir plus d'éléments qu'initialement

        idcSE = rand() % nbU;
        if (!used[idcSE]) {

            // Affectation du sous-ensemble
            memcpy(sousEnsemble, ensembles[idcSE], sizeof(int)*nbU);

            //Verification utilité du sous ensemble
            for (int i = 0; i < nbU; ++i) {
                if ((couverture[i] == 0) && (sousEnsemble[i] == 1)) {
                    flag = 1;
                    break;
                }
                flag = 0;
            }
        }

        if (flag) {
            solution[idcSE] = 1;
            for (int i = 0; i < nbU; ++i) {
                if (sousEnsemble[i] == 1) {
                    couverture[i] = 1;
                }
            }
        }
    }
    return solution;
}

int main()
{
    srand(time(NULL));


    int nbS = getNbS();
    int nbU = getNbU();
    int **ensembles = getValues();

    printf("Nombre d'ensembles : %d\nNombre d'éléments à couvrir: %d\n", nbS, nbU);
    printf("Les ensembles sont les suivants :\n");
    for (int i = 0; i < nbS; ++i)
    {
        for (int j = 0; j < nbU; ++j)
        {
            printf("%d", ensembles[i][j]);
        }
        printf("\n");
    }

    printf("Une solution du set cover glouton est : ");
    int *solution;
    solution = setCoverGlouton(ensembles, nbU, nbS);
    for (int i = 0; i < nbS; i++)
    {
        printf("%d", solution[i]);
    }

    return 0;
}
