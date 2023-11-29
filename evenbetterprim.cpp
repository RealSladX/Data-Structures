#include <iostream>

using namespace std;

const int MAX_ADJACENT_VERTICES = 5;
const int MAX_EDGES = 17;
const int MAX_PRIM_EDGES = 50;

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
        return 2*i + 1;
    }

    int rightChild(int i) {
        return 2*i + 2;
    }

    void swap(int *a, int *b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapify(int inputIndex){
        int minIndex = inputIndex;
        int left = leftChild(inputIndex);
        int right = rightChild(inputIndex);

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

    void extractMin(){
        if(heapSize <=0) {
            cout << "Error Heap is Empty" << endl;
        }
        if (heapSize == 1) {
            heapSize--;
            minKey = heapArray[0];
            minItem = itemTracker[0];
        }
        minKey = heapArray[0];
        minItem = itemTracker[0];
        heapArray[0] = heapArray[heapSize - 1];
        itemTracker[0] = itemTracker[heapSize - 1];
        heapSize--;
        heapify(0);
    }

    int getMinKey(){
        if(heapSize <=0) {
            cout << "Error Heap is Empty" << endl;
            return -1;
        }
        minKey = heapArray[0];
        return minKey;    
    }

    int getMinItem(){
        if(heapSize <=0) {
            cout << "Error Heap is Empty" << endl;
            return -1;
        }
        minItem = itemTracker[0];
        return minItem;
    }

    void decreaseKey(int index, int key){
        heapArray[index] = key;
        while (index != 0 && heapArray[parent(index)] > heapArray[index]){
            swap(&heapArray[index], &heapArray[parent(index)]);
            swap(&itemTracker[index], &itemTracker[parent(index)]);
            index = parent(index);
        }
    }

    bool isEmpty(){
        return heapSize == 0;
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
    int edgeCount = 0;
    int vertices[MAX_ADJACENT_VERTICES] = {0};
    Edge* edges[MAX_EDGES] = {nullptr};

    Graph(int inputMatrix[][MAX_ADJACENT_VERTICES], int matrixSize) {
        vertexCount = matrixSize;
        for(int v = 0; v < vertexCount; v++){
            vertices[v] = v;
        }

        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                int inputWeight = inputMatrix[i][j];
                adjMatrix[i][j] = inputWeight;
                if(inputWeight != 0){
                    Edge* newEdge = new Edge(i, j, inputWeight);
                    edges[edgeCount] = newEdge;
                    edgeCount++;
                }
            }
        }
    }
    
    ~Graph(){
        for (int i = 0; i < edgeCount; i++) {
            delete edges[i];
        }
    }

    void printGraph(){
        cout << "Here is a list of all vertices: " << endl;
        for(int i = 0; i < vertexCount; i++){
            cout << "Vertex " << vertices[i] << endl;
        }
        cout << endl;

        cout << "Here is the Adjacency Matrix for your Graph: " << endl;
        for(int i = 0; i < vertexCount; i++){
            for(int j = 0; j < vertexCount; j++){
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "Here is the list of Edges from your Graph and their weights:" << endl;
        for (int i = 0; i < edgeCount; i++){
            edges[i]->print();
        }
        
    }      

    void primMST(){
        bool permanent[MAX_ADJACENT_VERTICES] = {false};
        bool unvisited[MAX_ADJACENT_VERTICES] = {true};
        Edge* edgesMST[MAX_EDGES] = {nullptr};
        int edgeMSTCount = 0;
        MinHeap* graphMinHeap = new MinHeap(vertexCount);
        int MSTCount = 0;
        
        for(int v = 0; v < vertexCount; v++){
            graphMinHeap->insert(v, 10000);
            unvisited[v] = true;
        }

        int start = 1;
        permanent[start] = true;
        unvisited[start] = false;

        while(MSTCount < 5){
            for(int e = 0; e < edgeCount; e++){
                Edge* checkEdge = edges[e];
                if(permanent[checkEdge->from] == 1 && unvisited[checkEdge->to] == 1){
                    graphMinHeap->decreaseKey(checkEdge->to, checkEdge->weight);
                }
            }
            
            int minVertex = graphMinHeap->getMinItem();
            int minWeight = graphMinHeap->getMinKey();
            graphMinHeap->extractMin();
            
            graphMinHeap->insert(graphMinHeap->heapSize, 1000);

            Edge* edgeMST = new Edge(start, minVertex, minWeight);
            edgesMST[edgeMSTCount] = edgeMST;
            edgeMST++;

            permanent[minVertex] = true;
            unvisited[minVertex] = false;
            cout << start << endl;
            start = minVertex;
            MSTCount++;
            
        }

        
    }
};


int main() {

    int G[5][5] = {{0, 3, 65, 0, 0},
                   {3, 0, 85, 20, 45},
                   {65, 85, 0, 41, 77},
                   {0, 20, 41, 0, 51},
                   {0, 45, 77, 51, 0}};

    
    int matrixSize = sizeof(G)/sizeof(G[0]);

    Graph* testGraph = new Graph(G, matrixSize);

    //testGraph->printGraph();
    
    testGraph->primMST();
    return 0;
}