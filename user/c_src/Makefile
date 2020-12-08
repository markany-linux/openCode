CC		= 	gcc

INSTALL_DIR	= 	$(COMMON_HOME)/bin
OBJECT_DIR	=	./build

COMMON_HOME	= 	../..
UTIL_HOME	= 	../lib_utility
HEADER_HOME	= 	../headers

INCS		= 	$(COMMON_HOME) $(UTIL_HOME)/include $(HEADER_HOME)

INCLUDES	= 	$(INCS:%=-I%)

GTK_INCLUDE	= 	$(shell pkg-config --cflags-only-I gtk+-3.0)
GTK_LIBS	= 	$(shell pkg-config --libs gtk+-3.0)
CFLAGS		= 	-Wall $(INCLUDES) $(GTK_INCLUDE)
LDFLAGS		=	-L$(INSTALL_DIR) -Wl,--rpath=.
LDLIBS		= 	$(GTK_LIBS) -lopencode -ldl

SRCS		= 	code_main.c		\
			code_button_handler.c	\
			code_gui_init.c		\
			code_helper.c		\
			code_init.c		\
			code_search_dialog.c

OBJS	= $(SRCS:%.c=$(OBJECT_DIR)/%.o)
DEPS	= $(OBJS:%.o=%.d)
TARGET	= maCopen

all: lib dir $(TARGET)

lib:
	$(MAKE) -C $(UTIL_HOME)

dir:
	@mkdir -p $(OBJECT_DIR)

$(TARGET): $(OBJS)
	$(CC) -o $(INSTALL_DIR)/$@ $? $(LDFLAGS) $(LDLIBS)
	@printf "\nBuild Success : [32m%s[0m\n\n" $@

clean:
	$(MAKE) -C $(UTIL_HOME) clean
	rm -rf $(OBJS) $(DEPS) $(INSTALL_DIR)/$(TARGET)
	@printf "\nClean Success : [32m%s[0m\n\n" "$(OBJS) $(DEPS) $(TARGET)"

$(OBJECT_DIR)/%.o: %.c Makefile
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

-include $(DEPS)
