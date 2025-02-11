#include "frame.h"

bool isMatch(const char* text, const char* pattern){
    std::regex reg(pattern);
    return regex_match(text, reg);
}