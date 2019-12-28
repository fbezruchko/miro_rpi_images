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

	char msg1[] = "Hello there!\n";

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4000);
	addr.sin_addr.s_addr = inet_addr("192.168.1.214");

	while (true)
	{
		printf("Send to server\n");
		sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
		usleep(1000000);
	}
	close(sock);

	return 0;
}
