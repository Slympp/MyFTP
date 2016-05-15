#ifndef	 __MYFTP_H__
# define __MYFTP_H__

# include <arpa/inet.h>
# include <errno.h>
# include <netdb.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define MSG_LEN	250
# define CMD_LEN	50
# define ARG_LEN 	250
# define FUNC_NB 	14
# define SYNTAX_ERR "Incorrect syntax: CMD <SP> [ARG] <CRLF>. Type HELP\n"

# define QUIT_CODE	221
# define HELP_CODE	214

# define INV_CMD_CODE	501
# define INV_ARG_CODE	502
# define NO_ARG_CODE	503
# define INV_USER_CODE	504

# define INV_CMD 	"Command invalid."
# define INV_ARG 	"Argument invalid."
# define NO_ARG		"Command shouldn't have an argument"
# define INV_USER 	"Invalid username"

# define HELP1		"Specify user for authentication\n"
# define HELP2		"Specify password for authentication\n"
# define HELP3		"Change working directory\n"
# define HELP4		"Change working directory to parent directory\n"
# define HELP5		"Disconnection\n"
# define HELP6		"Delete file on the server\n"
# define HELP7		"Print working directory\n"
# define HELP8		"Enable \"passive\" mode for data transfer\n"
# define HELP9		"Enable \"active\" mode for data transfer\n"
# define HELP10		"List available commands\n"
# define HELP11		"Do nothing\n"
# define HELP12		"Download file from server to client\n"
# define HELP13		"Upload file from client to server\n"
# define HELP14		"List files in the current working directory\n\n"

/* 		
** 		DATA STORAGE
*/

typedef struct s_server_packet {
	int 	code;
	char 	msg[MSG_LEN];
} 			s_data;

typedef struct s_client_packet {
	char 	cmd[CMD_LEN];
	char 	arg[ARG_LEN];
} 			c_data;

typedef struct 	s_server_data {
	char 	*username;
	char 	*path;
	c_data 	*recv;
	s_data 	*send;
	int 	sock;
	int 	port;
} 			global_data;

typedef enum { false, true } bool;

typedef int (*t_func_ptr)(global_data *);


/*
** 		COMMONS
*/

int 	init_socket(void);
int 	my_error(char *);
void 	assign_str(char [5], char *);
void 	commands_tab(char [FUNC_NB][5]);


/*
** 		UTILS
*/

void 	display_help(void);
void 	free_tab(char **);
int 	check_syntax(char [300]);
char 	**split_buffer(char [300], char **);
bool 	is_valid_func(char [][5], char *);

int		check_path(char *s);



/*
** 		SERVER
*/

int 	server_send(global_data *);
void 	funcs_tab(t_func_ptr []);
bool	treat_packet(global_data *);
int 	new_connection(global_data *data, struct sockaddr_in *);

int 	my_user(global_data *);
int 	my_pass(global_data *);
int 	my_cwd(global_data *);
int 	my_cdup(global_data *);
int 	my_quit(global_data *);
int 	my_dele(global_data *);
int 	my_pwd(global_data *);
int 	my_pasv(global_data *);
int 	my_port(global_data *);
int 	my_help(global_data *);
int 	my_noop(global_data *);
int 	my_retr(global_data *);
int 	my_stor(global_data *);
int 	my_list(global_data *);


/*
** 		CLIENT
*/

bool	create_packet(c_data *, char **);
bool	read_packet(s_data *);

#endif
