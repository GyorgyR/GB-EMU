CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner
TESTBINDIR := test/bin
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -std=c++11 -Og #-O3 #-Ofast
LIB := -lSDL2main -lSDL2  #-pthread
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

analyze: $(OBJECTS)
	CC := clang --analyze
	$(CC) $^ -o $(TARGET) $(LIB)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) $(SRCDIR)/Helper.cpp test/HelperTests.cpp -o $(TESTBINDIR)/helperTests.bin && $(TESTBINDIR)/helperTests.bin
	@echo "===================================================================="
	$(CC) $(CFLAGS) $(SRCDIR)/Helper.cpp $(SRCDIR)/RegisterBank.cpp test/RegisterBankTests.cpp -o $(TESTBINDIR)/regTests.bin && $(TESTBINDIR)/regTests.bin
	@echo "===================================================================="
	$(CC) $(CFLAGS) $(SRCDIR)/RGBA.cpp $(SRCDIR)/Configuration.cpp $(SRCDIR)/Window.cpp test/WindowTests.cpp -o $(TESTBINDIR)/windowTests.bin $(LIB) && $(TESTBINDIR)/windowTests.bin

.PHONY: clean