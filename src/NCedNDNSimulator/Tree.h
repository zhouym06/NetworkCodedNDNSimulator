#ifndef __TREE_H___
#define __TREE_H___

class Tree
{
public:
	static int GetTreeLevel(int treeDegree,int routerID);
	static int GetTreeNodeNum(int treeDegree,int treeLevel);
	static int GetTreeLevelSize(int treeDegree,int treeLevel);
	static int GetParentIndex(int treeDegree,int treeLevel, int routerID);
};
#endif