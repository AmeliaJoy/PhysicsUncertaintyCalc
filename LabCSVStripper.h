#ifndef LABCSVSTRIPPER_H
#define LABCSVSTRIPPER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

#include "NumberWithUncertainty.h"
class LabCSVStripper
{
    public:
        std::vector<std::string> headers;
        
        LabCSVStripper(std::string filename);
        std::map<std::string, NumberWithUncertainty> readLine(int line);
        int streamLen();
        void WriteLine(std::string resultColumn, std::map<std::string, NumberWithUncertainty> mappy);
        void initFile(std::string resultName);
        };
#endif