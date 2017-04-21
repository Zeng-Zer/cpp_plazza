##
## Makefile :D
##
## Made by David Zeng
## Login   <zeng_d@epitech.net>
##
## Started on  Mon Oct 12 13:31:18 2015 David Zeng
## Last update Sat Jul  2 21:56:26 2016 David Zeng
##

NAME :=		plazza
SRCDIR :=	src/
INCLUDE :=	include/

SRC :=		main.cpp \
		Utils.cpp

CXX :=		g++
CXXFLAGS :=	-W -Wall -Wextra -g -std=c++14
SRC :=		$(addprefix $(SRCDIR), $(SRC))
OBJ :=		$(SRC:.cpp=.o)
RM :=		rm -f

DEFAULT :=	"\033[00;0m"
GREEN :=	"\033[0;32;1m"
RED :=		"\033[0;31;1m"
CYAN :=		"\033[0;36;1m"

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) && \
		echo -e $(GREEN)"[BIN]"$(CYAN) $(NAME)$(DEFAULT) || \
		echo -e $(RED)"[XX]"$(DEFAULT) $(NAME)
	for file in $(shell find . | cut -c 3- | grep -P ".*\.(cpp|hpp|c|h)"); \
		do fgrep -niH -e TODO -e FIXME $$file --color=auto; done; true

clean:
	echo -e $(CYAN)"Cleaning $(NAME) tmp files..." $(DEFAULT)
	$(RM) $(OBJ)

fclean:	clean
	echo -e $(CYAN)"Cleaning $(NAME) executable..." $(DEFAULT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: all $(NAME) clean fclean re

%.o: %.cpp
	@$(CXX) -c $< -o $@ $(CXXFLAGS) $(foreach dir, $(INCLUDE), -I$(dir)) && \
		echo -e $(GREEN)"[OK]"$(DEFAULT) $< || \
		echo -e $(RED)"[KO]"$(DEFAULT) $<
