
#include "Tests.h"
#include "GaloisApp.h"
#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "MersenneTwister.h"

#include <iostream>
using namespace std;

void Recode(GaloisElemVV& _factors, GaloisElemV factor)
{
	cout << "Recode(GaloisElemVV& in_cache, const GaloisElemV new_come)" << endl;
	MTRand CodingCoefficient;
	int x = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem a(&gf, x);
	int y = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem b(&gf, x);

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
/*
void Recode(GaloisElemV& _factors, GaloisElemV factor)
{
	cout << "Recode(GaloisElemV& in_cache, const GaloisElemV new_come)" << endl;
	MTRand CodingCoefficient;
	int x = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem a(&gf, x);
	int y = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem b(&gf, x);

	for(GaloisElemV::iterator it_vv = _factors.begin();it_vv != _factors.end(); it_vv++)
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

}*/

void TestReCode()
{
	cout << " TestReCode1()" << endl;
	GaloisElemVV _already_have;
	GaloisElemV _new_come = generateRandomNC(10);
	_already_have.clear();
	for(int i = 0; i< 1; i ++)
	{
		_already_have.push_back(generateRandomNC(10));
	}
	GaloisElemVV null_gevv;
	if(independenceMulti(null_gevv, _new_come))
	{
		cout << "null_gevv independenceMulti" << endl;
	}else{
		cout << "null_gevv not independenceMulti" << endl;
	}
	if(independenceMulti(_already_have, _new_come))
	{
		cout << "independenceMulti at first" << endl;
	}else{
		cout << "not independenceMulti at first" << endl;
	}
	Recode(_already_have, _new_come);

	if(independenceMulti(_already_have, _new_come))
	{
		cout << "independenceMulti after recode" << endl;
	}else{
		cout << "not independenceMulti after recode" << endl;
	}

}
/*
void TestReCode2()
{
	cout << " TestReCode2()" << endl;
	GaloisElemVV _already_have;
	GaloisElemV _new_come = generateRandomNC(10);
	_already_have.clear();
	for(int i = 0; i< 1; i ++)
	{
		_already_have.push_back(generateRandomNC(10));
	}
	GaloisElemVV null_gevv;
	if(independenceMulti(null_gevv, _new_come))
	{
		cout << "null_gevv independenceMulti" << endl;
	}else{
		cout << "null_gevv not independenceMulti" << endl;
	}
	if(independenceMulti(_already_have, _new_come))
	{
		cout << "independenceMulti at first" << endl;
	}else{
		cout << "not independenceMulti at first" << endl;
	}
	Recode(_already_have, _new_come);

	if(independenceMulti(_already_have, _new_come))
	{
		cout << "independenceMulti after recode" << endl;
	}else{
		cout << "not independenceMulti after recode" << endl;
	}

}*/