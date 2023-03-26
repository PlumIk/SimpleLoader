#include "ParamsBase.h"
#include <string>
#include <iostream>
#include <map>
#include "Loader.h"
#include <vector>

using namespace std;

/// <summary>
/// Класс с парсингом джейсона.
/// </summary>
Loader* _loaderZ;

ParamsBase::ParamsBase() {}

ParamsBase::ParamsBase(Loader* loader) {
	_loaderZ = loader;
	vector<string> names = (*loader).GetNames();
	for (int i = 0; i < names.size(); i++) {
		isChanged.insert(make_pair(names[i], false));
	}
	Reload();
}
void ParamsBase::Reload() {
	Loader _loader = *_loaderZ;
	map <string, int> ::iterator it2 = _loader.NameInt.begin();
	for (; it2 != _loader.NameInt.end(); it2++) {
		_nameInt[it2->first]= it2->second;
	}
	map <string, double> ::iterator it3 = _loader.NameDouble.begin();
	for (; it3 != _loader.NameDouble.end(); it3++) {
		_nameDouble[it3->first] = it3->second;
	}
	map <string, string> ::iterator it4 = _loader.NameString.begin();
	for (; it4 != _loader.NameString.end(); it4++) {
		_nameString[it4->first] = it4->second;
	}
	map <string, vector<int>> ::iterator it5 = _loader.NameIntMas.begin();
	for (; it5 != _loader.NameIntMas.end(); it5++) {
		vector<int> vec;
		for (int i = 0; i < _loader.NameIntMas[it5->first].size(); i++) {
			vec.push_back((it5->second)[i]);
		}
		_nameIntMas[it5->first] = vec;
	}
	map <string, vector<double>> ::iterator it6 = _loader.NameDoubleMas.begin();
	for (; it6 != _loader.NameDoubleMas.end(); it6++) {
		vector<double> vec;
		for (int i = 0; i < _loader.NameDoubleMas[it6->first].size(); i++) {
			vec.push_back((it6->second)[i]);
		}
		_nameDoubleMas[it6->first] = vec;
	}
	map <string, vector<string>> ::iterator it7 = _loader.NameStringMas.begin();
	for (; it7 != _loader.NameStringMas.end(); it7++) {
		vector<string> vec;
		for (int i = 0; i < _loader.NameStringMas[it7->first].size(); i++) {
			vec.push_back((it7->second)[i]);
		}
		_nameStringMas[it6->first] = vec;
	}
}

bool ParamsBase::GetIsChange() {
	if (_someChange) {
		_someChange = false;
		return true;
	}
	return false;
}


vector<string> ParamsBase::Changed() {
	vector<string> vec;
	map<string, bool>::iterator it = isChanged.begin();
	for (; it != isChanged.end(); it++) {
		if (it->second) {
			vec.push_back(it->first);
		}
	}
	return vec;
}

void ParamsBase::DoSome() {
	(*_loaderZ).NameInt["n"] = rand() % 4 + 1;
	
}

void ParamsBase::Update() {
	Loader loader = *_loaderZ;
	map <string, int> ::iterator it2 = loader.NameInt.begin();
	for (; it2 != loader.NameInt.end(); it2++) {
		if (_nameInt[it2->first] != it2->second) {
			_someChange = true;
			isChanged[it2->first] = true;
		}
	}
	map <string, double> ::iterator it3 = loader.NameDouble.begin();
	for (; it3 != loader.NameDouble.end(); it3++) {
		if (_nameDouble[it3->first] != it3->second) {
			_someChange = true;
			isChanged[it3->first] = true;
		}
	}
	map <string, string> ::iterator it4 = loader.NameString.begin();
	for (; it4 != loader.NameString.end(); it4++) {
		if (_nameString[it4->first] != it4->second) {
			_someChange = true;
			isChanged[it4->first] = true;
		}
	}
	map <string, vector<int>> ::iterator it5 = loader.NameIntMas.begin();
	for (; it5 != loader.NameIntMas.end(); it5++) {
		if (_nameIntMas[it5->first].size() != it5->second.size()) {
			_someChange = true;
			isChanged[it5->first] = true;
		}
		else {
			for (int i = 0; i < loader.NameIntMas[it5->first].size(); i++) {
				if (_nameIntMas[it5->first][i] != (it5->second)[i]) {
					_someChange = true;
					isChanged[it5->first] = true;
				}
			}
		}
	}
	map <string, vector<double>> ::iterator it6 = loader.NameDoubleMas.begin();
	for (; it6 != loader.NameDoubleMas.end(); it6++) {
		if (_nameDoubleMas[it6->first].size() != it6->second.size()) {
			_someChange = true;
			isChanged[it6->first] = true;
		}
		else {
			for (int i = 0; i < loader.NameDoubleMas[it6->first].size(); i++) {
				if (_nameDoubleMas[it6->first][i] != (it6->second)[i]) {
					_someChange = true;
					isChanged[it6->first] = true;
				}
			}
		}
	}
	map <string, vector<string>> ::iterator it7 = loader.NameStringMas.begin();
	for (; it7 != loader.NameStringMas.end(); it7++) {
		if (_nameStringMas[it7->first].size() != it7->second.size()) {
			_someChange = true;
			isChanged[it7->first] = true;
		}
		else {
			for (int i = 0; i < loader.NameStringMas[it7->first].size(); i++) {
				if (_nameStringMas[it7->first][i] != (it7->second)[i]) {
					_someChange = true;
					isChanged[it7->first] = true;
				}
			}
		}
	}
	if (_someChange) {
		Reload();
	}
}

int ParamsBase::GetInt(std::string name)
{
	return _nameInt[name];
}

double ParamsBase::GetDouble(std::string name)
{
	return _nameDouble[name];
}

std::string ParamsBase::GetString(std::string name)
{
	return _nameString[name];
}

vector<int> ParamsBase::GetIntMas(std::string name)
{
	return _nameIntMas[name];
}
vector<double> ParamsBase::GetDoubleMas(std::string name)
{
	return _nameDoubleMas[name];
}

vector<string> ParamsBase::GetStringMas(std::string name)
{
	return _nameStringMas[name];
}

