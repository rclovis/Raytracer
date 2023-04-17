##
## EPITECH PROJECT, 2021
## raytracer
## File description:
## Makefile
##

CC			=	g++

CFLAGS		=	-Wall -g -g3 -I$(INC_DIR) -std=c++20

TESTS_FLAGS	=	-Wall -g -g3 -I$(INC_DIR) -lcriterion --coverage

SRC_DIR		=	src

INC_DIR		=	inc

OBJ_DIR		=	obj

TESTS_DIR	=	tests

SRC			=	$(wildcard $(SRC_DIR)/*.cpp)

TESTS		=	$(wildcard $(TESTS_DIR)/*.cpp)

OBJ			=	$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

TESTS_OBJ	=	$(patsubst $(TESTS_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TESTS))

NAME		=	raytracer

GREEN		=	\033[1;32m

CYAN		=	\033[1;36m

YELLOW		=	\033[0;33m

NC			=	\033[0;0m

.PHONY:	all
all:
	@make $(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
	@echo -e "[$(GREEN)Compiled$(NC)] \"$(YELLOW)$@$(NC)\" executable created"

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "[$(GREEN)Compiled$(NC)] \"$(YELLOW)$<$(NC)\" object created"

.PHONY: tests_run
tests_run:	unit_tests
	@./unit_tests

unit_tests:	$(TESTS_OBJ)	$(OBJ)
	@$(CC) -o $@ $(filter-out $(OBJ_DIR)/main.o, $(OBJ)) \
		$(TESTS_OBJ) $(TESTS_FLAGS)
	@echo -e "[$(GREEN)Compiled$(NC)] \"$(YELLOW)$@$(NC)\" executable created"

$(TESTS_OBJ): $(OBJ_DIR)/%.o : $(TESTS_DIR)/%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "[$(GREEN)Compiled$(NC)] \"$(YELLOW)$<$(NC)\" object created"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

.PHONY:	clean
clean:
	@rm -rf $(OBJ)
	@rm -rf $(TESTS_OBJ)
	@rm -rf $(OBJ_DIR)/*.gc*
	@echo -e "[$(CYAN)Cleaning$(NC)] removed objects"

.PHONY:	fclean
fclean: clean
	@rm -rf $(NAME)
	@rm -rf unit_tests
	@echo -e "[$(CYAN)Cleaning$(NC)] removed target"

.PHONY:	re
re:	fclean	all
