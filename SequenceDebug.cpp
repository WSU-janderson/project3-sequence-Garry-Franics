/**
 * SequenceDebug.cpp
 * Project 3
 * CS 3100
 *
 * In this file, you will write your tests as you implement Sequence. If you are using CLion, you need to select
 * SequenceDebug from the drop-down menu next to the Build (hammer icon) if it is on SequenceTestHarness
 */

#include <iostream>
#include "Sequence.h"

using namespace std;

int main() {

    Sequence s(3);
    cout << s << endl;
    cout << s[1] << endl;
    s.insert(2, "7");
    cout << s << endl;
    cout << s[1] << endl;
    string front = s.front();
    cout << front << endl;
    string back = s.back();
    cout << back << endl;

    return 0;
}