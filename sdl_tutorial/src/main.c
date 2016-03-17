#include <stdlib.h>

#include "SDL.h"

int main(int argc, char* argv[])
{
  int status;
  SDL_Window *main_window;
  SDL_GLContext main_context;

  status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  if (status < 0) {
    exit(EXIT_FAILURE);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  main_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (!main_window) {
    exit(EXIT_FAILURE);
  }

  main_context = SDL_GL_CreateContext(main_window);

  SDL_GL_SetSwapInterval(1);

  SDL_GL_SwapWindow(main_window);
  SDL_Delay(2000);

  SDL_GL_DeleteContext(main_context);
  SDL_DestroyWindow(main_window);
  SDL_Quit();

  exit(0);
}
