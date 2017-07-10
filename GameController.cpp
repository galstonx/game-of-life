#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include "GameController.h"


GameController::GameController() {
}

// main game loop
int GameController::loop() {
  int rv=1; // return value
  char input; // user input
  input=ir->getNextInput();
  if(input=='q') rv=0;
  if(input=='e') {
    univ->evolve();
    oc->clearScreen();
    oc->displayScreen(univ);
  }
  std::string msg("You entered: ");
  msg+=input;
  oc->displayMessage(msg);
  return rv;
}

// start game after all options have been set
int GameController::startGame() {
  srand(time(NULL)); // init random number generator for random population
  if(displayType=='t') { // text based game
    // init text based objects
    oc=new OutputController;
    oc->setScreen(new TextScreen);
    oc->init();
    ir = new TextInputReader;
  }
  univ->addCellsToUniverse(this);
  setInitialStates();
  oc->displayScreen(univ);
  return 1;
}

// collect options before starting game
int GameController::getOptions() {
  std::string temp;
  int height=40;
  int width=40;

  std::cout << "Display type is text. Maximize terminal for best results." << std::endl;
  displayType='t'; // text display
  std::cout << "Use default settings (y or n, default is y)?"<<std::endl;
  getline(std::cin,temp);
  if(temp!="n") { // default options
    cellType='s';
    height=40;
    width=40;
    populateType='r';
    universeType='t';
  }
  else { // user chooses options
    // cell type
    std::cout<< "Select cell type:"<<std::endl;
    std::cout<< "a) Standard Conway's rules, b) Modified Conway's rules"<<std::endl;
    std::cin>>temp;
    if(temp=="a") {
      cellType='s'; // Standard
      std::cout << "Cell type is standard." << std::endl;
    }
    else if(temp=="b") {
      cellType='t'; // Standard2
      std::cout << "Cell type is modified standard."<< std::endl;
    }
    else {
      std::cout<<"Invalid input. Cell type is standard."<< std::endl;
      cellType='s';
    }
    // universe type
    // and extra options for chosen universe
    std::cout << "Universe type is 2d torus." << std::endl;
    universeType='t'; // standard 2d torus
    if(universeType=='t') { // add other universe types which need height and width
      std::cout << "Enter height (1-100):";
      std::cin >> height;
      if(!((height>0) && (height<101))) {
	std::cout << "Invalid height. Using default height of 40." << std::endl;
	height=40;
      }
      std::cout << "Enter width (1-100):";
      std::cin >> width;
      if(!((height>0) && (height<101))) {
	std::cout << "Invalid width. Using default width of 40." << std::endl;
	width=40;
      }
      std::cout << "Height is "<<height<<" and width is "<<width<<"."<<std::endl;
    }
    // populate type
    // all types might not be available for all universes
    std::cout << "Initial populate type is random." << std::endl;
    populateType='r'; // populate states randomly
    std::cout << "Press enter to continue.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin,temp);
  }

  // create universe here
  // so we can pass it any needed options not saved in GameController class
  if(universeType=='t') {
    univ=new Torus2d(height,width);
  }
  return 1;
}

// welcome screen
int GameController::showWelcome() {
  std::string temp;
  std::cout << std::endl << "Welcome to Conway's Game of Life!" << std::endl;
  return 1;
}

// other objects call this to get a cell
Cell* GameController::createNewCell() {
  if(cellType=='s') { // standard cell
    return new StdCell();
  }
  if(cellType=='t') { // modified standard cell
    return new StdCell2();
  }
}

// set the initial states of cells in the universe
int GameController::setInitialStates() {
  int n_cells;
  n_cells=univ->getNumberOfCells();
  std::vector<unsigned char> i_states(n_cells);

  if(populateType=='r') { // random initial states
    for(int i=0;i<n_cells;i++) {
      i_states[i]=rand()%2;
    }
  }

  univ->setInitialStates(i_states);
  return 1;
}


void GameController::sendDebugMessage(std::string msg) {
  oc->sendDebugMessage(msg);
}

