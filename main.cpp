#include <iostream>
#include <climits>
#include <string>
#include "loader.hpp"

using namespace std;

int main() {
    string filename = "left.png";
    Loader *loader = new Loader(filename);
    loader->setRegion(11, 300);
    /*
    char data[20];
    if (loader->getData(data, 20) != 0) {
        for (int i = 0; i < 20; i++) {
            cout << (size_t) data[i] << endl;
        }
        cout << data <<  endl;
    } else {
        cout << INT_MAX <<  endl;
    }
    */
    return 0;
}
