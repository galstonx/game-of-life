#ifndef IOCLASSES_H
#define IOCLASSES_H

#include <iostream>
#include "LifeClasses.h"

// forward declarations
class Universe;


//
// INPUT CLASSES
//


// base abstract class to read input
// all calls to read input in game should be routed through this
class InputReader {

 public:
  virtual char getNextInput()=0;

};

// class for text input
class TextInputReader : public InputReader {

 public:
  TextInputReader();
  char getNextInput();
  
};


// 
// OUTPUT CLASSES
//


// base abstract class to handle entire output screen
class Screen {
 public:
  virtual int init()=0;
  virtual int displayUniverse(Universe *)=0;
  virtual int displayMenu()=0;
  Screen();
  virtual int displayMessage(std::string)=0;
};

// text based screen
class TextScreen : public Screen {
 public:
  TextScreen();
  int init();
  int displayUniverse(Universe *);
  int displayMenu();
  int displayMessage(std::string);
};




// class to control output
// all calls to output things should be routed through this
class OutputController {
  
 public:
  OutputController();
  int init();
  void sendDebugMessage(std::string);
  int displayScreen(Universe *);
  int setScreen(Screen *);
  int clearScreen();
  int displayMessage(std::string);

 private:
  Screen * scr;
  
};








#endif
