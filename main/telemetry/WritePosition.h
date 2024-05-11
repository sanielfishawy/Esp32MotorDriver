#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <stdio.h>
#include <stdlib.h>

#include "esp_err.h"

#ifdef __cplusplus

class WritePosition{
    public:
        static void saveWritePos(const char *filename, size_t writePos);
        static size_t loadWritePos(const char *filename);

    private:
        static std::unordered_map<std::string, size_t> _writePositions;
};

#endif // __cplusplus