#include <iostream>
using namespace std;

#include "NumberWithUncertainty.h"
#include "LabCSVStripper.h"
std::ostream &operator<<(std::ostream &os, NumberWithUncertainty const &m)
{
    return os << m.asString();
}
int main(int argc, char *argv[])
{
    std::map<std::string, NumberWithUncertainty> mappy;
    LabCSVStripper stripper = LabCSVStripper("labdata.csv");
    int n = stripper.streamLen();
    stripper.initFile("muk");
    for (unsigned int i = 1; i < n; i++)
    {
        mappy = stripper.readLine(i);
        std::cout << NumberWithUncertainty::cosInDeg(mappy["theta"])<< '\n';
        mappy["muk"] = (mappy["m2"]*9.8 - mappy["m1"]*NumberWithUncertainty::sinInDeg(mappy["theta"])*9.8-mappy["a"]*(mappy["m1"]+ mappy["m2"]))/(mappy["m1"]*NumberWithUncertainty::cosInDeg(mappy["theta"])*9.8);
        stripper.WriteLine("muk", mappy);
    }
    
}
