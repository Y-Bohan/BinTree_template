#include <iostream>
using namespace std;


/*����������ඨ��*/
template <class T>
class BinNode
{

public:
	template <class T1>			//��ģ����Ϊ��ģ�����Ԫ��ʱ����Ҫ������Ԫ���ģ��������˵�ǳ���Ҫ
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
	BinNode* searchNode(int id);		//���������������Ϊid�Ľ��	
	bool preOrderTraverse();		//ǰ�����
	bool inOrderTraverse();			//�������
	bool postOrderTraverse();		//��������
	void InitData(T data) { m_data = data; }		
	void deleteNode();		//ɾ������ϵ���������
private:
	T m_data;
	BinNode* m_parent;
	BinNode* m_leftchild;
	BinNode* m_rightchild;
	int m_id;
};

/*����������*/
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
	bool insertRoot(BinNode<T> node);		//��������
	bool insertChild(int id, BinNode<T> node,char pose);		//���뺢�ӽ��
	BinNode<T>* searchTree(int id);		//�������б��Ϊid�Ľ��
	bool preOrderTree();			//ǰ�����
	bool inOrderTree();				//�������
	bool postOrderTree();		//��������
	void clean();		//������������Ϊһ�ſ���
	bool deleteTreeNode(int id);		//ɾ�����б��Ϊid������

private:
	BinNode<T>* root;
	int size;   //�������н�����
};

/*******************�������ĳ�Ա��������*******************************/
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
	if (current == NULL)	//˵������Ϊid�Ľ�㲻������
		return false;
	if (pose == 'L')		//��Ϊ���Ӳ���
	{
		if (current->m_leftchild != NULL)		//�����Ѿ����ڣ��޷��ٲ���
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

	else if(pose=='R')         //��Ϊ�Һ��Ӳ���
	{
		if (current->m_rightchild != NULL)		//�����Ѿ����ڣ��޷��ٲ���
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
	if (current == NULL)	//˵������Ϊid�Ľ�㲻������
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
	root->deleteNode();		//ɾ������㼰����������
	root = NULL;		//���ڵ�Ϊ�գ���ʱ��Ϊһ�ſ���
	return;
}



/*****************�����������ĳ�Ա��������*********************************************/
template <class T>
BinNode<T>* BinNode<T>::searchNode(int id)
{
	if (m_id == id)   //�Լ�������Ҫ�ҵ�������
	{
		return this;
	}
	if (this->m_leftchild != NULL)    //����������
	{
		BinNode<T>* temp = this->m_leftchild->searchNode(id);    //�����������������
		if (temp != NULL)    //temp != NULL˵������������������㣬����û�������������������������
			return temp;
	}
	if (this->m_rightchild != NULL)    // �����������������
	{
		BinNode<T>* temp =this->m_rightchild->searchNode(id);
		if (temp != NULL)    
			return temp;
	}
	else return NULL;     //�ý�������������δ�ѵ�������NULL
}

template <class T>
bool BinNode<T>::preOrderTraverse()
{
	cout << this->m_data << " ";		//����������
	if (this->m_leftchild != NULL)
	{
		this->m_leftchild->preOrderTraverse();		//�ٵݹ����������
	}
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->preOrderTraverse();		//���ݹ����������
	}
	return true;
}

template <class T>
bool BinNode<T>::inOrderTraverse()
{
	if (this->m_leftchild != NULL)
	{
		this->m_leftchild->inOrderTraverse();		//�ȵݹ����������
	}
	cout << this->m_data << " ";				//����������
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->inOrderTraverse();		//���ݹ����������
	}
	return true;
}

template <class T>
bool BinNode<T>::postOrderTraverse()
{
	if (this->m_leftchild != NULL)
	{
		this->m_leftchild->postOrderTraverse();			//�ȵݹ����������
	}
	
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->postOrderTraverse();		//�ٵݹ����������
	}
	cout << this->m_data << " ";		//�����������
	return true;
}

template <class T>
void BinNode<T>::deleteNode()
{
	if (this->m_leftchild != NULL)		
	{
		this->m_leftchild->deleteNode();		//������������ڣ���ݹ�ɾ��������

	}
		
	if (this->m_rightchild != NULL)
	{
		this->m_rightchild->deleteNode();	//������������ڣ���ݹ�ɾ��������
	}

	/***********��ʱ˵��thisû��������������Ҷ�ӽ�㣬ʹthis�ĸ��ڵ�ָ��գ���Ҷ�ӽ��ʹ�����ɾ���ˣ�����this����Ŀռ仹δɾ���������Ҫ��ɾ��this������ڴ�********************/
	/***********ע����this�ĸ��ڵ�ָ��գ�this�Ŵ����϶Ͽ���������thisָ��ա�������thisָ��գ���this�ĸ���㻹��ָ��this��this��㲢û�д����ϳ�����***********************/
	/***********���Դ����ϳ���this���Ĺؼ���this�ĸ��ڵ�ָ��ա�********************************/
	if (this->m_parent != NULL)			//�������䣬��Ϊ����Ǹ���㣬��m_parentΪ��ʱ��NULL->m_leftchild����Ȩ�޴�����ΪNULL�ǲ��ܷ��ʵ�
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
	delete this;			//����Ĳ���ֻ�ǽ�this�����ϳ�����������this������ڴ沢û���ͷţ���ʱ���ͷ�
}