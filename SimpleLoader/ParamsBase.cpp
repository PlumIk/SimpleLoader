#include "ParamsBase.h"
#include <string>
#include <iostream>
#include <map>
#include "MainParamsBase.h"
#include <vector>

using namespace std;

/// <summary>
/// Класс с парсингом джейсона.
/// </summary>
MainParamsBase* params;

ParamsBase::ParamsBase() {}

ParamsBase::ParamsBase(MainParamsBase* paramsIn) {
	params = paramsIn;
	vector<string> names = (*paramsIn).GetNames();
	for (int i = 0; i < names.size(); i++) {
		isChanged.insert(make_pair(names[i], false));
	}
	Reload();
}
void ParamsBase::Reload() {
	MainParamsBase param = *params;
	map <string, int> ::iterator it2 = param.NameInt.begin();
	for (; it2 != param.NameInt.end(); it2++) {
		nameInt[it2->first]= it2->second;
	}
	map <string, double> ::iterator it3 = param.NameDouble.begin();
	for (; it3 != param.NameDouble.end(); it3++) {
		nameDouble[it3->first] = it3->second;
	}
	map <string, string> ::iterator it4 = param.NameString.begin();
	for (; it4 != param.NameString.end(); it4++) {
		nameString[it4->first] = it4->second;
	}
	map <string, vector<int>> ::iterator it5 = param.NameIntMas.begin();
	for (; it5 != param.NameIntMas.end(); it5++) {
		vector<int> vec;
		for (int i = 0; i < param.NameIntMas[it5->first].size(); i++) {
			vec.push_back((it5->second)[i]);
		}
		nameIntMas[it5->first] = vec;
	}
	map <string, vector<double>> ::iterator it6 = param.NameDoubleMas.begin();
	for (; it6 != param.NameDoubleMas.end(); it6++) {
		vector<double> vec;
		for (int i = 0; i < param.NameDoubleMas[it6->first].size(); i++) {
			vec.push_back((it6->second)[i]);
		}
		nameDoubleMas[it6->first] = vec;
	}
	map <string, vector<string>> ::iterator it7 = param.NameStringMas.begin();
	for (; it7 != param.NameStringMas.end(); it7++) {
		vector<string> vec;
		for (int i = 0; i < param.NameStringMas[it7->first].size(); i++) {
			vec.push_back((it7->second)[i]);
		}
		nameStringMas[it6->first] = vec;
	}
}

bool ParamsBase::GetIsChange() {
	if (someChange) {
		someChange = false;
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
	
}

void ParamsBase::Update() {
	MainParamsBase loader = *params;
	map <string, int> ::iterator it2 = loader.NameInt.begin();
	for (; it2 != loader.NameInt.end(); it2++) {
		if (nameInt[it2->first] != it2->second) {
			someChange = true;
			isChanged[it2->first] = true;
		}
	}
	map <string, double> ::iterator it3 = loader.NameDouble.begin();
	for (; it3 != loader.NameDouble.end(); it3++) {
		if (nameDouble[it3->first] != it3->second) {
			someChange = true;
			isChanged[it3->first] = true;
		}
	}
	map <string, string> ::iterator it4 = loader.NameString.begin();
	for (; it4 != loader.NameString.end(); it4++) {
		if (nameString[it4->first] != it4->second) {
			someChange = true;
			isChanged[it4->first] = true;
		}
	}
	map <string, vector<int>> ::iterator it5 = loader.NameIntMas.begin();
	for (; it5 != loader.NameIntMas.end(); it5++) {
		if (nameIntMas[it5->first].size() != it5->second.size()) {
			someChange = true;
			isChanged[it5->first] = true;
		}
		else {
			for (int i = 0; i < loader.NameIntMas[it5->first].size(); i++) {
				if (nameIntMas[it5->first][i] != (it5->second)[i]) {
					someChange = true;
					isChanged[it5->first] = true;
				}
			}
		}
	}
	map <string, vector<double>> ::iterator it6 = loader.NameDoubleMas.begin();
	for (; it6 != loader.NameDoubleMas.end(); it6++) {
		if (nameDoubleMas[it6->first].size() != it6->second.size()) {
			someChange = true;
			isChanged[it6->first] = true;
		}
		else {
			for (int i = 0; i < loader.NameDoubleMas[it6->first].size(); i++) {
				if (nameDoubleMas[it6->first][i] != (it6->second)[i]) {
					someChange = true;
					isChanged[it6->first] = true;
				}
			}
		}
	}
	map <string, vector<string>> ::iterator it7 = loader.NameStringMas.begin();
	for (; it7 != loader.NameStringMas.end(); it7++) {
		if (nameStringMas[it7->first].size() != it7->second.size()) {
			someChange = true;
			isChanged[it7->first] = true;
		}
		else {
			for (int i = 0; i < loader.NameStringMas[it7->first].size(); i++) {
				if (nameStringMas[it7->first][i] != (it7->second)[i]) {
					someChange = true;
					isChanged[it7->first] = true;
				}
			}
		}
	}
	if (someChange) {
		Reload();
	}
}

int ParamsBase::GetInt(std::string name)
{
	return nameInt[name];
}

double ParamsBase::GetDouble(std::string name)
{
	return nameDouble[name];
}

std::string ParamsBase::GetString(std::string name)
{
	return nameString[name];
}

vector<int> ParamsBase::GetIntMas(std::string name)
{
	return nameIntMas[name];
}
vector<double> ParamsBase::GetDoubleMas(std::string name)
{
	return nameDoubleMas[name];
}

vector<string> ParamsBase::GetStringMas(std::string name)
{
	return nameStringMas[name];
}

