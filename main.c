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



//------------------EMPRUNTEUR---------------------------------------------------------
void AjoutEmprunteur(struct Emprunteur *lien,int *pos){

    int indice = *pos;
    char nom[20];
    char prenom[20];

    printf("   @ Nom de l'Emprunteur ~ ");
    fgets(nom,20,stdin);
    fflush(stdin);
    printf("   @ Prenom de l'Emprunteur ~ ");
    fgets(prenom,20,stdin);
    fflush(stdin);

    // on lave les chaine de \n
    clearChaine(nom);
    clearChaine(prenom);

    printf("   Ajout d'un Emprunteur  \n   Nom:%s , Prenom :%s\n",nom,prenom);
    puts("   #[succes] Insertion faite");
    strcpy((lien+indice)->nom,nom);
    strcpy((lien+indice)->prenom,prenom);
    (*pos)++;
}
void AfficheEmpreteur(struct Emprunteur *lien,int fond){

    puts("  LISTE D'EMPRUNTEUR ");
    puts("  N:[ NOM , PRENOM ]");
    for(int i=0;i<fond;i++){

        if(strcmp(lien->nom,"@")!=0 && strcmp(lien->prenom,"@") != 0){

            printf("  %d:[ %s , %s ]\n",(i+1),lien->nom,lien->prenom);
        }
        lien++;
    }
}
int RechercheEmprunteur(struct Emprunteur *lien,int pos){

    int founded = -1;
    char nom[20];
    puts("  RECHERCHE D'UN EMPRUNTEUR");
    printf("   @ Nom  ~ ");
    fgets(nom,20,stdin);
    fflush(stdin);
    clearChaine(nom);

    for(int i=0;i<pos;i++){

        if(strcmp(lien->nom,nom)==0){

            puts("  #[succes] EMPRUNTEUR DISPONIBLE");
            printf("  Nom:%s , Prenom:%s\n",lien->nom,lien->prenom);
            founded = i;
            break;
        }else lien++;
    }

    if(founded == (-1)) puts("  #[erreure] EMPRUNTEUR NON DISPONNIBLE");

    return founded;
}
void supprimerEmprunteur(struct Emprunteur *lien,int pos){


    int founded = 0;
    char nom[20];
    puts("  SUPPRESSION D'UN EMPRUNTEUR");
    printf("   @ nom ~ ");
    fgets(nom,20,stdin);
    fflush(stdin);
    clearChaine(nom);
    for(int i=0;i<pos;i++){

        if(strcmp(lien->nom,nom)==0){

            puts("  #[succes] EMPRUNTEUR A SUPPRIMER");
            printf("  Nom:%s , Prenom:%s\n",lien->nom,lien->prenom);
            strcpy(lien->nom,"@");
            strcpy(lien->prenom,"@");
            founded = 1;
            break;
        }else lien++;
    }

    if(founded == 0){

        puts("  #[erreure] EMPRUNTEUR NON DISPONNIBLE");
    }
}
int backUpEmprunteur(struct Emprunteur *lien,int pos){

    FILE *emprunteur_backup=fopen("emprunteur_db.txt","w+");
    if(!emprunteur_backup){

        printf("Impossible d'ouvrir le fichier de suavegarde\n");
        return 0;
    }
    for(int i=0;i<pos;i++){

        if(strcmp(lien->nom,"@")==0 && strcmp(lien->prenom,"@") == 0) {

            lien++;
            continue;
        }
        fputs(lien->nom,emprunteur_backup);
        fputs(";",emprunteur_backup);
        fputs(lien->prenom,emprunteur_backup);
        fputs("\n",emprunteur_backup);
        lien++;
    }
    fclose(emprunteur_backup);
    return 1;
}
int restoreEmprunteur(struct Emprunteur *lien,int *pos){

    FILE *emprunteur_db=fopen("emprunteur_db.txt","r");
    if(!emprunteur_db){

        printf("Impossible d'ouvrir le fichier de sauvegarde\n");
        return 0;
    }
    char chaine[40];
    while(fgets(chaine,40,emprunteur_db)!=NULL){

        printf("chaine =->%s",chaine);
        int seprator = getSeparator(chaine);
        copyPart(1,lien->nom,chaine,seprator);
        copyPart(2,lien->prenom,chaine,seprator);
        (*pos)++;
        lien++;
    }
    fclose(emprunteur_db);
    return 1;
}



//------------------EMPRUNT---------------------------------------------------------
void AjoutEmprunt(struct Emprunt *lien,struct Livre *stock,struct Emprunteur *stockEm,int *posEm,int posLivre,int posAm){

    int indice = *posEm;
    int LivreId = RechercheLivre(stock,posLivre);
    int EmprunteurID = RechercheEmprunteur(stockEm,posAm);

    if(LivreId >= 0 && EmprunteurID >= 0){

        (lien+indice)->IDLivre=LivreId;
        (lien+indice)->IDEmp=EmprunteurID;
        (*posEm)++;
        puts("  Emprunt Enregistrer");

    }else puts("Impossible d'ajouter l'emprunt car les infos sont incorrecte");

}
void AfficheEmprunt(struct Emprunt *lien,struct Livre *stock,struct Emprunteur *stockEm,int fond){

    puts("  LISTE D'EMPRUNTS ");
    puts("  N:[ TITRE , EMPRUNTEUR ]");
    for(int i=0;i<fond;i++){

        printf("  %d:[ %s , %s  %s ]\n",(i+1),
               (stock+lien->IDLivre)->titre,
               (stockEm+lien->IDEmp)->prenom,
               (stockEm+lien->IDEmp)->nom);
        lien++;
    }
}
void rechercheEmprunt(struct Emprunt *lien,struct Livre *stock,struct Emprunteur *stockEm,int fond){


    int founded = 0;
    char nomEm[20];
    puts("  RECHERCHE D'UN EMPRUNT");
    printf("   @ Nom  ~ ");
    fgets(nomEm,20,stdin);
    fflush(stdin);
    clearChaine(nomEm);
    printf(" LIVRE  EMPRUNTER DE %s\n",nomEm);
    for(int i=0;i<fond;i++){

        if(strcmp(
                  (stockEm+lien->IDEmp)->nom,nomEm)==0
           ){
            printf(" %d:%s\n",(i+1),(stock+lien->IDLivre)->titre);
            founded++;

        }else lien++;
    }

    if(founded ==0) puts("  EMPRUNT NON DISPONNIBLE");
}

int *getParts(char *src){

    int fin = strlen(src);
    static int retour[2];
    int pos =0;

    for(int i=0;i<fin;i++){

        if(*(src+i) == ';') continue;
        else{

            int r =toInt(*(src+i));
            retour[pos] = r;
            pos++;
        }
    }
    return &retour;
}
int backUpEmprunt(struct Emprunt *lien,int pos){

    FILE *emprunts_backup=fopen("emprunts_db.txt","w+");
    if(!emprunts_backup){

        printf("Impossible d'ouvrir le fichier de sauvegarde\n");
        return 0;
    }
    for(int i=0;i<pos;i++){

        char p[2] = {toCH(lien->IDLivre),'\0'};
        fputs(p,emprunts_backup);
        fputs(";",emprunts_backup);
        p[0] = toCH(lien->IDEmp);
        fputs(p,emprunts_backup);
        fputs("\n",emprunts_backup);
        lien++;
    }
    fclose(emprunts_backup);
    return 1;
}
int restoreEmprunts(struct Emprunt *lien,int *pos){

    FILE *emprunts_db=fopen("emprunts_db.txt","r");
    if(!emprunts_db){

        printf("Impossible d'ouvrir le fichier de sauvegarde\n");
        return 0;
    }
    char chaine[4];
    while(fgets(chaine,4,emprunts_db)!=NULL){


        int *parts = getParts(chaine);
        lien->IDLivre = *(parts);
        lien->IDEmp = *(parts+1);
        (*pos)++;
        lien++;
    }
    fclose(emprunts_db);
    return 1;
}
