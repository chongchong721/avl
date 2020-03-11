#include "AVL_tree.h"
//对各节点的函数
BiTreeNode::BiTreeNode(int x)
{
	repeat = 1;
	data = x;
	count = height = 1;
	lchild = rchild = nullptr;
}
void BiTreeNode::update() //更新高度和子节点个数（求平衡因子用）
{
	int countl, countr, heightl, heightr;
	countl = countr = heightl = heightr = 0;
	if (lchild == nullptr)
	{
		countl = 0; heightl = 0;
	}
	else
	{
		countl = lchild->count; heightl = lchild->height;
	}
	if (rchild == nullptr)
	{
		countr = 0; heightr = 0;
	}
	else 
	{
		countr = rchild->count; heightr = rchild->height;
	}
	this->count = countl + countr + 1;
	this->height = std::max(heightl, heightr) + 1;
}
int BiTreeNode::Balance_Factor() //求平衡因子
{
	int heightl, heightr;
	if (lchild == nullptr)
		heightl = 0;
	else
		heightl = lchild->height;
	if (rchild == nullptr)
		heightr = 0;
	else
		heightr = rchild->height;
	return heightl - heightr;
}
BiTreeNode * BiTreeNode::RR() 
{
	BiTreeNode *R = rchild;
	rchild = rchild->lchild;
	R->lchild = this;
	this->update();
	R->update();
	return R;
}
BiTreeNode * BiTreeNode::LL()
{
	BiTreeNode *L = lchild;
	lchild = lchild->rchild;
	L->rchild = this;
	this->update();
	L->update();
	return L;
}
//二叉树函数
BiTree::BiTree()
{
	root = nullptr;
	size = 0;
}
BiTree::~BiTree()
{
	Destroy();
}
void BiTree::Destroy() //释放所有空间
{
	std::vector<BiTreeNode *> allnode;
	if (root != nullptr)
		allnode.push_back(root);
	while (!allnode.empty())
	{
		BiTreeNode *TheNode = allnode.back();
		allnode.pop_back();
		if (TheNode->lchild != nullptr)
			allnode.push_back(TheNode->lchild);
		if (TheNode->rchild != nullptr)
			allnode.push_back(TheNode->rchild);

		size--;
		delete TheNode;
	}
	root = nullptr;
}  
void BiTree::Insert(int key)
{
	BiTreeNode **TheNode = &root;
	std::vector<BiTreeNode **> trace_tree;
	while (*TheNode != nullptr)
	{
		trace_tree.push_back(TheNode);
		if (key < (*TheNode)->data)
			TheNode = &((*TheNode)->lchild);
		else if(key>(*TheNode)->data)
			TheNode = &((*TheNode)->rchild);
		else
		{
			(*TheNode)->repeat++;
			return;
		}
	}
	*TheNode = new BiTreeNode(key);
	trace_tree.push_back(TheNode);
	Balance(trace_tree);  //只需要平衡之前的（降低时间复杂度）
	size++;
}
void BiTree::Delete(int key)
{
	BiTreeNode **TheNode = &root;
	std::vector<BiTreeNode **> trace_tree;
	while (*TheNode != nullptr && (*TheNode)->data!=key)
	{
		trace_tree.push_back(TheNode);
		if (key < (*TheNode)->data)
			TheNode = &((*TheNode)->lchild);
		else if(key>(*TheNode)->data)
			TheNode = &((*TheNode)->rchild);
	}
	if (*TheNode == nullptr)
		return;
	else
		trace_tree.push_back(TheNode);

	size_t index = trace_tree.size();

	if ((*TheNode)->repeat > 1)
	{
		(*TheNode)->repeat--;
	}
	else
	{
		if ((*TheNode)->lchild == nullptr && (*TheNode)->rchild == nullptr)
		{
			delete *TheNode;
			*TheNode = nullptr;
			trace_tree.pop_back();
		}
		else if ((*TheNode)->rchild == nullptr)
		{
			BiTreeNode * remove = *TheNode;
			*TheNode = (*TheNode)->lchild;
			delete remove;
			trace_tree.pop_back();
		}
		else
		{
			BiTreeNode ** exchange = &((*TheNode)->rchild);
			while ((*exchange)->lchild != nullptr)
			{
				trace_tree.push_back(exchange);
				exchange = &((*exchange)->lchild);
			}

			if (*exchange == (*TheNode)->rchild)
			{
				((*exchange)->lchild) = ((*TheNode)->lchild);
				BiTreeNode *remove = *TheNode;
				*TheNode = *exchange;
				delete remove;
			}
			else
			{
				BiTreeNode *temp = *trace_tree.back();
				BiTreeNode *ex = *exchange;
				temp->lchild = (*exchange)->rchild;
				ex->lchild = (*TheNode)->lchild;
				ex->rchild = (*TheNode)->rchild;
				
				delete *TheNode;
				*TheNode = ex;
				trace_tree[index] = &(ex->rchild);
			}
		}
		Balance(trace_tree);
		size--;
	}
}
void BiTree::Balance(std::vector<BiTreeNode**> tree_trace)
{
	std::reverse(tree_trace.begin(), tree_trace.end());
	for (auto temp : tree_trace)
	{
		(*temp)->update();
		if ((*temp)->Balance_Factor() >= 2 && (*temp)->lchild->Balance_Factor() >= 1)
		{
			*temp = (*temp)->LL();
		}
		else if ((*temp)->Balance_Factor() >= 2)
		{
			(*temp)->lchild = ((*temp)->lchild)->RR();
			*temp = (*temp)->LL();
		}
		else if ((*temp)->Balance_Factor() <= -2 && (*temp)->rchild->Balance_Factor() <= -1)
		{
			*temp = (*temp)->RR();
		}
		else if((*temp)->Balance_Factor()<=-2)
		{
			(*temp)->rchild = ((*temp)->rchild)->LL();
			*temp = (*temp)->RR();
		}
	}
}
bool BiTree::Search(int key, BiTreeNode * & TheNode)
{
	BiTreeNode *temp = root;
	while (temp != nullptr&&temp->data != key)
	{
		if (key < temp->data)
			temp = temp->lchild;
		else if (key > temp->data)
			temp = temp->rchild;
	}
	if (temp == nullptr)
	{
		return false;
	}
	else
	{
		TheNode = temp;
		return true;
	}
	
}
int BiTree::get_repeat(int key)
{
	BiTreeNode *temp = nullptr;
	Search(key, temp);
	return temp->repeat;
}
void BiTree::display(BiTreeNode *TheNode, int depth, int state) {  // state: 1 -> left, 2 -> right , 0 -> root
	if (TheNode->lchild)
		display(TheNode->lchild, depth + 1, 1);
	for (int i = 0; i < depth; i++)
		printf("     ");
	if (state == 1) // left
		printf("┌───");
	else if (state == 2)  // right
		printf("└───");
	std::cout << "[" << TheNode->data << "] - (" << TheNode->count << ", " << TheNode->height <<", "<<TheNode->repeat<< ")" << std::endl;
	if (TheNode->rchild)
		display(TheNode->rchild, depth + 1, 2);
}
//外部函数
int FindLargestOne(BiTreeNode *p)
{
	if (p == NULL)
	{
		return 0;
	}
	if (p->rchild == NULL)
	{
		return p->data;
	}
	while (p->rchild != NULL)
	{
		p = p->rchild;
	}
	return p->data;
}
int FindSmallestOne(BiTreeNode *p)
{
	if (p == NULL)
	{
		return 0;
	}
	if (p->lchild == NULL)
	{
		return p->data;
	}
	while (p->lchild != NULL)
	{
		p = p->lchild;
	}
	return p->data;
}
void InOrderMin(BiTreeNode *p, int key, BiTreeNode * & TheNode)
{
	if (p != nullptr)
	{
		InOrderMin(p->lchild, key, TheNode);
		if (p->data < key)
		{
			TheNode = p;
		}
		else
			return;
		InOrderMin(p->rchild, key, TheNode);
	}
}
void InOrderMax(BiTreeNode *p, int key, BiTreeNode * & TheNode)
{
	if (p != nullptr)
	{
		InOrderMax(p->lchild, key, TheNode);
		if (p->data > key)
		{
			if(TheNode==nullptr)
			TheNode = p;
		}
		InOrderMax(p->rchild, key, TheNode);
	}
}
int Depth(BiTreeNode *p)
{
	int left, right;
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		left = Depth(p->lchild);
		right = Depth(p->rchild);
		if (left > right)
			return left + 1;
		else
			return right + 1;
	}
}
void get_parent(BiTreeNode *p, BiTreeNode *TheNode, BiTreeNode *&parent)
{
	if (p != NULL)
	{
		if (p->lchild != NULL)
		{
			if (p->lchild->data == TheNode->data)
			{
				parent = p;
				return;
			}
		}
		if (p->rchild != NULL)
		{
			if (p->rchild->data == TheNode->data)
			{
				parent = p;
				return;
			}
		}
		get_parent(p->lchild, TheNode, parent);
		get_parent(p->rchild, TheNode, parent);
	}

}
void get_parent(BiTreeNode *p, int key, BiTreeNode *&parent)
{
	if (p != NULL)
	{
		if (p->lchild != NULL)
		{
			if (p->lchild->data == key)
			{
				parent = p;
				return;
			}
		}
		if (p->rchild != NULL)
		{
			if (p->rchild->data == key)
			{
				parent = p;
				return;
			}
		}
		get_parent(p->lchild, key, parent);
		get_parent(p->rchild, key, parent);
	}

}
void get_insert_time(BiTreeNode *p, int * temp)
{
	if (p != NULL)
	{
		get_insert_time(p->lchild,temp);
		*temp += p->repeat;
		get_insert_time(p->rchild,temp);
	}
}
void get_node_num(BiTreeNode *p, int * temp)
{
	if (p != NULL)
	{
		get_insert_time(p->lchild, temp);
		*temp++;
		get_insert_time(p->rchild, temp);
	}
}
//填箱子函数
extern int COUNTALL;
void fill(BiTree & p, int sizeofbox)
{
	BiTreeNode * TheNode = nullptr;
	int temp, max;
	max = FindLargestOne(p.root);
	temp = sizeofbox - max;
	std::cout << max << " ";
	COUNTALL++;
	p.Delete(max);
	while (p.root != nullptr)
	{
		int j = FindSmallestOne(p.root);
		if (temp < j)
			return;
		else if (temp == j)
		{
			std::cout << j << " ";
			COUNTALL++;
			temp = temp - j;
			p.Delete(j);
			return;
		}
		else
		{
			InOrderMin(p.root, temp, TheNode);
			temp = temp - TheNode->data;
			std::cout << TheNode->data << " ";
			COUNTALL++;
			p.Delete(TheNode->data);
			continue;
		}
	}
}
void fill_no_output(BiTree & p, int sizeofbox)   //in order to find time
{
	BiTreeNode * TheNode = nullptr;
	int temp, max;
	max = FindLargestOne(p.root);
	temp = sizeofbox - max;
//	std::cout << max << " ";
//	COUNTALL++;
	p.Delete(max);
	while (p.root != nullptr)
	{
		int j = FindSmallestOne(p.root);
		if (temp < j)
			return;
		else if (temp == j)
		{
//			std::cout << j << " ";
//			COUNTALL++;
			temp = temp - j;
			p.Delete(j);
			return;
		}
		else
		{
			InOrderMin(p.root, temp, TheNode);
			temp = temp - TheNode->data;
//			std::cout << TheNode->data << " ";
//			COUNTALL++;
			p.Delete(TheNode->data);
			continue;
		}
	}
}


