#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef enum {Black, bleu,vert,cyan,rouge,rose,marron,white,gray,brightblue,brightgreen ,bleuciel,orange,brightmagenta,jaune,neutre }   T_famille ;


typedef struct str_joueur joueur;

typedef struct str_terrain{
    char nom_domaine[25];
    char type_domaine[25];
    T_famille famille_domaine;//Couleur;
    int prix_domaine;
    int nbr_joueur;
    joueur *ptr_proprio;
    joueur *joueur_exist[4];
    int nbr_maison;
} terrain;

void init_Terrain(terrain *ter,char Nom[], char type[], int prix,T_famille famille_domaine);
terrain *initPlateau();
void affichePlateau(terrain *plateau);
void afficheTerrain(terrain t);
void color(int t,int f);
