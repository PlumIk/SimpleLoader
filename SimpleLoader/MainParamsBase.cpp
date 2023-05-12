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
			if (val.HasMember(keywords.TYPE)) {
				int valType = val.FindMember(keywords.TYPE)->value.GetInt();
				Value& valValue = val.FindMember(keywords.VALUE)->value;
				string name = m.name.GetString();
				_nameType.insert(make_pair(name, valType));
				if (keywords.isNumber(valType)) {
					ParseValue(name, valType, &val);
				}
				else if(val.HasMember(keywords.VALUE) && val.MemberCount() == 2) {
					if (keywords.isString(valType)) {
						NameString.insert(make_pair(name, valValue.GetString()));
					}
					else if (keywords.isValidType(valType)) {
						ParseMas(name, valType, &valValue);
					}
				}
			}
		}
	}
	else {
		throw new exception("ERROR, WRONG FILE NAME");
	}
}

void MainParamsBase::ParseValue(std::string name, int type, Value* valValue) {
	for (auto& curField : valValue->GetObject()) {
		std::string fieldName = curField.name.GetString();
		if (!keywords.isSpecialName(name, fieldName)) {
			if (type == keywords.INT_TYPE) {
				vector<int> values;
				auto a = curField.value.GetArray();
				for (int i = 0; i < curField.value.Size(); i++) {
					values.push_back(a[i].GetInt());
				}
				if (NameIntPosible.find(name) == NameIntPosible.end()) {
					std::map<std::string, std::vector<int>> ins;
					NameIntPosible.insert(make_pair(name, ins));
				}
				NameIntPosible[name].insert(make_pair(fieldName, values));
			}
			else {
				vector<double> values;
				auto a = curField.value.GetArray();
				for (int i = 0; i < curField.value.Size(); i++) {
					values.push_back(a[i].GetDouble());
				}
				if (NameDoublePosible.find(name) == NameDoublePosible.end()) {
					std::map<std::string, std::vector<double>> ins;
					NameDoublePosible.insert(make_pair(name, ins));
				}
				NameDoublePosible[name].insert(make_pair(fieldName, values));
			}
		}
		else if (fieldName.compare(name + keywords.RESTRICTIONS) == 0) {
			if (type == keywords.INT_TYPE) {
				vector<int> values;
				auto a = curField.value.GetArray();
				for (int i = 0; i < curField.value.Size(); i++) {
					values.push_back(a[i].GetInt());
				}
				NameIntRestrictions.insert(make_pair(name, values));
			}
			else {
				vector<double> values;
				auto a = curField.value.GetArray();
				for (int i = 0; i < curField.value.Size(); i++) {
					values.push_back(a[i].GetDouble());
				}
				NameDoubleRestrictions.insert(make_pair(name, values));
			}
		}
		else if (fieldName.compare(keywords.VALUE) == 0) {
			if (type == keywords.INT_TYPE) {
				NameInt.insert(make_pair(name, curField.value.GetInt()));
			}
			else {
				NameDouble.insert(make_pair(name, curField.value.GetDouble()));
			}
		}
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

int MainParamsBase::GetInt(std::string name)
{
	return NameInt[name];
}

bool MainParamsBase::SetInt(std::string name, int value) {
	if (GetIntRestrictions(name).size()==0) {
		NameInt[name] = value;
		return true;
	}
	vector<int> restrictions = GetIntRestrictions(name);
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
	if (GetDoubleRestrictions(name).size() == 0) {
		NameDouble[name] = value;
		return true;
	}
	vector<double> restrictions = GetDoubleRestrictions(name);
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
		NameIntMas[name] = value;
		return true;
}

vector<double> MainParamsBase::GetDoubleMas(std::string name)
{
	return NameDoubleMas[name];
}

bool MainParamsBase::SetDoubleMas(std::string name, std::vector<double> value) {
	NameDoubleMas[name] = value;
		return true;
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

std::vector<int> MainParamsBase::GetIntRestrictions(std::string name) {
	if (NameIntRestrictions.find(name) != NameIntRestrictions.end()) {
		return NameIntRestrictions[name];
	}
	std::vector<int> empty;
	return empty;
}

std::vector<double> MainParamsBase::GetDoubleRestrictions(std::string name) {
	if (NameDoubleRestrictions.find(name) != NameDoubleRestrictions.end()) {
		return NameDoubleRestrictions[name];
	}
	std::vector<double> empty;
	return empty;
}

std::vector<int> MainParamsBase::GetIntPosible(std::string valueName, std::string posibleName) {
	if (NameIntPosible.find(valueName) != NameIntPosible.end() && 
		NameIntPosible[valueName].find(posibleName)!= NameIntPosible[valueName].end()) {
		return NameIntPosible[valueName][posibleName];
	}
	std::vector<int> empty;
	return empty;
}

std::vector<double> MainParamsBase::GetDoublePosible(std::string valueName, std::string posibleName) {
	if (NameDoublePosible.find(valueName) != NameDoublePosible.end() &&
		NameDoublePosible[valueName].find(posibleName) != NameDoublePosible[valueName].end()) {
		return NameDoublePosible[valueName][posibleName];
	}
	std::vector<double> empty;
	return empty;
}

bool MainParamsBase::AddIntVar(std::string name, int value) {
	if (_nameType.find(name) != _nameType.end()) {
		return false;
	}
	NameInt.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddDoubleVar(std::string name, double value) {
	if (_nameType.find(name) != _nameType.end()) {
		return false;
	}
	NameDouble.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddStringVar(std::string name, std::string value) {
	if (_nameType.find(name) != _nameType.end()) {
		return false;
	}
	NameString.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddIntMasVar(std::string name, std::vector<int> value) {
	if (_nameType.find(name) != _nameType.end()) {
		return false;
	}
	NameIntMas.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddDoubleMasVar(std::string name, std::vector<double> value) {
	if (_nameType.find(name) != _nameType.end()) {
		return false;
	}
	NameDoubleMas.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddStringMasVar(std::string name, std::vector <std::string> value) {
	if (_nameType.find(name) != _nameType.end()) {
		return false;
	}
	NameStringMas.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddIntVarRestrictions(std::string name, std::vector<int> value) {
	if (_nameType.find(name) != _nameType.end() || NameIntRestrictions.find(name) != NameIntRestrictions.end() || value.size() != 2) {
		return false;
	}
	NameIntRestrictions.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddDoubleVarRestrictions(std::string name, std::vector<double> value) {
	if (_nameType.find(name) != _nameType.end() || NameDoubleRestrictions.find(name) != NameDoubleRestrictions.end() || value.size() != 2) {
		return false;
	}
	NameDoubleRestrictions.insert(make_pair(name, value));
	return true;
}

bool MainParamsBase::AddIntVarPosible(std::string name, std::string posibleName, std::vector<int> value) {
	if (_nameType.find(name) != _nameType.end() || value.size() < 1) {
		return false;
	}
	else if (NameIntPosible.find(name) != NameIntPosible.end()) {
		if (NameIntPosible[name].find(posibleName) != NameIntPosible[name].end()) {
			return false;
		}
		else
		{
			std::map<std::string, std::vector<int>> ins;
			NameIntPosible.insert(make_pair(name, ins));
		}
	}
	NameIntPosible[name].insert(make_pair(posibleName, value));
	return true;
}

bool MainParamsBase::AddDoubleVarPosible(std::string name, std::string posibleName, std::vector<double> value) {
	if (_nameType.find(name) != _nameType.end() || value.size() < 1) {
		return false;
	}
	else if (NameDoublePosible.find(name) != NameDoublePosible.end()) {
		if (NameDoublePosible[name].find(posibleName) != NameDoublePosible[name].end()) {
			return false;
		}
		else
		{
			std::map<std::string, std::vector<double>> ins;
			NameDoublePosible.insert(make_pair(name, ins));
		}
	}
	NameDoublePosible[name].insert(make_pair(posibleName, value));
	return true;
}

