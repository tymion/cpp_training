#ifndef _LOAD_HPP_
#define _LOAD_HPP_
#include <string>
//#include <cstdio>

using namespace std;

enum PNGChunkType {
    Ancillary = 1,
    Private = 2,
    Reserved = 4,
    SafeToCopy = 8
};

class Loader {
private:
    FILE * file;
    int height;
    int width;
    bool littleEndian;

    bool isPNG();
    PNGChunkType readChunkHeader(int &length);
    PNGChunkType readChunkHeaderD(int &length);
    void readChunk(char &data, const int &length);
    void readCrc();
        
public:
    Loader(string filename);
    void setRegion(int height, int width);
    int getData(char* data, size_t n);

};
#endif /* _LOAD_HPP_ */
