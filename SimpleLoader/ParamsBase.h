#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class ParamsBase
{
private:

	/// <summary>
	/// ����, ���������� �� ���-��.
	/// </summary>
	bool _someChange =false;

	/// <summary>
	/// ������� ���-���.
	/// </summary>
	std::map <std::string, int> _nameInt;

	/// <summary>
	/// ������� ���-����.
	/// </summary>
	std::map <std::string, double> _nameDouble;

	/// <summary>
	/// ������� ���-������.
	/// </summary>
	std::map <std::string, std::string> _nameString;

	/// <summary>
	/// ������� ���-������ ���.
	/// </summary>
	std::map <std::string, std::vector<int>> _nameIntMas;

	/// <summary>
	/// ������� ���-������ ����.
	/// </summary>
	std::map <std::string, std::vector<double>> _nameDoubleMas;

	/// <summary>
	/// ������� ���-������ �����.
	/// </summary>
	std::map <std::string, std::vector<std::string>> _nameStringMas;


	void Reload();

public:


	vector<string> Changed();

	/// <summary>
	/// ������� ��� �������������.
	/// </summary>
	void DoSome();

	void Update();

	map <string, bool> isChanged;

	ParamsBase(string FilePath);

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
	int  GetType(std::string name);
};

