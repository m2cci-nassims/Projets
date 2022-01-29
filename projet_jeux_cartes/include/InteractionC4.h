/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/


/* Interaction avec l'utilisateur */

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMUL, ANALYSE, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMUL, ANALYSE, FIN}     CodeCommande ;

void SaisirCommande (CodeCommande *);
