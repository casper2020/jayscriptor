
INCLUDE_DIRS = -I . -I ./osal/src

BISON_OBJECTS=./casper/java/fake_java_parser.o
RAGEL_OBJECTS=./casper/java/fake_java_scanner.o

INTERM = casper/java/fake_java_parser.hh casper/java/fake_java_parser.cc

OBJECTS = casper/java/fake_java_parser.o      \
					jayscriptor.o 											\
					casper/java/fake_java_scanner.o     \
					casper/scanner.o                    \
					casper/java/fake_java_expression.o  \
					casper/java/ast.o                   \
					casper/java/ast_node.o

PLATFORM:=$(shell uname -s)
ifeq (Darwin, $(PLATFORM))
  YACC=/usr/local/Cellar/bison/3.0.4_1/bin/bison
else
  YACC=bison
endif

jayscriptor: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)


RAGEL=ragel
DEFINES = -D CASPER_NO_ICU
CFLAGS = $(INCLUDE_DIRS) $(DEFINES) -c -g
CXXFLAGS = $(INCLUDE_DIRS) -std=c++11 -Wall $(DEFINES) -c -g

# bison
%.cc:%.yy
	@echo "* [$(TARGET)] bison  $< ..."
	$(YACC) $< -v --locations -o $@

# ragel
%.cc:%.rl
	@echo "* [$(TARGET)] rl  $< ..."
	$(RAGEL) $(RAGEL_FLAGS) $< -G2 -o $@

# c++
.c.o:
	@echo "* [$(TARGET)] c   $< ..."
	$(C) $(CFLAGS) $< -o $@

# c++
.cc.o:
	@echo "* [$(TARGET)] cc  $< ..."
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(INTERM)

ragel: $(RAGEL_OBJECTS)
	@echo "* RAGEL done"

bison: $(BISON_OBJECTS)
	@echo "* BISON done"
