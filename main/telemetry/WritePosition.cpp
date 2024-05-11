#include "WritePosition.h"

std::unordered_map<std::string, size_t> WritePosition::_writePositions;

void WritePosition::saveWritePos(const char *filename, size_t writePos){
    _writePositions[filename] = writePos;
}

size_t WritePosition::loadWritePos(const char *filename) {
    if (_writePositions.count(filename) == 0) return -1;
    return _writePositions[filename];
}