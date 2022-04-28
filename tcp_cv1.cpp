#include <iostream>
#include<cstring>
using namespace std;
#include <sys/types.h>
#include<termios.h>
#include<errno.h>
#include<string.h>
#include <sys/socket.h>
#include<sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXPWD 32
#define MOBL 40
struct User
{
    char usr[20];
    char pwd[20];
    //char mob[40];
    //char gen[20];
    //char acc_type[20];
    //char acc_num[20]={'0'};
}u1;

//=================================================================

ssize_t getpasswd (char **pw, size_t sz,int mask,FILE *fp)
 {
     if (!pw || !sz || !fp) return -1;    //invalid input
     #ifdef MAXPWD
     
     if(sz>MAXPWD) sz=MAXPWD;
     #endif
     
     if(*pw ==NULL)
     {
         void *tmp = realloc(*pw,sz * sizeof **pw);   //reallocate if no address
         if(!tmp)
         {
            return -1;
         }
         memset (tmp, 0 , sz);   //initialize memory to 0
         *pw = (char*) tmp;
     
         
     }
     size_t idx =0;
     int c =0;
     struct termios old_kbd_mode;
     struct termios new_kbd_mode;
     
     if(tcgetattr (0,&old_kbd_mode))
     {
         //cout<<stderr"Error: tcgetattr failed\n",__func__;
         return -1;
     }
     memcpy(&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));
     
     new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
     new_kbd_mode.c_cc[VTIME] =0;
     new_kbd_mode.c_cc[VMIN]=1;
     if(tcgetattr(0,&new_kbd_mode))
     {
         return-1;
     }
     
     //read characters from Fp, mask if valid char specidied
     while(((c=fgetc(fp)) != '\n' && c != EOF && idx<sz -1) || (idx == sz -1 && c == 127))
     {
         if(c!= 127)
         {
             if(31<mask && mask<127)
             {
                fputc(mask,stdout);
             }
            (*pw)[idx++] = c;
         }
         else if(idx>0)
         {
             if(31<mask && mask <127)
             {
                 fputc(0x8, stdout);
                 fputc(' ',stdout);
                 fputc(0x8,stdout);
             }
             (*pw)[--idx]=0;
         }
     }
     (*pw)[idx]=0;
     
     if(tcsetattr (0,TCSANOW,&old_kbd_mode))
     {
         cout<<stderr<<"error: tcsetattr failed.\n"<<__func__;
         return-1;
     }
     if(idx ==sz -1 && c!='\n')
     {
         cout<<stderr<<"Warning: truncate.\n"<<__func__<<sz-1;
         
     }
     return idx;
     
     
 }
//=======================================================================

// client sends a single character ('a') to the server and it recieves ('b') from the server
int main()
{
    
    int flag=0;
    char pw[MAXPWD]={0};
    char pw1[MAXPWD]={0};
    
    char *p1=pw; // store password
    char *p2=pw1;
    
    FILE *fp =stdin; // take password from keyboard
    FILE *fp1= stdin;
    
    ssize_t nchr =0;
    
    
    

//socket creation
int serv_fd = socket(AF_INET,SOCK_STREAM,0);
if (serv_fd == -1)
{
	perror("socket creation error");
	exit(1);
}
//initialize the socaddr_in structure
struct sockaddr_in sock_addr_serv;// sockaddr_in for IPV4
sock_addr_serv.sin_family = AF_INET;
sock_addr_serv.sin_port = 9980;
sock_addr_serv.sin_addr.s_addr = INADDR_ANY;

// connecting to server
socklen_t len = sizeof(sock_addr_serv);
if (connect(serv_fd,(struct sockaddr *)&sock_addr_serv,len)==-1)
{
	perror("connect error");
	exit(1);
}
//=============================================================================
/*cout << "in client client fd" << serv_fd << endl;                            
cout << "in client port (50) " << sock_addr_serv.sin_port << endl;
char ch = 'a';

write(serv_fd,&ch,1);// writes 'a' to server
read(serv_fd,&ch,1);// reads 'b' from server
cout << "from server " << ch << endl;*/
//==============================================================================
char usr[20],pwd[20];

int opt;
while(1)
{
    cout<<"\n 1. Register new user\n";
    cout<<"\n 2. Login\n";
    cout<<"\n 3. Exit\n";
    cout<<"Enter your choice: ";
    cin>>opt;
    
    //sending choice to server
    send(serv_fd,&opt,4,0);
    char usr[MAXPWD];
    char pwd[MAXPWD],pwd1[MAXPWD];
    //char mob[MOBL];
    //char gen[MAXPWD];
    //char acc_type[MAXPWD];
    //char acc_num[MAXPWD]={'0'};
    
    
    
    
    switch(opt)
    {
        case 1:
            cout<<"Enter User name: ";
            cin >>usr;
            cout<<"Enter password: ";
            getchar();
            getpasswd(&p1,MAXPWD,'*',fp);
            cout<<"Confirm password: ";
            getpasswd(&p2,MAXPWD,'*',fp1);
            
            //char* accnum= (char*)acc_num;
            if(strcmp(p1,p2)!=0)
            {
                cout<<"password is not matched\n";
                cout<<"Press any key to register again\n";
                getchar();
                continue;
            }
            cout<<"Please enter mobile number: ";
            //cin>>mob;
            cout<<"NOTE:- If male please enter M\n If Female please enter F\n"; 
            cout<<"Enter Gender: ";
            //cin>>gen;
            cout<<"NOTE:- If you want to open savings account, please enter S\n If you want to open current account, Please enter C\n";
            cout<<"Enter Account Type";
            //cin>>acc_type;
            //cout<<"Your Account Number is "<<acc_num<<endl;
            
            strcpy(u1.usr,usr);
            strcpy(u1.pwd,p1);
            //strcpy(u1.acc_num,acc_num);
            //strcpy(u1.mob,mob);
            //strcpy(u1.gen,gen);
            //strcpy(u1.acc_type,acc_type);
            
            send(serv_fd,&u1,sizeof(struct User),0);
            cout<<"Successfully Registered\n";
            int x;
            //x=(int)acc_num[0];
            //x++;
            //acc_num[0]=(char)x;
            
            
            
            
            break;
        case 2:
            
            cout<<"Enter User name: ";
            cin>>usr;
            cout<<"Enter password: ";
            getchar();
            getpasswd(&p1,MAXPWD,'*',fp);
            
            
            strcpy(u1.usr,usr);
            strcpy(u1.pwd,p1);
            send(serv_fd,&u1,sizeof(u1),0);
            char str[500];
            recv(serv_fd,str,sizeof(str),0);
            cout<<str<<endl;
            break;
        case 3:
            cout<<"Press any to exit\n";
            getchar();
            exit(1);
        default:
            cout<<"Invalid input\n";
            
            
    }
    
}









close(serv_fd);

}



