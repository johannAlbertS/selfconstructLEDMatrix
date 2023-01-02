#define ROW1 A0
#define ROW2 A1
#define ROW3 A2
#define COLUMN1 5
#define COLUMN2 4
#define COLUMN3 3
#define COLUMN4 2
#define MATRIX_HEIGHT 3
#define MATRIX_WEIGHT 4
#define SLIDE_LENGTH 8

boolean matrix[MATRIX_HEIGHT][MATRIX_WEIGHT];
boolean slide[SLIDE_LENGTH][MATRIX_WEIGHT];

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
  slide[0][0] = false; slide[0][1] = true; slide[0][2] = true; slide[0][3] = true;
  slide[1][0] = true; slide[1][1] = false; slide[1][2] = true; slide[1][3] = false;
  slide[2][0] = false; slide[2][1] = true; slide[2][2] = true; slide[2][3] = true;
  slide[3][0] = false; slide[3][1] = false; slide[3][2] = false; slide[3][3] = false;
  slide[4][0] = true; slide[4][1] = true; slide[4][2] = true; slide[4][3] = true;
  slide[5][0] = false; slide[5][1] = false; slide[5][2] = false; slide[5][3] = true;
  slide[6][0] = false; slide[6][1] = false; slide[6][2] = false; slide[6][3] = true;
  slide[7][0] = false; slide[7][1] = false; slide[7][2] = false; slide[7][3] = false;
}

void loop() {
  //Example: does the same as in the commit before but with the definition before the loop function.
  for(unsigned int i = 0; i < MATRIX_WEIGHT; i++) {
    matrix[0][i] = slide[0][i];
    matrix[1][i] = slide[1][i];
    matrix[2][i] = slide[2][i];
  }
  for(unsigned int i = 3; i < SLIDE_LENGTH; i++) {
    setMatrix(matrix);
    shiftMatrix(matrix, slide[i]);
  }
  setMatrix(matrix);
  resetAll();
  delay(1000);
}
