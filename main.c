#include "terrain.h"
#include "joueur.h"
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

//Credits : Omar KOHEN :    https://www.instagram.com/kohenomar/
//                          https://www.facebook.com/undeux345


int main() {
//les noms des joueurs A B C D
//les avatars joueurs  α ß Γ π
//les maisons ^  || les hotels H


    system("mode con lines=80 cols=120");
    int nbr=4;
    char avatars[40][9];
    int i_jou=0;
    int old_case,old_i;
    srand(time(NULL));
    joueur *j=init_joueur(nbr,avatars);
    terrain *ter=initPlateau();
    ter[0].nbr_joueur=nbr;
    for(int i =0; i<nbr; i++)
        ter[0].joueur_exist[i]=&j[i];
    plateau_graphic(avatars,j,0,ter,-1);
    printf("\n PRESS ANY KEY TO START ...\n");
    getch();
    while (nbr>1) {
        color(j[i_jou].couleur,0);
        old_case=j[i_jou].indice_case;
        old_i=i_jou;
        system("cls");
        deplacer(j,i_jou,ter,avatars);
        Payer_Tax(j,&i_jou,ter,j[i_jou].indice_case,&nbr,avatars);
        if(i_jou>=0) {
            plateau_graphic(avatars,j,old_i,ter,old_case);
            color(15,0);
            afficheTerrain(ter[j[i_jou].indice_case]);
            if(nbr==1)
                printf("\n ****   Congratulation  **** \n");
            print_stat(j,i_jou);

        }
      //  Sleep(1000);

getch();
        if(j[i_jou].nb_double==0)
            i_jou++;
        i_jou=i_jou%nbr;
    }

    free(j);
    free(ter);
    scanf("%d",&nbr);
    return 0;
}
