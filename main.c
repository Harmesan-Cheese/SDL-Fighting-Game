#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

SDL_Window *init();
SDL_Rect makerect(int x, int y, int w, int h);
SDL_Texture * maketext(TTF_Font *font, char *text, SDL_Renderer *rend);
SDL_Texture *loadassest(char *filename, SDL_Renderer *rend, SDL_Window *win);
void handleinput();
void update();
void render(SDL_Renderer *rend, SDL_Texture *tex, SDL_Rect srcrect, SDL_Rect dstrect);

int scene = 0;
int closerequest = 0;
int clicked;
SDL_Rect dstrect;
SDL_Texture *messagetex;
SDL_Rect messagerect;

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

   
   SDL_Texture *tex = loadassest("assests/Tyler.png", rend, win);

   TTF_Font *font = TTF_OpenFont("assests/ARCADECLASSIC.ttf", 30);
   messagetex = maketext(font, "Start Game", rend); 
   
   messagerect.y = 220;
   SDL_QueryTexture(messagetex, NULL, NULL, &messagerect.w, &messagerect.h);
   messagerect.x = (WINDOW_WIDTH/2) - (messagerect.w / 2);


   SDL_Rect srcrect = makerect(0, 0, 60, 120);
   dstrect = makerect(150, 250, 120, 250);

   printf("Finshed Initalizing\n");

   while (!closerequest) {
      handleinput();
      update();
      render(rend, tex, srcrect, dstrect);
   }

   SDL_DestroyTexture(tex);
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
            clicked = 1;
            if (event.button.x < messagerect.x) clicked = 0;
            else if (event.button.x > messagerect.x + messagerect.w) clicked = 0;
            else if (event.button.y < messagerect.y) clicked = 0;
            else if (event.button.y > messagerect.y + messagerect.h) clicked = 0;
      }
   }
}

void update()
{
   if (clicked == 1) {
      scene = 1;
      dstrect.x = 0;
      dstrect.y = 0;
   }
}

void render(SDL_Renderer *rend, SDL_Texture *tex, SDL_Rect srcrect, SDL_Rect dstrect)
{
   SDL_RenderClear(rend);
   if (scene == 0) {
      SDL_RenderCopy(rend, messagetex, NULL, &messagerect);
   } else if (scene == 1) {
      SDL_RenderCopy(rend, tex, &srcrect, &dstrect);
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
