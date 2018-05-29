#include <string>
#include <exception>
#include <iostream>
#include "loader.hpp"

using namespace std;

int main() {
    string filename = "left.png";
    try {
        Loader *loader = new Loader(filename);
        delete loader;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
