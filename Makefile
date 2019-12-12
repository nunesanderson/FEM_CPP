#==============================
# Compiler
CC := g++ 

#==============================
# Build
BUILDDIR := build

#==============================
# Build
TARGET := bin/FEM

#==============================
# Source files
SRCEXT := cpp
SRCDIR := src
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

#==============================
# Object files
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

DEPS := $(OBJECTS:.o=.d)
#==============================
# Flags
# Compiler flags
CFLAGS = -I${BLAS_INC} -g -std=c++11 -march=native -MMD -MP

# Linker flags
LDFLAGS = -L${BLAS_LIB} -lgsl -lgslcblas -lopenblas

#==============================
#Link
$(TARGET): $(OBJECTS)
	@echo "========================================="
	@echo "Linking"
	${CXX} $^ -o $(TARGET)  ${LDFLAGS}

# Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " ==========================="
	@echo " Compiling: $@ $<"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

#==============================
# Include the dependency files
-include $(DEPS)

#==============================
#Clear the directory
clean:
	@echo "========================================="
	@echo " Cleaning"; 
	$(RM) -rv $(BUILDDIR) $(TARGET)

#==============================
#Run the binary
run:
	@echo "========================================="
	@echo " Running"; 
	bash -c "./$(TARGET)"

.PHONY: clean