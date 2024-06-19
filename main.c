
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
