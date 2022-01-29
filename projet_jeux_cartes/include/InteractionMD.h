/*--------------------------------------------------------------*/
/* Reussites.
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/


/* Interaction avec l'utilisateur */

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULMD, ANALYSEMD, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMULMD, ANALYSEMD, FIN}     CodeCommande ;

void SaisirCommande (CodeCommande *);
