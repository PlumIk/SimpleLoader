#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "MainParamsBase.h"

using namespace std;

class ParamsBase
{
private:

	/// <summary>
	/// ����, ���������� �� ���-��.
	/// </summary>
	bool someChange =false;

	/// <summary>
	/// ������� ���-���.
	/// </summary>
	std::map <std::string, int> nameInt;

	/// <summary>
	/// ������� ���-����.
	/// </summary>
	std::map <std::string, double> nameDouble;

	/// <summary>
	/// ������� ���-������.
	/// </summary>
	std::map <std::string, std::string> nameString;

	/// <summary>
	/// ������� ���-������ ���.
	/// </summary>
	std::map <std::string, std::vector<int>> nameIntMas;

	/// <summary>
	/// ������� ���-������ ����.
	/// </summary>
	std::map <std::string, std::vector<double>> nameDoubleMas;

	/// <summary>
	/// ������� ���-������ �����.
	/// </summary>
	std::map <std::string, std::vector<std::string>> nameStringMas;


	void Reload();

public:


	ParamsBase();

	vector<string> Changed();

	/// <summary>
	/// ������� ��� �������������.
	/// </summary>
	void DoSome();

	void Update();

	map <string, bool> isChanged;

	ParamsBase(MainParamsBase* loader);

	bool GetIsChange();

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
	int GetType(std::string name);
};

