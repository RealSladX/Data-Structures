#include <iostream>

using namespace std;

struct AVLNode {
    int data;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    void print(){
        cout << data;
    }

};

class AVLTree{
    AVLNode* root;   

    int calibrateHeight(AVLNode* node){
        if(node == nullptr){
            return 0;
        }
        return node->height;
    }

    int balance(AVLNode* node){
        if(node == nullptr){
            return 0;
        }
        else{
            return calibrateHeight(node->left) - calibrateHeight(node->right);
        }
    }

    AVLNode* LeftRotate(AVLNode* node){
        AVLNode* tempNode = node->right;
        AVLNode* tempNodeLeft = tempNode->left;

        tempNode->left = node;
        node->right = tempNodeLeft;

        node->height = max(calibrateHeight(node->left), calibrateHeight(node->right)) + 1;
        tempNode->height = max(calibrateHeight(tempNode->left), calibrateHeight(tempNode->right)) + 1;
        
        return tempNode;
    }

    AVLNode* RightRotate(AVLNode* node){
        AVLNode* tempNode = node->left;
        AVLNode* tempNodeRight = tempNode->right;

        tempNode->right = node;
        node->left = tempNodeRight;

        node->height = max(calibrateHeight(node->left), calibrateHeight(node->right)) + 1;
        tempNode->height = max(calibrateHeight(tempNode->left), calibrateHeight(tempNode->right)) + 1;
        
        return tempNode;
    }

    AVLNode* insert(int x, AVLNode* node){
        if(node == nullptr){
            return new AVLNode(x);
        }

        if(x < node->data){
            node->left = insert(x, node->left);
        }
        else if(x > node->data){
            node->right = insert(x, node->right);
        }
        else {
            return node;
        }

        node->height = 1 + max(calibrateHeight(node->left), calibrateHeight(node->right));

        int checkBalance = balance(node);

        // Left Left Case
        if(checkBalance > 1 && x < node->left->data){
            return RightRotate(node);
        }
        // Right Right Case
        if(checkBalance < -1 && x > node->right->data){
            return LeftRotate(node);
        }
        // Left Right Case
        if(checkBalance > 1 && x > node->left->data){
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }
        // Right Left Case
        if(checkBalance < -1 && x < node->right->data){
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }
    
    AVLNode* empty(AVLNode* node){
        if (node == nullptr){
            return nullptr;
        }
        empty(node->left);
        empty(node->right);
        delete node;
        return nullptr;
    }

    AVLNode* remove(int x, AVLNode* node) {
        if(node == nullptr){
            return node;
        }

        if(x < node->data){
            node->left = remove(x, node->left);
        }
        else if(x > node->data){
            node->right = remove(x, node->right);
        } else {
            if(node->left == nullptr || node->right == nullptr){
                AVLNode* temp = node->left ? node->left : node->right;

                if(temp == nullptr){
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                    delete temp;
                }
  
            }
            else {
                AVLNode* temp = mostRight(node->left);
                node->data = temp->data;
                node->left = remove(temp->data, node->left);
            }
        }

        if(node == nullptr){
            return node;
        }

        node->height = 1 + max(calibrateHeight(node->left), calibrateHeight(node->right));

        int checkBalance = balance(node);

        // Left Left Case
        if(checkBalance > 1 && balance(node->left) >= 0){
            return RightRotate(node);
        }
        // Left Right Case
        if(checkBalance > 1 && balance(node->left) < 0){
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }
        // Right Right Case
        if(checkBalance < -1 && balance(node->right) <= 0){
            return LeftRotate(node);
        }
        // Right Left Case
        if(checkBalance < -1 && balance(node->right) > 0){
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }

        return node;
    }
    
    AVLNode* mostLeft(AVLNode* node)
    {
        if(node == nullptr)
            return nullptr;
        else if(node->left == nullptr)
            return node;
        else
            return mostLeft(node->left);
    }

    AVLNode* mostRight(AVLNode* node) {
        if(node == NULL)
            return NULL;
        else if(node->right == NULL)
            return node;
        else
            return mostRight(node->right);
    }

    AVLNode* find(AVLNode* node, int x) {
        if(node == nullptr){
            return nullptr;
        }
        else if(x < node->data){
            return find(node->left, x);
        } 
        else if(x > node->data){
            return find(node->right, x);
        }
        else{
            return node;
        } 
    }

    void printHelper(AVLNode* root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != nullptr) {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }
            
		   cout<<root->data<<endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

public:
    AVLTree(){
        root = nullptr;
    }

    ~AVLTree(){
        root = empty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    bool search(int x) {
        if(find(root, x) == nullptr){
            return false;
        }
        else if(find(root, x)->data == x){
            return true;
        }
        else{
            return false;
        }
    }

    void prettyPrint() {
	    if (root != nullptr) {
    		printHelper(this->root, "", true);
	    }
	}
    

};

int main() {
    AVLTree* testAVLTree = new AVLTree();
    testAVLTree->insert(8);
	testAVLTree->insert(18);
	testAVLTree->insert(5);
	testAVLTree->insert(15);
	testAVLTree->insert(17);
	testAVLTree->insert(25);
	testAVLTree->insert(40);
	testAVLTree->insert(80);

    // testAVLTree->remove(25);
    testAVLTree->remove(15);
    testAVLTree->remove(8);
    testAVLTree->remove(17);
    
    testAVLTree->prettyPrint();


    return 0;
}