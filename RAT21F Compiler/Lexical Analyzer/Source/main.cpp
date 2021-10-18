// main.cpp

// this file serves as the driver for testing the lexical analyzer class of my compiler project.
// The directions for using this program are found in the directory in which you found this file.

// Author: Joshua Lollis
// Last Edited: 10/16/21
// CPSC 323 James Choi, Fall 2021
// Assignment 1 Lexical Analyzer

#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


#include "../Include/LexicalAnalyzer.h"

bool isVerbose{ false };


#pragma region File IO Function Signatures
void ECHO_CLI_ARGS(int argc, char** argv);
bool ConfirmInputArgSuccess(int argCount);
bool ConfirmOutputArgSuccess(int argCount);
bool LoadInputFile(std::filebuf&, std::string, std::string&);
bool OutputResultData(std::string, std::string);
#pragma endregion // End File IO function Signatures


inline void mySleep(clock_t sec) // clock_t is a like typedef unsigned int clock_t. Use clock_t instead of integer in this context
{
	clock_t start_time = clock();
	clock_t end_time = sec * 1000 + start_time;
		while (clock() != end_time);
}


#pragma region Main Entry Point
int main(int argc, char** argv)
{
	

	for (int i = 1; i < argc; i++)
	{
		if (i + 1 != argc)
		{
			if (strcmp(argv[i], "-v") == 0) // This is your parameter name
			{
				isVerbose = true;
				i++;    // Move to the next flag
			}
		}
	}

#pragma region Init CLI arg and stream data
	
	// the source passed in from Command Line
	std::string SOURCE{ "" };
	
	// The string to output to file. Will append token/lexeme pairs to end
	std::string formattedOutputString
	{
		"Token\t\tLexeme\n" \
		"------------------\n"
	};

	// default file name if an output file is not supplied
	std::string defaultFileName{ "output.RAT21F" };


	// file buffer stream for loading file contents
	std::filebuf inStream;

	// flags to signal successfull file IO
	bool isSourceInputSuccess{ false };
	bool isSourceOutputSuccess{ false };

#pragma endregion	// End Init CLI arg and stream data

#pragma region Stream Input

	if(isVerbose) std::cout << "\Checking for input file path... ";
	if (isVerbose) mySleep(1);
	// check if input arg exists
	if (ConfirmInputArgSuccess(argc))
	{
		if (isVerbose) std::cout << "FOUND";
		if (isVerbose) mySleep(1);
		try // Try loading input source stream
		{
			if (isSourceInputSuccess = LoadInputFile(inStream, argv[1], SOURCE)) {}
		}
		catch (const std::exception&)
		{
			if (isVerbose) std::cout << "Error Loading Input File..." << std::endl;
			if (isVerbose) mySleep(1);
		}
	}
	else
	{
		if (isVerbose) std::cout << "NOT FOUND";
		if (isVerbose) mySleep(1);
	}
#pragma endregion // End Stream Input Region

#pragma region Lexical Analysis

	// strings for passing to lexer that will hold the lexical units on each calling
	std::string myToken, myLexeme;

	// Instantiation of the Lexical Analyzer passing our loaded string as source
	LexicalAnalyzer LA(SOURCE); // Instantiate Lexical Analyzer object with source code string
	
	// instantiate and initialize EOF flag
	bool isEOF{ false };

	//system("cls");
	if (isVerbose) {
		if (!isEOF) std::cout << "\nBeginning Lexical Analysis...";
		else std::cout << "\nEnd of file reached...";

	}
	
	if (isVerbose) mySleep(1);

	std::stack<std::string> tokenStack;
	std::stack<std::string> lexemeStack;

	// while not end of file, analyze source
	while (!isEOF)
	{
		// set EOF based on each call to Analyzer
		isEOF = LA.Lexer(myToken, myLexeme);

		// if the tokens are empty don't bother
		if (myToken.empty() || myLexeme.empty())
		{

		}
		// otherwise append to the output string
		else
		{
			tokenStack.push(myToken);
			lexemeStack.push(myLexeme);
			//system("CLS");
			
			
			formattedOutputString.append("\n" + myToken + "\t\t" + myLexeme);
		}
		if (isVerbose) mySleep(.5);

	}

	if (isVerbose) std::cout << "\nAnalyzer has found:";
	if (isVerbose) std::cout << "\nTotal Tokens: " << tokenStack.size() << "\nTotal Lexemes: " << lexemeStack.size();
	if (isVerbose) mySleep(1);
#pragma endregion // End Lexical Analysis Region

#pragma region Stream Output

	if (isVerbose) std::cout << "\nChecking for output file path... ";
	if (isVerbose) mySleep(1);

	// check for file output filename arg
	if (ConfirmOutputArgSuccess(argc))
	{	
		if (isVerbose) std::cout << "FOUND";
		try // Try outputting results to stream
		{	
			// if the arg exists use it
			if (isSourceOutputSuccess = OutputResultData(formattedOutputString,argv[2])) {}
			
		}
		catch (const std::exception&)
		{
			if (isVerbose) std::cout << "Error Outputting Results to Stream..." << std::endl;
		}
	}
	
	// else use the default file output name
	else
	{
		if (isVerbose) std::cout << "NOT FOUND" << "\t <Using default>";
		(isSourceOutputSuccess = OutputResultData(formattedOutputString, defaultFileName));
	}
#pragma endregion // End Stream Output Region


	return 0;
}
#pragma endregion // End Main Entry Point



// Definitions for File IO functions
#pragma region FILE IO FUNCTIONS

// return true if there is an arg in the input argv[1] of the CLI
bool ConfirmInputArgSuccess(int argCount)
{
	return argCount >= 2; // True means that there are at least the [0] arg (this exe), and the [1] arg which is input filename
}


bool ConfirmOutputArgSuccess(int argCount)
{
	return argCount >= 3; // True means there are at least 3 args, the 3rd being the output filepath. Ignore any args past 3.
}

// load input file
// passing in a buffer which is actually a legacy bit of code from this project and can be edited out probably
bool LoadInputFile(std::filebuf& fBuffer, std::string fileName, std::string& sourceStringRef)
{
	if (isVerbose) std::cout << "\nLoading Input File...";
	if (isVerbose) mySleep(.5);
	bool openedSuccess{ false };
	if (openedSuccess = fBuffer.open(fileName, std::ios::in))
	{
		if (isVerbose) std::cout << "SUCCESS";
		std::istream is(&fBuffer);
		while (is)
			sourceStringRef.push_back(char(is.get()));
		fBuffer.close();
		if (isVerbose) std::cout << "\nClosing Input File...";
		if (isVerbose) std::cout << "SUCCESS";
	}
	else 
		if (isVerbose)	std::cout << "FAILED";
	return openedSuccess;
}

// output file results to file
bool OutputResultData(std::string outString, std::string outFilename = "output.RAT12F")
{
	if (isVerbose) std::cout << "\nOpening Output File...";
	if (isVerbose) mySleep(.5);
	std::filebuf outStream; // see the filebuff is local in this function but passed in in the input version. I can remove the input version's param i think and make it local
	bool openedSuccess{ false };
	if (openedSuccess = outStream.open(outFilename, std::ios::out))
	{
		if (isVerbose) std::cout << "SUCCESS";
		std::ostream os(&outStream);
		os << outString;
		outStream.close();
		if (isVerbose) std::cout << "\nClosing Output File...";
		if (isVerbose) std::cout << "SUCCESS";
		return true;
	}
	else
	{
		if(isVerbose)	std::cout << "FAILED";
	}
	return false;
}

#pragma endregion // END file i/o function region