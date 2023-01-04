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
char msg[] = "AL";
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
  
  letters[0][0][0] = false; letters[0][0][1] = true; letters[0][0][2] = true; letters[0][0][3] = true;
  letters[0][1][0] = true; letters[0][1][1] = false; letters[0][1][2] = true; letters[0][1][3] = false;
  letters[0][2][0] = false; letters[0][2][1] = true; letters[0][2][2] = true; letters[0][2][3] = true; 
  letters[11][0][0] = true; letters[11][0][1] = true; letters[11][0][2] = true; letters[11][0][3] = true;
  letters[11][1][0] = false; letters[11][1][1] = false; letters[11][1][2] = false; letters[11][1][3] = true;
  letters[11][2][0] = false; letters[11][2][1] = false; letters[11][2][2] = false; letters[11][2][3] = true;
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
