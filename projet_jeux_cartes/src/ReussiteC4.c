/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>

/* Programme principal */

#include "C4.h"
#include "InteractionC4.h"
#include "Alea.h"

/* -------------------------------------------------------------------
 *      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
 * -------------------------------------------------------------------
 */
#define         TexteBienvenue           "Bienvenue \n" 
#define         TexteNbASimuler          "Choisissez le nombre de parties a simuler : "
#define         TexteNbAAnalyser         "Choisissez le nombre de parties a analyser : "
#define         TexteAuRevoir            "Au revoir \n" 

int main(void)
{

  CodeCommande    Commande ;
  int nbparties ;

  InitAlea();
 
  printf (TexteBienvenue) ;
  SaisirCommande (&Commande) ;
  while (Commande != FIN) {
    switch  (Commande) {
    case SIMUL : 
      printf(TexteNbASimuler);
      scanf("%d",&nbparties);
      OuvrirGraphique("C4");
      ObserverC4(nbparties);
      FermerGraphique();
      break ;

    case ANALYSE :
      printf(TexteNbAAnalyser);
      scanf("%d",&nbparties);
      AnalyserC4(nbparties);
      break;
    } 
    SaisirCommande (&Commande) ;
    
  } 
  printf (TexteAuRevoir) ;
}
	
