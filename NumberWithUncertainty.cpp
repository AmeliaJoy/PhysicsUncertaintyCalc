#include "NumberWithUncertainty.h"
NumberWithUncertainty NumberWithUncertainty::cosInDeg(NumberWithUncertainty& theta)
{
    NumberWithUncertainty cosTheta;
    cosTheta.value = (cos(atan(1)/45*(theta.value + theta.uncertainty)) + cos(atan(1)/45*(theta.value - theta.uncertainty)))/2;
    cosTheta.uncertainty = (cos(atan(1)/45*(theta.value + theta.uncertainty)) - cos(atan(1)/45*(theta.value - theta.uncertainty)))/2;    
    return cosTheta;
}
NumberWithUncertainty NumberWithUncertainty::sinInDeg(NumberWithUncertainty& theta)
{
    NumberWithUncertainty sinTheta;
    sinTheta.value = (sin(atan(1)/45*(theta.value + theta.uncertainty)) + sin(atan(1)/45*(theta.value - theta.uncertainty)))/2;
    sinTheta.uncertainty = abs(sin(atan(1)/45*(theta.value + theta.uncertainty)) - sin(atan(1)/45*(theta.value - theta.uncertainty)))/2;    
    return sinTheta;
}
NumberWithUncertainty NumberWithUncertainty::operator * (const NumberWithUncertainty &obj) {
    NumberWithUncertainty temp;
    temp.value = value * obj.value;
    temp.uncertainty = (uncertainty/value + obj.uncertainty/obj.value)*value*obj.value;
    return temp;
}
NumberWithUncertainty NumberWithUncertainty::operator * (double constantMultiplier) {
    NumberWithUncertainty temp;
    temp.value = value * constantMultiplier;
    temp.uncertainty = uncertainty * constantMultiplier;
    return temp;
}
NumberWithUncertainty NumberWithUncertainty::operator + (const NumberWithUncertainty &obj)
{
    NumberWithUncertainty temp;
    temp.value = value + obj.value;
    temp.uncertainty = uncertainty + obj.uncertainty;
    return temp;
}
NumberWithUncertainty NumberWithUncertainty::operator - (const NumberWithUncertainty &obj)
{
    NumberWithUncertainty temp;
    temp.value = value - obj.value;
    temp.uncertainty = uncertainty + obj.uncertainty;
    return temp;
}
NumberWithUncertainty NumberWithUncertainty::operator / (const NumberWithUncertainty &obj) {
    NumberWithUncertainty temp;
    temp.value = value / obj.value;
    temp.uncertainty = (uncertainty/value + obj.uncertainty/obj.value)*value/obj.value;
    return temp;
}
NumberWithUncertainty NumberWithUncertainty::operator / (double divisor) {
    NumberWithUncertainty temp;
    temp.value = value / divisor;
    temp.uncertainty = uncertainty /divisor;
    return temp;
}
void NumberWithUncertainty::set(double value, double uncertainty)
{
    this->value = value;
    this->uncertainty = uncertainty;
}
NumberWithUncertainty::NumberWithUncertainty(double value, double uncertainty)
{
    this->value = value;
    this->uncertainty = uncertainty;
}
NumberWithUncertainty::NumberWithUncertainty()
{
    value = 0;
    uncertainty = 0;
}
std::string NumberWithUncertainty::cleanString(std::string toClean)
{
    int first = 0;
    int last = toClean.length()-1;
    bool finishLast = false;
    while(!isdigit(toClean.at(first)))
    {
        first++;
    }

    
    
    while(!finishLast)
    {
        if (last == 0) 
        {
            finishLast = true;
        }
        else
        {
            finishLast = !(!isdigit(toClean.at(last)) || toClean.at(last-1) == '^');
            if(!finishLast)
            {
                last--;
            }
        }       
    }

    std::string substring = toClean.substr(first,last-first+1);
    
    return substring;

}

NumberWithUncertainty::NumberWithUncertainty(std::string rawVal)
{
    value = 0;
    uncertainty  =  0;
    if(rawVal.find("+-") != -1)
    {
        value = stod(cleanString(rawVal.substr(0,rawVal.find("+-")+1)));
        uncertainty = stod(cleanString(rawVal.substr(rawVal.find("+-"),rawVal.length()-rawVal.find("+-"))));
    }
    else if(rawVal.find("±") != -1)
    {
        value = stod(cleanString(rawVal.substr(0,rawVal.find("±")+1)));
        uncertainty = stod(cleanString(rawVal.substr(rawVal.find("±"),rawVal.length()-rawVal.find("+-"))));
    }
}

void NumberWithUncertainty::set(std::string rawVal)
{
    value = 0;
    uncertainty  =  0;
    if(rawVal.find("+-") != -1)
    {
        value = stod(cleanString(rawVal.substr(0,rawVal.find("+-")+1)));
        uncertainty = stod(cleanString(rawVal.substr(rawVal.find("+-"),rawVal.length()-1-rawVal.find("+-"))));
    }
   
    else if(rawVal.find("±") != -1)
    {
        value = stod(cleanString(rawVal.substr(0,rawVal.find("±")+1)));
        uncertainty = stod(cleanString(rawVal.substr(rawVal.find("±"),rawVal.length()-1-rawVal.find("+-"))));
    }
}

std::string NumberWithUncertainty::asString() const
{
    return std::to_string(value) +  " ±  " + std::to_string(uncertainty);
}
