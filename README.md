# Projet-Info-CY-Shop | Projet d'informatique PreIng1 CY_Shop_v1 MI2-5

## Programme codé en language C, qui permet la gestion de stocks, des données clients. Mais aussi l'achat de produit.

## Pré-requis 

Il est nécessaire d'avoir ces fichiers afin que le programme fonctionne correctement :
- main.c
- couleurs.h
- ReadSpecificLine.h
- stockmax.txt
- Makefile

## Codé avec 

- Replit 
- Atom

## Description

Ce projet permet de gérer un magasin virtuel et permet aux utilisateurs de naviguer à travers les produits mais aussi d'effectuer des achats.
Le programme stock et permet la modification les données produits et clients, suit l'évolution de la place disponible dans les stocks du magasin.

## Utilisation

Le programme permet à l'utilisateur d'accéder soit au mode "Gestion" soit au mode "Client" en fonction de la manière dont celui-ci se connecte
### Mode Gestion : 
L'utilisateur doit se connecter avec les logs suivant : - email : admin@gmail.com
                                                        - mdp : a
                                                     
 Le mode gestion permet : 
 - Gérer les produits
    - Ajouter un produit
    - Afficher la liste des produits
    - Modifier les informations d'un produit (nom, prix, taille, qté)
 - Gérer les clients
    - Modifier une informations d'un Client (nom, prenom, age)
    - Afficher la liste des clients inscrits (+leurs panier et historique)

### Mode Client :

L'utilisateur doit d'abord s'inscrire puis se connecter avec les logs qu'il à utilisé pour s'inscrire.

Le mode client permet :
- Modifier vos informations Clients
- Voir les Produits Disponibles
- Voir Votre Panier / Finaliser vos achats
- Voir Votre Historique
- Se désinscrire

### Compiler le programme :
(Sous linux)
Afin d'utiliser le programme vous devez d'abord le compiler avec la commande :
<code>make</code>   (dans le terminal)

### Exécuter le programme :
Afin d'éxécuter le programme vous devez utiliser la commande :
./CY_SHOP_main

## Limitations fonctionnelles

Nous n'avons pas mis à disposition un moyen de supprimer un produit de la liste à l'aide du programme, ainsi si vous supprimez manuellement le produit directement depuis le fichier .txt certaines fonctionnalitées du projet ne fonctionneront pas. (cela est valables pour les fichier : prodid.txt , product.txt et stockmax.txt)

## Auteurs
CY-Tech | MI2
- Paul HOPSORE
- Corentin PELLERIN
- Athalin LE CALVEZ
