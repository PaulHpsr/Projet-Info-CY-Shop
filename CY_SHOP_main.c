#include "ReadSpecificLine.h"
#include "couleurs.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
// Bibliothèques


// Structures

typedef struct {
  char name[100];
  char prenom[100];
  int age;
  char password[100];
  char email[100];
} Client;

typedef struct {
  int id;
  char name[100];
  int price;
  int qty;
  char taille;
  int place_stck;
} Product;


// Déclaration des fonction (dans l'ordre)//
void signup();
void Crea_Client();
int valid();
int compte_existant();
int login();

//
int DefaultScreen();
int getID();
void manageProduct();
void addProduct();
void displayAllProduct();
int NbrProduct();
int updateProduct();
void GestionMode();
void displayAllUsers();
int modifUsers();
int modifMesInfos();
void purchaseProduct();
void finalachat();
void openhistorique();
void openpanier();
void majProductachat();
void updatePRODUCTAchat();
int prixfinal();
void seDesinscrire();

// Espaces
void EspaceClient();
void EspaceAdmin();

// Déclaration des variables fichiers
char fproduct[] = {"product.txt"};
char fstock[] = {"stockmax.txt"};
char email[100];

// Connexion/Création de compte

void signup() {
// variables
  char t_name[100], t_password1[100];
  char t_password2[100], t_email[100];
  char t_prenom[100];
  int t_age;
  int x;
  int valide;  
  system("clear");

//Ecran d'inscription
  
  printf("\n\n\t=================Inscription à CY-SHOP=================\n\n");

  // Nom
  printf("\tEntrer votre NOM : ");
  scanf("%s", t_name);

  printf("\tEntrer votre PRENOM : ");
  scanf("%s", t_prenom);
  // Email
  printf("\tEntrer votre Email : ");
  scanf("%s", t_email);

  // MDP
  printf("\tMot de Passe : ");
  scanf("%s", t_password1);

  // MDP Confirm
  printf("\tConfirmez le Mot de Passe : ");
  scanf("%s", t_password2);

  // Age
  printf("\tEntrer votre AGE : ");
  scanf("%d", &t_age);

  //Voir si les infos entrées sont valides
  x = valid(t_name,t_password1,t_prenom,t_email,t_age);
  if (x == 1) {

    // Processus de crea de fiche client
    Crea_Client(t_name,t_prenom,t_email,t_password1,t_password2,t_age);

    // Se connecter
    GestionMode();
  }
}

// Création de la fiche client
void Crea_Client(char t_name[], char t_password1[], char t_prenom[], char t_email[], int t_age) {

  FILE *fc; // pointeur file du client
  Client client;
  int validate = 0;
  char *fname = malloc(sizeof(char) * 200);
  //nom du fichier client
  strcpy(fname, t_email);
  strcat(fname, ".txt");

  if (compte_existant(t_email) == 1) { // Pas de doublons de client

    fc = fopen(fname, "a"); // Creation du fichier Client
    strcpy(client.name, t_name);
    strcpy(client.email, t_email);
    strcpy(client.prenom, t_prenom);
    client.age = t_age;
    strcpy(client.password, t_password1);
    //écriture des infos dans le fichier
    fprintf(fc, "%s\n%s\n%d\n%s\n%s", client.name, client.prenom, client.age,
            client.password, client.email);
    fclose(fc);
    printf("\nCompte bien créé\n\n");
  }
  free(fname);
}

// Vérif des infos client bien conformes
int valid(char t_name[], char t_prenom[], char t_email[], char t_password1[], char t_password2[], int t_age) {
  int i;
  int count = 0;
  int nbr;
  int succes;
  
  // Verif Nom
  for (i = 0; t_name[i] != '\0'; i++) { //Tant qu'il reste des char dans t_name 
    while (!((t_name[i] >= 'a' && t_name[i] <= 'z') || (t_name[i] >= 'A' && t_name[i] <= 'Z'))) { //Vérif si le Nom composé que de lettres
      printf("\nVeuillez entrer un nom valide!\n");
     
      printf("Entrer votre prénom:\n");
      scanf("%s", t_name);
    }
  }
  
  // Verif Prenom
  for (i = 0; t_prenom[i] != '\0'; i++) {
    while (!((t_prenom[i] >= 'a' && t_prenom[i] <= 'z') ||     //Même chose que pour le Nom
             (t_prenom[i] >= 'A' && t_prenom[i] <= 'Z'))) {
      printf("\nVeuillez entrer un prénom valide!\n");
      
      scanf("%s", t_prenom);
    }
  }
  
  // Verif Email
  for (i = 0; t_email[i] != '\0'; i++) {
    if (t_email[i] == '@' || t_email[i] == '.') {       //Vérif si t_email contient au moins 1 @ et 1 . -> email valide
      count++;
    }
  }
  while (count != 2) {   //On sécurise l'entrée de email
    count = 0;
    printf("\nEmail non valide!!\nVeuillez Saisir une adresse email valide:\n");
    scanf("%s", t_email);
    for (i = 0; t_email[i] != '\0'; i++) {
      if (t_email[i] == '@' || t_email[i] == '.') {
        count++;
      }
    }
  }
  
  // Verif MDP et Age
  //MDP
  while (strcmp(t_password1, t_password2)) {  //On compare t_password et t_password2
    printf("\nMot de Passe ne sont pas les même!\n\n");
    printf("\nVeuillez recommencer:\n");

    printf("\tMot de Passe : ");
    scanf("%s", t_password1);

    // Verif MDP Confirm
    printf("\tConfirmer le Mot de Passe : ");
    scanf("%s", t_password2);
  }
  
  while (t_age == 0 && t_age < 0) {
    printf("\n\nVeuillez entrer un age valide!\n\n");
    // Verif Age
    printf("\tEntrer votre Age : ");
    scanf("%d", &t_age);
  }
  succes = 1;

  return succes;
}

// Vérif si client déjà inscrit != Doublons clients
int compte_existant(char t_email[]) {
  char *fname = malloc(sizeof(char) * 200);
  
  strcpy(fname, t_email);   //Les fichiers de client inscrit sont sous forme : "email.txt"
  strcat(fname, ".txt");
  
  // Recherche dans le directory (fichiers du programme)
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) // Tant qu'il reste des fichiers non vérif
    {
      if (!(strcmp(dir->d_name,fname))) { // Si d_name == email client -> déjà inscrit
        printf("\nCompte existant, veuillez vous connecter\n\n");
        free(fname);
        return 0; //compte existant
      }
    }
    closedir(d);
  }
  return 1; // Compte non existant
}

// Connexion des clients
int login() {
//Logs admin pour Mode Gestion
char admin[30] = "admin@gmail.com";
char adminp[10] = "a";
  
  system("clear");
  
  int a;
  int i;
  FILE *fc;
  int count = 0;

  char email2[5] = ".txt";
  char pasword[100];
  char pasword2[100];

  //Affichage de Connexion
  printf("\n\n\t================= ");
  couleur("34");
  printf("Connexion à CY-SHOP ");
  couleur("0");
  printf("=================\n\n");
  printf("\n\nLOGIN\n\n");
  printf("\t Entrez votre Email: ");

  // EMAIL
  scanf("%s", email);
  for (i = 0; email[i] != '\0'; i++) {
    if (email[i] == '@' || email[i] == '.') {
      count++;
    }
  }
  //Sécurisation de l''entrée email
  while (count != 2) {
    count = 0;
    printf("\nEmail non valide!!\nVeuillez Saisir une adresse email valide:\n");
    scanf("%s", email);
    for (i = 0; email[i] != '\0'; i++) {
      if (email[i] == '@' || email[i] == '.') {
        count++;
      }
    }
  }
  
  printf("\t Entrez votre Mot de Passe: ");
  // MDP
  scanf("%s", pasword2);
  if ((strcmp(email, admin) == 0)) { // Chemin Admin
    if ((strcmp(pasword2, adminp) == 0)) {
      a = 2;
      return a;
    }
  }
  
  strcat(email, email2);
  // Verif correspondance mdp/compte
  fc = fopen(email, "r");
  if (fc == NULL) {
    printf("\nCompte inexistant, Veuillez vous créer un compte\n");
    a = 3;
  }
  // Vérif de la 4ème ligne du fichier client (MDP)
  strcpy(pasword, ReadLine(4, email));

  // Correspondance
  if (strcmp(pasword, pasword2) == 0) {
    printf("\nVous êtes bien connecté\n");
    a = 1;
  } else {
    printf("\nMauvais Mot de passe ou adresse email\nVeuillez vous créer un "
           "compte\n");
    a = 3;
  }
  return a;
}

// Mode Management

// Generation de ID produit
int getID() {
  FILE *fp;
  int value = 0;
  
  fp = fopen("prodid.txt", "r");
  if (fp == NULL) { // Création du fichier qui suit le id produit (nbr de
                    // produit total -> prochain ID produit)
    fp = fopen("prodid.txt", "w");
    fprintf(fp, "%d", 0);
    fclose(fp);
    fp = fopen("prodid.txt", "r");
  }
  // Remplace la valeur par valeur+1 à chaque fois qu'un produit est ajouté à la liste
  fscanf(fp, "%d", &value);
  fclose(fp);
  fp = fopen("prodid.txt", "w");
  fprintf(fp, "%d", value + 1);
  fclose(fp);
  return value + 1;
}

// Interface de Management
void manageProduct() {
  int choice;
  int back = 0;

  // Affichage du mode Gestion produit (Admin)
  
  while (1) {

    printf("\n\n\t================= ");
    couleur("34");
    printf("Mode Management Produit ");
    couleur("0");
    printf("=================\n\n");
    couleur("36");
    printf("1.Ajouter un Produit\n\n");
    printf("2.Afficher la liste Produit\n\n");
    printf("3.Modifier un produit\n\n");
    printf("0.Retour\n\n");
    couleur("0");
    printf("\n\n\t=======================================================\n\n");
    printf("\nEntrer votre choix:\n");

    //Sécurisation de l'entrée
    while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3 && choice != 0)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2, 3 et 0
            printf("Erreur : saisie invalide. Veuillez entrer une valeur parmi 1, 2, 3 ou 0 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
//Appel de fonction dépendant du choix utilisateur
  switch (choice) {
    case 1:
      addProduct();
      break;
    case 2:
      displayAllProduct();
      break;
    case 3:
      updateProduct();
      break;
    case 0:
      EspaceAdmin();
      break;
    default:
      printf("\nVeuillez renter un choix valide\n");
      break;
    }
  }
}

// Ajouter un Produit
void addProduct() {
  FILE *fp;
  FILE *fstock_max;
  
  Product t1;
  
  int taille;
  int stockact;
  int stock_base = 0; //stock à ajouté (place que prend l'ajout du produit)
  
  fp = fopen(fproduct, "a");
  fstock_max = fopen(fstock, "r");
  t1.id = getID();
  //Entrées des données du produits
  printf("\nNom du produit:");
  scanf("%s", t1.name);
  
  printf("\nPrix du produit:");
  //sécurisation de l'entrée
  while (1) {
        if (scanf("%d", &t1.price) != 1 || (t1.price<0)) {
            printf("Erreur : saisie invalide. Veuillez entrer une valeur positive: \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
  
  printf("\nTaille du produit");
  printf("\n1.S\n2.M\n3.L\n");
  //sécurisation de l'entrée
  while (1) {
        if (scanf("%d", &taille) != 1 || (taille != 1 && taille != 2 && taille != 3)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2 et 3
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1, 2 ou 3 : ");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
  //Choix de la taille en fonction de l'entrée utilisateur
  switch (taille) {
  case 1:
    t1.taille = 'S';
    t1.place_stck = 1;
    break;
  case 2:
    t1.taille = 'M';
    t1.place_stck = 2;
    break;
  case 3:
    t1.taille = 'L';
    t1.place_stck = 3;
    break;
  }
  
  printf("\nQuantité en stock:");
  while (1) {
        if (scanf("%d", &t1.qty) != 1 || (t1.qty<1)) {
            printf("Erreur : saisie invalide. Veuillez entrer une valeur positive : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }

  //Lis la valeur des stock dispo actuelles
  fscanf(fstock_max, "%d", &stockact);
  fclose(fstock_max);
  
  stock_base += (t1.place_stck) * (t1.qty);
  //Vérif si il y a assez de place en stck pour ajouter le produit
  if (stock_base > stockact) {
    printf("La capacité de stockage du magasin est dépassé. Vous ne pouvez "
           "plus ajouter de produits\n");
    manageProduct();
  } else {
    //Ajoute le produit dans le fichier "product.txt"
    fprintf(fp, "%d\n%s\n%d\n%c\n%d\n%d\n", t1.id, t1.name, t1.price, t1.taille,t1.qty, t1.place_stck);
    
    //Actualise la valeur des stock dispo dans le CY-SHOP après l'ajout du produit
    stockact = stockact - stock_base;
    fstock_max = fopen(fstock, "w");
    fprintf(fstock_max, "%d", stockact);
    fclose(fstock_max);
  }
  fclose(fp);
}

// Afficher les produits
void displayAllProduct() {
  int MAX_LENGTH = 100;
  FILE *fichier = fopen(fproduct, "r");

  //Vérif si le fichier existe
  if (fichier == NULL) {
    printf("\nErreur lors de l'ouverture du fichier.\n");
    printf("\nFichier manquant\n");
    return;
  }
 
  int id;
  char nom[MAX_LENGTH];
  int prix;
  int quantite;
  char Taille[MAX_LENGTH];
  int Place_stck;

  //Affichage
  printf("\tTotal stock dispo:\t%d\n\n", atoi(ReadLine(1, fstock)));
  printf("\t\nProduits dont les stocks sont vides:\n");
  printf("\nID\t\tProduit\t\tPrix\t\tTaille\t\tQté\n");
fopen(fproduct,"a");
  //Pour chaque produit, la fct° Readline va récupérer la ligne correspondante à l'info désirée (chaque produit prend 6 lignes dans le fichier d'ou l'utilisation du "for (i)")
  for (int i = 0; i < NbrProduct(); i++) {
    id = atoi(ReadLine(1 + (6 * i), fproduct));
    strcpy(nom, ReadLine(2 + (6 * i), fproduct));
    prix = atoi(ReadLine(3 + (6 * i), fproduct));
    quantite = atoi(ReadLine(5 + (6 * i), fproduct));
    strcpy(Taille, ReadLine(4 + (6 * i), fproduct));
    Place_stck = atoi(ReadLine(6 + (6 * i), fproduct));
    if (quantite == 0) {
      //vérif si la qty est 0
      printf("%d\t\t%s\t\t\t\t%d\t\t%s\t\t%d\n", id, nom, prix, Taille,
             quantite);
    }
  }
  printf("\n\n\n\tTous les produits:\n");
  printf("\nID\t\tProduit\t\tPrix\t\tTaille\t\tQté\n");
  //Même procédé, mais cette fois affiche tous les produits
  for (int i = 0; i < NbrProduct(); i++) {
    id = atoi(ReadLine(1 + (6 * i), fproduct));
    strcpy(nom, ReadLine(2 + (6 * i), fproduct));
    prix = atoi(ReadLine(3 + (6 * i), fproduct));
    quantite = atoi(ReadLine(5 + (6 * i), fproduct));
    strcpy(Taille, ReadLine(4 + (6 * i), fproduct));
    Place_stck = atoi(ReadLine(6 + (6 * i), fproduct));
    printf("%d\t\t%s\t\t\t\t%d\t\t%s\t\t%d\n", id, nom, prix, Taille, quantite);
  }

  fclose(fichier);
}

// Obtenir le nombre de produits totaux
int NbrProduct() {
  int nprod;
  FILE *fp;
  //Récupère la valeur contenue dans le fichier prodid.txt qui contient l'id du dernier produit ajouté = le nbr de produit totaux
  fp = fopen("prodid.txt", "r");
  fscanf(fp, "%d", &nprod);
  fclose(fp);
  return nprod;
}

// Modifier une information du produit;
int updateProduct() {
  int choice;
  int id;
  FILE *file = fopen(fproduct, "r"), *temp;
  FILE *fstock_max = fopen(fstock, "r");
  char filename[FILENAME_SIZE];
  char temp_filename[FILENAME_SIZE];

  char buffer[MAX_LINE];
  char replace[MAX_LINE];
  int replace_line = 0;
  int stockact;
  int stock_base;
  int place_stck;
  stockact = atoi(ReadLine(1, fstock));
  int add_stck;
  int stockact_interm = 0;
  int qty_init_intermediaire = 0;
  int qty_init = atoi(ReadLine(5 + (6 * id), fproduct));

  //Vérif si le fichier produit existe
  if (file == NULL) {
    printf("\nErreur lors de l'ouverture du fichier.\n");
    printf("\nFichier manquant\n");
    return -1;
  }
//création du fichier temporaire
  strcpy(temp_filename, "temp__");
  strcat(temp_filename, fproduct);

  //Choix du produit à modif
  printf("\nQuel produit voulez-vous modifier (ID):\n");
    while(1){
      if(scanf("%d",&id) != 1 || id <= 0 || id > NbrProduct()){
        printf("\nMauvais code produit, veuillez réessayer\n");
        printf("\nQuel produit voulez-vous modifier (ID):\n");
        while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
      }
      else{
        break;
      }
    }
//Choix de l'info à modif
  couleur("36");
  printf("\nQue voulez vous changer:\n1.Nom du Produit\n2.Prix du "
         "Produit\n3.Quantité\n");
  couleur("0");
  
  while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2 ou 3
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1, 2 ou 3 : ");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        }
        else{
          break;
        }
    }
  
  if (choice == 1) { // NOM
    replace_line = 2 * id;
    
    printf("\nChangement:\n");
    scanf("%s", replace);

  } else if (choice == 2) { // PRIX
    
    printf("\nChangement:\n");
    scanf("%s", replace);
    replace_line = 3 * id;

  } else if (choice == 3) { // QTY
    printf("\n%d", id);
    
    printf("\nChangement:\n");
    scanf("%s", replace);
    int replace1 = atoi(replace); //Transforme char en int

    fclose(fstock_max);
    
    //Prend la place du produit (en fct° de la taille : S-> 1 M->2 L->3 unités de place)
    place_stck = atoi(ReadLine(6 + (6 * id), fproduct));
    
    fstock_max = fopen(fstock, "w");
    
    //Si la nouv. qté > à initiale -> alors on doit enlever des unités de place au stck max
    if (qty_init < replace1) {
        
      qty_init_intermediaire = replace1 - (qty_init); //Différence entre nouv. qté et l'ancienne = qty. rajoutée
      add_stck = qty_init_intermediaire * place_stck; //stock à retirer du max
        
      if (add_stck > qty_init_intermediaire) {
        printf("La capacité de stockage du magasin est dépassé. Vous ne pouvez plus ajouter de produits\n");
        manageProduct();
      } else {
        stockact_interm = stockact - add_stck;
        fprintf(fstock_max, "%d", stockact_interm); //On actualise la valeur du stock max dans le fichier
      }
    } 
    else if (qty_init > replace1) { //On fait la même chose mais cette fois-ci qty initiale > nouv. qté -> on rajoute de la place au stock dispo
      qty_init_intermediaire = (qty_init) - (replace1);
      add_stck = qty_init_intermediaire * place_stck;
      stockact_interm = stockact + add_stck;
      fprintf(fstock_max, "%d", stockact_interm);
    }
  replace_line = 5 * id;

  fclose(fstock_max);
  } else {
    printf("\nErreur!\n");
    return -1;
  }

  file = fopen(fproduct, "r");
  temp = fopen(temp_filename, "w");

  //On copie les lignes du fichier product dans le fichier temporaire sauf la ligne à modif -> on remplace avec le nouv.
  bool keep_reading = true;
  int current_line = 1;
  do {
    fgets(buffer, MAX_LINE, file);
    if (feof(file)) {
      keep_reading = false;
    } else if (current_line == replace_line) {
      fputs(replace, temp);
      fputc('\n', temp); // Ajout du caractère de fin de ligne
    } else {
      fputs(buffer, temp);
    }
    current_line++;
  } while (keep_reading);

  fclose(file);
  fclose(temp);
  remove(fproduct);
  rename(temp_filename, fproduct);
  return 0;
}

// BESOIN D'UNE VERSION DE UPDATEPRODUCT() SANS LE QUESTIONNAIRE DU DEBUT // Update Product pque pour les qté lorsque l'on fait un achat
void updatePRODUCTAchat(int id, int nouvQty) {
  FILE *file = fopen(fproduct, "r"), *temp;
  ;
  char temp_filename[100];
  char buffer[MAX_LINE];
  char replace[100];
  int replace_line = 0;

  //Vérif si le fichier existe
  if (file == NULL) {
    printf("\nErreur lors de l'ouverture du fichier.\n");
    printf("\nFichier manquant\n");
    EspaceClient();
  }

  strcpy(temp_filename, "temp__");
  strcat(temp_filename, fproduct);
  
//Lors de l'achat, la qty acheté doit être déduit de la qty disponible
//Même processus que uptdateProduct()
  replace_line = 5 + (6 * id);
  sprintf(replace, "%d", nouvQty);
  

  file = fopen(fproduct, "r");
  temp = fopen(temp_filename, "w");

  bool keep_reading = true;
  int current_line = 1;
  do {
    fgets(buffer, MAX_LINE, file);
    if (feof(file)) {
      keep_reading = false;
    } else if (current_line == replace_line) {
      fputs(replace, temp);
      fputc('\n', temp); // Ajout du caractère de fin de ligne
    } else {
      fputs(buffer, temp);
    }
    current_line++;
  } while (keep_reading);

  fclose(file);
  fclose(temp);
  remove(fproduct);
  rename(temp_filename, fproduct);
}

// Update du stock prod lorsque on achète
void majProductachat() {
  int compt = 0;
  char nom_panier[100];
  printf("%s",email);
  strcpy(nom_panier, email);
  strcat(nom_panier, "_panier.txt");
   printf("%s",nom_panier);
  FILE *panier = fopen(nom_panier, "r");

  //Vérif si 
  if (panier == NULL) {
    printf("Erreur : Impossible d'ouvrir le fichier\n");
    EspaceClient();
  }

  // CONNAITRE CB DE PROD DANS L'HISTORIQUE
  char id[100], nom[100], prix[100], taille[100], quantite[100], place[100];
  while (fscanf(panier, "%s %s %s %s %s %s", id, nom, prix, taille, quantite,
                place) == 6) {
    compt++;
  }

  int prod_id;
  int prod_qty;
  int prod_place_stck;

  int place_stck = 0;
  int stck_glob;
  FILE *fstock_max = fopen(fstock, "r");

  FILE *fp = fopen(fproduct, "r");
  int nouv_qty;

  for (int i = 0; i < compt; i++) { // Obtenir ID + QTY + PLACE STCK
    prod_id = atoi(ReadLine(1 + (6 * i), nom_panier));
    prod_qty = atoi(ReadLine(5 + (6 * i), nom_panier));
    prod_place_stck = atoi(ReadLine(6 + (6 * i), nom_panier));
    place_stck = place_stck + (prod_qty * prod_place_stck);


    prod_id = prod_id - 1;
    nouv_qty = atoi(ReadLine(5 + (6 * prod_id), fproduct)) - prod_qty;
  
    updatePRODUCTAchat(prod_id, nouv_qty);
  }

  stck_glob = atoi(ReadLine(1, fstock)) + place_stck; // Update la capa du shop
  fclose(fstock_max);
  fstock_max = fopen(fstock, "w");
  stck_glob = stck_glob + place_stck;
  fprintf(fstock_max, "%d", stck_glob);
  fclose(fstock_max);
  fclose(panier);

  // MODIF LA FICHE PRODUIT (QTY DIPSO)
}

// Afficher tous les utilisateurs//Admin
void displayAllUsers() {
  char fname[100];
  DIR *d;
  //Le pointeur va pointer tous les fichier dans le directory, si le fichier est un email -> client
  printf("\nVoici la liste des comptes utilisateurs enregistrés:\n");
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) !=NULL) // Tant qu'il reste des fichiers non vérif
    {
      strcpy(fname, dir->d_name);
      for (int i = 0; fname[i] != '\0'; i++) {
        if (fname[i] == '@') {
          printf("\n\t%s\n", fname);
        }
      }
    }
  }
  closedir(d);
  EspaceAdmin();
}

// Admin
int modifUsers() {
  FILE *file, *temp;
  int choice;
  char filename[FILENAME_SIZE];
  char temp_filename[FILENAME_SIZE];

  char buffer[MAX_LINE];
  char replace[MAX_LINE];
  int replace_line = 0;
  
  
  printf("\nQuel utilisateur voulez modifier(format .txt):\n");
  scanf("%s", filename);
  //sécurisation du scanf?

  strcpy(temp_filename, "temp");
  strcat(temp_filename, filename);

  couleur("36");
  printf("\nQue voulez vous changer:\n1.Nom de l'utilisateur\n2.Prenom de "
         "l'utilisateur\n3.Age de l'utilisateur\n");
  couleur("0");
  while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2 ou 3
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1, 2 ou 3 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
  switch(choice){
    case 1:
      replace_line = 1;
      break;
    case 2:
      replace_line = 2;
      break;
    case 3:
      replace_line = 3;
      break;
    default:
      printf("\nErreur!\n");
  }

  
  printf("Remplacement du texte:\n");
  scanf("%s", replace);

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("\nErreur lors de l'ouverture du fichier.\n");
    printf("\nFichier manquant\n");
    return -1;
  }
  temp = fopen(temp_filename, "w");

  bool keep_reading = true;
  int current_line = 1;
  do {
    fgets(buffer, MAX_LINE, file);
    if (feof(file)) {
      keep_reading = false;
    } else if (current_line == replace_line) {
      fputs(replace, temp);
      fputc('\n', temp); // Ajout du caractère de fin de ligne
    } else {
      fputs(buffer, temp);
    }
    current_line++;
  } while (keep_reading);

  fclose(file);
  fclose(temp);
  remove(filename);
  rename(temp_filename, filename);
  EspaceAdmin();
  return 0;
}
// Interface Manage Client//admin
void manageUsers() {
  int choice;
  int back = 0;
  while (1){

    printf("\n\n\t================= ");
    couleur("34");
    printf("Mode Management Client ");
    couleur("0");
    printf("=================\n\n");
    couleur("36");
    printf("1.Modifier Informations Client\n\n");
    printf("2.Afficher la liste des Clients\n\n");
    printf("0.Retour\n\n");
    couleur("0");
        printf("\n\n\t======================================================\n\n");
    printf("\nEntrer votre choix:\n");
    while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 0)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2 et 0
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1, 2 ou 0 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }

    switch (choice) {
    case 1:
      modifUsers();
      break;
    case 2:
      displayAllUsers();
      break;
    case 0:
      EspaceAdmin();
      break;
    default:
      printf("\nVeuillez renter un choix valide\n");
      break;
    }
  }
}

// Interface Client
int modifMesInfos() {
  FILE *file, *temp;
  int choice;
  char filename[FILENAME_SIZE];
  char temp_filename[FILENAME_SIZE];

  char buffer[MAX_LINE];
  char replace[MAX_LINE];
  int replace_line = 0;
  int MAX_LENGTH = 100;
  char nom[MAX_LENGTH];
  char prenom[MAX_LENGTH];
  char age[MAX_LENGTH];
  char email1[MAX_LENGTH];

  FILE *fc = fopen(email, "r");
  system("clear");
  
  printf("\nVoici Vos Informations Clients:\n");
  while (fscanf(fc, "%s", nom) == 1) {
    fscanf(fc, " %[^\n]", prenom);
    fscanf(fc, "%s", age);
    fscanf(fc, "%s", email1);

    printf("\nNom: %s\tPrenom: %s\tAge: %s\tEmail: %s\n", nom, prenom, age,
           email);
  }
  

  strcpy(filename, email);

  strcpy(temp_filename, "temp");
  strcat(temp_filename, filename);

  
  couleur("36");
  printf(
      "\nQue voulez vous changer:\n1.Nom\n2.Prenom\n3.Age\n4.Mot de Passe\n");
  couleur("0");
  while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3 && choice != 4)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2, 3 et 4
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1, 2, 3 ou 4 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
    
  switch(choice){
    case 1:
      replace_line = 1;
      break;
    case 2:
      replace_line = 2;
      break;
    case 3:
      replace_line = 3;
      break;
    case 4:
      replace_line = 4;
      break;
    default:
      printf("\nErreur!\n");
      break;
  }


  printf("Remplacement du texte:\n");
  scanf("%s", replace);

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("\nErreur lors de l'ouverture du fichier.\n");
    printf("\nFichier manquant\n");
    return -1;
  }
  temp = fopen(temp_filename, "w");

  bool keep_reading = true;
  int current_line = 1;
  do {
    fgets(buffer, MAX_LINE, file);
    if (feof(file)) {
      keep_reading = false;
    } else if (current_line == replace_line) {
      fputs(replace, temp);
      fputc('\n', temp); // Ajout du caractère de fin de ligne
    } else {
      fputs(buffer, temp);
    }
    current_line++;
  } while (keep_reading);

  fclose(file);
  fclose(temp);
  remove(filename);
  rename(temp_filename, filename);
  EspaceClient();
  return 0;
}

// Ajouter des produits au panier client
void Creapanier() {
  int choix_ach;
  FILE *panier;

  char nom_panier[100];
  int ID_prod;
  int aqty_achat;
  char anom_prod[100];
  int aprice_prod;
  char ataille_prod[100];
  int aqty_prod;
  int aplace_stck_prod;
  int aid_prod;

  printf("\nQuel produit voulez-vous ajouter au panier (ID) :\n");
  while (1){
    if(scanf("%d",&ID_prod) != 1 ||ID_prod <= 0 || ID_prod > NbrProduct()){
      printf("\nErreur mauvais ID, veuillez recommencer:\n");
      printf("\nQuel produit voulez-vous ajouter au panier (ID) :\n");
      while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
    }
    else{
      break;
    }
  }
  ID_prod--;
  printf("%s", ReadLine(5 + (ID_prod * 6), fproduct));
  aid_prod = atoi(ReadLine(1 + (ID_prod * 6), fproduct));
  strcpy(anom_prod, ReadLine(2 + (ID_prod * 6), fproduct));
  aprice_prod = atoi(ReadLine(3 + (ID_prod * 6), fproduct));
  strcpy(ataille_prod, ReadLine(4 + (ID_prod * 6), fproduct));
  aqty_prod = atoi(ReadLine(5 + (ID_prod * 6), fproduct));
  aplace_stck_prod = atoi(ReadLine(6 + (ID_prod * 6), fproduct));

  printf("\nQuel quantité voulez-vous acheter?\n");
  //scanf("%d", &aqty_achat);

  //while (aqty_achat > aqty_prod || aqty_achat < 1) {
  while(1){
    if(scanf("%d",&aqty_achat) != 1){
      printf("\nErreur,veuillez saisir un nombre:\n");
      while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
  }
    else if(aqty_achat < 1){
      printf("\nErreur, quantité trop petite, veuilez recommencer:\n");
      while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
    }

    else if(aqty_achat > aqty_prod){
      printf("\nErreur, quantité trop grande, veuilez recommencer:\n");
      while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
    }
    else{
      break;
    }
  }
  strcpy(nom_panier, email);
  strcat(nom_panier, "_panier.txt");
  panier = fopen(nom_panier, "a");
  fprintf(panier, "%d\n%s\n%d\n%s\n%d\n%d\n", aid_prod, anom_prod, aprice_prod,
          ataille_prod, aqty_achat, aplace_stck_prod);
  fclose(panier);

  printf("\n\tVoulez vous continuer vos achats:\n");
  couleur("32");
  printf("1.Oui\n");
  couleur("0");
  couleur("31");
  printf("2.Non\n");
  couleur("0");
  while (1) { 
        if (scanf("%d", &choix_ach) != 1 || (choix_ach != 1 && choix_ach != 2)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1 et 2
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1 ou 2 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
  if (choix_ach == 2) {
    EspaceClient();
  } else {
    Creapanier();
  }
}

// Avoir acces a lachat
void purchaseProduct() {
  int choix_ach;

  printf("\n\n\t================= ");
  couleur("34");
  printf("CY-SHOP ");
  couleur("0");
  printf("=================\n\n");
  printf("\t==========");
  couleur("33");
  printf("Bienvenue dans l'espace d'achat");
  couleur("0");
  printf("=============\n\n");

  printf("\n\t\tVoici nos produits\n");
  displayAllProduct();
  printf("\n\tVoulez vous faire un achat:\n");
  couleur("32");
  printf("1.Oui\n");
  couleur("0");
  couleur("31");
  printf("2.Non\n");
  couleur("0");
  while (1) {
        if (scanf("%d", &choix_ach) != 1 || (choix_ach != 1 && choix_ach != 2)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1 et 2
            printf("Erreur : saisie invalide. Veuillez entrer une valeur parmi 1 ou 2 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }

  if (choix_ach == 2) {
    EspaceClient();
  } else {
    Creapanier();
  }
}

// copier les produits du panier dans lhistorique
void finalachat() {
  char nom_panier[100];
  strcpy(nom_panier, email);
  strcat(nom_panier, "_panier.txt");
  FILE *fichier = fopen(nom_panier, "r");
  char buffer[100];
  FILE *historique;
  char nom_historique[100];
  strcpy(nom_historique, email);
  strcat(nom_historique, "_historique.txt");
  historique = fopen(nom_historique, "a");

  if (fichier == NULL) {
    printf("\nErreur,fichier inexistant\n");
    EspaceClient();
  }
  majProductachat();
  bool keep_reading = true;
  do {
    fgets(buffer, 100, fichier);
    if (feof(fichier)) {
      keep_reading = false;
    } else {
      fputs(buffer, historique);
    }
  } while (keep_reading);
  fclose(fichier);
  fclose(historique);
  remove(nom_panier);
  printf("\tAchat bien effectué\n");

  // Au revoir Cy-SHOP
  EspaceClient();
}

// afficher lhistorique
void openhistorique() {
  char nom_historique[50];
  strcpy(nom_historique, email);
  strcat(nom_historique, "_historique.txt");

  FILE *historique = fopen(nom_historique, "r");
  if (historique == NULL) {
    printf("Vous n'avez pas encore effectué d'achat\n");
    EspaceClient();
  }

  printf("\nID\tProduit\tPrix\tTaille\tQté\n");

  char id[30], nom[30], prix[30], taille[30], quantite[30], place[30];
  while (fscanf(historique, "%s %s %s %s %s %s", id, nom, prix, taille,
                quantite, place) == 6) {
    printf("%s\t%s\t%s\t\t\t%s\t%s\n", id, nom, prix, taille, quantite);
  }

  fclose(historique);
  EspaceClient();
}

// afficher le panier
void openpanier() {
  system("clear");
  int totalprixpanier;
  int choix_panier;
  int MAX_LENGTH = 100;
  char nom_panier[100];
  strcpy(nom_panier, email);
  strcat(nom_panier, "_panier.txt");
  FILE *fichier = fopen(nom_panier, "r");

  if (fichier == NULL) {
    printf("\nVotre Panier est vide\n");
    EspaceClient();
  }
  // Utiliser Malloc ??
  char id[MAX_LENGTH];
  char nom[MAX_LENGTH];
  char prix[MAX_LENGTH];
  char quantite[MAX_LENGTH];
  char Taille[MAX_LENGTH];
  char Place_stck[MAX_LENGTH];
  couleur("34");
  printf("Panier"); // Bienvenue Panier
  couleur("0");
  
  printf("\n\nID\tProduit\tPrix\tTaille\tQté\n");
  while (fscanf(fichier, "%s", id) == 1) {
    fscanf(fichier, " %[^\n]", nom);
    fscanf(fichier, "%s", prix);
    fscanf(fichier, "%s", Taille);
    fscanf(fichier, "%s", quantite);
    fscanf(fichier, "%s", Place_stck);
    printf("%s\t%s\t%s\t%s\t%s\n", id, nom, prix, Taille, quantite);
  }
  fclose(fichier);
  totalprixpanier = prixfinal();
  printf("\n\n\t\t\t\t\t\t\tTotal : %d €", totalprixpanier);
  printf("\n\tQue voulez-vous faire :");
  couleur("36");
  printf("\n1.Finaliser vos achats\n2.Retour\n");
  couleur("0");
  while (1) {
        if (scanf("%d", &choix_panier) != 1 || (choix_panier != 1 && choix_panier != 2)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1 et 2
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1 ou 2 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }

    
  

  if (choix_panier == 1) {
    finalachat();

  } else if (choix_panier == 2) {
    EspaceClient();
  }
}

// Se désinscrire
void seDesinscrire() {
  int choice;
  char panier_client[100];
  char historique_client[100];
  printf("\n\tVoulez-vous vraiment vous désinscrire:\n");
  couleur("32");
  printf("\n\t1.OUI");
  couleur("0");
  couleur("31");
  printf("\n2.NON\n");
  couleur("0");
  while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1 et 2
            printf("Erreur : saisie invalide. Veuillez entrer une valeur parmi 1 ou 2 : \n");
            while (getchar() != '\n');  //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
  switch (choice) {
  case 1:
    strcpy(panier_client, email);
    strcat(panier_client, "_panier.txt");
    strcpy(historique_client, panier_client);
    strcat(historique_client, "_historique.txt");

    remove(email);
    remove(panier_client);
    remove(historique_client);
    printf("\n\tVous vous êtes correctement désinscrit\n");
    exit(0);
    break;

  case 2:
    EspaceClient();
    break;
  }
}

// Prix final lors de l'achat
int prixfinal() {
  int prix_item;
  int qty_item;
  int prix_tot = 0;
  char nom_panier[100];
  strcpy(nom_panier, email);
  strcat(nom_panier, "_panier.txt");
  int count = 0;
  FILE *fichier = fopen(nom_panier, "r");

  char id[30], nom[30], prix[30], taille[30], quantite[30], place[30];
  while (fscanf(fichier, "%s %s %s %s %s %s", id, nom, prix, taille, quantite,
                place) == 6) {
    count++;
  }
  for (int i = 0; i < count; i++) {
    prix_item = atoi(ReadLine(3 + (6 * i), nom_panier));
    qty_item = atoi(ReadLine(5 + (6 * i), nom_panier));
    prix_tot = prix_tot + (qty_item * prix_item);
  }

  fclose(fichier);
  return prix_tot;
}

void EspaceClient() {
  int choice;
  printf("\n\n\t================= ");
  couleur("34");
  printf("CY-SHOP ");
  couleur("0");
  printf("=================\n\n");
  printf("\t========== ");
  couleur("33");
  printf("Bienvenue dans votre espace Client ");
  couleur("0");
  printf("=============\n\n");
  couleur("36");
  printf("1.Modifier vos informations Clients\n\n");
  printf("2.Voir nos Produits\n\n");
  printf("3.Votre Panier / Finaliser vos achats\n\n");
  printf("4.Votre Historique\n\n");
  printf("5.Se désinscrire\n\n");
  printf("0.Exit\n\n");
  couleur("0");

  printf("\n\n\t=================================================\n\n");
  printf("\nVeuillez entrer votre choix : ");
  while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 0)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2, 3, 4, 5 et 0
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1, 2, 3, 4, 5 ou 0 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
  switch (choice) {
  case 1:
    modifMesInfos();
    break;
  case 2:
    purchaseProduct();
    break;
  case 3:
    openpanier();
    break;
  case 4:
    openhistorique();
    break;
  case 5:
    seDesinscrire();
    break;
  case 0:
    DefaultScreen();
  default:
    GestionMode();
    break;
  }
}
void EspaceAdmin() {
  int choice;
  printf("\n\n\t================= ");
  couleur("34");
  printf("CY-SHOP ");
  couleur("0");
  printf("=================\n\n");
  printf("\t============== ");
  couleur("33");
  printf("MODE GESTION ");
  couleur("0");
  printf("=============\n\n");
  couleur("36");
  printf("1.Gérer les produits\n\n");
  printf("2.Gérer les Utilisateurs\n\n");
  printf("0.Exit\n\n");
  couleur("0");
  printf("\n\n\t==========================================\n\n");
  printf("\nVeuillez entrer votre choix:\n");
  while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 0)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2 et 0
            printf("Erreur : saisie invalide. Veuillez entrer une valeur parmi 1, 2 ou 0 : \n");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }
  switch (choice) {
  case 1:
    manageProduct();
    break;
  case 2:
    manageUsers();
    break;
  case 0:
    DefaultScreen();
  default:
    printf("Erreur");
    break;
  }
}
// Interface gestion
void GestionMode() {
  int ch;
  int logres = login();
  if (logres == 3) {
    signup();
  } else if (logres == 2) {
    // faire un while login() == 2 pour admin -> Manage + Voir les clients +
    // leurs infos.

    EspaceAdmin();
  } else if (logres == 1) {
    EspaceClient();
  }
}

// Main
int DefaultScreen() {
  system("clear");
  int choice;
  printf("\n\n\t================= ");
  couleur("34");
  printf("Bienvenue dans CY-SHOP ");
  couleur("0");
  printf("=================\n");
  printf("\t================ ");
  couleur("33");
  printf("La Mode à portée de main ");
  couleur("0");
  printf("=================\n\n");
  couleur("36");
  printf("\n\n1.Inscription");
  printf("\n2.Connexion");
  printf("\n3.Quitter");
  couleur("0");

  // Asking for choice
  printf("\n\n\nEntrez votre choix : ");
  while (1) {
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3)) { //s'effectue si l'entrée n'est pas un entier ou n'est pas égale à 1, 2 et 3
            printf("Saisie invalide. Veuillez entrer une valeur parmi 1, 2 ou 3 : ");
            while (getchar() != '\n'); //vide le tampon d'entrée jusqu'à trouver un caractère de fin de ligne
        } else {
            break;
        }
    }

    
  switch (choice) {
  case 1: {
    signup();
    break;
  }
  case 2: {

    GestionMode();
    break;
  }
  case 3: {

    printf("\n\n\t============ ");
    couleur("34");
    printf("Merci de votre visite ");
    couleur("0");
    printf("============\n\n");
    exit(0);
  }
  default: {

    printf("\n\nEntrez un choix valide!!\n");
    break;
  }
  }
}

int main() {

  while (1) {

    DefaultScreen();
  }

  return 0;
}
