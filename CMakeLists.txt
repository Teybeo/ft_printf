cmake_minimum_required(VERSION 3.12)
project(printf C)

set(CMAKE_C_STANDARD 99)

set(SOURCES
    libft/array.c
    libft/ft_realloc.c
    libft/ft_strlen.c
    libft/ft_memcpy.c
    libft/ft_memset.c
    libft/ft_max.c
    libft/ft_ltoa.c
    libft/ft_itoa.c
    libft/ft_atoi.c
    libft/ft_isdigit.c
    libft/ft_putnbr_fd.c
    libft/ft_putchar_fd.c
        libft/ft_otoa.c)
set(TEST_SOURCES
        ft_printf.c
        test.c)

add_library(printf ${SOURCES})

add_executable(printf_test ${TEST_SOURCES})

target_link_libraries(printf_test PUBLIC printf)

target_include_directories(printf PUBLIC libft)
