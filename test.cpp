#include <iostream>
#include "BinTree.h"

using namespace std;

int main()
{
	BinTree<char> tree;			//创建一颗空树
	BinNode<char> node[11];
	char temp = 'A';
	for (int i = 0; i < 10; i++)
	{
		node[i].InitData(temp);
		temp++;
	}
	tree.insertRoot(node[0]);
	tree.insertChild(0, node[1], 'L');
	tree.insertChild(0, node[2], 'R');
	tree.insertChild(1, node[3], 'L');
	tree.insertChild(2, node[4], 'L');
	tree.insertChild(2, node[5], 'R');
	tree.insertChild(3, node[6], 'L');
	tree.insertChild(3, node[7], 'R');
	tree.insertChild(5, node[8], 'R');
	tree.preOrderTree();
	tree.deleteTreeNode(2);
	tree.preOrderTree();
	tree.inOrderTree();
	tree.postOrderTree();

	BinTree<char> tree1;			//创建一颗空树
	char arry[] = { 'a','b','#','d','#','#','c','#','#' };
	tree1.InitBinTree(arry);
	tree1.preOrderTree();
	tree1.deleteTreeNode(2);
	tree1.preOrderTree();
	tree1.inOrderTree();
	tree1.postOrderTree();

	return 0;
}