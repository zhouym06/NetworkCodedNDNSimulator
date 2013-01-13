#include "GaloisApp.h"
#include "MersenneTwister.h"
#include <iostream>
using namespace std;

unsigned int prim_poly[9] = {1,1,1,0,0,0,0,1,1};
galois::GaloisField gf(8,prim_poly);


int rank(GaloisElemVV checkList){
	int i,j,p,q,k;

	const int m=checkList.size(), n=checkList[0].size();
	i=0; j=0;

	while(i<m && j<n){
		GaloisElem maxVal=checkList[i][j];
		int maxInd=i;
		if(maxVal == 0){
			for(k=i+1; k<m; k++){
				GaloisElem val=checkList[k][j];
				if(val>maxVal){	maxVal=val;	maxInd=k; break; }
			}
		}
		if(maxVal != 0){
			if(maxInd != i){
				GaloisElemVV temp;
				temp.push_back(checkList[i]);
				temp.push_back(checkList[maxInd]);

				for(p=0; p<n; p++){
					checkList[maxInd][p]=temp[0][p];
					checkList[i][p]=temp[1][p];
				}
			}
			for(q=i+1; q<m; q++){
				GaloisElem toto=checkList[q][j];
				for(p=j; p<n; p++){
					GaloisElem tata=checkList[q][p];
					checkList[q][p]=tata-toto*checkList[i][p]/checkList[i][j];
				}
			}
			i++;
		}
		j++;
	}

	int rank=0;
	for(i=0; i<m; i++) for(j=0; j<n; j++){
		if(checkList[i][j]!=0){	rank++;	break; }
	}
	return rank;
}
int gaussElimination(GaloisElemVV checkList){
	
	if(rank(checkList)==checkList.size()) return 1;
	return 0;
}
int independenceIntra(int layerNumb, GaloisElemVV *listVV, GaloisElemV elemVect){
	int maxDimen = 0;
	GaloisElemVV checkList;

	for(int i=layerNumb-1; i>=0; i--){
		if(listVV[i].size()!=0){
			maxDimen=listVV[i][0].size();
			break;
		}
	}
	if(maxDimen<elemVect.size()) maxDimen=elemVect.size();

	GaloisElem tZero(&gf, 0);

	for(int i=0; i<layerNumb; i++){
		for(int j=0; j<listVV[i].size(); j++){
			GaloisElemV ansV;
			for(int k=0; k<listVV[i][j].size(); k++) ansV.push_back(listVV[i][j][k]);
			for(int k=0; k<maxDimen-listVV[i][j].size(); k++) ansV.push_back(tZero);
			checkList.push_back(ansV);
		}
	}

	GaloisElemV ansV;
	for(int k=0; k<elemVect.size(); k++) ansV.push_back(elemVect[k]);
	for(int k=0; k<maxDimen-elemVect.size(); k++) ansV.push_back(tZero);
	checkList.push_back(ansV);

	return gaussElimination(checkList);
}
int independenceMulti(GaloisElemVV listVV, GaloisElemV elemVect){
	if(listVV.size() == 0) return 1;

	GaloisElemVV checkList;

	for(int i=0; i<listVV.size(); i++){
		checkList.push_back(listVV[i]);
	}

	checkList.push_back(elemVect);

	return gaussElimination(checkList);
}

GaloisElemV generateRandomNC(int size){
	MTRand CodingCoefficient;
	GaloisElemV ansV;

	for(int i=0; i<size; i++){
		//double tompo = (double(rand())/RAND_MAX)*CodingSpace + 1;
		int x = CodingCoefficient.randInt(CodingSpace)+1;//int(tompo);
		
		GaloisElem y(&gf, x);
		ansV.push_back(y);
	}

	//std::cout<<"generateRandomNC over \n";
	return ansV;
}

GaloisElemV getIntraRandomChunk(int layer, bool isDecode, GaloisElemVV *listVV){ //返回若为空，表示没有该层数据
	GaloisElemV ansV;

	if(isDecode){
		for(int i=0; i<=layer; i++){
			GaloisElemV coef = generateRandomNC(listVV[i].size());

			for(int j=0; j<listVV[i][0].size(); j++){
				GaloisElem tata(&gf, 0);

				for(int k=0; k<listVV[i].size(); k++){
					tata=tata + coef[i]*listVV[i][k][j];
				}
				ansV.push_back(tata);
			}
		}
	}
	else{
		if(listVV[layer].size()>0){
			GaloisElemV coef = generateRandomNC(listVV[layer].size());

			for(int i=0; i<listVV[layer][0].size(); i++){
				GaloisElem tata(&gf, 0);

				for(int j=0; j<listVV[i].size(); j++){
					tata=tata+coef[j]*listVV[layer][j][i];
				}
				ansV.push_back(tata);
			}
		}
	}

	return ansV;
}

GaloisElemV getMultiRandomChunk(GaloisElemVV listV){
	GaloisElemV ansV;
	GaloisElemV coef = generateRandomNC(listV.size());

	for(int i=0; i<listV[0].size(); i++){
		GaloisElem tata(&gf, 0);

		//cout<<"tata = "<<tata<<" ";
		for(int j=0; j < listV.size(); j++) 
			tata = tata+coef[j]*listV[j][i];
		ansV.push_back(tata);
	}
	//cout<<endl;
	
	return ansV;
}