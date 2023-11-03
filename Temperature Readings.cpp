#include "../../std_lib_facilites.h"

struct Reading
{
	int day;
	int hour;
	double temperature;
	char suffix;
};

istream& operator>> (istream& in, Reading& r)
{
	char c1, c2;
	int d, h;
	double t;
	char s;
	in >> c1;
	if (!c1)
		return in;
	if (c1 != '(')
	{
		in.unget();
		in.clear(ios_base::failbit);
		return in;
	}
	in >> d >> h >> t >> s >> c2;
	if (!in)
		return in;
	if (s != 'C' && s != 'c' && s != 'F' && s != 'f')
	{
		in.unget();
		cout << "Wrong temperature suffix." << endl;
		in.clear(ios_base::failbit);
		return in;
	}

	if (c2 != ')')
	{
		in.unget();
		cout << "Wrong Reading terminator." << endl;
		in.clear(ios_base::failbit);
		return in;
	}
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return in;
}

ostream& operator<< (ostream& out, const Reading& r)
{
	out << "(" << r.day << " " << r.hour << " " << r.temperature << " " << r.suffix << ")";
	return out;
}

void sortReadings(vector <Reading>& readings)
{
	double min;
	int minIndex;
	Reading temp;
	for (int i = 0; i < readings.size(); i++)
	{
		min = readings[i].temperature;
		minIndex = i;
		temp = readings[i];
		for (int j = i + 1; j < readings.size(); j++)
		{
			if (readings[j].temperature < min)
			{
				min = readings[j].temperature;
				minIndex = j;
			}
		}
		readings[i] = readings[minIndex];
		readings[minIndex] = temp;
	}

}

int main()
{
	// create a file containing data in the form Reading
	string oname;
	cout << "Enter the name of the output file:";
	cin >> oname;
	if (!cin)
		error("Wrong name!)");
	ofstream outFile{ oname };

	srand(time(0));
	char suff[4] = { 'f','F','c','C' };
	Reading r;
	for (int i = 0; i < 50; i++)
	{
		r.day = 1 + (rand() % 31);
		r.hour = rand() % 24;
		//generate a random floating point number between -200 and 200
		r.temperature = -200 + static_cast<double>(rand() / (static_cast<double>(RAND_MAX) / 400));
		r.suffix = suff[rand() % 4];

		outFile << r << endl;
	}
	outFile.close();

	// read the data generated into a vector
	vector<Reading> data;
	ifstream inFile{ oname };
	if (!inFile)
		error("File cannot be opened!");
	int counter = 1;
	for (Reading r; inFile >> r;)
		data.push_back(r);

	// calculate the mean and median temperatures
	double sum = 0;
	for (int i = 0; i < data.size(); i++)
	{
		// convert from Fahrenheit to Celsius
		if (data[i].suffix == 'F' || data[i].suffix == 'f')
		{
			data[i].temperature = (data[i].temperature - 32.0) * (5.0 / 9.0);
			data[i].suffix = 'c';
		}

		sum += data[i].temperature;
	}
	cout << "The mean temperature is: " << sum / data.size() << endl;


	//sot the vector by temperature values
	double median;
	sortReadings(data);
	if (data.size() % 2 != 0)
		median = data[data.size() / 2].temperature;
	else
		median = (data[(data.size() / 2) - 1].temperature + data[data.size() / 2].temperature) / 2;
	cout << "The median temperature is: " << median << endl;

	return 0;
}