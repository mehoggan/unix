#include <stdlib.h>

//#include "SDL.h"
#include "opengl_core.h"

int main(int argc, char* argv[])
{
  int status;

//status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
//if (status < 0) {
//  exit(EXIT_FAILURE);
//}

//status = opengl_core_init(0);
  status = init(0);

  exit(0);
}
