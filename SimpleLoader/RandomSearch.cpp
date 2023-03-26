#include "RandomSearch.h"

RandomSearch::RandomSearch(Loader* params) : IFinder::IFinder(params) {};

void RandomSearch::TryOptimize(vector<string> optimizedParams){
	for (string paramName : optimizedParams) {
		int type = (*_params).GetType(paramName);
		if (IFinder::isConst(type)) {
			if (paramName != "one") {
				if (type == _types.INT_TYPE) {
					(*_params).NameInt[paramName] = Random(1, 8);
				}
				else if (type == _types.DOUBLE_TYPE) {
					(*_params).NameDouble[paramName] = Random(1.0, 8.5);
				}
			}
			else {
				(*_params).NameInt[paramName] = Random(0, (*_params).GetIntMas("three").size());

			}
		}
	}
}

bool RandomSearch::IsEnd(double optimizedValue) {
	if (_previose <= optimizedValue) {
		_trys++;
	}
	else {
		_trys = 0;
		_previose = optimizedValue;
	} 
	return _trys < MAX_TRYS;
}

int RandomSearch::Random(int min, int max) {
	return rand() % (max - min) + min;
}

double RandomSearch::Random(double min, double max) {
	double f = (double)rand() / RAND_MAX;
	return f * (max - min) + min;
}