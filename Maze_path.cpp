/* Learning backtracking in maze solving
 * Refernce: freecodecamp.org/news/backtracking-algorithms-recursive-search
 * Written by ghaith khmeydan, Completed by 3/26/2021
 * Known bugs: none so far
 * Date: March 2021 (can you believe it?)
 */

#include <iostream>
#include <list>
#include <unordered_set>
using namespace std;

/* return a path from start point to finish point in a maze
 * represented by the "adjacent lists" */
list<int> SolveMaze(const list<int> maze[], int start, int finish);
void printPath(list<int>);
void visitedNodesList(unordered_set<int>);
int main()
{
    //Step 1: Maze representation:
    // 3x3 maze:  each point/square of maze is numebered 0, 1, 2, ...8
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // maze[i] stores the list  of points that point i is connected with
    list<int> maze[9]; //implemented as doubly-linked list
                       //to study more about list: https://www.cplusplus.com/reference/list/list/

    maze[0].push_back(1);
    maze[0].push_back(3);

    maze[1].push_back(0);
    maze[1].push_back(2);

    maze[2].push_back(1);

    maze[3].push_back(0);
    maze[3].push_back(4);

    maze[4].push_back(3);
    maze[4].push_back(5);
    maze[4].push_back(7);

    maze[5].push_back(4);

    maze[6].push_back(3);

    maze[7].push_back(4);
    maze[7].push_back(8);

    maze[8].push_back(7);

    list<int> path = SolveMaze(maze, 0, 8);
    cout << endl;
    cout << "The path traversed\n";
    printPath(path);
}

//Pratice #1.: Write a function to print path, a list of int
// first: let's review iterator: https://www.geeksforgeeks.org/iterators-c-stl/
// now let's practice use an iterator to print all points stored in path

//Pratice #2.: Write a function to print visited, an unordered_set of int

//Practice #3:add cout statements to SolveMaze show the progress:
//   1) when you go to a new point... "going to point ...", diplay path, display visted
//   2) when you backtracking  ... "backtracking to previous point...", display path, display visited
//

/* return a path from start point to finish point in a maze
 * represented by the "adjacent lists" */
void printPath(list<int> path)
{
    for (list<int>::iterator it = path.begin(); it != path.end(); it++)
    {
        int cur_point = *it;
        cout << cur_point << ", ";
    }
    cout << endl;
}

void visitedNodesList(unordered_set<int> vis)
{
    cout << "The list of visited nodes ";
    for (unordered_set<int>::iterator it = vis.begin(); it != vis.end(); it++)
    {
        int cur_point = *it;
        cout << cur_point << ", ";
    }
    cout << endl;
}
list<int> SolveMaze(const list<int> maze[], int start, int finish)
{
    //key data structures used:
    //
    unordered_set<int> visited; //The set of points that have been visited already
                                //implemented using hashtable
                                //https://www.cplusplus.com/reference/unordered_set/unordered_set/

    int current_point; //where we are right now?
    list<int> path;    //keep track the current path from start point to current point
                       // 2, 3, 1 => path 2, 3, 1

    //Initialization: what do we need to do?
    current_point = start;
    path.push_back(start);
    visited.insert(start);
    cout << "Started from " << current_point << endl;
    //Enter a loop
    //  as long as we haven't reached finish point yet, or path is not empty
    //    we check if current_point has any neighboring point that has not been visited
    //    yet, if so, we go to the neighboring point;
    //    else, we have reached a deadend, need to backtrack to previous point
    while (current_point != finish && path.size() != 0)
    {

        list<int> neighbors = maze[current_point];

        bool found = false; //Have we found a unvisited neighboring node yet?
        int cur_neighbor;
        for (list<int>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
        {
            cur_neighbor = *it; //dereference an iterator is like
                                //deferencing a point
            if (visited.find(cur_neighbor) == visited.end())
            {
                //cur_neighbor is not in visited set
                found = true;
                break; //Todo: We shall avoid using break, how?
            }
        }
        if (found)
        {
            //we find a neighbor that is not visited yet
            cout << "Going to point " << cur_neighbor << endl;
            path.push_back(cur_neighbor);
            visited.insert(cur_neighbor);
            cout << "Current Path => ";
            for (list<int>::iterator it = path.begin(); it != path.end(); it++)
            {
                int cur_point = *it;
                cout << cur_point << ", ";
            }
            cout << endl;
            visitedNodesList(visited);
        }
        else
        { //no way to go from current_point
            //backtrack by going back to previous point

            path.pop_back();
            current_point = path.back();
            cout << "Backtracking now" << endl;
            cout << "Current Path => ";
            for (list<int>::iterator it = path.begin(); it != path.end(); it++)
            {
                int cur_point = *it;
                cout << cur_point << ", ";
            }
            cout << endl;
            visitedNodesList(visited);
        }

        //either way, current point is the point at the back of path

        current_point = path.back();
        //cout << "current point is " << current_point << endl;

        //Think about this: what's the loop invariant?
        // what's in the path?
    }
    cout << "\nReached the destination!!\n";

    //post-condition: either path is empty; or current_point==finish, and pathstores
    // the path from start to finish: 0->3->4->7->8

    return path;
}
