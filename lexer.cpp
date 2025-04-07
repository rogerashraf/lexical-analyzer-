// Lexical Analyzer coverted from c to C++ roger ashraf 200044552
#include <iostream> //library for input and output
#include <fstream>  //library for files
#include <cctype>  //library for character 
#include <string> //library for string

using namespace std; // to use space insdted of std::

int charClass;      // Stores class of current character
string lexeme;      // Stores the current lexeme 
char nextChar;      // Next character 
int lexLen;         // Length of lexeme
int token;          // Current token
int nextToken;      // Next token 
ifstream in_fp;     // if stream mn el libary 3ashan yakhod el file kamel

void addChar();     // Adds character 
void getChar();     // Gets next character 
void getNonBlank(); // 3ashan yseeb el spaces
int lex();          // Main function
int lookup(char ch);// Looks up operators and parentheses

#define LETTER 0    // Alphabetic character
#define DIGIT 1       // Numeric digit
#define UNKNOWN 99  // any characters
#define INT_LIT 10      // Integer literal
#define IDENT 11     // Identifier
#define ASSIGN_OP 20    // Assignment operator
#define ADD_OP 21       // Addition operator
#define SUB_OP 22    // Subtraction operator
#define MULT_OP 23     // Multiplication operator
#define DIV_OP 24    // Division operator
#define LEFT_PAREN 25   // Left parenthesis
#define RIGHT_PAREN 26  // Right parenthesis
#define EOF_TOKEN -1    // End 

int main() {  // Main function
    in_fp.open("front.in");
    if (!in_fp) {
        cout << "ERROR - cannot open front.in" << endl;
        return 1;
    }

    getChar(); // Get first character
    do {
        lex(); // Process tokens until End
    } while (nextToken != EOF_TOKEN);

    in_fp.close(); // Close input file
    return 0;
}

// Looks up operators and parentheses to determine token type
int lookup(char ch) {
    switch (ch) {
        case '(': 
            addChar(); 
            nextToken = LEFT_PAREN; 
            break;
        case ')': 
            addChar(); 
            nextToken = RIGHT_PAREN; 
            break;
        case '+': 
            addChar(); 
            nextToken = ADD_OP; 
            break;
        case '-': 
            addChar(); 
            nextToken = SUB_OP; 
            break;
        case '*': 
            addChar(); 
            nextToken = MULT_OP; 
            break;
        case '/': 
            addChar(); 
            nextToken = DIV_OP; 
            break;
        default: 
            addChar(); 
            nextToken = EOF_TOKEN; 
            break;
    }
    return nextToken;
}

// Adds current character
void addChar() {
    if (lexeme.length() <= 98) { // Check for max length
        lexeme += nextChar; // add character to lexeme
    } else {
        cout << "Error - lexeme is too long" << endl;
    }
}

// Gets next character from input and classifies it
void getChar() {
    if (in_fp.get(nextChar)) { // Read next character
        if (isalpha(nextChar))
            charClass = LETTER; // Alphabetic character
        else if (isdigit(nextChar))
            charClass = DIGIT;  // Numeric digit
        else
            charClass = UNKNOWN; // Other character
    } else {
        charClass = EOF; // End of file reached
    }
}

// yseeb el spaces
void getNonBlank() {
    while (isspace(nextChar)) // While character is null
        getChar(); // Get next character
}

int lex() {
    lexeme.clear(); // Reset lexeme
    getNonBlank(); // Skip space
    
    switch (charClass) {
        case LETTER: // Handle identifiers
            addChar();
            getChar();
            // Continue while characters are letters or digits
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT; // Set token to identifier
            break;
            
        case DIGIT: // Handle integer literals
            addChar();
            getChar();
            // Continue while characters are digits
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT; // Set token to integer literal
            break;
            
        case UNKNOWN: // Handle operators and parentheses
            lookup(nextChar);
            getChar();
            break;
            
        case EOF: // Handle end of file
            nextToken = EOF_TOKEN;
            lexeme = "EOF";
            break;
    }
    
    // Output token
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
} // end of program coverted from c to C++ roger ashraf 200044552
