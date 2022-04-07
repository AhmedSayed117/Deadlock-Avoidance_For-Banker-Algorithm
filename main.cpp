#include <iostream>
#include "Banker.h"
using namespace std;

int main() {
    //displayNeed checkSafe Read request release
    // recovery display
    int n,m;
    cout<<"Banker Algorithm\n";
    cout<<"Enter Number of Processes : ";cin>>n;
    cout<<"Enter Number of Resources : ";cin>>m;
    Banker b(n,m);
    while(true){
        b.Read();
        here:
        char choose;
        cout<<"1- calc matrix of need\n2- Display Need\n3- Check if System in The safe state or Not\n4- Request process\n5- Display matrices of allocation, Maximum and Available\n6- exit\n";
        cin>>choose;
        switch (choose) {
            
            case '1':
            {
                b.calcNeed();
                goto here;
            }
            case '2':
            {
                b.displayNeed();
                goto here;
            }
            case '3':
            {
                if (b.CheckSafeState()){
                    cout<<"The System In Safe State\n";
                }else{
                    here2:
                    cout<<"The System is Not Safe State\n\n";
                    cout<<"1- Recovery\n2- close\n";
                    char choose2;int r;
                    cin>>choose2;
                    switch (choose2) {
                        case '1':{
                            int arr[m];
                            for (int i = 0; i < m; i++) {
                                cout<<"Enter r"<< i+1<<" : ";
                                cin>>r;
                                arr[i] = r;
                            }
                            cout<<"\n";
                            b.Recovery(arr);
                            goto here;
                        }
                        case '2':{
                            goto here;
                        }
                        default:{
                            cout<<"invalid choice\n";
                            goto here2;
                        }
                    }
                }
                goto here;
            }
            case '4':{

                goto here;
            }
            case '5':{

                goto here;
            }
            case '6':{
                exit(0);
            }
            default: {
                cout<<"invalid choice\n";
                goto here;
            }
        }
    }

}