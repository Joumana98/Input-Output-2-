#include "../../std_lib_facilites.h"

struct Point
{
	int x;
	int y;
};

istream& operator>> (istream& in, Point& p)
{
	int xx, yy;
	in >> xx >> yy;
	if (!in)
		return in;
	p.x = xx;
	p.y = yy;
	return in;
}

ostream& operator<< (ostream& out, const Point& p)
{
	out << "(" << p.x << "," << p.y << ")";
	return out;
}

int main()
{
	string iname;
	cout << "Please enter the name of the input file: ";
	cin >> iname;
	ifstream inFile{ iname };
	if (!inFile)
		error("Cannot open input file.");

	vector <Point> points;
	for (Point p; inFile >> p;)
		points.push_back(p);

	string oname;
	cout << endl;
	cout << "Enter the name of the output file: ";
	cin >> oname;
	ofstream outFile{ oname };
	if (!outFile)
		error("Cannot open output file.");
	for (Point p : points)
		outFile << p << endl;



	return 0;
}