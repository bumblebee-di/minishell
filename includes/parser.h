#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <term.h>
# include "../libft/libft.h"

typedef struct s_global {
	pid_t			*pid;
	int				status;
	int				sig;
}	t_global;

struct s_global	g_gl;

typedef struct s_lcmd {
	char			**arg;
	char			*ri;
	char			*ro;
	char			*aro;
	struct s_lcmd	*next;
}	t_lcmd;

typedef struct s_par {
	char	*s;
	size_t	s_size;
	char	**arg;
	size_t	arg_size;
	char	*env_name;
	size_t	env_size;
	char	*ri;
	char	*ro;
	char	*aro;
	int		quote1;
	int		quote2;
	int		*quote_flag;
	int		i;
	int		start_append_str;
	int		call_prompt;
	char	*filename;
	int		some_flag;
}				t_par;

typedef struct s_node {
	char			*data;
	size_t			data_size;
	char			**data_ar;
	size_t			ar_size;
	char			*s;
	size_t			s_size;
	int				quote1;
	int				quote2;
	char			*temp;
	int				init_flag;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_dlist {
	t_node	*head;
	t_node	*tail;
	t_node	*cur;
	int		cmd_type;
	char	*temp2;
	int		history;
	char	buf[10];
	size_t	bytes_read;
}				t_dlist;

void	print_promt(void);
void	skip_spaces(t_par *par, const char *data);
void	par_init(t_par *par);
int		check_final_backslash(t_dlist **ddl);

void	read_cmd(t_dlist **ddl);
int		disjoin_data(t_node **cur);
void	add_back(t_dlist **ddl);
t_node	*get_last(t_node *head);
int		append_ddl_char(t_dlist **ddl, t_node **cur, const char *buf);

int		parser(t_lcmd **lcmd, const char *data, t_list *environ);
void	parse_files(t_par *par, const char *data);
void	set_redir_and_clean_prev_filename(t_par *par, int *redir, int num);
void	parse_env_var(t_par *par, const char *data, t_list *environ);
void	parse_single_quotes(t_par *par, const char *data);
void	parse_double_quotes(t_par *par, const char *data, t_list *environ);

t_lcmd	*ft_lcmdnew(t_par *par);
t_lcmd	*ft_lcmdlast(t_lcmd *lcmd);
void	ft_lcmdadd_back(t_lcmd **lcmd, t_lcmd *new);
int		ft_lcmdsize(t_lcmd *lcmd);
void	ft_lcmdclear(t_lcmd **lst, void (*del)(void*));

void	append_char(t_par *par, const char *data);
void	append_str(t_par *par, const char *data);
void	append_lcmd(t_lcmd **lcmd, t_par *par, const char *data);
void	append_env_name_char(t_par *par, const char *data);
void	append_env_value_char(t_par *par, char ch, const char *data);

#endif
