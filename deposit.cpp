#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main ()
{
    string line;
    string username;
    float balance;
  ofstream myfile ("customer.txt",ios::app);
  if (myfile.is_open())
  {
      cout<<"Enter Username";
      getline(cin>>ws,username);
      cout<<"Enter the amount to be Deposit";
      cin>>balance;
    myfile << username<<","<<balance;
    myfile.close();
  }
  else cout << "Unable to open file";


  ifstream myfile1 ("customer.txt");
  if (myfile1.is_open())
  {
    while ( getline (myfile1,line) )
    {
      cout << line << '\n';
    }
    myfile1.close();
  }

  else cout << "Unable to open file";
  return 0;
}

