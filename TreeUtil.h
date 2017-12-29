#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <assert.h>

typedef int ElemType;//make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define NULLNODECODE 90017
#define LOAD_LIST_SIZE 31

typedef struct node {
	ElemType key;//a key to find this node
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
void LevelOreder_recurve(Node * node, int depthNow);
void BiTreeDepth_recurve(Node * node, int i);
Status InsertNode(Tree * T, Node * p, int LR, Node * c);
void PostOrderTraverse_recurve(Node * n);
void InOrderTraverse_recurve(Node * n);
void PreOrderTraverse_recurve(Node * n);
int Parent_recurve(Node * start, Node * key, Node ** parent);
void ClearBiTree_recurve(Node * n);
void printERROR(int code);//print error infomation
int FindNode_recurve(Node * node, ElemType key, Node ** result);
void saveTree_recurve(Node * node, int i);
Node * LoadTree_recurve(int i);
int BiTreeLength(Node * node);
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
	T->length = 0;
}
void ClearBiTree_recurve(Node * n) {//for recursion
	if (!n) return;
	ClearBiTree_recurve(n->left); n->left = NULL;
	ClearBiTree_recurve(n->right); n->right = NULL;
	//	printf("key=%d value=%d\n",n->key,n->data);
	free(n);//and set old position of n as null outside
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
	//	FindNode_recurve(node->left, key, result);
	//	FindNode_recurve(node->right, key, result);
	//	return 1;
	if (FindNode_recurve(node->left, key, result)) return 1;
	if (FindNode_recurve(node->right, key, result)) return 1;
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
	if (parent) {//have parent node
		if (parent->right) {//and parent have right node
            if(parent->right != e){// and this right node is not the parameter node
                return parent->right;
            }
        }
	}
	return NULL;
}

//find the left sibling of node-e in tree-T
Node * LeftSibling(Tree * T, Node * e) {
	Node * parent = Parent(T, e);
	if (parent) {//have parent node
		if (parent->left) {//and parent have right node
            if(parent->left != e){// and this right node is not the parameter node
                return parent->left;
            }
        }
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
	printf("key=%d value=%d\n", n->key,n->data);
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
	InOrderTraverse_recurve(n->left);
	printf("key=%d value=%d\n", n->key,n->data);
	InOrderTraverse_recurve(n->right);
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
	PostOrderTraverse_recurve(n->left);
	PostOrderTraverse_recurve(n->right);
	printf("key=%d value=%d\n", n->key,n->data);
}

//insert a subTree-c to the tree-T, 0->L 1->R
Status InsertChild(Tree * T, Node * p, int LR, Tree * c) {

	int flag = 0;
	if (LR == 0) {
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

	if (!LR) {
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
	if (!LR) {
		Node * left = p->left;
		if (left) {//left is not null
			T->length -= BiTreeLength(left);
			ClearBiTree_recurve(left);
			p->left = NULL;
			return OK;
		}
	} else {
		Node * right = p->right;
		if (right) {//right is not nulls
			T->length -= BiTreeLength(right);
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
int depthMax = 0;
int BiTreeDepth(Tree * T) {
	depthMax = 0;
	Node * head = T->root;
	BiTreeDepth_recurve(head, 1);
	return depthMax;
}
void BiTreeDepth_recurve(Node * node, int i) {
	if (!node) return;
	if (i > depthMax) depthMax = i;

	BiTreeDepth_recurve(node->left, i + 1);
	BiTreeDepth_recurve(node->right, i + 1);

}


//traverse in level, kind of BST, without an aux-quene to save memory
int i = 0;
Status LevelOrderTraverse(Tree * T) {
	i = 0; //reset two flags
	if (T) {
		Node * head = T->root;
		for (i = 1; i <= BiTreeDepth(T); i++) {
			//each i means that we are trying to print all elements of the i'th level
			LevelOreder_recurve(head, 1);
		}
		printf("\n");
		return OK;
	} else {
		return FALSE;
	}
}
void LevelOreder_recurve(Node * node, int depthNow) {
	if (!node) return;

	if (depthNow == i) {
		printf("key=%d value=%d\n", node->key,node->data);//print the go back in recursion
	} else {
		LevelOreder_recurve(node->left, depthNow + 1);
		LevelOreder_recurve(node->right, depthNow + 1);
	}

}

//save this tree in disk in a simple way
Node ** saveList = NULL;
Status saveTree(Tree * T) {

	FILE * fP = fopen(T->name, "wb");
	if (!fP) return FALSE;
	int depth = BiTreeDepth(T);
	int LISTSIZE = pow(2, depth) - 1;
	saveList = (Node **)malloc(sizeof(Node*)*LISTSIZE);
	int i = 0;
	for (i = 0; i < LISTSIZE; i++) {
		saveList[i] = NULL;
	}//initalize save list

	Node * nullNode = (Node*)malloc(sizeof(Node));
	nullNode->data = NULLNODECODE;
	nullNode->key = NULLNODECODE;

	saveTree_recurve(T->root, 1);//call this function to load nodes to save list, including null nodes

	for (i = 0; i < LISTSIZE; i++) {
		if (saveList[i]) {
			fwrite(saveList[i], sizeof(Node), 1, fP);
		} else {//null node
			fwrite(nullNode, sizeof(Node), 1, fP);
		}

	}//save node list to disk
	free(saveList); saveList = NULL;//reset
	fclose(fP);
	return TRUE;
}
void saveTree_recurve(Node * node, int i) {
	if (!node) return;
	saveList[i - 1] = node;

	saveTree_recurve(node->left, 2 * i);
	saveTree_recurve(node->right, 2 * i + 1);
}

//Load tree data from disk
Node ** loadList = NULL;
int maxIndex_loadTree = 0;

Tree * LoadTree(char * TreeName) {

	maxIndex_loadTree = 0;
	loadList = (Node **)malloc(sizeof(Node *) * LOAD_LIST_SIZE);//we set a init-num, in fact it's not elegant.
	register int i = 0;
	for (i = 0; i < LOAD_LIST_SIZE; i++) {
		loadList[i] = NULL;
	}

	FILE * fP = fopen(TreeName, "rb");
	if (!fP) return NULL;
	else {//this file exists
		i = 0;
		Node * newNode = (Node*)malloc(sizeof(Node));

		while (fread(newNode, sizeof(Node), 1, fP)) {
			loadList[i] = newNode; i++;
			newNode = (Node *)malloc(sizeof(Node));
		}
		free(newNode);
	}

	//now we got a list full of nodes
	//int i is length of this list
	//	int depth = (int)sqrt(i+1);
	maxIndex_loadTree = i;
	Node * root = LoadTree_recurve(1);//load
	Tree * T = (Tree *)malloc(sizeof(Tree));
	if (T) {
		T->root = root;
		T->length = i;
		T->name = TreeName;
	}
	free(loadList);
	return T;
}
Node * LoadTree_recurve(int i) {
	Node * node = loadList[i - 1];
	assert(node);//variable "node" here is not a null node
	if (node->data == NULLNODECODE) {
		return NULL;
	}
	if (i * 2 > maxIndex_loadTree) {//at the buttom of this sub-tree
		node->left = NULL;
	} else {
		node->left = LoadTree_recurve(i * 2);
	}
	if (i * 2 + 1 > maxIndex_loadTree) {//at the buttom of this sub-tree
		node->right = NULL;
	} else {
		node->right = LoadTree_recurve(i * 2 + 1);
	}
	return node;
}

int BiTreeLength(Node * node) {
	if (!node) return 0;
	return BiTreeLength(node->left) + BiTreeLength(node->right) + 1;
}
