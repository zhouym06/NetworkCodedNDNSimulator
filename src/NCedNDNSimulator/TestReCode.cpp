
#include "Tests.h"
#include "GaloisApp.h"
#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "MersenneTwister.h"

#include <iostream>
using namespace std;


bool ContainsOther(GaloisElemVV cache, GaloisElemVV already_have_factors);



void Recode(GaloisElemVV& _factors, GaloisElemV factor)
{
	cout << "Recode(GaloisElemVV& in_cache, const GaloisElemV new_come)" << endl;
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

void Recode(GaloisElemV& des, GaloisElemV src)
{
	//cout << "Recode(GaloisElemV& in_cache, const GaloisElemV new_come)" << endl;
	MTRand CodingCoefficient;
	int x = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem a(&gf, x);
	int y = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
	GaloisElem b(&gf, y);
	
	GaloisElemV::iterator it_des = des.begin();
	GaloisElemV::iterator it_src = src.begin();
	for(;it_des != des.end(); )
	{	
		
		(*it_des)	*= a;
		b		*= (*it_src);
		(*it_des) += b;

		it_des++;
		it_src++;
	}

}

void TestReCode()
{
	
	cout << " TestReCode()" << endl;
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

void TestReCode2()
{
	cout << " TestReCode2()" << endl;
	GaloisElemVV vv;
	GaloisElemV _x = generateRandomNC(8);
	GaloisElemV square_x = _x;
	Recode(square_x,square_x);

	vv.clear();
	vv.push_back(square_x);

	if(independenceMulti(vv, _x))
	{
		cout << "square_a independenceMulti" << endl;
	}else{
		cout << "square_a not independenceMulti" << endl;
	}

}

void TestReCode3()
{
	cout << " TestReCode3()" << endl;
	GaloisElemVV vv;
	GaloisElemV _x1 = generateRandomNC(8);
	GaloisElemV _x2 = _x1;
	GaloisElemV _y = generateRandomNC(8);

	
	Recode(_x1,_y);
	Recode(_x2,_y);

	vv.clear();
	vv.push_back(_x1);

	if(independenceMulti(vv, _x2))
	{
		cout << "Recode independenceMulti" << endl;
	}else{
		cout << "Recode not independenceMulti" << endl;
	}

}



void TestReCode4()
{

	cout << " TestReCode4()" << endl;
	GaloisElemVV vv;
	GaloisElemV _x1 = generateRandomNC(8);

	vv.push_back(_x1);
	vv.push_back(_x1);

	cout << gaussElimination(vv) << endl;
}


bool ContainsOther(GaloisElemVV cache, GaloisElemVV already_have_factors)
{
	for(GaloisElemVV::iterator c_it = cache.begin(); c_it != cache.end(); c_it++)
	{
		if(independenceMulti(already_have_factors, *c_it) == 1)
			return true;
	}
	return false;
}

void TestReCode5()
{

	cout << " TestReCode4()" << endl;
	GaloisElemVV vv;
	GaloisElemV x1 = generateRandomNC(8);
	GaloisElemV x2 = generateRandomNC(8);

	GaloisElemVV c1v;
	GaloisElemVV sink;

	c1v.push_back(x1);
	sink.push_back(x1);

	Recode(c1v,x2);

	sink.push_back(x2);

	if(ContainsOther(c1v, sink))
		cout << "ContainsOther(c1v, sink)" << endl;
	else
		cout << "Doesn't ContainsOther(c1v, sink)" << endl;

}
