#ifndef __GALOISAPP_H__
#define __GALOISAPP_H__

#include <vector>
#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "GaloisFieldPolynomial.h"
//#include "GeneratorPolynomialCreator.h"
#include <time.h>

#define CodingSpace 254

extern unsigned int prim_poly[9];
extern galois::GaloisField gf;

typedef galois::GaloisFieldElement GaloisElem;
typedef std::vector<GaloisElem> GaloisElemV;
typedef std::vector< GaloisElemV > GaloisElemVV;

int rank(GaloisElemVV checkList);
int gaussElimination(GaloisElemVV checkList);   //if independence return 1, else return 0
int independenceIntra(int layerNumb, GaloisElemVV *listVV, GaloisElemV elemVect);  //�ж�elemVect��listVV�Ƿ����Զ���,ά�ȿ��ܲ�һ��
int independenceMulti(GaloisElemVV listVV, GaloisElemV elemVect);  //ά��һ��

GaloisElemV generateRandomNC(int size);     //����һ��ά��Ϊsize��Galois����
GaloisElemV getIntraRandomChunk(int layer, bool isDecode, GaloisElemVV *listVV); //������Ϊ�գ���ʾû�иò�����
GaloisElemV getMultiRandomChunk(GaloisElemVV listV);  

#endif