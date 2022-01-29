#include <stdio.h>

#include "C4.h"

int compteurGagner =0;
int compteurPerdu =0;
char TexteCouleurC4[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

/* Tableau de jeu */

int NumTourC4;
typedef Tas SerieCouleurC4;
SerieCouleurC4 LigneC4[DerniereCouleur+1];
Tas TalonC4;

/* localisation des tas */
Localisation LocSeriesC4[DerniereCouleur+1];
Localisation LocTalonC4;

/* Formation du tableau de jeu initial */

void SaisirLocTasC4()
{
  int i;

  LocTalonC4.NC = 1;
  LocTalonC4.NL = 1;

  for (i=PremiereCouleur; i<=DerniereCouleur; i++)
    {
      LocSeriesC4[i].NC = 2*i+2;
      LocSeriesC4[i].NL = 1;
    }
}

void CreerTableauInitialC4()
{
  Couleur Co;
  int carte;

  SaisirLocTasC4();
  NumTourC4 = 1;

  /* Creation du talon avec un jeu de 32 cartes */
  CreerJeuNeuf(32, LocTalonC4, &TalonC4);
  BattreTas(&TalonC4);

  /* Creation des series de chaque couleur*/

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      CreerTasVide(LocSeriesC4[Co], etale, &(LigneC4[Co]));
      for (carte = Sept; carte <= As; carte++){
          DeplacerHautSur(&TalonC4, &LigneC4[Co]);/*distribuer les cartes du talon sur les lignes*/
      }
      BattreTas(&LigneC4[Co]);
    }

}

/* Visualisation des etats du jeu */
void ReformerTableauInitialC4()
{
  Couleur Co;
  int carte;
  /* On reforme le talon, en empilant les cartes de la ligne */
  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    {
      EmpilerTas(&(LigneC4[Co]));/*il faut que les tas aient le même mode d'empilement que le talon*/
      PoserTasSurTas(&(LigneC4[Co]), &TalonC4);
      EtalerTas(&(LigneC4[Co])); /*remettre les tas en mode etale pour la suite*/
    }
  RetournerTas(&TalonC4);
  BattreTas(&TalonC4);
   
  /*reformer les 4 tas avant de recommencer une partie*/
  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
  {
    for (carte = Sept; carte <= As; carte++){
        DeplacerHautSur(&TalonC4, &LigneC4[Co]);
    }
  }
  BattreTas(&LigneC4[Co]);
}

void AfficherC4()
{
  Couleur Co;

  EffacerGraphique();
  AfficherTas(TalonC4, "Talon");

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    AfficherTas(LigneC4[Co], TexteCouleurC4[Co]);
  
  MettreAJourGraphique();

  AttendreCliquer();/*on attend un clique pour jouer*/
}
/* Jouer C4 */

void JouerTasC4(Tas *T, Couleur *ProchaineCouleur) {

  Couleur Co;
  
  Co = LaCouleur(CarteSur(*T));/*on recupere la couleur de la carte située sur un tas de la ligne*/

  switch (Co) {/*en fonction de la couleur on deplace la carte sous le bon tas*/
  	case VideC:
	case Trefle: DeplacerHautSous(T, &(LigneC4[Co])); break;
	case Carreau: DeplacerHautSous(T, &(LigneC4[Co])); break;
	case Coeur: DeplacerHautSous(T, &(LigneC4[Co])); break;
	case Pique: DeplacerHautSous(T, &(LigneC4[Co])); break;
	}
 *ProchaineCouleur=Co;/*on sauvgarde la couleur du tas ou on devra retourner la carte du dessus*/
}

/* Jouer un tour C4: Arreter quand il y a un tas avec toutes ces cartes d�couvertes */

void JouerUnTourC4(ModeTrace MT) {
	
  Couleur ProchaineCouleur;
  booleen OK;

  if (MT == AvecTrace) {
    AfficherC4();
  }

  ProchaineCouleur=PremiereCouleur;/*on initialise la prochaine couleur par la premiere couleur */
  OK = vrai;

  while (OK) {
  	RetournerCarteSur(&(LigneC4[ProchaineCouleur]));
    if (MT == AvecTrace) {
    AfficherC4();
            }
  	JouerTasC4(&(LigneC4[ProchaineCouleur]), &ProchaineCouleur);
	OK = EstCachee(CarteSur(LigneC4[ProchaineCouleur]));/*si la carte du dessus n'est pas cachée alors toutes les cartes du tas sont decouvertes:fin de reussite*/
  	if (MT == AvecTrace)
	      AfficherC4();	
  }
}

/* Jouer C4 et decider si la partie est gagn�e ou pas*/

void JouerUneC4(ModeTrace MT) {
  int i;
  JouerUnTourC4(MT); /*la reussite est interompue a la suite de l'appel de cette fonction */
  Couleur Co;

/* retourner toutes les cartes cach�es */

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++) { 
	for (i=1; i<=((&LigneC4[Co])->HT); i++) {
	    if (EstCachee(IemeCarte(*(&LigneC4[Co]), i))) {
    RetournerIeme(&LigneC4[Co],i);
	    }
	}
    }
  if (MT == AvecTrace)
	      AfficherC4();

booleen victoire;
victoire = vrai;
for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++) { 
	for (i=1; i<=(LigneC4[Co].HT); i++) {
    victoire = victoire && (Co == LaCouleur(IemeCarte(LigneC4[Co], i)));
  }
}
  if (victoire)
    {
      if (MT == AvecTrace) {printf("Vous avez gagne\n");}
      else {compteurGagner+=1;}
    }
  else
    {
      if (MT == AvecTrace) {printf("Vous avez perdu\n");}
      else {compteurPerdu+=1;}
    }
}

	
void ObserverC4(int NP)
{
  int i;

  CreerTableauInitialC4();
  JouerUneC4(AvecTrace);
  for (i = 1; i <= NP-1; i++)
    {
      ReformerTableauInitialC4();
      JouerUneC4(AvecTrace);
    }
}

void AnalyserC4(int NP) {
  int i;
  CreerTableauInitialC4();
  JouerUneC4(SansTrace);
  for (i = 1; i <= NP-1; i++)
    {
      ReformerTableauInitialC4();
      JouerUneC4(SansTrace);
    }
  printf("Parties gagnees: %d\n", compteurGagner);
  printf("Parties perdues %d\n", compteurPerdu);

  compteurGagner=0;	
  compteurPerdu=0;
}
	


/*void JouerUnTourC4(ModeTrace MT)
{
    if (MT == AvecTrace){
        AfficherC4();
    }
    int OK;
    int gagner = 1;
    Couleur i;
    int j;
    int couleurComplete;
    int compteurTrefle = 0;
    int compteurCarreau = 0;
    int compteurCoeur = 0;
    int compteurPique = 0;

    int CoAl = UnEntier(DerniereCouleur);
    Couleur couleurAl = (Couleur) CoAl;
    int test = UnEntier(4);
    printf("%d\n", DerniereCouleur);
    printf("%d\n", CoAl);
    printf("%d\n", test);
    
    do{
        if((compteurTrefle<8) && (compteurCarreau<8) && (compteurCoeur<8) && (compteurPique<8)){
            OK = 1;
        }
        else{
            OK = 0;
            if(compteurTrefle==8){
              couleurComplete=1;
            }
             if(compteurCarreau==8){
              couleurComplete=2;
            }
             if(compteurCoeur==8){
              couleurComplete=3;
            }
             if(compteurPique==8){
              couleurComplete=4;
            }
        }

        RetournerCarteSur(&(LigneC4[couleurAl]));
        Couleur couleurCarte = LaCouleur(CarteSur(LigneC4[couleurAl]));
        switch(couleurCarte){
            case 0: break;
            case 1:compteurTrefle++; break;
            case 2:compteurCarreau++; break;
            case 3:compteurCoeur++; break;
            case 4:compteurPique++; break;
        }
        AfficherC4();
        AttendreCliquer();

        DeplacerHautSous(&(LigneC4[couleurAl]), &(LigneC4[couleurCarte]));
        couleurAl = couleurCarte;

        AfficherC4();
        AttendreCliquer();

    }while(OK==1);


    for(i=PremiereCouleur; i<=DerniereCouleur; i++){

        for(j=1; j<=((&LigneC4[i])->HT); j++){
          if(EstCachee(IemeCarte(LigneC4[i], j))) {
		        RetournerIeme(&LigneC4[i], j);
            AfficherC4();
            if(LaCouleur(IemeCarte(LigneC4[i], j)) != i){
              gagner = 0;
            }
          }
        }

    printf("fin1\n");
    }

    if(gagner == 0){
      printf("vous avez perdu");
    }
    else{
      printf("vous avez gagné");
    }
}*/



