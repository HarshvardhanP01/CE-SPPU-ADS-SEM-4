#include <iostream>
using namespace std;
#include <fstream>

class student
{
    int rollno;
    string name;
    char div;
    string address;

public:
    student()
    {
        rollno = 0;
        name = "";
        address = "";
        div = ' ';
    }
    student(int rollno, string name, char div, string address)
    {
        this->rollno = rollno;
        this->name = name;
        this->div = div;
        this->address = address;
    }
    friend fstream &operator<<(fstream &out, student &s)
    {
        out << s.rollno << " ";
        out << s.name << " ";
        out << s.div << " ";
        out << s.address << " ";
        out << endl;
        return out;
    }
    friend fstream &operator>>(fstream &in, student &s)
    {
        in >> s.rollno;
        in >> s.name;
        in >> s.div;
        in >> s.address;
        return in;
    }
    friend ostream &operator<<(ostream &out, student &s)
    {
        out << s.rollno << " ";
        out << s.name << " ";
        out << s.div << " ";
        out << s.address << " ";
        return out;
    }
    void display(fstream &in, student &s)
    {
        in.open("myfile.txt", ios::in);
        while (1)
        {
            in >> s;
            if (in.eof())
            {
                break;
            }
            cout << s;
        }
        in.close();
    }
    void search(fstream &in, int x, student &s)
    {
        in.open("myfile.txt", ios::in);
        while (1)
        {
            in >> s;
            if (s.rollno == x)
            {
                cout << s;
                break;
            }
            if (in.eof())
            {
                cout << "Record not found" << endl;
                break;
            }
        }
        in.close();
    }
    void Delete(fstream &in, int x, student &s, int n)
    {
        student arr[n];
        in.open("myfile.txt", ios::in);
        for (int i = 0; i < n; i++)
        {
            in >> s;
            arr[i] = s;
        }
        in.close();
        in.open("myfile.txt", ios::out | ios::trunc);
        for (int i = 0; i < n; i++)
        {
            if (arr[i].rollno == x)
            {
                continue;
            }
            else
            {
                in << arr[i];
                cout << arr[i];
            }
        }
        in.close();
    }
};
int main()
{
    student s1;
    int choice = 1;
    int n;
    fstream myfile;
    while (choice > 0)
    {
        cout << "1. Add record to file 2.Display 3.Search 4.Delete 5.Exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            myfile.open("myfile.txt", ios::out);
            cout << "Enter the number of records" << endl;
            cin >> n;
            int rollno;
            string name;
            char div;
            string address;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter the rollno" << endl;
                cin >> rollno;
                cout << "Enter the Name" << endl;
                cin >> name;
                cout << "Enter divsion" << endl;
                cin >> div;
                cout << "Enter address" << endl;
                cin >> address;
                student s(rollno, name, div, address);
                myfile << s;
            }
            myfile.close();
        }
        else if (choice == 2)
        {
            s1.display(myfile, s1);
        }
        else if (choice == 3)
        {
            int x = 0;
            cout << "Enter the rollno to be searched" << endl;
            cin >> x;
            s1.search(myfile, x, s1);
        }
        else if (choice == 4)
        {
            int x;
            cout << "Enter the rollno to be deleted" << endl;
            cin >> x;
            s1.Delete(myfile, x, s1, n);
        }
    }
    return 0;
}