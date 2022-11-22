#include <iostream>
#include "Loader.h"
#include "Types.h"
#include <string>
#include <fstream>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

/// <summary>
///  Константные типы(вместо enum).
/// </summary>
Types _types = Types();

Loader::Loader(){}

Loader::Loader(std::string filePath) {
	ifstream file;
	file.open(filePath);
	if (file.is_open()) {
		IStreamWrapper isw(file);
		Document documentFromFile;
		documentFromFile.ParseStream(isw);
		for (auto& m : documentFromFile.GetObject()) {
			Value& val = m.value;
			if (val.HasMember(_types.TYPE) && val.HasMember(_types.VALUE)&&val.MemberCount() == 2) {
				int valType = val.FindMember(_types.TYPE)->value.GetInt();
				Value& valValue = val.FindMember(_types.VALUE)->value;
				string name = m.name.GetString();
				_nameType.insert(make_pair(name, valType));
				if (valType == _types.INT_TYPE) {
					_nameInt.insert(make_pair(name, valValue.GetInt()));
				}
				else if (valType == _types.DOUBLE_TYPE) {
					_nameDouble.insert(make_pair(name, valValue.GetDouble()));
				}
				else if (valType == _types.STRING_TYPE) {
					_nameString.insert(make_pair(name, valValue.GetString()));
				}
				else if (valType < _types.MAX_TYPE_NUM) {
					ParseMas(name, valType, &valValue);
				}
			}
		}
	}
	else {
		cout << "ERROR, WRONG FILE NAME\n";
	}
}

void Loader::ParseMas(std::string name, int type, Value* valValue) {
	if (type == _types.INT_MAS) {
		vector<int> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back( a[i].GetInt());
		}
		_nameIntMas.insert(make_pair(name, values));
	}
	else if (type == _types.DOUBLE_MAS) {
		vector<double> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back(a[i].GetDouble());
		}
		_nameDoubleMas.insert(make_pair(name, values));
	}
	else if (type == _types.STRING_MAS) {
		vector<string> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back(a[i].GetString());
		}
		_nameStringMas.insert(make_pair(name, values));
		_nameType.insert(make_pair(name, _types.STRING_MAS));
	}
	else if (type == _types.INT_STEP_MAS) {
		auto b = valValue->GetArray();
		vector<int> values;
		for (int j = 0; j < b.Size(); j++) {
			Value stepValue = b[j].GetObject();
			if (stepValue.HasMember(_types.STEP) && stepValue.HasMember(_types.VALUE)) {
				Value& subValValue = stepValue.FindMember(_types.VALUE)->value;
				int step = stepValue.FindMember(_types.STEP)->value.GetInt();
				int* subMas = (int*)malloc(2 * sizeof(int));
				auto a = subValValue.GetArray();
				for (int i = 0; i < 2; i++) {
					subMas[i] = a[i].GetInt();
				}
				int last = subMas[0];
				values.push_back(last);
				last += step;
				while (last < subMas[1]) {
					values.push_back(last);
					last += step;
				}
				if (last != subMas[1]) {
					last = subMas[1];
					values.push_back(last); 
				}
			}
		}
		_nameIntMas.insert(make_pair(name, values));
		_nameType.insert(make_pair(name, _types.INT_MAS));
	}
	else if (type == _types.DOUBLE_STEP_MAS) {
		auto b = valValue->GetArray();
		vector<double> values;
		for (int j = 0; j < b.Size(); j++) {
			Value stepValue = b[j].GetObject();
			if (stepValue.HasMember(_types.STEP) && stepValue.HasMember(_types.VALUE)) {
				Value& subValValue = stepValue.FindMember(_types.VALUE)->value;
				int step = stepValue.FindMember(_types.STEP)->value.GetDouble();
				double* subMas = (double*)malloc(2 * sizeof(double));
				auto a = subValValue.GetArray();
				for (int i = 0; i < 2; i++) {
					subMas[i] = a[i].GetDouble();
				}
				double last = subMas[0];
				values.push_back(last);
				last += step;
				while (last < subMas[1]) {
					values.push_back(last);
					last += step;
				}
				if (last != subMas[1]) {
					last = subMas[1];
					values.push_back(last);
				}
			}
		}
		_nameDoubleMas.insert(make_pair(name, values));
		_nameType.insert(make_pair(name, _types.DOUBLE_MAS));
		
	}
}

void Loader::DoSome() {
	cout << "And what end?"<<endl;
	map <string, int> ::iterator it1 = _nameType.begin();
	for (; it1 != _nameType.end(); it1++) {
		cout  <<  it1->first << ":" << it1->second << endl;
	}
	cout << "Ints:\n";
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
	}
	
}

int Loader::GetInt(std::string name)
{
	return _nameInt[name];
}

double Loader::GetDouble(std::string name)
{
	return _nameDouble[name];
}

std::string Loader::GetString(std::string name)
{
	return _nameString[name];
}

vector<int> Loader::GetIntMas(std::string name)
{
	return _nameIntMas[name];
}
vector<double> Loader::GetDoubleMas(std::string name)
{
	return _nameDoubleMas[name];
}

vector<string> Loader::GetStringMas(std::string name)
{
	return _nameStringMas[name];
}

int Loader::GetType(std::string name)
{
	return _nameType[name];
}


vector<std::string> Loader::GetNames() {
	vector<string> forRet;
	for (auto it = _nameType.begin(); it != _nameType.end(); ++it)
	{
		forRet.push_back(it->first);
	}
	return forRet;
}
