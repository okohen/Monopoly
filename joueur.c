#include "joueur.h"
#include "terrain.h"
#include <string.h>

#define tai_ter 40

//===========================================================================================

int  go_prison(joueur *j, int i_jou) {
//ajoute 3 tours a j.prison
//initialise nb_double a 0
//retourne la indice_prison
    printf("\n Vous etes en Prison ! \n");
    j[i_jou].prison=3;
    j[i_jou].nb_double=0;
    return 10;
}

//===========================================================================================

int define_pos(joueur *j,int i_jou) {
//definir la nouvelle position du joueur
//Verifier si double
// si oui incremente la variable joueur.nb_double
//        si nb_double == 3 appel la fonction go_prison
//sinon initialise nb_double a 0 et retourne la nouvelle position
//et si on passe par le depart on ajoute 500 euro au montant_eco joueur
    int Old_indice=j[i_jou].indice_case;
    int a = lancer_dee(), b = lancer_dee();
    if (a==b) {
        printf("\n ***   DOUBLE  %d *** \n",j[i_jou].nb_double+1);
        j[i_jou].nb_double+=1;
        if(j[i_jou].nb_double==3) {
            return go_prison(j,i_jou);
        }
    } else {
        j[i_jou].nb_double=0;
    }
    int new_pos=(Old_indice+a+b);
    if (new_pos>=tai_ter)
        j[i_jou].montant_eco+=200;

    return new_pos%tai_ter;
}

//===========================================================================================

void aller_pos(joueur *j,int i_jou,terrain *ter,int old_pos, int new_pos) {
//aller_pos : pointe joueur_exist de l'ancienne position sur NULL et decremente le nbr_joueur
//met a jour la nouvelle pos
//pointe joueur_exist de la nouvelle position sur joueur et incremente le nbr_joueur

    ter[old_pos].joueur_exist[i_jou]=NULL;    //Edits on the Old_case
    ter[old_pos].nbr_joueur-=1;

    j[i_jou].indice_case=new_pos;   //Edits on the New_case
    ter[new_pos].joueur_exist[i_jou]=&j[i_jou];
    ter[new_pos].nbr_joueur+=1;
    //Show info
    printf("\nInfo Deplacement : \n");
    printf("%s : %d =====================> %d \n",j[i_jou].nom_joueur,old_pos,j[i_jou].indice_case);
    printf("\nInfo terrain : \n");
    printf("Pointeur Old case :  %s  || Nbr joueur restant sur ter : %d \n",ter[old_pos].joueur_exist[i_jou]->nom_joueur,ter[old_pos].nbr_joueur);
    printf("Pointeur New case :  %s  || Nbr joueur arrive sur ter : %d \n",ter[new_pos].joueur_exist[i_jou]->nom_joueur,ter[new_pos].nbr_joueur);
}

//===========================================================================================

void deplacer(joueur *j,int i_jou,terrain *ter,char t[][9]) {
//Verifie si le joueur est en prison
//si oui , proposer les choix disponible
//sinon se deplacer normalement
    int test_rep=2;
    if(j[i_jou].prison!=0) {
        printf(" 1.Voulez  vous payer 150 dollars ? ");
        printf(" 2.Ne rien faire. ");
        if(j[i_jou].carte_conserver!=NULL) {
            printf("\n3. utiliser votre carte Sortir prison ?");
            test_rep+=1;
        }
        int rep =rand()%test_rep;
        switch(rep) {
        case 0:
            if(j[i_jou].montant_eco-150<=0) {
                printf("\nChoix impossble, la banque ne fait pas de credit");
            } else {
                printf("\nVous avez payer 150 dollars! vous etes libre !! ");
                j[i_jou].montant_eco-=150;
                j[i_jou].prison=0;
                deplacer(j,i_jou,ter,t);
            }
            break;

        case 1:
            j[i_jou].prison-=1;
            printf("\n -------- NOMBRE DE TOURS A ATTENDRE : %d ----------------- \n",j[i_jou].prison);
            break;
        case 2 :
            printf("\nVous avez utiliser votre carte de sortir de prison\n");
            j[i_jou].prison=0;
            j[i_jou].carte_conserver=NULL;
            deplacer(j,i_jou,ter,t);
            break;
        default :
            printf("Error ! switch ");
            break;
        }
    } else {
        int new_pos=define_pos(j,i_jou);
        aller_pos(j,i_jou,ter,j[i_jou].indice_case,new_pos);
    }
}

//===========================================================================================

int lancer_dee() {
    return rand()%6+1;
}

//===========================================================================================

joueur * init_joueur(int nbr,char avatars[][9]) {
    //init avatars
    for(int i=0; i<tai_ter; i++) {
        for(int j=0; j<9; j++)
            avatars[i][j]=' ';
        avatars[i][8]='\0';
    }
    joueur *j=(joueur *)malloc(sizeof(joueur)*nbr);
    char c[2];
    for(int i=0; i<nbr; i++) {
        c[0]='A'+i;
        strcpy(j[i].nom_joueur,c);
        j[i].avatar='à'+i;
        j[i].indice_case=0;
        j[i].montant_eco=500;
        j[i].prison=0;//prison !=0 nbr de tour a attendre
        j[i].nb_double=0;
        j[i].couleur=2+i;
        j[i].nbr_ter=0;
        avatars[0][i]=  j[i].avatar;
        j[i].carte_conserver=NULL;
        for(int k=0; k<28; k++)
            j[i].terrain_achetes[k]=NULL;

    }
    return j;
}

//===========================================================================================

void supprimer_joueur(joueur *j,int *i_jou,terrain *ter,int *nbr,char t[][9]) {
//supprimer les maison du proprio et son avatar
//decrementer le nbr de joueur
//decrementer l'indice du joueur
    int indice_jou =*i_jou;
    for(int i=0; i<j[*i_jou].nbr_ter; i++)
        j[indice_jou].terrain_achetes[i]=NULL;
    //supprimer ses maison et son avatar
    for(int i=0; i<tai_ter; i++)
        for(int k =indice_jou; k<4; k++)
            t[i][k]=' ';

    if(indice_jou!=*nbr-1)
        for(int i=indice_jou; i<*nbr; i++)
            j[i]=j[i+1];

    *nbr=*nbr-1;
    if(indice_jou!=0)
        *i_jou=*i_jou-1;

    printf("\n\t***    PLAYER EXCLUDED   ****\t\n");
}

//===========================================================================================

void Payer_Tax(joueur *j,int *i_jou,terrain *ter,int i_ter,int *nbr,char t[][9]) {
//les actions que le joueur peut faire
//selon sa position et payer la tax
    int indice_jou =*i_jou;
    int pos=j[indice_jou].indice_case;
    if(pos == 7 || pos == 22 || pos == 36) {
        printf("\nTirer une carte chance\n");
        random_carte_chance(j,i_jou,ter,nbr,t);
    } else if(pos == 2 || pos == 17 || pos== 33) {
        printf("\nTirer une carte community\n");
        random_carte_communaute(j,i_jou,ter,nbr,t);
    } else if(pos == 30 ) {
        printf("\n You're going to Jail \n");
        aller_pos(j,indice_jou,ter,j[indice_jou].indice_case,go_prison(j,indice_jou));
    } else if(ter[i_ter].ptr_proprio==NULL && pos!=4 &&pos!=38 && pos!=10 && pos!=0 ) {
        acheter_terrain(j,indice_jou,ter,i_ter);
    } else if(ter[i_ter].ptr_proprio==&j[indice_jou] ) {
        printf("\n Info Achat Maison");
        printf("\n nbr de maison avant : %d\n",ter[i_ter].nbr_maison);
        acheter_maison(j,indice_jou,ter,i_ter,t);
        printf("\n nbr de maison Apres : %d\n",ter[i_ter].nbr_maison);
    } else if (pos!=10 && pos!=0) {
        payer_loyer(j,i_jou,ter,nbr,t);
    }
}

//===========================================================================================

void acheter_maison(joueur *j,int i_jou,terrain *ter,int i_ter,char t[][9] ) {
//voir si le joueur a acheté toute la famille
// si oui ,
//si sa premier maison  acheter une premier maison
//sinon voir s'il a une maison dans toutes les terrains de la famille
//  si oui acheter une N'eme maison
//si 4 maison , echanger les maison contre un hotel .

    int montant=(10*ter[i_ter].nbr_maison)/100;
    if(j[i_jou].montant_eco >montant && ter[i_ter].famille_domaine!=neutre) {
        int nbr_prop=0;
        int nbrtest =3;
        int nbr_maison=0;
        if(ter[i_ter].famille_domaine== marron || ter[i_ter].famille_domaine== bleu)
            nbrtest=2;
        for(int i=0; i<tai_ter; i++) { //a changer 40 par nbr_fjlmdqsjfm
            if(ter[i].ptr_proprio==&j[i_jou])
                if(ter[i].famille_domaine==ter[i_ter].famille_domaine) {
                    nbr_prop++;
                    if(ter[i].nbr_maison>0)//nbr maison de meme famille
                        nbr_maison++; //on doit avoir min 3
                }
        }
        if(nbr_prop==nbrtest) { //Si on peut acheter
            if( (ter[i_ter].nbr_maison==0) || (ter[i_ter].nbr_maison<=4 && nbr_maison>=nbrtest) ) { //si 4 maison demander si echange contre hotel
                ter[i_ter].nbr_maison+=1;
                j[i_jou].montant_eco-=montant;
                if(ter[i_ter].nbr_maison<5) {
                    t[i_ter][ter[i_ter].nbr_maison+3]='^';
                } else {
                    for(int i=4; i<9; i++)
                        t[i_ter][i]=' ';
                    t[i_ter][ter[i_ter].nbr_maison]='H';
                    t[i_ter][8]='\0';
                }
            } else {
                printf("Vous ne pouvez pas acheter plus d'un Hotel ");
            }
        } else {
            printf("Vous devez d'abord achter toute la famille   \n");
        }
    } else {
        printf("\nDesole monsieur,MAISON la banque ne fait pas de credit !\n");
    }
}

//===========================================================================================

void acheter_terrain(joueur *j,int i_jou,terrain *ter,int i_ter) {
    int montant=ter[i_ter].prix_domaine;
    if(j[i_jou].montant_eco>montant) {
        ter[i_ter].ptr_proprio=&j[i_jou];
        int k=j[i_jou].nbr_ter++;
        j[i_jou].terrain_achetes[k]=&ter[i_ter];
        j[i_jou].montant_eco-=ter[i_ter].prix_domaine;
        printf("\n Terrain achete ! \n");
    } else {
        printf("\nDesole monsieur,TERRAIN la banque ne fait pas de credit !\n");
    }
}

//===========================================================================================

void payer_loyer(joueur *j,int *i_jou,terrain *ter,int *nbr,char t[][9]) {
//Payer loyer au proprietaire selon le nombre de maison
// si montant loyer > montant_eco du joueur
// Supprimer le joueur
// sinon soustraire le montant loyer du montant_eco du joueur
    int indice_jou =*i_jou;
    printf("Vous devez payer la tax au proprietaire ");
    int i_ter = j[indice_jou].indice_case;
    int prix_domaine=ter[i_ter].prix_domaine;
    int nbr_maison=ter[i_ter].nbr_maison+1;
    int nbr_gare=0;
    int nbr_ter=j[indice_jou].nbr_ter;
    if(j[indice_jou].indice_case == 5 || j[indice_jou].indice_case == 15 || j[indice_jou].indice_case == 25 || j[indice_jou].indice_case == 35 )
        for(int i=0; i<nbr_ter; i++) {
            if(strcmp(j[indice_jou].terrain_achetes[i]->type_domaine,"Gare")==0)
                nbr_gare++;
            nbr_maison=0;
        }
    int prix_loyer = (prix_domaine*(nbr_maison+nbr_gare)*10)/100;
    if(j[indice_jou].montant_eco<=prix_loyer) {
        supprimer_joueur(j,i_jou,ter,nbr,t);
    } else {
        printf("\n Tax Payee ");
        if(ter[i_ter].ptr_proprio!=NULL) {
            ter[i_ter].ptr_proprio->montant_eco+=prix_loyer;
            printf(" a  : %s \n ",ter[i_ter].ptr_proprio->nom_joueur);
        }
        j[indice_jou].montant_eco-=prix_loyer;
    }
}

//===========================================================================================

void plateau_graphic(char t[][9],joueur *j,int i_jou,terrain *ter,int old_case) {
    int pos=j[i_jou].indice_case;
    t[old_case][i_jou]=' ';
    t[pos][i_jou]=j[i_jou].avatar;

    color(15,0);
    printf("\n ================================================================================================================\n |");
    //Ligne Haut
    //premiere ligne
    for(int i=0; i<=10; i++) {
        color(ter[i].famille_domaine,0);
        printf("|--------|");
        color(15,0);
    }
    printf("|\n |");
    //Deuxieme ligne (Afficher les nom_domaine)
    for(int i=0; i<=10; i++) {
        color(ter[i].famille_domaine,0);
        printf("| %.6s |",ter[i].nom_domaine);
        color(15,0);
    } //retour a la ligne
    printf("|\n |");
    //Troisieme ligne (Avatar de joueur)
    for(int i=0; i<=10; i++) {
        color(ter[i].famille_domaine,0);
        printf("|");
        color(15,0);
        printf("%s",t[i]);
        color(ter[i].famille_domaine,0);
        printf("|");
        color(15,0);
    }
    printf("|\n |");
    //Fin ligne Haut
    for(int i=0; i<=10; i++) {
        color(ter[i].famille_domaine,0);
        printf("|--------|");
        color(15,0);
    }
    printf("|");
    //BODY
    for(int j=1; j<=9; j++) {
        //Ligne gauche
        printf("\n");
        color(ter[tai_ter-j].famille_domaine,0);
        printf(" || %.6s ||",ter[tai_ter-j].nom_domaine);
        color(15,0);

        printf("\t\t\t\t\t\t\t\t\t\t             ");
        //Ligne droite
        color(ter[10+j].famille_domaine,0);
        printf("|| %.6s ||\n",ter[10+j].nom_domaine);
        color(15,0);

        color(ter[tai_ter-j].famille_domaine,0);
        printf(" ||");
        color(15,0);
        printf("%s",t[tai_ter-j]);
        color(ter[tai_ter-j].famille_domaine,0);
        printf("||");
        color(15,0);

        printf("\t\t\t\t\t\t\t\t\t\t            ");

        color(ter[10+j].famille_domaine,0);
        printf(" ||");
        color(15,0);
        printf("%s",t[10+j]);
        color(ter[10+j].famille_domaine,0);
        printf("||\n");
        color(15,0);

        color(ter[tai_ter-j].famille_domaine,0);
        printf(" ||        ||");
        color(15,0);

        printf("\t\t\t\t\t\t\t\t\t\t             ");

        color(ter[10+j].famille_domaine,0);
        printf("||        ||");
        color(15,0);
        printf("\n ||--------||\t\t\t\t\t\t\t\t\t\t             ||--------||  ");
    }
    //Fin Body

    //afficher premiere ligne
    printf("\n ||        |");
    for(int i=29; i>=21; i--) {
        color(ter[i].famille_domaine,0);
        printf("|--------|");
        color(15,0);
    }
    printf("|        ||\n |");

    //afficher deuxieme ligne

    for(int j=30; j>=20; j--) {
        color(ter[j].famille_domaine,0);
        printf("| %.6s |",ter[j].nom_domaine);
        color(15,0);
    } //retour a la ligne
    printf("|\n |");
    for(int j=30; j>=20; j--) {
        color(ter[j].famille_domaine,0);
        printf("|");
        color(15,0);
        printf("%s",t[j]);
        color(ter[j].famille_domaine,0);
        printf("|");
        color(15,0);
    }
    printf("|\n |");
    for(int i=30; i>=20; i--) {
        color(ter[i].famille_domaine,0);
        printf("|--------|");
        color(15,0);
    }
    printf("|");
    printf("\n ================================================================================================================\n");
}


//===========================================================================================

void print_stat(joueur *j,int i_jou) {
    printf(" ****     Stats     ***** \n");
    printf("Nom : %s \n",j[i_jou].nom_joueur);
    printf("Solde : %d \n",j[i_jou].montant_eco);
    if(j[i_jou].carte_conserver!=NULL)
        printf("Carte conserver  : %s", j[i_jou].carte_conserver->title);

    printf("Les proprietees : \n");
    for(int i =0; i<j[i_jou].nbr_ter; i++)
        printf(" ter %s \n",j[i_jou].terrain_achetes[i]->nom_domaine);

}

//=============== Marc

//===========================================================================================

void init_cartes_chance(cartes_chance *chance,char title[50],char type[20],int pos,int tax) {
    strcpy(chance->title, title);
    strcpy(chance->type, type);
    chance->new_position=pos;
    chance->tax=tax;
}

//===========================================================================================

void init_cartes_communaute(cartes_commu *communaute,char title[50],char type[20],int pos,int tax) {
    strcpy(communaute->title, title);
    strcpy(communaute->type, type);
    communaute->new_position=pos;
    communaute->tax=tax;
}

//===========================================================================================

cartes_chance *initDeckChance() {
    cartes_chance *deck=(cartes_chance *) malloc(11*sizeof(cartes_chance));
    init_cartes_chance(&deck[0],"Aller au depart","Deplacement",0,0);
    init_cartes_chance(&deck[1],"Aller a la rue de la paix","Deplacement",39,0);
    init_cartes_chance(&deck[2],"Aller a la prison","Deplacement",10,0);
    init_cartes_chance(&deck[3],"Aller a l'Avenue Henri-Martin","Deplacement",24,0);
    init_cartes_chance(&deck[4],"Aller a la Gare de Lyon","Deplacement",15,0);
    init_cartes_chance(&deck[5],"Decaler 3 cases","Deplacementx",-3,0);
    init_cartes_chance(&deck[6],"Payer tax 100$","Tax",0,100);
    init_cartes_chance(&deck[7],"Payer les frais de scolarite 150$","Tax",0,150);
    init_cartes_chance(&deck[8],"La banque vous verse un dividende 40$","Bonus",0,40);
    init_cartes_chance(&deck[9],"Vous avez gagne le concours 200$","Bonus",0,200);
    init_cartes_chance(&deck[10],"Carte liberation de prison " ,"Conserver",0,0);
    return deck;
}

//===========================================================================================

cartes_commu *initDeckCommunaute() {
    cartes_commu *deck=(cartes_commu *) malloc(10*sizeof(cartes_commu));
    init_cartes_communaute(&deck[0],"Aller au depart","Deplacement",0,0);
    init_cartes_communaute(&deck[1],"Aller au Boulevard de Belleville","Deplacement",1,0);
    init_cartes_communaute(&deck[2],"Aller a la prison","Deplacement",10,0);
    init_cartes_communaute(&deck[3],"Payer les frais d'hospitalisation 100$","Tax",0,100);
    init_cartes_communaute(&deck[4],"Payer les honoraires du medecin 50$","Tax",0,50);
    init_cartes_communaute(&deck[5],"Prime d'assurance 50$","Tax",0,50);
    init_cartes_communaute(&deck[6],"Erreur de banque. Collecter 200$","Bonus",0,200);
    init_cartes_communaute(&deck[7],"Vous heritez de 100$","Bonus",0,100);
    init_cartes_communaute(&deck[8],"C'est votre anniversaire. Collecter 40$.","Bonus",0,40);
    init_cartes_communaute(&deck[9],"Vous gagnez la loterie. Collecter 100$","Bonus",0,100);
    return deck;
}

//===========================================================================================

void AfficheCarteChance(cartes_chance chance) {
    printf("%s\n",chance.title);
}

//===========================================================================================

void AfficheCarteCommunaute(cartes_commu communaute) {
    printf("%s\n",communaute.title);
}

//===========================================================================================

void random_carte_chance(joueur *j,int *i_jou, terrain *ter,int *nbr,char t[][9]) {

    int indice_jou =*i_jou;
    cartes_chance *chance=initDeckChance();
    int c;
    c = rand()% 11;
    AfficheCarteChance(chance[c]);

    if(strcmp(chance[c].type,"Deplacement")==0) {
        if(c==2) { // aller en  prison
            aller_pos(j,indice_jou,ter,j[indice_jou].indice_case,go_prison(j,indice_jou));
        } else {
            aller_pos(j,indice_jou,ter,j[indice_jou].indice_case,chance[c].new_position);
        }
    } else if(strcmp(chance[c].type,"Tax")==0) {
        int montant =j[indice_jou].montant_eco-chance[c].tax;
        if(montant<=0)
            supprimer_joueur(j,i_jou,ter,nbr,t);
        else
            j[indice_jou].montant_eco-=chance[c].tax;
    } else if(strcmp(chance[c].type,"Deplacementx")==0) {
        aller_pos(j,indice_jou,ter,j[indice_jou].indice_case,j[indice_jou].indice_case+chance[c].new_position);

    } else if(strcmp(chance[c].type,"Bonus")==0) {
        j[indice_jou].montant_eco+=chance[c].tax;
    } else if(strcmp(chance[c].type,"Conserver")==0) {
        j[indice_jou].carte_conserver=&chance[c];
    }

}

//===========================================================================================

void random_carte_communaute(joueur *j,int *i_jou, terrain *ter,int *nbr,char t[][9]) {
    int indice_jou =*i_jou;
    cartes_commu *communaute=initDeckCommunaute();
    int c;
    c = rand()% 10;
    AfficheCarteCommunaute(communaute[c]);

    if(strcmp(communaute[c].type,"Deplacement")==0) {
        if(c==2) { // aller en prison
            aller_pos(j,indice_jou,ter,j[indice_jou].indice_case,go_prison(j,indice_jou));
        } else {
            aller_pos(j,indice_jou,ter,j[indice_jou].indice_case,communaute[c].new_position);
        }
    } else if(strcmp(communaute[c].type,"Tax")==0) {
        int montant =j[indice_jou].montant_eco-communaute[c].tax;
        if(montant<=0)
            supprimer_joueur(j,i_jou,ter,nbr,t);
        else
            j[indice_jou].montant_eco-=communaute[c].tax;

    } else if(strcmp(communaute[c].type,"Bonus")==0) {

        j[indice_jou].montant_eco+=communaute[c].tax;
    }
}





