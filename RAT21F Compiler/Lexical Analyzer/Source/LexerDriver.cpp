#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include "../Include/Utility/SourceStripper.hpp"


bool LoadInputFile(std::filebuf&, std::string);
bool OutputResultData(std::filebuf&, std::string);

std::string SOURCE{ "This is my \n Source \n\nCode. Thre are a few lines\n in it" };
std::filebuf inStream;
std::filebuf outStream;
//std::ostream outStream;

bool isSourceInputSuccess{ false };
bool isSourceOutputSuccess{ false };

int main()
{	
#pragma region Stream Input
	//try // Try loading input source stream
	//{
	//	if (isSourceInputSuccess = LoadInputFile(inStream, "test.txt")){}
	//}
	//catch (const std::exception&)
	//{
	//	std::cout << "Error Loading Input File..." << std::endl;
	//}
#pragma endregion

#pragma region Lexical Analysis
	// TODO implement Lexer here
#pragma endregion

#pragma region Stream Output
	try // Try outputting results to stream
	{
		if (isSourceOutputSuccess = OutputResultData(outStream, "FilenameParam.RAT21F")){}
	}
	catch (const std::exception&)
	{
		std::cout << "Error Outputting Results to Stream..." << std::endl;
	}
#pragma endregion

	return 0;
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
bool OutputResultData(std::filebuf& outStream, std::string outFilename = "output.RAT12F")
{
	bool openedSuccess{ false };
	if (openedSuccess = outStream.open(outFilename, std::ios::out))
	{
		std::ostream os(&outStream);
		os << "Test sentence\n";
		outStream.close();
		return true;
	}
	return false;
}