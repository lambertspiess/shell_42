# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    variables.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/29 16:50:56 by lspiess           #+#    #+#              #
#    Updated: 2020/06/30 06:17:24 by lspiess          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######### Source names, locations, and aliases

VPATH +=.:.
VPATH +=:srcs/ 

SRCS_PATH += ./srcs

# Add new source files here as such : SRCSNAMES += filename.c
SRCNAMES += main.c
SRCNAMES += static_utils.c
SRCNAMES += env_init.c
SRCNAMES += lexer.c
SRCNAMES += lexer_free.c
SRCNAMES += lexer_check_for_redundant_quotes.c
SRCNAMES += lexer_misc.c
SRCNAMES += parser.c
SRCNAMES += parser_build_job_tree.c
SRCNAMES += parser_build_line_tree.c
SRCNAMES += parser_build_command_tree.c
SRCNAMES += parser_build_command_tree_get_filename.c
SRCNAMES += parser_build_builtin_tree.c
SRCNAMES += parser_build_arg_tree.c
SRCNAMES += parser_free.c
SRCNAMES += print_tree.c
SRCNAMES += ast_utils.c
SRCNAMES += executer.c
SRCNAMES += executer_get_io_filenames.c
SRCNAMES += executer_pipeline.c
SRCNAMES += executer_pipeline_utils.c
SRCNAMES += executer_set_io_streams.c
SRCNAMES += executer_get_cmd_av.c
SRCNAMES += executer_check_dollar.c
SRCNAMES += executer_check_dollar_utils.c
SRCNAMES += executer_get_envstrarr.c
SRCNAMES += executer_get_pathstrarr.c
SRCNAMES += executer_execve.c
SRCNAMES += executer_exit_process.c
SRCNAMES += executer_free.c
SRCNAMES += executer_errmsg.c
SRCNAMES += executer_pwd.c
SRCNAMES += executer_env.c
SRCNAMES += executer_export.c
SRCNAMES += executer_unset.c
SRCNAMES += executer_echo.c
SRCNAMES += executer_cd.c
SRCNAMES += executer_exit.c

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCNAMES))

######### There are three libft for the three builds

LIBFTPATH = ./libft

LIBFTNAME = libft.a
SAN_LIBFTNAME = libftsan.a
VAL_LIBFTNAME = libftval.a

LIBFT = $(LIBFTPATH)/$(LIBFTNAME)
LIBFTSAN = $(LIBFTPATH)/$(SAN_LIBFTNAME)
LIBFTVAL = $(LIBFTPATH)/$(VAL_LIBFTNAME)

######### Header files

HEADER_PATH_MINISHELL += includes
HEADER_PATH_LIBFT += $(LIBFTPATH)/includes
INCLUDES = -I $(HEADER_PATH_LIBFT) -I $(HEADER_PATH_MINISHELL)

######### Valgrind flags are for leaks hunting, sanitize for debugging

CC = gcc

CFLAGS += -Wall -Wextra -D_POSIX_JOB_CONTROL -D_POSIX_C_SOURCE=200809L #-Werror
SANFLAGS += -Wall -Wextra -fsanitize=address,undefined
VALFLAGS += -Wall -Wextra -ggdb3

# Objects dir, respectively normal, and debugging (both sanitize and valgrind)

OBJS_PATH = objects_minishell
SAN_OBJS_PATH = san_objects_minishell
VAL_OBJS_PATH = val_objects_minishell
OBJSNAMES = $(SRCNAMES:.c=.o)

OBJS = $(addprefix $(OBJS_PATH)/,$(OBJSNAMES))
SAN_OBJS = $(addprefix $(SAN_OBJS_PATH)/,$(OBJSNAMES))
VAL_OBJS = $(addprefix $(VAL_OBJS_PATH)/,$(OBJSNAMES))

######### MISC : color codes for a pretty command line

GREEN = \033[32m
CYAN = \033[0;36m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m

CLEAR = \033[0m

# Clear line
CLRLINE = \033[K

# Go back to line
BTOLINE = \033[A
