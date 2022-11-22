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
Loader _loader;


ParamsBase::ParamsBase(string FilePath) {
	_loader = Loader(FilePath);
	vector<string> names = _loader.GetNames();
	for (int i = 0; i < names.size(); i++) {
		isChanged.insert(make_pair(names[i], false));
	}
	Reload();
	
}

void ParamsBase::Reload() {
	map <string, int> ::iterator it2 = _loader._nameInt.begin();
	for (; it2 != _loader._nameInt.end(); it2++) {
		_nameInt[it2->first]= it2->second;
	}
	map <string, double> ::iterator it3 = _loader._nameDouble.begin();
	for (; it3 != _loader._nameDouble.end(); it3++) {
		_nameDouble[it3->first] = it3->second;
	}
	map <string, string> ::iterator it4 = _loader._nameString.begin();
	for (; it4 != _loader._nameString.end(); it4++) {
		_nameString[it4->first] = it4->second;
	}
	map <string, vector<int>> ::iterator it5 = _loader._nameIntMas.begin();
	for (; it5 != _loader._nameIntMas.end(); it5++) {
		vector<int> vec;
		for (int i = 0; i < _loader._nameIntMas[it5->first].size(); i++) {
			vec.push_back((it5->second)[i]);
		}
		_nameIntMas[it5->first] = vec;
	}
	map <string, vector<double>> ::iterator it6 = _loader._nameDoubleMas.begin();
	for (; it6 != _loader._nameDoubleMas.end(); it6++) {
		vector<double> vec;
		for (int i = 0; i < _loader._nameDoubleMas[it6->first].size(); i++) {
			vec.push_back((it6->second)[i]);
		}
		_nameDoubleMas[it6->first] = vec;
	}
	map <string, vector<string>> ::iterator it7 = _loader._nameStringMas.begin();
	for (; it7 != _loader._nameStringMas.end(); it7++) {
		vector<string> vec;
		for (int i = 0; i < _loader._nameStringMas[it7->first].size(); i++) {
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
	/*cout << "Ints:\n";
	map <string, int> ::iterator it2 = _nameInt.begin();
	for (; it2 != _nameInt.end(); it2++) {
		cout << it2->first << ":" << it2->second << endl;
	}
	cout << "Doubles:\n";
	map <string, double> ::iterator it3 = _nameDouble.begin();
	for (; it3 != _nameDouble.end(); it3++) {
		cout << it3->first << ":" << it3->second << endl;
	}
	cout << "Strings:\n";
	map <string, string> ::iterator it4 = _nameString.begin();
	for (; it4 != _nameString.end(); it4++) {
		cout << it4->first << ":" << it4->second << endl;
	}
	cout << "Ints[]:\n";
	map <string, vector<int>> ::iterator it5 = _nameIntMas.begin();
	for (; it5 != _nameIntMas.end(); it5++) {
		cout << it5->first << ": [";
		for (int i = 0; i < _nameIntMas[it5->first].size(); i++) {
			cout << (it5->second)[i] << ", ";
		}
		cout << "]\n";
	}
	cout << "Double[]:\n";
	map <string, vector<double>> ::iterator it6 = _nameDoubleMas.begin();
	for (; it6 != _nameDoubleMas.end(); it6++) {
		cout << it6->first << ": [";
		for (int i = 0; i < _nameDoubleMas[it6->first].size(); i++) {
			cout << (it6->second)[i] << ", ";
		}
		cout << "]\n";
	}
	cout << "String[]:\n";
	map <string, vector<string>> ::iterator it7 = _nameStringMas.begin();
	for (; it7 != _nameStringMas.end(); it7++) {
		cout << it7->first << ": [";
		for (int i = 0; i < _nameStringMas[it7->first].size(); i++) {
			cout << (it7->second)[i] << ", ";
		}
		cout << "]\n";
	}*/
	_loader._nameInt["one"] = _loader._nameInt["one"] + 1;
}

void ParamsBase::Update() {
	map <string, int> ::iterator it2 = _loader._nameInt.begin();
	for (; it2 != _loader._nameInt.end(); it2++) {
		if (_nameInt[it2->first] != it2->second) {
			_someChange = true;
			isChanged[it2->first] = true;
		}
	}
	map <string, double> ::iterator it3 = _loader._nameDouble.begin();
	for (; it3 != _loader._nameDouble.end(); it3++) {
		if (_nameDouble[it3->first] != it3->second) {
			_someChange = true;
			isChanged[it3->first] = true;
		}
	}
	map <string, string> ::iterator it4 = _loader._nameString.begin();
	for (; it4 != _loader._nameString.end(); it4++) {
		if (_nameString[it4->first] != it4->second) {
			_someChange = true;
			isChanged[it4->first] = true;
		}
	}
	map <string, vector<int>> ::iterator it5 = _loader._nameIntMas.begin();
	for (; it5 != _loader._nameIntMas.end(); it5++) {
		if (_nameIntMas[it5->first].size() != it5->second.size()) {
			_someChange = true;
			isChanged[it5->first] = true;
		}
		else {
			for (int i = 0; i < _loader._nameIntMas[it5->first].size(); i++) {
				if (_nameIntMas[it5->first][i] != (it5->second)[i]) {
					_someChange = true;
					isChanged[it5->first] = true;
				}
			}
		}
	}
	map <string, vector<double>> ::iterator it6 = _loader._nameDoubleMas.begin();
	for (; it6 != _loader._nameDoubleMas.end(); it6++) {
		if (_nameDoubleMas[it6->first].size() != it6->second.size()) {
			_someChange = true;
			isChanged[it6->first] = true;
		}
		else {
			for (int i = 0; i < _loader._nameDoubleMas[it6->first].size(); i++) {
				if (_nameDoubleMas[it6->first][i] != (it6->second)[i]) {
					_someChange = true;
					isChanged[it6->first] = true;
				}
			}
		}
	}
	map <string, vector<string>> ::iterator it7 = _loader._nameStringMas.begin();
	for (; it7 != _loader._nameStringMas.end(); it7++) {
		if (_nameStringMas[it7->first].size() != it7->second.size()) {
			_someChange = true;
			isChanged[it7->first] = true;
		}
		else {
			for (int i = 0; i < _loader._nameStringMas[it7->first].size(); i++) {
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

