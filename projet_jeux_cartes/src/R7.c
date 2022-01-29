/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Le relais des 7 */

#include <stdio.h>

#include "R7.h"

char TexteCouleurR7[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

/* Tableau de jeu */

int NumTourR7;
typedef Tas SerieCouleurR7;
SerieCouleurR7 LigneR7[DerniereCouleur+1];
Tas TalonR7, RebutR7;
	/* localisation des tas */
Localisation LocSeriesR7[DerniereCouleur+1];
Localisation LocTalonR7, LocRebutR7;

/* Formation du tableau de jeu initial */

void SaisirLocTasR7()
{
  int i;

  LocTalonR7.NC = 1;
  LocTalonR7.NL = 1;
  LocRebutR7.NC = 1;
  LocRebutR7.NL = 3;

  for (i=PremiereCouleur; i<=DerniereCouleur; i++)
    {
      LocSeriesR7[i].NC = 2*i+2;
      LocSeriesR7[i].NL = 1;
    }
}

void CreerTableauInitialR7()
{
  Couleur Co;

  SaisirLocTasR7();
  NumTourR7 = 1;

  /* Cr�ation du talon avec un jeu de 52 cartes et du rebut avec un tas vide */
  CreerJeuNeuf(52, LocTalonR7, &TalonR7);
  BattreTas(&TalonR7);
  CreerTasVide(LocRebutR7, empile, &RebutR7);

  /* Cr�ation des s�ries de chaque couleur et initialisation avec le sept */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      CreerTasVide(LocSeriesR7[Co], etale, &(LigneR7[Co]));
      DeplacerCarteSur(Co, Sept, &TalonR7, &(LigneR7[Co]));
      RetournerCarteSur(&(LigneR7[Co]));
    }
}

void ReformerTableauInitialR7()
{
  Couleur Co;

  /* On reforme le talon, en empilant les cartes du rebut et de la ligne */
  PoserTasSurTas(&RebutR7, &TalonR7);
  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      EmpilerTas(&(LigneR7[Co]));
      PoserTasSurTas(&(LigneR7[Co]), &TalonR7);
      EtalerTas(&(LigneR7[Co])); 
    }
  RetournerTas(&TalonR7);
  BattreTas(&TalonR7);

  NumTourR7 = 1;

  /* Initialisation des series de chaque couleur avec le sept */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      DeplacerCarteSur(Co, Sept, &TalonR7, &(LigneR7[Co]));
      RetournerCarteSur(&(LigneR7[Co]));
    }
}

/* Visualisation des etats du jeu */

void AfficherR7()
{
  Couleur Co;

  EffacerGraphique();
  AfficherTas(TalonR7, "Talon");
  AfficherTas(RebutR7, "Rebut");

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    AfficherTas(LigneR7[Co], TexteCouleurR7[Co]);

  MettreAJourGraphique();
  AttendreCliquer();
}

/* Jouer le relais des 7 */

void JouerTasR7(Tas *T, booleen *OK)
{
  Couleur Co;
  Rang RT, RSous, RSur;

  Co = LaCouleur(CarteSur(*T));
  RT = LeRang(CarteSur(*T));
  RSous = LeRang(CarteSous(LigneR7[Co]));
  RSur = LeRang(CarteSur(LigneR7[Co]));

  *OK = vrai;
  if (RT == RangSuivant(RSur))
    DeplacerHautSur(T, &(LigneR7[Co]));
  else if (RSous == RangSuivant(RT))
    DeplacerHautSous(T, &(LigneR7[Co]));
  else 
    *OK = faux;
}

void JouerUnTourR7(ModeTrace MT)
{
  booleen OK;
  
  if (MT == AvecTrace)
    AfficherR7();
  do	/* Jeu du talon, puis eventuellement du rebut */ {
      /* On sait qu'on ne peut pas jouer le rebut et que le talon n'est pas vide */
      /* Jouer le talon */
      RetournerCarteSur(&TalonR7);
      JouerTasR7(&TalonR7, &OK);
      if (!OK)
	      DeplacerHautSur(&TalonR7, &RebutR7);
      if (MT == AvecTrace)
	      AfficherR7();
      while (OK && !TasVide(RebutR7))	{
	      /* On a joue le talon ou le rebut. Le rebut n'est pas vide: on joue le rebut */
	      JouerTasR7(&RebutR7, &OK);
	      if (OK && (MT == AvecTrace))
	         AfficherR7();
	   }
  }
  while (!TasVide(TalonR7));
}

void JouerUneR7(int NMaxT, ModeTrace MT)
{
  JouerUnTourR7(MT);
  /* Jeu d'au plus NMaxT tours */

  while (!(TasVide(RebutR7)) && (NumTourR7 < NMaxT))  
    {
      RetournerTas(&RebutR7);
      PoserTasSurTas(&RebutR7, &TalonR7);
      JouerUnTourR7(MT);
      NumTourR7 = NumTourR7 + 1;
    }
  if (TasVide(RebutR7))
    {
      printf("Vous avez gagne en %d tours !\n",NumTourR7);
    }
  else
    {
      printf("Vous avez perdu !\n");
    }
}
		
void ObserverR7(int NP, int NMaxT)
{
  int i;

  CreerTableauInitialR7();
  JouerUneR7(NMaxT, AvecTrace);
  for (i = 1; i <= NP-1; i++)
    {
      ReformerTableauInitialR7();
      JouerUneR7(NMaxT, AvecTrace);
    }
}

int JouerUneR7An(int NMaxT, ModeTrace MT)
{
  JouerUnTourR7(MT);
  /* Jeu d'au plus NMaxT tours */

  while (!(TasVide(RebutR7)) && (NumTourR7 < NMaxT))  
    {
      RetournerTas(&RebutR7);
      PoserTasSurTas(&RebutR7, &TalonR7);
      JouerUnTourR7(MT);
      NumTourR7 = NumTourR7 + 1;
    }
return NumTourR7 ;

  /* if (TasVide(RebutR7))
   {
      printf("Vous avez gagne en %d tours !\n",NumTourR7);
    }
  else
    {
      printf("Vous avez perdu !\n");
   }   */
}


void AnalyserR7(int NP, int NMaxT)
{


  int i;  
  int  NumTourR7;
  NumTourR7 =0 ;
  int count1;
  count1 =0;
   int count2;
  count2 =0;
   int count3;
  count3 =0;
  int count4;
  count4 =0;
  int NMaxTAn;
  NMaxTAn =4;
 
  
  CreerTableauInitialR7();  
  JouerUneR7An(NMaxTAn,SansTrace);  
   for (i = 0; i <= NP-1; i++)     {   
   
        ReformerTableauInitialR7();    
        NumTourR7 = JouerUneR7An(NMaxTAn, SansTrace);   

        switch (NumTourR7){
        case 1:count1+=1;break;
        case 2:count2+=1;break;
        case 3:count3+=1;break;   
        }
       
       count4=NP-(count1+count2+count3);

    }

       printf("Pourcentage de gagner en 1 fois : %.2f %% \n",(float)count1*100/NP); 
       printf("Pourcentage de gagner en 2 fois : %.2f %% \n",(float)count2*100/NP); 
       printf("Pourcentage de gagner en 3 fois : %.2f %% \n",(float)count3*100/NP); 
       printf("Pourcentage de perdre : %.2f %% \n",(float)count4*100/NP);
      

 
}
	