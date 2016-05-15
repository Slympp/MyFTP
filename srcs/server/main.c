#include "myFTP.h"

int 		server_send(global_data *data) {
	char	compact_data[300];
	int 	i;

	memset(compact_data, 0, sizeof(compact_data));

	compact_data[0] = data->send->code / 100 + '0';
	compact_data[1] = data->send->code / 10 % 10 + '0';
	compact_data[2] = data->send->code % 10 + '0';
	compact_data[3] = ' ';

	i = 0;
	while (data->send->msg[i]) {
		compact_data[i + 4] = data->send->msg[i];
		i++;
	}
	compact_data[i + 4] = '\r';
	compact_data[i + 5] = '\n';

	if (write(data->sock, compact_data, strlen(compact_data)) == -1)
		return (my_error(strerror(errno)));

	return (EXIT_SUCCESS);
}

int 		server_recv(global_data *data) {
	char 	compact_data[300];
	int 	i;
	int 	j;
	int 	len;

	i = 0;
	j = 0;
	memset(compact_data, 0, sizeof(compact_data));
	if ((len = read(data->sock, compact_data, 299)) == -1)
			return (my_error(strerror(errno)));

	while (compact_data[i] && compact_data[i] != ' ' && 
		(compact_data[i] != '\r' && compact_data[i + 1] != '\n'))
		data->recv->cmd[j++] = compact_data[i++];
	data->recv->cmd[j] = '\0';
	i++;
	
	j = 0;
	while (compact_data[i] && i < len)
		data->recv->arg[j++] = compact_data[i++];
	data->recv->arg[j] = '\0';
	
	return (EXIT_SUCCESS);
}

global_data 			*init_global_data(global_data *data, int sock, char *path) {

	if (!(data = malloc(sizeof(global_data))) ||
		!(data->username = malloc(sizeof(char) * 250)) ||
		!(data->recv = malloc(sizeof(c_data))) ||
		!(data->send = malloc(sizeof(s_data)))) {
		fprintf(stderr, "%s\n", strerror(ENOMEM));
		return (NULL);
	}
	data->path = path;
	data->sock = sock;
	data->port = 0;
	data->username = "\0";
	return (data);
}

int 					handle_client(struct sockaddr_in server, int sock, char *path) {
  	global_data 		*data;
  	pid_t 				err;
	bool 				loop;

	if ((err = fork())) {
		data = NULL;
		if (!(data = init_global_data(data, sock, path)))
			return (EXIT_FAILURE);
		new_connection(data, &server);
		loop = true;
		while (loop) {
			if (server_recv(data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			loop = treat_packet(data);
			if (server_send(data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		printf("[LOG] Client %d dropped connection.\n", sock);
	} else if (err == -1)
		return (my_error(strerror(errno)));
	return (EXIT_SUCCESS);
}

int 					loop(int sock, char *path) {
  	struct sockaddr_in	server;
	int 				c_sock;
	int 				len;

	if (listen(sock, 100) == -1)
		return (my_error(strerror(errno)));

	len = sizeof(server);
	printf("[LOG] Server started and waiting for clients.\n");
	while (1) {
		if ((c_sock = accept(sock, (struct sockaddr *)&server,
				(socklen_t *)&len)) == -1)
			return (my_error(strerror(errno)));

		if (handle_client(server, c_sock, path) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int 					main(int ac, char **av) {
	int					sock;
	struct sockaddr_in	server;

	if (ac != 3) {
		fprintf(stderr, "%s\n", "Usage: ./server port path");
		return (EXIT_FAILURE);
	}
	if ((sock = init_socket()) == -1)
		return (EXIT_FAILURE);

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(av[1]));

	if (bind(sock, (const struct sockaddr *)&server, sizeof(server)) == -1)
		return (my_error(strerror(errno)));

	return (loop(sock, av[2]));
}
