#include <iostream>
#include <ncurses.h>
#include <string.h>

#include "GameController.h"



int main()
{

  GameController gc;
  int returnCode;
  
  gc.showWelcome();
  gc.getOptions();
  gc.startGame();
  do {
    returnCode=gc.loop();
  } while (returnCode==1);

  endwin();
  return 0;
}
