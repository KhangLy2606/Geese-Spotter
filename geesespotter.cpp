#include "geesespotter_lib.h"
//g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
char * createBoard(std::size_t xdim, std::size_t ydim);
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim);
void hideBoard(char * board, std::size_t xdim, std::size_t ydim);
void cleanBoard(char * board);
void printBoard(char * board, std::size_t xdim, std::size_t ydim);
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim);

char * createBoard(std::size_t xdim, std::size_t ydim) {
std::size_t board_size = xdim* ydim;
char* new_board{new char[board_size]{}};
return new_board;
}

void cleanBoard(char * board) {
delete[] board;
board = nullptr;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim) {
    
    int cap = xdim * ydim;
    int yloc, xloc;

for (size_t i = 0; i < cap; i++)
{   
yloc = i / xdim;
xloc = i % xdim; 
if (board[i] == 9) {
    
   for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
        if (xloc + x  >= 0 && xloc + x < xdim && yloc + y >= 0 && yloc + y < ydim) {
            if(board[i+y*xdim+x]==9) {}
            else board [i + y*xdim+x] += 1;
        }
        }
    }
}
}   
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim) {
    int index = 0;
    for (size_t i = 0; i < ydim; i++)
    {
        
        for (size_t j = 0; j < xdim; j++)
        {
           
            if((board[i*xdim+j] & markedBit()) == markedBit()) {
                std::cout<<'M';
            }
            else if((board[i*xdim+j] & hiddenBit()) == hiddenBit()) {
               std::cout<<'*';
            }
            else 
            { std::cout<< char(board[i*xdim+j]+48); }
        }
        std::cout<<std::endl;
    }

}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim) {
for (size_t i = 0; i < xdim*ydim; i++)
    {
    board[i] = board[i] | hiddenBit();
    }
    
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {

if (board[xdim*yloc+xloc] < 9 ) {
return 2;
}
else if(board[xdim*yloc+xloc] & markedBit() && board[xdim*yloc+xloc] & hiddenBit()){board[xdim*yloc+xloc] = board[xdim*yloc+xloc] -= markedBit();}
else {
 board[xdim*yloc+xloc] = board[xdim*yloc+xloc] | markedBit();
}
return 0;
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
int index = xdim*yloc +xloc; 
if ((board[index] & markedBit()) == markedBit()) {return 1;}
if ((board[index] & valueMask()) == 9) {board[index] &= valueMask(); return 9;}
if ((board[index] & hiddenBit()) == 0x00) {return 2;}

if ((board[index] & hiddenBit()) == hiddenBit() && board[index] != 0) {board[index] &=  valueMask(); }

if(board[index] == 0) {
     for (int y = -1; y <= 1; y++)
     {
        for (int x = -1; x <= 1; x++)
        {
        if (xloc + x  >= 0 && xloc + x < xdim && yloc + y >= 0 && yloc + y < ydim) {
            if(board[index + y*xdim+x] == 9 || (board[index + y*xdim+x] & markedBit()) == markedBit() ) {}
            else board [index + y*xdim+x] &= valueMask();
        }
      }
    }
  }

return 0;
}


bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
bool isWon = true;

for (int i = 0; i < xdim*ydim; i++){
 
    if( (board[i] & hiddenBit()) == hiddenBit() && (board[i]&valueMask()) !=9) {
        isWon = false;
    }
}

return isWon;
}


