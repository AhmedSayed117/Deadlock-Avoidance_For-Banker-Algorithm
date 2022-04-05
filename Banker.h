using namespace std;
#include <fstream>

struct Banker{
public:
    int n,m;
    int *available;
    int **Maximum;
    int **allocated;
    int **need;
    Banker(int,int);
    ~Banker();
};

Banker::Banker(int row, int col) {
        n=row,m=col;
        available = new int[m];
        Maximum = new int*[n];
        allocated = new int*[n];
        need = new int*[n];
        for (int i = 0; i < n; ++i) {
            Maximum[i] = new int[m];
            allocated[i] = new int[m];
            need[i] = new int[m];
        }
}

Banker::~Banker() {
        delete []available;
        for (int i = 0; i < n; i++) {
            delete[] Maximum[i];
            delete[] allocated[i];
            delete[] need[i];
        }
        delete[] Maximum;
        delete[] allocated;
        delete[] need;
}