/* Igli Duro
 * Project 3
 * Dr. William Hendrix
 * COT 4400
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// Graph struct
// V = number of verticies
// adjList = adjacency list representation of the graph using a unordered_set
// labels = vector of labels for the verticies, 1:1
// swings = vector of swings for the verticies, 2:1 
//    A vector can have at most two edges
//    Swing 3 corresponds to swings[vertexNum*2]
//    Swing 4 corresponds to swings[vertexNum*2+1]

struct Graph 
{
    int V;
    unordered_set<int>* adjList;
    vector<string>labels;
    vector<int>swings;
 
};


//Create graph function
Graph* createGraph(int V) 
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->adjList = new unordered_set<int>[V];
    graph->swings.resize(V*2, -1);

    return graph;
}

//Add edge function, takes in source vertex and destination vertex.
void addEdge(Graph* graph, int src, int dest)
{
    graph->adjList[src].insert(dest);
}



//Modified BFS algorithm, takes in the graph, starting vertex and target vertex
//Returns a vector containing a path to JoJo
vector<int> BFS(Graph* graph, int u, int v) {
    
    vector<bool> discovered;
    vector<int> explored;
    
    //Unorderd map to track parents of nodes 
    unordered_map<int,int> pmap;
    discovered.resize(graph->V, false);
    queue<int> queue;


    queue.push(u);
    discovered[u] = true;
    while (!(queue.empty())){  
        int i = queue.front();
        queue.pop();
        unordered_set<int> neighbors = graph->adjList[i];

        //if neighbor is undiscovered, add neighbor to queue and mark discovered, add neighbor and parent to map.
        for (auto itr = neighbors.begin(); itr != neighbors.end(); ++itr){
            if (discovered[*itr] == false){
                queue.push(*itr);
                discovered[*itr] = true;
                pmap[*itr] = i;
            }
        }
        explored.push_back(i);
    }

    //Starting from the target vertex v, add v to jojoPath and look up v in pmap.
    //If v is in pmap, set v = itr->second.
    //Else set flag to false, breaking the loop.
    int flag = true;
    vector<int> jojoPath;
    int vertex = v;
    while (flag){
        auto itr = pmap.find(v);
        jojoPath.push_back(v);
        if (itr != pmap.end()){
            v = itr->second;
        }
        else {
            flag = false;
        }
    }

    //Reverse path to get correct order.
    reverse(jojoPath.begin(), jojoPath.end());
    return jojoPath;
}

int main()
{
    ifstream infile;

    //Open File
    infile.open("input.txt");

    //Test files
    //infile.open("small.txt");
    //infile.open("tarzan.txt");
    //infile.open("large.txt");
    
    //Vector to hold maze
    vector<vector<string>> maze;
    
    //m = rows, n = columns, x,y = startsapce
    int m, n, x, y;

    infile >> m >> n;
    infile >> x >> y;

    //Resize maze to correct dimensions, initilize all to 0. 
    maze.resize(m, vector<string>(n, "0"));
    
    //Read maze from input
    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            infile >> maze[i][j];
        }
    }
    //Maze in now in matrixstring label;

    //Create graph with n*m verticies
    struct Graph* graphM = createGraph(n*m);

    string label;
    
    //current vertex
    int vNum = 0;
    int target = -1;

    //Nested for loop to build the adjacency list
    //Match label, check if "swing" would be in bounds, add edge if so.
    //Ignore if vertex to be swung to has a label of "X"
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j <maze[i].size(); j++) {
            label = maze[i][j];
            //cout << label << " ";
            
            if (label == "N") {
                    graphM->labels.push_back("N");
                    if((i - 3 >= 0) && (maze[i-3][j] != "X")){
                        addEdge(graphM, vNum, vNum - n * 3);
                        graphM->swings[vNum*2] = vNum - n * 3;
                    }
                    if((i - 4 >= 0) && (maze[i-4][j] != "X")){
                        addEdge(graphM, vNum, vNum - n * 4 );
                        graphM->swings[vNum*2+1] = vNum - n * 4;
                    }
            }
            else if (label == "E"){
                    graphM->labels.push_back("E");
                    if((j + 3 <= n-1) && (maze[i][j+3] != "X")){
                        addEdge(graphM, vNum, vNum + 3);
                        graphM->swings[vNum*2] = vNum + 3;
                    }
                    if((j + 4 <= n-1) && (maze[i][j+4] != "X")){
                        addEdge(graphM, vNum, vNum + 4);
                        graphM->swings[vNum*2+1] = vNum + 4;
                    }
            }
            else if (label == "S"){
                    graphM->labels.push_back("S");
                    if((i + 3 <= m-1) && (maze[i+3][j] != "X")){
                        addEdge(graphM, vNum, vNum + n * 3 );
                        graphM->swings[vNum*2] = vNum + n * 3;
                    }
                    if((i + 4 <= m-1) && (maze[i+4][j] != "X")){
                        addEdge(graphM, vNum, vNum + n * 4 );
                        graphM->swings[vNum*2+1] = vNum + n * 4;
                    }
            }
            else if (label == "W"){
                    graphM->labels.push_back("W");
                    if((j - 3 >= 0) && (maze[i][j-3] != "X")){
                        addEdge(graphM, vNum, vNum - 3 );
                        graphM->swings[vNum*2] = vNum - 3;
                    }
                    if((j - 4 >= 0) && (maze[i][j-4] != "X")){
                        addEdge(graphM, vNum, vNum - 4 );
                        graphM->swings[vNum*2+1] = vNum - 4;
                    }
            }
            else if(label == "NE"){
                    graphM->labels.push_back("NE");
                    if((i - 3 >= 0) && (j + 3 <= n-1) && (maze[i-3][j+3] != "X")){
                        addEdge(graphM, vNum, vNum - (3*n - 3));
                        graphM->swings[vNum*2] = vNum - (3*n - 3);
                    }
                    if((i - 4 >= 0) && (j + 4 <= n-1) && (maze[i-4][j+4] != "X")){
                        addEdge(graphM, vNum, vNum - (4*n - 4));
                        graphM->swings[vNum*2+1] = vNum - (4*n - 4);
                    }
            }
            else if(label == "SE"){
                    graphM->labels.push_back("SE");
                    if((i + 3 <= m-1) && (j + 3 <= n-1) && (maze[i+3][j+3] != "X")){
                        addEdge(graphM, vNum, vNum + (3*n + 3));
                        graphM->swings[vNum*2] = vNum + (3*n + 3);
                    }
                    if((i + 4 <= m-1) && (j + 4 <= n-1) && (maze[i+4][j+4] != "X")){
                        addEdge(graphM, vNum, vNum + (4*n + 4));
                        graphM->swings[vNum*2+1] = vNum + (4*n + 4);
                    }
            }
            else if(label == "NW") {
                    graphM->labels.push_back("NW");
                    if((i - 3 >= 0) && (j - 3 >= 0) && (maze[i-3][j-3] != "X")){
                        addEdge(graphM, vNum, vNum - (3*n + 3));
                        graphM->swings[vNum*2] = vNum - (3*n + 3);
                    }
                    if((i - 4 >= 0) && (j - 4 >= 0) && (maze[i-4][j-4] != "X")){
                        addEdge(graphM, vNum, vNum - (4*n + 4));
                        graphM->swings[vNum*2+1] = vNum - (4*n + 4);
                    }
            }
            else if(label == "SW"){
                    graphM->labels.push_back("SW");
                    if((i + 3 <= m-1) && (j - 3 >= 0) && (maze[i+3][j-3] != "X")){
                        addEdge(graphM, vNum, vNum + (3*n - 3));
                        graphM->swings[vNum*2] = vNum + (3*n - 3);
                    }
                    if((i + 4 <= m-1) && (j - 4 >= 0) && (maze[i+4][j-4] != "X")){
                        addEdge(graphM, vNum, vNum + (4*n - 4));
                        graphM->swings[vNum*2] = vNum + (4*n - 4);
                    }
            }
            else if (label == "X"){
                    graphM->labels.push_back("X");
                    //cout << vNum << ". " << "We don't care about 'X', it is stinky";
            }

            else {
                if(label == "J"){
                    graphM->labels.push_back("J");
                    //found target vertex
                    target = vNum;
                    //cout << target << ". " << "I'm coming for you JoJo";
                }
            }
            vNum++;
        }
    } 
    
    int initial = 0;

    //calculate initial vertex
    initial = (m * (x - 1)) + (y-1);
    //Call BFS, returns a correct path to target
    vector<int> path = BFS(graphM, initial, target);

    //Write to file.
    ofstream outfile;
    outfile.open("output.txt");
    for(int i = 0; i < path.size()-1; i ++){
        outfile << graphM->labels[path[i]];
        outfile << "-";

        // cout << graphM->swings[path[i]*2] << endl;
        // cout << graphM->swings[path[i]*2+1] << endl;

        if ((path[i+1]) == (graphM->swings[path[i]*2])){
            outfile << 3;
        }
        else if ((path[i+1]) == (graphM->swings[path[i]*2+1])){
            outfile << 4;
        }

        outfile << " ";
    }


    return 0;
}