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

class Loader
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
	Loader();

	/// <summary>
	/// ����������� ������.
	/// </summary>
	/// <param name="filePath">������������ �����.</param>
	Loader(std::string filePath);

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

	/// <summary>
	/// ���������� ���������� ����.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	double GetDouble(std::string name);

	/// <summary>
	/// ���������� ���������� ������.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::string GetString(std::string name);

	/// <summary>
	/// ���������� ���������� ������ ���.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::vector<int> GetIntMas(std::string name);

	/// <summary>
	/// ���������� ���������� ������ ����.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::vector<double> GetDoubleMas(std::string name);

	/// <summary>
	/// ���������� ���������� ������ ������.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::vector<std::string> GetStringMas(std::string name);

	/// <summary>
	/// ���������� ��� ���������.
	/// </summary>
	/// <param name="name">���</param>
	/// <returns>���</returns>
	int  GetType(std::string name);
};

