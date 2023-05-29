#ifndef SHOWTEXT_H
#define SHOWTEXT_H

#include <iostream>
#include <fstream>

#include <string.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <array>
#include "ConstValues.h"
#include "OtherFunctions.h"

extern ConstValues CV;

std::vector<std::string> showOptions(int caseNum);
void printOptions(std::string tp, int &type, bool &skip, std::vector<std::string> &acceptableValues);

void showHelp (int caseNum);

void synopsis();
void casualtyReport(std::array<int,5> troopsLost, std::array<int,5> injuredTroops);

void printFile (std::string fileName);

void scoutLogFunction ();

char getOption (int caseNum);


#endif






