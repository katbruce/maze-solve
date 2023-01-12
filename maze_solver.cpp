//Kathryn Bruce
/*
    maze_solver.cpp

    Code for the maze_solver class.  This class will use stack-based depth
    first search or queue-based breadth first search to find a solution (if
    possible) to a simple maze.

*/

#include "maze_solver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


// initialize()
// Find the start and goal points.  Push or enqueue the start point.  Set
// the boolean no_more_steps and goal_reached flags to false.
void maze_solver::initialize() {
    no_more_steps = false;
    goal_reached = false;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if(maze.at(i)[j]=='o'){
                starting.first=i;
                starting.second=j;
                s.push(starting);
                q.push(starting);
            }if(maze.at(i)[j]=='*'){
                finish.first = i;
                finish.second = j;
            }
        }
    }

}

// write_maze()
// Output the (partially or totally solved) maze on the provided output stream.
void maze_solver::write_maze(ostream& out) {
    // TODO: write this method
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            out << maze.at(i)[j];
        } out << endl;
    }
}

// step()
// Take one step towards solving the maze, setting no_more_steps and
// goal_reached as appropriate.  This implements the essential maze search
// algorithm; take the next location from your stack or queue, mark the
// location with '@', add all reachable next points to your stack or queue,
// etc.

void maze_solver::step() {
    // TODO: write this method
    if (s.empty()||q.empty()){
        no_more_steps = true;
        return;
    }
    pair<int,int>temp_s = s.top();
    if (use_stack) {
        //up
        update_map_s({temp_s.first + 1, temp_s.second});
        if (s.top()==temp_s){
            //right
            update_map_s({temp_s.first, temp_s.second + 1});
            if(s.top() == temp_s){
                //down
                update_map_s({temp_s.first - 1, temp_s.second});
                if(s.top() == temp_s){
                    //left
                    update_map_s({temp_s.first, temp_s.second-1});
                    if(s.top()==temp_s){
                        s.pop();
}}}}}
    pair<int,int> q_temp = q.front();
    if(!use_stack) {
            //up
            update_map_q({q_temp.first + 1, q_temp.second});
            //right
            update_map_q({q_temp.first, q_temp.second + 1});
            //down
            update_map_q({q_temp.first - 1, q_temp.second});
            //left
            update_map_q({q_temp.first, q_temp.second - 1});
            q.pop();
    }
}

// TODO: add helper methods as needed
void maze_solver::update_map_s(pair<int,int> tem) {
    char pos;
    if((tem.first<0 || tem.first>rows-1)||(tem.second<0 ||tem.second>columns-1)){
        pos=' ';
    }else{
        pos = maze.at(tem.first)[tem.second];
    }
    switch (pos) {
        case '.'://keep in stack/queue
            s.push(tem);
            maze.at(tem.first)[tem.second] = '@';
            break;
        case '*':
            s.push(tem);
            goal_reached = true;
            no_more_steps = true;
            break;
        default:
            break;
    }
}
void maze_solver::update_map_q(pair<int,int> temp){
    char pos;
    if((temp.first<0 || temp.first>rows-1)||(temp.second<0 ||temp.second>columns-1)){
        pos=' ';
    }else{
        pos = maze.at(temp.first)[temp.second];
    switch (pos) {
        case '.'://in stack/queue
            q.push(temp);
            maze.at(temp.first)[temp.second] = '@';
            break;
        case '*':
            goal_reached = true;
            no_more_steps = true;
            q.empty();
            break;
        default:
            break;
    }
}}

// Here's the constructor code
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
    use_stack = use_stak;
    do_pause = pause;

    // parse out maze name for later use in creating output file name
    int pos = infile.find(".");
    if (pos == string::npos) {
        maze_name = infile;
    } else {
        maze_name = infile.substr(0, pos);
    }

    // open input file and read in maze
    ifstream fin(infile);
    if (!fin) {
        cerr << "Error opening input file \"" << infile << "\"; exiting." << endl;
        exit(1);
    }

    fin >> rows >> columns;

    string row;
    getline(fin, row);
    for (int i = 0; i < rows; i++) {
        getline(fin, row);
        maze.push_back(row); //old stanford library call .add(row);
    }

    fin.close();
}

// run()
// Drives the solution forward.
// While more steps are possible (while no_more_steps == false), run repeatedly
// calls step(), then write_maze() on cout, then pause().  Once there are no
// more steps, it prints a success/failure message to the user (based on the
// goal_reached flag) and writes the final maze to a solution file.
void maze_solver::run() {
    cout << "Solving maze '" << maze_name << "'." << endl;
    cout << "Initial maze: " << endl << endl;
    write_maze(cout);
    cout << endl;
    pause();

    // main loop
    while (!no_more_steps) {
        step();
        cout << endl;
        write_maze(cout);
        cout << endl;
        pause();
    }


    // final output to user
    cout << "Finished: ";
    if (goal_reached) {
        cout << "goal reached!" << endl;
    } else {
        cout << "no solution possible!" << endl;
    }

    // save solution file
    string outfile;
    if (use_stack) outfile = maze_name + "-stack-solution.txt";
    else outfile = maze_name + "-queue-solution.txt";

    ofstream fout(outfile);
    if (!fout) {
        cerr << "Could not open file \"" << outfile << "\" for writing." << endl;
        cerr << "Solution file could not be saved!" << endl;
    }
    else {
        write_maze(fout);
        fout.close();
    }
}

void maze_solver::pause() {
    if (!do_pause) return;
    string foo;
    cout << "Hit Enter to continue...";
    getline(cin, foo);
}