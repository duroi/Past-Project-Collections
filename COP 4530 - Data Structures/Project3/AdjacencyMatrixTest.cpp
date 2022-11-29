#include <bits/stdc++.h>
#include <vector>


using namespace std;


int main()
{
// 
ifstream in("sample-graph1.txt");
 
vector<vector<int>> matrix;

int n;
int m;
if (!in.is_open()) {
        cout << "Couldn't open " << "file" << "\n";
    }
    //Read n and m
    in >> n >> m;
    in.ignore(); //Ignore \n
    string line;
    int idx1, idx2, val;
    // Resizing the matrix data member
    matrix.resize(n);
    for(int i = 0; i<n; i++) {
        matrix[i].resize(n, 0);
    }
    // Getting input line by line and storing it in the matrix
    for (int i = 0; i < m; i++) {
        getline(in, line);
        stringstream  ss(line);
        ss >> idx1 >> idx2;
        matrix[idx1][idx2] = 1;
    }


    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            cout << matrix[i][j] << " ";
        }   
        cout << endl;
    }
}
