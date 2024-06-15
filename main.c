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
    puts("    lvnv -> AJoutet un Livre au stock");
    puts("    lvls -> Afficher les livre disponibles");
    puts("    lvsr -> Rechrecher un un Livre dans le stock");
    puts("    lvdl -> Supprimer un Livre du stock");
    puts(" ");
    puts("  COMMANDE SUR EMPRUNTEUR");
    puts("    amnv -> AJouter un Emprunteur");
    puts("    amls -> Afficher les Emprunteurs");
    puts("    amsr -> Rechrecher un Emprunteur");
    puts("    amdl -> Supprimer un Emprunteur");
    puts(" ");
    puts("  COMMANDE SUR EMPRUNTS");
    puts("    emnv -> AJouter un Emprunt");
    puts("    emls -> Afficher les Emprunts");
    puts("    emsr -> Rechrecher un Emprunt");
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
