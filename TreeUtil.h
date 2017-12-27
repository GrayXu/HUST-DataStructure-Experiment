#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int ElemType;//make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1


typedef struct node {
	ElemType key;
	ElemType data;
	struct node * left;
	struct node * right;
}Node;

typedef struct tree {
	int length;
	char * name;
	Node * root;
} Tree;

Status InitBiTree(Tree ** T);
void DestroyTree(Tree * T);
//Status CreateTree(Tree * T);//WTF for definition
void ClearBiTree(Tree * T);
Status BiTreeEmpty(Tree * T);
int BiTreeDepth(Tree * T);
Node * Root(Tree * T);
ElemType Value(Tree * T, Node * e);
Status Assign(Tree * T, Node * e, ElemType value);
Node * Parent(Tree * T, Node * e);
Node * LeftChild(Tree * T, Node * e);
Node * RightChild(Tree * T, Node * e);
Node * LeftSibling(Tree * T, Node * e);
Node * RightSibling(Tree * T, Node * e);
Status InsertChild(Tree * T, Node *p, int LR, Tree * c);//c is a new tree to insert
Status DeleteChild(Tree * T, Node * p, int LR);
Node * FindNode(Tree * T, ElemType key);

Status PreOrderTraverse(Tree * T);
Status InOrderTraverse(Tree * T);
Status PostOrderTraverse(Tree * T);
Status LevelOrderTraverse(Tree * T);

Tree * LoadTree(char * TreeName);
Status saveTree(Tree * T);
void LevelOreder_recurve(Node * node);
void BiTreeDepth_recurve(Node * node);
Status InsertNode(Tree * T, Node * p, int LR, Node * c);
void PostOrderTraverse_recurve(Node * n);
void InOrderTraverse_recurve(Node * n);
void PreOrderTraverse_recurve(Node * n);
int Parent_recurve(Node * start, Node * key, Node ** parent);
void ClearBiTree_recurve(Node * n);
void printERROR(int code);//print error infomation
int FindNode_recurve(Node * node, ElemType key, Node ** result);

//Create a new and empty binary tree
Status InitBiTree(Tree ** T) {

	Tree * newT = (Tree *)malloc(sizeof(Tree));
	newT->length = 0;
	newT->name = NULL;//set its name outside
	newT->root = NULL;
	if (newT != NULL) {
		*T = newT;
		return OK;
	} else {
		printERROR(1);
		return FALSE;
	}

}

//destroy this tree and free all space it had taken.
void DestroyTree(Tree * T) {
	ClearBiTree(T);
	free(T->name);
	free(T);
}

//clear all data of this tree
void ClearBiTree(Tree * T) {
	ClearBiTree_recurve(T->root);
	T->root = NULL;
}
void ClearBiTree_recurve(Node * n) {//for recursion
	if (!n) return;
	ClearBiTree_recurve(n->left);
	ClearBiTree_recurve(n->right);
	free(n);
}

//get the root node of tree-T
Node * Root(Tree * T) {
	return T->root;
}

//assign a value for node-e of tree-T
Status Assign(Tree * T, Node * e, ElemType value) {
	//Assign_recurve(T->root, e, &value);
	if (e == NULL) {
		return FALSE;
	} else {
		e->data = value;
		return OK;
	}
}

//get value of node-e of tree-T
ElemType Value(Tree * T, Node *e) {
	if (!T || !e) return FALSE;
	return e->data;
}

//just print error info
void printERROR(int code) {

	switch (code) {
	case 1:
		printf("\nStack overflow\n");
		break;
	case 2:
		printf("\nThere isn't such a tree.\n");
		break;
	case 3:
		printf("\nThere isn't such a node in this tree.\n");
		break;
	}
}

//find the node of tree-T by key
Node * FindNode(Tree * T, ElemType key) {
	Node * result = NULL;
	FindNode_recurve(T->root, key, &result);
	return result;
}
int FindNode_recurve(Node * node, ElemType key, Node ** result) {
	if (!node) return 0;
	if (node->key == key) {
		*result = node;
		return 1;//1 means that we found the element, so we can set a flag to stop recursion
	}
	if (FindNode_recurve(node->left, key, result)) return 1;
	if (FindNode_recurve(node->left, key, result)) return 1;
	return 0;
}

//get left child of tree-T
Node * LeftChild(Tree * T, Node * e) {
	return e->left;
}

//get right child of tree-T
Node * RightChild(Tree * T, Node * e) {
	return e->right;
}

//find the parent node of node-e
Node * Parent(Tree * T, Node * e) {
	Node * parent = NULL;
	Parent_recurve(T->root, e, &parent);
	return parent;
}
int Parent_recurve(Node * start, Node * key, Node ** parent) {
	if (!start) return 0;
	if (start->right == key || start->left == key) {
		*parent = start;
		return 1;
	}
	if (Parent_recurve(start->left, key, parent)) return 1;
	if (Parent_recurve(start->right, key, parent)) return 1;
	return 0;
}

//find the right sibling of node-e in tree-T
Node * RightSibling(Tree * T, Node * e) {
	Node * parent = Parent(T, e);
	if (parent) {
		if (parent->right) return parent->right;
	}
	return NULL;
}

//find the left sibling of node-e in tree-T
Node * LeftSibling(Tree * T, Node * e) {
	Node * parent = Parent(T, e);
	if (parent) {
		if (parent->left) return parent->left;
	}
	return NULL;
}

//PreOrderTraverse
Status PreOrderTraverse(Tree * T) {
	if (T == NULL) return FALSE;
	PreOrderTraverse_recurve(T->root);
	printf("\n");
	return OK;
}
void PreOrderTraverse_recurve(Node * n) {//for recursion
	if (!n) return;
	printf("%d ", n->data);
	PreOrderTraverse_recurve(n->left);
	PreOrderTraverse_recurve(n->right);
}

//InOrderTraverse
Status InOrderTraverse(Tree * T) {
	if (T == NULL) return FALSE;
	InOrderTraverse_recurve(T->root);
	printf("\n");
	return OK;
}
void InOrderTraverse_recurve(Node * n) {//for recursion
	if (!n) return;
	PreOrderTraverse_recurve(n->left);
	printf("%d ", n->data);
	PreOrderTraverse_recurve(n->right);
}

//PostOrderTraverse
Status PostOrderTraverse(Tree * T) {
	if (T == NULL) return FALSE;
	PostOrderTraverse_recurve(T->root);
	printf("\n");
	return OK;
}
void PostOrderTraverse_recurve(Node * n) {//for recursion
	if (!n) return;
	PreOrderTraverse_recurve(n->left);
	PreOrderTraverse_recurve(n->right);
	printf("%d ", n->data);
}

//insert a subTree-c to the tree-T, 0->L 1->R
Status InsertChild(Tree * T, Node * p, int LR, Tree * c) {

	int flag = 0;
	if (LR) {
		Node * left = p->left;
		if (!left) {//left is null
			p->left = c->root;
			flag = 1;
		}
	} else {
		Node * right = p->right;
		if (!right) {//right is null
			p->right = c->root;
			flag = 1;
		}
	}
	if (flag) {
		T->length += c->length;
		free(c);//but we preserve the data part
		return OK;
	} else {
		return FALSE;
	}
}

//insert a new node to the tree-T, 0->L 1->R
Status InsertNode(Tree * T, Node * p, int LR, Node * c) {

	if (LR) {
		Node * left = p->left;
		if (!left) {//left is null
			p->left = c;
			T->length++;
			return OK;
		}
	} else {
		Node * right = p->right;
		if (!right) {//right is null
			p->right = c;
			T->length++;
			return OK;
		}
	}
	return FALSE;

}

//delete a child-tree
Status DeleteChild(Tree * T, Node * p, int LR) {
	if (LR) {
		Node * left = p->left;
		if (left) {//left is not null
			ClearBiTree_recurve(left);
			p->left = NULL;
			return OK;
		}
	} else {
		Node * right = p->right;
		if (right) {//right is not null
			ClearBiTree_recurve(right);
			p->right = NULL;
			return OK;
		}
	}
	return FALSE;
}

//this tree is empty or not
Status BiTreeEmpty(Tree * T) {
	return T->length;
}

//get the depth of this binary tree
int depth = 0;//aux-count
int depthMax = 0;
int BiTreeDepth(Tree * T) {
	depth = 0;//reset their value
	depthMax = 0;
	Node * head = T->root;
	BiTreeDepth_recurve(head);
	return depthMax;
}
void BiTreeDepth_recurve(Node * node) {
	if (!node) {
		--depth;
		return;
	}

	++depth;
	if (depth > depthMax) depthMax = depthMax;

	BiTreeDepth_recurve(node->left);
	BiTreeDepth_recurve(node->right);

}


//traverse in level, kind of BST, using an aux-quene
int i = 0;
int depthNow = 0;
Status LevelOrderTraverse(Tree * T) {
	if (T) {
		Node * head = T->root;
		depthNow = 0;
		printf("LevelOrderTraverse:");
		for (i = 1; i <= BiTreeDepth(T); i++) {

			//each i means that we are trying to print all elements of the i'th level
			LevelOreder_recurve(head);
		}
		printf("\n");
		return OK;
	} else {
		return FALSE;
	}

}
void LevelOreder_recurve(Node * node) {
	if (!node) {
		--depthNow;
		return;
	}

	++depthNow;
	if (depthNow == i) {
		printf("%d ", node->data);
	}
	LevelOreder_recurve(node->left);
	LevelOreder_recurve(node->right);
}

Status saveTree(Tree * T) {
	return FALSE;
}

Tree * LoadTree(char * TreeName) {
	return NULL;
}

