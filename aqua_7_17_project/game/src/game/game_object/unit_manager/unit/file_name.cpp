#include "file_name.h"
#include <algorithm>

std::string filename::num(int count, bool load)
{
    std::string string = "";

    int num = rand() % std::max(1, count);
    if (load)
        num = count;
    if (num < 10)
        string = "0";
    string += std::to_string(num) + ".png";
    return string;
}
