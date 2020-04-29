/**
 * Assignment: life
 * Name: TODO
 * PID: TODO
 * Class: UCSD CSE30-sp20
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
  // TODO: 
  while (srcStart <= srcEnd) {
    int numAlive = 0;
    int columns = cols;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        numAlive += *(srcStart + (i*columns + j));
      }
    }

    numAlive -= *srcStart;

    if ((*srcStart == 1) && (numAlive < 2)) {
      *dest = 0;
    }
    else if ((*srcStart == 1) && (numAlive > 3)) {
      *dest = 0;
    }
    else if ((*srcStart == 0) && (numAlive == 3)) {
      *dest = 1;
    }
    else {
      *dest = *srcStart;
    }

    srcStart++;
    dest++;
  }
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
  // TODO:
  int numStep = steps;
  for (int k = 0; k < numStep; k++) {
    int numberRows = self->numRows;
    int numberColumns = self->numCols;


    belem *dest, *srcStart, *srcEnd;  
    srcStart = self->currentBuffer + (self->numCols) + 1;
    srcEnd = srcStart + numberColumns - 3;
    dest = self->nextBuffer + (self->numCols) + 1;

    for (int i = 0; i < (numberRows - 2); i++) {
        dest = dest + numberColumns;
        srcStart = srcStart + numberColumns;
        srcEnd = srcEnd + numberColumns;
        doRow(&dest, &srcStart, &srcEnd, self->numCols);
    }

    swapBuffers(self);
    self->gen = self->gen + 1;
  }
}




