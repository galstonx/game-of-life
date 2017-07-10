#include <ncurses.h>
#include <string.h>
#include <iostream>
#include "IOClasses.h"

//
// TextInputReader methods
//

TextInputReader::TextInputReader() {
}

char TextInputReader::getNextInput() {
  return getch();
}


//
// OutputController methods
//

OutputController::OutputController() {
}

int OutputController::setScreen(Screen * s) {
  scr=s;
}

int OutputController::init() {
  scr->init();
  return 1;
}


void OutputController::sendDebugMessage(std::string msg) {
  mvprintw(0,0,"Debug message: %s",msg.c_str());
  mvprintw(1,0,"(Press a key to continue)");
  getch();
  move(0,0);
  clrtoeol();
  move(1,0);
  clrtoeol();
}

int OutputController::displayScreen(Universe * u) {
  scr->displayUniverse(u);
  scr->displayMenu();
  return 1;
}

int OutputController::clearScreen() {
  clear();
  return 1;
}

int OutputController::displayMessage(std::string msg) {
  scr->displayMessage(msg);
}

//
// Screen methods
//

Screen::Screen() {
}

//
// TextScreen methods
//

TextScreen::TextScreen() {
}

int TextScreen::init() {
  initscr();
  noecho();
  curs_set(0);

  return 1;
}

int TextScreen::displayUniverse(Universe * u) {
  std::vector<std::string>  data=u->getVecStringsForTextDisplay();
  int lineoffset, coloffset; // used to center text
  int height,width; // height and width of display
  std::string border;
  
  height=data.size();
  width=data[0].length();

  lineoffset=LINES/2-height/2;
  coloffset=COLS/2-width/2;

  // print top and bottom border
  border="";
  for(int i=0;i<width+2;i++) {
    border+="-";
  }
  mvprintw(lineoffset-1,coloffset,border.c_str());
  mvprintw(lineoffset+height,coloffset,border.c_str());
  // print interior with side border added
  for(int i=0;i< data.size();i++) {
    mvprintw(lineoffset+i,coloffset,("|"+data[i]+"|").c_str());
  }
  return 1;
}

int TextScreen::displayMenu() {
  mvprintw(LINES-2,0,"Options: e)volve, q)uit");
  return 1;
}

int TextScreen::displayMessage(std::string msg) {
  mvprintw(LINES-1,0,msg.c_str());
  return 1;
}









