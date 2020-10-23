#include <iostream>
using namespace std;
#include "BST.h"
#include "PriorityQueue.h"

int main() {
    PriorityQueue miFila;

    miFila.push(100);
    miFila.push(75);
    miFila.push(80);
    miFila.push(40);
    miFila.push(35);
    miFila.push(45);
    miFila.push(60);
    miFila.push(20);
    miFila.push(15);

    cout << miFila.top() << endl;
    miFila.pop();
    cout << miFila.top() << endl;
/*
    if (miArbol.search(21)) {
        cout << "Si encontro al 21" << endl;
    } else {
        cout << "No encontro al 21" << endl;
    }

    if (miArbol.search(100)) {
        cout << "Si encontro al 100" << endl;
    } else {
        cout << "No encontro al 100" << endl;
    }

    */
    return 0;
}
