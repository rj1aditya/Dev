#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

int main()
{
   int listener_d = socket(PF_INET, SOCK_STREAM, 0);
   
   struct sockaddr_in name;
   name.sin_family = PF_INET;
   name.sin_port = (in_port_t)htons(30000);
   name.sin_addr.s_addr = inet_addr("192.168.56.101");
   
   char rmsg[255];
   int c = bind( listener_d, (struct sockaddr*)&name, sizeof(name) );
   
   if( (listen(listener_d,10)) == -1 )
      cout<<"Error in listen"<<endl;
  
   int reuse = 1;
   
   if((setsockopt( listener_d, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int))) == -1 )
		printf("not possible");
  
   while(1)
   {
		struct sockaddr_storage client_name;
		unsigned int add_size = sizeof( client_name );

		int connect_d = accept( listener_d, (struct sockaddr*)&client_name, &add_size );
		
		if( connect_d == -1 )
			cout<<"Error in accept client connection"<<endl;
 
		const char *msg = "Hi this is server responding to you\n";
		char  smsg[255];
		send(connect_d, msg, strlen(msg), 0);
		
		if(!fork())
		{
			while(1){
				int count = recv(connect_d, rmsg, sizeof(rmsg), 0);
				cout<<rmsg;
				memset( rmsg, '\0', sizeof( rmsg ) );
			}
		}
		char c[100] = "\t";
		if(!fork())
		{
			while(1)
			{
				memset( smsg, '\0', sizeof( rmsg ) );
				scanf("%s",smsg);
				for( int i = 0; smsg[i] != '\0'; i++ )
				{
					i++;
				}
				strcat(smsg, "\n");
				strcat(c,smsg);
				send(connect_d, smsg, strlen(smsg), 0);
				//send(connect_d, c, strlen(c), 0 );
			}
		}
	}
    return 0;
}
