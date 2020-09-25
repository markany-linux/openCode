CC	= gcc

INSTALL_DIR	=	$(shell pwd)/../../bin

COMMON_HOME	=	$(shell pwd)/../..
UTIL_HOME	=	$(shell pwd)/../lib_utility
HEADER_HOME	=	$(shell pwd)/../headers

INCS		=	$(COMMON_HOME) $(UTIL_HOME) $(HEADER_HOME)

INCLUDES	=	$(INCS:%=-I%)

GTK_FKLAGS	=	$(shell pkg-config --cflags --libs gtk+-3.0)
CFLAGS		=	-Wall $(INCLUDES) $(GTK_FKLAGS) -lmautil -ldl

LIB_UTIL	= -L$(INSTALL_DIR) -lmautil -Wl,-rpath $(INSTALL_DIR)

LIBS = $(LIB_UTIL)

SRCS		=	code_main.c				\
				code_button_handler.c	\
				code_gui_init.c			\
				code_helper.c			\
				code_init.c				\
				code_search_dialog.c

OBJS	= $(SRCS:%.c=%.o)
TARGET	= maCopen

.SUFFIXES: .c .o


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)
	cp $(TARGET) $(INSTALL_DIR)
	@printf "\nBuild Success : [32m%s[0m\n\n" $@

clean:
	rm -rf $(OBJS) $(INSTALL_DIR)/$(TARGET)
	@printf "\nClean Success : [32m%s[0m\n\n" "$(OBJS) $(TARGET)"

