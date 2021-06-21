/* Learning backtracking in maze solving
 * Refernce: freecodecamp.org/news/backtracking-algorithms-recursive-search
 * Written by Prof. Zhang, Completed by ....
 * Known bugs: none so far
 * Date: March 2021 (can you believe it?)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

//Read a maze/graph from a file, format as below:
//9 ## first line givens the total number of nodes, followed by 9 lines
// 0 1 3   #point 0 is connected with node 1 and node 3
// 1 0 2
// 2 1    #point 2 is only connected with 1
//...
// 8  ## this would mean that point 8 is NOT connected with any other point
//Post-condition: set NodeNum to the total numbre of nodes, and return
//                adjacent lists vector
vector<list<int>> ReadGraph(string fileName, int& NodeNum);


/* return a path from start point to finish point in a maze
 * represented by the "adjacent lists" */
list<int> SolveMaze(const vector<list<int>>& maze, int start, int finish);

/* Print a path */
void PrintPath(list<int>& path);

// Print the set of visited of nodes
void PrintVisited(const unordered_set<int>& visited);

/* Recursive maze walker and its wrapper */
list<int> SolveMaze_Wrapper(const vector<list<int>>& maze, int start, int finish);
list<int> SolveMaze_Recursive(const vector<list<int>>& maze, int current_point,int finish, unordered_set<int>& visited);

// Calculate and print nodes degree, directed or undirected, and adjacency matrix
void GraphInfo(const vector<list<int>>& graph);

void DFSFromSource(const vector<list<int>>& maze, int start,
    unordered_set<int>& visited);

void DFS(const vector<list<int>>&);

int main()
{
    int nodeNum;
    string fileName = "testMaze.txt";

    vector<list<int>> maze = ReadGraph(fileName, nodeNum);

    GraphInfo(maze);

    unordered_set<int> visited;

    DFS(maze);
    //DFSFromSource(maze, 0, visited);
}

// use an iterator to print all points stored in path
void PrintPath(list<int>& path)
{
    list<int>::iterator it; //an iterator to iterate through path...


    cout << "Path is ";
    for (it = path.begin(); it != path.end(); it++)
    {
        cout << *it << ","; //dereference it to get int element
    }
    cout << endl;

}

//Write a function to print visited, an unordered_set of int
void PrintVisited(unordered_set<int>& visited)
{
    unordered_set<int>::iterator it;

    cout << "Visited points:";
    for (it = visited.begin(); it != visited.end(); it++)
        cout << *it << ",";
    cout << endl;
}

// Top level function
list<int> SolveMaze_Wrapper(const vector<list<int>>& maze, int start, int finish)
{
    unordered_set<int> visited; //this will be passed to all recursive calls

    return SolveMaze_Recursive(maze, start, finish, visited);
}

//Practice #1: cout statements to SolveMaze show the progress:
//   1) when you go to a new point... "going to point ...", diplay path, display visted
//   2) when you backtracking  ... "backtracking to previous point...", display path, display visited
/* Recursive function to return a path from current_point to finish point,
   using only points that are not visited yet. */
list<int> SolveMaze_Recursive(const vector<list<int>>& maze, int current_point,
    int finish, unordered_set<int>& visited)
{
    list<int> subPath, path;
    cout << "Recursive " << current_point << endl;

    if (current_point == finish) {
        path.push_back(current_point);
        return path;
    }


    list<int> neighbors = maze[current_point];
    visited.insert(current_point);
    for (list<int>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
    {
        int cur_neighbor = *it;
        if (visited.find(cur_neighbor) == visited.end()) {
            subPath = SolveMaze_Recursive(maze, cur_neighbor, finish, visited);

            // if the above function find a path, then add current point to the front
            //   of returned path, and return it.
            if (subPath.size() != 0) {
                path = subPath;
                path.insert(path.begin(), current_point);
                return path;
            }
        }
    }
    return path;  //path will be empty at this point
}

//

/* Perform a DFS traversal using "start" as our starting node,
   visit all nodes taht are reachable from start point */
void DFSFromSource(const vector<list<int>>& maze, int start,unordered_set<int>& visited)
{
    //key data structures used:
    //
    //unordered_set<int> visited; //The set of points that have been visited already
               //implemented using hashtable
       //https://www.cplusplus.com/reference/unordered_set/unordered_set/

    int current_point; //where we are right now?
    list<int> path;//keep track the current path from start point to current point
   // 2, 3, 1 => path 2, 3, 1

    //Initialization: what do we need to do?
    current_point = start;
    path.push_back(start);
    visited.insert(start);


    while (path.size() != 0) {

        list<int> neighbors = maze[current_point];

        bool found = false; //Have we found a unvisited neighboring node yet?
        int cur_neighbor;
        for (list<int>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
        {
            cur_neighbor = *it; //dereference an iterator is like
                       //deferencing a point
            if (visited.find(cur_neighbor) == visited.end()) {
                //cur_neighbor is not in visited set
                found = true;
                break; //Todo: We shall avoid using break, how?
            }
        }
        if (found) { //we find a neighbor that is not visited yet
            cout << "----------------------------------------------" << endl;
            cout << "Going to point: " << cur_neighbor << endl;
            path.push_back(cur_neighbor);
            visited.insert(cur_neighbor);
            current_point = path.back(); //current point is the point at the back of path,
                //i.e., what is push_back just now

            PrintPath(path);
            PrintVisited(visited);
        }
        else {
            //no way to go from current_point
    //backtrack by going back to previous point
            cout << "----------------------------------------------" << endl;
            cout << "Backtracking...";
            path.pop_back();   //This remove last element from path

            current_point = path.back(); //current_point is now the previos point

            cout << "current point is " << current_point << endl;

            PrintPath(path);
            PrintVisited(visited);
        }
        //Think about this: what's the loop invariant?
        // what's in the path?
    }
}

void DFS(const vector<list<int>>& graph)
{
    unordered_set<int> visisted;
    int u=0;
    //Pratice
    //as long as there is a node, u, that is not visited yet,
    // call DFSFromSource using that u as source
    DFSFromSource (graph, u, visisted);
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"Traversal Completed"<<endl;

}

vector<list<int>> ReadGraph(string fileName, int& NodeNum) {
    string line;
    ifstream graphFile(fileName);
    int u, v;

    if (!graphFile.is_open()) {
        vector<list<int>> emptylists;
        cout << "Failed to open file " << fileName << endl;
        return emptylists;
    }

    graphFile >> NodeNum;
    //cout <<"Total # of nodes:" << NodeNum;
    vector<list<int>> lists(NodeNum);

    getline(graphFile, line);

    //graphFile >> u;
    while (getline(graphFile, line))
    {
        stringstream s(line);

        s >> u;
        list<int> adj;
        while (s >> v) {
            adj.push_back(v);
        }
        lists[u] = adj;
    }

    graphFile.close();
    return lists;
}

// Calculate and print nodes degree, directed or undirected, and adjacency matrix
void GraphInfo(const vector<list<int>>& graph)
{
    int nodeNum = graph.size();

    for (int i = 0; i < nodeNum; i++)
    {
        cout << "Node" << i << " out-degree: " << graph[i].size() << endl;
    }
    int sum=0;
    //check if the graph is directed or not
    int adjMat[nodeNum][nodeNum];
    for(int i=0;i<nodeNum;i++)
    {
        for(int j=0;j<nodeNum;j++)
            adjMat[i][j]=0;
    }
    for(int i=0;i<nodeNum;i++)
    {
        for(auto &j : graph[i])
        {
            int x=j;
            adjMat[i][x]=1;
        }
    }
    for(int i=0;i<nodeNum;i++)
    {
        for(int j=0;j<nodeNum;j++)
        {
            if(adjMat[i][j]==1)
                sum+=1;
            if(adjMat[j][i]==1)
                sum-=1;
        }
    }
    if(sum==0)
        cout<<"Graph is undirected"<<endl;
    else
        cout<<"Graph is directed"<<endl;
    //print out the adjacency matrix of the graph
    cout<<"Adjacency Matrix for the graph"<<endl;
    for(int i=0;i<nodeNum;i++)
    {
        for(int j=0;j<nodeNum;j++)
        {
            cout<<adjMat[i][j]<<" ";
        }
        cout<<endl;
    }

}
