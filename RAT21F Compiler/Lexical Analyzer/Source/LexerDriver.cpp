#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include "../Include/Utility/SourceStripper.hpp"

#define DEBUG_ON

void ECHO_CLI_ARGS(int argc, char** argv);
bool ConfirmInputArgSuccess(int argCount);
bool ConfirmOutputArgSuccess(int argCount);
bool LoadInputFile(std::filebuf&, std::string);
bool OutputResultData(std::string, std::filebuf&, std::string );



int main(int argc, char** argv)
{
#pragma region Init CLI arg and stream data
	std::string SOURCE{ "This is my \n Source \n\nCode. Thre are a few lines\n in it" };
	std::string formattedOutputString{ "This is placeholder text for the actual outputted token/lexeme pair table" };
	std::filebuf inStream;
	std::filebuf outStream;


	bool isSourceInputSuccess{ false };
	bool isSourceOutputSuccess{ false };
	bool is_CLI_Input_Arg{ false };
	bool is_CLI_Output_Arg{ false };
#pragma endregion	

#ifdef DEBUG_ON
	ECHO_CLI_ARGS(argc, argv);
#endif // DEBUG_ON

#pragma region Stream Input
	if (ConfirmInputArgSuccess(argc))
	{
		try // Try loading input source stream
		{
			if (isSourceInputSuccess = LoadInputFile(inStream, "test.txt")) {}
		}
		catch (const std::exception&)
		{
			std::cout << "Error Loading Input File..." << std::endl;
		}
	}
#pragma endregion

#pragma region Lexical Analysis
	// TODO implement Lexer here
#pragma endregion

#pragma region Stream Output
	if (ConfirmOutputArgSuccess(argc))
	{
		try // Try outputting results to stream
		{
			if (isSourceOutputSuccess = OutputResultData(formattedOutputString,outStream, "FilenameParam.RAT21F")) {}
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
bool LoadInputFile(std::filebuf& fBuffer, std::string fileName)
{
	bool openedSuccess{ false };
	if (openedSuccess = fBuffer.open(fileName, std::ios::in))
	{
		std::istream is(&fBuffer);
		while (is)
			std::cout << char(is.get());
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
