#include "../../std_lib_facilites.h"

int main()
{
	string iname;

	cout << "Enter the name of the first file: ";
	cin >> iname;
	cout << endl;

	ifstream inFile{ iname };
	if (!inFile)
		error("Cannot open input file.");

	inFile.exceptions(inFile.exceptions() | ios_base::badbit);
	char c;
	int nb;
	int sum = 0;
	inFile >> c;
	while (inFile)
	{
		if (isdigit(c))
		{
			inFile.unget();
			inFile >> nb;
			sum += nb;
		}
		inFile >> c;
	}
	cout << "The sum of the numbers present in the file is: " << sum << endl;


	return 0;
}