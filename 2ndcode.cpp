#include <iostream>
using namespace std;

class BSTnode
{
public:
    int data;
    BSTnode *left;
    BSTnode *right;
    BSTnode(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};
class BST
{
public:
    BSTnode *root;
    BST()
    {
        root = NULL;
    }
    BSTnode *create(BSTnode *T, int d);
    int max_node(BSTnode *T);
    void inorder(BSTnode *T);
    int min_node(BSTnode *T);
    int height(BSTnode *T);
    int search(BSTnode *T, int d);
    void preorder(BSTnode *T);
    BSTnode *swap(BSTnode *T);
};
BSTnode *BST::create(BSTnode *T, int d)
{
    // BSTnode* root;
    if (T == NULL)
    {
        T = new BSTnode(d);
        return T;
    }
    if (T->data > d)
    {
        T->left = create(T->left, d);
        // return T;
    }
    else
    {
        T->right = create(T->right, d);
    }
    // T->right = create(T->right, d);

    return T;
}
int BST::max_node(BSTnode *T)
{
    T = root;
    while (T->right != NULL)
    {
        T = T->right;
    }
    return T->data;
}
int BST::min_node(BSTnode *T)
{
    T = root;
    while (T->left != NULL)
    {
        T = T->left;
    }
    return T->data;
}
int BST::height(BSTnode *T)
{
    int hl, hr;
    if (T == NULL)
    {
        return 0;
    }
    if (T->left == NULL && T->right == NULL)
    {
        return 0;
    }
    hl = height(T->left);
    hr = height(T->right);
    if (hl > hr)
    {
        return (hl + 1);
    }
    return (hr + 1);
}
BSTnode *BST::swap(BSTnode *T)
{
    BSTnode *p;
    if (T != NULL)
    {
        p = T->left;
        T->left = swap(T->right);
        T->right = swap(p);
    }
    return T;
}
int BST::search(BSTnode *T, int d)
{
    int count = 0;
    int ans;
    if (T == NULL)
    {
        return 0;
    }
    if (T->data == d)
    {
        count++;
        return 1;
    }
    else
    {
        if (d < T->data)
        {
            count++;
            ans = search(T->left, d);
            // cout<<"\nIn d < T->data = ";
            // cout<<"\nComparisons required = "<<count<<endl;
            //         return ans;
        }
        else
        {
            count++;
            // cout<<"\nIn d > T->data = ";
            ans = search(T->right, d);
            // cout<<"\nComparisons required = "<<count<<endl;
            //         return ans;
        }
    }
    // cout << "\nComparisons required1 = " << count << endl;
    return ans;
}
void BST::inorder(BSTnode *T)
{

    if (T != NULL)
    {
        inorder(T->left);
        cout << T->data << " ";
        inorder(T->right);
    }
}
int main()
{
    BST t;
    BST t1;
    int ch;
    while (1)
    {
        cout << "\n1.Create BST by inserting nodes";
        cout << "\n2.Number of nodes in Longest path";
        cout << "\n3.Minimum and Maximum data value";
        cout << "\n4.SWap tree";
        cout << "\n5.Search an element";
        cout << "\n\nEnter your choice : ";
        cout << "\n>>";
        cin >> ch;
        switch (ch)
        {
        case 1:
            // BSTnode* root1 = NULL;
            while (1)
            {
                int num;
                cout << "\nEnter num :";
                cin >> num;
                if (num <= 0)
                {
                    break;
                }
                t.root = t.create(t.root, num);
            }
            break;
        case 2:
            cout << "\nNumber of nodes in Longest path = " << t.height(t.root);
            break;
        case 3:
            cout << "\nMInimum data node is = " << t.min_node(t.root);
            cout << "\nMaximum data node is = " << t.max_node(t.root);
            break;
        case 4:
            t.swap(t.root);
            cout << "\nTree is swapped ";
            t.inorder(t.root);
            break;
        case 5:
            int srch;
            cout << "\nEnter element to search = ";
            cin >> srch;
            if (t.search(t.root, srch))
            {
                cout << "\nElement found in Binary search tree ";
            }
            else
            {
                cout << "\nElement not found in Binary search tree ";
            }
            cout << "\n Inorder traversal of tree is : ";
            t.inorder(t.root);
            break;
        default:
            break;
        }
        if (ch > 5 || ch <= 0)
        {
            break;
        }
    }
}