#include <iostream>
#include "Banker.h"
using namespace std;
/*
    Ahmed Sayed Hassan Youssef          ==> 20190034   ==> s1,s2
    khaled Ashraf Hanafy mahmoud        ==> 20190186   ==> s1,s2
    Ebrahim mohammed Ebrahim Hegii      ==> 20190009   ==> s1,s2
    Omar Mohammed mahmoud awad          ==> 20190730   ==> s1,s2
*/
int main() {
    int n,m;
    cout<<"Banker Algorithm\n";
    cout<<"Enter Number of Processes : ";cin>>n;
    cout<<"Enter Number of Resources : ";cin>>m;
    Banker b(n,m);
    while(true){
        b.Read();
        here:
        char choose;
        cout<<"1- calc matrix of need\n2- Display Need\n3- Check if System in The safe state or Not\n4- Request process\n5- Release Resource\n6- Display matrices of allocation, Maximum and Available\n7- exit\n";
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
//                            int arr[m];
                            //RQ <1> <1> <2> <3> <4> <5>
//                            for (int i = 0; i < m; i++) {
//                                cout<<"Enter r"<< i+1<<" : ";
//                                cin>>r;
//                                arr[i] = r;
//                            }
//                            cout<<"\n";
                            b.Recovery();
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
                int arr[m];
                cout<<"Enter Process Number: ";
                int num,R;
                cin>>num;
                for (int i = 0; i < m; i++) {
                    cout<<"Enter r"<< i+1<<" : ";
                    cin>>R;
                    arr[i] = R;
                }
                b.Request(num,arr);
                goto here;
            }
            case '5':{
                int arr[m];
                cout<<"Enter Process Number: ";
                int num,rel;
                cin>>num;
                for (int i = 0; i < m; i++) {
                    cout<<"Enter r"<< i+1<<" : ";
                    cin>>rel;
                    arr[i] = rel;
                }
                b.Release(num,arr);
                goto here;
            }
            case '6':{
                b.display();
                goto here;
            }
            case '7':{
                exit(0);
            }
            default: {
                cout<<"invalid choice\n";
                goto here;
            }
        }
    }
}