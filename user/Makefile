CXX =			g++

LDLIBS =		$(shell pkg-config --libs gtkmm-3.0)
CXXFLAGS =		-g -W -Wall -Wextra -Werror -std=c++14

INCLUDE_DIR =	./src ../common $(shell pkg-config --cflags-only-I gtkmm-3.0)
INCLUDE_DIRS =	$(INCLUDE_DIR:%=-I%)

SOURCE_DIR =	./src
SOURCES =		

OBJECTS =		$(SOURCES:%.cpp=$(SOURCE_DIR)/%.o)

INSTALL_DIR =	./bin
TARGET =		test

.SUFFIXES:	.cpp .o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(INSTALL_DIR)/$(TARGET) $? $(LDLIBS) $(CXXFLAGS)

.cpp .o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -rf $(SOURCE_DIR)/*.o
	rm -rf $(INSTALL_DIR)/$(TARGET)
