#include <iostream>

using namespace std;

const int MAX_ADJACENT_VERTICES = 5;
const int MAX_EDGES = 9;
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

    Graph(int inputMatrix[][MAX_ADJACENT_VERTICES], int matrixSize) {
        vertexCount = matrixSize;
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                int inputWeight = inputMatrix[i][j];
                if (inputWeight != 0){
                    inputMatrix[j][i] = 0;
                }
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
        
        while(MSTEdgeCount < 4){
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
            
            while(foundEdges[minEdgeIndex]->to == permanent[foundEdges[minEdgeIndex]->to] ){
                graphMinHeap->extractMin();
                graphMinHeap->getMin();
                minEdgeIndex = graphMinHeap->minItem;
            }

            cout << graphMinHeap->minItem << endl;


            MST[MSTEdgeCount] = foundEdges[minEdgeIndex];
            
            start = MST[MSTEdgeCount]->to;
            
            permanent[start] = start;
            
            MSTEdgeCount++;
            // for(int p = 0; p < vertexCount; p++){
            //     cout << permanent[p] << " ";
            // } 
            // cout << endl;

            // for(int u = 0; u < vertexCount; u++){
            //     cout << unvisited[u] << " ";
            // }

            // cout << endl;
            // graphMinHeap->printHeapArray();
            // graphMinHeap->printHeapVertices();
            // cout << endl;
            cout << endl;     
        }     

        for(int e = 0; e < MSTEdgeCount; e++){
            MST[e]->print();
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
    
    testGraph->primMST();
    return 0;
}