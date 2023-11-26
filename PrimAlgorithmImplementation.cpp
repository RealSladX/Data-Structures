#include <iostream>
#include <string>
using namespace std;

const int MAX_ADJACENT_VERTICES = 5;
const int MAX_EDGES = 11;
const int MAX_PRIM_EDGES = 5;

struct Vertex {
    int vertexID;
    int numAdjacentVertices;
    Vertex* adjTo[MAX_ADJACENT_VERTICES] = {nullptr};

    Vertex(int vID) {
        vertexID = vID;
        numAdjacentVertices = 0;
    }

    void addAdjVertex(Vertex* adjVertex){
        adjTo[numAdjacentVertices] = adjVertex;
        numAdjacentVertices++;
    }

    void print(){
        cout << vertexID << " ";
    }

    void printAdj(){
        cout << "Vertex " << vertexID << " is adjacent to: ";
        for(int i = 0; i < numAdjacentVertices; i++){
            cout << "Vertex "<< adjTo[i]->vertexID << " ";
        }
        cout << endl;
    }
};

struct Edge {
    string edgeName;
    Vertex* from;
    Vertex* to;
    int weight;
    
    Edge(Vertex* v1, Vertex* v2, int weight){
        this->from = v1;
        this->to = v2;
        this->weight = weight;
        v1->addAdjVertex(v2);
        this->edgeName = to_string(from->vertexID) + " - " + to_string(to->vertexID);
    }

    void print(){
        cout << edgeName << " -> " << weight;
    }
};

struct MinHeap{
    int heapSize;
    int heapNumMax;
    int* heapArray;
    int* edgeTracker;
    int minVertexID;  
    int minWeight;
    
    MinHeap(int inputMax){
        heapSize = 0;
        heapNumMax = inputMax;
        heapArray = new int[heapNumMax];
        edgeTracker = new int[heapNumMax];
    }

    ~MinHeap() {
        delete[] heapArray;
        delete[] edgeTracker;
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
            swap(&edgeTracker[inputIndex], &edgeTracker[minIndex]);
            heapify(minIndex);
        }
    }

    void insert(int foundEdge, int inputVal){
        if (heapSize == heapNumMax){
            cout << "Overflow: Could not insert into Heap" << endl;
            return;
        }

        heapSize++;
        int heapIndex = heapSize-1;
        heapArray[heapIndex] = inputVal;
        edgeTracker[heapIndex] = foundEdge;

        while (heapIndex != 0 && heapArray[parent(heapIndex)] > heapArray[heapIndex]){
            swap(&heapArray[heapIndex], &heapArray[parent(heapIndex)]);
            swap(&edgeTracker[heapIndex], &edgeTracker[parent(heapIndex)]);
            heapIndex = parent(heapIndex);
        }
        
    }

    void extractMin(){
        if(heapSize <=0) {
            cout << "Error Heap is Empty" << endl;
        }
        if (heapSize == 1) {
            heapSize--;
            minWeight = heapArray[0];
            minVertexID = edgeTracker[0];
        }
        minWeight = heapArray[0];
        minVertexID = edgeTracker[0];
        heapArray[0] = heapArray[heapSize - 1];
        edgeTracker[0] = edgeTracker[heapSize - 1];
        heapSize--;
        heapify(0);
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
            cout << edgeTracker[i] << " ";
        }
        cout << endl;
    }
};

class Graph {
public:
    int adjMatrix[MAX_ADJACENT_VERTICES][MAX_ADJACENT_VERTICES];
    int vertexCount;
    int edgeCount;
    Vertex* vertices[MAX_ADJACENT_VERTICES] = {nullptr};
    Edge* edges[MAX_EDGES];

    Graph(int inputMatrix[][5], int matrixSize) {
        vertexCount = matrixSize;
        edgeCount = 0;
        int checkWeight;
        
        for (int i = 0; i < vertexCount; i++) {
            Vertex* newVertex = new Vertex(i);
            vertices[i] = newVertex;
            for (int j = 0; j < vertexCount; j++) {
                int inputWeight = inputMatrix[i][j];
                adjMatrix[i][j] = inputWeight;
            }
        }
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                checkWeight = adjMatrix[i][j];
                if(checkWeight != 0){
                    Edge* newEdge = new Edge(vertices[i], vertices[j], checkWeight);
                    edges[edgeCount] = newEdge;
                }
            }
        }
    }
    
    ~Graph(){
        for (int i = 0; i < vertexCount; i++) {
            delete vertices[i];
        }
        for (int i = 0; i < edgeCount; i++) {
            delete edges[i];
        }
    }

    void printGraph(){
        cout << "Here is a list of all vertices and their adjacencies: " << endl;
        for(int i = 0; i < vertexCount; i++){
            vertices[i]->printAdj();
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
    }      

    void primMST(int startVertex){
        Vertex* permanent[MAX_ADJACENT_VERTICES] = {nullptr};
        Vertex* unvisited[MAX_ADJACENT_VERTICES] = {nullptr};
        Edge* edgesMST[MAX_EDGES] = {nullptr};
        int startIndex;
        int checkIndex;
        int edgeMSTCount = 0;
        int unvisitedCount = vertexCount;
        for(int i = 0; i < vertexCount; i++){
            Vertex* temp = vertices[i];
            unvisited[i] = temp;
        }

        Vertex* start = vertices[startVertex];
        int adjVerticesCount = start->numAdjacentVertices;
        startIndex = start->vertexID;
        permanent[startIndex] = start;
        unvisited[startVertex] = nullptr;
        unvisitedCount--;
        
        while(unvisitedCount != 0){
            MinHeap* graphMinHeap = new MinHeap(adjVerticesCount);
            for(int i = 0; i < adjVerticesCount; i++){
                Vertex* neighbor = start->adjTo[i];
                checkIndex = neighbor->vertexID;
                if (permanent[checkIndex] != neighbor && unvisited[checkIndex] == neighbor){
                    int discoveredWeight = adjMatrix[startIndex][checkIndex];
                    graphMinHeap->insert(checkIndex, discoveredWeight);
                    cout << "Vertex ";
                    neighbor->print();
                    cout << "with a weight of " << discoveredWeight;
                    cout << endl;
                }
            }
            cout << endl;
            graphMinHeap->extractMin();
            int nextIndex = graphMinHeap->minVertexID;
            int permWeight = graphMinHeap->minWeight;
            cout << "Vertex " << nextIndex << " has the minimum edge" << endl << endl;
            Vertex* nextStop = vertices[nextIndex];
            permanent[nextIndex] = nextStop;
            Edge* permEdge = new Edge(start, nextStop, permWeight);
            edgesMST[edgeMSTCount] = permEdge;
            delete graphMinHeap;
            edgeMSTCount++;
            start = nextStop;
            adjVerticesCount = start->numAdjacentVertices;
            unvisited[nextIndex] = nullptr;
            cout << "There are " << unvisitedCount << " vertices left" << endl;
            unvisitedCount--;
        }
        
        cout << endl;

        cout << "The MST would be: " << endl;

        for(int i = 0; i < edgeMSTCount; i++){
            edgesMST[i]->print();
            cout << endl;
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

    // testGraph->printGraph();
    
    testGraph->primMST(1);
    return 0;
}