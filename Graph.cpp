#include <stdio.h>
#include <stdbool.h>

#define MAX 100  // Assume a maximum number of vertices

// Define the Status type
typedef int Status;
#define OK 1
#define ERROR 0

// Define the Graph structure
typedef struct {
    int vexnum;  // Number of vertices
    int adjMatrix[MAX][MAX];  // Adjacency matrix
} Graph;

bool visited[MAX];  // Visit flag array
Status(*VisitFunc)(int v);  // Function pointer to a visit function


//Spanning tree
// The cost of a spanning tree is the sum of the costs of the edges in the tree.
//Every spanning tree with n vertices contains exactly n - 1 edges.
//If we add any edge to a free tree, we get a cycle.
//

//
// directed tree(������): 
// the tree with one node whose in-degree is zero. Other nodes��s in-degree is 1.
//

//Adjacency Matrix(�ڽӾ���)
//����ͼ�п����ȿ��У�����ȿ���
//��Ȩ���û�������������ʾ

//�洢����ͨ����ռ��N^2,�Ƚ��˷ѣ����Դ����ڽӱ�(Adjacency List )�У��ռ�����ΪO(E+N),������ϡ��ͼ,��¼����(��¼��ȵ����ڽӱ�),����ͼ�й�ϵ�ͼ�¼


//------------------------Graph Traversal-------------------------
//Depth-First Traversal  O(n^2)
void DFS(Graph G, int v) {
    visited[v] = true;  // Mark the current vertex as visited
    VisitFunc(v);  // Perform the visit operation

    // Recur for all adjacent vertices
    for (int w = 0; w < G.vexnum; ++w) {
        if (G.adjMatrix[v][w] != 0 && !visited[w]) {
            DFS(G, w);
        }
    }
}
void DFSTraverse(Graph G, Status(*Visit)(int v)) {
    // Assign the function pointer to the provided function
    VisitFunc = Visit;

    // Initialize the visited array to false
    for (int v = 0; v < G.vexnum; ++v) {
        visited[v] = false;
    }

    // Perform DFS on each vertex that has not been visited
    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) {
            DFS(G, v);  // Call DFS on unvisited vertex
        }
    }
}
// Example visit function
Status Visit(int v) {
    printf("Visited vertex: %d\n", v);
    return OK;
}

//Breadth-First Traversal
//O(n^2)
typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;
void InitQueue(Queue* Q) {
    Q->front = 0;
    Q->rear = 0;
}
bool IsQueueEmpty(Queue* Q) {
    return Q->front == Q->rear;
}
bool EnQueue(Queue* Q, int e) {
    if ((Q->rear + 1) % MAX == Q->front) {
        return false;  // ������
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX;
    return true;
}
bool DeQueue(Queue* Q, int* e) {
    if (IsQueueEmpty(Q)) {
        return false;  // ���п�
    }
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX;
    return true;
}

void BFSTraverse(Graph G, Status(*Visit)(int v)) {
    // ��ʼ�����ʱ�־����Ϊfalse
    for (int v = 0; v < G.vexnum; ++v) {
        visited[v] = false;
    }

    Queue Q;
    InitQueue(&Q);

    // ��ÿ��δ���ʵĶ���ִ��BFS
    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) {
            visited[v] = true;
            VisitFunc(v);
            EnQueue(&Q, v);

            while (!IsQueueEmpty(&Q)) {
                //�ó���һ�ν��б����Ľ��
                int u;
                DeQueue(&Q, &u);
                for (int w = 0; w < G.vexnum; ++w) {
                    if (G.adjMatrix[u][w] != 0 && !visited[w]) {
                        visited[w] = true;
                        VisitFunc(w);
                        EnQueue(&Q, w);
                    }
                }
            }
        }
    }
}

//---------------------------------Topological Sort------------------------------------
void TopologicalSort(Graph G) {
    int inDegree[MAX] = { 0 };  // �������
    int topologicalOrder[MAX];  // �洢����������
    int index = 0;
    // ����ÿ����������
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (G.adjMatrix[i][j] != 0) {
                inDegree[j]++;
            }
        }
    }
    Queue Q;
    InitQueue(&Q);
    // ���������Ϊ0�Ķ������
    for (int i = 0; i < G.vexnum; ++i) {
        if (inDegree[i] == 0) {
            EnQueue(&Q, i);
        }
    }
    // ִ����������
    while (!IsQueueEmpty(&Q)) {
        int u;
        DeQueue(&Q, &u);
        topologicalOrder[index++] = u;

        for (int v = 0; v < G.vexnum; ++v) {
            if (G.adjMatrix[u][v] != 0) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    EnQueue(&Q, v);
                }
            }
        }
    }
    // ����Ƿ���ڻ�
    if (index != G.vexnum) {
        printf("ͼ�д��ڻ����޷�������������\n");
        return;
    }
    // ��ӡ����������
    printf("������������\n");
    for (int i = 0; i < index; ++i) {
        printf("%d ", topologicalOrder[i]);
    }
    printf("\n");
}

//--------------------------------Shortest Paths Problem------------------------------------
//Strategy: Breadth-first search
#define INF 9999  // ���ڱ�ʾ������ֵ
void Dijkstra(Graph G, int start, int dist[], int prev[]) {
    bool visited[MAX] = { false };  // ���ʱ�־����
    for (int i = 0; i < G.vexnum; ++i) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < G.vexnum; ++i) {
        int u = -1;
        int minDist = INF;
        for (int j = 0; j < G.vexnum; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) break;  // ʣ�ඥ�㲻��ͨ

        visited[u] = true;

        for (int v = 0; v < G.vexnum; ++v) {
            if (!visited[v] && G.adjMatrix[u][v] != 0 && dist[u] + G.adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + G.adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }
}


//---------------------------------Minimum Spanning Tree------------------------------------------
//In the minimum spanning tree
//n vertices and n - 1 edges
//it is acyclic
//It has the lowest total cost.

//!!!!Prim's Algorithm  and Kruskal's Algorithm. 
//! Prim's Algorithm
int MinKey(int key[], bool mstSet[], int vexnum) {
    int min = INF, minIndex;

    for (int v = 0; v < vexnum; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}
void PrimMST(Graph G) {
    int parent[MAX];  // ���ڴ洢��С������
    int key[MAX];  // ���ڴ洢��СȨֵ
    bool mstSet[MAX];  // ���ڱ�ʾ�����Ƿ��������С��������

    // ��ʼ�����м�ֵΪ�����mstSet[] Ϊ false
    for (int i = 0; i < G.vexnum; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }
    // ѡ���һ��������Ϊ��ʼ��
    key[0] = 0;  // ʹ��һ��������Ϊ���ڵ�
    parent[0] = -1;  // ��һ���ڵ�û�и��ڵ�
    for (int count = 0; count < G.vexnum - 1; count++) {
        // ��δ��������С�������еĶ�����ѡȡȨֵ��С�Ķ���
        int u = MinKey(key, mstSet, G.vexnum);
        // ��ѡȡ�Ķ�����ӵ���С������������
        mstSet[u] = true;
        // ������ѡȡ�������ڵĶ���ļ�ֵ�͸��ڵ�
        for (int v = 0; v < G.vexnum; v++) {
            // ���¶���v�ļ�ֵֻ����������С�������У����ڴ�u��v�ıߣ���ȨֵС��v��ǰ�ļ�ֵ
            if (G.adjMatrix[u][v] && mstSet[v] == false && G.adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = G.adjMatrix[u][v];
            }
        }
    }
    // ��ӡ��С������
    printf("�� \tȨֵ\n");
    for (int i = 1; i < G.vexnum; i++) {
        printf("%d - %d \t%d \n", parent[i], i, G.adjMatrix[i][parent[i]]);
    }
}

//Kruskal's Algorithm. 
typedef struct {
    int u, v, weight;
} Edge;

int Find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return Find(parent, parent[i]);
}
// ���鼯�ĺϲ�����
void Union(int parent[], int rank[], int x, int y) {
    int xroot = Find(parent, x);
    int yroot = Find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    }
    else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    }
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}
// ���ߵ�Ȩֵ����
int compare(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}