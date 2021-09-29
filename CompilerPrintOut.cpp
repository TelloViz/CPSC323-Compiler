//
//  main.cpp
//  Compiler_Project_Print_Out
//
//  Created by Andy Vera on 9/26/21.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;



int main(int argc, const char * argv[]) {
    
    //THIS IS FOR TESTING
    //NEED THIS TO MAKE SURE OUTPUT IS GOING TO A FILE
    ifstream inputfile (argv [1]);
    ofstream opout (argv[2]);

    if (inputfile.is_open() != 1){
        cout << "The input file could not be opened!\n";
        return 1;
    }

    if (opout.is_open() != 1){
        cout << "The output file could not be opened!\n";
        return 1;
    } 
    string line;
    //------------------------------------------------------


   opout << "    Token    |    Lexeme    \n" << setfill('-') << setw(29) << '\n';
   while (!inputfile.eof()){

       //THIS IS FOR TESTING IF OUTPUTTING TO A FILE WORKS
       getline(inputfile, line);
       //-------------------------------------------------


       //Lexer();
        //opout << setw(13) << center << LexicalUnit.tokenString << "|" << setw(14) << LexicalUnit.lexeme << '\n';
       
       opout << line << '\n';
   }
    
    inputfile.close();
    opout.close();
    
    cout << "\nLexical Analyzer Done! Check Output file for results!\n";
    return 0;
}
