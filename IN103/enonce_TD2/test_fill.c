//#include <SDL.h>
#include <unistd.h>    /* Pour getpid. */
#include "gfxprims.h"
#include "fill.h"


#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)


int main (int argc, char *argv[])
{
  int go_on = 1 ;

  if (argc != 2) {
    printf ("Wrong argument. Expected <nb initial points>.\n") ;
    return (-1) ;
  }

  if (SDL_Init (SDL_INIT_VIDEO) < 0) {
    printf ( "Unable to init SDL: %s\n", SDL_GetError ()) ;
    return (-1) ;
  }

  g_screenSurface =
    SDL_SetVideoMode
    (SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_HWSURFACE | SDL_DOUBLEBUF) ;
  if (g_screenSurface == NULL) {
    printf
      ("Unable to set %dx%d video: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_GetError ()) ;
    SDL_Quit () ;
    return (-1) ;
    }

  /* Set the title of the window. */
  SDL_WM_SetCaption ("Press ESC to quit.", NULL) ;

  if (SDL_MUSTLOCK (g_screenSurface)) {
    if (SDL_LockSurface(g_screenSurface) < 0) return (-1) ;
  }

  srand (getpid ()) ;

  /* Calcul du remplissage. */
  fill (SCREEN_WIDTH, SCREEN_HEIGHT, atoi (argv[1])) ;

  if (SDL_MUSTLOCK (g_screenSurface)) SDL_UnlockSurface (g_screenSurface) ;

  while (go_on) {
    SDL_Event event ;
    SDL_Flip (g_screenSurface) ;

    while (SDL_PollEvent (&event)) {
      if (event.type == SDL_QUIT) go_on = 0 ;

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          go_on = 0 ;
          break ;
        default:  /* Explicitly ignore. */
          break ;
        }
      }
    }
  }

  SDL_FreeSurface (g_screenSurface) ;
  SDL_Quit () ;
  return (0) ;
}
