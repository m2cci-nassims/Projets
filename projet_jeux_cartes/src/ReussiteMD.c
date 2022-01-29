


/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Programme principal */

#include "MD.h"
#include "InteractionMD.h"
#include "Alea.h"
#include <stdio.h>

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
  int nbparties = 0;

  InitAlea();
 
  printf (TexteBienvenue) ;
  SaisirCommande (&Commande) ;
  while (Commande != FIN) {
    switch  (Commande) {
    case SIMULMD : 
      while (nbparties <= 0)
      {
        printf(TexteNbASimuler);
        scanf("%d",&nbparties);
      }
      OuvrirGraphique("MD");
      ObserverMD(nbparties);
      FermerGraphique();
      break ;

   case ANALYSEMD :
      
      
        printf(TexteNbAAnalyser);
        scanf("%d",&nbparties);
      AnalyserMD(nbparties);
  
      
        
      
      break;

    default:
      break;
    } 
    SaisirCommande (&Commande) ;
    
  } 
  printf (TexteAuRevoir) ;

  return 0;
}
	
