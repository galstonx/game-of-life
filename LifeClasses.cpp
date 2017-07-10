#include "LifeClasses.h"


//
// Cell methods
//
Cell::Cell() {
}

Cell::~Cell() {
}

int Cell::addLink(Cell * c) {
  links.push_back(c);
  return 1;
}

std::string Cell::getStringForTextDisplay() {
  if(cellState==0) return std::string(" ");
  else return std::string("*");
}

std::vector<std::string> Cell::getVecStringsForTextDisplay() {
  std::vector<std::string> v;
  return v;
}



int Cell::moveToNextState() {
  cellState=nextCellState;
  return 1;
}

unsigned char Cell::getCellState() {
  return cellState;
}

int Cell::setCellState(unsigned char s) {
  cellState=s;
  return 1;
}

//
// StdCell methods
//
StdCell::StdCell() {
  cellState=1;
}

StdCell::StdCell(unsigned char state_code) {
  cellState=state_code;
}

StdCell::~StdCell() {
}

int StdCell::calculateNextCellState() {
  int aliveNeighbors=0;
  for(int i=0;i<links.size(); i++) {
    if(links[i]->getCellState()==1) aliveNeighbors+=1;
  }
  // currently dead
  if(cellState==0) {
    if(aliveNeighbors == 3) nextCellState=1;
  }
  // currently alive
  else {
    // dies if fewer than 2 neighbors
    if(aliveNeighbors<2) {
      nextCellState=0;
    }
    // dies if more than 3 neighbors
    else if(aliveNeighbors>3) {
      nextCellState=0;
    }
    // lives if 2 or 3 neighbors
    else {
      nextCellState=1;
    }
  }
  return 1;
}

//
// StdCell2 methods
//
int StdCell2::calculateNextCellState() {
  int aliveNeighbors=0;
  for(int i=0;i<links.size(); i++) {
    if(links[i]->getCellState()==1) aliveNeighbors+=1;
  }
  // currently dead
  if(cellState==0) {
    if(aliveNeighbors == 3) nextCellState=1;
  }
  // currently alive
  else {
    // only difference from StdCell is here
    // dies if fewer than 1 neighbors
    if(aliveNeighbors<1) {
      nextCellState=0;
    }
    // dies if more than 3 neighbors
    else if(aliveNeighbors>3) {
      nextCellState=0;
    }
    // lives if 2 or 3 neighbors
    else {
      nextCellState=1;
    }
  }
  return 1;
}

//
// Universe methods
//
Universe::Universe() {
}

Universe::~Universe() {
}


int Universe::evolve() {
  for(int i=0;i<cells.size();i++) {
    cells[i]->calculateNextCellState();
  }
  for(int i=0;i<cells.size();i++) {
    cells[i]->moveToNextState();
  }
  return 1;
}

int Universe::getNumberOfCells() {
  return cells.size();
}

int Universe::setInitialStates(std::vector<unsigned char> i_states) {
  if(i_states.size()==cells.size()) {
    for(int i=0;i<cells.size();++i) {
      cells[i]->setCellState(i_states[i]);
    }
  }
  else {
    // error
  }
  return 1;
}

//
// Torus2d methods
//
Torus2d::Torus2d() {
  height=10;
  width=10;
  cells.reserve(height*width);
}

Torus2d::Torus2d(int h,int w) {
  height=h;
  width=w;
  cells.reserve(height*width);
}

Torus2d::~Torus2d() {
}

// only GameController knows the type of cells to add
// so need to call gc->createNewCell() to get the correct cell
int Torus2d::addCellsToUniverse(GameController* gc) {
  // create cells
  for(int i=1; i <= height*width ; i=i+1) {
    cells.push_back(gc->createNewCell());
  }
  
  // create and add links
  // i,j is vert,hor position
  // cells are stored row-wise
  // so fixing i and incrementing j by 1 gives the next cell in the vector
  for(int i=1; i<= height; i=i+1) {
    for(int j=1; j<= width; j=j+1) {
      Cell* c=cells[(i-1)*width+j-1];
      //add right link
      if(j<width) c->addLink(cells[(i-1)*width+j]);
      if(j==width) c->addLink(cells[(i-1)*width]);
      //add left link
      if(j>1) c->addLink(cells[(i-1)*width+j-2]);
      if(j==1) c->addLink(cells[(i-1)*width+width-1]);
      //up link
      if(i>1) c->addLink(cells[(i-2)*width+j-1]); 
      if(i==1) c->addLink(cells[(height-1)*width+j-1]); 
      //down link
      if(i<height) c->addLink(cells[(i)*width+j-1]); 
      if(i==height) c->addLink(cells[j-1]); 
      //up right link
      if((j<width) && (i>1)) c->addLink(cells[(i-2)*width+j]);
      if((j<width) && (i==1)) c->addLink(cells[(height-1)*width+j]);
      if((j==width) && (i>1)) c->addLink(cells[(i-2)*width]);
      if((j==width) && (i==1)) c->addLink(cells[(height-1)*width]);
      //up left link
      if((j>1) && (i>1)) c->addLink(cells[(i-2)*width+j-2]);
      if((j>1) && (i==1)) c->addLink(cells[(height-1)*width+j-2]);
      if((j==1) && (i>1)) c->addLink(cells[(i-2)*width+width-1]);
      if((j==1) && (i==1)) c->addLink(cells[(height-1)*width+width-1]);
      //down left link
      if((j>1) && (i<height)) c->addLink(cells[(i)*width+j-2]);
      if((j>1) && (i==height)) c->addLink(cells[j-2]);
      if((j==1) && (i<height)) c->addLink(cells[(i)*width+width-1]);
      if((j==1) && (i==height)) c->addLink(cells[width-1]);
      //down right link
      if((j<width) && (i<height)) c->addLink(cells[(i)*width+j]);
      if((j<width) && (i==height)) c->addLink(cells[j]);
      if((j==width) && (i<height)) c->addLink(cells[(i)*width]);
      if((j==width) && (i==height)) c->addLink(cells[0]);
    }
  }
  return 1;
}


std::string Torus2d::getStringForTextDisplay() {
  std::string s("");
  return s;
}

// return a vector of strings
// each string in vector represents a line of display
std::vector<std::string> Torus2d::getVecStringsForTextDisplay() {
  std::vector<std::string> rv; // return value
  Cell* c;
  for(int i=1; i<=height; i=i+1) {
    std::string nextline;
    for(int j=1; j<=width; j=j+1) {
      c=cells[(i-1)*width+j-1];
      nextline+=c->getStringForTextDisplay();
    }
    rv.push_back(nextline);
  }
  return rv;
}
