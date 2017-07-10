#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <ncurses.h>
#include "IOClasses.h"
#include "LifeClasses.h"


// forward declarations
class Cell;
class StdCell;
class Universe;
class OutputController;
class InputReader;

// object to control main game flow and initialize object
//
// knows all of the settings
//
// responsible for creating objects which depend on a setting
//
// has pointers to the 2 high level I/O objects InputReader and OutputController
//
// has pointer to the main game object Universe


class GameController
{


 private:
  InputReader * ir;
  OutputController * oc;
  char displayType;
  char cellType;
  char universeType;
  char populateType;
  Universe * univ;
  int setInitialStates();

 protected:
  
 public:
  GameController();
  int getOptions();
  int startGame();
  int loop();
  int exit();
  int showWelcome();

  // only GameController knows the type of cells to add
  // so other objs should use this to create cells
  Cell* createNewCell();

  void sendDebugMessage(std::string);
};


#endif
