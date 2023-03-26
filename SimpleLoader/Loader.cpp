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
					NameInt.insert(make_pair(name, valValue.GetInt()));
				}
				else if (valType == _types.DOUBLE_TYPE) {
					NameDouble.insert(make_pair(name, valValue.GetDouble()));
				}
				else if (valType == _types.STRING_TYPE) {
					NameString.insert(make_pair(name, valValue.GetString()));
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
		NameIntMas.insert(make_pair(name, values));
	}
	else if (type == _types.DOUBLE_MAS) {
		vector<double> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back(a[i].GetDouble());
		}
		NameDoubleMas.insert(make_pair(name, values));
	}
	else if (type == _types.STRING_MAS) {
		vector<string> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back(a[i].GetString());
		}
		NameStringMas.insert(make_pair(name, values));
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
		NameIntMas.insert(make_pair(name, values));
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
		NameDoubleMas.insert(make_pair(name, values));
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
	map <string, int> ::iterator it2 = NameInt.begin();
	for (; it2 != NameInt.end(); it2++) {
		cout << it2->first << ":" << it2->second << endl;
	}
	cout << "Doubles:\n";
	map <string, double> ::iterator it3 = NameDouble.begin();
	for (; it3 != NameDouble.end(); it3++) {
		cout << it3->first << ":" << it3->second << endl;
	}
	cout << "Strings:\n";
	map <string, string> ::iterator it4 = NameString.begin();
	for (; it4 != NameString.end(); it4++) {
		cout << it4->first << ":" << it4->second << endl;
	}
	cout << "Ints[]:\n";
	map <string, vector<int>> ::iterator it5 = NameIntMas.begin();
	for (; it5 != NameIntMas.end(); it5++) {
		cout << it5->first << ": [";
		for (int i = 0; i < NameIntMas[it5->first].size(); i++) {
			cout << (it5->second)[i] << ", ";
		}
		cout << "]\n";
	}
	cout << "Double[]:\n";
	map <string, vector<double>> ::iterator it6 = NameDoubleMas.begin();
	for (; it6 != NameDoubleMas.end(); it6++) {
		cout << it6->first << ": [";
		for (int i = 0; i < NameDoubleMas[it6->first].size(); i++) {
			cout << (it6->second)[i] << ", ";
		}
		cout << "]\n";
	}
	cout << "String[]:\n";
	map <string, vector<string>> ::iterator it7 = NameStringMas.begin();
	for (; it7 != NameStringMas.end(); it7++) {
		cout << it7->first << ": [";
		for (int i = 0; i < NameStringMas[it7->first].size(); i++) {
			cout << (it7->second)[i] << ", ";
		}
		cout << "]\n";
	}
	
}

int Loader::GetInt(std::string name)
{
	return NameInt[name];
}

double Loader::GetDouble(std::string name)
{
	return NameDouble[name];
}

std::string Loader::GetString(std::string name)
{
	return NameString[name];
}

vector<int> Loader::GetIntMas(std::string name)
{
	return NameIntMas[name];
}
vector<double> Loader::GetDoubleMas(std::string name)
{
	return NameDoubleMas[name];
}

vector<string> Loader::GetStringMas(std::string name)
{
	return NameStringMas[name];
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
