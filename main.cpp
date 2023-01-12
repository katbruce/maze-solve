//Kathryn Bruce

#include <iostream>
#include <string>

#include "maze_solver.h"

using namespace std;

int main(int argc, char* argv[]) {
    string infile;
    string s_or_q;
    bool do_pause = true;
    bool use_stack = true;

    if (argc >= 3) {
        infile = argv[1];
        s_or_q = argv[2];
        if (argc == 4 && string(argv[3]) == "false") do_pause = false;
    }
    else {
        cout << "Please enter a maze filename: ";
        getline(cin, infile);
        cout << "Please enter (S) to use a stack, or (Q) to use a queue: ";
        getline(cin, s_or_q);
    }

    if (s_or_q == "Q") use_stack = false;

    maze_solver solver(infile, use_stack, do_pause);
    solver.initialize();
    solver.run();

    return 0;
}