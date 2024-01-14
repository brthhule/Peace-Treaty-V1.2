//Shortens down absolute file paths for easy formatting
#ifndef FILEPATHS_H
#define FILEPATHS_H


//Fun stuff
#define print(x) std::cout << x;
#define println(x) std::cout << x << "\n";

//Types
#define INTEGER_
#define STRING_
#define void_
#define BOOL_
#define ARRAY_
#define TYPE_

//#define DEBUGGING_MODE

#ifndef DEBUGGING_MODE
#define DEBUG_FUNCTION(x, y) std::cout << "\033[35mFile: " << x << ", Method: " << y << " \033[0m\n";
#else
#define DEBUG_FUNCTION(x, y)
#endif
//MainActions Folder
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths\MainActions\MainActions_Paths.h"

//Misc Folder
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths\Misc\Misc_Paths.h"

//Units Folder
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths\Units\Units_Paths.h"

#endif