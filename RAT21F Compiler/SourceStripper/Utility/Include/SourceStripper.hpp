#pragma once
#include <vector>
#include <string>

namespace Utility
{

     /*----------------------------------------------------------------------------------------
       split_string splits a string based on the provided delimiter parameter
       ----------------------------------------------------------------------------------------
       The function uses code pulled from Stack Overflow: https://stackoverflow.com/a/13172514
       ----------------------------------------------------------------------------------------*/
     std::vector<std::string> split_string(const std::string& str,
          const std::string& delimiter);
    


};
