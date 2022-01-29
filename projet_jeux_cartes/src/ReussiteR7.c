/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Programme principal */

#include "R7.h"
#include "InteractionR7.h"
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
  const unsigned int NBMAXT = 4;

  CodeCommande    Commande ;
  int nbparties = 0;

  InitAlea();
 
  printf (TexteBienvenue) ;
  SaisirCommande (&Commande) ;
  while (Commande != FIN) {
    switch  (Commande) {
    case SIMULR7 : 
      while (nbparties <= 0)
      {
        printf(TexteNbASimuler);
        scanf("%d",&nbparties);
      }
      OuvrirGraphique("R7");
      ObserverR7(nbparties, NBMAXT);
      FermerGraphique();
      break ;

    case ANALYSER7 :
      
      
        printf(TexteNbAAnalyser);
        scanf("%d",&nbparties);
      
      AnalyserR7(nbparties,NBMAXT);
      
        
      
      break;

    default:
      break;
    } 
    SaisirCommande (&Commande) ;
    
  } 
  printf (TexteAuRevoir) ;

  return 0;
}
	
