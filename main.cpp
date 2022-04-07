#include <iostream>
#include "Banker.h"
using namespace std;

int main() {
    int n,m;
    cout<<"Enter Number of Processes : ";cin>>n;
    cout<<"Enter Number of Resources : ";cin>>m;
    Banker b(n,m);
    b.Read();
    b.calcNeed();
    b.displayNeed();
    int arr[3] ={1,0,2};

    b.Request(1,arr);
    int arr2[3] ={3,2,2};
    b.Request(0,arr2);
}