#include <iostream>
#include "Banker.h"
#include "Steps.h"
using namespace std;

int main() {
    int n =5,m=3;
    Banker b(n,m);
    Steps s;

    s.Read2dFromFile("../files/max.txt",b.Maximum,n,m);
    s.Read2dFromFile("../files/allocate.txt",b.allocated,n,m);
    s.Read1dFromFile("../files/available.txt",b.available,m);
    Steps::calcNeed(b.Maximum,b.allocated,b.need,n,m);
    Steps::displayNeed(b.need,n,m);
}