#include <string.h>
#include <windows.h>

#include "terrain.h"

#define Nbr_case 40

//=======================================================================================================

void color(int t,int f){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}

//=======================================================================================================

void init_Terrain(terrain *ter,char Nom[], char type[], int prix,T_famille famille_domaine)
{
    strcpy(ter->nom_domaine, Nom);
    ter->prix_domaine = prix;
    strcpy(ter->type_domaine,type);
    ter->famille_domaine=famille_domaine;
    ter->ptr_proprio = NULL;
    ter->nbr_joueur= 0;
    ter->nbr_maison = 0;
    ter->joueur_exist[0]=NULL;
    ter->joueur_exist[1]=NULL;
    ter->joueur_exist[2]=NULL;
    ter->joueur_exist[3]=NULL;

}

//=======================================================================================================

terrain *initPlateau(joueur *j,int nbr)
{
    terrain *Plateau=(terrain *) malloc(40*sizeof(terrain));
    init_Terrain(&Plateau[0],"Depart","Depart",0,neutre);
    init_Terrain(&Plateau[1],"Boulevard de Belleville","Terrain",60,marron);
    init_Terrain(&Plateau[2],"Caisse de Communaute","Caisse de Communaute",300,neutre);
    init_Terrain(&Plateau[3],"Rue Lecourbe","Terrain",60,marron);
    init_Terrain(&Plateau[4],"Impots sur le Revenu","Impots",300,neutre);
    init_Terrain(&Plateau[5],"Gare Montparnasse","Gare",200,neutre);
    init_Terrain(&Plateau[6],"Rue de Vaugirard","Terrain",100,bleuciel);
    init_Terrain(&Plateau[7],"Chance","Chance",0,neutre);
    init_Terrain(&Plateau[8],"Rue de Courcelles","Terrain",100,bleuciel);
    init_Terrain(&Plateau[9],"Avenue de la Repulblique","Terrain",120,bleuciel);
    init_Terrain(&Plateau[10],"Prison Simple Visite","Prison",0,neutre);
    init_Terrain(&Plateau[11],"Boulevard de la Villette","Terrain",140,rose);
    init_Terrain(&Plateau[12],"Compagnie de Distribution Electricite","Compagnie",150,neutre);
    init_Terrain(&Plateau[13],"Avenue de Neuilly","Terrain",140,rose);
    init_Terrain(&Plateau[14],"Rue de Paradis","Terrain",160,rose);
    init_Terrain(&Plateau[15],"Gare de Lyon","Gare",200,neutre);
    init_Terrain(&Plateau[16],"Avenue Mozart","Terrain",180,orange);
    init_Terrain(&Plateau[17],"Caisse de Communaute","Caisse de Communaute",300,neutre);
    init_Terrain(&Plateau[18],"Boulevard Saint-Michel","Terrain",180,orange);
    init_Terrain(&Plateau[19],"Place Pigalle","Terrain",200,orange);
    init_Terrain(&Plateau[20],"Place gratuit","Parking",0,neutre);
    init_Terrain(&Plateau[21],"Avenue Matignon","Terrain",220,rouge);
    init_Terrain(&Plateau[22],"Chance","Chance",0,neutre);
    init_Terrain(&Plateau[23],"Boulevard Malesherbes","Terrain",220,rouge);
    init_Terrain(&Plateau[24],"Avenue Henri-Martin","Terrain",240,rouge);
    init_Terrain(&Plateau[25],"Gare du Nord","Gare",200,neutre);
    init_Terrain(&Plateau[26],"Fauboug Saint-Honore","Terrain",260,jaune);
    init_Terrain(&Plateau[27],"Place de la Bourse","Terrain",260,jaune);
    init_Terrain(&Plateau[28],"Water Works","Terrain",100,neutre);
    init_Terrain(&Plateau[29],"Place La Fayette","Terrain",100,jaune);
    init_Terrain(&Plateau[30],"Allez en Prison","Prison",0,neutre);
    init_Terrain(&Plateau[31],"Avenue de Breteuil'","Terrain",300,vert);
    init_Terrain(&Plateau[32],"Avenue Foch","Terrain",300,vert);
    init_Terrain(&Plateau[33],"Caisse de Communaute","Caisse de Communaute",300,neutre);
    init_Terrain(&Plateau[34],"Boulevard des Capuches","Terrain",320,vert);
    init_Terrain(&Plateau[35],"Gare Saint-Lazare","Gare",200,neutre);
    init_Terrain(&Plateau[36],"Chance","Chance",0,neutre);
    init_Terrain(&Plateau[37],"Avenue des Champs-Elysées","Terrain",350,bleu);
    init_Terrain(&Plateau[38],"Taxe de Luxe","Impots",300,neutre);
    init_Terrain(&Plateau[39],"Rue de la Paix","Terrain",400,bleu);
    return Plateau;
}

//=======================================================================================================

void affichePlateau(terrain *plateau)
{
    int i;
    for(i=0; i<Nbr_case; i++)
    {
        color(plateau[i].famille_domaine,0);
        printf("%s ||  %s ||  %d  ||  ",plateau[i].nom_domaine, plateau[i].type_domaine, plateau[i].prix_domaine);
        color(15,0);
        printf("\n================================================================================\n");
    }
}

//================================================================================

void afficheTerrain(terrain t)
{
    color(t.famille_domaine,0);
    printf("%s ||  %s ||  %d  ||  ",t.nom_domaine, t.type_domaine, t.prix_domaine);

    color(15,0);
    printf("\n================================================================================\n");
}

//================================================================================





