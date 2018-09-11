#ifndef _LOAD_H_
#define _LOAD_H_
#include <string>
#include <cstdio>
#include <cstdbool>
#include "iimage.h"

using namespace std;

class Loader {
private:
    bool isPNG(FILE *file);

public:
    IImage *loadImage(string filename);
};
#endif /* _LOAD_H_ */
