#include "myFTP.h"

void 	display_help(void) {

	printf("USER <SP> <username> <CRLF>\t: %s", HELP1);
    printf("PASS <SP> <password> <CRLF>\t: %s", HELP2);
    printf("CWD  <SP> <pathname> <CRLF>\t: %s", HELP3);
    printf("CDUP <CRLF>\t\t\t: %s", HELP4);
    printf("QUIT <CRLF>\t\t\t: %s", HELP5);
    printf("DELE <SP> <pathname> <CRLF>\t: %s", HELP6);
    printf("PWD  <CRLF>\t\t\t: %s", HELP7);
    printf("PASV <CRLF>\t\t\t: %s", HELP8);
    printf("PORT <SP> <host-port> <CRLF>\t: %s", HELP9);
    printf("HELP [<SP> <string>] <CRLF>\t: %s", HELP10);
    printf("NOOP <CRLF>\t\t\t: %s", HELP11);
    printf("RETR <SP> <pathname> <CRLF>\t: %s", HELP12);
    printf("STOR <SP> <pathname> <CRLF>\t: %s", HELP13);
    printf("LIST [<SP> <pathname>] <CRLF>\t: %s", HELP14);
}

void 		free_tab(char **tab) {
	int		i;

	i = 0;
	if (tab) {
		while (tab[i])
			free(tab[i]);
		free(tab);
	}
}

int 		check_syntax(char s[300]) {
	int 	i;
	int 	cpt;

	i = 0;
	cpt = 0;
	if (!s || s[0] == '\n')
		return (2);
	while (s[i]) {
		if (s[i] == ' ')
			cpt++;
		i++;
	}
	return (cpt);
}

char 			**split_buffer(char buffer[300], char **s) {
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != ' ' && buffer[i] != '\n')
		s[0][j++] = buffer[i++];
	s[0][j] = '\0';
	i++;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		s[1][j++] = buffer[i++];
	s[1][j] = '\0';
	return (s);
}

bool 		is_valid_func(char cmd[][5], char *s1) {
	int 	i;
	bool	found;

	found = false;
	i = 0;
	while (i < FUNC_NB) {
		if (!strcmp(cmd[i], s1))
			found = true;
		i++;
	}
	if (!found)
		printf(SYNTAX_ERR);
	return (found);
}