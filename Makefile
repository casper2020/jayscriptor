#
# Copyright (c) 2011-2020 Cloudware S.A. All rights reserved.
#

THIS_DIR := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
ifeq (jayscriptor, $(shell basename $(THIS_DIR)))
  PACKAGER_DIR := $(abspath $(THIS_DIR)/../casper-packager)
else
  PACKAGER_DIR := $(abspath $(THIS_DIR)/..)
endif

include $(PACKAGER_DIR)/common/c++/settings.mk

REL_DATE             := $(shell date -u)
REL_VARIANT          ?= 0
REL_NAME             ?= jayscriptor$(EXECUTABLE_SUFFIX)

PROJECT_SRC_DIR     := $(ROOT_DIR)/jayscriptor
EXECUTABLE_SUFFIX   ?=
EXECUTABLE_NAME     ?= jayscriptor$(EXECUTABLE_SUFFIX)
EXECUTABLE_MAIN_SRC := jayscriptor.cc
LIBRARY_NAME        :=
VERSION             ?= $(shell cat $(PACKAGER_DIR)/$(EXECUTABLE_NAME)/version)
CHILD_CWD           := $(THIS_DIR)
CHILD_MAKEFILE      := $(MAKEFILE_LIST)

EV_DEP_ON           := true

###################
# THIS TOOL SOURCE
###################

# $(PROJECT_SRC_DIR)

JAYSCRIPTOR_CC_SRC :=                       \
	src/casper/v8/context.cc                \
	src/casper/v8/singleton.cc              \
	src/casper/java/ast_node.cc             \
	src/casper/java/fake_java_expression.cc \
	src/casper/java/ast.cc                  \
	src/casper/scanner.cc

JAYSCRIPTOR_YY_SRC := \
	src/casper/java/fake_java_parser.yy

JAYSCRIPTOR_RL_SRC := \
	src/casper/java/fake_java_scanner.rl

##########
# SOURCE
##########

BISON_SRC := $(JAYSCRIPTOR_YY_SRC)
RAGEL_SRC := $(JAYSCRIPTOR_RL_SRC)

C_SRC  :=
CC_SRC := \
	$(JAYSCRIPTOR_CC_SRC)

OBJECTS :=           \
	$(C_SRC:.c=.o)      \
	$(CC_SRC:.cc=.o)    \
	$(RAGEL_SRC:.rl=.o) \
	$(BISON_SRC:.yy=.o)

INCLUDE_DIRS += \
	-I $(PROJECT_SRC_DIR)/src

# common makefile
include $(PACKAGER_DIR)/common/c++/common.mk

# dependencies
set-dependencies: casper-connectors-v8-dep-on v8-dep-on

# this is a command line tool
all: exec

# version
version:
	@echo " $(LOG_COMPILING_PREFIX) - patching $(PROJECT_SRC_DIR)/src/version.h"
	@cp -f $(PROJECT_SRC_DIR)/src/version.tpl.h $(PROJECT_SRC_DIR)/src/version.h
	@sed -i.bak s#"@b.n.s@"#${EXECUTABLE_SUFFIX}#g $(PROJECT_SRC_DIR)/src/version.h
	@sed -i.bak s#"x.x.x"#$(VERSION)#g $(PROJECT_SRC_DIR)/src/version.h
	@sed -i.bak s#"n.n.n"#$(REL_NAME)#g $(PROJECT_SRC_DIR)/src/version.h
	@sed -i.bak s#"d.d.d"#"$(REL_DATE)"#g $(PROJECT_SRC_DIR)/src/version.h
	@sed -i.bak s#"v.v.v"#"$(REL_VARIANT)"#g $(PROJECT_SRC_DIR)/src/version.h
	@rm -f $(PROJECT_SRC_DIR)/src/version.h.bak
