NAME =	philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = routine.c utils.c utils2.c init.c parsing.c main.c

OBJS = $(SRCS:.c=.o)

YELLOW		= \033[1;33m
MAGENTA		= \033[1;35m
END			= \033[0m

TOTAL_FILES = $(words $(SRCS))

all:			$(NAME)
				@clear
				@echo "${MAGENTA}▗▄▄▖ ▐▌   ▄ █  ▄▄▄  ${END}";
				@echo "${MAGENTA}▐▌ ▐▌▐▌   ▄ █ █   █ ${END}";
				@echo "${MAGENTA}▐▛▀▘ ▐▛▀▚▖█ █ ▀▄▄▄▀ ${END}";
				@echo "${MAGENTA}▐▌   ▐▌ ▐▌█ █       ${END}";



$(NAME):		$(OBJS)
				$(CC) -pthread -lpthread -o $(NAME) $(OBJS) $(CFLAGS)

.c.o:
	@CURRENT_COUNT=$$(ls $(OBJS) 2>/dev/null | wc -l); \
	printf "\eCompiling philosophers.. [$$CURRENT_COUNT/$(TOTAL_FILES)]\e\r"; \
	$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)
				@clear
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡆⠀⠀clean⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡈⠻⠇⢸⣷⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡿⠿⠟⠛⠋⣉⣤⣴⣶⡀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣁⣠⣤⣤⣴⣶⣿⣿⠿⠿⠛⠋⣁⡀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠋⣉⣉⣠⣤⣴⣶⣾⣿⣿⣷⡀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢦⣄⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠂⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡏⣿⣿⣿⣿⡿⣿⣿⢿⣿⡿⢿⣿⠻⡿⠛⠁⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⠀⡟⢹⣿⡿⠃⠸⠿⠀⠙⠃⠀⠁⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}                                     ${END}";


fclean: 		clean
				$(RM) $(NAME)
				@clear
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡆⠀⠀Fclean⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡈⠻⠇⢸⣷⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡿⠿⠟⠛⠋⣉⣤⣴⣶⡀⠀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣁⣠⣤⣤⣴⣶⣿⣿⠿⠿⠛⠋⣁⡀⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠋⣉⣉⣠⣤⣴⣶⣾⣿⣿⣷⡀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢦⣄⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠂⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡏⣿⣿⣿⣿⡿⣿⣿⢿⣿⡿⢿⣿⠻⡿⠛⠁⠀⠀${END}";
				@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⠀⡟⢹⣿⡿⠃⠸⠿⠀⠙⠃⠀⠁⠀⠀⠀⠀⠀⠀${END}";
				@echo "${YELLOW}                                     ${END}";

re: 			fclean all

.PHONY:			all clean fclean re
