#include <iostream>
using namespace std;


/*二叉树结点类定义*/
template <class T>
class BinNode
{

public:
	template <class T1>			//类模板作为类模板的友元类时，需要声明友元类的模板参数，此点非常重要
	friend class BinTree;		
	BinNode() {}
	BinNode(T data)			
	{
		m_data = data;
		m_id =-1;
		m_parent = NULL;
		m_leftchild = NULL;
		m_rightchild = NULL;
	}
	BinNode* searchNode(int id);		//再子树中搜索编号为id的结点	
	bool preOrderTraverse();		//前序遍历
	bool inOrderTraverse();			//中序遍历
	bool postOrderTraverse();		//后续遍历
	void InitData(T data) { m_data = data; }		
	void deleteNode();		//删除结点上的所有子树
private:
	T m_data;
	BinNode* m_parent;
	BinNode* m_leftchild;
	BinNode* m_rightchild;
	int m_id;
};

/*二叉树定义*/
template <class T>
class BinTree
{
public:
	BinTree()
	{
		size = 0;
		root = NULL;
	}
	~BinTree()
	{
		cout << "**********~BinTree*******" << endl;
		clean();
	}
	bool insertRoot(BinNode<T> node);		//插入根结点
	bool insertChild(int id, BinNode<T> node,char pose);		//插入孩子结点
	BinNode<T>* searchTree(int id);		//搜索树中编号为id的结点
	bool preOrderTree();			//前序遍历
	bool inOrderTree();				//中序遍历
	bool postOrderTree();		//后续遍历
	void clean();		//清空树，将其变为一颗空树
	bool deleteTreeNode(int id);		//删除树中编号为id的子树

private:
	BinNode<T>* root;
	int size;   //树的所有结点个数
};

/*******************二叉树的成员函数定义*******************************/
template <class T>
bool BinTree<T>::insertRoot(BinNode<T> node)
{
	if (size == 0)
	{
		root = new BinNode<T>;
		root->m_data = node.m_data;
		root->m_id = 0;
		size++;
		root->m_parent = NULL;
		root->m_leftchild = NULL;
		root->m_rightchild = NULL;
		return true;
	}
	else return false;
}

template <class T>
BinNode<T>* BinTree<T>::searchTree(int id)
{
	return root->searchNode(id);
}

template <class T>
bool BinTree<T>::insertChild(int id, BinNode<T> node, char pose)
{
	BinNode<T>* current = searchTree(id);
	if (current == NULL)	//说明索引为id的结点不在树中
		return false;
	if (pose == 'L')		//作为左孩子插入
	{
		if (current->m_leftchild != NULL)		//左孩子已经存在，无法再插入
			return false;
		else
		{
			BinNode<T>* temp = new BinNode<T>;
			temp->m_id = current->m_id * 2 + 1;
			temp->m_data = node.m_data;
			temp->m_leftchild = NULL;
			temp->m_rightchild = NULL;
			temp->m_parent = current;
			current->m_leftchild = temp;
			size++;
			return true;
		}
	}

	else if(pose=='R')         //作为右孩子插入
	{
		if (current->m_rightchild != NULL)		//左孩子已经存在，无法再插入
			return false;
		else
		{
			BinNode<T>* temp = new BinNode<T>;
			temp->m_id = current->m_id * 2 + 2;
			temp->m_data = node.m_data;
			temp->m_leftchild = NULL;
			temp->m_rightchild = NULL;
			temp->m_parent = current;
			current->m_rightchild = temp;
			size++;
			return true;
		}
	}
	else
	{
		cout << "invalid insert order" << endl;
		return false;
	}
}

template <class T>
bool BinTree<T>::deleteTreeNode(int id)
{
	BinNode<T>* current = searchTree(id);
	if (current == NULL)	//说明索引为id的结点不在树中
		return false;
	current->deleteNode();
	return true;
}


template <class T>
bool BinTree<T>::preOrderTree()
{
	if (root == NULL)
		return false;
	else
	{
		root->preOrderTraverse();
		cout << endl;
		return true;
	}
}

template <class T>
bool BinTree<T>::inOrderTree()
{
	if (root == NULL)
		return false;
	else
	{
		root->inOrderTraverse();
		cout << endl;
		return true;
	}
}

template <class T>
bool BinTree<T>::postOrderTree()
{
	if (root == NULL)
		return false;
	else
	{
		root->postOrderTraverse();
		cout << endl;
		return true;
	}
}

template <class T>
void BinTree<T>::clean()
{
	if (root == NULL)
		return ;
	root->deleteNode();		//删除根结点及其所有子树
	root = NULL;		//根节点为空，此时变为一颗空树
	return;
}



/*****************二叉树结点类的成员函数定义*********************************************/
template <class T>
BinNode<T>* BinNode<T>::searchNode(int id)
{
	if (m_id == id)   //自己就是需要找的这个结点
	{
		return this;
	}
	if (this->m_leftchild != NULL)    //搜索左子树
	{
		BinNode<T>* temp = this->m_leftchild->searchNode(id);    //左子树中搜索到结点
		if (temp != NULL)    //temp != NULL说明左子树中搜索到结点，否则没搜索到则继续向下搜索右子树
			return temp;
	}
	if (this->m_rightchild != NULL)    // 右子树中搜索到结点
	{
		BinNode<T>* temp =this->m_rightchild->searchNode(id);
		if (temp != NULL)    
			return temp;
	}
	else return NULL;     //该结点的左右子树都未搜到，返回NULL
}

template <class T>
bool BinNode<T>::preOrderTraverse()
{
	cout << this->m_data << " ";		//先输出根结点
	if (this->m_leftchild != NULL)
	{
		this->m_leftchild->preOrderTraverse();		//再递归输出左子树
	}
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->preOrderTraverse();		//最后递归输出右子树
	}
	return true;
}

template <class T>
bool BinNode<T>::inOrderTraverse()
{
	if (this->m_leftchild != NULL)
	{
		this->m_leftchild->inOrderTraverse();		//先递归输出左子树
	}
	cout << this->m_data << " ";				//再输出根结点
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->inOrderTraverse();		//最后递归输出右子树
	}
	return true;
}

template <class T>
bool BinNode<T>::postOrderTraverse()
{
	if (this->m_leftchild != NULL)
	{
		this->m_leftchild->postOrderTraverse();			//先递归输出左子树
	}
	
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->postOrderTraverse();		//再递归输出右子树
	}
	cout << this->m_data << " ";		//最后输出根结点
	return true;
}

template <class T>
void BinNode<T>::deleteNode()
{
	if (this->m_leftchild != NULL)		
	{
		this->m_leftchild->deleteNode();		//如果左子树存在，则递归删除左子树

	}
		
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->deleteNode();	//如果右子树存在，则递归删除右子树
	}

	/***********此时说明this没有左右子树，是叶子结点，使this的父节点指向空，此叶子结点就从树上删除了，但是this本身的空间还未删除，最后还需要再删除this本身的内存********************/
	/***********注意是this的父节点指向空，this才从树上断开。而不是this指向空。仅仅是this指向空，则this的父结点还是指向this，this结点并没有从树上撤下来***********************/
	/***********所以从树上撤下this结点的关键是this的父节点指向空。********************************/
	if (this->m_parent != NULL)			//必须加这句，因为如果是根结点，其m_parent为空时，NULL->m_leftchild访问权限错误，因为NULL是不能访问的
	{
		if (this->m_parent->m_leftchild == this)
		{
			this->m_parent->m_leftchild = NULL;
		}
		if (this->m_parent->m_rightchild == this)
		{
			this->m_parent->m_rightchild = NULL;
		}
	}
	cout << "delete " << this->m_data << endl;
	delete this;			//上面的步骤只是讲this从树上撤下来，但是this本身的内存并没有释放，此时才释放
}