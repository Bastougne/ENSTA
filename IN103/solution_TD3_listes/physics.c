/* gcc gfxprims.c body.c draw.c physics.c `sdl-config --cflags --libs` */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>

#include "gfxprims.h"
#include "body.h"
#include "draw.h"
#include "simu.h"


int main (int argc, char *argv[])
{
  struct body_list_t *bodies = NULL ;
  int go_on = true ;

  if (SDL_Init (SDL_INIT_VIDEO) < 0) {
    printf ("Unable to init SDL: %s\n", SDL_GetError ()) ;
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

  /* Create the bodies. */
  bodies = new_body (bodies, 0xFF0000, 5, 10.0, 0.0, 100.0, 20.0, 20.0) ;
  bodies = new_body (bodies, 0x00FF00, 10, 1.0, 0.0, 0.0, 15.0, 15.0) ;
  bodies = new_body (bodies, 0x0000FF, 8, 5.0, 0.0, 0.0, 15.0, 15.0) ;

  while (go_on) {
    SDL_Event event ;

    if (SDL_MUSTLOCK (g_screenSurface)) {
      if (SDL_LockSurface(g_screenSurface) < 0) return (-5) ;
    }

    /* Clear the previously drawn bodies. */
    //    draw_bodies (true, bodies) ;

    if (SDL_MUSTLOCK (g_screenSurface))
      SDL_UnlockSurface (g_screenSurface) ;
    SDL_Flip (g_screenSurface) ;

    /* Compute one step of simulation. */
    simulate_bodies (bodies, forces_array) ;

    if (SDL_MUSTLOCK (g_screenSurface)) {
      if (SDL_LockSurface(g_screenSurface) < 0) return (-5) ;
    }

    /* Render the bodies at their new position. */
    draw_bodies (false, bodies) ;

    if (SDL_MUSTLOCK (g_screenSurface))
      SDL_UnlockSurface (g_screenSurface) ;

    SDL_Flip (g_screenSurface) ;

    /* Check if the ESC key has been pressed and if so trigger the exit. */
    while (SDL_PollEvent (&event)) {
      if (event.type == SDL_QUIT) go_on = false ;
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE: go_on = false ; break ;
        default: break ;  /* Explicitly ignore. */
        }
      }
    }      /* End of while (SDL_PollEvent (&event)). */
  }        /* End of while (go_on). */

  /* Housework. */
  SDL_FreeSurface (g_screenSurface) ;
  SDL_Quit () ;
  return (0) ;
}
