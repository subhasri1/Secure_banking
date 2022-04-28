#include<iostream>
#include "edit_user.h"
#include <string.h>
using namespace std;
//edit_user{}
edit_user::edit_user(string u,string g,long m,string t)
{
	    {
	       user_name=u;
	       gender=g;
	       mob=m;
	       type=t;
	    }
	    void show();
};
void edit_user::show()
{
    cout<<"\nThe Name of The account Holder : "<<user_name;
    cout<<"\nGender (M/F) : "<<gender;
    cout<<"\nType of The account (C/S) : "<<type;
    cout<<"\nMobile Number: "<<mob<<endl;
}

