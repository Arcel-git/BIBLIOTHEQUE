
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
