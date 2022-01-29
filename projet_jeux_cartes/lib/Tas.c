/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              
   --> types enumeres : Couleur, Rang
   --> tas representes par des listes chainees
----------------------------------------------------------------*/

#include "Tas.h"
#include "Alea.h"

/*-----------------------------------*/
/* Specifications des objets de base */
/*-----------------------------------*/

/* Couleurs et rangs */

/* Couleurs */
/* Ordre croissant sur les couleurs: trefle, carreau, coeur, pique */

Couleur CouleurSuivante(Couleur C) {
  return ((C < DerniereCouleur) ? C+1 : PremiereCouleur);
}

/* Rangs */
/* Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as */

Rang RangSuivant(Rang R) {
  return ((R < DernierRang) ? R+1 : PremierRang);
}

/*--------------------------------------------------------------------*/
/* Representation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Representation des cartes */

	/* Testeurs et selecteurs */
	
Rang LeRang(Carte C) {
  return C.RC;
}

Couleur LaCouleur(Carte C) {
  return C.CC;
}

Visibilite EstCachee(Carte C) {
  return !C.VC;
}

Visibilite EstDecouverte(Carte C) {
  return C.VC;
}

	/* Comparaison de cartes */
	
booleen RangInferieur(Carte C1, Carte C2) {
  return LeRang(C1) < LeRang(C2);
}

booleen MemeRang(Carte C1, Carte C2) {
  return LeRang(C1) == LeRang(C2);
}

booleen CouleurInferieure(Carte C1, Carte C2) {
  return LaCouleur(C1) < LaCouleur(C2);
}

booleen MemeCouleur(Carte C1, Carte C2) {
  return LaCouleur(C1) == LaCouleur(C2);
}

booleen EstCarteAvant(Carte C1, Carte C2) {
  return (CouleurInferieure(C1, C2) || 
	  (MemeCouleur(C1, C2) && RangInferieur(C1, C2)));
}

/* Representation des tas */
	
	/* Testeurs et selecteurs */
	
booleen TasActif(Tas T) {
  return (T.RT == actif);
}

booleen TasVide(Tas T) {
  return (T.HT == 0);
}

booleen TasEmpile(Tas T) {
  return (T.MT == empile);
}

booleen TasEtale(Tas T) {
  return (T.MT == etale);
}

int LaHauteur(Tas T) {
  return T.HT;
}

Localisation LaPlace(Tas T) {
  return T.LT;
}

	/* Constructeurs */
	
/* *************************************************************
void CreerTasVide(Localisation L, Mode M, Tas *T)
associe a T un tas vide actif place en L et de mode d'etalement M.
Pre-condition : l'emplacement L est disponible
**************************************************************** */
void CreerTasVide(Localisation L, Mode M, Tas *T) {
  ((*T).LT).NL = L.NL;
  ((*T).LT).NC = L.NC;
  (*T).RT = actif;
  (*T).MT = M;
  (*T).HT = 0;
  (*T).tete = NULL;
  (*T).queue = NULL;
}

/* *************************************************************
void SupprimerTasVide(Tas *T)
rend le tas vide inactif. En particulier, la place qu'il occupait
devient libre pour un autre tas.
Pre-condition : le tas T est vide et actif
**************************************************************** */
void SupprimerTasVide(Tas *T) {
  (*T).RT = inactif;
}

/* *************************************************************
void CreerJeuNeuf(int N, Localisation L, Tas *T)
forme en L le tas empile T avec l'ensemble des N cartes du jeu dans
l'ordre des cartes et faces cachees.
Donne leur valeur aux variables globales NbCartes et PremierRang.
Pre-condition : l'emplacement L est libre
                N==52 ou N==32
**************************************************************** */
void CreerJeuNeuf(int N, Localisation L, Tas *T) {
  Couleur Co;
  Rang R;
  struct adCarte *adcour;
  struct adCarte *adprec;

  NbCartes = N;
  PremierRang = (N == 52) ? Deux : Sept;

  ((*T).LT).NL = L.NL;
  ((*T).LT).NC = L.NC;
  (*T).RT = actif;
  (*T).MT = empile;
  (*T).HT = NbCartes;

  /* creer la premiere carte de la liste */
  adcour = (struct adCarte *) malloc (sizeof(struct adCarte));
  (*T).tete = adcour;
  (*adcour).prec = NULL;
  for (Co = PremiereCouleur; Co <= DerniereCouleur; Co++)
    for (R = PremierRang; R <= DernierRang; R++) {
      (*adcour).elt.CC = Co;
      (*adcour).elt.RC = R;
      (*adcour).elt.VC = Cachee;
      adprec = adcour;
      adcour = (struct adCarte *) malloc (sizeof(struct adCarte));
      (*adprec).suiv = adcour;
      (*adcour).prec = adprec;
   }
   (*adprec).suiv = NULL;
   (*T).queue = adprec;
   free(adcour);
}

	/* Consultation des cartes d'un tas: ne deplace pas la carte */
	
/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T) {
  return (*(T.queue)).elt; 
}

/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T)
{
  return (*(T.tete)).elt;
}

/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Pre-condition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i) {
int j;
struct adCarte *cour;
  cour = T.tete;
  j = 1;
  while (j<i) {
    cour = (*cour).suiv;
    j++;
  };
  return (*cour).elt;
}

	/* Retournement d'une carte sur un tas */
	
/* *************************************************************
void RetournerCarteSur(Tas *T)
retourne la carte situee au dessus du tas T.
Pre-condition : T non vide
**************************************************************** */
void RetournerCarteSur(Tas *T) {
struct adCarte *cour;
  cour = (*T).queue;
  (*cour).elt.VC = ! ((*cour).elt.VC); 
}

/* *************************************************************
void RetournerCarteSous(Tas *T)
retourne la carte situee au dessous du tas T.
Pre-condition : T non vide
**************************************************************** */
void RetournerCarteSous(Tas *T) {
struct adCarte *cour;
  cour = (*T).tete;
   (*cour).elt.VC = ! ((*cour).elt.VC);
}

/* *************************************************************
void RetournerIeme(Tas *T, int i)
retourne la ieme carte du tas T.
Pre-condition : T non vide, i <= LaHauteur(T)
**************************************************************** */
void RetournerIeme(Tas *T, int i)
{
  int j;
  struct adCarte *cour;
  cour = (*T).tete;
  j = 1;
  while (j<i) {
    cour = (*cour).suiv;
    j++;
  };
  (*cour).elt.VC = ! (*cour).elt.VC;
}

	/* Modification d'un tas */

/* *************************************************************
void EmpilerTas(Tas *T)
void EtalerTas(Tas *T)
modification du mode d'etalement d'un tas
**************************************************************** */
void EmpilerTas(Tas *T) {
  (*T).MT = empile;
}

void EtalerTas(Tas *T) {
  (*T).MT = etale;
}

	
/* *************************************************************
void EchangerCartes(int i, int j, Tas *T)
echange les cartes i et j du tas T
Precondition : les deux cartes existent i,j <= LaHauteur(T)
**************************************************************** */
void EchangerCartes(int i, int j, Tas *T) {
int k;
struct adCarte *cour;
struct adCarte *ci;
struct adCarte *cj;
Carte temp;
  cour = (*T).tete;
  if (j<i) { k=i;i=j;j=k; };
  k = 1;
  while (k<i) {
    cour = cour->suiv; k++;
  };
  ci = cour;
  while (k<j) {
    cour = cour->suiv; k++;
  };
  cj = cour;
  temp = (*ci).elt;
  (*ci).elt.CC = (*cj).elt.CC;
  (*ci).elt.RC = (*cj).elt.RC;
  (*ci).elt.VC = (*cj).elt.VC;
  (*cj).elt.CC = temp.CC;
  (*cj).elt.RC = temp.RC;
  (*cj).elt.VC = temp.VC;
  
}

/* *************************************************************
void BattreTas(Tas *T)
bas le tas T
**************************************************************** */
void BattreTas(Tas *T) {
  int i;
  for (i = (*T).HT; i >=2; i--)
    EchangerCartes(i, UnEntier(i), T);
}

/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T) {
struct adCarte *cour;
struct adCarte *temp;
int i;

  cour = (*T).tete;
  for (i=1; i<=LaHauteur(*T); i++) {
     (*cour).elt.VC = ! (*cour).elt.VC;
     temp = (*cour).suiv;
     (*cour).suiv = (*cour).prec;
     (*cour).prec = temp;
     cour = temp;
  };
  temp = (*T).tete;
  (*T).tete = (*T).queue;
  (*T).queue = temp;
 
}

	/* Deplacements de cartes d'un tas sur un autre */


/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (struct adCarte *ac, Tas *T) {
   if ( (*T).HT == 0 ) { /* le tas T est vide */
      (*ac).suiv = NULL;
      (*ac).prec = NULL;
      (*T).tete = ac;
      (*T).queue = ac;
   }
   else { /* ajout en queue */
      (* ((*T).queue)).suiv = ac;
      (*ac).prec = (*T).queue;
      (*T).queue = ac;
   };
   (*T).HT = (*T).HT + 1;
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (struct adCarte *ac, Tas *T) {
   if ( (*T).HT == 0 ) { /* le tas T est vide */
      (*ac).suiv = NULL;
      (*ac).prec = NULL;
      (*T).tete = ac;
      (*T).queue = ac;
   }
   else { /* ajout en tete */
      (*ac).suiv = (*T).tete;
      (* ((*T).tete)).prec = ac;
      (*T).tete = ac;
   };
   (*T).HT = (*T).HT + 1;
}

/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enleve la carte situee au dessus de T1 et la place au dessus de T2
Pre-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2) {
struct adCarte *ac;
struct adCarte *acprec;
   ac = (*T1).queue;
   if ( (*T1).HT == 1 ) {   /* T1 a un seul element, il va devenir vide */
      (*T1).tete = NULL;
      (*T1).queue = NULL;
   } else {     /* enlever la derniere carte de T1 */
      acprec = (*ac).prec;
      (*T1).queue = acprec;
      (*acprec).suiv = NULL;
   };
   AjouterCarteSurTas (ac, T2);
   (*T1).HT = (*T1).HT - 1;
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enleve la carte situee au dessus de T1 et la place au dessous de T2.
Pre-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2) {
struct adCarte *ac;
struct adCarte *acprec;
   ac = (*T1).queue;
   if ( (*T1).HT == 1 ) {   /* T1 a un seul element, il va devenir vide */
      (*T1).tete = NULL;
      (*T1).queue = NULL;
   } else {     /* enlever la derniere carte de T1 */
      acprec = (*ac).prec;
      (*T1).queue = acprec;
      (*acprec).suiv = NULL;
   };
   AjouterCarteSousTas (ac, T2);
   (*T1).HT = (*T1).HT - 1;
}

/* ******************************************************************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enleve la carte situee au dessous de T1 et la place au dessus de T2.
Pre-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2) {
struct adCarte *ac;
struct adCarte *acsuiv;
   ac = (*T1).tete;
   if ( (*T1).HT == 1 ) {   /* T1 a un seul element, il va devenir vide */
      (*T1).tete = NULL;
      (*T1).queue = NULL;
   } else {     /* enlever la premiere carte de T1 */
      acsuiv = (*ac).suiv;
      (*T1).tete = acsuiv;
      (*acsuiv).prec = NULL;
      (*T1).queue = NULL;
   };
   AjouterCarteSurTas (ac, T2);
   (*T1).HT = (*T1).HT - 1;
}

/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enleve la carte situee au dessous de T1 et la place au dessous de T2.
Pre-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2) {
struct adCarte *ac;
struct adCarte *acsuiv;
   ac = (*T1).tete;
   if ( (*T1).HT == 1 ) {   /* T1 a un seul element, il va devenir vide */
      (*T1).tete = NULL;
      (*T1).queue = NULL;
   } else {     /* enlever la premiere carte de T1 */
      acsuiv =  (*ac).suiv;
      (*T1).tete = acsuiv;
      (*acsuiv).prec = NULL;
   };
   AjouterCarteSousTas (ac, T2);
   (*T1).HT = (*T1).HT - 1;
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enleve du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pre-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2) {
struct adCarte *cour1;
struct adCarte *prec1;
struct adCarte *suiv1;

  prec1 = NULL; cour1 = (*T1).tete;
  while ((LaCouleur((*cour1).elt) != C) || (LeRang((*cour1).elt) != R)) {
     prec1 = cour1; cour1 = (*cour1).suiv;
  };
  suiv1 = (*cour1).suiv;
  if ( (*T1).HT == 1 ) { /* T1 a un seul element, il devient vide */
     (*T1).tete = NULL;
     (*T1).queue = NULL;
  } else if (prec1==NULL) {  /* la carte est la premiere de T1 */
     (*T1).tete = suiv1;
     (*suiv1).prec = NULL;
  } else if (suiv1==NULL) { /* la carte etait la derniere de T1 */
     (*T1).queue = prec1;
     (*prec1).suiv = suiv1;
  } else {
     (*prec1).suiv = suiv1;
     (*suiv1).prec = prec1;
  };
  (*T1).HT = (*T1).HT - 1;
  AjouterCarteSurTas (cour1, T2);
}

/* ******************************************************************************
void PoserTasSurTas(Tas *T1, Tas *T2)
pose le tas T1 sur le tas T2.
Les deux tas doivent avoir le meme mode d'etalement.
A l'etat final, le tas T1 est vide mais toujours actif, et le tas T2 comporte (de bas en
haut) toutes les cartes qu'il avait au depart puis toutes les cartes de T1 dans l'ordre
qu'elles avaient au depart dans chacun des tas.
Cette operation ne modifie ni la visibilite des cartes, ni la localisation des tas T1 et T2,
ni leur mode d'etalement.
********************************************************************************* */
void PoserTasSurTas(Tas *T1, Tas *T2) {
  int i, h;

  h = LaHauteur(*T1);
  for (i = 1; i <= h; i++)
       DeplacerBasSur(T1, T2);
}


