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
// ˵����			�ַ�ͳ����
// 
// ���ԣ�			vFileData
//					ԭʼ��������(����ΪȫASCII�ַ���Ӣ��Сд�ַ���)
//
//					vWordsList
//					�����б�
//
//					vWordsListValue
//					����Ƶ��ͳ��
//
// ����������		StatisticsCharacter(string vFileData)
//					���ƹ��캯������ȡָ���ļ��е�������
//
//					EffectiveRows()
//					��Ч����ͳ��
//
//					EffectiveCharacter()
//					��Ч�ַ�����ͳ��
//
//					EffectiveWordsValue()
//					��Ч��������ͳ��
//
//					EffectiveWordFrequency()
//					����Ƶ��ͳ��
//
// ˽�к�����		EffectiveWords()
//					��Ч����ͳ��
//
//					IsWord()
//					������Ч�ж�
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
// ˵����			�๹�캯�����ڴ˹��캯���У������������ļ��е����ݣ�
//					��ִ�У�ȥ�����еķ�ASCII���Ų��� �� ȫ�ֶ�Сд������
// 
// ����������		oInputFileStream			�ļ�������
//
// ���ݱ�����		vPrimitiveData				ԭʼ����
//					vASCIIData					ȫASCII������
//					vTolowerData				ȫСд����
//					vpTemp						��ʱָ��
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
// ˵����			ͳ���ļ�ASCII�ַ��ĸ���
// ********************************************************************************

int StatisticsCharacter::EffectiveCharacter()
{
	return vFileData.length();
}

// ********************************************************************************
// ˵����			ͳ�Ƶ�������
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
// ˵����			ͳ����Ч����������ʹ�����и�����ķ�ʽ��ͳ�Ʋ������������Ч�ַ���
//					�������������������
// 
// ����������		oStreamFileData				�ļ�������
//
// ���ݱ�����		vRowsList					��Ч�����б�
//					vsTemp						��ʱ�ַ���
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
// ˵����			����ͳ�ƺ���
// 
// ���ݱ�����		vsTemp						��ʱ�ַ���
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
// ˵����			��������λ�ж�
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
// ˵����			����Ƶ��ͳ�ơ�
// 
// ����������		oWordFrequency				map��ֵ��
//
// ���ݱ�����		vWordTop					Ƶ����ߵ�ʮ������
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