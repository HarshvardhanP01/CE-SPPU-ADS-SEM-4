#include <iostream>
#include <stack>
using namespace std;
class Node
{
private:
    int data;
    int height;
    Node *left;
    Node *right;
public:
    Node(){
        data = 0;
        height = 1;
        left = NULL;
        right = NULL;
    }
    friend class AVLDict;
};

class AVLDict
{
private:
    Node *root;
public:
    AVLDict(){
        root = NULL;
    }
    // To update the height of any node whenever needed..
    int update_height(Node *node){
        if (node == NULL) return 0;
        node->height =  1 + max((update_height(node->left)), (update_height(node->right)));
        return node->height;
    }
    // To calculate balance factor whenever needed..
    int balance_factor(Node *node){
        if (node == NULL) return 0;
        return ((update_height(node->left)) - (update_height(node->right)));
    }
    // This piece of code will balance things out
    Node *balance(Node *node){
        if (balance_factor(node) == 2){ // Positive Balance Factor means Left side subtree is unbalanced
            if (balance_factor(node->left) < 0) node = LRRotation(node);
            else node = LLRotation(node);
        }
        else if (balance_factor(node) == -2){ // Problem in balancing right subtree
            if (balance_factor(node->right) > 0) node = RLRotation(node);                 
            else node = RRRotation(node);
        }
        update_height(node);
        return node;
    }
    // When we want to insert something
    Node *insert(Node *&node, int key){
        if (node == NULL){
            node = new Node;
            node->data = key;
            return node;
        }
        if (key > node->data){
            node->right = insert(node->right, key);
        }
        else if (key < node->data){
            node->left = insert(node->left, key);
        } 
        // If key is equal to node's data, don't create a new node
        return balance(node);
    }
    // 4 Rotations:
    Node *LLRotation(Node *node){
        Node *new1 = node->left;
        node->left = new1->right;
        new1->right = node;
        update_height(node);
        update_height(new1);
        return new1;
    }

    Node *LRRotation(Node *node){
        node->left = RRRotation(node->left);
        return LLRotation(node);
    }

    Node *RRRotation(Node *node){
        Node *new1 = node->right;
        node->right = new1->left;
        new1->left = node;
        update_height(node);
        update_height(new1);
        return new1;
    }
    Node *RLRotation(Node *node){
        node->right = LLRotation(node->right);
        return RRRotation(node);
    }
    void inorder(Node *node){
        if (node == NULL) return;
        inorder(node->left);
        cout << node->data << " "<<" BF : "<<balance_factor(node)<<endl;
        inorder(node->right);
    }
    void printDescending(Node *node){
        Node *curr = node;
        stack<Node *> s1;
        while (curr != NULL || !s1.empty()){
            while (curr != NULL){
                s1.push(curr);
                curr = curr->right;
            }
            curr = s1.top();
            s1.pop();
            cout << curr->data << " "<<" BF : "<<balance_factor(curr)<<endl;
            curr = curr->left;
        }
        cout << endl;
    }
    void search(Node *node, int data, int &pos){
        if (node == NULL){
            pos = -1;
            cout << data << " not found !! " << endl;
        }
        else if (data == node->data){
            pos++;
            cout << data << " found !! " << endl;
        }
        else if (data < node->data){
            pos++;
            search(node->left, data, pos);
        }
        else if (data > node->data){
            pos++;
            search(node->right, data, pos);
        }
    }
    void searchELement(Node *node){
        int data;
        cout << "Enter the data you want to search " << endl;
        cin >> data;
        int noc = 0;
        search(node, data, noc);
        cout << "No of comparisons required to search element is " << noc << endl;
    }
};

int main()
{
    int ch, ch1;
    int data;
    AVLDict obj;
    Node *p = NULL;

    do
    {
        cout << "---------------Enter your choice--------------------" << endl;
        cout << "1-Insert Data" << endl;
        cout << "2-Display Data in Ascending Order" << endl;
        cout << "3-Display Data in Descending Order" << endl;
        cout << "4-Search Data " << endl;
        cout << "5-Exit" << endl;
        cout << "----------------------------------------------------" << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter the data you want to insert !! " << endl;
            cin >> data;
            p = obj.insert(p, data);
            cout << "Element inserted Successfully!! " << endl;
            break;

        case 2:
            cout << "Displaying Data in Ascending Order " << endl;
            obj.inorder(p);
            cout << endl;
            break;

        case 3:
            cout << "Displaying Data in Descending Order " << endl;
            obj.printDescending(p);
            cout << endl;
            break;

        case 4:
            obj.searchELement(p);
            cout << endl;
            break;

        case 5:
            cout << "Exiting...." << endl;
            exit(0);
            break;
        default:
            cout << "Enter a valid choice..." << endl;
            break;
        }

        cout << "Do you want to continue,Press 1 " << endl;
        cin >> ch1;
    } while (ch1 == 1);

    return 0;
}