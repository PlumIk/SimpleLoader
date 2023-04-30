#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;

class MainParamsBase
{
private:


	/// <summary>
	/// ������� ���-���.
	/// </summary>
	std::map <std::string , int> _nameType;

	/// <summary>
	/// ������ ������� �� json.
	/// </summary>
	/// <param name="name">��� ����������.</param>
	/// <param name="type">��� ���������.</param>
	/// <param name="val">������������ ��������.</param>
	void ParseMas(std::string name, int type, Value* val);

public:	


	/// <summary>
	/// ������� ���-���.
	/// </summary>
	std::map <std::string, int> NameInt;

	/// <summary>
	/// ������� ���-����.
	/// </summary>
	std::map <std::string, double> NameDouble;

	/// <summary>
	/// ������� ���-������.
	/// </summary>
	std::map <std::string, std::string> NameString;

	/// <summary>
	/// ������� ���-������ ���.
	/// </summary>
	std::map <std::string, std::vector<int>> NameIntMas;

	/// <summary>
	/// ������� ���-������ ����.
	/// </summary>
	std::map <std::string, std::vector<double>> NameDoubleMas;

	/// <summary>
	/// ������� ���-������ �����.
	/// </summary>
	std::map <std::string, std::vector<std::string>> NameStringMas;

	/// <summary>
	/// ����������� �� ���������.
	/// </summary>
	MainParamsBase();

	/// <summary>
	/// ����������� ������.
	/// </summary>
	/// <param name="filePath">������������ �����.</param>
	MainParamsBase(std::string filePath);

	/// <summary>
	/// ������� ��� �������������.
	/// </summary>
	void DoSome();

	std::vector<std::string> GetNames();

	/// <summary>
	/// ���������� ���������� ���.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	int GetInt(std::string name);

	bool SetInt(std::string name, int value);

	/// <summary>
	/// ���������� ���������� ����.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	double GetDouble(std::string name);

	bool SetDouble(std::string name, double value);

	/// <summary>
	/// ���������� ���������� ������.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::string GetString(std::string name);

	bool SetString(std::string name, std::string value);

	/// <summary>
	/// ���������� ���������� ������ ���.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::vector<int> GetIntMas(std::string name);

	bool SetIntMas(std::string name, std::vector<int> value);

	/// <summary>
	/// ���������� ���������� ������ ����.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::vector<double> GetDoubleMas(std::string name);

	bool SetDoubleMas(std::string name, std::vector<double> value);

	/// <summary>
	/// ���������� ���������� ������ ������.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::vector<std::string> GetStringMas(std::string name);

	bool SetStringMas(std::string name, std::vector<std::string> value);

	/// <summary>
	/// ���������� ��� ���������.
	/// </summary>
	/// <param name="name">���</param>
	/// <returns>���</returns>
	int  GetType(std::string name);

	bool CanChange(std::string name);

	bool HaveRestrictions(std::string name);

	bool HavePossible(std::string name);
};

