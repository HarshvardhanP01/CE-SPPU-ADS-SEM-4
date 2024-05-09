#include <iostream>
using namespace std;
class Graph
{
    int **adjMatrix;
    string *cities;
    int v;

public:
    Graph(int n)
    {
        this->v = n;
        adjMatrix = new int *[v];
        cities = new string[v];
        for (int i = 0; i < v; i++)
        {
            adjMatrix[i] = new int[v];
            for (int j = 0; j < v; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }
    int getIndex(string city)
    {
        for (int i = 0; i < v; i++)
        {
            if (cities[i] == city)
            {
                return i;
            }
        }
        return -1;
    }
    void addEdge(int src, int des, int weight)
    {
        adjMatrix[src][des] = weight;
        adjMatrix[des][src] = weight;
    }
    void initGraph()
    {
        string des, src;
        int weight;
        int desld, srcld;
        for (int i = 0; i < v; i++)
        {
            cout << "Enter the city" << i << " ";
            cin >> cities[i];
        }
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v - 1; j++)
            {
                cout << "Add city connected to " << cities[i] << " if no city connected enter -1 : ";
                cin >> des;
                cout << "Enter the cost of connection : ";
                cin >> weight;
                srcld = getIndex(cities[i]);
                desld = getIndex(des);
                if (srcld == -1 || desld == -1)
                {
                    break;
                }
                addEdge(srcld, desld, weight);
            }
        }
    }
    void DisplayGraph()
    {
        for (int i = 0; i < v; i++)
        {
            cout << cities[i] << " ";
            for (int j = 0; j < v; j++)
            {
                cout << " " << cities[j] << "," << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    int minKey(int key[], bool mstSet[])
    {
        int min = 999;
        int min_index;
        for (int i = 0; i < v; i++)
        {
            if (mstSet[i] == false && key[i] < min)
            {
                min = key[i];
                min_index = i;
            }
        }
        return min_index;
    }
    void prims()
    {
        int parent[v];
        int key[v];
        bool mstSet[v];
        for (int i = 0; i < v; i++)
        {
            key[i] = 999;
            mstSet[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < v - 1; count++)
        {
            int u = this->minKey(key, mstSet);

            mstSet[u] = true;
            for (int i = 0; i < v; i++)
            {
                if (adjMatrix[u][i] && mstSet[i] == false && adjMatrix[u][i] < key[i])
                {
                    parent[i] = u;
                    key[i] = adjMatrix[u][i];
                }
            }
        }
        printMST(parent);
    }
    void printMST(int parent[])
    {
        cout << "Minimum cost for Connection is : " << endl;
        int cost = 0;
        for (int i = 1; i < v; i++)
        {
            cost = cost + adjMatrix[i][parent[i]];
            cout << cities[parent[i]] << "-" << cities[i] << "\t" << adjMatrix[i][parent[i]] << endl;
        }
        cout << "Total cost is : " << cost << endl;
    }
};
int main()
{
    int v;
    cout << "enter the number of cities : ";
    cin >> v;

    Graph obj(v);
    bool flag = true;
    int ch;
    while (flag)
    {
        cout << "1.Intialize Graph" << endl;
        cout << "2.Add connections" << endl;
        cout << "3.Prims Min Cost" << endl;
        cout << "4.Exit" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            obj.initGraph();
            break;
        case 2:
            obj.DisplayGraph();
            break;
        case 3:
            obj.prims();
            break;
        case 4:
            flag = false;
            break;
        default:
            cout << "Invalid Input " << endl;
            break;
        }
    }

    return 0;
}
