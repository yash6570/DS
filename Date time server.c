#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int get_cpu_load() {
	int file_handler;
	char file_buffer[1024];
	float load;

	file_handler = open("/proc/loadavg", O_RDONLY);
	if (file_handler < 0) {
		return -1;
	}
	read(file_handler, file_buffer, sizeof(file_buffer) - 1);
	sscanf(file_buffer, "%f", &load);
	close(file_handler);
	return (int)(load);
}

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

	while (1) {
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		ticks = time(NULL);
		int cpu_usage = get_cpu_load();
		snprintf(sendBuff, sizeof(sendBuff), "%.24s\tCPU: %d%%\r\n",
				 ctime(&ticks), cpu_usage);
		write(connfd, sendBuff, strlen(sendBuff));

		close(connfd);
		sleep(1);
	}
}
