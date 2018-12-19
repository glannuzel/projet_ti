# projet_ti

Module Outils d'imagerie pour la robotique

**Membres de l'équipe :**
* Gaëlle Lannuzel
* Vincent Leconte
* Yoann Menanteau
* Effie Segas

## Compiler les programmes
Utiliser la commande make
## Exécuter les traitements

### Algorithme 1
Ce pipeline prend une image en entrée et retourne le masque de du terrain en utilisant l'algorithme 1 (distance de mahalanobis)

COMMANDE : make algo1 DATA="nom_image_a_traiter.png" DESTINATION="nom_enregistrement_image_traitee.png"

NECESSAIRE : l'image 001 du dossier log1 qui sera situé dans ../data (../data/log1/001-rgb.png)

Arguments :
DATA : image à traiter
DESTINATION : chemin d'enregistrement de l'image traitee

### Algorithme 2
Ce pipeline prend une image en entrée et retourne le masque du terrain en utilisant l'algorithme 2

COMMANDE : make algo2 DATA="nom_image_a_traiter.png" DESTINATION="nom_enregistrement_image_traitee.png" TAILLEMASQUE=0

Arguments :
DATA : image à traiter
DESTINATION : chemin d'enregistrement de l'image traitee
TAILLEMASQUE : augmente la taille du masque de dilatation une fois le masque du terrain obtenu pour assurer un recouvrement du terrain (défini à 0 de base, plus il est grand plus le rappel sera élevé mais la précision faible)

## Exécuter les tests

### Tests algorithme 1

Ce pipeline permet d'obtenir les résultats quantitatifs de l'algorithme 1 à partir des 24 vérités terrain présentes dans le dossier images_vt.

COMMANDE : make test_algo1 MULTIPLE=1

NECESSAIRE : 
Le dossier images_vt avec les 24 images vérité terrain à l'intérieur
Le dossier data avec les dossiers log 1 - log 2 - log 3 - log 4 et les 24 images correspondant aux vérités terrain du dossier images_vt (../data/log1/XXX.png)

Arguments :
MULTIPLE : si 1 > affiche les résultats quantitatifs pour chaque image ainsi que les résultats globaux à la fin
           si 0 > affiche uniquement les résultats globaux
           

### Tests algorithme 2

Ce pipeline permet d'obtenir les résultats quantitatifs de l'algorithme 2 à partir des 24 vérités terrain présentes dans le dossier images_vt.

COMMANDE : make test_algo2 MULTIPLE=1

NECESSAIRE : 
Le dossier images_vt avec les 24 images vérité terrain à l'intérieur
Le dossier data avec les dossiers log 1 - log 2 - log 3 - log 4 et les 24 images correspondant aux vérités terrain du dossier images_vt (../data/log1/XXX.png)

Arguments :
MULTIPLE : si 1 > affiche les résultats quantitatifs pour chaque image ainsi que les résultats globaux à la fin
           si 0 > affiche uniquement les résultats globaux

