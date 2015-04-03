# project name (generate executable with this name)
TARGET   = libmthread.a

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -g

LINKER   = ar rcs
# linking flags here
LFLAGS   = 

# change these to set the proper directories where each files shoould be
SRCDIR   = src
INCDIR	 = include
OBJDIR   = bin
BINDIR   = lib

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

all: $(OBJECTS) $(BINDIR)/$(TARGET) test

test:
	gcc -g -o $(BINDIR)/mthread.out $(OBJECTS)
	@echo test created!

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "'$(BINDIR)/$(TARGET)' generated!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@
	@echo "Compiled '"$<"' successfully!"

.PHONEY: clean
clean: remove
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove:
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
