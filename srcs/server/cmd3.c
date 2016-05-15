#include "myFTP.h"

int my_noop(global_data *data) {

	if (strlen(data->recv->arg) != 2) {
		data->send->code = NO_ARG_CODE;
		strcpy(data->send->msg, NO_ARG);
		return (EXIT_SUCCESS);
	}
	data->send->code = 200;
	strcpy(data->send->msg, "Command okay.");
	return (EXIT_SUCCESS);
}

int my_retr(global_data *data) {

	data->send->code = 150;
	strcpy(data->send->msg,
		"File status okay; about to open data connection.");
	return (EXIT_SUCCESS);
}

int my_stor(global_data *data) {

	data->send->code = 150;
	strcpy(data->send->msg,
		"File status okay; about to open data connection.");
	return (EXIT_SUCCESS);
}

int my_list(global_data *data) {

	data->send->code = 150;
	strcpy(data->send->msg,
		"File status okay; about to open data connection.");
	return (EXIT_SUCCESS);
}