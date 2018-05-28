#ifndef _LOAD_HPP_
#define _LOAD_HPP_
#include <string>
#include <cstdio>

using namespace std;

class Loader {
private:
    bool isPNG(FILE *file);

public:
    Loader(string filename);

};
#endif /* _LOAD_HPP_ */
