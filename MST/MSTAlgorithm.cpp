#include <iostream>

using namespace std;

const int MAX_ADJACENT_VERTICES = 5;
const int MAX_EDGES = 17;
const int MAX_MST_EDGES = 5;

struct Edge {
    int from;
    int to;
    int weight;
    
    Edge(int v1, int v2, int weight){
        this->from = v1;
        this->to = v2;
        this->weight = weight;
    }

    void print(){
        cout << from << " - " << to << " -> " << weight << endl;
    }
};

struct MinHeap{
    int heapSize;
    int heapNumMax;
    int* heapArray;
    int* itemTracker;
    int minItem;
    int minKey;
    
    MinHeap(int inputMax){
        heapSize = 0;
        heapNumMax = inputMax;
        heapArray = new int[heapNumMax];
        itemTracker = new int[heapNumMax];
    }

    ~MinHeap() {
        delete[] heapArray;
        delete[] itemTracker;
    }

    int parent(int i){
        return (i-1)/2;
    }

    int leftChild(int i) {
        return (2*i + 1);
    }

    int rightChild(int i) {
        return (2*i + 2);
    }

    void swap(int *a, int *b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapify(int inputIndex){
        int minIndex = inputIndex;
        int left = leftChild(minIndex);
        int right = rightChild(minIndex);

        if(left < heapSize && heapArray[left] < heapArray[minIndex]){
            minIndex = left;
        }
        if(right < heapSize && heapArray[right] < heapArray[minIndex]){
            minIndex = right;
        }
        if (minIndex != inputIndex){
            swap(&heapArray[inputIndex], &heapArray[minIndex]);
            swap(&itemTracker[inputIndex], &itemTracker[minIndex]);
            heapify(minIndex);
        }
    }

    void insert(int item, int key){
        if (heapSize == heapNumMax){
            cout << "Overflow: Could not insert into Heap" << endl;
            return;
        }

        heapSize++;
        int heapIndex = heapSize-1;
        heapArray[heapIndex] = key;
        itemTracker[heapIndex] = item;

        while (heapIndex != 0 && heapArray[parent(heapIndex)] > heapArray[heapIndex]){
            swap(&heapArray[heapIndex], &heapArray[parent(heapIndex)]);
            swap(&itemTracker[heapIndex], &itemTracker[parent(heapIndex)]);
            heapIndex = parent(heapIndex);
        }
    }
    void getMin(){
        if(heapSize <=0) {
            cout << "Error Heap is Empty" << endl;
        }
        minItem = itemTracker[0];
        minKey = heapArray[0];
    }

    void extractMin(){
        if(heapSize <=0) {
            cout << "Error Heap is Empty" << endl;
        }
        if (heapSize == 1) {
            heapSize--;
        }
        heapArray[0] = heapArray[heapSize - 1];
        itemTracker[0] = itemTracker[heapSize - 1];
        heapSize--;
        heapify(0);
    }

    void decreaseKey(int index, int key){
        heapArray[index] = key;
        while (index != 0 && heapArray[parent(index)] > heapArray[index]){
            swap(&heapArray[index], &heapArray[parent(index)]);
            swap(&itemTracker[index], &itemTracker[parent(index)]);
            index = parent(index);
        }
    }

    void printHeapArray(){
        for (int i = 0; i < heapSize; i++){
            cout << heapArray[i] << " ";
        }
        cout << endl;
    }
    void printHeapVertices(){
        for(int i = 0; i < heapSize; i++){
            cout << itemTracker[i] << " ";
        }
        cout << endl;
    }
};

class Graph {
public:
    int adjMatrix[MAX_ADJACENT_VERTICES][MAX_ADJACENT_VERTICES];
    int vertexCount;
    Graph(int inputMatrix[][MAX_ADJACENT_VERTICES], int matrixSize) {
        vertexCount = matrixSize;
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                int inputWeight = inputMatrix[i][j];
                adjMatrix[i][j] = inputWeight;
            }
        }
    }

    void printGraph(){

        cout << "Here is the Adjacency Matrix for your Graph: " << endl;
        for(int i = 0; i < vertexCount; i++){
            for(int j = 0; j < vertexCount; j++){
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }      

    void primMST(){
        int permanent[MAX_ADJACENT_VERTICES];
        int unvisited[MAX_ADJACENT_VERTICES];
        Edge* MST[MAX_MST_EDGES] = {nullptr};
        Edge* foundEdges[MAX_EDGES] = {nullptr};
        int MSTEdgeCount = 0;
        int foundEdgeCount = 0;
        
        MinHeap* graphMinHeap = new MinHeap(MAX_EDGES);
        
        for(int v = 0; v < vertexCount; v++){
            permanent[v] = -1;
            unvisited[v] = v;
        }
        
        int start = 0;
        permanent[start] = start;
        unvisited[start] = -1;
        
        while(MSTEdgeCount < vertexCount - 1){
            for(int neighbor = 0; neighbor < vertexCount; neighbor++){
                if(adjMatrix[start][neighbor] != 0){
                    Edge* foundEdge = new Edge(start, neighbor, adjMatrix[start][neighbor]);
                    foundEdges[foundEdgeCount] = foundEdge;
                    graphMinHeap->insert(foundEdgeCount, adjMatrix[start][neighbor]);
                    foundEdgeCount++;
                }
            }
            graphMinHeap->getMin();
            int minEdgeIndex = graphMinHeap->minItem;
            int toVertex = foundEdges[minEdgeIndex]->to;
            
            while(permanent[foundEdges[minEdgeIndex]->from] == foundEdges[minEdgeIndex]->from && permanent[foundEdges[minEdgeIndex]->to] == foundEdges[minEdgeIndex]->to){
                graphMinHeap->extractMin();
                graphMinHeap->getMin();
                minEdgeIndex = graphMinHeap->minItem;
                toVertex = foundEdges[minEdgeIndex]->to;
            }
            MST[MSTEdgeCount] = foundEdges[minEdgeIndex];
            MSTEdgeCount++;
            permanent[toVertex] = toVertex;
            unvisited[toVertex] = -1;
            start = toVertex;   
        }     

        for(int e = 0; e < MSTEdgeCount; e++){
            MST[e]->print();
        } 

        delete graphMinHeap;
    }

    void kruskalMST(){
        int MSTEdgeCount = 0;
        int foundEdgeCount = 0;
        int vertices[MAX_ADJACENT_VERTICES];
        Edge* kruskalMST[MAX_MST_EDGES] = {nullptr};
        Edge* foundEdges[MAX_EDGES] = {nullptr};
        MinHeap* graphMinHeap = new MinHeap(MAX_EDGES);

        for(int v = 0; v < vertexCount; v++){
            vertices[v] = -1;
        }
        
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (adjMatrix[i][j] != 0){
                    adjMatrix[j][i] = 0;
                    Edge* foundEdge = new Edge(i, j, adjMatrix[i][j]);
                    foundEdges[foundEdgeCount] = foundEdge;
                    graphMinHeap->insert(foundEdgeCount, adjMatrix[i][j]);
                    foundEdgeCount++;
                }
            }
        }

        graphMinHeap->getMin();
        int minEdgeIndex = graphMinHeap->minItem;
        kruskalMST[MSTEdgeCount] = foundEdges[minEdgeIndex];
        vertices[kruskalMST[MSTEdgeCount]->from] = kruskalMST[MSTEdgeCount]->from;
        vertices[kruskalMST[MSTEdgeCount]->to] = kruskalMST[MSTEdgeCount]->to;
        MSTEdgeCount++;
        
        graphMinHeap->extractMin();

        while(MSTEdgeCount < vertexCount - 1){
            graphMinHeap->getMin();
            int minEdgeIndex = graphMinHeap->minItem;
            
            while(vertices[foundEdges[minEdgeIndex]->from] == foundEdges[minEdgeIndex]->from && vertices[foundEdges[minEdgeIndex]->to] == foundEdges[minEdgeIndex]->to){
                graphMinHeap->extractMin();
                graphMinHeap->getMin();
                minEdgeIndex = graphMinHeap->minItem;
            }
            kruskalMST[MSTEdgeCount] = foundEdges[minEdgeIndex];
            vertices[kruskalMST[MSTEdgeCount]->from] = kruskalMST[MSTEdgeCount]->from;
            vertices[kruskalMST[MSTEdgeCount]->to] = kruskalMST[MSTEdgeCount]->to;
            MSTEdgeCount++; 
        }     

        for(int e = 0; e < MSTEdgeCount; e++){
            kruskalMST[e]->print();
        }
    }
};


int main() {

    int G[5][5] = {{0, 3, 77, 0, 0},
                   {3, 0, 77, 51, 3},
                   {77, 77, 0, 51, 77},
                   {0, 51, 51, 0, 51},
                   {0, 3, 77, 51, 0}};

    int H[5][5] = {{0, 67, 4, 86, 16},
                   {67, 0, 36, 47, 69},
                   {4, 36, 0, 41, 77},
                   {86, 47, 41, 0, 34},
                   {16, 69, 77, 34, 0}};

    int Assign3[6][6] = {{0, 8, 8, 0, 0, 0},
                         {8, 0, 4, 0, 0, 0},
                         {8, 4, 0, 6, 4, 8},
                         {0, 0, 6, 0, 0, 6},
                         {0, 0, 4, 0, 0, 6},
                         {0, 0, 8, 6, 6, 0}};

    int matrixSize = sizeof(G)/sizeof(G[0]);
    int matrixSize2 = sizeof(H)/sizeof(H[0]);
    int sizeAssign3 = sizeof(Assign3)/sizeof(Assign3[0]);

    Graph* graphG = new Graph(G, matrixSize);
    Graph* graphH = new Graph(H, matrixSize2);
    
    graphG->printGraph();
    graphG->primMST();
    cout << endl;
    graphG->kruskalMST();
    cout << endl;

    graphH->printGraph();
    graphH->primMST();
    cout << endl;
    graphH->kruskalMST();

    // Graph* graphAssign3 = new Graph(Assign3, sizeAssign3);

    // graphAssign3->printGraph();
    // graphAssign3->primMST();
    // cout << endl;
    // graphAssign3->kruskalMST();

    

    return 0;
}