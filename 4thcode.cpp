#include <iostream>
#include <iomanip>
#include <cstdlib>

#define SIZE 10

class Hashtable {
    long long int wor[SIZE] = {0}; // Initializing arrays in the constructor is not necessary
    long long int wr[SIZE] = {0}; // Initializing arrays in the constructor is not necessary

public:
    int hash(int key) {
        return key % SIZE;
    }

    void insertwithoutreplacement(long long int ph) {
        int index = hash(ph);

        if (wor[index] == 0) {
            wor[index] = ph;
        } else {
            while (wor[index] != 0) {
                index = (index + 1) % SIZE;
                if (index == hash(ph)) {
                    std::cout << "\nHashtable is full";
                    return;
                }
            }
            wor[index] = ph;
        }
    }

    void insertwithreplacement(long long int ph) {
        int index = hash(ph);

        if (wr[index] == 0) {
            wr[index] = ph;
        } else {
            long long int temp = wr[index];
            wr[index] = ph;
            int temp1 = index;

            while (wr[index] != 0) {
                index = (index + 1) % SIZE;
                if (index == temp1) {
                    std::cout << "\nHashtable is full";
                    return;
                }
            }
            wr[index] = temp;
        }
    }

    void search_wor(long long int ph) {
        int index = hash(ph);
        int count_wor = 0;

        while (wor[index] != 0 && wor[index] != ph) {
            index = (index + 1) % SIZE;
            count_wor++;
        }

        if (wor[index] == ph) {
            std::cout << "\nelement found";
            count_wor++;
            std::cout << "\nComparisons required = " << count_wor << std::endl;
            return;
        }

        std::cout << "\nElement not found";
        std::cout << "\nComparisons required = " << count_wor << std::endl;
    }

    void search_wr(long long int ph) {
        int index = hash(ph);
        int count_wr = 0;

        while (wr[index] != 0 && wr[index] != ph) {
            index = (index + 1) % SIZE;
            count_wr++;
        }

        if (wr[index] == ph) {
            std::cout << "\nelement found";
            count_wr++;
            std::cout << "\nComparisons required = " << count_wr << std::endl;
            return;
        }

        std::cout << "\nElement not found";
        std::cout << "\nComparisons required = " << count_wr << std::endl;
    }

    void display() {
        std::cout << "\nLinear Probing without Replacement" << std::setw(50) << "Linear Probing with Replacement";

        for (int i = 0; i < 10; i++) {
            std::cout << "\n" << i << " : " << wor[i] << std::setw(40) << i << " : " << wr[i];
        }
    }
};

int main() {
    Hashtable h;
    long long int x;
    int choice;

    while (true) {
        std::cout << "\n*********** MENU *************";
        std::cout << "\n1. Insert without Replacement";
        std::cout << "\n2. Show";
        std::cout << "\n3. Comparisons";
        std::cout << "\n4. Exit";
        std::cout << "\nEnter choice : ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\nEnter mobile number : ";
                std::cin >> x;
                h.insertwithoutreplacement(x);
                h.insertwithreplacement(x);
                break;
            case 2:
                h.display();
                break;
            case 3:
                std::cout << "\nEnter mobile number to find comparison : ";
                std::cin >> x;
                std::cout << "\nComparisons without replacement : ";
                h.search_wor(x);
                std::cout << "\nComparisons with replacement : ";
                h.search_wr(x);
                break;
            case 4:
                exit(0);
            default:
                std::cout << "\nInvalid choice";
                break;
        }
    }

    return 0;
}
