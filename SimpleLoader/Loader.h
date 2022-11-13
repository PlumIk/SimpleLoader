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
	/// Словарь имя-тип.
	/// </summary>
	std::map <std::string , int> _nameType;

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
	/// Словарь имя-Размер массива.
	/// </summary>
	std::map <std::string, int> _nameSizeMas;

	/// <summary>
	/// Словарь имя-массив инт.
	/// </summary>
	std::map <std::string, int*> _nameIntMas;

	/// <summary>
	/// Словарь имя-массив дабл.
	/// </summary>
	std::map <std::string, double*> _nameDoubleMas;

	/// <summary>
	/// Словарь имя-массив строк.
	/// </summary>
	std::map <std::string, std::string*> _nameStringMas;


	/// <summary>
	/// Парсит массивы из json.
	/// </summary>
	/// <param name="name">Имя переменной.</param>
	/// <param name="type">Тип пееменной.</param>
	/// <param name="val">Запакованное значение.</param>
	void ParseMas(std::string name, int type, Value* val);

public:	

	/// <summary>
	/// Конструктор класса.
	/// </summary>
	/// <param name="filePath">Расположения файла.</param>
	Loader(std::string filePath);

	/// <summary>
	/// Функция для эксперементов.
	/// </summary>
	void DoSome();

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
	int* GetIntMas(std::string name);

	/// <summary>
	/// Возвращает записанный массив дабл.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	double* GetDoubleMas(std::string name);

	/// <summary>
	/// Возвращает записанный мфссив стринг.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Записанное значение.</returns>
	std::string* GetStringMas(std::string name);

	/// <summary>
	/// Определяет тип параметра.
	/// </summary>
	/// <param name="name">Имя</param>
	/// <returns>тип</returns>
	int  GetType(std::string name);

	/// <summary>
	/// Возвращает длину массива.
	/// </summary>
	/// <param name="name">Имя.</param>
	/// <returns>Длина.</returns>
	int GetMasSize(std::string name);
};

