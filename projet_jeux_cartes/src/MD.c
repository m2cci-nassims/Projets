/* Réussite Monté-Decente */

#include <stdio.h>
#include "MD.h"

char TexteCouleurMD[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};

/* Tableau de jeu */

int NumTourMD;
typedef Tas SerieCouleurMD;
SerieCouleurMD LigneMD[DerniereCouleur + 1];
Tas TalonMD;
Tas TS1;
Tas TS2;
Tas TS3;
Tas TS4;
/* localisation des tas */
Localisation LocSeriesMD[DerniereCouleur + 1];
Localisation LocTalonMD;
Localisation LocTS1;
Localisation LocTS2;
Localisation LocTS3;
Localisation LocTS4;

/* Formation du tableau de jeu initial */

void SaisirLocTasMD()
{
  int i;

  LocTalonMD.NC = 1;
  LocTalonMD.NL = 1;

  LocTS1.NC = 2;
  LocTS1.NL = 1;

  LocTS2.NC = 2;
  LocTS2.NL = 3;

  LocTS3.NC = 12;
  LocTS3.NL = 1;

  LocTS4.NC = 12;
  LocTS4.NL = 3;

  for (i = PremiereCouleur; i <= DerniereCouleur; i++)
  {
    LocSeriesMD[i].NC = 2 * i + 2;
    LocSeriesMD[i].NL = 1;
  }
}

void CreerTableauInitialMD()
{
  Couleur Co;

  SaisirLocTasMD();
  NumTourMD = 1;

  /* Cr�ation du talon avec un jeu de 52 cartes et du rebut avec un tas vide */
  CreerJeuNeuf(32, LocTalonMD, &TalonMD);
  BattreTas(&TalonMD);

  CreerTasVide(LocTS1, empile, &TS1);
  CreerTasVide(LocTS2, empile, &TS2);
  CreerTasVide(LocTS3, empile, &TS3);
  CreerTasVide(LocTS4, empile, &TS4);

  /* Cr�ation des s�ries de chaque couleur et initialisation avec le sept */

  for (Co = PremiereCouleur; Co <= DerniereCouleur; Co++)
  {
    CreerTasVide(LocSeriesMD[Co], etale, &(LigneMD[Co]));
  }
}

/* Visualisation des etats du jeu */

void AfficherMD()
{
  Couleur Co;

  EffacerGraphique();
  AfficherTas(TalonMD, "Talon");
  AfficherTas(TS1, "TS1");
  AfficherTas(TS2, "TS2");
  AfficherTas(TS3, "TS3");
  AfficherTas(TS4, "TS4");

  for (Co = PremiereCouleur; Co <= DerniereCouleur; Co++)
  {
    AfficherTas(LigneMD[Co], TexteCouleurMD[Co]);
  }

  MettreAJourGraphique();
  AttendreCliquer();
}

int PoserDansTS()
{
  int fini;
  fini = 0;
  if (TasVide(TS1))
  {
    DeplacerHautSur(&TalonMD, &TS1);
    if (EstCachee(CarteSur(TS1)))
    { /* Pb : des fois la carte sur TS est retournée, à chercher pourquoi */
      RetournerCarteSur(&TS1);
    }
  }
  else
  {
    if (RangInferieur(CarteSur(TalonMD), CarteSur(TS1)) || MemeRang(CarteSur(TalonMD), CarteSur(TS1)))
    {
      DeplacerHautSur(&TalonMD, &TS1);
      if (EstCachee(CarteSur(TS1)))
      { /* Pb : des fois la carte sur TS est retournée, à chercher pourquoi */
        RetournerCarteSur(&TS1);
      }
    }
    else
    {
      if (TasVide(TS2))
      {
        DeplacerHautSur(&TalonMD, &TS2);
      }
      else
      {
        if (RangInferieur(CarteSur(TalonMD), CarteSur(TS2)) || MemeRang(CarteSur(TalonMD), CarteSur(TS2)))
        {
          DeplacerHautSur(&TalonMD, &TS2);
          if (EstCachee(CarteSur(TS2)))
          { /* Pb : des fois la carte sur TS est retournée, à chercher pourquoi */
            RetournerCarteSur(&TS2);
          }
        }
        else
        {
          if (TasVide(TS3))
          {
            DeplacerHautSur(&TalonMD, &TS3);
          }
          else
          {
            if (RangInferieur(CarteSur(TalonMD), CarteSur(TS3)) || MemeRang(CarteSur(TalonMD), CarteSur(TS3)))
            {
              DeplacerHautSur(&TalonMD, &TS3);
              if (EstCachee(CarteSur(TS3)))
              { /* Pb : des fois la carte sur TS est retournée, à chercher pourquoi */
                RetournerCarteSur(&TS3);
              }
            }

            else
            {
              if (TasVide(TS4))
              {
                DeplacerHautSur(&TalonMD, &TS4);
                if (EstCachee(CarteSur(TS4)))
                { /* Pb : des fois la carte sur TS est retournée, à chercher pourquoi */
                  RetournerCarteSur(&TS4);
                }
              }
              else
              {
                if (RangInferieur(CarteSur(TalonMD), CarteSur(TS4)) || MemeRang(CarteSur(TalonMD), CarteSur(TS4)))
                {
                  DeplacerHautSur(&TalonMD, &TS4);
                  if (EstCachee(CarteSur(TS4)))
                  { /* Pb : des fois la carte sur TS est retournée, à chercher pourquoi */
                    RetournerCarteSur(&TS4);
                  }
                }
                else
                {

                  fini = 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return fini;
}

int DeplacerCarteST(ModeTrace MT)
{
  Rang carte;
  Couleur Co;
  int b;
  b = 0;
  for (Co = PremiereCouleur; Co <= DerniereCouleur; Co++)
  {
    if (!TasVide(LigneMD[Co]))
    {
      carte = LeRang(CarteSur(LigneMD[Co]));
      if (!TasVide(TS1))
      {
        if (LaCouleur(CarteSur(TS1)) == LaCouleur(CarteSur(LigneMD[Co])) && LeRang(CarteSur(TS1)) == RangSuivant(carte))
        {
          DeplacerHautSur(&TS1, &(LigneMD[Co]));
          if (MT == AvecTrace)
            AfficherMD();
          b = 1;
        }
      }

      if (!TasVide(TS2))
      {
        if (LaCouleur(CarteSur(TS2)) == LaCouleur(CarteSur(LigneMD[Co])) && LeRang(CarteSur(TS2)) == RangSuivant(carte))
        {
          DeplacerHautSur(&TS2, &(LigneMD[Co]));
          if (MT == AvecTrace)
            AfficherMD();
          b = 1;
        }
      }
      if (!TasVide(TS3))
      {
        if (LaCouleur(CarteSur(TS3)) == LaCouleur(CarteSur(LigneMD[Co])) && LeRang(CarteSur(TS3)) == RangSuivant(carte))
        {
          DeplacerHautSur(&TS3, &(LigneMD[Co]));
          if (MT == AvecTrace)
            AfficherMD();
          b = 1;
        }
      }
      if (!TasVide(TS4))
      {
        if (LaCouleur(CarteSur(TS4)) == LaCouleur(CarteSur(LigneMD[Co])) && LeRang(CarteSur(TS4)) == RangSuivant(carte))
        {
          DeplacerHautSur(&TS4, &(LigneMD[Co]));
          if (MT == AvecTrace)
            AfficherMD();

          b = 1;
        }
      }
    }
  }
  return b;
}

int JouerUneMD(ModeTrace MT)
{
  Rang RT, RS;
  Couleur Co;
  int Fini, b, Resultat;
  Fini = 0;

  while (!TasVide(TalonMD) && Fini != 1)
  {
    do
    {
      b = DeplacerCarteST(MT);
    } while (b == 1);
    RetournerCarteSur(&TalonMD);
    if (MT == AvecTrace)
      AfficherMD();
    RT = LeRang(CarteSur(TalonMD));
    Co = LaCouleur(CarteSur(TalonMD));

    if (TasVide(LigneMD[Co])) /*  Au debut les series sont vides, on cherche à deposer les 7 pour pouvoir débuter */
    {
      if (RT == 7) /* Si la carte est un 7 on le pose sur la série correspondante */
      {
        DeplacerHautSur(&TalonMD, &(LigneMD[Co]));
        if (MT == AvecTrace)
          AfficherMD();
      }
      else /* Si la carte est != 7 on la pose dans un tas de stockage */
      {
        Fini = PoserDansTS();
        DeplacerCarteST(MT);
        if (MT == AvecTrace)
          AfficherMD();
      }
    }
    else /* Si un 7 est déjà posé alors  */
    {
      RS = LeRang(CarteSur(LigneMD[Co]));
      if (RT == RangSuivant(RS)) /* soit la carte correspond à la suivante dans la série et on la pose dessus*/
      {
        DeplacerHautSur(&TalonMD, &(LigneMD[Co]));
        DeplacerCarteST(MT);
        if (MT == AvecTrace)
          AfficherMD();
      }
      else /* soit on pose la carte dans un tas de stockage */
      {
        Fini = PoserDansTS();
        if (MT == AvecTrace)
          AfficherMD();
      }
      DeplacerCarteST(MT);
    }
  }

  do
  {
    b = DeplacerCarteST(MT);

  } while (b == 1);
  if (TasVide(TalonMD) && TasVide(TS1) && TasVide(TS2) && TasVide(TS3) && TasVide(TS4))
  {
    if (MT == AvecTrace)
    {
      printf("Vous avez gagné \n");
    }
    return Resultat = 1;
  }
  else
  {
    if (MT == AvecTrace)
    {
      printf("Vous avez perdu \n");
    }
    return Resultat = 0;
  }
}

void ObserverMD(int nbparties)
{
  int i;
  for (i = 0; i < nbparties; i++)
  {
    CreerTableauInitialMD();
    AfficherMD();
    AttendreCliquer();
    JouerUneMD(AvecTrace);
    AfficherMD();
  }
}

void AnalyserMD(int nbparties)
{
  int i, Resultat, NbG;
  NbG = 0;
  for (i = 0; i < nbparties; i++)
  {
    CreerTableauInitialMD();

    Resultat = JouerUneMD(SansTrace);
    if (Resultat == 1)
    {
      NbG = NbG + 1;
    }
  }
  printf("Vous avez gagner %d parties sur %d. \n", NbG, nbparties);
  printf("Le pourcentage de réussite est d'environ: %.2f %% \n", (float) NbG*100/nbparties);
}