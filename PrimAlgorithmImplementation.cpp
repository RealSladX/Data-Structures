#include <iostream>
#include <string>

using namespace std;

struct Vertex {
  int vertexID;
  int numAdjacentVertices;
  Vertex *adjTo[_MAX_INT_DIG] = {nullptr};

  Vertex(int vID) {
    this->vertexID = vID;
    numAdjacentVertices = 0;
  }

  void addAdjVertex(Vertex *adjVertex) {
    adjTo[numAdjacentVertices] = adjVertex;
    numAdjacentVertices++;
  }

  void print() { cout << vertexID << " "; }

  void printAdj() {
    cout << "Vertex " << vertexID << " is adjacent to: ";
    for (int i = 0; i < numAdjacentVertices; i++) {
      cout << "Vertex " << adjTo[i]->vertexID << " ";
    }
    cout << endl;
  }
};

struct Edge {
  Vertex *from;
  Vertex *to;
  int weight;

  Edge(Vertex *v1, Vertex *v2, int weight) {
    this->from = v1;
    this->to = v2;
    this->weight = weight;
    v1->addAdjVertex(v2);
  }

  void print() {
    from->print();
    cout << "- ";
    to->print();
    cout << "-> ";
    cout << weight;
    cout << endl;
  }
};

struct MSTEdge {
  Vertex *from;
  Vertex *to;
  int weight;

  MSTEdge(Vertex* v1, Vertex* v2, int weight) {
    this->from = v1;
    this->to = v2;
    this->weight = weight;
  }

  void print() {
    from->print();
    cout << "- ";
    to->print();
    cout << "-> ";
    cout << weight;
    cout << endl;
  }
};

struct MinHeap {
  int heapSize;
  int heapNumMax;
  int *heapArray;
  int *itemTracker;
  int minItem;
  int minKey;

  MinHeap(int inputMax) {
    heapSize = 0;
    heapNumMax = inputMax;
    heapArray = new int[heapNumMax];
    itemTracker = new int[heapNumMax];
  }

  ~MinHeap() {
    delete[] heapArray;
    delete[] itemTracker;
  }

  int parent(int i) { return (i - 1) / 2; }

  int leftChild(int i) { return 2 * i + 1; }

  int rightChild(int i) { return 2 * i + 2; }

  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }

  void heapify(int inputIndex) {
    int minIndex = inputIndex;
    int left = leftChild(inputIndex);
    int right = rightChild(inputIndex);

    if (left < heapSize && heapArray[left] < heapArray[minIndex]) {
      minIndex = left;
    }
    if (right < heapSize && heapArray[right] < heapArray[minIndex]) {
      minIndex = right;
    }
    if (minIndex != inputIndex) {
      swap(&heapArray[inputIndex], &heapArray[minIndex]);
      swap(&itemTracker[inputIndex], &itemTracker[minIndex]);
      heapify(minIndex);
    }
  }

  void insert(int item, int key) {
    if (heapSize == heapNumMax) {
      cout << "Overflow: Could not insert into Heap" << endl;
      return;
    }

    heapSize++;
    int heapIndex = heapSize - 1;
    heapArray[heapIndex] = key;
    itemTracker[heapIndex] = item;

    while (heapIndex != 0 &&heapArray[parent(heapIndex)] > heapArray[heapIndex]) {
      swap(&heapArray[heapIndex], &heapArray[parent(heapIndex)]);
      swap(&itemTracker[heapIndex], &itemTracker[parent(heapIndex)]);
      heapIndex = parent(heapIndex);
    }
  }

  void extractMin() {
    if (heapSize <= 0) {
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

  int getMinItem() {
    if (heapSize <= 0) {
      cout << "Error Heap is Empty" << endl;
      return -1;
    }
    minItem = itemTracker[0];
    return minItem;
  }

  int getMinKey() {
    if (heapSize <= 0) {
      cout << "Error Heap is Empty" << endl;
      return -1;
    }
    minKey = heapArray[0];
    return minKey;
  }

  bool isEmpty() { return heapSize == 0; }

  void printMinHeap() {
    for (int i = 0; i < heapSize; i++) {
      cout << "Item " << itemTracker[i] << " with key ";
      cout << heapArray[i] << endl;
    }
    cout << endl;
  }
  
};

class Graph {
public:
  int adjMatrix[_MAX_INT_DIG][_MAX_INT_DIG] = {0};
  int vertexCount;
  int edgeCount = 0;
  Vertex *vertices[_MAX_INT_DIG] = {nullptr};
  Edge *edges[_MAX_INT_DIG] = {nullptr};

  Graph(int inputMatrix[][5], int matrixSize) {
    vertexCount = matrixSize;
    for (int i = 0; i < vertexCount; i++) {
      Vertex *newVertex = new Vertex(i);
      vertices[i] = newVertex;
      for (int j = 0; j < vertexCount; j++) {
        int inputWeight = inputMatrix[i][j];
        adjMatrix[i][j] = inputWeight;
      }
    }

    for (int i = 0; i < vertexCount; i++) {
      for (int j = 0; j < vertexCount; j++) {
        if (adjMatrix[i][j] != 0) {
          Vertex *newFrom = vertices[i];
          Vertex *newTo = vertices[j];
          Edge *newEdge = new Edge(newFrom, newTo, adjMatrix[i][j]);
          edges[edgeCount] = newEdge;
          edgeCount++;
        }
      }
    }
  }

  ~Graph() {
    for (int i = 0; i < vertexCount; i++) {
      delete vertices[i];
    }
    for (int i = 0; i < edgeCount; i++) {
      delete edges[i];
    }
  }

  void printAdjList() {
    cout << "Here is a list of all vertices and their adjacencies: " << endl;
    for (int i = 0; i < vertexCount; i++) {
      vertices[i]->printAdj();
    }
    cout << endl;
  }

  void printAdjMatrix(){
    cout << "Here is the Adjacency Matrix for your Graph: " << endl;
    for (int i = 0; i < vertexCount; i++) {
      for (int j = 0; j < vertexCount; j++) {
        cout << adjMatrix[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  void printEdges(){
    cout << "There are " << edgeCount/2 << " undirected edges in this Matrix" << endl;
    for (int i = 0; i < edgeCount; i++) {
      edges[i]->print();
    }
  }

   void primMST(){
      Vertex* permanent[_MAX_INT_DIG] = {nullptr};
      Vertex* unvisited[_MAX_INT_DIG] = {nullptr};
      MSTEdge* edgesMST[_MAX_INT_DIG] = {nullptr};
      MSTEdge* discoveredEdges[_MAX_INT_DIG];
      MinHeap* edgeMinHeap = new MinHeap(_MAX_INT_DIG);
      int from = 0;
      int insertKey;
      int discEdgeCount = 0;
      int MSTEdgeCount = 0;

      for(int i = 0; i < vertexCount; i++){
          unvisited[i] = vertices[i];
      }
      
      permanent[from] = unvisited[from];
      unvisited[from] = nullptr;
      
      while(MSTEdgeCount < vertexCount){
        for(int to = 0; to < vertexCount; to++){
          insertKey = adjMatrix[from][to];
          if(insertKey != 0){
            MSTEdge* foundEdge = new MSTEdge(vertices[from], vertices[to], insertKey);
            discoveredEdges[discEdgeCount] = foundEdge;
            edgeMinHeap->insert(discEdgeCount, insertKey);
            discEdgeCount++;
            
          }
        }
        
        
        int minEdge = edgeMinHeap->getMinItem();
        int checkFrom = discoveredEdges[minEdge]->from->vertexID;
        int checkTo = discoveredEdges[minEdge]->to->vertexID;
        
        while(permanent[checkFrom] == nullptr && unvisited[checkTo] == false){
          edgeMinHeap->extractMin();
          minEdge = edgeMinHeap->getMinItem();
          checkFrom = discoveredEdges[minEdge]->from->vertexID;
          checkTo = discoveredEdges[minEdge]->to->vertexID;
        }
        // edgeMinHeap->printMinHeap();
        // cout << endl << endl;
        permanent[checkTo] = vertices[checkTo];
        unvisited[checkTo] = false;
        edgesMST[MSTEdgeCount] = discoveredEdges[minEdge];
        MSTEdgeCount++;
        from = checkTo;
        cout << from << endl;
      }
      

      delete edgeMinHeap;
      

  //     while(unvisitedCount != 0){
  //         MinHeap* graphMinHeap = new MinHeap(adjVerticesCount);
  //         for(int i = 0; i < adjVerticesCount; i++){
  //             Vertex* neighbor = start->adjTo[i];
  //             checkIndex = neighbor->vertexID;
  //             if (permanent[checkIndex] != neighbor && unvisited[checkIndex]
  //             == neighbor){
  //                 int discoveredWeight = adjMatrix[startIndex][checkIndex];
  //                 graphMinHeap->insert(checkIndex, discoveredWeight);
  //                 cout << "Vertex ";
  //                 neighbor->print();
  //                 cout << "with a weight of " << discoveredWeight;
  //                 cout << endl;
  //             }
  //         }
  //         cout << endl;
  //         graphMinHeap->extractMin();
  //         int nextIndex = graphMinHeap->minVertexID;
  //         int permWeight = graphMinHeap->minWeight;
  //         cout << "Vertex " << nextIndex << " has the minimum edge" << endl
  //         << endl; Vertex* nextStop = vertices[nextIndex];
  //         permanent[nextIndex] = nextStop;
  //         Edge* permEdge = new Edge(start, nextStop, permWeight);
  //         edgesMST[edgeMSTCount] = permEdge;
  //         delete graphMinHeap;
  //         edgeMSTCount++;
  //         start = nextStop;
  //         adjVerticesCount = start->numAdjacentVertices;
  //         unvisited[nextIndex] = nullptr;
  //         cout << "There are " << unvisitedCount << " vertices left" << endl;
  //         unvisitedCount--;
  //     }

  //     cout << endl;

  //     cout << "The MST would be: " << endl;

  //     for(int i = 0; i < edgeMSTCount; i++){
  //         edgesMST[i]->print();
  //         cout << endl;
  //     }

  }
};

int main() {

  int G[5][5] = {{0, 3, 65, 0, 0},
                 {3, 0, 85, 20, 45},
                 {65, 85, 0, 41, 77},
                 {0, 20, 41, 0, 51},
                 {0, 45, 77, 51, 0}};

  int matrixSize = sizeof(G) / sizeof(G[0]);

  Graph *testGraph = new Graph(G, matrixSize);

  // testGraph->printAdjList();
  
  // testGraph->printEdges();

  // testGraph->printAdjMatrix();

  testGraph->primMST();

  delete testGraph;

  return 0;
}