CC	= gcc

INSTALL_DIR	=	$(shell pwd)/../bin

COMMON_HOME	=	$(shell pwd)/../..

INCS		=	$(COMMON_HOME)

INCLUDES	=	$(INCS:%=-I%)

CFLAGS		=	-Wall $(INCLUDES) -ldl -fPIC
LIBFLAGS	=	-shared

SRCS		=	file_check.c

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
