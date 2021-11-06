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
#include "../Include/LexicalAnalyzer.h"
#include "../Include/SyntaxAnalyzer.h"
#include <list>




#pragma region File IO Function Signatures
void ECHO_CLI_ARGS(int argc, char** argv);
bool ConfirmInputArgSuccess(int argCount);
bool ConfirmOutputArgSuccess(int argCount);
bool LoadInputFile(std::filebuf&, std::string, std::string&);
bool OutputResultData(std::string, std::string);
#pragma endregion // End File IO function Signatures

#pragma region Main Entry Point
int main(int argc, char** argv)
{


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


	// check if input arg exists
	if (ConfirmInputArgSuccess(argc))
	{
		try // Try loading input source stream
		{
			if (isSourceInputSuccess = LoadInputFile(inStream, argv[1], SOURCE)) {}
		}
		catch (const std::exception&)
		{
			std::cout << "Error Loading Input File..." << std::endl;
		}
	}
#pragma endregion // End Stream Input Region



	// strings for passing to lexer that will hold the lexical units on each calling
	std::string myToken, myLexeme;

	// Instantiation of the Lexical Analyzer passing our loaded string as source
	LexicalAnalyzer LA(SOURCE); // Instantiate Lexical Analyzer object with source code string

	// instantiate and initialize EOF flag
	bool isEOF{ false };

	SyntaxAnalyzer SA;
	std::vector<std::pair<std::string, std::string>> tokenLexemeList;
	// while not end of file, analyze source
	while (!isEOF)
	{
		// set EOF based on each call to Analyzer
		isEOF = LA.Lexer(myToken, myLexeme);


		// if the tokens are empty don't bother
		if (myToken.empty() || myLexeme.empty())
		{

		}		
		else// otherwise append to the output string also syntax analyze it
		{
			tokenLexemeList.push_back(std::pair<std::string, std::string>{ myToken, myLexeme });
			// todo analyze token and lexeme5 u
			formattedOutputString.append("\n" + myToken + "\t\t" + myLexeme);
			std::pair<std::string, std::string>tempPair{ "#", "#"};
			SA.A(tempPair);
		}
	}
#pragma region Stream Output

	// check for file output filename arg
	if (ConfirmOutputArgSuccess(argc))
	{
		try // Try outputting results to stream
		{
			// if the arg exists use it
			if (isSourceOutputSuccess = OutputResultData(formattedOutputString, argv[2])) {}

		}
		catch (const std::exception&)
		{
			std::cout << "Error Outputting Results to Stream..." << std::endl;
		}
	}

	// else use the default file output name
	else
	{
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
	bool openedSuccess{ false };
	if (openedSuccess = fBuffer.open(fileName, std::ios::in))
	{
		std::istream is(&fBuffer);
		while (is)
			sourceStringRef.push_back(char(is.get()));
		fBuffer.close();
	}
	return openedSuccess;
}

// output file results to file
bool OutputResultData(std::string outString, std::string outFilename = "output.RAT12F")
{
	std::filebuf outStream; // see the filebuff is local in this function but passed in in the input version. I can remove the input version's param i think and make it local
	bool openedSuccess{ false };
	if (openedSuccess = outStream.open(outFilename, std::ios::out))
	{
		std::ostream os(&outStream);
		os << outString;
		outStream.close();
		return true;
	}
	return false;
}

#pragma endregion // END file i/o function region