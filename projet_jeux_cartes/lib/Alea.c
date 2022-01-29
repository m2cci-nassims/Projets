/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Generateur aleatoire */

#include <stdlib.h>
#include <time.h>

void InitAlea()
{
  int g;
  time_t t;

  g = (unsigned int) time(&t);
  srand(g);
}

int UnEntier(int n)
{
  /* tirage aleatoire d'un entier entre 1 et n */
  
  return rand()%n + 1;
}


