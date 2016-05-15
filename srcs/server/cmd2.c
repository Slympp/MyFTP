#include "myFTP.h"

int my_dele(global_data *data) {

	data->send->code = 250;
	strcpy(data->send->msg, "Requested file action okay, completed.");
	return (EXIT_SUCCESS);
}

int 	my_pwd(global_data *data) {
	int len;

	len = strlen(data->recv->arg);
	if (len != 2) {
		data->send->code = NO_ARG_CODE;
		strcpy(data->send->msg, NO_ARG);
		return (EXIT_SUCCESS);
	}
	data->send->code = 257;
	strcpy(data->send->msg, "\"PATHNAME\" created.");
	return (EXIT_SUCCESS);
}

int my_pasv(global_data *data) {

	if (strlen(data->recv->arg) != 2) {
		data->send->code = NO_ARG_CODE;
		strcpy(data->send->msg, NO_ARG);
		return (EXIT_SUCCESS);
	}
	data->send->code = 227;
	strcpy(data->send->msg, "Entering Passive Mode (h1,h2,h3,h4,p1,p2).");
	return (EXIT_SUCCESS);
}

int my_port(global_data *data) {

	data->port = atoi(data->recv->arg);
	data->send->code = 200;
	strcpy(data->send->msg, "Command okay.");
	return (EXIT_SUCCESS);
}

int my_help(global_data *data) {

	data->send->code = 214;
	strcpy(data->send->msg, "Help message.");
	return (EXIT_SUCCESS);
}