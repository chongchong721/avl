#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
class BiTreeNode
{
public:
	int data;
	int height;
	int count;  
	int repeat;
	BiTreeNode *lchild, *rchild;

	BiTreeNode(int x);   //请将repeat给1
	void update();//更新信息 height count；
	int Balance_Factor();//求平衡因子
	BiTreeNode * RR();   //左旋
	BiTreeNode * LL();   //右旋
};
class BiTree
{
public:
	int size;             //尺寸
	BiTreeNode *root;         //根节点

	BiTree();
	~BiTree();
	 
	void Insert(int key);     //插入并平衡调整
	void Delete(int key);     //删除并平衡调整
	void Destroy();          
	int Search(int key);    //没用到
	bool Search(int key, BiTreeNode * & TheNode);  //搜索值
	int get_repeat(int key);
	int Smaller_One(int key);    //没用到 在外部使用inodermin实现
	int Larger_One(int key);    //没用到 在外部使用inordermax实现
	void Balance(std::vector<BiTreeNode**> trace_tree);   //平衡调整
	void BiTree::display(BiTreeNode *cur, int depth, int state);  //图形化展示
};

int FindLargestOne(BiTreeNode *p);
int FindSmallestOne(BiTreeNode *p);
void InOrderMin(BiTreeNode *p, int key, BiTreeNode * & TheNode);
void InOrderMax(BiTreeNode *p, int key, BiTreeNode * & TheNode);
int Depth(BiTreeNode *p);
void get_parent(BiTreeNode *p, BiTreeNode *TheNode, BiTreeNode *&parent);
void get_parent(BiTreeNode *p, int key, BiTreeNode *&parent);
void get_insert_time(BiTreeNode *p, int * temp);  //获得插入时间
void get_node_num(BiTreeNode *p, int * temp);
void fill(BiTree & p, int sizeofbox);  //装箱并输出
void fill_no_output(BiTree & p, int sizeofbox);  //装箱不输出，用于测试时间