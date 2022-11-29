p2memo.cpp
#include <iostream>
#include <vector>
using namespace std;

vector<vector<double>> solutions;
vector<vector<vector<double>>> solutions3;
vector<double> solSeq;
// vector<double> solSeq1;
// vector<double> solSeq2;



double cos_sim(vector<double> x, int i, vector<double> y, int j, vector<double> t, int k)
{
    double op1 = 0;
    double op2 = 0;
    vector<int>sol;
    int n = x.size();
    int m = y.size();
    
    //no more values to compute score, target reached size n + m
    if(k == n + m) 
        return 0;
    //values of both seq1 and seq2 remain, so we still need to recurse
    //on the next options of both sequences
    else if( i != n && j != m) 
    {
        solSeq[k] = x[i];
        op1 = x[i]*t[k] + cos_sim(x , i + 1, y , j , t , k + 1);
        // solSeq1[k] = x[i];

        solSeq[k] = y[j];
        op2 = y[j]*t[k] + cos_sim(x , i, y, j + 1, t, k + 1);
        // solSeq2[k] = y[j];
    }
    //if sol already has all of seq1 but not all of seq2 yet
    else if (i == n && j != m)
    {
        solSeq[k] = y[j];
        op1 = y[j]*t[k] + cos_sim(x , i, y, j + 1, t, k + 1);
        // solSeq1[k] = y[j];
    }
    //if sol already has al of seq2 but not all of seq1 yet
    else if (i != n && j == m)
    {
        solSeq[k] = x[i];
        op2 = x[i]*t[k] + cos_sim(x , i + 1, y, j, t , k + 1);
        // solSeq2[k] = x[i];

    }



//Saving to matrix

    //if k == t.size() - 1, then we're in the top left of the matrix
    if (k == t.size() - 1 && i == x.size()) {
        // cout <<"1: "<< i << ":" << j<< ":" << k << endl;
        if ((op1) >= (op2)) {
            solutions[0][0] = op1;        
            for(int a = 0; a < t.size(); a++){
                solutions3[0][0][a] = solSeq[a];
            }
        }
        else {
            solutions[0][0] = op2;
            for(int a = 0; a < t.size(); a++){
                solutions3[0][0][a] = solSeq[a];
            }
        }
    }
    //if k = 0, then we're in the in the bottom right of the matrix
    else if (k == 0){
        //cout <<"2: "<< i << ":" << j<< ":" << k << endl;
        if ((op1) >= (op2)) {
        // cout <<"2.1: "<< i << ":" << j<< ":" << k << endl;
            solutions[n - 1][m - 1] = op1;        
            for(int a = 0; a < t.size(); a++){
                solutions3[n - 1][m - 1][a] = solSeq[a];
            }
        }
        else {
        // cout <<"2.2: "<< i << ":" << j<< ":" << k << endl;
            solutions[n - 1][m - 1] = op2;
            for(int a = 0; a < t.size(); a++){
                solutions3[n - 1][m - 1][a] = solSeq[a];
            }
        }
    }

    // if k != 0 or t.size() 
    else {
        //i == n, we're in column 0 
        if (k != t.size() && i == n ) {
            // cout <<"3: "<< i << ":" << j<< ":" << k << endl;
            solutions[n - i][m - j - 1] = op1;
            for(int a = 0; a < t.size(); a++){
                solutions3[n - i][m - j - 1][a] = solSeq[a];
            }        
        }
        //j == m, we're in row 0 
        else if (k != t.size() && j == m) {
            // cout <<"4: "<< i << ":" << j<< ":" << k << endl;            
            solutions[n - i - 1][m - j] = op2;
            for(int a = 0; a < t.size(); a++){
                solutions3[n - i - 1][m - j][a] = solSeq[a];
            }
        }
        //
        else {
            //cout <<"5: "<< i << ":" << j<< ":" << k << endl;

            if ((op1) >= (op2)) {
                // cout <<"5.1: "<< i << ":" << j<< ":" << k << endl;
                solutions[n - i - 1][m - j - 1] = op1;        
                for(int a = 0; a < t.size(); a++){
                    solutions3[n - i - 1][m - j - 1][a] = solSeq[a];
                }
            }
            else {
                // cout <<"5.2: "<< i << ":" << j<< ":" << k << endl;
                solutions[n - i - 1][m - j - 1] = op2;
                for(int a = 0; a < t.size(); a++){
                    solutions3[n - i - 1][m - j - 1][a] = solSeq[a];
                }
           }
        }
    }

    cout << endl;
    return max(op1, op2);
}

int main()
{
//    vector<double> s1 = {-0.2742,0.2195,0.0291,-0.1251,-0.1341,0.0184,0.2053,-0.0918,-0.1009,0.2517,-0.1632,0.0514,0.0419,0.3797,-0.2062}; 

//    vector<double> s2 = {-0.4702,-0.2227,0.2929,0.0387,-0.0131,0.0689,0.1644,0.0365,-0.3298};

//    vector<double> target = {-0.1513,0.1748,0.0366,-0.0787,-0.5992,-0.0785,-0.1488,0.1381,0.0329,-0.0138,0.0870,0.0113,0.1329,0.2018,-0.1088,-0.0484,0.0262,-0.4134,0.3257,-0.1048,0.0377,0.0532,0.3544,-0.1801};

//pdf sample

    // vector<double> s1 = {0.1, 0.2, 0.7}; 

    // vector<double> s2 = {0.1, 0.3, 0.6};

    // vector<double> target = {0.1, 0.2, 0.1, 0.3, 0.7, 0.6};

//small example 
   
    Bvector<double> s1 = {0.1, 0.7}; 

    vector<double> s2 = {-0.5, 0.5};

    vector<double> target = {0.0625, 0.1875, 0.3125, 0.9375};

    //resize the solutions matrix to n by m, values are between -1 and 1 so initilize to -2 
    solutions.resize(s1.size(), vector<double>(s2.size(), -2.0));
    //solSeq1.resize(target.size(), -2.0);
    //solSeq2.resize(target.size(), -2.0);
    solutions3.resize(s1.size());
    for(int i = 0; i < s1.size(); i++){
        solutions3[i].resize(s2.size());
        for(int j = 0; j < s2.size(); j++) {
            solutions3[i][j].resize(target.size());
            // for (int k = 0; k < target.size(); k++){
            //     solutions3[i][j][k] = -2.0;
            // }
        }
    }
    // solutions3.resize(s1.size(), s2.size(), vector<double>(target.size(), -2.0));
    solSeq.resize(target.size(), -2.0);
    
    double x = cos_sim(s1, 0, s2, 0, target, 0);
    cout << x << endl << endl;
    

    //iterate though solutions 
    for (int i = 0; i < solutions.size(); i++) {
        for (int j = 0; j < solutions[i].size(); j++)
            cout << solutions[i][j] << " ";
        cout << endl;
    }

    for(int i = 0; i < target.size(); i++){
        cout << solutions3[s1.size() - 1][s2.size() - 1][i] << " ";
    }
    cout << endl;
}

