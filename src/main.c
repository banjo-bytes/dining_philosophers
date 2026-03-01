/* ################################################################################
# File:    main.c
# Author:  banjo-bytes
# Date:    2026-03-01
################################################################################ */

#include <stdlib.h>
/*	Usage: ./phil N td te ts [Nm]
	N - Number of philosophers
	td - time to die (ms)
	te - time to eat (ms)
	ts - time to sleep (ms)
	[Nm] - number of meals before sim stops [optional]
*/
int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 7) //TODO: Add || arg_check(argv))
		return (EXIT_FAILURE);
	return (0);
}
