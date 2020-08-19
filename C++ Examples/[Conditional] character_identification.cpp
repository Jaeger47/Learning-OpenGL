//Character Identification
//Coded by Mark Daniel G. Dacer
//https://github.com/Jaeger47/
#include <iostream>
using namespace std;

void main()
{
	char ch;
	cout <<	"Enter the character : ";
	cin >> ch;
	if(('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
	{
		cout << "Character " << ch << " is an alphabet" << endl;
	}
	else if('0' <= ch && ch <= '9')
	{
		cout << "Character " << ch << " is a number" << endl;
	}
	else
	{
		cout << "Character " << ch << " is special character" << endl;
	}
	
	system("pause");
}
