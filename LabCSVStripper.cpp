#include "LabCSVStripper.h"
LabCSVStripper::LabCSVStripper(std::string filename)
{
    
    std::string headerStr;
    std::ifstream toRead;
    toRead = std::ifstream(filename);
    getline(toRead,headerStr);

    std::stringstream ss(headerStr);
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        headers.push_back(substr);
    }
    toRead.close();
}
int LabCSVStripper::streamLen()
{
    std::ifstream toRead;
    std::string test;
    int linenum = 0;
    toRead = std::ifstream("labdata.csv");
    while(toRead.good())
    {
        getline(toRead,test);
        linenum++;
    }
    toRead.close();
    return linenum;
}
std::map<std::string, NumberWithUncertainty> LabCSVStripper::readLine(int line)
{
    std::ifstream toRead;
    toRead = std::ifstream("labdata.csv");
    std::map<std::string,NumberWithUncertainty> mapToReturn;
    int index = 0;
    std::string data;
    for(index = 0; index <= line; index++)
    {
        if (toRead.good())
        {
            getline(toRead,data);
        }
    }
    std::stringstream ss(data);
    int head = 0;
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        NumberWithUncertainty temp = NumberWithUncertainty(substr);
        mapToReturn[headers[head]] = temp;
        head++;
    }
    toRead.close();
    return mapToReturn;
}
void LabCSVStripper::initFile(std::string resultName){   
    std::ofstream MyFile("labCalcs.csv");
    int n = headers.size();
    for (unsigned int i = 0; i < n; i++)
    {
       MyFile << headers[i] << ',';
    }
    MyFile << resultName << '\n';
        MyFile.close();
}
void LabCSVStripper::WriteLine(std::string resultColumn, std::map<std::string, NumberWithUncertainty> mappy)
{   
    std::ofstream MyFile("labCalcs.csv", std::ios_base::app);
    int n = headers.size();
    for (unsigned int i = 0; i < n; i++)
    {
       MyFile << mappy[headers[i]].asString() << ',';
    }
    MyFile << mappy[resultColumn].asString() << '\n';
    MyFile.close();
}