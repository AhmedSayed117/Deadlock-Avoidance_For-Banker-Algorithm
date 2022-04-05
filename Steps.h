#include <fstream>
using namespace std;
class Steps {
    ifstream file;
public:
    void Read2dFromFile(const string&,int**,int,int);
    void Read1dFromFile(const string&,int*,int);
    static int** calcNeed(int**,int**,int**,int,int);
    static void displayNeed(int**,int,int);
};