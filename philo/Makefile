#===CONFIGURATION===

NAME = philo

SRC =\
	main.c\
	mint.c\
	get_ms_ts.c\
	setup_clean.c
	
CFLAGS = -Wall -Werror -Wextra -g3
LFLAGS = -lpthread

LIBS =\
	../libft/libft.a\

INCLUDES =\
	-I./\
	-I./philo\
	-I../libft/

OBJ_DIR = obj

#===AUTOMATIC VARS===

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))

LIB_FLAGS = $(addprefix -L, $(dir $(LIBS))) $(addprefix -l, $(patsubst lib%.a, %, $(notdir $(LIBS))))

#===TARGETS===

all : $(NAME)

#===COMPILING===

$(OBJ_DIR) :
	$(shell mkdir -p $(OBJ_DIR))
$(OBJ_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	cc $(CFLAGS) -o $@ -c $< $(INCLUDES)
%.a :
	make -C $(dir $@)

#===LINKING===
$(NAME) : $(OBJ_DIR) $(LIBS) $(OBJ)
	cc -o $(NAME) $(OBJ) $(LIB_FLAGS) $(LFLAGS)

#===CLEAN===
clean :
	rm -rf $(OBJ_DIR) || true

#===FCLEAN===
fclean : clean
	rm -f $(NAME) || true

#===RE===
re : fclean all

.PHONY : re fclean clean all default bonus