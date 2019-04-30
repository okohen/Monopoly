#include <stdio.h>
#include <stdlib.h>

typedef struct cartes carte;
typedef struct str_terrain terrain;
typedef struct cartes cartes_chance;
typedef struct cartes cartes_commu;

typedef struct str_joueur{
    char nom_joueur[25];
    char avatar;
    int indice_case;
    int montant_eco;
    carte *carte_conserver;
    terrain *terrain_achetes[28];
    int nbr_ter;
    int prison;
    int nb_double;
    int couleur;
} joueur;

struct cartes{
    char title[50];
    char type[20];
    int new_position;
    int tax;
};

joueur * init_joueur(int nbr,char avatars[][9]);
int lancer_dee();
int define_pos(joueur *j,int i_jou);
int go_prison(joueur *j,int i_jou);
void aller_pos(joueur *j,int i_jou,terrain *ter,int old_pos, int new_pos);
void deplacer(joueur *j,int i_jou,terrain *ter,char t[][9]);
void supprimer_joueur(joueur *j,int *i_jou,terrain *ter,int *nbr,char t[][9]);

void Payer_Tax(joueur *j,int *i_jou,terrain *ter,int i_ter,int *nbr,char t[][9]);

void payer_loyer(joueur *j,int *i_jou,terrain *ter,int *nbr,char t[][9]);
void acheter_maison(joueur *j,int i_jou,terrain *ter,int i_ter,char t[][9] );

void acheter_terrain(joueur *j,int i_jou,terrain *ter,int i_ter);
void plateau_graphic(char t[][9],joueur *j,int i_jou,terrain *ter,int old_case);
void print_stat(joueur *j,int i_jou);

cartes_chance *initDeckChance();
cartes_commu *initDeckCommunaute();
void init_cartes_chance(cartes_chance *chance,char title[50],char type[20],int pos,int tax);
void init_cartes_communaute(cartes_commu *communaute,char title[50],char type[20],int pos,int tax);
void AfficheCarteChance(cartes_chance chance);
void AfficheCarteCommunaute(cartes_commu communaute);
void random_carte_chance(joueur *j,int *i_jou, terrain *ter,int *nbr,char t[][9]);
void random_carte_communaute(joueur *j,int *i_jou, terrain *ter,int *nbr,char t[][9]);









