CXX =			g++

LDLIBS =		$(shell pkg-config --libs gtkmm-3.0)
CXXFLAGS =		-g -W -Wall -Wextra -Werror -std=c++14 $(INCLUDE_DIRS)

INCLUDE_DIR =	./src
INCLUDE_DIRS =	$(INCLUDE_DIR:%=-I%) $(shell pkg-config --cflags-only-I gtkmm-3.0)

SOURCE_DIR =	./src
SOURCES =		button_box.cpp		\
				main.cpp			\
				main_window.cpp		\
				subtitle_box.cpp


OBJECTS =		$(SOURCES:%.cpp=$(SOURCE_DIR)/%.o)

INSTALL_DIR =	./bin
TARGET =		maOpen

.SUFFIXES:	.cpp .o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(INSTALL_DIR)/$(TARGET) $? $(LDLIBS) $(CXXFLAGS)

.cpp .o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(SOURCE_DIR)/*.o
	rm -rf $(INSTALL_DIR)/$(TARGET)
