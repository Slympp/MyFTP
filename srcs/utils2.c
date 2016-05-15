#include "myFTP.h"

int 		check_path(char *s) {
	int		i;
	int		cpt;

	i = 1;
	cpt = 0;
	while (s[i]) {
		if (s[i] == '/')
			cpt++;
		i++;
	}
	if (cpt == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}