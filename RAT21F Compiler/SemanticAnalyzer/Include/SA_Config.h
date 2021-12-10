#pragma once

namespace SA_cfg
{
	/* Use these defines to toggle different modes of output text*/
	// There are two pairs of toggles, one for Printing Non-Termainals on function call entry
	// the other is to print the rull as it is accepted at the deepest nest of the function.
	// both can be on at the same time and both have a verbose option
	// the verbose option requires the both of the #define in the pair to be active
	// ******************************************************************************************

	//************************* Print Rule When Calling Function **********************************
#ifndef PRINT_RULE_ON_CALL
//#define PRINT_RULE_ON_CALL // Comment out ths line to turn off
#endif
// **********************************************************************************************


//************************* Print Rule When Calling Function Verbose ****************************
#ifndef VERBOSE_PRINT_RULE_ON_CALL	// Both modes must be defined for Verbose to work
//#define VERBOSE_PRINT_RULE_ON_CALL  // Comment out ths line to turn off	
#endif
// **********************************************************************************************


//************************* Print Rule if Accepted **********************************************
#ifndef PRINT_RULE_ON_ACCEPT
//#define PRINT_RULE_ON_ACCEPT
#endif
// **********************************************************************************************


//************************* Print Rule if Accepted Verbose *************************************
#ifndef VERBOSE_PRINT_RULE_ON_ACCEPT	// Both modes must be defined for Verbose to work
//#define VERBOSE_PRINT_RULE_ON_ACCEPT	// Comment out ths line to turn off
#endif
// **********************************************************************************************


//************************* Print Rule if Rejected ************************************************
#ifndef PRINT_RULE_ON_REJECT
//#define PRINT_RULE_ON_REJECT
#endif
// **********************************************************************************************


//************************* Print Rule if Rejected Verbose ****************************************
#ifndef VERBOSE_PRINT_RULE_ON_REJECT	// Both modes must be defined for Verbose to work
//#define VERBOSE_PRINT_RULE_ON_REJECT	// Comment out ths line to turn off
#endif
// **********************************************************************************************


//************************* Print Symbols when Recognized ****************************************
#ifndef PRINT_RECOGNIZE_LABEL
//#define PRINT_RECOGNIZE_LABEL	// Comment out ths line to turn off
#endif // !PRINT_RECOGNIZE_LABEL
// **********************************************************************************************


//************************* Print Rules Abstractly  (<A>, <B>, <C>) *****************************
#ifndef ABBREVIATED_MODE
#define ABBREVIATED_MODE		// Comment out ths line to turn off
#endif // !ABBREVIATED_MODE
// **********************************************************************************************


//*************************  Slow Down Print Output  ********************************************
#ifndef SLOW_MODE
//#define SLOW_MODE		// Comment out ths line to turn off
#endif // !SLOW_MODE
// **********************************************************************************************


// ********************** Print in Color *******************************************************
#ifndef COLOR_MODE
#define COLOR_MODE		// Comment out ths line to turn off
#endif // !COLOR_MODE
// **********************************************************************************************

#ifndef PRINT_SOURCE
//#define PRINT_SOURCE
#endif // !PRINT_SOURCE


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! DO NOT EDIT #DEFINES BELOW !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#pragma region Do Not Edit This Region
#ifdef _WIN32
#include <windows.h>
#include <wincon.h>

#ifdef SLOW_MODE
	int slowModeSpeed{ 1000 };			// milliseconds between printing lines
	void mySleep(unsigned milliseconds)
	{
		Sleep(milliseconds);
	}
#endif
#ifdef COLOR_MODE
	enum COLOR
	{
		black = 0,
		dark_blue = 1,
		dark_green = 2,
		dark_aqua, dark_cyan = 3,
		dark_red = 4,
		dark_purple = 5, dark_pink = 5, dark_magenta = 5,
		dark_yellow = 6,
		dark_white = 7,
		gray = 8,
		blue = 9,
		green = 10,
		aqua = 11, cyan = 11,
		red = 12,
		purple = 13, pink = 13, magenta = 13,
		yellow = 14,
		white = 15
	};
	COLOR TRYING_COLOR{ COLOR::dark_yellow };
	COLOR RECOGNIZED_COLOR{ COLOR::aqua };
	COLOR ACCEPTED_COLOR{ COLOR::dark_aqua };
	COLOR REJECTED_COLOR{ COLOR::red };
	COLOR SUCCESS_COLOR{ COLOR::green };
#endif
#else
#include <unistd.h>

	void sleep(unsigned milliseconds)
	{
		usleep(milliseconds * 1000); // takes microseconds
	}
#endif
#pragma endregion
#pragma region	DO NOT CHANGE THESE VALUES
	/***********************************************************************************************************************/
	// !!! Do not change the settings in this block !!!
#ifndef PRINT_RULE_ON_CALL				// Verbose only works when PRINT_RULE_ON_CALL is also defined
#ifdef VERBOSE_PRINT_RULE_ON_CALL
#undef VERBOSE_PRINT_RULE_ON_CALL
#endif
#endif // !PRINT_RULE_ON_CALL

/***********************************************************************************************************************/

/***********************************************************************************************************************/
// !!! Do not change the settings in this block !!!
#ifndef PRINT_RULE_ON_ACCEPT				// Verbose only works when PRINT_RULE_ON_ACCEPT is also defined
#ifdef VERBOSE_PRINT_RULE_ON_ACCEPT
#undef PRINT_RULE_ON_ACCEPT
#endif
#endif // VERBOSE_PRINT_RULE_ON_ACCEPT
/***********************************************************************************************************************/
#pragma endregion
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ DO NOT EDIT #DEFINES ABOVE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


}