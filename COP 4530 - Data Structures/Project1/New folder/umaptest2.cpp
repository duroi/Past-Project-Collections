#include <iostream>
#include <unordered_map>
using namespace std;


int main()
{

    unordered_map<string, int> umap;

    umap["THIS"] = 55;
    umap["IS"] = 33;
    umap["A"] = 99999;
    umap["TEST"] = 0;


    for (auto x : umap)
        cout << x.first << " " << x.second << endl;

    return 0;    
}