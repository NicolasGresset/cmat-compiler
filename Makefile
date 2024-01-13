TARGET = main

SRCDIR   := src
OBJDIR   := obj
BINDIR   := bin
TESTDIR  := test
INCLUDE_PATH := ./include
LEXDIR   := flex
BISONDIR := bison

CFLAGS := -Wall -Wextra -g
LDLIBS := -lfl

LEXSOURCE = lexer
BISONSOURCE = parser
TESTSOURCE = test

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	gcc -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete"

$(TESTDIR)/$(TESTSOURCE): $(OBJECTS)
	mkdir -p $(TESTDIR)
	gcc -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete for test file"

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	mkdir -p $(OBJDIR)
	gcc -o $@ -c $< $(CFLAGS) $(LDLIBS) -I$(INCLUDE_PATH)/


$(SRCDIR)/$(BISONSOURCE).c: $(BISONDIR)/$(BISONSOURCE).y
	bison --header=$(INCLUDE_PATH)/$(BISONSOURCE).h -t -o $@ $< -Wcounterexamples
	@echo "Linking complete for bison file"

$(SRCDIR)/$(LEXSOURCE).c: $(LEXDIR)/$(LEXSOURCE).lex $(SRCDIR)/$(BISONSOURCE).c
	flex --header-file=$(INCLUDE_PATH)/$(LEXSOURCE).h -o $@ $<
	@echo "Linking complete for flex file"

dir:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(SRCDIR)
	mkdir -p $(INCLUDE_PATH)
	mkdir -p $(LEXDIR)
	mkdir -p $(BISONDIR)

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/*.o
	rm -f $(BINDIR)/$(TARGET)
	touch $(SRCDIR)/$(LEXSOURCE).c
	touch $(BISONDIR)/$(BISONSOURCE).y
	touch $(LEXDIR)/$(LEXSOURCE).lex
