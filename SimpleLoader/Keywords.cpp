#include "Keywords.h"

bool Keywords::isNumber(int type) {
	return type == INT_TYPE || type == DOUBLE_TYPE;
}

bool Keywords::isMas(int type) {
	return type == INT_MAS || type == DOUBLE_MAS || type == STRING_MAS;
}
bool Keywords::isString(int type) {
	return type == STRING_TYPE;
}
bool Keywords::isValidType(int type) {
	return type == type > 0 && type < MAX_TYPE_NUM;
}