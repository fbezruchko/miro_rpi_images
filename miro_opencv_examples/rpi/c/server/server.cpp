#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in addr;
	char sock_buf[1024];
	int sock_bytes_read;
	
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	
	while (true)
	{
		sock_bytes_read = recvfrom(sock, sock_buf, 1024, 0, NULL, NULL);
		sock_buf[sock_bytes_read] = '\0';
		printf("Recieved from client: %s", sock_buf);
	}

	return 0;
}
