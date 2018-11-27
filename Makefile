NAME := libftprintf.a

FILES += ft_printf.c
FILES += parsing.c
FILES += parsing_functions_1.c
FILES += parsing_functions_2.c
FILES += printing_functions_1.c
FILES += printing_functions_2.c
FILES += printing_functions_3.c
FILES += processing.c
FILES += processing_functions_1.c
FILES += processing_functions_2.c

LIB_FILES += array.c
LIB_FILES += ft_strlen.c
LIB_FILES += ft_memcpy.c
LIB_FILES += ft_memset.c
LIB_FILES += ft_max.c
LIB_FILES += ft_abs_double.c
LIB_FILES += ft_realloc.c
LIB_FILES += ft_atoi.c
LIB_FILES += ft_itoa.c
LIB_FILES += ft_hextoa.c
LIB_FILES += ft_ltoa.c
LIB_FILES += ft_otoa.c
LIB_FILES += ft_wctomb.c
LIB_FILES += ft_isdigit.c
LIB_FILES += ft_isascii.c
LIB_FILES += ft_tolower.c
LIB_FILES += ft_toupper.c
LIB_FILES += ft_isprint.c
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

mouli: $(NAME)
	make -C ~/tools/42FileChecker/moulitest_42projects/ft_printf_tests/

yapt: $(NAME)
	make -C ~/tools/YAPT re
	~/tools/YAPT/yapt.py ~/tools/YAPT/test_files/regular_cases.py

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all