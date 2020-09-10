CC	= gcc

INSTALL_DIR	=	$(shell pwd)/../bin

COMMON_HOME	=	$(shell pwd)/../..

INCS		=	$(COMMON_HOME)

INCLUDES	=	$(INCS:%=-I%)

CFLAGS		=	-g -std=gnu90 -Wall -Wextra -Werror $(INCLUDES) -ldl -fPIC
LIBFLAGS	=	-shared

SRCS		=	file_check.c			\
				proc_handler.c			\
				string_parser.c			\
				system_info.c			\
				utility_init.c			\
				crc.c					\
				malog_handler.c			\
				single_instance.c       \
                time_handler.c          \
                config_handler.c

OBJS	= $(SRCS:%.c=%.o)
TARGET	= libmautil.so

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $?
	mv $(TARGET) $(INSTALL_DIR)
	@printf "\nBuild Success : [32m%s[0m\n\n" $@

clean:
	rm -rf $(OBJS) $(INSTALL_DIR)/$(TARGET)
	@printf "\nClean Success : [32m%s[0m\n\n" "$(OBJS) $(TARGET)"
