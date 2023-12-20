#include <iostream>

using namespace std;

struct AVLDictNode {
    string name;
    int key;
    int height;
    AVLDictNode *left;
    AVLDictNode *right;

    AVLDictNode() {
        left = nullptr;
        right = nullptr;
    }

    AVLDictNode(string inputName, int inputKey) {
        name = inputName;
        key = inputKey;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    void print(){
        cout << key;
    }

};

class AVLDictionary{
private:
    AVLDictNode* root;
    int count;

    int calibrateHeight(AVLDictNode* node){
        if(node == nullptr){
            return 0;
        }
        return node->height;
    }

    int balance(AVLDictNode* node){
        if(node == nullptr){
            return 0;
        }
        else{
            return calibrateHeight(node->left) - calibrateHeight(node->right);
        }
    }

    AVLDictNode* LeftRotate(AVLDictNode* node){
        AVLDictNode* tempNode = node->right;
        AVLDictNode* tempNodeLeft = tempNode->left;

        tempNode->left = node;
        node->right = tempNodeLeft;

        node->height = max(calibrateHeight(node->left), calibrateHeight(node->right)) + 1;
        tempNode->height = max(calibrateHeight(tempNode->left), calibrateHeight(tempNode->right)) + 1;
        
        return tempNode;
    }

    AVLDictNode* RightRotate(AVLDictNode* node){
        AVLDictNode* tempNode = node->left;
        AVLDictNode* tempNodeRight = tempNode->right;

        tempNode->right = node;
        node->left = tempNodeRight;

        node->height = max(calibrateHeight(node->left), calibrateHeight(node->right)) + 1;
        tempNode->height = max(calibrateHeight(tempNode->left), calibrateHeight(tempNode->right)) + 1;
        
        return tempNode;
    }

    AVLDictNode* insert(AVLDictNode* insertNode, AVLDictNode* checkNode){
        if(checkNode == nullptr){
            checkNode = insertNode;
            count++;
        }

        if(insertNode->key < checkNode->key){
            checkNode->left = insert(insertNode, checkNode->left);
        }
        else if(insertNode->key > checkNode->key){
            checkNode->right = insert(insertNode, checkNode->right);
        }
        else {
            return checkNode;
        }

        checkNode->height = 1 + max(calibrateHeight(checkNode->left), calibrateHeight(checkNode->right));

        int checkBalance = balance(checkNode);

        // Left Left Case
        if(checkBalance > 1 && insertNode->key < checkNode->left->key){
            return RightRotate(checkNode);
        }
        // Right Right Case
        if(checkBalance < -1 && insertNode->key > checkNode->right->key){
            return LeftRotate(checkNode);
        }
        // Left Right Case
        if(checkBalance > 1 && insertNode->key > checkNode->left->key){
            checkNode->left = LeftRotate(checkNode->left);
            return RightRotate(checkNode);
        }
        // Right Left Case
        if(checkBalance < -1 && insertNode->key < checkNode->right->key){
            checkNode->right = RightRotate(checkNode->right);
            return LeftRotate(checkNode);
        }
        return checkNode;
    }
    
    AVLDictNode* empty(AVLDictNode* node){
        if (node == nullptr){
            return nullptr;
        }
        empty(node->left);
        empty(node->right);
        delete node;
        return nullptr;
    }

    AVLDictNode* FindMin(AVLDictNode* node) {
        if(node == nullptr)
            return nullptr;
        else if(node->left == nullptr)
            return node;
        else
            return FindMin(node->left);
    }

    AVLDictNode* FindMax(AVLDictNode* node) {
        if(node == nullptr)
            return nullptr;
        else if(node->right == nullptr)
            return node;
        else
            return FindMax(node->right);
    }
    
    AVLDictNode* remove(int removeNodeKey, AVLDictNode* compareNode) {
        if(compareNode == nullptr){
            return compareNode;
        }

        if(removeNodeKey < compareNode->key){
            compareNode->left = remove(removeNodeKey, compareNode->left);
        }
        
        else if(removeNodeKey > compareNode->key){
            compareNode->right = remove(removeNodeKey, compareNode->right);
        } else {
            if(compareNode->left == nullptr || compareNode->right == nullptr){
                AVLDictNode* temp = compareNode->left ? compareNode->left : compareNode->right;

                if(temp == nullptr){
                    temp = compareNode;
                    compareNode = nullptr;
                    count--;
                }
                else {
                    *compareNode = *temp;
                    delete temp;
                    count--;
                }
            } else {
                AVLDictNode* temp = FindMax(compareNode->left);

                compareNode->key = temp->key;
                compareNode->left = remove(temp->key, compareNode->left);
            }
        }
        
        if(compareNode == nullptr){
            return compareNode;
        }

        compareNode->height = 1 + max(calibrateHeight(compareNode->left), calibrateHeight(compareNode->right));

        int checkBalance = balance(compareNode);

        // Left Left Case
        if(checkBalance > 1 && balance(compareNode->left) >= 0){
            return RightRotate(compareNode);
        }
        // Left Right Case
        if(checkBalance > 1 && balance(compareNode->left) < 0){
            compareNode->left = LeftRotate(compareNode->left);
            return RightRotate(compareNode);
        }
        // Right Right Case
        if(checkBalance < -1 && balance(compareNode->right) <= 0){
            return LeftRotate(compareNode);
        }
        // Right Left Case
        if(checkBalance < -1 && balance(compareNode->right) > 0){
            compareNode->right = RightRotate(compareNode->right);
            return LeftRotate(compareNode);
        }
        
        return compareNode;
    }

    AVLDictNode* find(int searchKey, AVLDictNode* checkNode) {
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

   void printHelper(AVLDictNode* root, string indent, bool last) {
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

    void inOrderHelper(AVLDictNode* checkNode) {
		if (checkNode != nullptr) {
			inOrderHelper(checkNode->left);
			cout<<checkNode->name<<" ";
			inOrderHelper(checkNode->right);
		} 
	}

public:
    AVLDictionary(){
        root = nullptr;
        count = 0;
    }

    ~AVLDictionary(){
        root = empty(root);
        count = 0;
    }

    void insertItem(string inputName, int inputKey) {
        AVLDictNode* insertNode = new AVLDictNode(inputName, inputKey);
        root = insert(insertNode, root);
    }

    void removeElement(int x) {
        root = remove(x, root);
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

    void prettyPrint() {
	    if (root != nullptr) {
    		printHelper(this->root, "", true);
	    }
	}
    
};

int main() {
    AVLDictionary* dictionary = new AVLDictionary();
    
    dictionary->insertItem("Kori", 8);
	dictionary->insertItem("Stephanie", 18);
	dictionary->insertItem("Uma", 5);
	dictionary->insertItem("Susan", 15);
	dictionary->insertItem("Roland", 17);
	dictionary->insertItem("Igor", 25);
	dictionary->insertItem("Selene", 40);
	dictionary->insertItem("Bert", 80);
    dictionary->insertItem("Jenna", 34);
    dictionary->insertItem("Matt", 56);
    dictionary->insertItem("Rose", 21);
    dictionary->insertItem("Larry", 77);

    dictionary->removeElement(8);
    // dictionary->removeElement(77);
    dictionary->removeElement(40);
    // dictionary->removeElement(56);
    dictionary->removeElement(25);
    // dictionary->removeElement(21);
    dictionary->removeElement(18);
    dictionary->removeElement(17);

    dictionary->prettyPrint();

    cout << dictionary->size();
    

    return 0;
}