#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
using namespace std;

class mystack
{
    int arr[20];
    int top;

public:
    mystack()
    {
        for (int i = 0; i < 20; i++)
        {
            arr[i] = -1;
        }
        this->top = -1;
    }

    bool empty()
    {
        return top == -1;
    }

    bool full()
    {
        return top >= 20;
    }

    void push(int x)
    {
        top++;
        if (!full())
        {
            arr[top] = x;
        }
        else
        {
            cout << "\nStack is full";
        }
    }

    int pop()
    {
        if (!empty())
        {
            int item = arr[top];
            top--;
            return item;
        }
        else
        {
            cout << "\nStack is empty";
            return -1;
        }
    }
};

class Node
{
public:
    string value;
    Node *lnext;
    Node *next;

    Node(string v)
    {
        this->value = v;
        this->lnext = NULL;
        this->next = NULL;
    }
};

class graph
{
    Node *head;
    Node *arr[20];

public:
    int n;
    string *places;
    int *degree;
    graph()
    {
        head = NULL;
    }

    int getindex(string p)
    {
        for (int i = 0; i < n; i++)
        {
            if (places[i] == p)
                return i;
        }
        return -1;
    }

    void create_adjlist()
    {
        int n1, v;
        string p, p1;
        int *arr1;
        cout << "\nEnter no. of Places : ";
        cin >> n;
        places = new string[n];
        arr1 = new int[n];
        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter Place [" << i << "] : ";
            cin >> p;
            int check = getindex(p);
            if (check == -1)
            {
                places[i] = p;
            }
            else
            {
                cout << "\nPlace already considered before Try again " << endl;
                i = i - 1;
            }
        }
        for (int i = 0; i < n; i++)
        {
            Node *newnode;
            newnode = new Node(places[i]);
            arr[i] = newnode;
            cout << "\nEnter no. of adjacent nodes to " << places[i] << "  : ";
            cin >> n1;
            Node *temp = arr[i];
            for (int j = 0; j < n1; j++)
            {
                Node *newnode1;
                cout << "Enter adjacent node to " << places[i] << " : ";
                cin >> p1;
                int check1 = getindex(p1);
                int check2 = getindex(places[i]);
                if (check1 == check2)
                {
                    cout << "\nSame vertex cannot be its adjacent try again " << endl;
                    i = i - 1;
                    continue;
                }
                else
                {
                    newnode1 = new Node(p1);
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = newnode1;
                }
            }
        }
    }

    void display_adjlist()
    {
        cout << "\nAdjacency list is \n";
        degree = new int[n];
        int count;
        for (int i = 0; i < n; i++)
        {
            count = 0;
            Node *temp = arr[i];
            if (temp)
            {
                cout << temp->value << " :  ";
            }
            while (temp->next != NULL)
            {
                temp = temp->next;
                cout << " " << temp->value;
                if (temp->next != NULL)
                {
                    cout << " -> ";
                }
                count++;
            }
            cout<<" -> Null"<< endl;
            degree[i]=count;
        }
        cout<<endl<<endl;
        cout<<"\nDegrees of vertices are "<<endl;
        cout<<"Places"<<setw(20)<<"Degree"<<endl;
        for(int i=0; i<n; i++){
            cout<<places[i]<<setw(20)<<degree[i]<<endl;
        }
        cout<<endl;
    }

    void DFS(string startVertex)
    {
        bool visited[n + 20];
        for (int i = 0; i < n + 20; i++)
        {
            visited[i] = false;
        }
        stack<string> s;
        s.push(startVertex);
        int startVertexi = getindex(startVertex);
        visited[startVertexi] = true;
        cout << "\nDFS traversal = ";
        while (!s.empty())
        {
            string item = s.top();
            int itemi = getindex(item);
            s.pop();
            cout << " " << item;
            Node *temp = arr[itemi]->next;
            // temp = temp->next;
            while (temp != NULL)
            {
                string val = temp->value;
                int vali = getindex(val);
                if (!visited[vali])
                {
                    s.push(val);
                    visited[vali] = true;
                }
                temp = temp->next;
            }
        }
    }

    void BFS(string startVertex)
    {
        bool visited[n + 20];
        for (int i = 0; i < n + 20; i++)
        {
            visited[i] = false;
        }
        queue<string> q;
        cout << "\nBFS = ";
        q.push(startVertex);
        int startVertexi = getindex(startVertex);
        visited[startVertexi] = true;
        while (!q.empty())
        {
            string current = q.front();
            int currenti = getindex(current);
            q.pop();
            cout << " " << current;
            Node *temp = arr[currenti];
            temp = temp->next;
            while (temp != NULL)
            {
                string adj = temp->value;
                int adji= getindex(adj);
                if (!visited[adji])
                {
                    q.push(adj);
                    visited[adji] = true;
                }
                temp = temp->next;
            }
        }
    }
};

int main()
{
    cout << "!!!Hello World!!!" << endl;
    graph g;
    g.create_adjlist();
    g.display_adjlist();
    string startVertex;
    cout << "Enter starting vertex for DFS and BFS traversal: ";
    cin >> startVertex;
    g.DFS(startVertex);
    g.BFS(startVertex);
    return 0;
}
