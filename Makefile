#===CONFIGURATION===

NAME = philosopher
NAME_BONUS = bababooey

SRC =\
	philo/main.c\
	philo/setup_clean.c\
	philo/routine.c\
	philo/get_ms_ts.c\
	philo/mutexed_int.c

SRC_BONUS =\
	
CFLAGS = -Wall -Werror -Wextra -g3
LFLAGS = -lpthread

LIBS =\
	libft/libft.a\


INCLUDES =\
	-I./\
	-I./philo\
	-Ilibft/

OBJ_DIR = obj

#===AUTOMATIC VARS===

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))
OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(addsuffix _bonus.o, $(notdir $(basename $(SRC_BONUS)))))

LIB_FLAGS = $(addprefix -L, $(dir $(LIBS))) $(addprefix -l, $(patsubst lib%.a, %, $(notdir $(LIBS))))

#===TARGETS===

all : $(NAME)

bonus : $(NAME_BONUS)

#===COMPILING===

$(OBJ_DIR) :
	$(shell mkdir -p $(OBJ_DIR))
$(OBJ_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(INCLUDES)
$(OBJ_DIR)/%_bonus.o : bonus/%.c
	mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(INCLUDES)
%.a :
	make -C $(dir $@)

#===LINKING===
$(NAME_BONUS) : $(OBJ_DIR) $(LIBS) $(OBJ_BONUS)
	cc -o $(NAME_BONUS) $(OBJ_BONUS) $(LIB_FLAGS) $(LFLAGS)
$(NAME) : $(OBJ_DIR) $(LIBS) $(OBJ)
	cc -o $(NAME) $(OBJ) $(LIB_FLAGS) $(LFLAGS)

#===CLEAN===
clean :
	rm -rf $(OBJ_DIR) || true

#===FCLEAN===
fclean : clean
	rm -f $(NAME) $(NAME_BONUS) || true

#===RE===
re : fclean all

# valgrind : all
# 	valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.cfg ./minishell

.PHONY : re fclean clean all default bonus