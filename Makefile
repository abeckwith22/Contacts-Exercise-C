CXX=clang
CXXFLAGS=

SRC=src/app.c src/Contacts.c
OBJ=$(SRC:.c=.o)

TARGET=target.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
