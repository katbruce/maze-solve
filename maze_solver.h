//Kathryn Bruce
/*
    maze_solver.h

    Class declaration for the maze_solver class.

*/

#ifndef _MAZE_SOLVER_H
#define _MAZE_SOLVER_H

#include <iostream>

#include <vector>
#include <queue>
#include <stack>


using namespace std;


class maze_solver {
public:
    // constructor
    maze_solver(string infile, bool use_stak, bool pause=false);

    // public methods
    void initialize();
    void run();
    void step();
    void write_maze(ostream& out);
    void pause();

    // instance variables
    string maze_name;
    bool use_stack;
    bool do_pause;

    int rows, columns;
    vector<string> maze;

    bool no_more_steps;
    bool goal_reached;

    // TODO: your own public methods or variables here?
    void update_map_s(pair<int,int> temp);//checks each new element of stack
    void update_map_q(pair<int,int> temp);// or queue and reacts accordingly
    //points of significance
    pair<int,int> starting;
    pair<int,int> finish;
    //stack
    stack <pair<int,int>> s;//row,col
    //queue
    queue <pair<int,int>> q;//row,col
private:

};

#endif