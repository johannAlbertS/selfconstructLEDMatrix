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

typedef struct {
  boolean arr[MATRIX_HEIGHT][MATRIX_WEIGHT];
}slide_t;
//String that should be displayed on the matrix
char msg[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//LLES";
//Array containing the description of all letters
boolean letters[26][MATRIX_HEIGHT][MATRIX_WEIGHT];

/**Function to return the settings of the matrix for a specific letter
 * @param letter the Letter for which a setting is searched
 * @param letters a list of al settings of the matrix for all letters in the alphabet
 * @return an structure with an two dimentional array, which can be fed in setMatrix() for example
 */
slide_t interpretString(char letter, boolean letters[26][MATRIX_HEIGHT][MATRIX_WEIGHT]) {
	slide_t matrixOfLetter;
  for(unsigned short o = 0; o < MATRIX_WEIGHT; o++) {
    matrixOfLetter.arr[0][o] = letters[letter-65][0][o];
    matrixOfLetter.arr[1][o] = letters[letter-65][1][o];
    matrixOfLetter.arr[2][o] = letters[letter-65][2][o];
  }
  return matrixOfLetter;
}

//Function to reset all the pins to a state where no leds are on
void resetAll() {
  digitalWrite(ROW1, LOW);
  digitalWrite(ROW2, LOW);
  digitalWrite(ROW3, LOW);
  digitalWrite(COLUMN1, HIGH);
  digitalWrite(COLUMN2, HIGH);
  digitalWrite(COLUMN3, HIGH);
  digitalWrite(COLUMN4, HIGH);
}

/**Function to set the pins of all Columns
 * @param values the matrix to be evaluated
 * @param the row in the matrix to be evaluated
 */
void setColumns(boolean values[MATRIX_HEIGHT][MATRIX_WEIGHT], int row) {
  unsigned int pin = COLUMN1;
  for(unsigned int i = 0; i < MATRIX_WEIGHT; i++) {
    if(values[row-1][i] == true) digitalWrite(pin, LOW);
    else digitalWrite(pin, HIGH);
    pin--;
  }
}

/**Function to shift the Matrix further leftwards
 * @param matrix the matrix to be shifted
 * @param lastrow a boolean array to be last row of the matrix
 */
void shiftMatrix(boolean matrix[MATRIX_HEIGHT][MATRIX_WEIGHT],boolean lastrow[MATRIX_WEIGHT]) {
  for(unsigned short i = 0; i < MATRIX_WEIGHT; i++) {
    matrix[0][i] = matrix[1][i];
    matrix[1][i] = matrix[2][i];
    matrix[2][i] = lastrow[i];
  }
}

/**Function to set Matrix by setting the rows and calling the function to set the columns
 * @param matrix the Matrix to be displayed
 */
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

  //A
  letters[0][0][0] = false; letters[0][0][1] = true; letters[0][0][2] = true; letters[0][0][3] = true;
  letters[0][1][0] = true; letters[0][1][1] = false; letters[0][1][2] = true; letters[0][1][3] = false;
  letters[0][2][0] = false; letters[0][2][1] = true; letters[0][2][2] = true; letters[0][2][3] = true;
  //B
  letters[1][0][0] = true; letters[1][0][1] = true; letters[1][0][2] = true; letters[1][0][3] = true;
  letters[1][1][0] = true; letters[1][1][1] = true; letters[1][1][2] = true; letters[1][1][3] = true;
  letters[1][2][0] = false; letters[1][2][1] = true; letters[1][2][2] = false; letters[1][2][3] = true;
  //C
  letters[2][0][0] = false; letters[2][0][1] = true; letters[2][0][2] = true; letters[2][0][3] = false;
  letters[2][1][0] = true; letters[2][1][1] = false; letters[2][1][2] = false; letters[2][1][3] = true;
  letters[2][2][0] = true; letters[2][2][1] = false; letters[2][2][2] = false; letters[2][2][3] = true;
  //D
  letters[3][0][0] = true; letters[3][0][1] = true; letters[3][0][2] = true; letters[3][0][3] = true;
  letters[3][1][0] = true; letters[3][1][1] = false; letters[3][1][2] = false; letters[3][1][3] = true;
  letters[3][2][0] = false; letters[3][2][1] = true; letters[3][2][2] = true; letters[3][2][3] = false;
  //E
  letters[4][0][0] = true; letters[4][0][1] = true; letters[4][0][2] = true; letters[4][0][3] = true;
  letters[4][1][0] = true; letters[4][1][1] = true; letters[4][1][2] = false; letters[4][1][3] = true;
  letters[4][2][0] = true; letters[4][2][1] = true; letters[4][2][2] = false; letters[4][2][3] = true;
  //F
  letters[5][0][0] = true; letters[5][0][1] = true; letters[5][0][2] = true; letters[5][0][3] = true;
  letters[5][1][0] = true; letters[5][1][1] = false; letters[5][1][2] = true; letters[5][1][3] = false;
  letters[5][2][0] = true; letters[5][2][1] = false; letters[5][2][2] = true; letters[5][2][3] = false;
  //G
  letters[6][0][0] = false; letters[6][0][1] = true; letters[6][0][2] = true; letters[6][0][3] = false;
  letters[6][1][0] = true; letters[6][1][1] = false; letters[6][1][2] = false; letters[6][1][3] = true;
  letters[6][2][0] = true; letters[6][2][1] = false; letters[6][2][2] = true; letters[6][2][3] = true;
  //H
  letters[7][0][0] = true; letters[7][0][1] = true; letters[7][0][2] = true; letters[7][0][3] = true;
  letters[7][1][0] = false; letters[7][1][1] = false; letters[7][1][2] = true; letters[7][1][3] = false;
  letters[7][2][0] = true; letters[7][2][1] = true; letters[7][2][2] = true; letters[7][2][3] = true;
  //I
  letters[8][0][0] = true; letters[8][0][1] = false; letters[8][0][2] = false; letters[8][0][3] = true;
  letters[8][1][0] = true; letters[8][1][1] = true; letters[8][1][2] = true; letters[8][1][3] = true;
  letters[8][2][0] = true; letters[8][2][1] = false; letters[8][2][2] = false; letters[8][2][3] = true;
  //J
  letters[9][0][0] = true; letters[9][0][1] = false; letters[9][0][2] = true; letters[9][0][3] = false;
  letters[9][1][0] = true; letters[9][1][1] = false; letters[9][1][2] = false; letters[9][1][3] = true;
  letters[9][2][0] = true; letters[9][2][1] = true; letters[9][2][2] = true; letters[9][2][3] = false;
  //K
  letters[10][0][0] = true; letters[10][0][1] = true; letters[10][0][2] = true; letters[10][0][3] = true;
  letters[10][1][0] = false; letters[10][1][1] = false; letters[10][1][2] = true; letters[10][1][3] = false;
  letters[10][2][0] = true; letters[10][2][1] = false; letters[10][2][2] = false; letters[10][2][3] = true;
  //L
  letters[11][0][0] = true; letters[11][0][1] = true; letters[11][0][2] = true; letters[11][0][3] = true;
  letters[11][1][0] = false; letters[11][1][1] = false; letters[11][1][2] = false; letters[11][1][3] = true;
  letters[11][2][0] = false; letters[11][2][1] = false; letters[11][2][2] = false; letters[11][2][3] = true;
  //M
  letters[12][0][0] = true; letters[12][0][1] = true; letters[12][0][2] = true; letters[12][0][3] = true;
  letters[12][1][0] = false; letters[12][1][1] = true; letters[12][1][2] = false; letters[12][1][3] = false;
  letters[12][2][0] = true; letters[12][2][1] = true; letters[12][2][2] = true; letters[12][2][3] = true;
  //N
  letters[13][0][0] = true; letters[13][0][1] = true; letters[13][0][2] = true; letters[13][0][3] = true;
  letters[13][1][0] = false; letters[13][1][1] = true; letters[13][1][2] = true; letters[13][1][3] = false;
  letters[13][2][0] = true; letters[13][2][1] = true; letters[13][2][2] = true; letters[13][2][3] = true;
  //O
  letters[14][0][0] = false; letters[14][0][1] = true; letters[14][0][2] = true; letters[14][0][3] = false;
  letters[14][1][0] = true; letters[14][1][1] = false; letters[14][1][2] = false; letters[14][1][3] = true;
  letters[14][2][0] = false; letters[14][2][1] = true; letters[14][2][2] = true; letters[14][2][3] = false;
  //P
  letters[15][0][0] = true; letters[15][0][1] = true; letters[15][0][2] = true; letters[15][0][3] = true;
  letters[15][1][0] = true; letters[15][1][1] = false; letters[15][1][2] = true; letters[15][1][3] = false;
  letters[15][2][0] = false; letters[15][2][1] = true; letters[15][2][2] = false; letters[15][2][3] = false;
  //Q
  letters[16][0][0] = false; letters[16][0][1] = true; letters[16][0][2] = true; letters[16][0][3] = false;
  letters[16][1][0] = true; letters[16][1][1] = false; letters[16][1][2] = true; letters[16][1][3] = true;
  letters[16][2][0] = false; letters[16][2][1] = true; letters[16][2][2] = false; letters[16][2][3] = true;
  //R
  letters[17][0][0] = true; letters[17][0][1] = true; letters[17][0][2] = true; letters[17][0][3] = true;
  letters[17][1][0] = true; letters[17][1][1] = false; letters[17][1][2] = true; letters[17][1][3] = false;
  letters[17][2][0] = false; letters[17][2][1] = true; letters[17][2][2] = false; letters[17][2][3] = true;
  //S
  letters[18][0][0] = false; letters[18][0][1] = true; letters[18][0][2] = false; letters[18][0][3] = true;
  letters[18][1][0] = true; letters[18][1][1] = false; letters[18][1][2] = true; letters[18][1][3] = true;
  letters[18][2][0] = true; letters[18][2][1] = false; letters[18][2][2] = true; letters[18][2][3] = false;
  //T
  letters[19][0][0] = true; letters[19][0][1] = false; letters[19][0][2] = false; letters[19][0][3] = false;
  letters[19][1][0] = true; letters[19][1][1] = true; letters[19][1][2] = true; letters[19][1][3] = true;
  letters[19][2][0] = true; letters[19][2][1] = false; letters[19][2][2] = false; letters[19][2][3] = false;
  //U
  letters[20][0][0] = true; letters[20][0][1] = true; letters[20][0][2] = true; letters[20][0][3] = false;
  letters[20][1][0] = false; letters[20][1][1] = false; letters[20][1][2] = false; letters[20][1][3] = true;
  letters[20][2][0] = true; letters[20][2][1] = true; letters[20][2][2] = true; letters[20][2][3] = true;
  //V
  letters[21][0][0] = true; letters[21][0][1] = true; letters[21][0][2] = true; letters[21][0][3] = false;
  letters[21][1][0] = false; letters[21][1][1] = false; letters[21][1][2] = false; letters[21][1][3] = true;
  letters[21][2][0] = true; letters[21][2][1] = true; letters[21][2][2] = true; letters[21][2][3] = false;
  //W
  letters[22][0][0] = true; letters[22][0][1] = true; letters[22][0][2] = true; letters[22][0][3] = true;
  letters[22][1][0] = true; letters[22][1][1] = true; letters[22][1][2] = true; letters[22][1][3] = false;
  letters[22][2][0] = true; letters[22][2][1] = true; letters[22][2][2] = true; letters[22][2][3] = true;
  //X
  letters[23][0][0] = true; letters[23][0][1] = false; letters[23][0][2] = false; letters[23][0][3] = true;
  letters[23][1][0] = false; letters[23][1][1] = true; letters[23][1][2] = true; letters[23][1][3] = false;
  letters[23][2][0] = true; letters[23][2][1] = false; letters[23][2][2] = false; letters[23][2][3] = true;
  //Y
  letters[24][0][0] = true; letters[24][0][1] = true; letters[24][0][2] = false; letters[24][0][3] = false;
  letters[24][1][0] = false; letters[24][1][1] = false; letters[24][1][2] = true; letters[24][1][3] = true;
  letters[24][2][0] = true; letters[24][2][1] = true; letters[24][2][2] = false; letters[24][2][3] = false;
  //Z
  letters[25][0][0] = true; letters[25][0][1] = false; letters[25][0][2] = true; letters[25][0][3] = true;
  letters[25][1][0] = true; letters[25][1][1] = true; letters[25][1][2] = false; letters[25][1][3] = true;
  letters[25][2][0] = true; letters[25][2][1] = false; letters[25][2][2] = false; letters[25][2][3] = true;
}

void loop() {
  //Example: prints first the character 'A' on the matrix then the character 'L'
  for(size_t i = 0; i < strlen(msg); i++) {
    char letter = msg[i];
    slide_t buchstabe = interpretString(letter, letters);
    setMatrix(buchstabe.arr);
    resetAll();
    delay(500);
  }
}
