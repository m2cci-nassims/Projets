/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include "InteractionMD.h"

/* Interaction avec l'utilisateur */

/* ----------------------------------------------------------
 * CONSTANTES 
 * ----------------------------------------------------------
*/

#define         NbMaxEssais              3 
#define         Invite                   "Votre Choix (? pour liste des commandes) : " 
#define         TexteSimulationMD        '1' 
#define         TexteAnalyseMD           '2' 
#define         TexteFin                 'F' 
#define         TexteAide                '?' 

/* -------------------------------------------------------------------
 *      INTERACTION
 *
 *      EstTexteCommande : fonction (c : caractere) ---> booleen
 *      EcrireMenu       : action
 *      SaisirCommande   : action (resultat CC : CodeCommande)
 * -------------------------------------------------------------------
*/

void	LireCar (char	*c)
{	int l ;
	while (isspace ( l=getchar ()))
	;
  	*c = l ;
}

int EstTexteCommande (char c)
{
  return
    ((c == TexteSimulationMD) ||
     (c == TexteAnalyseMD) ||
     (c == TexteFin)) ;
}

void EcrireMenu ()
{
  printf ("Tapez \n") ; 
  printf ("%c pour Simulation graphique de la reussite MD, \n",TexteSimulationMD) ; 
  printf (" %c pour Analyse d une serie de reussites MD (sans affichage graphique), \n",TexteAnalyseMD);
  printf (" %c pour Fin, \n",TexteFin);
  printf (" %c pour Aide.\n",TexteAide); 
}

void SaisirCommande (CodeCommande *CC) 
{
  char C  ;
  int  NbEssais ;

  printf (Invite) ; LireCar (&C) ;
  NbEssais = 0 ;
  while ((NbEssais < NbMaxEssais) && (! EstTexteCommande (C))) 
    {
      if (C == TexteAide) 
	{
	  EcrireMenu ()  ; 
	  LireCar (&C) ;
	}
      else 
	{
	  printf ("Commande incorrecte.");
	  NbEssais++ ;
	  if (NbEssais < NbMaxEssais)
	    {
	      printf (Invite) ; 
	      LireCar (&C) ;
	    } 
	}
    } 
  if (NbEssais == NbMaxEssais) 
    *CC = FIN  ;
  else switch (C)  
    {
    case TexteSimulationMD : *CC = SIMULMD ; break ;
    case TexteAnalyseMD :    *CC = ANALYSEMD ; break ;
    case TexteFin :          *CC = FIN ; break ;
    } 
} 
