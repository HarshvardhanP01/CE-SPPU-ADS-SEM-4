#include <iostream>
#include <vector>
using namespace std;

class Node
{
private:
    string str;
    Node *ls;
    Node *rs;

public:
    Node()
    {
        str = "";
        ls = NULL;
        rs = NULL;
    }
    Node(string s)
    {
        str = s;
        ls = NULL;
        rs = NULL;
    }
    friend class OBST;
};

class OBST
{
private:
    Node *root;

public:
    OBST(){
        root = NULL;
    }
    int height(Node* node){
        if(node==NULL) return 0;
        return 1+max(height(node->ls),height(node->rs));
    }
    void calculate_weight(vector<double> &p, vector<double> &q, vector<string> &st){
        int n = p.size();
        // Creating 2D Arrays dynamically
        double **w = new double *[n + 1];
        double **c = new double *[n + 1];
        double **r = new double *[n + 1];

        // Now allocating memeory for these data
        for (int i = 0; i < n + 1; i++)
        {
            w[i] = new double[n + 1];
            c[i] = new double[n + 1];
            r[i] = new double[n + 1];
        }

        // Setting up initial 2 rows for further calculation in DP
        for (int i = 0; i < n; i++)
        {
            w[i][i] = q[i];
            c[i][i] = r[i][i] = 0;

            w[i][i + 1] = p[i] + q[i + 1] + q[i];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }

        w[n][n] = q[n];
        c[n][n] = r[n][n] = 0;

        // Using Dynamic Programming now
        for (int m = 2; m <= n; m++)
        {
            for (int i = 0; i <= n - m; i++)
            {
                double min = 999;
                int j = i + m;
                int k = 0;
                w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

                for (int x = i + 1; x <= j; x++)
                {
                    double sum = c[i][x - 1] + c[x][j];
                    if (sum < min)
                    {
                        min = sum;
                        k = x;
                    }
                }

                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
                r[i][j] = k;
            }
        }
        // Creating OBST
        this->root = this->createTree(0, n, r, st);
        // Displaying contents
        show(w, c, r, n + 1);
    }

    void show(double **w, double **c, double **r, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                cout << w[i][j] << " " << c[i][j] << " " << r[i][j] << " | "<< " ";
            }
            cout << endl;
        }
    }

    Node *createTree(int i, int j, double **r, vector<string> &st){
        if (i != j){
            int k = r[i][j];
            Node *new_node = new Node(st[k - 1]);
            new_node->ls = createTree(i, k - 1, r, st);
            new_node->rs = createTree(k, j, r, st);
            return new_node;
        }
        else{
            return NULL;
        }
    }
    int search(vector<string> &st,string s){
        int n = st.size();
        for(int i=0;i<n;i++){
            if(st[i]==s) return i;
        }
        return -1;
    }
    void preorder(Node *node,int& cost,vector<double> &p,vector<string> &st){
        if (node == NULL) return;
        cout << node->str << " ";
        int level = height(node);
        int idx = search(st,node->str);
        cost += (level*p[idx]);
        preorder(node->ls,cost,p,st);
        preorder(node->rs,cost,p,st);
    }

    Node *getRoot(){
        return root;
    }
};

// using namespace std;
int main()
{
    int n;
    vector<string> st;
    vector<double> p, q;
    OBST obj;

    cout << "Enter the number of strings " << endl;
    cin >> n;

    cout << "Enter those keys/strings " << endl;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        st.push_back(str);
    }

    cout << "Enter " << n << " Successfull probabilities " << endl;
    for (int i = 0; i < n; i++)
    {
        double num;
        cin >> num;
        p.push_back(num);
    }

    cout << "Enter " << n + 1 << " Unsuccessfull probabilities " << endl;
    for (int i = 0; i <= n; i++)
    {
        double num;
        cin >> num;
        q.push_back(num);
    }

    obj.calculate_weight(p, q, st);
    cout << "The Preorder Traversal is " << endl;
    int cost = 0;
    obj.preorder(obj.getRoot(),cost,p,st);
    cout<<"\nMinimum cost of tree : "<<cost;

    return 0;
}