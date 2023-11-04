#include "../../std_lib_facilites.h"

int main()
{
	string iname1, iname2;
	string concatenated;

	cout << "Enter the name of the first file: ";
	cin >> iname1;
	cout << endl;
	cout << "Enter the name of the second file: ";
	cin >> iname2;
	cout << endl;

	ifstream inFile1{ iname1 };
	if (!inFile1)
		error("Cannot open the first file.");

	ifstream inFile2{ iname2 };
	if (!inFile2)
		error("Cannot open the second file.");

	cout << "Enter the name of the output file: ";
	cin >> concatenated;
	cout << endl;

	ofstream outFile{ concatenated };

	inFile1.exceptions(inFile1.exceptions() | ios_base::badbit);
	inFile2.exceptions(inFile1.exceptions() | ios_base::badbit);
	string s1, s2;
	inFile1 >> s1;
	inFile2 >> s2;
	while (inFile1 && inFile2)
	{
		if (s1 <= s2)
			outFile << s1 << " ";
		else
		{
			while (s2 < s1 && inFile2)
			{
				outFile << s2 << " ";
				inFile2 >> s2;
			}
			outFile << s1 << " ";
		}
		inFile1 >> s1;
	}
	while (inFile1)
	{
		outFile << s1 << " ";
		inFile1 >> s1;
	}
	while (inFile2)
	{
		outFile << s2 << " ";
		inFile2 >> s2;
	}



	return 0;
}
