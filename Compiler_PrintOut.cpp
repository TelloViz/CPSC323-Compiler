//
//  CompilerPrintOut.cpp
//  Compiler_Project_Print_Out
//
//  Created by Andy Vera and Nurhaliza Hassan on 9/26/21.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    

    // Checks that the program has the appropriate number and types of statements
    if (argc != 3)  {
        cout << "Entered wrong number of statements\n It should be in the format of ' <exe file> <input text file> <output text file> \n";
        return 0;
    }

    // Opens the input and output text files
    // Changes where input is coming from and where output is going
    ifstream inputfile (argv [1]);
    ofstream opout (argv[2]);

    // Checks if the files were opened correctly
    if (inputfile.is_open() != 1){
        cout << "The input file could not be opened!\n";
        return 1;
    }
    if (opout.is_open() != 1){
        cout << "The output file could not be opened!\n";
        return 1;
    } 

    // Reads entire input text file into a string to be processed by the lexer
    string SOURCE ((istreambuf_iterator<char>(inputfile)),istreambuf_iterator<char>());             

    // Loads the Source string into the Lexical Analyzer
//    LA::LexicalAnalyzer lex(SOURCE);

    // Prints out the header of table containing the Tokens and Lexemes 
//    opout << "    Token(s)    |    Lexeme(s)    \n" << setfill('-') << setw(29) << '\n';

    // While Loop that keeps calling the Lexer to read character by character until it reaches the end of the file
//    while (!lex.IsEOF()){

    // This is where the Lexer is being directly called
//         //LA::LexicalUnit lexUnit = lex.Lexer(); 
    // Prints out the results from the Lexer into a text file
//         //opout << setw(16) << center << LexicalUnit.tokenString << "|" << setw(17) << LexicalUnit.lexeme << '\n';
//    }

//    cout << SOURCE << "\n"; This was driver code to test out if string Source read the entire text file
    
    // Closes input and output stream
    inputfile.close();
    opout.close();
    
    //Message that indicates successful run of program
    cout << "\nLexical Analyzer Done! Check Output file for results!\n";
    return 0;
}
