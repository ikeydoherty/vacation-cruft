AM_CFLAGS = \
	-fstack-protector -Wall -pedantic			\
	-Wstrict-prototypes -Wundef -fno-common 		\
	-Werror-implicit-function-declaration 			\
	-Wformat -Wformat-security -Werror=format-security 	\
	-Wconversion -Wunused-variable -Wunreachable-code 	\
	-Wall -W -D_FORTIFY_SOURCE=2 -std=c11

bin_PROGRAMS = \
	snake

snake_SOURCES = \
	src/snake/main.c \
	src/snake/util.h

snake_CFLAGS = \
	$(SDL_CFLAGS) \
	$(AM_CFLAGS)

snake_LDADD = \
	$(SDL_LIBS)
