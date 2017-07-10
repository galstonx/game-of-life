#ifndef LIFECLASSES_H
#define LIFECLASSES_H

#include <vector>
#include "GameController.h"

// forward declarations
class Cell;
class StdCell;
class GameController;


//
// interface (for game objects) with methods to return string suitable for text display
//
class TextDisplayInterface {
 public :
  TextDisplayInterface(){}
  virtual ~TextDisplayInterface(){}
  virtual std::string getStringForTextDisplay()=0;
  virtual std::vector<std::string> getVecStringsForTextDisplay()=0;
};


//
// cell classes
//

// abstract cell class
class Cell : public TextDisplayInterface {

 protected:
  unsigned char cellState;
  unsigned char nextCellState;
  std::vector<Cell *> links; // list of cells neighboring this cell

 public:
  Cell();
  Cell(unsigned char);
  virtual ~Cell();
  int addLink(Cell * l);
  virtual unsigned char getCellState();
  virtual std::string getStringForTextDisplay();
  virtual std::vector<std::string> getVecStringsForTextDisplay();
  virtual int calculateNextCellState()=0;
  virtual int moveToNextState();
  virtual int setCellState(unsigned char);
};

// standard cell class
class StdCell : public Cell {

 public:
  StdCell();
  StdCell(unsigned char);
  ~StdCell();
  virtual int calculateNextCellState();
};

// modified standard cell class
// has a slightly modifed rule for calculating next state
class StdCell2 : public StdCell {
 public:
  int calculateNextCellState();
};


//
// universe class
// this is the "game board" or world
//
// the main thing it contains is a vector of cells
// the "geometry" of the universe is encoded into how the cells are linked
// this object creates these links
// the links are stored in the individual cells
//
// the most important method is evolve
// this is what moves the cells from the current state to the next state
// the exact rule to use to do this is encoded in the cell objects


// abstract universe class
class Universe : public TextDisplayInterface {
 protected:
  std::vector<Cell *> cells;

 public:
  virtual ~Universe()=0;
  Universe();
  virtual std::string getStringForTextDisplay()=0;
  virtual std::vector<std::string> getVecStringsForTextDisplay()=0;
  virtual int evolve();
  virtual int addCellsToUniverse(GameController*)=0;  // only GameController knows the type of cells to add
  virtual int getNumberOfCells();
  virtual int setInitialStates(std::vector<unsigned char>);

};

// standard universe
class Torus2d : public Universe {

 private:
  unsigned int width;
  unsigned int height;
 public:
  Torus2d();
  Torus2d(int,int);
  ~Torus2d();
  virtual std::string getStringForTextDisplay();
  std::vector<std::string> getVecStringsForTextDisplay();
  int addCellsToUniverse(GameController*);
};









#endif
