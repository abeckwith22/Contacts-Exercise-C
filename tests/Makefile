CXX=clang
CXXFLAGS=-lcmocka

SRC=../src/Contacts.c Contacts_test.c
OBJ=$(SRC:.c=.o)

TARGET=contacts_tests.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
