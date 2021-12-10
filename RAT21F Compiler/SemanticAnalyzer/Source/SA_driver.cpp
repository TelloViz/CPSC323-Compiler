// main.cpp

// This is the driver file for the Semantic Analyzer.
// I modified the driver from project one to suit the needs of this project
// so not much here is new code.

// Author: Joshua Lollis
// Last Edited:12/6/21
// CPSC 323 James Choi, Fall 2021
// Assignment 2 Syntactical Analyzer


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Include/LexicalAnalyzer.h"
#include "../Include/SyntaxAnalyzer.h"
#include <list>

#include "../Include/CLI11.hpp"


#pragma region File IO Function Signatures
bool ConfirmInputArgSuccess(int argCount);
bool ConfirmOutputArgSuccess(int argCount);
bool LoadInputFile(std::filebuf&, std::string, std::string&);
bool OutputResultData(std::string, std::string);
#pragma endregion // End File IO function Signatures


#pragma region SA Functions

//bool Open_Syntax_Analyzer_Output_Stream(std::ofstream& outStream);
#pragma endregion

int main(int argc, char** argv)
{
#pragma region Init CLI arg and stream data
		
	// the source passed in from Command Line
	std::string SOURCE{};
	
	CLI::App cliApp{ "\n\nRAT21F Compiler" };

	std::string HELP_STRING{ "Print this help menu." };
	auto help = cliApp.set_help_flag("-h, --help", HELP_STRING);	
	
	std::string sourceFilename{};
	//auto inputOptionGroup = cliApp.add_option_group("Input File", "Input File Option.");
	//auto inputOption = inputOptionGroup->add_option("-i", sourceFilename, "Input Filename")->check(CLI::ExistingFile);

	auto testOpt = cliApp.add_option("-i", sourceFilename, "Input Filename")->check(CLI::ExistingFile)->required(true);

	//inputOptionGroup->require_option(1,1);

	std::string defaultLexicalOutputFileName{ "lexout.RAT21F" };
	std::string defaultSyntacticOutputFileName{ "synout.RAT21F" };
	std::string defaultSemanticOutputFileName{ "semout.RAT21F" };
	auto OutputFileOptionGroup = cliApp.add_option_group("Compiler File Output", "Output File Options.");
	auto lexFileOption = OutputFileOptionGroup->add_option("--ofLex", defaultLexicalOutputFileName, "Output Lexical Analysis to [TEXT].txt")->ignore_case();
	auto synFileOption = OutputFileOptionGroup->add_option("--ofSyn", defaultSyntacticOutputFileName, "Output Syntactic Analysis to [TEXT].txt")->ignore_case();
	auto semFileOption = OutputFileOptionGroup->add_option("--ofSem", defaultSemanticOutputFileName, "Output Semantic Analysis to [TEXT].txt")->ignore_case();
	OutputFileOptionGroup->require_option(0, 3);

	
	bool isLex2Console{ false };
	bool isSyn2Console{ false };
	bool isSem2Console{ false };
	auto printFlags = cliApp.add_option_group("Compiler Console Output", "For compilation console print flags");
	auto lexFlag = printFlags->add_flag("--lex", isLex2Console, "Print Lexical Analysis to console.")->ignore_case();
	auto synFlag = printFlags->add_flag("--syn", isSyn2Console, "Print Syntactic Analysis to console.")->ignore_case();
	auto semFlag = printFlags->add_flag("--sem", isSem2Console, "Print Semantic Analysis to console.")->ignore_case();
	printFlags->require_option(0, 3);


	bool shouldPrintLinedSource{};
	auto linedSourceFlag = cliApp.add_flag("-l", shouldPrintLinedSource, "Print lined source code to console.")->ignore_case();


	bool shouldPrintSource{};
	auto sourceFlag = cliApp.add_flag("-s", shouldPrintSource, "Print source code to console.")->ignore_case();

	//linedSourceFlag->excludes(sourceFlag);

	bool shouldPrintASM{};
	auto asmFlag = cliApp.add_flag("-a", shouldPrintASM, "Print assembly instruction set to console.");

	bool shouldPrintSymbols{};
	auto symbFlag = cliApp.add_flag("-t", shouldPrintSymbols, "Print symbol table to console.");

	cliApp.get_formatter()->column_width(40);

	try 
	{
		CLI11_PARSE(cliApp, argc, argv);		
	}
	catch (const CLI::Error& e)
	{
		std::cout << "Error in CLI parse" << std::endl;
	}


	// The pairs of Tokens/Lexemes as returned from the Lexer
	std::vector<std::pair<std::string, std::string>> tokenLexemeVec;


	// The string to output to file. Will append token/lexeme pairs to end
	std::string formattedOutputString
	{
		"Token\t\tLexeme\n" \
		"------------------\n"
	};

	


	// file buffer stream for loading file contents
	std::filebuf inStream;


	// flags to signal successfull file IO
	bool isSourceInputSuccess{ false };
	bool isSourceOutputSuccess{ false };

#pragma endregion	// End Init CLI arg and stream data

#pragma region Stream Input
	// check if input arg exists
	if (*testOpt/*inputOption*/) // This *inputOption is dereferencing a CLI::Option* which converts to a bool by documentation.
	{
		try // Try loading input source stream
		{
			if (isSourceInputSuccess = LoadInputFile(inStream, sourceFilename, SOURCE)) 
			{
				inStream.close();
			}
		}
		catch (const std::exception&)
		{
			std::cout << "Error Loading Input File..." << std::endl;
		}
	}

#pragma endregion // End Stream Input Region

#pragma region Lexical Analysis
	// strings for passing to lexer that will hold the lexical units on each calling
	std::string myToken, myLexeme;

	// Instantiation of the Lexical Analyzer passing our loaded string as source
	LexicalAnalyzer LA(SOURCE); // Instantiate Lexical Analyzer object with source code string

	if (shouldPrintSource)
	{
		std::cout << SOURCE;
	}	
	
	if (shouldPrintLinedSource)
	{
		LA.PrintLineNumberedSource();
	}

	// instantiate and initialize EOF flag
	bool isEOF{ false };
	
	// while not end of file, analyze source
	while (!isEOF)
	{
		// set EOF based on each call to Analyzer
		isEOF = LA.Lexer(myToken, myLexeme);

		// if the tokens are empty don't bother
		if (myToken.empty() || myLexeme.empty())
		{

		}		
		else// otherwise append to the output string
		{
			tokenLexemeVec.push_back(std::pair<std::string, std::string>{ myToken, myLexeme });

			formattedOutputString.append("\n" + myToken + "\t\t" + myLexeme);			
		}
	}
#pragma endregion

#pragma region Syntax Analysis


	std::string SA_outString;

	SyntaxAnalyzer SA(tokenLexemeVec, SA_outString);
	if (SA.Analyze())
	{
		if (shouldPrintASM)
		{
			SA.PrintGeneratedInstructions();
		}

		
		if (OutputResultData(SA_outString, std::string{ "Syntax_Analysis.txt" }))
		{

		}
	}

	if (shouldPrintSymbols)
	{
		SA.PrintSymbolTable();
	}
	
#pragma endregion

#pragma region Stream Output
	// check for file output filename arg
	if (ConfirmOutputArgSuccess(argc))
	{
		try // Try outputting results to stream
		{
			// if the arg exists use it
			if (isSourceOutputSuccess = OutputResultData(formattedOutputString, SOURCE)) {}

		}
		catch (const std::exception&)
		{
			std::cout << "Error Outputting Results to Stream..." << std::endl;
		}
	}
#pragma endregion // End Stream Output Region
	
	return 0;
}



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
bool OutputResultData(std::string outString, std::string outFilename)

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


//bool Open_Syntax_Analyzer_Output_Stream(std::string filename, std::string data)
//{
//	std::string filename{ "Syntax_Analysis_Results.txt" };
//	std::ofstream outStream{ filename };
//
//	std::filebuf outStream; // see the filebuff is local in this function but passed in in the input version. I can remove the input version's param i think and make it local
//	bool openedSuccess{ false };
//	if (openedSuccess = outStream.open(filename, std::ios::out))
//	{
//		std::ostream os(&outStream);
//		os << outString;
//		outStream.close();
//		return true;
//	}
//	return false;
//
//}

