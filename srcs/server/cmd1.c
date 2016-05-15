#include "myFTP.h"

int my_user(global_data *data) {

	
	if (strcmp(data->username, "\0")) {
		data->send->code = 230;
		strcpy(data->send->msg, "User logged in, proceed.");
	}
	else if ((data->recv->arg[0] == '\r' && data->recv->arg[1] == '\n')
	 || (strcmp(data->recv->arg, "Anonymous\r\n"))) {
		data->send->code = INV_USER_CODE;
		strcpy(data->send->msg, INV_USER);
	}
	else {
		data->username = data->recv->arg;
		data->send->code = 331;
		strcpy(data->send->msg, "User name okay, need password.");
	}
	return (EXIT_SUCCESS);
}

int my_pass(global_data *data) {
	if (!strcmp(data->username, "\0")) {
		data->send->code = 332;
		strcpy(data->send->msg, "Need account for login.");
	} else {
		data->send->code = 230;
		strcpy(data->send->msg, "User logged in, proceed.");
	}
	return (EXIT_SUCCESS);
}

int 			my_cwd(global_data *data) {
	struct stat s;
	int 		err;

	data->send->code = INV_ARG_CODE;
	strcpy(data->send->msg, INV_ARG);

	if (strlen(data->recv->arg) > 2) {
		err = stat(strcat(data->path, data->recv->arg), &s);
		if (err != -1 && S_ISDIR(s.st_mode)) {
			data->path = data->recv->arg;
			data->send->code = 250;
			strcpy(data->send->msg, "Requested file action okay, completed.");
		}
	}
	return (EXIT_SUCCESS);
}

int 	my_cdup(global_data *data) {
	int i;

	if (strlen(data->recv->arg) != 2) {
		data->send->code = NO_ARG_CODE;
		strcpy(data->send->msg, NO_ARG);
	} else if (check_path(data->path) == EXIT_SUCCESS) {
		i = strlen(data->path) - 1;
		
		if (data->path[i] == '/')
			data->path[i--] = '\0';
		while (data->path[i] != '/') {
			data->path[i--] = '\0';
		}
		data->send->code = 200;
		strcpy(data->send->msg, "Command okay.");
	} else {
		data->send->code = INV_ARG_CODE;
		strcpy(data->send->msg, INV_ARG);
	}
	return (EXIT_SUCCESS);
}

int my_quit(global_data *data) {

	if (strlen(data->recv->arg) != 2) {
		data->send->code = NO_ARG_CODE;
		strcpy(data->send->msg, NO_ARG);
		return (EXIT_SUCCESS);
	}
	data->send->code = QUIT_CODE;
	strcpy(data->send->msg, "Service closing control connection.");
	return (EXIT_FAILURE);
}