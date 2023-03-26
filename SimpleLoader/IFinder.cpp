#include "IFinder.h"

IFinder::IFinder(Loader* params) {
	this->_params = params;
}

bool IFinder::isConst(int type) {
	return type == _types.INT_TYPE || type == _types.DOUBLE_TYPE || type == _types.STRING_TYPE;
}