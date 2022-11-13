#pragma once
#include <string>
#include <iostream>

using namespace std;

class Types
{
public:
	/// <summary>
	/// Ключ типа.
	/// </summary>
	const char* TYPE = "type";

	/// <summary>
	/// Ключ значения.
	/// </summary>
	const char* VALUE = "value";

	/// <summary>
	/// Ключ значения шага.
	/// </summary>
	const char* STEP = "step";

	/// <summary>
	/// Тип инт.
	/// </summary>
	const int INT_TYPE = 1;

	/// <summary>
	/// Тип дабл.
	/// </summary>
	const int DOUBLE_TYPE = 2;

	/// <summary>
	/// Тип строка.
	/// </summary>
	const int STRING_TYPE = 3;

	/// <summary>
	/// Тип массив инт.
	/// </summary>
	const int INT_MAS = 4;

	/// <summary>
	/// Тип массив дабл.
	/// </summary>
	const int DOUBLE_MAS = 5;

	/// <summary>
	/// Тип массив строк.
	/// </summary>
	const int STRING_MAS = 6;

	/// <summary>
	/// Тип массив инт с шагом.
	/// </summary>
	const int INT_STEP_MAS = 7;

	/// <summary>
	/// Тип массив дабл с шагом.
	/// </summary>
	const int DOUBLE_STEP_MAS = 8;

	/// <summary>
	/// Значения максимального типа.
	/// </summary>
	const int MAX_TYPE_NUM = 9;
};

