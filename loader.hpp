#ifndef _LOAD_HPP_
#define _LOAD_HPP_
#include <string>
#include <cstdio>
#include <cstdbool>
#include "IImage.hpp"

using namespace std;

class Loader {
private:
    bool isPNG(FILE *file);

public:
    IImage *loadImage(string filename);

};
#endif /* _LOAD_HPP_ */
