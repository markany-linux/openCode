CXX =			clang++-10

# glibmm에서 Copy Constructor Deprecated Copy Warning이 뜨는 문제가 있어
# 해당 Warning 제외
CXXFLAGS =		-W -Wall -Wextra -Werror -Wno-deprecated-copy -std=c++14 $(INCLUDE_DIRS)
LDLIBS =		$(shell pkg-config --libs gtkmm-3.0)

INCLUDE_DIR =	./src ./
INCLUDE_DIRS =	$(INCLUDE_DIR:%=-I%) $(shell pkg-config --cflags-only-I gtkmm-3.0)

SOURCE_DIR =	./src
SOURCES =		agent_main.cc		\
				agent_window.cc		\
				button_box.cc		\
				main.cc				\
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

