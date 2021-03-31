#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// ********************************************************************************
// 说明：			字符统计类
// 
// 属性：			vFileData
//					原始操作数据(数据为全ASCII字符的英文小写字符串)
//
//					vWordsList
//					单词列表
//
//					vWordsListValue
//					单词频率统计
//
// 公共函数：		StatisticsCharacter(string vFileData)
//					复制构造函数，获取指定文件中的数据流
//
//					EffectiveRows()
//					有效行数统计
//
//					EffectiveCharacter()
//					有效字符数量统计
//
//					EffectiveWordsValue()
//					有效单词数量统计
//
//					EffectiveWordFrequency()
//					单词频率统计
//
// 私有函数：		EffectiveWords()
//					有效单词统计
//
//					IsWord()
//					单词有效判断
// ********************************************************************************

class StatisticsCharacter
{
private:
	string vFileData;
	vector<string> vWordsList;
	vector<int> vWordsListValue;

public:
	int EffectiveRows();
	int EffectiveCharacter();
	int EffectiveWordsValue();
	void EffectiveWordFrequency();

private:
	void EffectiveWords();
	bool IsWord(string vTestWord);

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
	EffectiveWords();
}

// ********************************************************************************
// 说明：			统计文件ASCII字符的个数
// ********************************************************************************

int StatisticsCharacter::EffectiveCharacter()
{
	return vFileData.length();
}

// ********************************************************************************
// 说明：			统计单词数量
// ********************************************************************************

int StatisticsCharacter::EffectiveWordsValue()
{
	int vTotal = 0;
	for (int i = 0; i < vWordsListValue.size(); i++)
	{
		vTotal += vWordsListValue[i];
	}
	return vTotal;
}

// ********************************************************************************
// 说明：			统计有效行数。这里使用流切割输入的方式，统计并储存包含了有效字符的
//					行数。并输出其行数。
// 
// 操作变量：		oStreamFileData				文件操作流
//
// 数据变量：		vRowsList					有效行数列表
//					vsTemp						临时字符串
// ********************************************************************************

int StatisticsCharacter::EffectiveRows()
{
	vector<string> vRowsList;
	stringstream oStreamFileData(vFileData);
	string vsTemp;

	while (getline(oStreamFileData, vsTemp, '\n'))
	{
		if (vsTemp != "")
			vRowsList.push_back(vsTemp);
	}

	return vRowsList.size();
}

// ********************************************************************************
// 说明：			单词统计函数
// 
// 数据变量：		vsTemp						临时字符串
// ********************************************************************************

void StatisticsCharacter::EffectiveWords()
{
	string vsTemp = "";

	for (int i = 0; i <= vFileData.length(); i++)
	{
		if (vFileData[i] >= 'a' && vFileData[i] <= 'z')
			vsTemp += vFileData[i];
		else
		{
			if (vFileData[i] >= '0' && vFileData[i] <= '9')
				vsTemp += vFileData[i];
			else
			{
				if (vsTemp.size() >= 4 && IsWord(vsTemp))
				{
					int flag = 0;
					for (int j = 0; j < vWordsList.size(); j++)
					{
						if (vsTemp == vWordsList[j])
						{
							vWordsListValue[j]++;
							flag = 1;
							break;
						}
					}

					if (flag == 0)
					{
						vWordsList.push_back(vsTemp);
						vWordsListValue.push_back(1);
					}
					flag = 0;
				}
				vsTemp = "";
			}
		}
	}
}

// ********************************************************************************
// 说明：			单词首四位判断
// ********************************************************************************

bool StatisticsCharacter::IsWord(string vTestWord)
{
	for (int i = 0; i < 4; i++)
	{
		if (vTestWord[i] >= '0' && vTestWord[i] <= '9')
			return false;
	}
	return true;
}

typedef pair<string, int> PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	return lhs.second > rhs.second;
}

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};

// ********************************************************************************
// 说明：			单词频率统计。
// 
// 操作变量：		oWordFrequency				map键值对
//
// 数据变量：		vWordTop					频率最高的十个单词
// ********************************************************************************

void StatisticsCharacter::EffectiveWordFrequency()
{
	map<string, int> oWordFrequency;

	for (int i = 0; i < vWordsList.size(); i++)
		oWordFrequency.insert(pair<string, int>(vWordsList[i], vWordsListValue[i]));

	vector<PAIR> vWordTop(oWordFrequency.begin(), oWordFrequency.end());
	sort(vWordTop.begin(), vWordTop.end(), CmpByValue());
	for (int i = 0; vWordTop.size() < 10 ? i != vWordTop.size() : i != 10; ++i) {
		cout << vWordTop[i].first << ": " << vWordTop[i].second << endl;
	}
}

int main()
{
	StatisticsCharacter vStatisticsCharacter("input.txt");

	cout << "characters: " << vStatisticsCharacter.EffectiveCharacter() << endl;
	cout << "words: " << vStatisticsCharacter.EffectiveWordsValue() << endl;
	cout << "lines: " << vStatisticsCharacter.EffectiveRows() << endl;
	vStatisticsCharacter.EffectiveWordFrequency();

	return 0;
}