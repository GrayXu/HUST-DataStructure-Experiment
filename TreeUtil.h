#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef int ElemType;//make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define NOTFOUNDCODE 90017
#define SUCCESSFULCODE 90016


typedef struct node {
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

Status PreOrderTraverse(Tree * T);
Status InOrderTraverse(Tree * T);
Status PostOrderTraverse(Tree * T);
Status LevelOrderTraverse(Tree * T);


//Create a new and empty binary tree
Status InitBiTree(Tree ** T) {

	Tree * newT = (Tree *)malloc(sizeof(Tree));
	newT->length = 0;
	newT->name = NULL;
	newT->root = NULL;
	if (newT != NULL) {
		*T = newT;
		return OK;
	} else {
		printERROR();
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
void ClearBiTree_recurve(Node * n){//for recursion
    if(!n) return;
    ClearBiTree_recurve(n->left);
    ClearBiTree_recurve(n->right);
    free(n);
}

//get the root node of tree-T
Node * Root(Tree * T) {
	return T->root;
}

//assign a value for node-e of tree-T
Status Assign(Tree * T, Node * e, ElemType value){
    ElemType valueBackup = value;
    Assign_recurve(T->root, e, &value);
    if(value == SUCCESSFULCODE){
        return OK;
    }else{
        return FALSE;
    }
}
int Assign_recurve(Node * start, Node * key, ElemType * value){//for recursion

    if(!start) return 0;
    if(key == start) {
        key->data = *value;
        *value = SUCCESSFULCODE;
        return 1;
    }
    if(Assign_recurve(start->left)) return 1;
    if(Assign_recurve(start->right)) return 1;

}

//get value of node-e of tree-T
ElemType Value(Tree * T, Node *e) {
    ElemType get = NOTFOUNDCODE;
    Value_recurve(e, T->root, &get);
    if(get == NOTFOUNDCODE) {
        return NOTFOUNDCODE;
    }else{
        return get;
    }
}
int Value_recurve(Node * key, Node * n, ElemType * get) {//for recursion
    if(n == NULL) return 0;
    if(key == n){
        *get = n->data;
        return 1;//1 means that we found the element, so we can set a flag to stop recursion
    }

    if(Value_recurve(key,n->left,get)) return 1;
    if(Value_recurve(key,n->right,get)) return 1;

}

//just print error info
void printERROR() {
	printf("\nStack overflow\n");
}

//get left child of tree-T
Node * LeftChild(Tree * T, Node * e){
    return e->left;
}

//get right child of tree-T
Node * RightChild(Tree * T, Node * e){
    return e->right;
}

//find the parent node of node-e
Node * Parent(Tree * T, Node * e){
    Node * parent = NULL;
    Parent_recurve(T->root, e, &parent);
    return parent;
}
int Parent_recurve(Node * start, Node * key, Node * parent){
    if(!start) return 0;
    if(start->right == key || start->left == key){
        *parent = start;
        return 1;
    }
    if(Parent_recurve(start->left, key, parent)) return 1;
    if(Parent_recurve(start->right, key, parent)) return 1;
}

//find the right sibling of node-e in tree-T
Node * RightSibling(Tree * T, Node * e){
    Node * parent = Parent(T, e);
    if(parent){
        if(parent->right) return parent->right;
    }
    return NULL;
}

//find the left sibling of node-e in tree-T
Node * LeftSibling(Tree * T, Node * e){
    Node * parent = Parent(T, e);
    if(parent){
        if(parent->left) return parent->left;
    }
    return NULL;
}

//PreOrderTraverse
Status PreOrderTraverse(Tree * T){
    if(T == NULL) return FALSE;
    PreOrderTraverse_recurve(T->root);
    printf("\n");
}
void PreOrderTraverse_recurve(Node * n){//for recursion
    if(!n) return;
    printf("%d ",n->data);
    PreOrderTraverse(n->left);
    PreOrderTraverse(n->Right);
}

//InOrderTraverse
Status InOrderTraverse(Tree * T){
    if(T == NULL) return FALSE;
    InOrderTraverse_recurve(T->root);
    printf("\n");
}
void InOrderTraverse_recurve(Node * n){//for recursion
    if(!n) return;
    PreOrderTraverse(n->left);
    printf("%d ",n->data);
    PreOrderTraverse(n->Right);
}

//PostOrderTraverse
Status PostOrderTraverse(Tree * T){
    if(T == NULL) return FALSE;
    PostOrderTraverse_recurve(T->root);
    printf("\n");
}
void PostOrderTraverse_recurve(Node * n){//for recursion
    if(!n) return;
    PreOrderTraverse(n->left);
    PreOrderTraverse(n->Right);
    printf("%d ",n->data);
}

//insert a subTree-c to the tree-T, 0->L 1->R
Status InsertChild(Tree * T, Node * p, int LR, Tree * c){

    int flag = 0;
    if(LR){
        Node * left = p->left;
        if(!left){//left is null
            p->left = c->root;
            flag = 1;
        }
    }else{
        Node * right = p->right;
        if(!right){//right is null
            p->right = c->root
            flag = 1;
        }
    }
    if(flag){
        T->length += c->length;
        free(c);//but we preserve the data part
        return OK;
    }else{
        return FALSE;
    }
}

//insert a new node to the tree-T, 0->L 1->R
Status InsertNode(Tree * T, Node * p, int LR, Node * c){

    if(LR){
        Node * left = p->left;
        if(!left){//left is null
            p->left = c;
            return OK;
        }
    }else{
        Node * right = p->right;
        if(!right){//right is null
            p->right = c;
            return OK;
        }
    }
    return FALSE;

}

//delete a child-tree
Status DeleteChild(Tree * T, Node * p, int LR){
    if(LR){
        Node * left = p->left;
        if(left){//left is not null
            ClearBiTree_recurve(left);
            p->left = NULL;
            return OK;
        }
    }else{
        Node * right = p->right;
        if(right){//right is not null
            ClearBiTree_recurve(right);
            p->right = NULL;
            return OK;
        }
    }
    return FALSE;
}


//traverse in level, kind of BST, using an aux-quene
Status LevelOrderTraverse(Tree * T){

}
