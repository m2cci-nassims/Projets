/*--------------------------------------------------------------*/
/* Reussites. 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include "AfficherTas.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CARD_WIDTH 100
#define CARD_HEIGHT 150
#define SPRITE_COLS 13
#define SPRITE_LINES 5

#define ESP_X 100
#define ESP_Y 160
#define DEC_Y 40

#define FONT_SIZE 25
#define BG_COLOR 0x555555

#define WIN_GUARD(win) if (!(win)) { \
  printf("La fenetre n'existe pas."); \
  SDL_Quit(); \
  IMG_Quit(); \
  exit(1); \
}

static SDL_Window *win;
static SDL_Surface *spritesheet;
static TTF_Font *font;

const int CouleurVersLigne[SPRITE_LINES] = {
  [Coeur] = 0,
  [Carreau] = 1,
  [Trefle] = 2,
  [Pique] = 3,
};

/* Renvoie la position de la face de la carte c dans la spritesheet
 * prend en compte si la carte est cachee ou non */
SDL_Rect SpriteCarte(Carte c)
{
  const unsigned int C_SPRITE_WIDTH = spritesheet->w / SPRITE_COLS;
  const unsigned int C_SPRITE_HEIGHT = spritesheet->h / SPRITE_LINES;

  int col, ligne;
  SDL_Rect ret;

  WIN_GUARD(win);

  ret = (SDL_Rect) {
    .w = C_SPRITE_WIDTH,
    .h = C_SPRITE_HEIGHT
  };

  if (EstCachee(c)) {
    ret.x = 0;
    ret.y = (SPRITE_LINES - 1) * C_SPRITE_HEIGHT;
  } else {
    col = c.RC - Deux;
    ligne = CouleurVersLigne[c.CC];

    ret.x = col * C_SPRITE_WIDTH;
    ret.y = ligne * C_SPRITE_HEIGHT;
  }

  return ret;
}

SDL_Rect SpriteVide()
{
  const unsigned int C_SPRITE_WIDTH = spritesheet->w / SPRITE_COLS;
  const unsigned int C_SPRITE_HEIGHT = spritesheet->h / SPRITE_LINES;

  WIN_GUARD(win);

  return (SDL_Rect) {
    .x = 6 * C_SPRITE_WIDTH, /* Carte vide dans la spritesheet */
    .y = (SPRITE_LINES - 1) * C_SPRITE_HEIGHT,
    .w = C_SPRITE_WIDTH,
    .h = C_SPRITE_HEIGHT
  };
}

void OuvrirGraphique(char nom[])
{
  /* First init IMG */
  const int flags = IMG_INIT_PNG;
  if (!(IMG_Init(flags) & flags)) {
    printf("Impossible de lire des images PNG : %s", IMG_GetError());
    exit(1);
  }

  spritesheet = IMG_Load("assets/cards.png");
  if (!spritesheet) {
    printf("Impossible d'ouvrir les cartes : %s", IMG_GetError());
    IMG_Quit();
    exit(1);
  }

  /* Apres init TTF */
  if(TTF_Init()) {
    printf("Impossible de lire des fontes : %s", TTF_GetError());
    IMG_Quit();
    exit(1);
  }

  font = TTF_OpenFont("assets/jackinput.ttf", FONT_SIZE);
  if (!font) {
    printf("Impossible d'ouvrir la police : %s", TTF_GetError());
    IMG_Quit();
    exit(1);
  }

  /* Enfin, init SDL */
  if (SDL_Init(SDL_INIT_VIDEO)) {
    printf("Impossible de demarrer la SDL : %s", SDL_GetError());
    IMG_Quit();
    exit(1);
  }

  win = SDL_CreateWindow(nom,
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      WIN_WIDTH, WIN_HEIGHT, 0);

  if (!win) {
    printf("Impossible de creer la fenetre : %s", SDL_GetError());
    SDL_Quit();
    IMG_Quit();
    exit(1);
  }

  WIN_GUARD(win);
}

void FermerGraphique()
{
  if (win) {
    SDL_DestroyWindow(win);
  }

  if (spritesheet) {
    SDL_FreeSurface(spritesheet);
  }

  SDL_Quit();
  IMG_Quit();
}

void EffacerGraphique()
{
  SDL_Surface *surf;

  WIN_GUARD(win);

  surf = SDL_GetWindowSurface(win);
  SDL_FillRect(surf, NULL, BG_COLOR);
}

void MettreAJourGraphique()
{
  WIN_GUARD(win);

  SDL_UpdateWindowSurface(win);
}

void AttendreCliquer()
{
  SDL_Event event;

  WIN_GUARD(win);

  while (SDL_WaitEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
      case SDL_MOUSEBUTTONDOWN:
        return;
      case SDL_QUIT:
        FermerGraphique();
        exit(0);
      default:
        continue;
    }
  }
}

void AfficherTexte(const char * txt, int x, int y)
{
  SDL_Surface *txt_surf;
  SDL_Rect dest;

  WIN_GUARD(win);

  dest = (SDL_Rect) {
    .x = x,
    .y = y
  };

  txt_surf = TTF_RenderText_Solid(font, txt, (SDL_Colour){ 0 });

  SDL_BlitSurface(
      txt_surf, &(txt_surf->clip_rect),
      SDL_GetWindowSurface(win), &dest);

  SDL_FreeSurface(txt_surf);
}

void AfficherCarte(Carte C, int x, int y)
{
  SDL_Rect src, dst;

  WIN_GUARD(win);

  dst = (SDL_Rect) {
    .x = x,
    .y = y,
    .w = CARD_WIDTH,
    .h = CARD_HEIGHT
  };

  src = SpriteCarte(C);

  SDL_BlitScaled(spritesheet, &src, SDL_GetWindowSurface(win), &dst);
}

void AfficherTasVide(Localisation L)
{
  SDL_Rect src, dst;

  WIN_GUARD(win);

  dst = (SDL_Rect){
    .x = ESP_X*(L.NC-1),
    .y = ESP_Y*(L.NL-1),
    .w = CARD_WIDTH,
    .h = CARD_HEIGHT
  };

  src = SpriteVide();

  SDL_BlitScaled(spritesheet, &src, SDL_GetWindowSurface(win), &dst);
}

void AfficherTas(Tas T, char message[])
{
  int i;
  Localisation L;
  int H;

  L.NC = (LaPlace(T)).NC;
  L.NL = (LaPlace(T)).NL;


  if (TasVide(T)) {
    AfficherTasVide(L);
    AfficherTexte(message, ESP_X*(L.NC-1), ESP_Y*L.NL+ DEC_Y/2);
  } else
    if (TasEmpile(T)) {
      AfficherCarte(CarteSur(T), ESP_X*(L.NC-1), ESP_Y*(L.NL-1));
      AfficherTexte(message, ESP_X*(L.NC-1), ESP_Y*L.NL+ DEC_Y/2);
    } else	/* tas �tal� */ {
      H = LaHauteur(T);
      for (i = 1; i <= H; i++)
        AfficherCarte(IemeCarte(T, i), ESP_X*(L.NC-1), ESP_Y*(L.NL-1) + DEC_Y*(i-1));
      AfficherTexte(message, ESP_X*(L.NC-1), WIN_HEIGHT - 50);
    }
}
