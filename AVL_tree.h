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

	BiTreeNode(int x);   //�뽫repeat��1
	void update();//������Ϣ height count��
	int Balance_Factor();//��ƽ������
	BiTreeNode * RR();   //����
	BiTreeNode * LL();   //����
};
class BiTree
{
public:
	int size;             //�ߴ�
	BiTreeNode *root;         //���ڵ�

	BiTree();
	~BiTree();
	 
	void Insert(int key);     //���벢ƽ�����
	void Delete(int key);     //ɾ����ƽ�����
	void Destroy();          
	int Search(int key);    //û�õ�
	bool Search(int key, BiTreeNode * & TheNode);  //����ֵ
	int get_repeat(int key);
	int Smaller_One(int key);    //û�õ� ���ⲿʹ��inoderminʵ��
	int Larger_One(int key);    //û�õ� ���ⲿʹ��inordermaxʵ��
	void Balance(std::vector<BiTreeNode**> trace_tree);   //ƽ�����
	void BiTree::display(BiTreeNode *cur, int depth, int state);  //ͼ�λ�չʾ
};

int FindLargestOne(BiTreeNode *p);
int FindSmallestOne(BiTreeNode *p);
void InOrderMin(BiTreeNode *p, int key, BiTreeNode * & TheNode);
void InOrderMax(BiTreeNode *p, int key, BiTreeNode * & TheNode);
int Depth(BiTreeNode *p);
void get_parent(BiTreeNode *p, BiTreeNode *TheNode, BiTreeNode *&parent);
void get_parent(BiTreeNode *p, int key, BiTreeNode *&parent);
void get_insert_time(BiTreeNode *p, int * temp);  //��ò���ʱ��
void get_node_num(BiTreeNode *p, int * temp);
void fill(BiTree & p, int sizeofbox);  //װ�䲢���
void fill_no_output(BiTree & p, int sizeofbox);  //װ�䲻��������ڲ���ʱ��