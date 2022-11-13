#pragma once
#include <string>
#include <iostream>

using namespace std;

class Types
{
public:
	/// <summary>
	/// ���� ����.
	/// </summary>
	const char* TYPE = "type";

	/// <summary>
	/// ���� ��������.
	/// </summary>
	const char* VALUE = "value";

	/// <summary>
	/// ���� �������� ����.
	/// </summary>
	const char* STEP = "step";

	/// <summary>
	/// ��� ���.
	/// </summary>
	const int INT_TYPE = 1;

	/// <summary>
	/// ��� ����.
	/// </summary>
	const int DOUBLE_TYPE = 2;

	/// <summary>
	/// ��� ������.
	/// </summary>
	const int STRING_TYPE = 3;

	/// <summary>
	/// ��� ������ ���.
	/// </summary>
	const int INT_MAS = 4;

	/// <summary>
	/// ��� ������ ����.
	/// </summary>
	const int DOUBLE_MAS = 5;

	/// <summary>
	/// ��� ������ �����.
	/// </summary>
	const int STRING_MAS = 6;

	/// <summary>
	/// ��� ������ ��� � �����.
	/// </summary>
	const int INT_STEP_MAS = 7;

	/// <summary>
	/// ��� ������ ���� � �����.
	/// </summary>
	const int DOUBLE_STEP_MAS = 8;

	/// <summary>
	/// �������� ������������� ����.
	/// </summary>
	const int MAX_TYPE_NUM = 9;
};

