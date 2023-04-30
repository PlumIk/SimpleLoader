#pragma once
#include "IFinder.h"
class RandomSearch: IFinder
{
private:

	int _trys = 0;

	const int MAX_TRYS = 5;

	int Random(int min, int max);

	double Random(double min, double max);

	map<string, LocalObject> latestValues;

public:

	void TryOptimize(vector<string> optimizedParams);

	bool IsEnd(double optimizedValue);

	RandomSearch(MainParamsBase* params);

	void selectBestSuggest();

	void selectBestSuggest(vector<string> names);
};

