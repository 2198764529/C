#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void character();

// ͳ���ַ�
void character()
{
	char c, fileName[60];
	int count = 0;
	cout << "Please enter the file's name:\n";
	cin.getline(fileName, 60);
	fstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "Could not find the file\n";
		cout << "Program terminating\n";
		exit(EXIT_FAILURE);
	}
	inFile >> c;
	while (!inFile.eof()) {
		if (inFile.good()) {
			count++;
			inFile >> c;
		}
		/*else
		{
			inFile.get();
		}*/
	}
	cout << "The file include " << count << " characters." << endl;
	system("pause");
}

#include <iostream> 
#include <fstream> 
#include <string> 
#include <iterator> 
using namespace std;


int main()
{
	ifstream ifs("input.txt");
	if (ifs.fail())
		return -1;
	string ss;
	ifs.unsetf(ios::skipws);
	
	// ������ݵĲɼ�
	copy(istream_iterator<char>(ifs), istream_iterator<char>(), back_insert_iterator<string>(ss));

	// ��ȥ�����ַ���ȫ���ַ�

	// ���ʵĸ�����˼·���£��Ȳ�֣����жϣ�

	// ������з� �����жϻ��з��ڲ���û�пհ��ַ�


	ifs.close();
	copy(ss.begin(), ss.end(), ostream_iterator<char>(cout, ""));

	return 0;
}