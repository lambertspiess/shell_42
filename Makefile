# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lspiess <lspiess@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/26 12:49:22 by lspiess           #+#    #+#              #
#    Updated: 2020/12/25 00:49:37 by lspiess          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include variables.mk

# Reminder : sanitize and valgrind flags are not compatible. Running valgrind 
# on binaries compiled with -fsanitize will crash your machine.
# To avoid this, this build compiles three executables : 
# minishell, val_minishell, san_minishell

NAME = minishell
SAN_NAME = san_minishell
VAL_NAME = val_minishell

######### Rules to build "normal" executable (-Wall -Wextra -Werror)

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(CLRLINE)$(CYAN)$(NAME)$(CLEAR)"

$(OBJS) : $(OBJS_PATH)/%.o: %.c
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(CYAN) Compiling $(SRCS_PATH)/$<$(CLEAR)$(CLRLINE)$(BTOLINE)"

$(LIBFT) :
	@$(MAKE) -C $(LIBFTPATH)

clean :
	@rm -rf $(OBJS_PATH)

fclean : clean
	@rm -f $(NAME)

re : fclean
	@make all

lftclean :
	@cd $(LIBFTPATH) && make clean

lftfclean : lftclean
	@cd $(LIBFTPATH) && make fclean

######### Rules to build debugging executable (-fsanitize)

san : $(SAN_NAME)

$(SAN_NAME) : $(LIBFTSAN) $(SAN_OBJS)
	@$(CC) $(SANFLAGS) $(INCLUDES) $(LIBFTSAN) $(SAN_OBJS) -o $(SAN_NAME)
	@echo "$(CLRLINE)$(PURPLE)$(SAN_NAME)$(CLEAR)"


$(SAN_OBJS) : $(SAN_OBJS_PATH)/%.o: %.c
	@mkdir $(SAN_OBJS_PATH) 2> /dev/null || true
	@$(CC) $(SANFLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(PURPLE) Compiling $(SRCS_PATH)/$<$(CLEAR)$(CLRLINE)$(BTOLINE)"

$(LIBFTSAN) :
	@$(MAKE) san -C $(LIBFTPATH)

sanclean :
	@rm -rf $(SAN_OBJS_PATH)

sanfclean : sanclean
	@rm -f $(SAN_NAME)

sanre : sanfclean
	@make san

sanlftclean :
	@cd $(LIBFTPATH) && make sanclean

sanlftfclean : lftclean
	@cd $(LIBFTPATH) && make sanfclean

######### Rules to build leaks-checking executable (valgrind)

val : $(VAL_NAME)

$(VAL_NAME) : $(LIBFTVAL) $(VAL_OBJS)
	@$(CC) $(VALFLAGS) $(INCLUDES) $(LIBFTVAL) $(VAL_OBJS) -o $(VAL_NAME)
	@echo "$(CLRLINE)$(YELLOW)$(VAL_NAME)$(CLEAR)"

$(VAL_OBJS) : $(VAL_OBJS_PATH)/%.o: %.c
	@mkdir $(VAL_OBJS_PATH) 2> /dev/null || true
	@$(CC) $(VALFLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(YELLOW) Compiling $(SRCS_PATH)/$<$(CLEAR)$(CLRLINE)$(BTOLINE)"

$(LIBFTVAL) :
	@$(MAKE) val -C $(LIBFTPATH)

valclean :
	@rm -rf $(VAL_OBJS_PATH)

valfclean : valclean
	@rm -f $(VAL_NAME)

valre : valfclean
	@make val

vallftclean :
	@cd $(LIBFTPATH) && make valclean

vallftfclean : lftclean
	@cd $(LIBFTPATH) && make valfclean

########## For Salty's alpine VM
#
#alpine :
#	$(MAKE) -C ./libft
#	gcc -Wall -Wextra -I includes -I ./libft/includes -L ./libft -c ./srcs/*.c
#	gcc -o alpine_minishell -I includes -I ./libft/includes *.o ./libft/libft.a -Wall -Wextra
#
#alpclean :
#	rm -rf *.o
#
#alpfclean :
#	make alpclean
#	rm -f alpine_minishell
#
#alpre :
#	make alpfclean
#	make alpine
#
#alpsan :
#	cd ./libft && make san
#	gcc -Wall -Wextra -fsanitize=address,undefined -I includes -I ./libft/includes -L ./libft -c ./srcs/*.c
#	gcc -Wall -Wextra -fsanitize=address,undefined -o alpsan_minishell -I includes -I ./libft/includes *.o ./libft/libft.a -Wall -Wextra
#
#alpsanclean :
#	rm -rf *.o
#
#alpsanfclean :
#	make alpsanclean
#	rm -f alpsan_minishell
#
#alpsanre :
#	make alpsanfclean
#	make alpsan
#

######### For Xubuntu

xubuntu :
	$(MAKE) -C ./libft
	gcc -Wall -Wextra -I includes -I ./libft/includes -L ./libft -c ./srcs/*.c
	gcc -o xminishell -I includes -I ./libft/includes *.o ./libft/libft.a -Wall -Wextra

xclean :
	rm -rf *.o

xfclean :
	make xclean
	rm -f xminishell

xre :
	make xfclean
	make xubuntu

xsan :
	cd ./libft && make san
	gcc -Wall -Wextra -fsanitize=address,undefined -I includes -I ./libft/includes -L ./libft -c ./srcs/*.c
	gcc -Wall -Wextra -fsanitize=address,undefined -o alpsan_minishell -I includes -I ./libft/includes *.o ./libft/libft.a -Wall -Wextra

xclean :
	rm -rf *.o

xfclean :
	make xclean
	rm -f xminishell

xre :
	make xfclean
	make xsan
