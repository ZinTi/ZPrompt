#include "frame.h"

// @overloaded
void SafeExit(int _Code){
	ChCP(0, 0);
	exit(_Code);
}