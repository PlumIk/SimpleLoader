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
	/// Словарь имя-тип.
	/// </summary>
	std::map <std::string , int> _nameType;

	/// <summary>
	/// Парсит массивы из json.
	/// </summary>
	/// <param name="name">Имя переменной.</param>
	/// <param name="type">Тип пееменной.</param>
	/// <param name="val">Запакованное значение.</param>
	void ParseMas(std::string name, int type, Value* val);

public:	


	/// <summary>
	/// Словарь имя-инт.
	/// </summary>
	std::map <std::string, int> NameInt;

	/// <summary>
	/// Словарь имя-дабл.
	/// </summary>
	std::map <std::string, double> NameDouble;

	/// <summary>
	/// Словарь имя-строка.
	/// </summary>
	std::map <std::string, std::string> NameString;

	/// <summary>
	/// Словарь имя-массив инт.
	/// </summary>
	std::map <std::string, std::vector<int>> NameIntMas;

	/// <summary>
	/// Словарь имя-массив дабл.
	/// </summary>
	std::map <std::string, std::vector<double>> NameDoubleMas;

	/// <summary>
	/// Словарь имя-массив строк.
	/// </summary>
	std::map <std::string, std::vector<std::string>> NameStringMas;

	/// <summary>
	/// Конструктор по умолчанию.
	/// </summary>
	MainParamsBase();

	/// <summary>
	/// Конструктор класса.
	/// </summary>
	/// <param name="filePath">Расположения файла.</param>
	MainParamsBase(std::string filePath);

	/// <summary>
	/// Функция для эксперементов.
	/// </summary>
	void DoSome();

	std::vector<std::string> GetNames();

	/// <summary>
	/// Возвращает записанный инт.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	int GetInt(std::string name);

	bool SetInt(std::string name, int value);

	/// <summary>
	/// Возвращает записанный дабл.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	double GetDouble(std::string name);

	bool SetDouble(std::string name, double value);

	/// <summary>
	/// Возвращает записанный стринг.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::string GetString(std::string name);

	bool SetString(std::string name, std::string value);

	/// <summary>
	/// Возвращает записанный массив инт.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::vector<int> GetIntMas(std::string name);

	bool SetIntMas(std::string name, std::vector<int> value);

	/// <summary>
	/// Возвращает записанный массив дабл.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::vector<double> GetDoubleMas(std::string name);

	bool SetDoubleMas(std::string name, std::vector<double> value);

	/// <summary>
	/// Возвращает записанный мфссив стринг.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::vector<std::string> GetStringMas(std::string name);

	bool SetStringMas(std::string name, std::vector<std::string> value);

	/// <summary>
	/// Определяет тип параметра.
	/// </summary>
	/// <param name="name">Имя</param>
	/// <returns>тип</returns>
	int  GetType(std::string name);

	bool CanChange(std::string name);

	bool HaveRestrictions(std::string name);

	bool HavePossible(std::string name);
};

