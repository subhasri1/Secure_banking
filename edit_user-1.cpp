#include<iostream>
#include "edit_user.h"
#include <string.h>
using namespace std;

edit_user::edit_user(string u,string e,long m,string a)
{
	    {
	       user_name=u;
	       email=e;
	       mob=m;
	       address=a;
	    }
	    void show();
};
void edit_user::show()
{
    cout<<"\nThe Name of The account Holder : "<<user_name;
    cout<<"\nEmail : "<<email;
    cout<<"\nMobile Number : "<<mob;
    cout<<"\nAddress : "<<address<<endl;
}

