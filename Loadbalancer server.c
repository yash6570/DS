
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BACKLOG 10

int clientNumber = 0;
int numberOfConnections = 0;

typedef struct pthread_arg_t {
	int new_socket_fd;
	struct sockaddr_in client_address;
} pthread_arg_t;

/* Thread routine to serve connection to client. */
void *pthread_routine(void *arg);

/* Signal handler to handle SIGTERM and SIGINT signals. */
void signal_handler(int signal_number);

int main(int argc, char *argv[]) {
	int port, socket_fd, new_socket_fd;
	struct sockaddr_in address;
	pthread_attr_t pthread_attr;
	pthread_arg_t *pthread_arg;
	pthread_t pthread;
	socklen_t client_address_len;

	/* Get port from command line arguments or stdin. */
	port = argc > 1 ? atoi(argv[1]) : 0;
	if (!port) {
		printf("Enter Port: ");
		scanf("%d", &port);
	}

	/* Initialize IPv4 address. */
	memset(&address, 0, sizeof address);
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

	/* Create TCP socket. */
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* Bind address to socket. */
	if (bind(socket_fd, (struct sockaddr *)&address, sizeof address) == -1) {
		perror("bind");
		exit(1);
	}

	/* Listen on socket. */
	if (listen(socket_fd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	/* Assign signal handlers to signals. */
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		perror("signal");
		exit(1);
	}
	if (signal(SIGTERM, signal_handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	/* Initialize pthread attribute to create detached threads. */
	if (pthread_attr_init(&pthread_attr) != 0) {
		perror("pthread_attr_init");
		exit(1);
	}
	if (pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) !=
		0) {
		perror("pthread_attr_setdetachstate");
		exit(1);
	}

	while (1) {
		/* Create pthread argument for each connection to client. */
		pthread_arg = (pthread_arg_t *)malloc(sizeof *pthread_arg);
		if (!pthread_arg) {
			perror("malloc");
			continue;
		}

		/* Accept connection to client. */
		client_address_len = sizeof pthread_arg->client_address;
		new_socket_fd =
			accept(socket_fd, (struct sockaddr *)&pthread_arg->client_address,
				   &client_address_len);
		if (new_socket_fd == -1) {
			perror("accept");
			free(pthread_arg);
			continue;
		}

		/* Initialize pthread argument. */
		pthread_arg->new_socket_fd = new_socket_fd;

		/* Create thread to serve connection to client. */
		if (pthread_create(&pthread, &pthread_attr, pthread_routine,
						   (void *)pthread_arg) != 0) {
			perror("pthread_create");
			free(pthread_arg);
			continue;
		}
	}
	return 0;
}

/*function to convert string to upper case*/
void upper_string(char s[]) {
	int c = 0;
	while (s[c] != '\0') {
		if (s[c] >= 'a' && s[c] <= 'z') s[c] = s[c] - 32;
		c++;
	}

	// following loop is added to increase the time taken by this function
	for (int i = 0; i < 1000000000; i++)
		for (int j = 0; j < 10; j++) c = j;
	return;
}

void *pthread_routine(void *arg) {
	/*initialize*/
	clientNumber++;
	int clientIdx = clientNumber;
	numberOfConnections++;
	pthread_arg_t *pthread_arg = (pthread_arg_t *)arg;
	int new_socket_fd = pthread_arg->new_socket_fd;
	struct sockaddr_in client_address = pthread_arg->client_address;
	/* TODO: Get arguments passed to threads here. See lines 22 and 116. */

	free(arg);

	/*read the input string*/
	char string[100];
	read(new_socket_fd, string, 100);

	/*perform task based on the input*/
	if (strcmp("__clients?", string) == 0) {
		printf("load check\n");
		char result[100];
		sprintf(result, "%d", numberOfConnections - 1);
		write(new_socket_fd, result, 100);
		clientNumber--;
	} else {
		printf("client#%d : connected\n", clientIdx);
		upper_string(string);
		write(new_socket_fd, string, 100);
		printf("client#%d : disconnected\n", clientIdx);
	}

	/*close connection*/
	close(new_socket_fd);
	numberOfConnections--;

	return NULL;
}

void signal_handler(int signal_number) { exit(0); }
