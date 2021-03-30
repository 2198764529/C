#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ********************************************************************************
// 说明：			字符统计类
// 
// 属性：			vFileData					原始操作数据
//												(数据为全ASCII字符的英文小写字符串)
//
// 操作：			StatisticsCharacter(string vFileData)
//												复制构造函数，获取指定文件中的数据流
// ********************************************************************************

class StatisticsCharacter
{
private:
	// 获得只保留汉字并全小写的数据串
	string vFileData;

public:
	StatisticsCharacter(string vFileData);
};

// ********************************************************************************
// 说明：			类构造函数，在此构造函数中，将初步导入文件中的数据；
//					并执行，去除其中的非ASCII符号操作 和 全字段小写操作。
// 
// 操作变量：		oInputFileStream			文件操作流
//
// 数据变量：		vPrimitiveData				原始数据
//					vASCIIData					全ASCII码数据
//					vTolowerData				全小写数据
//					vpTemp						临时指针
// ********************************************************************************

StatisticsCharacter::StatisticsCharacter(string vFilePath) 
{
	ifstream oInputFileStream(vFilePath);
	if (oInputFileStream.fail())
	{
		cout << "Fail of file!" << endl;
	}
	else
	{
		string vPrimitiveData, vASCIIData;
		oInputFileStream.unsetf(ios::skipws);
		copy(istream_iterator<char>(oInputFileStream), istream_iterator<char>(), back_insert_iterator<string>(vPrimitiveData));

		const char* vpTemp = vPrimitiveData.c_str();
		for (int i = 0; i < vPrimitiveData.length(); i++)
			if (vpTemp[i] - '\0' >= 0 && vpTemp[i] - '\0' <= 127)
				vASCIIData += vpTemp[i];

		std::transform(vASCIIData.begin(), vASCIIData.end(), std::back_inserter(vFileData), std::tolower);
	}
}

int main()
{
	StatisticsCharacter vStatisticsCharacter("input.txt");
	return 0;
}
