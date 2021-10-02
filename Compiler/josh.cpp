#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "LexicalAnalyzer.h"


int main(int argc, char** argv)
{
     int cp = 0;    // intialze current position 

     /* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        :::::::::::::::::::::::::::::::::::::::::FILE LOADING::::::::::::::::::::::::::::::::::::::::::::::::::::::
        :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
     std::string   file_path;
     std::ifstream in_stream;
     std::ofstream of_stream;

     if (argc > 1) // this can pass even when the filepath is not a good one (which is fine but not ideal)
     {
          file_path.assign(argv[1]);                   // get CL arg and assign it to file_path

          /* A bitmask value of member type iostate formed by a combination of error
          state flag bits to be set (badbit, eofbit and/or failbit), or set to goodbit (or zero).*/
          in_stream.exceptions(std::ifstream::failbit);


          try                                                             // ** Try Loading File from 
          {                                                               // path provided by argv **
               in_stream.open(file_path, std::ifstream::in);

          }
          catch (const std::ifstream::failure& e)                         // catch paramter same as bitmask
          {
               std::ostringstream msg;
               msg << "\n\n**ERROR** \n\nOpening file '" << file_path
                    << "' failed, it either doesn't exist or is not accessible.\n\n";
               std::cout << msg.str();
               return 1;
          }
          // *************End of Try/Catch ****************



         // string(InputIterator first, InputIterator last);          // Overloaded std::String ctor
          //std::string file_text((
          //     std::istreambuf_iterator<char>(in_stream)),            // First
          //     std::istreambuf_iterator<char>());                     // Last

          std::string file_text = "Some temp file text"; // TODO delete this and uncomment above

          of_stream.open("output.txt");       // open a file to write in

         // check for error
          if (!of_stream.is_open())
          {
               std::cout << "Error opening file";
               exit(1);
          }

          /* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
             :::::::::::::::::::::::::::::::::::::::::END OF FILE LOADING:::::::::::::::::::::::::::::::::::::::::::::::
             :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

          
          //of_stream << "TOKEN\t\t\tLEXEMES" << std::endl << std::endl;                // write to file


          LA::LexicalAnalyzer lex(file_text);
          LA::LexicalUnit lexUnit;

          //of_stream << "    Token    |    Lexeme    \n" << std::setfill('-') << std::setw(29) << '\n';
          std::cout << "    Token    |    Lexeme    \n" << std::setfill('-') << std::setw(29) << '\n';

          // loop through entire string of text   
          while (lex.Lexer(lexUnit)) // this is where you call Lex.Lexer();
          {
               //of_stream << std::setw(13) << lexUnit.tokenString << "|" << std::setw(14) << lexUnit.lexeme << '\n';
               std::cout << std::setw(13) << lexUnit.tokenString << "|" << std::setw(14) << lexUnit.lexeme << '\n';

          }
     }

     of_stream.close();                 // close file
     //std::cin.get();                    // Keeps program from terminating (debug)
     return 0;
}