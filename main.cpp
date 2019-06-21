#include <iostream>
#include "virtualFileSystem.h"
#include <sstream>
using namespace std;
int getInput() {
    string input;
    cin >> input;
    for (int i = 0; i < input.size(); i++)
        if (input[i] > '9' || input[i] < '0') {
            cout << "Invalid input\n";
            return getInput();
        }
    int ret;
    stringstream(input)>>ret;
    return ret;
}
int main() {
    while (true) {
        cout << "1- Load\n"
             << "2- new Virtual File System\n";
        int ch;
        ch = getInput();
        if (ch == 1) {
            virtualFileSystem vfs;
            vfs.run();
            break;
        } else if (ch == 2) {
            cout << "please enter disk size\n";
            int size;
            cin >> size;
            virtualFileSystem vfs(size);
            vfs.run();
            break;
        } else {
            cout << "Invalid input\n";
        }
    }
}