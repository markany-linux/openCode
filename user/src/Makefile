CXX =			clang++

PROJECT_DIR =		../..

INSTALL_DIR =		$(PROJECT_DIR)/bin

CXXFLAGS =		-O2 -W -Wall -Wextra -std=c++14 $(INCLUDE_DIR)
LDLIBS =		-lmautil $(shell pkg-config --libs gtkmm-3.0)
LDFLAGS =		-L$(INSTALL_DIR) -Wl,--rpath=.

LIB_UTILITY_DIR =	../lib_utility

INCS =			$(PROJECT_DIR) $(LIB_UTILITY_DIR)/include
INCLUDE_DIR =		$(INCS:%=-I%) \
			$(shell pkg-config --cflags-only-I gtkmm-3.0)

OBJECT_DIR =		./build
SOURCES =		agent_data.cc		\
			agent_main.cc		\
			agent_window.cc		\
			button_box.cc		\
			main.cc			\
			proc_search_dialog.cc	\
			text_window.cc

OBJECTS =		$(SOURCES:%.cc=$(OBJECT_DIR)/%.o)
DEPENDS =		$(OBJECTS:%.o=%.d)

TARGET =		maOpen

all: lib dir $(TARGET)

lib:
	$(MAKE) -C $(LIB_UTILITY_DIR)

dir:
	@mkdir -p $(OBJECT_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(INSTALL_DIR)/$@ $? $(LDFLAGS) $(LDLIBS)
	@printf "\nBuild Success : \e[32m%s\e[0m\n\n" $(TARGET)

$(OBJECT_DIR)/%.o: %.cc Makefile
	$(CXX) -MMD -MP -c $< -o $@ $(CXXFLAGS)

clean:
	$(MAKE) -C $(LIB_UTILITY_DIR) clean
	rm -rf $(OBJECTS) $(DEPENDS) $(INSTALL_DIR)/$(TARGET)
	@printf "\nClean Success : \e[32m%s\e[0m\n\n" "$(OBJECTS) $(DEPENDS) $(TARGET)"

-include $(DEPENDS)
