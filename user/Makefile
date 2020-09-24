CXX =			clang++

INSTALL_DIR =		../bin

CXXFLAGS =		-g -W -Wall -Wextra -std=c++14 $(INCLUDE_DIRS)
LDLIBS =		-lmautil $(shell pkg-config --libs gtkmm-3.0)
LDFLAGS =		-L$(INSTALL_DIR) -Wl,--rpath=./

LIB_UTILITY_DIR =	./lib_utility

INCLUDE_DIR =		./src ./ ../ ./lib_utility/include
INCLUDE_DIRS =		$(INCLUDE_DIR:%=-I%) \
			$(shell pkg-config --cflags-only-I gtkmm-3.0)

SOURCE_DIR =		./src
SOURCES =		agent_data.cc		\
			agent_main.cc		\
			agent_window.cc		\
			button_box.cc		\
			main.cc			\
			proc_search_dialog.cc	\
			text_window.cc

OBJECTS =		$(SOURCES:%.cc=$(SOURCE_DIR)/%.o)

TARGET =		maOpen

.SUFFIXES:		.cc .o

all: make_lib $(TARGET)

make_lib:
	$(MAKE) -C $(LIB_UTILITY_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(INSTALL_DIR)/$(TARGET) $? $(LDFLAGS) $(LDLIBS) $(CXXFLAGS)

.cc .o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(MAKE) -C $(LIB_UTILITY_DIR) clean
	rm -rf $(SOURCE_DIR)/*.o
	rm -rf $(INSTALL_DIR)/$(TARGET)
