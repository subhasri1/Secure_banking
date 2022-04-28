#include<iostream>
#include "edit_user.h"
#include <string.h>
using namespace std;
int main()
{   
    	string un;
	string em;
	long mb;
	string ad;
    	cout<<"Enter The Name of The account Holder : ";
	cin>>un;
	cout<<"Enter E-mail : ";
	cin>>em;
	cout<<"Enter Mobile NUmber : ";
	cin>>mb;
	cout<<"Enter Address: ";
	cin>>ad;
    	edit_user eu(un,em,mb,ad) ;
    	eu.show();
}
    
