// HugeNumberCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HugeNumberLib.h"
#include <iostream>
#include <vector>
#include <string>


int main()
	{
	const long long test_val=std::numeric_limits<int>::max()+(long long)2;
	HugeNumber n(test_val);
	cout <<test_val<< " as base(-2) is " << static_cast<string>(n) << endl;
	n=numeric_limits<long long>::max();
	cout<<"Type long long takes up to "<<n.size()<<" bits to represent for positive numbers and "<<(-n).size()<<" bits for negative numbers."<<endl;
	cout<<"Max long long is "<<static_cast<long long>(n)<<" and in base(-2) looks like\n"<<static_cast<string>(n)<<endl;
	HugeNumber mn=-n;
	cout<<"Negated it looks like "<<static_cast<long long>(mn)<<" :\n"<<static_cast<string>(mn)<<endl;
	HugeNumber a(23);
	HugeNumber b={true, false, true, false, false, true, true};
	string bit_string("1010011");
	HugeNumber d;
	d.FromString(bit_string);
	cout<<"After negation "<<static_cast<string>(n)<<" in decimal = "<<n.ToInt()<<endl;
	cout << "a as base(-2) is " << static_cast<string>(a) << endl;
	cout << "b as base(-2) is " << static_cast<string>(b) << endl;
	cout << "d as base(-2) is " << static_cast<string>(d) << endl;
	cout << "-d as base(-2) is " << static_cast<string>(-d) << endl;
	//HugeNumber left(std::numeric_limits<int>::max());
	HugeNumber left(117);
	HugeNumber right(123);
	auto result=left+right;
	cout<<static_cast<string>(left)<<" + "<<static_cast<string>(right)<<" = "<<static_cast<string>(result)<<endl;
	cout<<left.ToInt()<<" + "<<right.ToInt()<<" = "<<result.ToInt()<<endl;
	if(a<b)
		cout<<a.ToInt()<<" < "<<b.ToInt()<<endl;
	long long ex_a=31605;
	HugeNumber A(ex_a);
	//int ex_b=63646912;
	long long ex_b=23318;
	HugeNumber B(ex_b);
	HugeNumber C(ex_a+ex_b);
	HugeNumber D=A+B;
	HugeNumber E(63583541);
	cout<<static_cast<string>(A)<<endl<<static_cast<string>(B)<<endl<<static_cast<string>(C)<<endl<<static_cast<string>(D)<<endl<<static_cast<string>(E)<<endl;
	ex_a=-30100;
	A=ex_a;
	ex_b=-695106;
	B=ex_b;
	cout<<"Addition test:\n";
	cout<<static_cast<string>(A)<<" ("<<static_cast<long long>(A)<<")"<<endl<<static_cast<string>(B)<<" ("<<static_cast<long long>(B)<<")"<<endl;
	C=A+B;
	D=ex_a+ex_b;
	cout<<static_cast<string>(C)<<" ("<<static_cast<long long>(C)<<")"<<endl<<static_cast<string>(D)<<" ("<<static_cast<long long>(D)<<")"<<endl;
	cout<<"It all adds up to nothing..."<<endl;
	//A=numeric_limits<int>::max();
	A=439571010;
	B=-A;
	//D=-numeric_limits<int>::max();
	D=A-A;
	cout<<static_cast<string>(A)<< " ("<<static_cast<long long>(A)<<")" <<endl<<static_cast<string>(B)<<" ("<<static_cast<long long>(B)<<")"<<endl;
	cout<<static_cast<string>(D)<<"< ("<<static_cast<long long>(D)<<")"<<endl;
	//cout<<endl<<endl<<static_cast<int>(D)<<"<"<<endl;
	ex_a=2147481817;
	A=ex_a;
	ex_b=-880358856;
	B=ex_b;
	cout<<"Subtracting "<<endl;
	cout<<static_cast<string>(A)<<" ("<<static_cast<long long>(A)<<")"<<endl<<static_cast<string>(B)<<" ("<<static_cast<long long>(B)<<")"<<endl;
	C=A-B;
	D=A.ToInt()-B.ToInt();
	cout<<static_cast<string>(C)<<" ("<<static_cast<long long>(C)<<")"<<endl<<static_cast<string>(D)<<" ("<<static_cast<long long>(D)<<")"<<endl;
	getchar();
	return 0;
	}

