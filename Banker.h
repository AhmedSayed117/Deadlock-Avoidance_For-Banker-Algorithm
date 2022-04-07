using namespace std;
#include "queue"

class Banker{
    int n,m; // n --> p  // m --> R
    int *available;
    int *work;
    bool *finish;

    int **Maximum;
    int **allocated;
    int **need;
public:
    void calcNeed() const;
    void displayNeed() const;
    void Read();
    bool CheckAllocation(int);// NeedLessThanOrEqualWork

    void display();
    bool ValidRequest(int,const int*);
    void Request(int,int*);
    bool CheckFinish();
    bool isFull();//work = available
    bool CheckSafeState();
    Banker(int,int);
    ~Banker();
};

Banker::Banker(int row, int col) {
        n=row,m=col;
        available = new int[m];
        work = new int[m];
        finish = new bool[n];

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
        delete []work;
        delete []finish;
        for (int i = 0; i < n; i++) {
            delete[] Maximum[i];
            delete[] allocated[i];
            delete[] need[i];
        }
        delete[] Maximum;
        delete[] allocated;
        delete[] need;
}

void Banker::calcNeed() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = abs(Maximum[i][j] - allocated[i][j]);
        }
    }
}

void Banker::displayNeed() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<need[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void Banker::Read(){

    cout << "Enter Matrix Allocated: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int num;
            cin >> num;
            allocated[i][j] = num;
        }
    }

    cout << "Enter Matrix Maximum: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int num;
            cin >> num;
            Maximum[i][j] = num;
        }
    }

    cout << "Enter Matrix Available: \n";
    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;
        available[i] = num;
    }

    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
        available[j]+=allocated[i][j];
        }
    }

}

bool Banker::CheckSafeState() {
    queue <int> q;
    for (int i = 0; i < n; i++)q.push(i);// 0 1 2 3 4
    int index = q.front(); //0
    int Current=0; //0

    while(!q.empty()){
        if (finish[index]){}
        else if(!finish[index] && CheckAllocation(index)){

            for (int i = 0; i < m; i++) {
                work[i]+=allocated[index][i]; // 3 3 2
            }

            finish[index] = true; // 0 3
            q.pop(); // 1 2 3 4
            Current = 0; // 0
        }
        else
        {
            Current++;//2
        }
        index++;// 3
        if (index == n )index=0;
        if(Current == q.size())break;//base case
    }


    if(CheckFinish()){
        return true;
    } else return false;
}

bool Banker::isFull() {
    for (int i = 0; i < m; i++) {
       if (work[i] != available[i])return false;
    }
    return true;
}

bool Banker::CheckAllocation(int index) {
    for (int i = 0; i < m; i++) {
        if (need[index][i]>work[i]) return false; // 0 1 1       3 4 2
    }
    return true;
}

bool Banker::CheckFinish() {
    for (int i = 0; i < n; i++) {
        if (!finish[i]) return false;
    }
    return true;
}

void Banker::Request(int NumberOfP,int *arr) {
    if (ValidRequest(NumberOfP,arr)){
        Banker b(n,m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                b.allocated[i][j] = allocated[i][j];
                b.need[i][j] = need[i][j];
                b.Maximum[i][j]= Maximum[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            b.finish[i] = false;
        }



        for (int i = 0; i < m; i++) {
            b.allocated[NumberOfP][i]+=arr[i];
            b.need[NumberOfP][i]= abs(arr[i]-b.need[NumberOfP][i]);
            b.work[i]= abs(arr[i]-b.work[i]);
        }
        for (int i = 0; i < m; i++) {
            b.work[i] = work[i];
        }



        if (b.CheckSafeState()){
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    allocated[i][j] = b.allocated[i][j];
                    need[i][j] = b.need[i][j];
                    Maximum[i][j]= b.Maximum[i][j];
                }
            }
            for (int i = 0; i < m; i++) {
                work[i] = b.work[i];
            }

//            for (int i = 0; i < n; i++) {
//                finish[i] = b.finish[i];
//            }

            for (int i = 0; i < n; i++) {
                b.finish[i] = false;
            }

//            for (int i = 0; i < m; i++) {
//                work[i] = available[i];
//            }
            cout<<"process " <<NumberOfP <<" added and the System will be in Safe State\n";
        }else cout<<"Request denied Because process "<<NumberOfP<<" Will Make The System In UnSafe State\n";
    }
    else cout<<"Request denied Because process "<<NumberOfP<<" Will Make The System In UnSafe State\n";
}

bool Banker::ValidRequest(int p,const int* Request) {
    for (int i = 0; i < m; i++) {
        if (Request[i]>need[p][i]) return false;
        else if(Request[i]>available[i]) return false;
    }
    return true;
}

void Banker::display() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<allocated[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<Maximum[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    for (int i = 0; i < m; i++) {
        cout<<work[i]<<" ";
    }


}
