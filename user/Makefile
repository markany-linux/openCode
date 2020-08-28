CXX =			clang++-10

LDLIBS =		$(shell pkg-config --libs gtkmm-3.0)
# glibmm에서 Copy Constructor Deprecated Copy Warning이 뜨는 문제가 있어 해당 Warning 제외
CXXFLAGS =		-g -W -Wall -Wextra -Werror -Wno-deprecated-copy -std=c++14 $(INCLUDE_DIRS)

INCLUDE_DIR =	./src
INCLUDE_DIRS =	$(INCLUDE_DIR:%=-I%) $(shell pkg-config --cflags-only-I gtkmm-3.0)

SOURCE_DIR =	./src
SOURCES =		button_box.cc		\
				contents_box.cc		\
				main.cc			\
				main_window.cc		\
				subtitle_box.cc	\
				text_window.cc		\


OBJECTS =		$(SOURCES:%.cc=$(SOURCE_DIR)/%.o)

INSTALL_DIR =	./bin
TARGET =		maOpen

.SUFFIXES:	.cc .o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(INSTALL_DIR)/$(TARGET) $? $(LDLIBS) $(CXXFLAGS)

.cc .o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(SOURCE_DIR)/*.o
	rm -rf $(INSTALL_DIR)/$(TARGET)
