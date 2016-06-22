#pragma once

#include <iostream>

using namespace std;

template <typename T>
class Range
{
public:
	Range():isSet(false){}
	Range(const T& minValue, const T& maxValue):isSet(true),itsMinValue(minValue),itsMaxValue(maxValue)
	{
		if (itsMinValue > itsMaxValue)
			std::swap(itsMinValue,itsMaxValue);
	}
	T Max() const {	return itsMaxValue; }
	T Min() const{ return itsMinValue; }
	bool IsInRange(const T& value) const
	{
		if(!isSet) return true; // not set, pass
		if(value >= itsMinValue && value <= itsMaxValue) 
			return true;
		else 
			return false;
	}
private:
	T itsMinValue;
	T itsMaxValue;
	bool isSet;
};

template <typename T>
bool operator==(const Range<T>& lhs,const Range<T>& rhs)  
{
	return lhs.Min() == rhs.Min() && lhs.Max() == rhs.Max();
}

template <typename T>
ostream& operator<<(ostream& o,const Range<T>& rhs)
{
	o << "Min: " << rhs.Min() << " \t Max: " << rhs.Max();
	return o;
}