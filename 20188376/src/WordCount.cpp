#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void character();

// 统计字符
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
	
	// 完成数据的采集
	copy(istream_iterator<char>(ifs), istream_iterator<char>(), back_insert_iterator<string>(ss));

	// 除去汉字字符的全部字符

	// 单词的个数（思路如下：先拆分，再判断）

	// 输出换行符 并且判断换行符内部有没有空白字符


	ifs.close();
	copy(ss.begin(), ss.end(), ostream_iterator<char>(cout, ""));

	return 0;
}