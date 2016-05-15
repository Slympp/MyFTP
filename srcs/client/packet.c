#include "myFTP.h"

bool			create_packet(c_data *send, char **line) {
	char		buffer[300];
	char 		cmds[FUNC_NB][5];
	int 		rd;

	commands_tab(cmds);
	write(1, "-> ", 3);
	while ((rd = read(1, buffer, 300)) > 0) {
		buffer[rd] = '\0';
		if (rd < 300 && check_syntax(buffer) < 2) {
			if (!(split_buffer(buffer, line)))
				return (false);
			strcpy(send->cmd, line[0]);
			strcpy(send->arg, line[1]);
			return (true);
		} else 
			printf(SYNTAX_ERR);
		write(1, "\n-> ", 4);
	}
	return (true);
}

bool 		treat_code(int code) {

	if (code == QUIT_CODE)
		return (false);
	else if (code == HELP_CODE || code == 501)
		display_help();
	return (true);
}

bool		read_packet(s_data *recv) {

	printf("<- %d\t%s\n", recv->code, recv->msg);
	return (treat_code(recv->code));
}