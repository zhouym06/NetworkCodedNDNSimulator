

#include "NCContentElement.h"
#include "Logger.h"

#include "GaloisApp.h"
#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "MersenneTwister.h"

#include <iostream>

NCContentElement::NCContentElement(int content_no, GaloisElemV factor)
{
	_content_no		= content_no;
	_factors.clear();
	_factors.push_back(factor);
}
NCContentElement::NCContentElement(int content_no, GaloisElemVV factors)
{
	_content_no		= content_no;
	_factors		= factors;
}

void NCContentElement::AddNew(int content_no, GaloisElemV factor)
{
	if(_content_no != content_no)
	{
		Logger::Log(LOGGER_ERROR) << "ERROR!:NCContentElement::AddNew(int content_no, GaloisElemV factor): content no dismatch" << content_no << endl;
	}
	_factors.push_back(factor);
	Recode(factor);

}

void NCContentElement::Recode(GaloisElemV factor)
{
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCContentElement::Recode(GaloisElemV factor)" << endl;
	MTRand CodingCoefficient;
	int x = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem a(&gf, x);
	int y = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem b(&gf, y);

	for(GaloisElemVV::iterator it_vv = _factors.begin();it_vv != _factors.end(); it_vv++)
	{
		GaloisElemV::iterator it_f = factor.begin();
		for(GaloisElemV::iterator it_v = it_vv->begin(); it_v != it_vv->end(); it_v++)
		{
			(*it_v)	*= a;
			b		*= (*it_f);
			(*it_v) += b;
			it_f++;
		}
	}
}

bool NCContentElement::RemoveLast()
{
	if(_factors.size() <= 1)
	{
		_factors.clear();
		return true;
	}
	_factors.pop_back();
	return false;

}