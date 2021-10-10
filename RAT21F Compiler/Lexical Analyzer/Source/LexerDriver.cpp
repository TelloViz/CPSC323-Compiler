#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include "../Include/Utility/SourceStripper.hpp"
#include "../Include/LexicalAnalyzer.h"

#define DEBUG_ON

#pragma region File IO Function Signatures
void ECHO_CLI_ARGS(int argc, char** argv);
bool ConfirmInputArgSuccess(int argCount);
bool ConfirmOutputArgSuccess(int argCount);
bool LoadInputFile(std::filebuf&, std::string, std::string&);
bool OutputResultData(std::string, std::filebuf&, std::string);
#pragma endregion




int main(int argc, char** argv)
{
#pragma region Init CLI arg and stream data
	std::string SOURCE{ "This is my \n Source \n\nCode. Thre are a few lines\n in it" };
	std::string formattedOutputString
	{
		"Token\t\tLexeme\n" \
		"------------------\n"
	};

	std::filebuf inStream;
	std::filebuf outStream;


	bool isSourceInputSuccess{ false };
	bool isSourceOutputSuccess{ false };
	bool is_CLI_Input_Arg{ false };
	bool is_CLI_Output_Arg{ false };
#pragma endregion	

#pragma region DEBUG Code
#ifdef DEBUG_ON
	ECHO_CLI_ARGS(argc, argv);
#endif // DEBUG_ON
#pragma endregion

#pragma region Stream Input
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
#pragma endregion

#pragma region Lexical Analysis
	LexicalAnalyzer LA(SOURCE); // Instantiate Lexical Analyzer object with source code string
	LexicalUnit lexUnit;
	
	while (LA.Lexer(lexUnit))
	{
		formattedOutputString.append("\n" + lexUnit.sToken + "\t\t" + lexUnit.sLexeme);
	}
#pragma endregion

#pragma region Stream Output
	if (ConfirmOutputArgSuccess(argc))
	{
		try // Try outputting results to stream
		{
			if (isSourceOutputSuccess = OutputResultData(formattedOutputString,outStream, argv[2])) {}
		}
		catch (const std::exception&)
		{
			std::cout << "Error Outputting Results to Stream..." << std::endl;
		}
	}
#pragma endregion

	return 0;
}

#pragma region FILE IO FUNCTIONS
void ECHO_CLI_ARGS(int argc, char** argv)
{
	std::cout << "You have entered " << argc
		<< " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		std::cout << argv[i] << "\n";
}
bool ConfirmInputArgSuccess(int argCount)
{
	return argCount >= 2; // True means that there are at least the [0] arg (this exe), and the [1] arg which is input filename
}
bool ConfirmOutputArgSuccess(int argCount)
{
	return argCount >= 3; // True means there are at least 3 args, the 3rd being the output filepath. Ignore any args past 3.
}
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
bool OutputResultData(std::string outString, std::filebuf& outStream, std::string outFilename = "output.RAT12F")
{
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
#pragma endregion
