
#include "Tree.h"

int Tree::GetTreeLevel(int treeDegree,int routerID)
{
	int sum = 0;
	int levelNum = 1;
	int level;
	for(level = 0; routerID > sum; level++)
	{
		levelNum *= treeDegree;
		sum += levelNum;
	}
	return level;
}
int Tree::GetTreeNodeNum(int treeDegree,int treeLevel)
{
	int sum = 0;
	int levelNum = 1;
	for(int i = 0; i < treeLevel;i++)
	{
		sum += levelNum;
		levelNum *= treeDegree;
	}
	return sum;
}
int Tree::GetTreeLevelSize(int treeDegree,int treeLevel)
{
	int levelSize = 1;
	for(int i = 0; i < treeLevel;i++)
	{
		levelSize *= treeDegree;
	}
	return levelSize;
}
int Tree::GetParentIndex(int treeDegree,int treeLevel, int routerID)
{
	int parent = (int)((routerID - 0.1)/treeDegree);
	return parent;
}
