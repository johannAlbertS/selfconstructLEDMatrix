#define ROW1 A0
#define ROW2 A1
#define ROW3 A2
#define COLUMN1 5
#define COLUMN2 4
#define COLUMN3 3
#define COLUMN4 2
#define MATRIX_HEIGHT 3
#define MATRIX_WEIGHT 4

boolean matrix[MATRIX_HEIGHT][MATRIX_WEIGHT];

void resetAll() {
  digitalWrite(ROW1, LOW);
  digitalWrite(ROW2, LOW);
  digitalWrite(ROW3, LOW);
  digitalWrite(COLUMN1, HIGH);
  digitalWrite(COLUMN2, HIGH);
  digitalWrite(COLUMN3, HIGH);
  digitalWrite(COLUMN4, HIGH);
}

void setColumns(boolean values[MATRIX_HEIGHT][MATRIX_WEIGHT], int row) {
  unsigned int pin = COLUMN1;
  for(unsigned int i = 0; i < MATRIX_WEIGHT; i++) {
    if(values[row-1][i] == true) digitalWrite(pin, LOW);
    else digitalWrite(pin, HIGH);
    pin--;
  }
}

void shiftMatrix(boolean matrix[MATRIX_HEIGHT][MATRIX_WEIGHT],boolean lastrow[MATRIX_WEIGHT]) {
  for(unsigned short i = 0; i < MATRIX_WEIGHT; i++) {
    matrix[0][i] = matrix[1][i];
    matrix[1][i] = matrix[2][i];
    matrix[2][i] = lastrow[i];
  }
}

void setMatrix(boolean matrix[MATRIX_HEIGHT][MATRIX_WEIGHT]) {
  for(unsigned int i = 0; i<2000; i++) {
    resetAll();
    digitalWrite(ROW1, HIGH);
    setColumns(matrix, 1);
    resetAll();
    digitalWrite(ROW2, HIGH);
    setColumns(matrix, 2);
    resetAll();
    digitalWrite(ROW3, HIGH);
    setColumns(matrix, 3);
  }
}

void setup() {
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(COLUMN1, OUTPUT);
  pinMode(COLUMN2, OUTPUT);
  pinMode(COLUMN3, OUTPUT);
  pinMode(COLUMN4, OUTPUT);
}

void loop() {
  //Example: shifts the characters 'A' and 'L' over the Matrix
  matrix[0][0] = false; matrix[0][1] = true; matrix[0][2] = true; matrix[0][3] = true;
  matrix[1][0] = true; matrix[1][1] = false; matrix[1][2] = true; matrix[1][3] = false;
  matrix[2][0] = false; matrix[2][1] = true; matrix[2][2] = true; matrix[2][3] = true;
  setMatrix(matrix);
  boolean lastrow[MATRIX_WEIGHT] = {false, false, false, false};
  shiftMatrix(matrix, lastrow);
  setMatrix(matrix);
  lastrow[0] = true; lastrow[1] = true; lastrow[2] = true; lastrow[3] = true;
  shiftMatrix(matrix, lastrow);
  setMatrix(matrix);
  lastrow[0] = false; lastrow[1] = false; lastrow[2] = false; lastrow[3] = true;
  shiftMatrix(matrix, lastrow);
  setMatrix(matrix);
  lastrow[0] = false; lastrow[1] = false; lastrow[2] = false; lastrow[3] = true;
  shiftMatrix(matrix, lastrow);
  setMatrix(matrix);
  lastrow[0] = false; lastrow[1] = false; lastrow[2] = false; lastrow[3] = false;
  shiftMatrix(matrix, lastrow);
  setMatrix(matrix);
  resetAll();
  delay(1000);
}
