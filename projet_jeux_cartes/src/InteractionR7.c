/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include "InteractionR7.h"

/* Interaction avec l'utilisateur */

/* ----------------------------------------------------------
 * CONSTANTES 
 * ----------------------------------------------------------
*/

#define         NbMaxEssais              5 
#define         Invite                   "Votre Choix (? pour liste des commandes) : " 
#define         TexteSimulationR7        '1' 
#define         TexteAnalyseR7           '2' 
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
    ((c == TexteSimulationR7) ||
     (c == TexteAnalyseR7) ||
     (c == TexteFin)) ;
}

void EcrireMenu ()
{
  printf ("Tapez \n") ; 
  printf ("%c pour Simulation graphique de la reussite R7, \n",TexteSimulationR7) ; 
  printf (" %c pour Analyse d une serie de reussites R7 (sans affichage graphique), \n",TexteAnalyseR7);
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
    case TexteSimulationR7 : *CC = SIMULR7 ; break ;
    case TexteAnalyseR7 :    *CC = ANALYSER7 ; break ;
    case TexteFin :          *CC = FIN ; break ;
    } 
} 
