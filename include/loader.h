#ifndef _LOAD_H_
#define _LOAD_H_
#include <string>
#include <cstdio>
#include <cstdbool>
#include "iimage.h"

using namespace std;

class Loader
{
    private:
        static bool isPNG(FILE *file);

        Loader() {}

    public:
        static IImage *loadImage(string filename);

        Loader(Loader const&) = delete;
        void operator=(Loader const&) = delete;
};
#endif /* _LOAD_H_ */
