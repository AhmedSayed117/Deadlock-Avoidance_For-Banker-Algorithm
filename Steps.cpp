#include "Steps.h"
#include "iostream"

void Steps::Read2dFromFile(const string& fileName, int **arr,int n,int m) {
    int*temp = new int [n*m];
    basic_string<char> ch;int i=0;
    file.open(fileName);
    while (true)
    {
        file>>ch;
        temp[i++] = stoi(ch);
        if (file.eof())break;
    }
    file.close();
    int index =0;
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < m; k++) {
            arr[j][k] = temp[index++];
        }
    }
    delete[]temp;
}

void Steps::Read1dFromFile(const string& fileName, int *arr,int m) {
    int*temp = new int [m];
    basic_string<char> ch;int i=0;
    file.open(fileName);
    while (true)
    {
        file>>ch;
        temp[i++] = stoi(ch);
        if (file.eof())break;
    }
    file.close();
    int index =0;
    for (int j = 0; j < m; j++) {
        arr[j] = temp[index++];
    }
    delete[]temp;
}

int **Steps::calcNeed(int **Max, int **allocate,int **need,int n,int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = Max[i][j] - allocate[i][j];
        }
    }
    return need;
}

void Steps::displayNeed(int **arr,int n,int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
}