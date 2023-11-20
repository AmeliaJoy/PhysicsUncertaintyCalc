#ifndef NUMBERWITHUNCERTAINTY_H
#define NUMBERWITHUNCERTAINTY_H
#include "math.h"
#include <iostream>
class NumberWithUncertainty
{
    private:
        double value;
        double uncertainty;
    public:
        NumberWithUncertainty(double value, double uncertainty);
        NumberWithUncertainty(std::string rawVal);
        NumberWithUncertainty();
        void set(double value, double uncertainty);
        void set(std::string rawVal);
        static NumberWithUncertainty cosInDeg(NumberWithUncertainty& theta);
        static NumberWithUncertainty sinInDeg(NumberWithUncertainty& theta);
        NumberWithUncertainty operator * (const NumberWithUncertainty &obj);
        NumberWithUncertainty operator * (double constantMultiplier);
        NumberWithUncertainty operator + (const NumberWithUncertainty &obj);
        NumberWithUncertainty operator - (const NumberWithUncertainty &obj);
        NumberWithUncertainty operator / (const NumberWithUncertainty &obj);
        NumberWithUncertainty operator / (double divisor);
        static std::string cleanString(std::string toClean);
        std::string  asString() const;
};
#endif