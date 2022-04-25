#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include<cstring>


struct User
{
    char usr[20];
    char pwd[20];
    //char mob[40];
    //char gen[20];
    //char acc_type[20];
    //char acc_num[20];
    
}u1,u2;



// server receives a single character from the client('a') and it sends 'b' to client
int main()
{
    FILE *fwrite1,*fread1;

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

//bind the socket with ip address and port
if (bind(serv_fd,(struct sockaddr *)&sock_addr_serv,sizeof(sock_addr_serv))==-1)
{
	perror("bind error");
	exit(1);
}

// listening (waiting) for client request
if (listen(serv_fd,5)==-1)
{
	perror("listen error");
	exit(1);
}

while (1)
{
	cout << "server waiting for client to connect"  << endl;
	
	//accepting client request
	struct sockaddr_in sock_addr_cli;
	socklen_t cli_len = sizeof(sock_addr_cli);
	int client_fd=accept(serv_fd,(struct sockaddr *)&sock_addr_cli,&cli_len);
	cout << "in server serv fd" << serv_fd << endl;
	cout << "in server client fd" << client_fd << endl;
	cout << "in server port (50) " << sock_addr_cli.sin_port << endl;
	cout << "in server ip " << sock_addr_cli.sin_addr.s_addr << endl;
 
	if (client_fd==-1)
	{
		perror(" accept error");
		exit(1);
	}
	/*char ch;
	read(client_fd,&ch,1);
	cout << " from client : " << ch << endl;		
	ch++;
	write(client_fd,&ch,1);*/	
	
	int opt;
	recv(client_fd,&opt,4,0);
	
	
	switch(opt)
	{
	    case 1:
	        recv(client_fd,&u1,sizeof(struct User),0);
	        cout<<"User name\n"<<u1.usr;
	        cout<<"User password for user "<<u1.usr<<" is "<<u1.pwd;
	        //fwrite1=fopen("user_data.txt",0660);
	        fwrite1 = fopen("user_data.txt","a+");
	        fwrite(&u1,sizeof(struct User),1,fwrite1);
	        //fwrite1<<"\n";
	        fclose(fwrite1);
	        cout<<"Data saved Successfully\n";
	        break;
	   case 2:
	        recv(client_fd,&u2,sizeof(struct User),0);
	        fread1= fopen("user_data.txt","a+");
	        cout<<"Hiii";
	        while(fread(&u1,sizeof(struct User),1,fread1)>0)
	        {
	            if(strcmp(u1.usr,u2.usr)==0 && strcmp(u1.pwd,u2.pwd)==0)
	            {
	                cout<<"Successfully logged in\n";
	                char str[500]="Successfully logged in\n";
	                send(client_fd,str,strlen(str),0);
	                
	            }
	            
	        }
	        fclose(fread1);
	        
	        break;
	   case 3:
	        exit(1);
	   default:
	        cout<<"Invalid option entered by client\n";
	        
	}
	
}

//close socket
if (close(serv_fd)==-1)
{
	perror("socket close error");
	exit(1);
}
}

