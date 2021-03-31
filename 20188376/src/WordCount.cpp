#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ********************************************************************************
// ˵����			�ַ�ͳ����
// 
// ���ԣ�			vFileData					ԭʼ��������
//												(����ΪȫASCII�ַ���Ӣ��Сд�ַ���)
//
// ������			StatisticsCharacter(string vFileData)
//					���ƹ��캯������ȡָ���ļ��е�������
//
//					EffectiveRows()
//					��Ч����ͳ��
// ********************************************************************************

class StatisticsCharacter
{
private:
	// ���ֻ�������ֲ�ȫСд�����ݴ�
	string vFileData;

public:
	StatisticsCharacter(string vFileData);

public:
	int EffectiveRows();
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
}

// ********************************************************************************
// ˵����			��Ч����ͳ�ơ�����ʹ�����и�����ķ�ʽ��ͳ�Ʋ������������Ч�ַ���
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

int main()
{
	StatisticsCharacter vStatisticsCharacter("input.txt");
	int vEffectiveRows = vStatisticsCharacter.EffectiveRows();
	return 0;
}