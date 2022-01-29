/*--------------------------------------------------------------*/
/* Reussites.
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/


/* Interaction avec l'utilisateur */

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULR7, ANALYSER7, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMULR7, ANALYSER7, FIN}     CodeCommande ;

void SaisirCommande (CodeCommande *);
