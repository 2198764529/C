#include "StatisticsCharacter.h"

int main(int argc, char* argv[])
{
	StatisticsCharacter vStatisticsCharacter(argv[1]);

	ofstream outFile;
	outFile.open(argv[2], ios::out);

	outFile << "characters: " << vStatisticsCharacter.EffectiveCharacter() << endl;
	outFile << "words: " << vStatisticsCharacter.EffectiveWordsValue() << endl;
	outFile << "lines: " << vStatisticsCharacter.EffectiveRows() << endl;
	vStatisticsCharacter.EffectiveWordFrequency(outFile);

	return 0;
}