#include <iostream>

using namespace std;

class BSTDictNode {
public:
    string name;
    int key;
    BSTDictNode *left;
    BSTDictNode *right;
    
    BSTDictNode() {
        left = nullptr;
        right = nullptr;
    }

    BSTDictNode(string inputName, int inputKey) {
        key = inputKey;
        name = inputName;
        left = nullptr;
        right = nullptr;
    }

    void print(){
        cout << name;
    }

};

class BSTDictionary{
private:
    BSTDictNode* root;
    int count;
    
    BSTDictNode* empty(BSTDictNode* node){
        if (node == nullptr){
            return nullptr;
        }
        empty(node->left);
        empty(node->right);
        delete node;
        return nullptr;
    }

    BSTDictNode* insert(BSTDictNode* insertNode, BSTDictNode* checkNode) {
        if(checkNode == nullptr){
            checkNode = insertNode;
            count++;
        }
        else if(insertNode->key < checkNode->key){
            checkNode->left = insert(insertNode, checkNode->left);
        }    
        else if(insertNode->key > checkNode->key){
            checkNode->right = insert(insertNode, checkNode->right);
        }
        return checkNode;
    }

    BSTDictNode* findMin(BSTDictNode* node)
    {
        if(node == nullptr)
            return nullptr;
        else if(node->left == nullptr)
            return node;
        else
            return findMin(node->left);
    }

    BSTDictNode* findMax(BSTDictNode* node) {
        if(node == nullptr)
            return nullptr;
        else if(node->right == nullptr)
            return node;
        else
            return findMax(node->right);
    }

    BSTDictNode* remove(int removeNodeKey, BSTDictNode* checkNode) {
        BSTDictNode* tempNode;
        if(checkNode == nullptr){
            return nullptr;
        } else if(removeNodeKey < checkNode->key) {
            checkNode->left = remove(removeNodeKey, checkNode->left);
        } else if(removeNodeKey > checkNode->key) {
            checkNode->right = remove(removeNodeKey, checkNode->right);
        }else{
            
            if (checkNode->left == nullptr) {
                BSTDictNode* temp = checkNode->right;
                delete checkNode;
                count--;
                return temp;
            } else if (checkNode->right == nullptr) {
                BSTDictNode* temp = checkNode->left;
                delete checkNode;
                count--;
                return temp;
            }
            BSTDictNode* temp = findMax(checkNode->left);
            checkNode->key = temp->key;
            checkNode->left = remove(temp->key, checkNode->left);
        }
        return checkNode;
    }

    BSTDictNode* find(int searchKey, BSTDictNode* checkNode) {
        if(checkNode == nullptr){
            return nullptr;
        }
        else if(searchKey < checkNode->key){
            return find(searchKey, checkNode->left);
        } 
        else if(searchKey > checkNode->key){
            return find(searchKey, checkNode->right);
        }
        else{
            return checkNode;
        } 
    }

    void printHelper(BSTDictNode* root, string indent, bool last) {
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
            
		   cout<<root->name<< " " <<root->key<<endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

    void inOrderHelper(BSTDictNode* checkNode) {
		if (checkNode != nullptr) {
			inOrderHelper(checkNode->left);
			cout<<checkNode->name<<" ";
			inOrderHelper(checkNode->right);
		} 
	}

public:
    BSTDictionary() {
        root = nullptr;
        count = 0;
    }

    ~BSTDictionary() {
        root = empty(root);
        count = 0;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    void elements(){ 
	   	inOrderHelper(root);
    }

    void findElement(int searchKey){
        if(find(searchKey, root) == nullptr) {
            cout << "Dictionary Empty" << endl;
        }
        else if(find(searchKey, root)->key == searchKey) {
            cout << "Element Found" << endl;
        }
        else{
            cout << "Element Not Found" << endl; 
        }
    }

    void insertItem(string inputName, int inputKey) {
        BSTDictNode* insertNode = new BSTDictNode(inputName, inputKey);
        root = insert(insertNode, root);
    }

    void removeElement(int inputKey){
        root = remove(inputKey, root);
    }

    void prettyPrint() {
	    if (root != nullptr) {
    		printHelper(root, "", true);
	    }
	}
};

int main() {

    BSTDictionary* dictionary = new BSTDictionary();

    dictionary->insertItem("Kori", 8);
	dictionary->insertItem("Stephanie", 18);
	dictionary->insertItem("Uma", 5);
	dictionary->insertItem("Susan", 15);
	dictionary->insertItem("Roland", 17);
	dictionary->insertItem("Igor", 25);
	dictionary->insertItem("Selene", 40);
	dictionary->insertItem("Bert", 80);


    dictionary->removeElement(8);
    dictionary->removeElement(5);
    dictionary->removeElement(18);
    dictionary->removeElement(40);
    dictionary->prettyPrint();


    // dictionary->elements();
    // cout << endl;
    cout << dictionary->size();
    cout << endl;

    return 0;
}