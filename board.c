/**
 * Assignment: life
 * Name :Edward Liang
 * PID: A99037382
 * Class: UCSD CSE30-sp20
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - ensure that no border cells are set to alive
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){
  // TODO: 
  boards_t* newBoard = malloc(sizeof(boards_t));

  FILE *myFile = fopen(initFileName, "r");
  if (myFile == NULL) {
    return NULL;
  }

  int nRow, nCol;
  fscanf(myFile, "%d", &nRow);
  fscanf(myFile, "%d", &nCol);

  if (nRow < 2 || nCol < 2) {
    fclose(myFile);
    return NULL;
  }

  newBoard->numRows = nRow;
  newBoard->numCols = nCol;

  newBoard->bufferA = malloc((newBoard->numCols)*(newBoard->numRows) * sizeof(belem));
  newBoard->bufferB = malloc((newBoard->numCols)*(newBoard->numRows) * sizeof(belem));

  newBoard->currentBuffer = newBoard->bufferA;
  newBoard->nextBuffer = newBoard->bufferB;

  clearBoards(newBoard);

  int readRow, readCol;
  while(fscanf(myFile, "%d %d", &readRow, &readCol) > 0) {
    newBoard->currentBuffer[getIndex(newBoard, readRow, readCol)] = 1;
  }

  for (int i = 0; i < newBoard->numRows; i++) {
    for (int j = 0; j < newBoard->numCols; j++) {
      if (i == 0 || i == (newBoard->numCols - 1) || j == 0 || j == (newBoard->numRows - 1))
      {
        newBoard->currentBuffer[getIndex(newBoard, i, j)] = 0;
        newBoard->nextBuffer[getIndex(newBoard, i, j)] = 0;
      }
    }
  }

  newBoard->gen = 0;
  fclose(myFile);
  return newBoard;

}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
  // TODO:
  free((*bptrPtr)->bufferA);
  (*bptrPtr)->bufferA = NULL;
  free((*bptrPtr)->bufferB);
  (*bptrPtr)->bufferB = NULL;
  free(*bptrPtr);
  (*bptrPtr) = NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
  // TODO:
  for (int i = 0; i < (self->numCols)*(self->numRows); i++) {
    self->currentBuffer[i] = 0;
    self->nextBuffer[i] = 0;
  }
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
  // TODO:
  belem *tempBuffer = self->currentBuffer;
  self->currentBuffer = self->nextBuffer;
  self->nextBuffer = tempBuffer;
  tempBuffer = NULL;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
  // TODO:
  int index;
  index = (row*(self->numCols)) + col;
  return index;
}
