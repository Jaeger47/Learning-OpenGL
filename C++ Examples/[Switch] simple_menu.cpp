//Simple Menu
//Coded by Mark Daniel G. Dacer
//https://github.com/Jaeger47/

#include <iostream>
using namespace std;

int main () 
{
	char selection;
	cout<<"\n Menu";
	cout<<"\n========";
	cout<<"\n A - Append";
	cout<<"\n M - Modify";
	cout<<"\n D - Delete";
	cout<<"\n X - Exit";
	cout<<"\n Enter selection: ";

	cin>>selection;

	switch(selection)
	{

		case 'A' :
		case 'a' :{cout<<"\n To append a record\n";}
		break;
		case 'M' :
		case 'm' :{cout<<"\n To modify a record";}
		break;
		case 'D' :
		case 'd' :{cout<<"\n To delete a record";}
		break;
		case 'X' :
		case 'x' :{cout<<"\n To exit the menu";}

		break;

		// other than A, M, D and X...

		default : cout<<"\n Invalid selection";

		// no break in the default case

}

	cout<<"\n";
   cout << "" << endl;
   system("pause");
   return 0;
}
