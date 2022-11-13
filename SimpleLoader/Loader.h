#include <string>
#include <iostream>
#include <map>
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
	/// ������� ���-������ �������.
	/// </summary>
	std::map <std::string, int> _nameSizeMas;

	/// <summary>
	/// ������� ���-������ ���.
	/// </summary>
	std::map <std::string, int*> _nameIntMas;

	/// <summary>
	/// ������� ���-������ ����.
	/// </summary>
	std::map <std::string, double*> _nameDoubleMas;

	/// <summary>
	/// ������� ���-������ �����.
	/// </summary>
	std::map <std::string, std::string*> _nameStringMas;


	/// <summary>
	/// ������ ������� �� json.
	/// </summary>
	/// <param name="name">��� ����������.</param>
	/// <param name="type">��� ���������.</param>
	/// <param name="val">������������ ��������.</param>
	void ParseMas(std::string name, int type, Value* val);

public:	

	/// <summary>
	/// ����������� ������.
	/// </summary>
	/// <param name="filePath">������������ �����.</param>
	Loader(std::string filePath);

	/// <summary>
	/// ������� ��� �������������.
	/// </summary>
	void DoSome();

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
	int* GetIntMas(std::string name);

	/// <summary>
	/// ���������� ���������� ������ ����.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	double* GetDoubleMas(std::string name);

	/// <summary>
	/// ���������� ���������� ������ ������.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>���������� ��������.</returns>
	std::string* GetStringMas(std::string name);

	/// <summary>
	/// ���������� ��� ���������.
	/// </summary>
	/// <param name="name">���</param>
	/// <returns>���</returns>
	int  GetType(std::string name);

	/// <summary>
	/// ���������� ����� �������.
	/// </summary>
	/// <param name="name">���.</param>
	/// <returns>�����.</returns>
	int GetMasSize(std::string name);
};

