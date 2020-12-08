CC =		gcc

COMMON_HOME =	../..

INSTALL_DIR =	$(COMMON_HOME)/bin
OBJECT_DIR =	./build

INCS =		$(COMMON_HOME) ./include

INCLUDES =	$(INCS:%=-I%)

CFLAGS =	-std=gnu90 -Wall -Wextra -Werror $(INCLUDES) -fPIC
LDLIBS =	-ldl
LIBFLAGS =	-shared

SRCS =		file_check.c		\
		proc_handler.c		\
		string_parser.c		\
		system_info.c		\
		utility_init.c		\
		crc.c			\
		malog_handler.c		\
		single_instance.c	\
                time_handler.c		\
                config_handler.c

OBJS =		$(SRCS:%.c=$(OBJECT_DIR)/%.o)
DEPS =		$(OBJS:%.o=%.d)
TARGET =	libmautil.so

all: dir $(TARGET)

dir:
	@mkdir -p $(OBJECT_DIR)

$(TARGET): $(OBJS)
	$(CC) -o $(INSTALL_DIR)/$@ $? $(LIBFLAGS) $(LDLIBS)
	@printf "\nBuild Success : [32m%s[0m\n\n" $@

clean:
	rm -rf $(OBJS) $(DEPS) $(INSTALL_DIR)/$(TARGET)
	@printf "\nClean Success : [32m%s[0m\n\n" "$(OBJS) $(DEPS) $(TARGET)"

$(OBJECT_DIR)/%.o: %.c Makefile
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

-include $(DEPS)
