#include <iostream>
#include <string>
using namespace std;

const int MAX_ADJACENT_VERTICES = 5;
const int MAX_EDGES = 20;
const int MAX_PRIM_EDGES = 4;

struct Vertex {
    int vertexID;
    int numAdjacentVertices;
    bool discovered;

    Vertex(int vertexID) {
        this->vertexID = vertexID;
        numAdjacentVertices = 0;
        discovered = false;
    }

    void print(){
        cout << vertexID;
    }

    void printAdjCount(){
        cout << "Vertex " << vertexID << " has " << numAdjacentVertices << " adjacent vertices";
    }
};

struct Edge {
    string edgeName;
    Vertex* vertex1;
    Vertex* vertex2;
    int weight;
    bool permanentMST;
    
    Edge(Vertex* v1, Vertex* v2, int weight){
        this->vertex1 = v1;
        this->vertex2 = v2;
        this->weight = weight;
        this->edgeName = to_string(vertex1->vertexID) + " - " + to_string(vertex2->vertexID);
        permanentMST = false;
    }

    bool hasVertex(Vertex* vertex){
        if(this->vertex1 == vertex || this->vertex2 == vertex) {
            return true;
        }
        else return false;
    }

    bool compareEdge(Edge* e2)
    {
        if(this->vertex1 == e2->vertex1 || this->vertex1 == e2->vertex2 && this->weight == e2->weight) {
            return true;
        }
        else return false;
    }

    void print(){
        cout << edgeName << " -> " << weight;
    }
};

struct MinHeap{
    int heapSize;
    int heapNumMax;
    int* vertexTracker;
    int* heapArray;

    MinHeap(int inputMax){
        heapSize = 0;
        heapNumMax = inputMax;
        vertexTracker = new int[MAX_ADJACENT_VERTICES];
        heapArray = new int[heapNumMax];
    }

    ~MinHeap() {
        delete[] vertexTracker;
        delete[] heapArray;
    }

    void swap(int a, int b){
        int temp = a;
        a = b;
        b = temp;
    }

    void heapify(int i){
        int minValue = i;
        int leftChild = 2*i + 1;
        int rightChild = 2*i + 2;

        if(leftChild < heapSize && heapArray[leftChild] < heapArray[minValue]){
            minValue = leftChild;
        }
        else if(rightChild < heapSize && heapArray[rightChild] < heapArray[minValue]){
            minValue = rightChild;
        }
        if (minValue != i){
            swap(heapArray[i], heapArray[minValue]);
            heapify(minValue);
        }
    }

    void insert(int vertex, int weight){
        heapSize++;
        int i = heapSize - 1;
        heapArray[i] = weight;
        vertexTracker[vertex] = i;

        while(i != 0 && heapArray[(i-1)/2] > heapArray[i]){
            swap(heapArray[i], heapArray[(i-1)/2]);
            i = (i - 1)/2;
        }
    }

    int extractMin(){
        if(heapSize <=0) {return -1;}

        else if (heapSize == 1) {
            heapSize--;
            return heapArray[0];
        }
        else {
            int minExtract = heapArray[0];
            heapArray[0] = heapArray[heapSize - 1];
            heapSize--;
            heapify(0);
            return minExtract;
        }
    }

    void decreaseKey(int vertex, int weight){
        int i = vertexTracker[vertex];
        heapArray[i] = weight;

        while (i != 0 && heapArray[(i - 1)/2] > heapArray[i]) {
            swap(heapArray[i], heapArray[(i - 1)/2]);
            i = (i - 1)/2;
        }
    }

    bool isEmpty(){
        return heapSize == 0;
    }
};

class Graph {
public:
    int adjMatrix[MAX_ADJACENT_VERTICES][MAX_ADJACENT_VERTICES] = {0};
    int vertexCount;
    int edgeCount;
    Vertex* vertices[MAX_ADJACENT_VERTICES] = {nullptr};
    Edge* edges[MAX_EDGES] = {nullptr};

    Graph(int inputCount) {
        vertexCount = inputCount;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++) {
            Vertex* newVertex = new Vertex(i);
            vertices[i] = newVertex;
            for (int j = 0; j < vertexCount; j++) {
                adjMatrix[i][j] = 0;
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

    void addEdge(Vertex* v1, Vertex* v2, int weight){
        Edge* newEdge = new Edge(v1, v2, weight);
        int i = v1->vertexID;
        int j = v2->vertexID;
        v1->numAdjacentVertices++;
        adjMatrix[i][j] = weight;
        adjMatrix[j][i] = weight;
        edges[edgeCount] = newEdge;
        edgeCount++;
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

        cout << "Here are the Edges for your Graph: " << endl;
        for(int i = 0; i < edgeCount; i++){
            edges[i]->print();
            cout << endl;
        }
        cout << endl;
    }      

    void printVertices(){
        cout << "Here are the Vertices in your Graph: " << endl;
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] != nullptr) {
                vertices[i]->print();
            } 
            else {
                cout << "Vertex " << i << " is not present in the graph";
            }
        cout << endl;
        }  
    }

    void primMST(){
        MinHeap* graphMinHeap = new MinHeap(vertexCount);
        Vertex* permanent[MAX_ADJACENT_VERTICES];
        Vertex* temporary[MAX_ADJACENT_VERTICES];
        Edge* primEdges[MAX_EDGES];

        for(int i = 0; i < vertexCount; i++){
            temporary[i] = vertices[i];
        }
        Vertex* startVertex = vertices[0];
        
        for(int i = 0; i < edgeCount; i++){
            if (edges[i]->hasVertex(startVertex)){
                graphMinHeap->insert(i, edges[i]->weight);
            }
            else {
                graphMinHeap->insert(i, 0);
            }
            cout << graphMinHeap->heapArray[i] << " ";
        }
    }
    
};


int main() {
    Graph* testGraph = new Graph(5);
    
    testGraph->addEdge(testGraph->vertices[0], testGraph->vertices[2], 65);
    testGraph->addEdge(testGraph->vertices[2], testGraph->vertices[4], 77);
    testGraph->addEdge(testGraph->vertices[1], testGraph->vertices[3], 20);
    testGraph->addEdge(testGraph->vertices[0], testGraph->vertices[1], 3);
    testGraph->addEdge(testGraph->vertices[1], testGraph->vertices[4], 45);
    testGraph->addEdge(testGraph->vertices[2], testGraph->vertices[3], 41);
    testGraph->addEdge(testGraph->vertices[3], testGraph->vertices[4], 51);
    testGraph->addEdge(testGraph->vertices[1], testGraph->vertices[2], 85);
   
    // testGraph->printGraph();
    // testGraph->printVertices();

    testGraph->primMST();
    return 0;
}