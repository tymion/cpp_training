#include <string>
#include "loader.hpp"

using namespace std;

int main() {
    string filename = "left.png";
    Loader *loader = new Loader(filename);
    delete loader;
    return 0;
}
