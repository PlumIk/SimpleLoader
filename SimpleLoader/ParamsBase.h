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
	/// Флаг, изменилось ли что-то.
	/// </summary>
	bool _someChange =false;

	/// <summary>
	/// Словарь имя-инт.
	/// </summary>
	std::map <std::string, int> _nameInt;

	/// <summary>
	/// Словарь имя-дабл.
	/// </summary>
	std::map <std::string, double> _nameDouble;

	/// <summary>
	/// Словарь имя-строка.
	/// </summary>
	std::map <std::string, std::string> _nameString;

	/// <summary>
	/// Словарь имя-массив инт.
	/// </summary>
	std::map <std::string, std::vector<int>> _nameIntMas;

	/// <summary>
	/// Словарь имя-массив дабл.
	/// </summary>
	std::map <std::string, std::vector<double>> _nameDoubleMas;

	/// <summary>
	/// Словарь имя-массив строк.
	/// </summary>
	std::map <std::string, std::vector<std::string>> _nameStringMas;


	void Reload();

public:


	vector<string> Changed();

	/// <summary>
	/// Функция для эксперементов.
	/// </summary>
	void DoSome();

	void Update();

	map <string, bool> isChanged;

	ParamsBase(string FilePath);

	bool GetIsChange();

	/// <summary>
	/// Возвращает записанный инт.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	int GetInt(std::string name);

	/// <summary>
	/// Возвращает записанный дабл.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	double GetDouble(std::string name);

	/// <summary>
	/// Возвращает записанный стринг.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::string GetString(std::string name);

	/// <summary>
	/// Возвращает записанный массив инт.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::vector<int> GetIntMas(std::string name);

	/// <summary>
	/// Возвращает записанный массив дабл.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::vector<double> GetDoubleMas(std::string name);

	/// <summary>
	/// Возвращает записанный мфссив стринг.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::vector<std::string> GetStringMas(std::string name);

	/// <summary>
	/// Определяет тип параметра.
	/// </summary>
	/// <param name="name">Имя</param>
	/// <returns>тип</returns>
	int  GetType(std::string name);
};

