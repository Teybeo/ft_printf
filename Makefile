NAME := libftprintf.a

FILES += ft_printf.c

LIB_FILES += array.c
LIB_FILES += ft_strlen.c
LIB_FILES += ft_memcpy.c
LIB_FILES += ft_memset.c
LIB_FILES += ft_max.c
LIB_FILES += ft_realloc.c
LIB_FILES += ft_atoi.c
LIB_FILES += ft_itoa.c
LIB_FILES += ft_ltoa.c
LIB_FILES += ft_otoa.c
LIB_FILES += ft_isdigit.c
LIB_FILES += ft_putchar_fd.c
LIB_FILES += ft_putnbr_fd.c

FILES += $(addprefix libft/,$(LIB_FILES))

OBJ_DIR := obj
OBJ_LIST := $(FILES:.c=.o)

OBJS := $(addprefix $(OBJ_DIR)/,$(OBJ_LIST))

FLAGS := -Wall -Wextra -Werror

INCLUDES := -I libft/ -I .

LIBS := -lft -L libft

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/libft/

# $^ is the dependencies of the rule
# $@ is the name of the rule
$(OBJ_DIR)/%.o : %.c
	gcc $(FLAGS) $(INCLUDES) -o $@ -c $^

curqui: $(NAME)
	cp libftprintf.a ~/tools/curqui_test/
	make -C ~/tools/curqui_test/
	~/tools/curqui_test/ft_printf_tests

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all