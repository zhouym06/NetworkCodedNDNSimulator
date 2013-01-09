#ifndef __TESTS_H__
#define __TESTS_H__


void TestReCode();
void TestReCode2();

void LinearTopoTest();
void SimpleLinearTopoTest();
void TreeTopoTest();
void SimpleTreeTopoTest();
void LinearCacheFigure1();		//for cache without k
void TreeCacheFigure1();		//for cache without k
void TestUniformLinear();
void TestUniformTree();


extern int request_num;
extern int content_num_s[1];
extern int content_num_l;
extern int slice_per_content_s[1];
extern int slice_per_content_l;

extern int k_s[10];
extern int k_l	;
extern int len;
extern int level;
extern int tree_degree;

#endif