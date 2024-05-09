#include <iostream>
using namespace std;
class Hashnode
{
    pair<string, string> data;
    Hashnode *next;

public:
    Hashnode()
    {
        data.first = "";
        data.second = "";
        next = NULL;
    }
    Hashnode(string str, string str2)
    {
        data.first = str;
        data.second = str2;
        next = NULL;
    }
    friend class SLL;
    friend class Dictionary;
};
class SLL
{
    Hashnode *head;

public:
    SLL()
    {
        head = NULL;
    }
    void Append(string val, string mean)
    {
        Hashnode *newnode = new Hashnode(val, mean);
        if (head == NULL)
        {
            head = newnode;
        }
        else
        {
            Hashnode *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }
    void Traversal()
    {
        Hashnode *ptr = head;
        while (ptr != NULL)
        {
            cout << ptr->data.first << " : " << ptr->data.second << " -> ";
            ptr = ptr->next;
        }
    }
    int Search(string val)
    {
        Hashnode *temp = head;
        bool flag = false;
        while (temp != NULL)
        {
            if (temp->data.first == val)
            {
                flag = true;
                break;
            }
            temp = temp->next;
        }
        if (flag == true)
            return 1;
        else
            return 0;
    }
    void del(string value)
    {
        if (head == NULL)
        {
            cout << "\nEmpty!";
        }
        else
        {
            Hashnode *temp = head;
            if (temp->data.first == value || temp->next == NULL)
            {
                head = head->next;
                return;
            }
            while (temp && temp->next->data.first != value)
            {
                temp = temp->next;
            }
            temp->next = temp->next->next;
        }
    }
    friend class Dictionary;
};
class Dictionary
{
    SLL arr[26];

public:
    int Hash(string str)
    {
        int val = int(str[0]) - 97;
        return val;
    }
    void Insert(string value, string mean)
    {
        int key = Hash(value);
        arr[key].Append(value, mean);
    }
    void Find(string value)
    {
        int key = Hash(value);
        int ans = arr[key].Search(value);
        if (ans)
            cout << "\nElement found in Dictionary !";
        else
            cout << "\nElement not found in Dictionary !";
    }
    void remove(string value)
    {
        int key = Hash(value);
        int ans = arr[key].Search(value);
        if (ans)
        {
            arr[key].del(value);
            cout << "\nElement Deleted Successfully !";
        }
        else
            cout << "\nElement Does not Exists !";
    }
    void show()
    {
        for (int i = 0; i < 26; i++)
        {
            cout << char('a' + i) << " : ";
            arr[i].Traversal();
            cout << endl;
        }
    }
};
int main()
{
    Dictionary d;
    char c = 'y';
    while (c == 'y')
    {
        cout << "\n1.Insert element in Dictionary";
        cout << "\n2.Find an element in Dictionary";
        cout << "\n3.Delete element in Dictionary";
        cout << "\n4.Display Dictionary";
        cout << "\n5.Exit";
        cout << "\nEnter your choice : ";
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            string str;
            cout << "\nEnter element to be inserted ";
            cout << "\nEnter keyword : ";
            cin >> str;
            cout << "\nEnter meaning : ";
            string str2;
            cin >> str2;
            d.Insert(str, str2);
            cout << "\nElement Inserted Successfully !";
        }
        else if (ch == 2)
        {
            string str;
            cout << "\nEnter Key of element to be Searched : ";
            cin >> str;
            d.Find(str);
        }
        else if (ch == 3)
        {
            string str;
            cout << "\nEnter Key of element to be Deleted : ";
            cin >> str;
            d.remove(str);
        }
        else if (ch == 4)
        {
            d.show();
        }
        else if (ch == 5)
        {
            break;
        }
        else
        {
            cout << "\nInvalid Choice !!!";
            break;
        }
        cout << "\nDo you want to continue (y/n) : ";
        cin >> c;
    }
    return 0;
}