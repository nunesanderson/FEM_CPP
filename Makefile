CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/FEM
INCDIR:=include
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := -lgsl -lgslcblas
INC := -I include

DEPS := $(OBJS:.o=.d)

-include $(DEPS)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -MMD -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -rv $(BUILDDIR) $(TARGET)"; $(RM) -rv $(BUILDDIR) $(TARGET)

run:
	@echo " Running..."; 
	@echo "bash -c bin/FEM" ; bash -c "bin/FEM"

.PHONY: clean