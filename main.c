#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// generale
void clearChaine(char *src);
//------------DATA EMpreteurs--------------------
struct Emprunteur{

    char nom[20];
    char prenom[20];
};
void AjoutEmprunteur(struct Emprunteur *lien,int *pos);
void AfficheEmpreteur(struct Emprunteur *lien,int fond);
int RechercheEmprunteur(struct Emprunteur *lien,int pos);
void supprimerEmprunteur(struct Emprunteur *lien,int pos);
int backUpEmprunteur(struct Emprunteur *lien,int pos);
int restoreEmprunteur(struct Emprunteur *lien,int *pos);

//------------DATA Emprunt--------------------
struct Emprunt{

    int IDLivre;
    int IDEmp;
};

//-------------DATA sur les livres
struct Livre{

    char titre[20];
    char auteur[20];
};
void AjoutLivre(struct Livre *lien,int *pos);
void AfficheLivres(struct Livre *lien,int fond);
int RechercheLivre(struct Livre *lien,int pos);
void supprimerLivre(struct Livre *lien,int pos);
int backUpLivre(struct Livre *lien,int pos);
int restoreLivres(struct Livre *lien,int *pos);
//----------------------------------------------------
int main()
{
    struct Emprunt stockEmp[100];
    struct Emprunt *ptrEmp;
    ptrEmp = stockEmp;
    int posEmp = 0;
    //--------------
    struct Emprunteur stockEm[100];
    struct Emprunteur *ptrEm;
    int posEm = 0;
    ptrEm = stockEm;
    //creation des varables livre
    struct Livre stock[100];
    struct Livre *ptr;
    ptr = stock;
    int last = 0;
    // initialisation
    puts("  INITIALISATION DE LA BIBLIOTHEQUE");
    int r = restoreLivres(ptr,&last);
    if(r==0)puts("   #[erreure] Impossible de recupere les donnees de livre");
    else puts("   #[succes] Initialisation Livre");
    r = restoreEmprunteur(ptrEm,&posEm);
    if(r==0)puts("   #[erreure] Impossible de recupere les donnees des EMprunteurs");
    else puts("   #[succes] Initialisation Emprunteurs");
    r = restoreEmprunts(ptrEmp,&posEmp);
    if(r==0)puts("   #[erreure] Impossible de recupere les donnees des EMprunteurs");
    else puts("   #[succes] Initialisation Emprunts");
    puts("  INITIALISATION DE LA BIBLIOTHEQUE FAITE");
    puts("  taper help pour afficher de l'aide");
    //Fonction principale
    int sortie = 0;
    char cmd[5];
    while(sortie ==0){

        printf("bib@ $ ");
        fgets(cmd,5,stdin);
        fflush(stdin);
        if(strcmp(cmd,"lvnv")==0) AjoutLivre(&stock,&last);
        else if(strcmp(cmd,"lvls")==0) AfficheLivres(&stock,last);
        else if(strcmp(cmd,"lvsr")==0) RechercheLivre(&stock,last);
        else if(strcmp(cmd,"lvdl")==0) supprimerLivre(&stock,last);
        else if(strcmp(cmd,"amnv")==0) AjoutEmprunteur(&stockEm,&posEm);
        else if(strcmp(cmd,"amls")==0) AfficheEmpreteur(&stockEm,posEm);
        else if(strcmp(cmd,"amsr")==0) RechercheEmprunteur(&stockEm,posEm);
        else if(strcmp(cmd,"amdl")==0) supprimerEmprunteur(&stockEm,posEm);
        else if(strcmp(cmd,"emnv")==0) AjoutEmprunt(&stockEmp,&stock,&stockEm,&posEmp,last,posEm);
        else if(strcmp(cmd,"emls")==0) AfficheEmprunt(&stockEmp,&stock,&stockEm,posEmp);
        else if(strcmp(cmd,"emsr")==0) rechercheEmprunt(&stockEmp,&stock,&stockEm,posEmp);
        else if(strcmp(cmd,"help")==0) help();
        else if(strcmp(cmd,"clsc")==0) system("cls");
        else if(strcmp(cmd,"exit")==0) {
            backUpLivre(&stock,last);
            backUpEmprunteur(&stockEm,posEm);
            backUpEmprunt(&stockEmp,posEmp);
            sortie=1;
        }
        else puts("  #[erreure] Commande Inconnue !");
    }
    return 0;
}
//----------------------------------------------------
//fonctions dur les chaines
char toCH(int x){
    char t = '0';
    switch(x){

        case 0:
            t = '0';
        break;
        case 1:
            t = '1';
        break;
        case 2:
            t = '2';
        break;
        case 3:
            t = '3';
        break;
        case 4:
            t = '4';
        break;
        case 5:
            t = '5';
        break;
        case 6:
            t = '6';
        break;
        case 7:
            t = '7';
        break;
        case 8:
            t = '8';
        break;
        case 9:
            t = '9';
        break;
    }

    return t;
}
int toInt(char x){
    char t = 0;
    switch(x){

        case '0':
            t = 0;
        break;
        case '1':
            t = 1;
        break;
        case '2':
            t = 2;
        break;
        case '3':
            t = 3;
        break;
        case '4':
            t = 4;
        break;
        case '5':
            t = 5;
        break;
        case '6':
            t = 6;
        break;
        case '7':
            t = 7;
        break;
        case '8':
            t = 8;
        break;
        case '9':
            t = 9;
        break;
    }

    return t;
}
void clearChaine(char *chaine){

    int t = strlen(chaine);
    for(int i=0;i<t;i++){

        if(*(chaine+i) == '\n') *(chaine+i) = '\0';
    }
}
void help(){
    puts(" ");
    puts("  COMMANDE GENERALES");
    puts("    help -> Afficher l'aide");
    puts("    clsc -> Effacer l'ecran");
    puts(" ");
    puts("  COMMANDE SUR LIVRE");
    puts("    lvnv -> Ajouter un livre ");
    puts("    lvls -> Afficher tous les livres disponibles");
    puts("    lvsr -> Rechercher un livre ");
    puts("    lvdl -> Supprimer un livre ");
    puts(" ");
    puts("  COMMANDE SUR EMPRUNTEUR");
    puts("    amnv -> Ajouter un emprunteur");
    puts("    amls -> Afficher tous les emprunteurs");
    puts("    amsr -> Rechercher un emprunteur");
    puts("    amdl -> Supprimer un emprunteur");
    puts(" ");
    puts("  COMMANDE SUR EMPRUNTS");
    puts("    emnv -> Ajouter un emprunt");
    puts("    emls -> Afficher tous les emprunts");
    puts("    emsr -> Rechercher un emprunt");
    puts(" ");
}

//------------------LIVRES---------------------------------------------------------

void AjoutLivre(struct Livre *lien,int *pos){

    int indice = *pos;
    char titre[20];
    char auteur[20];

    printf("   @ titre du livre ~ ");
    fgets(titre,20,stdin);
    fflush(stdin);
    printf("   @ Auteur du livre ~ ");
    fgets(auteur,20,stdin);
    fflush(stdin);

    // on lave les chaine de \n
    clearChaine(titre);
    clearChaine(auteur);

    printf("   Ajout d'un nouveau livre \n   Titre:%s , Auteur :%s\n",titre,auteur);
    puts("   #[succes] Insertion faite");
    strcpy((lien+indice)->titre,titre);
    strcpy((lien+indice)->auteur,auteur);
    (*pos)++;
}

void AfficheLivres(struct Livre *lien,int fond){

    puts("  LISTE DE LIVRE DISPONIBLE");
    puts("  N:[ Titre , Auteur ]");
    for(int i=0;i<fond;i++){

        if(strcmp(lien->titre,"@")==0 && strcmp(lien->auteur,"@") == 0){

            lien++;
            continue;
        };
        printf("  %d:[ %s , %s ]\n",(i+1),lien->titre,lien->auteur);
        lien++;
    }
}

int RechercheLivre(struct Livre *lien,int pos){

    int founded = -1;
    char titre[20];
    puts("  RECHERCHE D'UN LIVRE");
    printf("   @ titre du livre ~ ");
    fgets(titre,20,stdin);
    fflush(stdin);

    clearChaine(titre);
    for(int i=0;i<pos;i++){

        if(strcmp(lien->titre,titre)==0){

            puts("   #[succes] LIVRE DISPONIBLE");
            printf("  Titre:%s , Auteur:%s\n",lien->titre,lien->auteur);
            founded = i;
            break;
        }else lien++;
    }

    if(founded == (-1)) puts("  #[erreure] LIVRE NON DISPONNIBLE");

    return founded;
}

void supprimerLivre(struct Livre *lien,int pos){


    int founded = 0;
    char titre[20];
    puts("  SUPPRESSION D'UN LIVRE");
    printf("   @ titre du livre ~ ");
    fgets(titre,20,stdin);
    fflush(stdin);
    clearChaine(titre);
    for(int i=0;i<pos;i++){

        if(strcmp(lien->titre,titre)==0){

            puts("  #[succes] LIVRE A SUPPRIMER");
            printf("  Titre:%s , Auteur:%s\n",lien->titre,lien->auteur);
            strcpy(lien->titre,"@");
            strcpy(lien->auteur,"@");
            founded = 1;
            break;
        }else lien++;
    }

    if(founded == 0){

        puts("  #[erreure] LIVRE NON DISPONNIBLE");
    }
}

int backUpLivre(struct Livre *lien,int pos){

    FILE *livre_backup=fopen("livre_bd.txt","w+");
    if(!livre_backup){

        printf("Impossible d'ouvrir le fichier de suavegarde");
        return 0;
    }
    for(int i=0;i<pos;i++){

        if(strcmp(lien->titre,"@")==0 && strcmp(lien->auteur,"@") == 0) {

            lien++;
            continue;
        }
        fputs(lien->titre,livre_backup);
        fputs(";",livre_backup);
        fputs(lien->auteur,livre_backup);
        fputs("\n",livre_backup);
        lien++;
    }
    fclose(livre_backup);
    return 1;
}

int getSeparator(char *chaine){

    int pos =-1;
    int tour=0;
    while(pos==(-1)){

        if(*(chaine+tour)==';'){

            pos = tour;
        }else tour++;
    }
    return pos;
}
void copyPart(int part,char *dst,char *target,int separator){

    int i =(part == 1)?0:separator+1;
    int fin = (part == 1)?separator:strlen(target);
    int start =0;
    for(i;i<fin;i++){

        if(*(target+i)!='\n'){

            *(dst+start) =*(target+i);
             start++;
        }
    }
    *(dst+start)='\0';
}
int restoreLivres(struct Livre *lien,int *pos){

    FILE *livre_backup=fopen("livre_bd.txt","r");
    if(!livre_backup){

        printf("Impossible d'ouvrir le fichier de suavegarde");
        return 0;
    }
    char chaine[40];
    while(fgets(chaine,40,livre_backup)!=NULL){

        int seprator = getSeparator(chaine);
        copyPart(1,lien->titre,chaine,seprator);
        copyPart(2,lien->auteur,chaine,seprator);
        (*pos)++;
        lien++;
    }
    fclose(livre_backup);
    return 1;
}
