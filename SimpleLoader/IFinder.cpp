#include "IFinder.h"

IFinder::IFinder(MainParamsBase* params) {
	this->_params = params;
}

bool IFinder::isConst(int type) {
	return type == keywords.INT_TYPE || type == keywords.DOUBLE_TYPE || type == keywords.STRING_TYPE;
}

void IFinder::setGlobalBestSuggest(string name) {
	map <string, LocalObject> ::iterator it = bestSuggest.find(name);
	if (it != bestSuggest.end()) {
		if (it->second.type == keywords.INT_TYPE) {
			(*_params).SetInt(name, it->second.intValue);
		}else if (it->second.type == keywords.DOUBLE_TYPE) {
			(*_params).SetDouble(name, it->second.doubleValue);
		}
	}
}

void IFinder::setBestSuggest(string name, LocalObject object) {
	bestSuggest[name] = object;
}

void IFinder::selectBestSuggest() {
	for (map <string, LocalObject> ::iterator it = bestSuggest.begin(); it != bestSuggest.end(); it++) {
		setGlobalBestSuggest(it->first);
	}
}

void IFinder::selectBestSuggest(vector<string> names) {
	for (int i = 0; i < names.size(); i++) {
		setGlobalBestSuggest(names[i]);
	}
}