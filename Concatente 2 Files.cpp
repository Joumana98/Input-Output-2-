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
	char c;
	inFile1.get(c);
	if (!inFile1)
		error("First file is empty!");
	while (inFile1)
	{
		outFile << c;
		inFile1.get(c);
	}

	cout << "First file copied." << endl;

	inFile2.exceptions(inFile2.exceptions() | ios_base::badbit);
	inFile2.get(c);
	if (!inFile2)
		error("Second file is empty!");
	while (inFile2)
	{
		outFile << c;
		inFile2.get(c);
	}

	return 0;
}