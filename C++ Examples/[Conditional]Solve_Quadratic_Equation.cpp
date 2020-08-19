//Solve Quadratic Equation depending upon the value of Delta
//Coded by Mark Daniel G. Dacer
//https://github.com/Jaeger47/
#include <iostream>
using namespace std;

void main()
{
int a,b,c;
float x1,x2,d;
cout << "Enter the value of a, b and c to calculate delta : ";
cin >> a >> b >> c;
d = b * b - 4 * a * c;
cout << "Delta is : " << d << endl;

if(d==0)
{
	cout << "Since delta is 0. The roots are equal\n";
	x1 = -b/(2*a);
	cout << "The root is : " << x1 << endl;
}
else if(d>0)
{
	cout << "Since delta is positive. The roots are unequal and real\n";
	x1 = ( -b + sqrt(d) )/(2*a);
	x2 = ( -b - sqrt(d) )/(2*a);
	cout << "The roots are : " << x1 <<" and "<< x2 << endl;
}
else
{
	cout << "Since delta is negative. The roots are unequal and imaginary\n";
	cout << "The roots are : ";
	cout << "x1 = ("<<-b<<" + "<<sqrt(-d)<<"i)/"<<(2*a)<<" and ";
	cout << "x2 = ("<<-b<<" - "<<sqrt(-d)<<"i)/"<<(2*a) << endl;
}
	
	system("pause");
}
