#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <TreeUtil.h>
typedef int ElemType;//make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1

Tree ** treeArray = NULL;//init an array for tree array.
int indexTreeArray = 0;//index for the array above
char *fgetsNoN(char *buf, int bufsize, FILE *stream);
Tree * getTreeFromName(char * name);

void IBT1() {
	Tree * T = NULL;
	printf("\nPlease input the name of new list.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	if (InitBiTree(&T)) printf("Binary Tree has been created\n");
	else printf("\nFailed! Because there is no more space in stake's memory, we can't creat a new tree.\n");
	T->name = name;
	treeArray[indexTreeArray] = T; indexTreeArray++;
}

void A2() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree under your control.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		//Do Assign 
		//TODO: YOU CAN'T GET THE NODE WITHOUT ANY NOTATION
	} else {
		printERROR(2);
	}
	free(name);
}

void DT3() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to destroy.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		DestroyTree(T);
		treeArray[indexTreeArray] = NULL;//array outside reset index
		indexTreeArray--;
		printf("\nDone!\n");
	} else {
		printERROR(2);
	}
	free(name);
}

void P4() {//= =

}

void CBT5() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to clear.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		ClearBiTree(T);//just clear all data, but still keep its position
		printf("\nDone!\n");
	} else {
		printERROR(2);
	}
	free(name);
}

void BTE7() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to control.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		if (BiTreeEmpty(T)) {
			printf("\nIt's not empty\n");
		} else {
			printf("\nIt's empty\n");
		}
	} else {
		printERROR(2);
	}
	free(name);
}

void BTD9() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to control.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		int d = BiTreeDepth(T);
		printf("\nIt's depth is %d.\n", d);
	} else {
		printERROR(2);
	}
	free(name);
}

void R11() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to control.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		Node * root = T->root;
		if (root) {
			printf("\nRoot is %d.\n", root->data);
		} else {
			printf("\nThis tree is empty.\n");
		}
	} else {
		printERROR(2);
	}
	free(name);
}

void V13() {//= =
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to clear.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		Node * root = T->root;
		if (root) {
			//int get = Value(T)//TODO: how to get this node's address
		} else {
			printf("\nThis tree is empty.\n");
		}
	} else {
		printERROR(2);
	}
	free(name);
}

void POT16(){
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to traverse.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		Node * root = T->root;
		if (root) {
			PreOrderTraverse(T);
		} else {
			printf("\nThis tree is empty.\n");
		}
	} else {
		printERROR(2);
	}
	free(name);
}

void IOT17() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to traverse.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		Node * root = T->root;
		if (root) {
			InOrderTraverse(T);
		} else {
			printf("\nThis tree is empty.\n");
		}
	} else {
		printERROR(2);
	}
	free(name);
}

void POT18() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to traverse.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		Node * root = T->root;
		if (root) {
			PostOrderTraverse(T);
		} else {
			printf("\nThis tree is empty.\n");
		}
	} else {
		printERROR(2);
	}
	free(name);
}

void LOT19() {
	Tree * T = NULL;
	printf("\nPlease input the name of the tree you want to traverse.\n");
	char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);
	T = getTreeFromName(name);
	if (T) {
		Node * root = T->root;
		if (root) {
			LevelOrderTraverse(T);
		} else {
			printf("\nThis tree is empty.\n");
		}
	} else {
		printERROR(2);
	}
	free(name);
}

int main() {

	treeArray = (Tree **)malloc(sizeof(Tree*) * 10);//init an array for tree array.
	indexTreeArray = 0;//index for the array above
	int op = 1;
	while (op) {
		system("cls");	printf("\n");
		printf("          Menu for Binary Tree\n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitBiTree\t2. Assign\n");
		printf("    	  3. DestroyTree\t4. Parent \n");
		printf("    	  5. ClearBiTree\t6. LeftChild\n");
		printf("    	  7. BiTreeEmpty\t8. RightChild\n");
		printf("    	  9. BiTreeDepth\t10. LeftSibling\n");
		printf("    	  11. Root\t12. RightSibling\n");
		printf("    	  13. Value\t14. InsertChild\n");
		printf("    	  15. DeleteChild\t16. PreOrderTraverse\n");
		printf("    	  17. InOrderTraverse\t18. PostOrderTraverse\n");
		printf("    	  19. LevelOrderTraverse\t20. LoadTree\n");
		printf("    	  21. saveTree\t22. InsertNode\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    Please select your option [0~12]:");
		scanf("%d%*c", &op);

		switch (op) {
		case 1://InitBiTree
			IBT1();
			break;
		case 2://Assign
			A2();
			break;
		case 3://Destroy
			DT3(); break;
		case 4:
			P4(); break;
		case 5:
			CBT5();break;
		case 6:
			break;
		case 7:
			BTE7();break;
		case 8:
			break;
		case 9:
			BTD9(); break;
		case 10:
			break;
		case 11:
			R11(); break;
		case 12:
			break;
		case 13:
			V13(); break;
		case 14:
			break;
		case 15:
			break;
		case 16:
			POT16(); break;
		case 17:
			IOT17(); break;
		case 18:
			POT18(); break;
		case 19:
			LOT19(); break;
		case 20:
			break;
		case 21:
			break;
		case 22:
			break;
		case 0:
			op = 0;
			break;
		}
		system("pause");
	}
	printf("\nSee you\n");
	return 0;
}



char *fgetsNoN(char *buf, int bufsize, FILE *stream) {
	char * returnP = fgets(buf, bufsize, stream);
	int i = 0;
	while (buf[i] != '\n') {
		i++;
	}
	buf[i] = '\0';
	return returnP;
}

//get tree node
Tree * getTreeFromName(char * name) {
	Tree * reTree = NULL;

	return reTree;
}
