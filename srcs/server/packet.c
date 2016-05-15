#include "myFTP.h"

int 		get_cmd_id(char cmd[][5], char *s1) {
	int 	i;

	i = 0;
	while (i < FUNC_NB) {
		if (!strcmp(cmd[i], s1))
			return (i);
		i++;
	}
	return (-1);
}

void 	funcs_tab(t_func_ptr execute[]) {

	execute[0] = my_user;
	execute[1] = my_pass;
	execute[2] = my_cwd;
	execute[3] = my_cdup;
	execute[4] = my_quit;
	execute[5] = my_dele;
	execute[6] = my_pwd;
	execute[7] = my_pasv;
	execute[8] = my_port;
	execute[9] = my_help;
	execute[10] = my_noop;
	execute[11] = my_retr;
	execute[12] = my_stor;
	execute[13] = my_list;
}

void 			invalid_command(s_data *send, char *s) {

	send->code = 501;
	strcpy(send->msg, s);	
}

bool			treat_packet(global_data *data) {
	char 		cmds[FUNC_NB][5];
	t_func_ptr	execute[14];
	int 		cmd_id;

	commands_tab(cmds);
	funcs_tab(execute);
	if ((cmd_id = get_cmd_id(cmds, data->recv->cmd)) != -1) {
		if (execute[cmd_id](data) == EXIT_FAILURE)
			return (false);
	} else
		invalid_command(data->send, INV_CMD);
	return (true);
}

int 	new_connection(global_data *data, struct sockaddr_in *server) {

	printf("[LOG] New connection etablished. IP:%s ID:%d\n", 
		inet_ntoa(server->sin_addr), data->sock);
	data->send->code = 220;
	strcpy(data->send->msg, "Service ready for new user.");
	if (server_send(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}