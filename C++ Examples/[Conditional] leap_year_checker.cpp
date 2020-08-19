//Leap Year Checker
//Coded by Mark Daniel G. Dacer
//https://github.com/Jaeger47/
#include <iostream>
using namespace std;

void main()
{
	int year;
	cout << "Enter a year: ";
	cin >> year;
	if ( ( year%4==0 && year%100!=0 ) || year%400==0 )
		cout << year << " is a leap year.";
	else
		cout << year << " is not a leap year." << endl;

	system("pause");
}
