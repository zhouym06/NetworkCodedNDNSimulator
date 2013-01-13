#ifndef __TESTS_H__
#define __TESTS_H__


void TestReCode();
void TestReCode2();
void TestReCode3();
void TestReCode4();
void TestReCode5();
void TestReCode6();

void LinearTopoTest();
void SimpleLinearTopoTest();
void TreeTopoTest();
void SimpleTreeTopoTest();
void LinearCacheFigure1();		//for cache without k
void TreeCacheFigure1();		//for cache without k
void TestUniformLinear();
void TestUniformTree();

void TestLittleCacheLinear();
void TestLittleCacheTree();


extern int request_num;
extern int content_num_s[];
extern int content_num_l;
extern int slice_per_content_s[];
extern int slice_per_content_l;

extern int k_s[];
extern int k_l	;
extern int len;
extern int level;
extern int tree_degree;

#endif