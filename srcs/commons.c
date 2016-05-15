#include "myFTP.h"

int 				init_socket(void) {
	struct protoent	*protocol;
  	int				sock;

	if (!(protocol = getprotobyname("TCP"))) {
		fprintf(stderr, "%s\n", "Failed to get protocol.");
		return (-1);
    }
  	if ((sock = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) == -1) {
  		fprintf(stderr, "%s\n", strerror(errno));
  		return (-1);
    }
	return (sock);
}

int 	my_error(char *s) {
	fprintf(stderr, "%s\n", s);
	return (EXIT_FAILURE);
}

void 	assign_str(char dest[5], char *src) {
	int	i;

	i = -1;
	while (++i < 4)
		dest[i] = src[i];
	dest[4] = '\0';
}

void 	commands_tab(char cmds[14][5]) {

	assign_str(cmds[0], "USER");
	assign_str(cmds[1], "PASS");
	assign_str(cmds[2], "CWD");
	assign_str(cmds[3], "CDUP");
	assign_str(cmds[4], "QUIT");
	assign_str(cmds[5], "DELE");
	assign_str(cmds[6], "PWD");
	assign_str(cmds[7], "PASV");
	assign_str(cmds[8], "PORT");
	assign_str(cmds[9], "HELP");
	assign_str(cmds[10], "NOOP");
	assign_str(cmds[11], "RETR");
	assign_str(cmds[12], "STOR");
	assign_str(cmds[13], "LIST");
}