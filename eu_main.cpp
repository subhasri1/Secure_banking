#include<iostream>
#include "edit_user.h"
#include <string.h>
using namespace std;
int main()
{   
    	string un;
	string gr;
	long mb;
	string tp;
    	cout<<"Enter The Name of The account Holder : ";
	cin>>un;
	cout<<"Gender (M/F) : ";
	cin>>gr;
	cout<<"Enter Type of The account (C/S) : ";
	cin>>tp;
	cout<<"Enter Mobile Number: ";
	cin>>mb;
    	edit_user eu(un,gr,mb,tp) ;
    	eu.show();
}
    
