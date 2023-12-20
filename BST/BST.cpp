#include <iostream>

using namespace std;

class BSTNode {
public:
    int data;
    BSTNode *left;
    BSTNode *right;
    
    BSTNode() {
        left = nullptr;
        right = nullptr;
    }

    BSTNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }

    void print(){
        cout << data;
    }

};

class BST{
    BSTNode* root;
    
    BSTNode* empty(BSTNode* node){
        if (node == nullptr){
            return nullptr;
        }
        empty(node->left);
        empty(node->right);
        delete node;
        return nullptr;
    }

    BSTNode* insert(int x, BSTNode* node)
    {
        if(node == nullptr)
        {
            BSTNode* tempNode = new BSTNode(x);
            node = tempNode;
        }
        else if(x < node->data)
            node->left = insert(x, node->left);
        else if(x > node->data)
            node->right = insert(x, node->right);
        return node;
    }

    BSTNode* findMin(BSTNode* node)
    {
        if(node == nullptr)
            return nullptr;
        else if(node->left == nullptr)
            return node;
        else
            return findMin(node->left);
    }

    BSTNode* findMax(BSTNode* node) {
        if(node == NULL)
            return NULL;
        else if(node->right == NULL)
            return node;
        else
            return findMax(node->right);
    }

    BSTNode* remove(int x, BSTNode* node) {
        BSTNode* tempNode;
        if(node == NULL)
            return NULL;
        else if(x < node->data)
            node->left = remove(x, node->left);
        else if(x > node->data)
            node->right = remove(x, node->right);
        else if(node->left && node->right)
        {
            tempNode = findMax(node->left);
            node->data = tempNode->data;
            node->left = remove(node->data, node->left);
        }
        else
        {
            tempNode = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            delete tempNode;
        }
        return node;
    }


    BSTNode* find(BSTNode* node, int x) {
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

   void printHelper(BSTNode* root, string indent, bool last) {
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
    BST() {
        root = nullptr;
    }

    ~BST() {
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
    BST* testBST = new BST();
    testBST->insert(20);
    testBST->insert(25);
    testBST->insert(15);
    testBST->insert(10);
    testBST->insert(30);
    testBST->insert(5);
    testBST->insert(18);
    testBST->insert(28);
    testBST->insert(35);
    testBST->insert(12);

    testBST->remove(20);
    
    testBST->prettyPrint();

    // cout << testBST->search(30);
    
    return 0;
}