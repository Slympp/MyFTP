#include "myFTP.h"

int 		client_send(int sock, c_data *data) {
	char	compact_data[300];
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	memset(compact_data, 0, sizeof(compact_data));
	while (data->cmd && data->cmd[i])
		compact_data[j++] = data->cmd[i++];
	compact_data[j++] = ' ';

	i = 0;
	while (data->arg && data->arg[i])
		compact_data[j++] = data->arg[i++];
	compact_data[j] = '\r';
	compact_data[j + 1] = '\n';
	
	if (write(sock, compact_data, strlen(compact_data)) == -1)
		return (my_error(strerror(errno)));

	return (EXIT_SUCCESS);
}

int 		client_recv(int sock, s_data *data) {
	char 	compact_data[300];
	int 	i;
	int 	len;

	memset(compact_data, 0, sizeof(compact_data));
	if ((len = read(sock, compact_data, 299)) == -1)
			return (my_error(strerror(errno)));
	else if (len == 0) {
		fprintf(stderr, "%s\n", "Server dropped connection.");
		return (EXIT_FAILURE);
	}

	data->code = compact_data[2] - '0';
	data->code += (compact_data[1] - '0') * 10;
	data->code += (compact_data[0] - '0') * 100;
	
	i = 0;
	while (compact_data[i + 4] &&
		(compact_data[i] != '\r' && compact_data[i] != '\n')) {
		data->msg[i] = compact_data[i + 4];
		i++;
	}
	data->msg[i] = '\0';
	return (EXIT_SUCCESS);
}

char 	**malloc_tab(char **s) {

	if (!(s = malloc(sizeof(char) * 2))
		|| !(s[0] = malloc(sizeof(char) * 250))
		|| !(s[1] = malloc(sizeof(char) * 250))) {
		fprintf(stderr, "%s\n", strerror(ENOMEM));
		return (NULL);
	}
	return (s);
}

int 		loop(int sock) {
	c_data 	*send;
	s_data 	*recv;
	bool 	loop;
	char 	**line;

	line = NULL;
	line = malloc_tab(line);
	if (!(send = malloc(sizeof(c_data *)))
		|| !(recv = malloc(sizeof(s_data *))))
		return (my_error(strerror(ENOMEM)));
	if (client_recv(sock, recv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	loop = read_packet(recv);
	while (loop) {
		if (!(loop = create_packet(send, line)))
			return (EXIT_FAILURE);
		if (client_send(sock, send) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (client_recv(sock, recv) == EXIT_FAILURE)
			return (EXIT_FAILURE);

		loop = read_packet(recv);
	}
	return (EXIT_SUCCESS);
}

int 					main(int ac, char **av) {
	int					sock;
	struct sockaddr_in	client;

	if (ac != 3) {
		fprintf(stderr, "%s\n", "Usage: ./client address port");
		return (EXIT_FAILURE);
	}
	if ((sock = init_socket()) == -1)
		return (EXIT_FAILURE);

	client.sin_addr.s_addr = inet_addr(av[1]);
	client.sin_family = AF_INET;
	client.sin_port = htons(atoi(av[2]));

	if (connect(sock, (const struct sockaddr *)&client, sizeof(client)) == -1)
    	return (my_error(strerror(errno)));

	return (loop(sock));
}
