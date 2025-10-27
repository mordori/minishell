#ifndef VERIFIER_UTILS_H
# define VERIFIER_UTILS_H

#

char	*scan_directory(t_minishell *ms, char *directory, char *cmd_name);
char	*path_verif(t_minishell *ms, char *cmd_path);
char	*environ_verif(t_minishell *ms, char *path, char *cmd_name);

#endif
