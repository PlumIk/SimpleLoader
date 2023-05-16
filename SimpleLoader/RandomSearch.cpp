#include "RandomSearch.h"

RandomSearch::RandomSearch(MainParamsBase* params) : IFinder::IFinder(params) {};

void RandomSearch::TryOptimize(vector<string> optimizedParams){
	map<string, LocalObject> currentMap;
	for (string paramName : optimizedParams) {
		int type = (*_params).GetType(paramName);
		LocalObject obj;
		obj.type = type;
		if (IFinder::isConst(type)) {
			if ((*_params).GetIntPosible(paramName, "value1").size()==0) {
				if (type == keywords.INT_TYPE) {
					obj.intValue = Random(1, 8);
					(*_params).SetInt(paramName, obj.intValue);
				}
				else if (type == keywords.DOUBLE_TYPE) {
					obj.doubleValue = Random(1.0, 8.5);
					(*_params).SetDouble(paramName, obj.doubleValue);
				}
			}
			else {
				if (type == keywords.INT_TYPE) {
					vector<int> pos= (*_params).GetIntPosible(paramName, "value1");
					obj.intValue = pos[Random(0, pos.size())];
					(*_params).SetInt(paramName, obj.intValue);
				}
				else if (type == keywords.DOUBLE_TYPE) {
					vector<double> pos = (*_params).GetDoublePosible(paramName, "value1");
					obj.intValue = pos[Random(0.0, pos.size())];
					(*_params).SetDouble(paramName, obj.doubleValue);
				}
			}
			currentMap[paramName] = obj;
		}
	}
	latestValues = currentMap;
}

bool RandomSearch::IsEnd(double optimizedValue) {
	if (previose <= optimizedValue) {
		_trys++;
	}
	else {
		_trys = 0;
		previose = optimizedValue;
		for (map<string, LocalObject>::iterator it = latestValues.begin(); it != latestValues.end(); it++) {
			setBestSuggest(it->first, it->second);
		}
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

void RandomSearch::selectBestSuggest() {
	__super::selectBestSuggest();
}

void RandomSearch::selectBestSuggest(vector<string> names) {
	__super::selectBestSuggest(names);
}