
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_NAME_LEN_MAX 255
#define SERVERPORT 6000

int main(int argc, char *argv[]) {
	char server_name[SERVER_NAME_LEN_MAX + 1] = "127.0.0.1\0";
	int server_port = SERVERPORT, socket_fd;
	struct hostent *server_host;
	struct sockaddr_in server_address;

	server_host = gethostbyname(server_name);

	/* Initialize IPv4 server address with server host. */
	memset(&server_address, 0, sizeof server_address);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);
	memcpy(&server_address.sin_addr.s_addr, server_host->h_addr,
		   server_host->h_length);

	/* Create TCP socket. */
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* Connect to socket with server address. */
	if (connect(socket_fd, (struct sockaddr *)&server_address,
				sizeof server_address) == -1) {
		perror("connect");
		exit(1);
	}

	printf("connection established\n");

	/*read the string to send*/
	char string[100];
	printf("input : ");
	scanf("%s", string);

	/*send query to the server*/
	write(socket_fd, string, 100);

	/*read the reply*/
	read(socket_fd, string, 100);

	/*close connection*/
	close(socket_fd);

	printf("output : %s\n\n", string);
	return 0;
}
