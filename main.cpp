#include <iostream>
#include <fstream>
#include <string>

// using namespace std;
// function prototypes enabled for retrieving + reading files
void retrieveFile(std::ifstream &filename);
void readFile(std::ifstream &filename);

// command line arguments es aqui
int main(int argc, char* argv[]) {
    // enables retrieving + reading file
    std::ifstream file;
    retrieveFile(file);
    readFile(file);
    return 0;
}

void retrieveFile(std::ifstream &filename) {
    std::string file;
    // prompts user to input file for read input + write output file
    std::cout << "Please enter desired filename that needs to be read: ";
    // file exists - will find + open file
    while(true) {
        std::cin >> file;
        filename.open(file); 
        // accounts for file opening errors
        if(!filename) { 
            std::cout << "Error - Something is wrong with the file inputted.\n";
            std::cout << "Try another file next time.\n";
            exit(0); // immediately closes program
        }
    }
}

void readFile(std::ifstream &filename) {
    // enables reading + writing file
    std::ofstream oput;
    oput.open(""); // desired file may be inserted here
    int a = 0; // helps in incrementing file - in while loop
    std::string oputL = " "; // inputted strings 
    std::string value;
    std::cout << "Reading through file ... \n";
    oput << "Token(s)\n Lexeme(s)\n";
    /*  while (filename >> value) {
        a++;
        // refer to + implement lexer analyzer here 
        // probably use a for loop to iterate through file 
        // then use oput(aka output) to write out oput
    } */
    oput.close();  // closes file
}