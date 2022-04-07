#include <algorithm>
#include "iostream"
#include "queue"
using namespace std;

class Banker{
    int n,m; // n --> p  // m --> R
    int *available;
    int *work;
    bool *finish;
    int* victim;
    int **Maximum;
    int **allocated;
    int **need;

public:
    queue<int> priority;
    void calcNeed() const;
    void displayNeed() const;
    void Read();
    bool CheckAllocation(int);// NeedLessThanOrEqualWork

    void display();
    bool ValidRequest(int,const int*);
    bool ValidRelease(int,const int*);
    bool Request(int,int*);
    void Release(int,int*);
    bool CheckFinish();
    bool CheckSafeState();
    void Recovery();
    Banker(int,int);
    ~Banker();
};

Banker::Banker(int row, int col) {
        n=row,m=col;
        available = new int[m];
        work = new int[m];
        finish = new bool[n];
        victim = new int[n];
        Maximum = new int*[n];
        allocated = new int*[n];
        need = new int*[n];

        for (int i = 0; i < n; ++i) {
            Maximum[i] = new int[m];
            allocated[i] = new int[m];
            need[i] = new int[m];
            finish[i] = false;
            victim[i] = -1;
        }
}

Banker::~Banker() {
        delete []available;
        delete []work;
        delete []finish;
        delete []victim;
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


    for (int i = 0; i < m; i++) {
        work[i] = available[i];
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
            cout<<"process : "<<index<<" Finished In The System\n";
            victim[index]=index;//-1 1 2 -1 4
            q.pop(); // 0 1 2 3 4
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

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int arr[n];// 0 1 2 3 4      -1 -1 2 -1 4
    for (int j = 0; j < n; j++) {
        arr[j] = j;
    }
    for (int i = 0; i < n; i++) {
        if (victim[i]==arr[i]){
            victim[i] = -1;// 1212 1 121 1212
        } else{
            victim[i] = arr[i];
            priority.push(victim[i]);
        }
    }

    if(CheckFinish())
    {
        for (int i = 0; i < n; i++)
        {
            finish[i] = false;
        }
        return true;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            finish[i] = false;
        }
        return false;
    }
}

bool Banker::CheckAllocation(int index) {
    for (int i = 0; i < m; i++) {
        if (need[index][i]>work[i]) return false;
    }
    return true;
}

bool Banker::CheckFinish() {
    for (int i = 0; i < n; i++) {
        if (!finish[i]) return false;
    }
    return true;
}

bool Banker::Request(int NumberOfP,int *arr) {
    if (ValidRequest(NumberOfP,arr)){
        cout<<"Request valid Because process "<<NumberOfP<< " Will Make The System In Safe State\n";
        Banker b(n,m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                b.allocated[i][j] = allocated[i][j];
                b.need[i][j] = need[i][j];
                b.Maximum[i][j]= Maximum[i][j];
            }
        }
        for (int i = 0; i < m; i++) {
            b.available[i] = available[i];
        }
        for (int i = 0; i < m; i++) {
            b.allocated[NumberOfP][i]+=arr[i];
            b.need[NumberOfP][i]= abs(arr[i]-b.need[NumberOfP][i]);
            b.work[i]= abs(arr[i]-b.available[i]);
        }
        int * temp = new int[m];
        for (int i = 0; i < m; i++) {
            temp[i] = b.work[i];
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
                available[i] = temp[i];
            }

            for (int i = 0; i < n; i++) {
                finish[i] = false;
            }
            return true;
        }else {
            cout<<"Request denied Because process Will Make The System In UnSafe \n";
            return false;
        }
    }
    else{
        cout<<"Request Invalid Because process "<<NumberOfP<< " Will Make The System In UnSafe State\n";
        return false;
    }
}

bool Banker::ValidRequest(int p,const int* Request) {
    for (int i = 0; i < m; i++) {
        if (Request[i]>need[p][i]) return false;
        else if(Request[i]>available[i]) return false;
    }
    return true;
}

void Banker::display() {
    cout<<"matrix of allocation\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<allocated[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"matrix of need\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<need[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"matrix of available\n";
    for (int i = 0; i < m; i++) {
        cout<<available[i]<<" ";
    }
    cout<<"\n";
}

void Banker::Release(int NumberOfP, int *Release) {
    if (ValidRelease(NumberOfP,Release)){
        for (int i = 0; i < m; i++) {
            allocated[NumberOfP][i] = abs(allocated[NumberOfP][i] - Release[i]);
//            need[NumberOfP][i] += Release[i];
            available[i] += Release[i];
        }
    }
}

bool Banker::ValidRelease(int p , const int * Release) {
    for (int i = 0; i < m; i++) {
        if (Release[i] > allocated[p][i]) {
            return false;
        }
    }
    return true;
}

void Banker::Recovery() {
    int process = priority.front();//
    int check =0;
    int arr[m];
    for (int i = 0; i < m; i++) {
        arr[i] = allocated[process][i];
    }
    while (!priority.empty() && !Request(process,arr)){
        cout<<"process "<<process<<" that request System will cause deadLock and the system try recover it\n";
        if (check!=0){

            for (int i = 0; i < m; i++) {
                allocated[process][i] = abs(allocated[process][i] - arr[i]);
//              need[NumberOfP][i] += Release[i];
                available[i] += arr[i];
            }
            if (!priority.empty()){
                priority.pop();
            }
            process = priority.front();
            for (int i = 0; i < m; i++) {
                arr[i] = allocated[process][i];
            }
        } else{
            for (int i = 0; i < m; i++) {
                allocated[process][i] = abs(allocated[process][i] - arr[i]);
//              need[NumberOfP][i] += Release[i];
                available[i] += arr[i];
            }
            check++;
            if (!priority.empty()){
                priority.pop();
                process = priority.front();
                for (int i = 0; i < m; i++) {
                    arr[i] = allocated[process][i];
                }
            }
        }
    }
}