#include<iostream>
#include<string>
using namespace std;
void func(string s)
{
	if(!s.empty())
	{
	cout <<s<<endl;
	func(s.substr(1));
    }
}

int main()
{
func("hello");
	
	
} 
