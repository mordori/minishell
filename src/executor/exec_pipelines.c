#include "defines.h"
#include "executor.h"

//pipeline commands. basically PIPEX shit, calld from execute_pipeline in executor.c
int		create_pipes()
{
	return (SUCCESS);
}

int		spawn_children()
{
	fork(); //forking probably involved xD
	return (SUCCESS);
}

int		close_pipes()
{
	close(); //or something else?
	return (SUCCESS);
}
