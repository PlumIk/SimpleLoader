#include <iostream>
#include "MainParamsBase.h"
#include "Keywords.h"
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
Keywords keywords = Keywords();

MainParamsBase::MainParamsBase(){}

MainParamsBase::MainParamsBase(std::string filePath) {
	ifstream file;
	file.open(filePath);
	if (file.is_open()) {
		IStreamWrapper isw(file);
		Document documentFromFile;
		documentFromFile.ParseStream(isw);
		for (auto& m : documentFromFile.GetObject()) {
			Value& val = m.value;
			if (val.HasMember(keywords.TYPE) && val.HasMember(keywords.VALUE)&&val.MemberCount() == 2) {
				int valType = val.FindMember(keywords.TYPE)->value.GetInt();
				Value& valValue = val.FindMember(keywords.VALUE)->value;
				string name = m.name.GetString();
				_nameType.insert(make_pair(name, valType));
				if (valType == keywords.INT_TYPE) {
					NameInt.insert(make_pair(name, valValue.GetInt()));
				}
				else if (valType == keywords.DOUBLE_TYPE) {
					NameDouble.insert(make_pair(name, valValue.GetDouble()));
				}
				else if (valType == keywords.STRING_TYPE) {
					NameString.insert(make_pair(name, valValue.GetString()));
				}
				else if (valType < keywords.MAX_TYPE_NUM) {
					ParseMas(name, valType, &valValue);
				}
			}
		}
	}
	else {
		cout << "ERROR, WRONG FILE NAME\n";
	}
}

void MainParamsBase::ParseMas(std::string name, int type, Value* valValue) {
	if (type == keywords.INT_MAS) {
		vector<int> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back( a[i].GetInt());
		}
		NameIntMas.insert(make_pair(name, values));
	}
	else if (type == keywords.DOUBLE_MAS) {
		vector<double> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back(a[i].GetDouble());
		}
		NameDoubleMas.insert(make_pair(name, values));
	}
	else if (type == keywords.STRING_MAS) {
		vector<string> values;
		auto a = valValue->GetArray();
		for (int i = 0; i < valValue->Size(); i++) {
			values.push_back(a[i].GetString());
		}
		NameStringMas.insert(make_pair(name, values));
		_nameType.insert(make_pair(name, keywords.STRING_MAS));
	}
	else if (type == keywords.INT_STEP_MAS) {
		auto b = valValue->GetArray();
		vector<int> values;
		for (int j = 0; j < b.Size(); j++) {
			Value stepValue = b[j].GetObject();
			if (stepValue.HasMember(keywords.STEP) && stepValue.HasMember(keywords.VALUE)) {
				Value& subValValue = stepValue.FindMember(keywords.VALUE)->value;
				int step = stepValue.FindMember(keywords.STEP)->value.GetInt();
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
		_nameType.insert(make_pair(name, keywords.INT_MAS));
	}
	else if (type == keywords.DOUBLE_STEP_MAS) {
		auto b = valValue->GetArray();
		vector<double> values;
		for (int j = 0; j < b.Size(); j++) {
			Value stepValue = b[j].GetObject();
			if (stepValue.HasMember(keywords.STEP) && stepValue.HasMember(keywords.VALUE)) {
				Value& subValValue = stepValue.FindMember(keywords.VALUE)->value;
				int step = stepValue.FindMember(keywords.STEP)->value.GetDouble();
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
		_nameType.insert(make_pair(name, keywords.DOUBLE_MAS));
		
	}
}

void MainParamsBase::DoSome() {
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

bool MainParamsBase::CanChange(std::string name) {
	return name.find(keywords.RESTRICTIONS) == std::string::npos;
}

bool MainParamsBase::HaveRestrictions(std::string name) {
	vector<std::string> names = GetNames();
	return std::find(names.begin(), names.end(), name + keywords.RESTRICTIONS) != names.end();
}

int MainParamsBase::GetInt(std::string name)
{
	return NameInt[name];
}

bool MainParamsBase::SetInt(std::string name, int value) {
	if (!MainParamsBase::HaveRestrictions(name)) {
		NameInt[name] = value;
		return true;
	}
	vector<int> restrictions = MainParamsBase::GetIntMas(name + keywords.RESTRICTIONS);
	bool isValid = value >= restrictions[0] && value <= restrictions[1];
	if (isValid) {
		NameInt[name] = value;
		return true;
	}
	return false;
}

double MainParamsBase::GetDouble(std::string name)
{
	return NameDouble[name];
}

bool MainParamsBase::SetDouble(std::string name, double value) {
	if (!MainParamsBase::HaveRestrictions(name)) {
		NameDouble[name] = value;
		return true;
	}
	vector<double> restrictions = GetDoubleMas(name + keywords.RESTRICTIONS);
	bool isValid = value >= restrictions[0] && value <= restrictions[1];
	if (isValid) {
		NameDouble[name] = value;
		return true;
	}
	return false;
}

std::string MainParamsBase::GetString(std::string name)
{
	return NameString[name];
}

bool MainParamsBase::SetString(std::string name, std::string value) {
	NameString[name] = value;
	return true;
}

vector<int> MainParamsBase::GetIntMas(std::string name)
{
	return NameIntMas[name];
}

bool MainParamsBase::SetIntMas(std::string name, std::vector<int> value) {
	if (MainParamsBase::CanChange(name)) {
		NameIntMas[name] = value;
		return true;
	}
	return false;
}

vector<double> MainParamsBase::GetDoubleMas(std::string name)
{
	return NameDoubleMas[name];
}

bool MainParamsBase::SetDoubleMas(std::string name, std::vector<double> value) {
	if (MainParamsBase::CanChange(name)) {
		NameDoubleMas[name] = value;
		return true;
	}
	return false;
}

vector<string> MainParamsBase::GetStringMas(std::string name)
{
	return NameStringMas[name];
}

bool MainParamsBase::SetStringMas(std::string name, vector<std::string> value) {
	NameStringMas[name] = value;
	return true;
}

int MainParamsBase::GetType(std::string name)
{
	return _nameType[name];
}


vector<std::string> MainParamsBase::GetNames() {
	vector<string> forRet;
	for (auto it = _nameType.begin(); it != _nameType.end(); ++it)
	{
		forRet.push_back(it->first);
	}
	return forRet;
}

bool MainParamsBase::HavePossible(std::string name) {
	vector<std::string> names = GetNames();
	return std::find(names.begin(), names.end(), name + keywords.POSSIBLE) != names.end();
}

