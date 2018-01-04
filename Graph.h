#include <QueueForGraph.h>

typedef int ElemType;//make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define VERTEX_LIST_SIZE 31
#define NOT_FOUND_CODE 90071

/**
* by adjacency list. All parameter vertexs are in the first line
*/

typedef struct graph {
	int vertexCount;
	Vertex * head;
} Graph;

typedef struct edge {
	/*Vertex * a;
	Vertex * b;*/
	ElemType keyV;
	ElemType keyW;
} Edge;

//Status CreateGraph(Grapgh ** g, Vertex ** vertexList, Edge ** edgeList);//better a more convient way to create a new graph
Status CreateEmptyGraph(Graph ** gP);
Status DestoryGraph(Graph * g);
ElemType LocateVex(Graph * g, ElemType data);//Confused about the meaning of this function
ElemType GetVex(Graph * g, ElemType loc);
Status PutVex(Graph * g, Vertex * v, ElemType value);
Vertex * FirstAdjVex(Graph * g, Vertex * v);
Vertex * NextAdjVex(Graph * g, Vertex * v, Vertex * w);
Status InsertVex(Graph * g, Vertex * v);
Status DeleteVex(Graph * g, Vertex * v);
Status InsertArc(Graph * g, Vertex * v, Vertex * w);
Status DeleteArc(Graph * g, Vertex * v, Vertex * w);
void DFSTraverse(Graph * g);
void BFSTraverse(Graph * g);

Status deleteVexFromAdj(Vertex * del, Vertex ** startVex);
void deleteAdjLink(Vertex * v);
void dfs_recurve(Graph * g, Vertex * v);
Status isMarked(Vertex * v);
Vertex * FindVertex(Graph * g, ElemType key);
Vertex * addVexToAdjEnd(Vertex * startVex, Vertex * newVex);
Status isAdj(Graph * g, Vertex * v, Vertex * w);

//Create a graph with no vertex and edge
Status CreateEmptyGraph(Graph ** gP) {
	if (*gP) DestoryGraph(*gP);

	Graph * g = (Graph *)malloc(sizeof(Graph));
	if (!g) return FALSE;
	*gP = g;

	g->vertexCount = 0;
	g->head = NULL;
	return TRUE;
}

/*
Find a vertex by a key in graph-g
*/
Vertex * FindVertex(Graph * g, ElemType key) {
	Vertex * startVex = g->head;
	while (startVex) {
		if (startVex->key == key) return startVex;
		startVex = startVex->next;
	}
	return NULL;
}

//delete a adj-link
void deleteAdjLink(Vertex * startVex) {
	Vertex * v = startVex; Vertex * vAdj = v;
	while (v->adj) {
		vAdj = v->adj;
		free(v);
		v = vAdj;
	}
	free(v);
}

//Destory the whole graph
Status DestoryGraph(Graph * g) {
	Vertex * startVex = g->head;
	while (startVex) {
		Vertex * tempV = startVex->next;
		deleteAdjLink(startVex);
		startVex = tempV;
	}
	free(g);
	return TRUE;
}

//this func is used to find node's key from value
ElemType LocateVex(Graph * g, ElemType data) {
	Vertex * startVex = g->head;
	while (startVex) {
		if (startVex->data == data) {//find the vertex we want
			return startVex->key;
		}
		startVex = startVex->next;
	}
	return NOT_FOUND_CODE;
}

//return the first vextex linked with Vretex-v
Vertex * FirstAdjVex(Graph * g, Vertex * v) {
	return v->adj;
}

//this is a WTF function
Vertex * NextAdjVex(Graph * g, Vertex * v, Vertex * w) {
	Vertex * tempV = v;
	while (tempV) {
		//'cause w is in the first link, so w don't have adj vertex
		if (tempV->key == w->key) {
			return tempV->adj;
		}

		tempV = tempV->adj;
	}
	return NULL;
}

//this func is used to find node's value from key
ElemType GetVex(Graph * g, ElemType loc) {
	Vertex * startVex = g->head;
	while (startVex) {
		if (startVex->key == loc) {//find the vertex we want
			return startVex->data;
		}
		startVex = startVex->next;
	}
	return NOT_FOUND_CODE;
}

/*
put a value for a specialized vertex
*/
Status PutVex(Graph * g, Vertex * v, ElemType value) {
	if (v) {
		v->data = value;
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
Insert a nude vex in this graph, which would the last vertex in first line
*/
Status InsertVex(Graph * g, Vertex * v) {

	Vertex * lastVex = g->head;
	if (lastVex) {
		while (lastVex->next) {
			lastVex = lastVex->next;
		}
		//now the lastVex is the last vertex in this graph
		lastVex->next = v;
	} else {
		g->head = v;
	}
	v->next = NULL;
	v->adj = NULL;

	g->vertexCount++;
	//then we should update v's linking infomation, but v is nude???
	return TRUE;
}

/**
*	calling this func when you need to delete a vertex from a adj-link.
*	return a new head vextex pointer for updating head outside
*	we need a ** pointer parameter in case we have to change start-vertex
*/
Status deleteVexFromAdj(Vertex * del, Vertex ** startVex) {
	Vertex * tempV = *startVex;

	if (tempV->key == del->key) {//lucky enough, it's the first one
		*startVex = tempV->adj;
		free(tempV);
		return TRUE;
	}
	while (tempV->adj != NULL) {

		if (tempV->adj->key == del->key) {
			Vertex * newAdj = tempV->adj->adj;
			free(tempV->adj);
			tempV->adj = newAdj;
			return TRUE;
		}

		tempV = tempV->adj;
	}
	printf("error\n");
	return FALSE;
}

/*
delete a vertex and clean all edge concered about it
*/
Status DeleteVex(Graph * g, Vertex * v) {
	Vertex * startVex = g->head;
	while (startVex) {
		if (startVex->key == v->key) {
			deleteAdjLink(startVex);
		} else {
			if (!deleteVexFromAdj(v, &startVex)) return FALSE;
		}
		startVex = startVex->next;
	}
	g->vertexCount--;
	return TRUE;
}

/*
find out v and w is connected or not.
return: TRUE or FALSE
*/
Status isAdj(Graph * g, Vertex * v, Vertex * w) {
	Vertex * startVex = g->head;
	int flag = 1;
	while (startVex) {
		if (startVex->key == v->key) {//find the vertex we want
			if (flag) {
				Vertex * tempV = startVex->adj;
				while (tempV) {
					if (tempV->key == w->key) return TRUE;
					tempV = tempV->adj;
				}
				flag = 0;
			}
		} else if (startVex->key == w->key) {
			if (flag) {
				Vertex * tempV = startVex->adj;
				while (tempV) {
					if (tempV->key == v->key) return TRUE;
					tempV = tempV->adj;
				}
				flag = 0;
			}
		}

		startVex = startVex->next;
	}
	return FALSE;
}

/*
insert a arc into this graph and update lots of relationships....
*/
Status InsertArc(Graph * g, Vertex * v, Vertex * w) {
	Vertex * startVex = g->head;
	if (isAdj(g, v, w)) return FALSE;//check they are connected or not

	Vertex * vCopy = (Vertex *)malloc(sizeof(Vertex)); Vertex * wCopy = (Vertex *)malloc(sizeof(Vertex));
	vCopy->next = NULL; wCopy->next = NULL;
	vCopy->key = v->key; wCopy->key = w->key;
	vCopy->adj = NULL; wCopy->adj = NULL;
	//in fact we don't have to value data, so that we don't have to update all same-vertex in all adj-links

	//all vertex in adj-link is a copy of the origin

	int flag = 0;

	while (startVex) {
		if (startVex->key == v->key) {//find the vertex we want
			startVex->adj = addVexToAdjEnd(startVex->adj, wCopy);
			flag++;
		} else if (startVex->key == w->key) {
			startVex->adj = addVexToAdjEnd(startVex->adj, vCopy);
			flag++;
		}//we don't check v or w is already have linking or not
		startVex = startVex->next;
	}

	if (flag == 2) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
A tool func to help add a vertex to a adj-link's tail
Return: the new head of adj-link after adding
*/
Vertex * addVexToAdjEnd(Vertex * firstAdjVex, Vertex * newVex) {

	Vertex * tempV = firstAdjVex;
	if (tempV) {
		while (tempV->adj) {
			tempV = tempV->adj;
		}//make tempV become the last one in this adj-link
		tempV->adj = newVex;
		return firstAdjVex;
	} else {
		return newVex;
	}
}

/*
delete a arc from this graph
*/
Status DeleteArc(Graph * g, Vertex * v, Vertex * w) {
	Vertex * startVex = g->head;
	int flag = 0;
	while (startVex) {
		if (startVex->key == v->key) {
			if (deleteVexFromAdj(w, &startVex)) flag++;
		} else if (startVex->key == w->key) {
			if (deleteVexFromAdj(v, &startVex)) flag++;
		}
		startVex = startVex->next;
	}
	if (flag == 2) return TRUE;
	else return FALSE;
}

//some data to support two search functions
ElemType * markVertexKeys;//save keys
int size_markVertex;

//figure out parameter Vertex-v is marked or not, so that we can make decision outside
Status isMarked(Vertex * v) {
	int i = 0;
	for (i = 0; i < size_markVertex; i++) {
		if (markVertexKeys[i] == v->key) {
			return TRUE;
		}
	}
	return FALSE;
}

/*
DFS depth first search
*/
void DFSTraverse(Graph * g) {
	size_markVertex = 0;
	markVertexKeys = (ElemType *)malloc(sizeof(ElemType) * g->vertexCount);
	int i = 0;
	for (i = 0; i < g->vertexCount; i++) {
		markVertexKeys[i] = NOT_FOUND_CODE;//init this array
	}
	//start dfs
	dfs_recurve(g, g->head);
	//end dfs
	free(markVertexKeys);
}
void dfs_recurve(Graph * g, Vertex * v) {
	markVertexKeys[size_markVertex] = v->key; size_markVertex++;
	//do sth
	Vertex * trueV = FindVertex(g, v->key);
	printf("key=%d value=%d\n", trueV->key, trueV->data);

	Vertex * tempV = trueV->adj;
	while (tempV) {
		if (!isMarked(tempV)) {
			dfs_recurve(g, tempV);//not be marked so we traverse this node
		}
		tempV = tempV->adj;
	}
}

/*
BFS breadth first search
*/
void BFSTraverse(Graph * g) {
	if (!g->head) return;
	Queue * q;
	if (!initQueue(&q)) return;

	size_markVertex = 0;
	markVertexKeys = (ElemType *)malloc(sizeof(ElemType) * g->vertexCount);
	if (!markVertexKeys) return;

	int i = 0;
	for (i = 0; i < g->vertexCount; i++) {
		markVertexKeys[i] = 0;//init this array
	}
	//init-work is done

	enQueue(q, g->head);
	printf("key=%d value=%d\n", g->head->key, g->head->data);//startpoint
	markVertexKeys[size_markVertex] = g->head->key; size_markVertex++;

	while (q->length) {//when Queue is not empty
		Vertex * v = deQueue(q);
		Vertex * startVex = g->head;
		while (startVex) {
			if (startVex->key == v->key) {//found this vertex's adj-vertexs
				Vertex * tempV = startVex->adj;
				while (tempV) {
					if (!isMarked(tempV)) {
						Vertex * trueV = FindVertex(g, tempV->key);
						printf("key=%d value=%d\n", trueV->key, trueV->data);
						enQueue(q, tempV);
						markVertexKeys[size_markVertex] = tempV->key; size_markVertex++;
					}
					tempV = tempV->adj;
				}
				break;
			}
			startVex = startVex->next;
		}
	}

	//free memory
	free(markVertexKeys);
	destroyQueue(q);
}
