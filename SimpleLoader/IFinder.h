#pragma once
#include "Types.h"
#include "Loader.h"
class IFinder
{
private:

	IFinder();

protected:

	double _previose = std::numeric_limits<double>::max();

	Types _types = Types();

	Loader* _params;

	bool isConst(int type);

public:

	IFinder(Loader* params);

	void TryOptimize(vector<string> optimizedParams);

	bool IsEnd(double optimizedValue);

};

