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
int independenceIntra(int layerNumb, GaloisElemVV *listVV, GaloisElemV elemVect);  //判断elemVect与listVV是否线性独立,维度可能不一样
int independenceMulti(GaloisElemVV listVV, GaloisElemV elemVect);  //维度一样

GaloisElemV generateRandomNC(int size);     //生成一个维度为size的Galois向量
GaloisElemV getIntraRandomChunk(int layer, bool isDecode, GaloisElemVV *listVV); //返回若为空，表示没有该层数据
GaloisElemV getMultiRandomChunk(GaloisElemVV listV);  

#endif