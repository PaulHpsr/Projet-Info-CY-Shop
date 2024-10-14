# Projet CY_Shop | Application de Gestion de Stock et de Clients

Programme développé en langage C permettant de gérer les stocks et les données clients d'une boutique en ligne, avec la possibilité de naviguer à travers les produits et d'effectuer des achats. Le programme propose un mode "Gestion" pour les administrateurs et un mode "Client" pour les utilisateurs, chacun offrant des fonctionnalités spécifiques.

## Fonctionnalités Clés

### Gestion de l'Inventaire
- **Gestion des Produits** : Ajouter, afficher et modifier les informations des produits (nom, prix, taille, quantité).
- **Gestion des Clients** : Consulter et mettre à jour les informations des clients, y compris le nom, l'âge, le panier d'achat et l'historique des achats.

### Mode Client
- **Inscription et Connexion** : Les utilisateurs peuvent s'inscrire et se connecter avec leurs identifiants.
- **Navigation dans la Boutique** : Parcourir les produits disponibles, consulter le panier, finaliser les achats et accéder à l'historique des achats.
- **Gestion du Profil** : Mettre à jour les informations personnelles ou se désinscrire du système.

### Mode Gestion
- **Accès Administrateur** : Accessible avec les identifiants suivants :
  - **Email** : `admin@gmail.com`
  - **Mot de Passe** : `a`
- Permet de gérer les produits et les données des clients de manière avancée.

## Installation du Projet

### Prérequis
Assurez-vous que les fichiers suivants sont présents pour que le programme fonctionne correctement :
- `main.c`
- `couleurs.h`
- `ReadSpecificLine.h`
- `stockmax.txt`
- `Makefile`

### Compilation et Exécution
- **Compiler** : Utilisez la commande `make` dans le terminal (sous Linux).
- **Exécuter le Programme** : Lancez le programme avec `./CY_SHOP_main`.

## Limitations
Le programme ne permet pas la suppression directe d'un produit via l'interface. Si un produit est supprimé manuellement depuis les fichiers `.txt` (`prodid.txt`, `product.txt`, `stockmax.txt`), certaines fonctionnalités pourraient ne plus fonctionner correctement.

## Développement

### Outils Utilisés
- **Éditeurs de Code** : Replit, Atom
- **Langage** : C

## Auteurs
Développé par les étudiants de **CY-Tech | MI2** :
- **Paul HOPSORE**
- **Corentin PELLERIN**
- **Athalin LE CALVEZ**
