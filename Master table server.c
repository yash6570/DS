#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {	// main method
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;

	char sendBuff[1025];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);

	bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 10);
	printf("Node 	IP Address 		Port\n");
	while (1) {
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		ticks = time(NULL);
		printf("%d		%s 		%d\n", 1, "localhost", 5000);
		snprintf(sendBuff, sizeof(sendBuff), "%d		%s 		%d\n", 1,
				 "localhost", 5000);
		write(connfd, sendBuff, strlen(sendBuff));
		close(connfd);
		sleep(1);
	}
}
