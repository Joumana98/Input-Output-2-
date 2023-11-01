// Reading a structured file

#include "../../std_lib_facilites.h"

const int not_a_reading = -7777;
const int not_a_month = -1;

const double Min = -200;
const double Max = 200;

struct Reading
{
	int day;
	int hour;
	double temperature;
};

struct Day
{
	vector <double> hours{ vector<double>(24,not_a_reading) };
};

struct Month
{
	vector <Day> days{ 32 }; //waste days[0] to make the code easier
	int month{ not_a_month }; // ientifying member
};

struct Year
{
	vector <Month> months{ 12 };
	int year;
};

//----------------------------------------------------------------------------------------------------------
// define input operator to read each struct

istream& operator>> (istream& in, Reading& r)
{
	// (day hour temperature)
	int d, h;
	double t;
	char c1, c2;
	in >> c1 >> d >> h >> t >> c2;
	if (!in)
		return in;
	if (c1 != '(' || c2 != ')')
	{
		cout << "Bad Reading format" << endl;
		in.clear(ios_base::failbit);
		return in;
	}
	r = Reading{ d,h,t };
	return in;
}

vector<string> monthNames = { "jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec" };
int month_to_int(string m)
{
	for (int i = 0; i < 12; i++)
	{
		if (m == monthNames[i])
			return i;
	}
	return -1;
}

bool is_valid(Reading r)
{
	if (r.day <= 0 || r.day > 31)
		return false;
	if (r.hour < 0 || r.hour>23)
		return false;
	if (r.temperature > Max || r.temperature < Min)
		return false;
	return true;

}


istream& operator>> (istream& in, Month& mm)
{
	// {month jan Readings}
	char c1, c2;
	string marker, m;
	in >> c1;
	if (!in)
		return in;
	if (c1 != '(')
	{
		in.unget();
		in.clear(ios_base::failbit);
		return in;
	}
	in >> marker >> m;
	if (!in)
		return in;
	if (marker != "month")
	{
		in.unget();
		in.clear(ios_base::failbit);
		return in;
	}
	mm.month = month_to_int(m);

	//count duplicates and invalid readings
	int duplicates = 0;
	int invalids = 0;
	Reading r;
	while (in >> r)
	{
		if (is_valid(r))
		{
			if (mm.days[r.day].hours[r.hour] != not_a_reading)
				duplicates++;
			mm.days[r.day].hours[r.hour] = r.temperature;
		}
		else
			invalids++;
	}
	if (duplicates)
		error("Duplicate readings in a month");
	if (invalids)
		error("Invalid readings in a month");
	in >> c2;
	if (!in)
		return in;
	if (c2 != '}')
	{
		in.unget();
		in.clear(ios_base::failbit);
		cout << "Invalid month terminator" << endl;
		return in;
	}
	return in;
}

istream& operator>> (istream& in, Year& y)
{
	char c1, c2;
	string marker;
	int yy;
	in >> c1;
	if (!in)
		return in;
	if (c1 != '(')
	{
		in.unget();
		in.clear(ios_base::failbit);
		return in;
	}
	in >> marker >> yy;
	if (!in)
		return in;
	if (marker != "year")
	{
		in.unget();
		in.clear(ios_base::failbit);
		return in;
	}
	y.year = yy;

	while (true)
	{
		Month mm; // need to define a new struct in every iteration
		in >> mm;
		if (!in)
			break;
		y.months[mm.month] = mm;
	}

}


int main()
{

	cout << "Enter the name of the file." << endl;
	string iname;
	cin >> iname;
	ifstream inFile{ iname };
	if (!inFile)
		error("Cannot open the file.");

	inFile.exceptions(inFile.exceptions() | ios_base::badbit);

	vector<Year> years;
	while (true)
	{
		Year y;
		inFile >> y;
		if (!inFile)
			break;
		years.push_back(y);

	}

	return 0;
}