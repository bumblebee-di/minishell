NAME = minishell

CC= gcc
FLAGS= -g -Wall -Wextra -Werror

RED= \x1B[31m
GREEN= \033[92m
CYAN= \x1B[36m
ENDCOLOR= \x1B[0m

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -ltermcap -lcurses

SRCS = main.c shell_loop.c error.c
SRCS_EXECUTOR = $(addprefix executor/, simple_executor.c complex_executor.c execve_utils.c)
SRCS_HISTORY = $(addprefix history/, ddl_utils.c cmd_reader.c data_disjoiner.c)
SRCS_PARSER = $(addprefix parser/, parser.c parser_utils.c appender.c file_parser.c lcmd_creator.c lcmd_handler.c quote_parser.c env_var_parser.c)
SRCS_BUILTIN = $(addprefix builtin/, export.c sort_export.c unset.c cd.c cd_utils.c echo.c other.c shlvl.c exit.c export_utils.c)
SRCS_PIPE = $(addprefix pipe_redir/, pipe_redir.c pipe_redir_utils.c)
SRCS_TERMCAP = $(addprefix termcap/, tty.c)
SRCS_SIGNAL = $(addprefix signal/, signal.c)
SRCS_LIB	:= \
			ft_memset.c					\
			ft_bzero.c					\
			ft_memcpy.c					\
			ft_memccpy.c				\
			ft_memchr.c					\
			ft_memmove.c				\
			ft_memcmp.c					\
			ft_strlen.c					\
			ft_strlcpy.c				\
			ft_strlcat.c				\
			ft_strnstr.c				\
			ft_atoi.c					\
			ft_isalpha.c				\
			ft_isdigit.c				\
			ft_isalnum.c				\
			ft_isascii.c				\
			ft_isprint.c				\
			ft_toupper.c				\
			ft_tolower.c				\
			ft_strncmp.c				\
			ft_strrchr.c				\
			ft_strchr.c					\
			ft_calloc.c					\
			ft_strdup.c					\
			ft_substr.c					\
			ft_strjoin.c				\
			ft_strtrim.c				\
			ft_putchar_fd.c				\
			ft_putstr_fd.c				\
			ft_putendl_fd.c				\
			ft_putnbr_fd.c				\
			ft_strmapi.c				\
			ft_itoa.c					\
			ft_split.c					\
			ft_lstnew.c					\
			ft_lstadd_front.c			\
			ft_lstsize.c				\
			ft_lstlast.c				\
			ft_lstadd_back.c			\
			ft_lstdelone.c				\
			ft_lstclear.c				\
			ft_lstmap.c					\
			ft_lstiter.c				\


OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o) $(SRCS_EXECUTOR:.c=.o) $(SRCS_PARSER:.c=.o) $(SRCS_HISTORY:.c=.o) $(SRCS_BUILTIN:.c=.o) $(SRCS_PIPE:.c=.o) $(SRCS_TERMCAP:.c=.o) $(SRCS_SIGNAL:.c=.o))
OBJS_LIB = $(addprefix libft/, $(SRCS_LIB:.c=.o))

SRCS_DIR= srcs/
BIN_DIR= bin/
BIN= $(shell mkdir -p bin/parser) $(shell mkdir -p bin/builtin) $(shell mkdir -p bin/history) $(shell mkdir -p bin/pipe_redir) $(shell mkdir -p bin/termcap) $(shell mkdir -p bin/signal) $(shell mkdir -p bin/executor)

INCLUDES = $(addprefix includes/, minishell.h parser.h pipe_redir.h termcap.h signals.h)
RM = rm -rf

all: $(NAME) $(BIN)

$(BIN_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES)
	$(CC) -g $(FLAGS) -MMD -c $< -o $@
-include $(OBJS:.o=.d)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) $(OBJS_LIB)
	$(CC) $(FLAGS) $(LIBS) $^ -o $@
	$(RM) $(OBJS:.o=.d)
	echo "minishell ${GREEN}is compiled${ENDCOLOR}"

bonus: ;

clean:
	$(RM) $(OBJS)
	$(RM) $(BIN_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	echo "object files ${RED}are deleted${ENDCOLOR}"

fclean: clean
	$(RM) $(NAME) $(LIBFT)
	echo "minishell libft ${RED}are deleted${ENDCOLOR}"

re: fclean
	$(MAKE) all

norm:
	echo "${CYAN}--- libft/ ---${ENDCOLOR}"
	-norminette libft/*.c
	echo "${CYAN}--- srcs/executor ---${ENDCOLOR}"
	-norminette ${addprefix srcs/, ${SRCS_EXECUTOR}}
	echo "${CYAN}--- srcs/pipe_redir/ ---${ENDCOLOR}"
	-norminette ${addprefix srcs/, ${SRCS_PIPE}}
	echo "${CYAN}--- srcs/history/ ---${ENDCOLOR}"
	-norminette ${addprefix srcs/, ${SRCS_HISTORY}}
	echo "${CYAN}--- srcs/parser/ ---${ENDCOLOR}"
	-norminette ${addprefix srcs/, ${SRCS_PARSER}}
	echo "${CYAN}--- srcs/ ---${ENDCOLOR}"
	-norminette ${addprefix ${SRCS_DIR}, ${SRCS}}
	echo "${CYAN}--- srcs/builtin/ ---${ENDCOLOR}"
	-norminette ${addprefix srcs/, ${SRCS_BUILTIN}}
	echo "${CYAN}--- srcs/termcap/ ---${ENDCOLOR}"
	-norminette ${addprefix srcs/, ${SRCS_TERMCAP}}
	echo "${CYAN}--- srcs/signal/ ---${ENDCOLOR}"
	-norminette ${addprefix srcs/, ${SRCS_SIGNAL}}
	echo "${CYAN}--- srcs/includes/ ---${ENDCOLOR}"
	-norminette ${INCLUDES}

.SILENT:

.PHONY: all clean fclean re norm
