#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;

struct nation
{
	char name[20];
	double land = 0;
	long population = 0;
};

const char* file = "nation.txt";

void writeNation(const char* file);
void readNation(const char* file);

int main()
{
	readNation(file);
	writeNation(file);
	cout.put(10);
	readNation(file);

	cout << "Done!\n";
	system("pause");
	return 0;
}

void writeNation(const char* file)
{
	ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);
	if (!fout.is_open())
	{
		cerr << "Can't open " << file << " file to write!\n";
		exit(1);
	}
	cout << "Country Name(space line to quit): ";
	nation cty;

	while (isalpha(cin.peek()) and (cin.get(cty.name, 20)))
	{

		cout << "Land Area: ";
		while (!(cin >> cty.land))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "=>Incorrect input!\nre-enter:___\b\b\b";
		}
		cout << "Popluation: ";
		while (!(cin >> cty.population))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "=>Incorrect input!\nre-enter:___\b\b\b";
		}
		fout.write((char*)&cty, sizeof cty);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Next Country Name(space line to quit): ";
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	fout.close();
}

void readNation(const char* file)
{
	nation cty;
	ifstream fin(file, ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		cout << setw(20) << left << setfill('=') << "¡ùCountry" << setw(15) << "¡ùLand Area" << setw(15) << "¡ùPopulation" << endl;
		while (fin.read((char*)&cty, sizeof cty))
			cout << setw(20) << right << setfill(' ') << cty.name << setw(15) << cty.land << setw(15) << cty.population << endl;
		cout << setw(51) << setfill('=') << "\n";
	}
	else
	{
		cerr << "Can't open " << file << " file to read!\n";
		cout << "Do you want to create a nation.txt file?[y/n]";
		if (cin.get() == 'y')
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			writeNation(file);
		}
		else
			exit(1);
	}
	fin.close();
}


