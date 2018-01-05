#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef int ElemType; // make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define LIST_INIT_SIZE 100 // init length
#define LISTINCREMENT 10 //step-length when growing and cutting
#define LISTGAP 15 //redundant length needed to decide cutting list or not

typedef struct {
	ElemType * elem;
	int length;
	int listsize;
	char * name; //length = 30
}SqList;

Status InitList(SqList ** L);
void DestoryList(SqList * L);
void ClearList(SqList * L);
Status ListEmpty(SqList * L);
int ListLength(SqList * L);
Status GetElem(SqList * L, int i, ElemType * e);
int LocateElem(SqList * L, ElemType * e);
Status PriorElem(SqList * L, ElemType * cur_e, ElemType * pre_e);
Status NextElem(SqList * L, ElemType * cur_e, ElemType * next_e);
Status ListInsert(SqList * L, int i, ElemType * e);
Status ListDelete(SqList * L, int i, ElemType * e);
Status ListTraverse(SqList * L);
void growList(SqList * L);
void cutList(SqList * L);
Status SaveList(SqList * L);
Status LoadList(SqList ** L, char * name);
char *fgetsNoN(char *buf, int bufsize, FILE *stream);

//main page
int main() {
	printf("Hello world!\n");
	SqList * L = NULL;
	int op = 1;
	while (op) {
		system("cls");	printf("\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		if (L != NULL) {
			printf("  List:%s  is under your control .\n", L->name);
		}
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList		8. PriorElem\n");
		printf("    	  2. DestroyList	9. NextElem \n");
		printf("    	  3. ClearList		10. ListInsert\n");
		printf("    	  4. ListEmpty		11. ListDelete\n");
		printf("    	  5. ListLength		12. ListTraverse\n");
		printf("    	  6. GetElem		13. SaveList\n");
		printf("    	  7. LocateElem		14. LoadList\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    Please select your option [0~12]:");
		scanf("%d%*c", &op);

		int pos = 0;
		ElemType * cur = (ElemType *)malloc(sizeof(ElemType));

		switch (op) {
		case 1://IntiaList
			printf("\nPlease input the name of new list.\n");
			char * name = (char *)malloc(30 * sizeof(char)); fgetsNoN(name, 30, stdin);

			if (InitList(&L) == OK) printf("Linear Table has been created\n");
			else printf("\nFailed! Because there is no more space in stake's memory, we can't creat a new table.\n");
			L->name = name;
			break;
		case 2://DestoryList
			if (L == NULL) printf("You should init or load first!\n");
			else DestoryList(L);L=NULL;
			break;
		case 3://ClearList
			if (L == NULL) printf("You should init or load first!\n");
			else ClearList(L);
			break;
		case 4://ListEmpty
			if (L == NULL) printf("You should init or load first!\n");
			else {
				if (ListEmpty(L)) {
					printf("\n----This list is empty.\n");
				} else {
					printf("\n----This list is not empty.\n");
				}
			}
			break;
		case 5://ListLength
			if (L == NULL) printf("You should init or load first!\n");
			else printf("\n----The length of this list is %d.\n", ListLength(L));
			break;
		case 6://GetElem
			if (L == NULL) printf("You should init or load first!\n");
			else {
				printf("\nPlease input the element's position.\n");
				scanf("%d%*c", &pos);

				ElemType * get = (ElemType *)malloc(sizeof(ElemType));
				if (GetElem(L, pos, get)) {
					printf("\n----The element you get is %d.\n", *get);
				} else {
					printf("\n----Failed! The position you input is out of bound.\n");
				}
				free(get);
			}
			break;
		case 7://LocateElem
			if (L == NULL) printf("You should init or load first!\n");
			else {
				printf("\nPlease input the model element.\n");
				scanf("%d%*c", cur);
				pos = LocateElem(L, cur); pos++;
				if (pos != 0) {
					printf("\n----The index of the first element equal with yours is %d.\n", pos);
				} else {
					printf("\n----Failed! It seems like that we don't have such element.\n");
				}
			}
			break;
		case 8://PriorElem
			if (L == NULL) printf("You should init or load first!\n");
			else {
				printf("\nPlease input the beginning element:");
				scanf("%d%*c", cur);

				int pos = LocateElem(L, cur);
				if (pos != -1) {
					ElemType * get = (ElemType *)malloc(sizeof(ElemType));
					if (PriorElem(L, cur, get)) {
						printf("\n----The prior element you get is %d.\n", *get);
					} else {
						printf("\n----Failed! The element you select don't have a prior element.\n");
					}
					free(get);
				} else {
					printf("\n----Failed! We can't find such a element.\n");
				}

			}
			break;
		case 9://NextElem
			if (L == NULL) printf("You should init or load first!\n");
			else {
				printf("\nPlease input the beginning element:");
				scanf("%d%*c", cur);

				int pos = LocateElem(L, cur);
				if (pos != -1) {
					ElemType * get = (ElemType *)malloc(sizeof(ElemType));
					if (NextElem(L, cur, get)) {
						printf("\n----The next element you get is %d.\n", *get);
					} else {
						printf("\n----Failed! The element you select don't have a next element.\n");
					}
					free(get);
				} else {
					printf("\n----Failed! We can't find such a element.\n");
				}
			}
			break;
		case 10://ListInsert
			if (L == NULL) printf("You should init or load first!\n");
			else {
				printf("\n---Please input the position:");
				scanf("%d%*c", &pos);
				printf("\n---Please input the element:");
				ElemType * elemNew = (ElemType *)malloc(sizeof(ElemType));
				scanf("%d%*c", elemNew);

				if (ListInsert(L, pos, elemNew)) {
					printf("\n----Successful!\n");
				} else {
					printf("\n----Failed! The position you input is out of bound.\n");
				}
				free(elemNew);
			}
			break;
		case 11://ListDelete
			if (L == NULL) printf("You should init or load first!\n");
			else {
				printf("\n---Please input the position:");
				scanf("%d%*c", &pos);
				ElemType * elem = (ElemType *)malloc(sizeof(ElemType));

				if (ListDelete(L, pos, elem)){
                    printf("\n----Successfully delete element:%d!\n", *elem);
				} else{
                    printf("\n----Failed!\n");
				}

				free(elem);
			}
			break;
		case 12://ListTraverse
			if (L == NULL) printf("You should init or load first!\n");
			else if (!ListTraverse(L)) printf("\nThis list is empty!\n");
			break;
		case 13://SaveList
			if (L == NULL) printf("You should init or load first!\n");
			else {
				if (SaveList(L)) {
					printf("Successful!\n ");
				} else {
					printf("We can't open this file.\n ");
				}
			}
			break;
		case 14://LoadList
			printf("\n---Please input list's name:");
			char * nameIn = (char *)malloc(30 * sizeof(char));
			fgetsNoN(nameIn, 30, stdin);
			if (LoadList(&L, nameIn)) {
				printf("\n---Successfully load!\n");
			} else {
				printf("\n---Loading failed!\n");
			}
			break;
		case 0://Exit
			break;
		}
		free(cur);
//		Sleep(1000);
		system("pause");
	}
	printf("See you!\n");
	return 0;
}

//save a list to disk
Status SaveList(SqList * L) {
	FILE * fP = fopen(L->name, "wb");
	if (fP != NULL) {
		fwrite(L->elem, sizeof(ElemType), L->length, fP);
		fclose(fP);
		return TRUE;
	} else {
		printf("File open error\n ");
		fclose(fP);
		return FALSE;
	}
}

//loada list from disk, and the sqlist pointer will be the parameter-Lp
Status LoadList(SqList ** Lp, char * name) {
    SqList * L = *Lp;
    FILE * fP = fopen(name, "rb");

    if (fP == NULL) {
    	return FALSE;
		printf("File open error\n ");
		fclose(fP);
	}

	if (L != NULL) {
		DestoryList(L);
		*Lp = NULL;
	}
	if (InitList(Lp) != OK) return FALSE;
    L = *Lp;
	L->name = name;

	while (fread(&(L->elem[L->length]), sizeof(ElemType), 1, fP)) {
		L->length++;
		if (L->length == L->listsize) {
			growList(L);
		}
	}
	fclose(fP);
	return OK;
}

//initalize this list, give it space and make it empty
Status InitList(SqList ** Lp) {
	*Lp = (SqList *)malloc(sizeof(SqList));
	SqList * L = *Lp;
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));

	if (!L->elem) {
		exit(0);
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}

//grow this list's space
void growList(SqList * L) {
	L->elem = (ElemType *)realloc(L->elem, L->listsize + LISTINCREMENT * sizeof(ElemType));
    L->listsize += LISTINCREMENT;
	if (L->elem == NULL) exit(0);
}

void cutList(SqList * L) {//Pay attention to the opportunity to avoid frequently cutting and growing
	L->elem = (ElemType *)realloc(L->elem, L->listsize - LISTINCREMENT * sizeof(ElemType));
    L->listsize -= LISTINCREMENT;
	if (L->elem == NULL) exit(0);
}

//Destory the whole list with its space
void DestoryList(SqList * L) {
	free(L->elem);
	free(L->name);
	free(L);
}

//clear the data of this list
void ClearList(SqList * L) {
	int length = L->length;
	int i;
	for (i = 0; i < length; i++) {
		L->elem[i] = 0;
	}
	L->length = 0;
}

//empty->TRUE not-empty->FALSE
Status ListEmpty(SqList * L) {
	if (L->length == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//return the length of this list
int ListLength(SqList * L) {
	return L->length;
}

//get element by index-i
Status GetElem(SqList * L, int i, ElemType * e) {
    i--;
	if (i < L->length) {
		*e = L->elem[i];
		return TRUE;
	} else {//IndexOutOfBoundException
		return FALSE;
	}
}

//return the prior item of parameter-cur_e
Status PriorElem(SqList * L, ElemType * cur_e, ElemType * pre_e) {
	int length = L->length;
	int i = 0;
	*pre_e = 0;
	for (i = 0; i < length; i++) {
		if (L->elem[i] == *cur_e) {
			if (i >= 1) {
				*pre_e = L->elem[i - 1];
				return TRUE;
			}
		}
	}
	return FALSE;
}

//return the prior item of parameter-cur_e
Status NextElem(SqList * L, ElemType * cur_e, ElemType * next_e) {
	int length = L->length;
	int i = 0;
	*next_e = 0;
	for (i = 0; i < length; i++) {
		if (L->elem[i] == *cur_e) {
			if (i + 1 < length) {
				*next_e = L->elem[i + 1];
				return TRUE;
			}
		}
	}
	return FALSE;
}

//insert a element into this list
Status ListInsert(SqList * L, int i, ElemType * e) {
    i--;
	int index = L->length;
	if (i > index) {//IndexOutOfBoundException
		return FALSE;
	}
	if (L->length == L->listsize) {
		growList(L);
	}
	ElemType * head = L->elem;
	for (index = L->length; index > i; index--) {
		head[index] = head[index - 1];
	}
	head[i] = *e;
	L->length++;
	return TRUE;
}

//delete a element from this list
Status ListDelete(SqList * L, int i, ElemType * e) {
	if (i >= L->length){
        *e = 0;
        return FALSE;
	}
	int temp = i;
	int length = L->length;
	ElemType * head = L->elem;
	*e = head[temp];
	for (temp = i; temp < length - 1; temp++) {
		head[temp] = head[temp + 1];
	}
	head[length - 1] = 0;//reset this value
	L->length--;
	if (15 <= L->listsize - length) {//cut list
		cutList(L);
	}
	return TRUE;
}

//traverse this list and output all element
Status ListTraverse(SqList * L) {
	int i;
	printf("\n-----------all elements -----------------------\n");
	for (i = 0; i<L->length; i++) printf("%d ", L->elem[i]);
	printf("\n------------------ end ------------------------\n");
	return L->length;//return the length of list
}

//return a element's index of list-l
int LocateElem(SqList * L, ElemType * e) {
	int i = 0;
	ElemType * head = L->elem;
	for (i = 0; i < L->length; i++) {
		if (*e == head[i]) {
			return i;
		}
	}
	return -1;
}

//Override fgets, so that we can get a string in inputstream without '\n'
char *fgetsNoN(char *buf, int bufsize, FILE *stream) {
	char * returnP = fgets(buf, bufsize, stream);
	int i = 0;
	while (buf[i] != '\n') {
		i++;
	}
	buf[i] = '\0';
	return returnP;
}

