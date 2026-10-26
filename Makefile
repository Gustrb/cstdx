CC      := clang
AR      := ar
LD      := ld
CFLAGS  := -I. -std=c23 -Wall -Werror -Wextra -pedantic -g
BUILD   := build
OBJDIR  := $(BUILD)/obj
TESTDIR := $(BUILD)/tests
LIB     := $(BUILD)/libcstdx.a

# Unity test framework (vendored, see vendor/unity/README.md)
UNITY_DIR := vendor/unity
UNITY_OBJ := $(BUILD)/vendor/unity.o
TEST_CFLAGS := $(CFLAGS) -I$(UNITY_DIR)

# A package is any packages/<name>/ that contains at least one .c file.
PKGS := $(sort $(notdir $(patsubst %/,%,$(dir $(wildcard packages/*/*.c)))))

# build/<pkg>.o -- one bundled object per package
PKG_OBJS := $(foreach p,$(PKGS),$(BUILD)/$(p).o)

.PHONY: all clean test $(addprefix test-,$(PKGS))

all: $(LIB)

# ---- the one big file: every package object in a single archive ----
$(LIB): $(PKG_OBJS)
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

# Unity is third-party: build it without our -Werror-grade warnings.
$(UNITY_OBJ): $(UNITY_DIR)/unity.c $(UNITY_DIR)/unity.h $(UNITY_DIR)/unity_internals.h
	@mkdir -p $(@D)
	$(CC) -I$(UNITY_DIR) -std=c11 -g -c $< -o $@

# ---- per-package rules, generated for each package ----
# $(1) = package name
define PKG_RULES
$(1)_SRCS := $$(wildcard packages/$(1)/*.c)
$(1)_OBJS := $$(patsubst packages/$(1)/%.c,$(OBJDIR)/$(1)/%.o,$$($(1)_SRCS))

# each source file -> its own .o
$(OBJDIR)/$(1)/%.o: packages/$(1)/%.c
	@mkdir -p $$(@D)
	$$(CC) $$(CFLAGS) -MMD -MP -c $$< -o $$@

# partial link: all of the package's .o files -> build/$(1).o
$(BUILD)/$(1).o: $$($(1)_OBJS)
	@mkdir -p $$(@D)
	$$(LD) -r -o $$@ $$^

-include $$($(1)_OBJS:.o=.d)

# ---- tests: tests/$(1)/*.c, one binary per test file ----
$(1)_TEST_SRCS := $$(wildcard tests/$(1)/*.c)
$(1)_TEST_BINS := $$(patsubst tests/$(1)/%.c,$(TESTDIR)/$(1)/%,$$($(1)_TEST_SRCS))

$(TESTDIR)/$(1)/%: tests/$(1)/%.c $(LIB) $(UNITY_OBJ)
	@mkdir -p $$(@D)
	$$(CC) $$(TEST_CFLAGS) $$< $(UNITY_OBJ) $(LIB) -o $$@

test-$(1): $$($(1)_TEST_BINS)
	@if [ -z "$$($(1)_TEST_BINS)" ]; then echo "no tests for $(1)"; exit 0; fi
	@fail=0; for t in $$(filter $(TESTDIR)/%,$$^); do \
		"$$$$t" || fail=1; \
	done; exit $$$$fail
endef

$(foreach p,$(PKGS),$(eval $(call PKG_RULES,$(p))))

test: $(addprefix test-,$(PKGS))

clean:
	rm -rf $(BUILD)
