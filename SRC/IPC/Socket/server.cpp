#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<string>
using namespace std;

int main()
{
   int listener_d = socket(PF_INET, SOCK_STREAM, 0);
   
   struct sockaddr_in name;
   name.sin_family = PF_INET;
   name.sin_port = (in_port_t)htons(30000);
   name.sin_addr.s_addr = htonl(INADDR_ANY);
   
   char rmsg[255];
   int c = bind( listener_d, (struct sockaddr*)&name, sizeof(name) );
   
   if( (listen(listener_d,10)) == -1 )
      cout<<"Error in listen"<<endl;
  
   int reuse = 1;
   
   setsockopt( listener_d, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int)); 
  
   while(1)
   {
		struct sockaddr_storage client_name;
		unsigned int add_size = sizeof( client_name );

		int connect_d = accept( listener_d, (struct sockaddr*)&client_name, &add_size );
		
		if( connect_d == -1 )
			cout<<"Error in accept client connection"<<endl;
 
		const char *msg = "Hi this is server responding to you\n";
		string smsg;
		send(connect_d, msg, strlen(msg), 0);
		
		while(1){
			//memset( smsg, '\0', sizeof( rmsg ) );
			int count = recv(connect_d, rmsg, sizeof(rmsg), 0);
			cout<<rmsg;
			memset( rmsg, '\0', sizeof( rmsg ) );
			getline( cin, smsg );
			char *s = static_const<char*>(smsg);
			send(connect_d, s, smsg.length(), 0);
		}
	}
    return 0;
}
