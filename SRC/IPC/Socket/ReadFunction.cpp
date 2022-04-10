#include<iostream>
#include<sys/socket.h>
using namespace std;

int read_in( int fd, char *buf, int msg_size )
{
	int slen = msg_size;
	char *s = buf;

	int c = recv( fd, s, slen, 0 );

	while( c > 0 && s[c-1] != '\n' )
	{
		s += c;
		slen -= c;
		int c = recv( fd, s, slen, 0 );
	}
	
	if( c < 0 )
		return c;
	else if( c == 0 )
		buf[0] = '\0';
	else
	{
		s[c-1] = '\0';
		return (msg_size - slen);
	}
}
