#pragma once
#include "Keywords.h"
#include "MainParamsBase.h"

class IFinder
{
public:

	struct LocalObject
	{
		int type;
		int intValue;
		double doubleValue;
	};

	IFinder(MainParamsBase* params);

	void TryOptimize(vector<string> optimizedParams);

	bool IsEnd(double optimizedValue);

	void selectBestSuggest();

	void selectBestSuggest(vector<string> names);

private:

	IFinder();

protected:

	double _previose = std::numeric_limits<double>::max();

	map<string, LocalObject> bestSuggest;

	Keywords keywords = Keywords();

	MainParamsBase* _params;

	bool isConst(int type);

	void setGlobalBestSuggest(string name);

	void setBestSuggest(string name, LocalObject object);
};

