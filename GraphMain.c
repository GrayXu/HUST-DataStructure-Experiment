#include <windows.h>
#include <Graph.h>
typedef int ElemType;//make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0

/*
	print some infomation to users
	1.Stack over flow
	2.There is not such vertex
	3.Successful!
	4.You should create a graph first
*/
void printInfo(int code) {
	switch (code) {
	case 1:
		printf("Stack over flow.\n");
		break;
	case 2:
		printf("There is not such vertex.\n");
		break;
	case 3:
		printf("Successful!\n");
		break;
	case 4:
		printf("You should create a graph first.\n");
		break;
	}
}

//bro-function of func-"fgets", which can get string input without '\n'
char *fgetsNoN(char *buf, int bufsize, FILE *stream) {
	char * returnP = fgets(buf, bufsize, stream);
	int i = 0;
	while (buf[i] != '\n') {
		i++;
	}
	buf[i] = '\0';
	return returnP;
}

/*
	a logistic func to low donw lines of code
*/
Vertex * getKeyNode(Graph * g) {
	printf("\nPlease input the key of this vertex:");
	ElemType key = 0; scanf("%d%*c", &key);
	return FindVertex(g, key);
}

/*
	print the top-layer menu
*/
void printMenu(Graph * g) {
	system("cls");	
	
	printf("----Menu for Undirected and Unweighted Graph----\n\n");
	printf("    	  1. CreateEmptyGraph\t2. DestoryGraph\n");
	printf("    	  3. LocateVex\t\t4. GetVex \n");
	printf("    	  5. PutVex\t\t6. FirstAdjVex\n");
	printf("    	  7. NextAdjVex\t\t8. InsertVex\n");
	printf("    	  9. DeleteVex\t\t10. InsertArc\n");
	printf("    	  11. DeleteArc\t\t12. DFSTraverse\n");
	printf("    	  13. BFSTraverse\t0. Exit\n");
	

	if (g) {
		printf("\n------------------Vertexs' Key List--------------\n");
		Vertex * startVex = g->head;
		while (startVex) {
			printf("%d,", startVex->key);
			startVex = startVex->next;
		}
		printf("\n-------------------------------------------------\n");
	} else {
		printf("\n-------------------------------------------------\n");
	}
	
}

int main() {

	int op = 1;
	Graph * g = NULL;
	while (op) {
		printMenu(g);//print the top-layer menu
		printf("\tPlease select your option [0~13]:");
		scanf("%d%*c", &op);

		switch (op) {
		case 1://CreatEmptyGraph
			if (!CreateEmptyGraph(&g)) printInfo(1);
			else printInfo(3);
			break;
		case 2://DestoryGraph
			if (!g) printInfo(4);
			else {
				DestoryGraph(g);
				printInfo(3);
			}
			break;
		case 3://LocateVex
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"data\" of this vertex:");
				ElemType data = 0; scanf("%d%*c", &data);
				int key = LocateVex(g, data);
				if (key == NOT_FOUND_CODE) printf("we don't find such a vertex having this data.\n");
				else printf("data of this vertex is %d.\n", key);
			}
			break;
		case 4://GetVex
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"key\" of this vertex:");
				ElemType key = 0; scanf("%d%*c", &key);
				int data = GetVex(g, key);
				if (data == NOT_FOUND_CODE) printf("we don't find such a vertex having this key.\n");
				else printf("key of this vertex is %d.\n", data);
			}
			break;
		case 5://PutVex
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"key\" of this vertex:");
				ElemType key = 0; scanf("%d%*c", &key);
				Vertex * v = FindVertex(g, key);
				if (!v) printInfo(2);
				else {
					printf("\nPlease input a new value for this vertex:");
					ElemType newValue = 0; scanf("%d%*c", &newValue);
					PutVex(g, v, newValue);
				}
			}
			break;
		case 6://FirstAdjVex
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"key\" of this vertex:");
				ElemType key = 0; scanf("%d%*c", &key);
				Vertex * v = FindVertex(g, key);
				if (!v) printInfo(2);
				else {
					Vertex * getVer = FirstAdjVex(g, v);
					if (!getVer) printf("this vertex don't have adj-vex\n");
					else { 
						Vertex * trueV = FindVertex(g, getVer->key);
						printf("the first adj-vex: key=%d value=%d\n", trueV->key, trueV->data);
					}
				}
			}
			break;
		case 7://NextAdjVex
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"key\" of this vertex:");
				ElemType key = 0; scanf("%d%*c", &key);
				Vertex * v = FindVertex(g, key);
				if (!v) printInfo(2);
				else {
					printf("\nPlease input \"key\" of adj-vex of the prior vertex:");
					ElemType keyAdj = 0; scanf("%d%*c", &keyAdj);
					Vertex * vAdj = FindVertex(g, keyAdj);
					if(!vAdj) printInfo(2);
					else {
						Vertex * nextV = NextAdjVex(g, v, vAdj);
						if (!nextV) printf("We don't find such a next-adj-vex.\n");
						else { 
							Vertex * trueV = FindVertex(g, nextV->key);
							printf("next-adj-vex: key=%d value=%d", trueV->key, trueV->data);
						}
					}
				}
			}
			break;
		case 8://InsertVex
			if (!g) printInfo(4);
			else {
				printf("Please input a new key of this vertex:");
				ElemType key = 0; scanf("%d%*c", &key);
				if (FindVertex(g, key)) printf("This key has been occupied.\n");
				else {
					printf("Please input data of this vertex:");
					ElemType data = 0; scanf("%d%*c", &data);
					Vertex * newVertex = (Vertex *)malloc(sizeof(Vertex));
					newVertex->key = key; newVertex->data = data; newVertex->next = NULL;
					if (!newVertex) { 
						printInfo(1); 
						free(newVertex);
					}
					else {
						InsertVex(g, newVertex);
						printInfo(3);
					}
				}
			}
			break;
		case 9://DeleteVex
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"key\" of this vertex:");
				ElemType key = 0; scanf("%d%*c", &key);
				Vertex * v = FindVertex(g, key);
				if (!v) printInfo(2);
				else {
					DeleteVex(g, v); printInfo(3);
				}
			}
			break;
		case 10://InsertArc
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"key\" of two vertexs( splited by space ):");
				ElemType keyV = 0; ElemType keyW = 0;
				scanf("%d%*c%d%*c", &keyV, &keyW);
				Vertex * v = FindVertex(g, keyV); Vertex * w = FindVertex(g, keyW);
				if (v && w) {
					if (InsertArc(g, v, w)) printInfo(3);
					else printf("perhaps these two vertexs have been connected already or some error else happen!");
				} else {
					printInfo(2);
				}
			}
			break;
		case 11://DeleteArc
			if (!g) printInfo(4);
			else {
				printf("\nPlease input \"key\" of two vertexs( splited by space ):");
				ElemType keyV = 0; ElemType keyW = 0;
				scanf("%d%*c%d%*c", &keyV, &keyW);
				Vertex * v = FindVertex(g, keyV); Vertex * w = FindVertex(g, keyW);
				if (v && w) {
					if (DeleteArc(g, v, w)) printInfo(3);
					else printf("Error!");
				} else {
					printInfo(2);
				}
			}
			break;
		case 12://DFSTraverse
			if (!g) printInfo(4);
			else {
				printf("----DFS starts.----\n");
				DFSTraverse(g);
				printf("----DFS end.----\n");
			}
			break;
		case 13://BFSTraverse
			if (!g) printInfo(4);
			else {
				printf("----BFS starts.----\n");
				BFSTraverse(g);
				printf("----BFS end.----\n");
			}
			break;
		case 0://Exit
			op = 0;
			break;
		}
		system("pause");
	}
	printf("\nSee you\n");
	return 0;
}

