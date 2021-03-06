#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

struct character {
   char name[20];
   int health;
   int attack;
   int xp;
   int level;
   struct SDL_Texture *tex;
   struct SDL_Rect srcrect;
   struct SDL_Rect dstrect;
};

struct button {
   struct SDL_Texture *tex;
   int clicked;
   SDL_Rect rect;
};

SDL_Window *init();
void rendertext(char *text, SDL_Renderer *rend, int x, int y);
SDL_Rect makerect(int x, int y, int w, int h);
struct character makecharacter(char *name, int health, int attack, SDL_Texture *tex, SDL_Rect srcrect, SDL_Rect dstrect);
struct button makebutton(SDL_Texture *buttontex, SDL_Rect buttonrect);
int clickedbutton(SDL_Event event, struct button button);
SDL_Texture * maketext(TTF_Font *font, char *text, SDL_Renderer *rend);
SDL_Texture *loadassest(char *filename, SDL_Renderer *rend, SDL_Window *win);
void handleinput();
void update(SDL_Window *win, SDL_Renderer *rend);
void render(SDL_Renderer *rend, struct character charlist[4]);

int scene = 0;
int closerequest = 0;
struct button startbutton;
struct button attackbutton;
struct button selectcharbutton;
struct button tylerbutton;
struct button raulbutton;
struct button scenebutton;
//struct button donebutton;

struct character charlist[4];
TTF_Font *font;

int main()
{
   SDL_Window *win = init();

   Uint32 renderflags = SDL_RENDERER_ACCELERATED;
   SDL_Renderer *rend = SDL_CreateRenderer(win, -1, renderflags);
   if (!rend) {
      printf("error creating render: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
   }

   font = TTF_OpenFont("assests/ARCADECLASSIC.ttf", 30);
   SDL_Texture *messagetex = maketext(font, "Start Game", rend);
   SDL_Rect messagerect;

   SDL_Texture *attacktex = maketext(font, "Attack", rend);
   SDL_Rect attackrect;

   SDL_Texture *charactertoptex = maketext(font, "Select your character", rend);
   SDL_Rect charactertoprect;
   SDL_Texture *selecttylertex = maketext(font, "Tyler", rend);
   SDL_Rect selecttylerrect;
   SDL_Texture *selectraultex = maketext(font, "Raul", rend);
   SDL_Rect selectraulrect;
   SDL_Texture *scenetex = maketext(font, "Scene 2", rend);
   SDL_Rect scenerect;

   //SDL_Texture *donetex = maketext(font, "Done Selecting", rend);
   //SDL_Rect donerect;

   charactertoprect.x = 10;
   selecttylerrect.x = 10;
   selectraulrect.x = 10;
   scenerect.x = 10;
   //donerect.x = 10;
   charactertoprect.y = 30;
   selecttylerrect.y = 100;
   selectraulrect.y = 150;
   scenerect.y = 200;
   //donerect.y = 200;

   SDL_QueryTexture(charactertoptex, NULL, NULL, &charactertoprect.w, &charactertoprect.h);
   SDL_QueryTexture(selecttylertex, NULL, NULL, &selecttylerrect.w, &selecttylerrect.h);
   SDL_QueryTexture(selectraultex, NULL, NULL, &selectraulrect.w, &selectraulrect.h);
   SDL_QueryTexture(scenetex, NULL, NULL, &scenerect.w, &scenerect.h);
   //SDL_QueryTexture(donetex, NULL, NULL, &donerect.w, &donerect.h);


   selectcharbutton = makebutton(charactertoptex, charactertoprect);
   tylerbutton = makebutton(selecttylertex, selecttylerrect);
   raulbutton = makebutton(selectraultex, selectraulrect);
   scenebutton = makebutton(scenetex, scenerect);
   //donebutton = makebutton(donetex, donerect);


   attackrect.x = 100;
   attackrect.y = 300;
   messagerect.y = 220;
   SDL_QueryTexture(messagetex, NULL, NULL, &messagerect.w, &messagerect.h);
   SDL_QueryTexture(attacktex, NULL, NULL, &attackrect.w, &attackrect.h);
   messagerect.x = (WINDOW_WIDTH/2) - (messagerect.w / 2);

   startbutton = makebutton(messagetex, messagerect);
   attackbutton = makebutton(attacktex, attackrect);

   printf("Finshed Initalizing\n");

   while (!closerequest) {
      handleinput();
      update(win, rend);
      render(rend, charlist);
   }

   SDL_DestroyTexture(charlist[0].tex);
   SDL_DestroyTexture(charlist[1].tex);
   SDL_DestroyRenderer(rend);
   SDL_DestroyWindow(win);

   return 0;
}

void handleinput()
{
   SDL_Event event;
   while (SDL_PollEvent(&event)) {
      switch (event.type) {
         case SDL_QUIT:
            closerequest = 1;
            break;
         case SDL_MOUSEBUTTONDOWN:
            startbutton.clicked = clickedbutton(event, startbutton);
            tylerbutton.clicked = clickedbutton(event, tylerbutton);
            raulbutton.clicked = clickedbutton(event, raulbutton);
            attackbutton.clicked = clickedbutton(event, attackbutton);
            //donebutton.clicked = clickedbutton(event, donebutton);
      }
   }
}

void update(SDL_Window *win, SDL_Renderer *rend)
{
   if (startbutton.clicked == 1 && scene == 0) {
      scene = 1;
   } else if (tylerbutton.clicked == 1 && scene == 1) {
      SDL_Texture *tylertex = loadassest("assests/Tyler.png", rend, win);
      SDL_Rect tylersrcrect = makerect(0, 0, 60, 120);
      SDL_Rect tylerdstrect = makerect(300, 250, 120, 250);
      charlist[0] = makecharacter("Tyler", 100, 20, tylertex, tylersrcrect, tylerdstrect);

      scene = 2;
      tylerbutton.clicked = 0;
   } else if (tylerbutton.clicked == 1 && scene == 2) {
      SDL_Texture *tylertex = loadassest("assests/Tyler.png", rend, win);
      SDL_Rect tylersrcrect = makerect(0, 0, 60, 120);
      SDL_Rect tylerdstrect = makerect(300, 250, 120, 250);
      charlist[1] = makecharacter("Tyler", 100, 20, tylertex, tylersrcrect, tylerdstrect);

      scene = 3;
      tylerbutton.clicked = 0;
   } else if (raulbutton.clicked == 1 && scene == 1) {
      SDL_Texture *raultex = loadassest("assests/Raul.png", rend, win);
      SDL_Rect raulsrcrect = makerect(0, 0, 50, 75);
      SDL_Rect rauldstrect = makerect(100, 100, 100, 150);
      charlist[0] = makecharacter("Raul", 100, 20, raultex, raulsrcrect, rauldstrect);
      
      scene = 2;
      raulbutton.clicked = 0;
   } else if (raulbutton.clicked == 1 && scene == 2) {
      SDL_Texture *raultex = loadassest("assests/Raul.png", rend, win);
      SDL_Rect raulsrcrect = makerect(0, 0, 50, 75);
      SDL_Rect rauldstrect = makerect(100, 100, 100, 150);
      charlist[1] = makecharacter("Raul", 100, 20, raultex, raulsrcrect, rauldstrect);
      
      scene = 3;
      raulbutton.clicked = 0;
   } else if (attackbutton.clicked == 1 && scene == 3) {
         charlist[1].health -= charlist[0].attack;
         attackbutton.clicked = 0;
         scene = 4;
   } else if (attackbutton.clicked == 1 && scene == 4) {
         charlist[0].health -= charlist[1].attack;
         attackbutton.clicked = 0;
         scene = 3;
   }
      
      //else if (donebutton.clicked == 1 && (scene == 1 || scene == 2)) {
      //scene = 3;
   //}
}

void render(SDL_Renderer *rend, struct character charlist[4])
{
   SDL_RenderClear(rend);
   if (scene == 0) {
      SDL_RenderCopy(rend, startbutton.tex, NULL, &startbutton.rect);
   } else if (scene == 1) { 
      SDL_RenderCopy(rend, selectcharbutton.tex, NULL, &selectcharbutton.rect);
      SDL_RenderCopy(rend, tylerbutton.tex, NULL, &tylerbutton.rect);
      SDL_RenderCopy(rend, raulbutton.tex, NULL, &raulbutton.rect);
      //SDL_RenderCopy(rend, donebutton.tex, NULL, &donebutton.rect);
   } else if (scene == 2) {
      SDL_RenderCopy(rend, selectcharbutton.tex, NULL, &selectcharbutton.rect);
      SDL_RenderCopy(rend, tylerbutton.tex, NULL, &tylerbutton.rect);
      SDL_RenderCopy(rend, raulbutton.tex, NULL, &raulbutton.rect);
      SDL_RenderCopy(rend, scenebutton.tex, NULL, &scenebutton.rect);
      //SDL_RenderCopy(rend, donebutton.tex, NULL, &donebutton.rect);
   } else if (scene == 3) {
      SDL_RenderCopy(rend, charlist[0].tex, &charlist[0].srcrect, &charlist[0].dstrect);
      SDL_RenderCopy(rend, attackbutton.tex, NULL, &attackbutton.rect);
      char *healthstr = (char *) malloc(15 * sizeof(char));
      sprintf(healthstr, "Health %d", charlist[0].health);
      rendertext(healthstr, rend, 10, 30);
   } else if (scene == 4) {
      SDL_RenderCopy(rend, charlist[1].tex, &charlist[1].srcrect, &charlist[1].dstrect);
      SDL_RenderCopy(rend, attackbutton.tex, NULL, &attackbutton.rect);
      char *healthstr = (char *) malloc(15 * sizeof(char));
      sprintf(healthstr, "Health %d", charlist[1].health);
      rendertext(healthstr, rend, 10, 30);
   }
   SDL_RenderPresent(rend);
}

SDL_Window *init()
{
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      printf("error initalizing SDL: %s\n", SDL_GetError());
      exit(1);
   }

   if (TTF_Init() == -1) {
      printf("error initalizing SDL_ttf\n");
      exit(1);
   }

   SDL_Window *win = SDL_CreateWindow("Fighting Game",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
   if (!win) {
      printf("error creating window: %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   return win;
}

SDL_Texture *loadassest(char *filename, SDL_Renderer *rend, SDL_Window *win)
{
   SDL_Surface *surface = IMG_Load(filename);

   if (!surface) {
      printf("error creating surface\n");
      SDL_DestroyRenderer(rend);
      SDL_DestroyWindow(win);
      SDL_Quit();
      exit(1);
   }

   SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);
   SDL_FreeSurface(surface);
   if (!tex) {
      printf("error creating texture: %s\n", SDL_GetError());
      SDL_DestroyRenderer(rend);
      SDL_DestroyWindow(win);
      SDL_Quit();
      exit(1);
   }

   return tex;
}

SDL_Rect makerect(int x, int y, int w, int h)
{
   SDL_Rect rect;
   rect.x = x;
   rect.y = y;
   rect.w = w;
   rect.h = h;
   return rect;
}
SDL_Texture *maketext(TTF_Font *font, char *text, SDL_Renderer *rend)
{
   SDL_Color textcolor = {255,255,255};
   SDL_Surface *message = TTF_RenderText_Solid(font, text, textcolor);
   SDL_Texture *messagetex = SDL_CreateTextureFromSurface(rend, message);
   SDL_FreeSurface(message);

   return messagetex;
}

struct character makecharacter(char *name, int health, int attack, SDL_Texture *tex, SDL_Rect srcrect, SDL_Rect dstrect)
{
   struct character newcharacter;

   memcpy(newcharacter.name, name, 20);
   newcharacter.health = health;
   newcharacter.attack = attack;
   newcharacter.xp = 0;
   newcharacter.level = 1;
   newcharacter.tex = tex;
   newcharacter.srcrect = srcrect;
   newcharacter.dstrect = dstrect;

   return newcharacter;
}

struct button makebutton(SDL_Texture *buttontex, SDL_Rect buttonrect)
{
   struct button newbutton;

   newbutton.tex = buttontex;
   newbutton.clicked = 0;
   newbutton.rect = buttonrect;

   return newbutton;
}

int clickedbutton(SDL_Event event, struct button button)
{
   button.clicked = 1;

   if (event.button.x < button.rect.x) button.clicked = 0;
   else if (event.button.x > button.rect.x + button.rect.w) button.clicked = 0;
   else if (event.button.y < button.rect.y) button.clicked = 0;
   else if (event.button.y > button.rect.y + button.rect.h) button.clicked = 0;
   
   return button.clicked;
}

void rendertext(char *text, SDL_Renderer *rend, int x, int y)
{
   SDL_Color textcolor = {255,255,255};
   SDL_Surface *message = TTF_RenderText_Solid(font, text, textcolor);
   SDL_Texture *messagetex = SDL_CreateTextureFromSurface(rend, message);
   SDL_FreeSurface(message);
   
   int w, h;
   SDL_QueryTexture(messagetex, NULL, NULL, &w, &h);
   SDL_Rect dstrect = makerect(x, y, w, h);

   SDL_RenderCopy(rend, messagetex, NULL, &dstrect);
   SDL_DestroyTexture(messagetex);
}
