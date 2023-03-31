# ----------------------------
# Set NAME to the program name
# Set DEBUGMODE to "DEBUG" to use debug functions
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ** Add all shared library names to L **
# ----------------------------

NAME        ?= LUDO
DEBUGMODE   ?= NDEBUG
COMPRESSED  ?= YES
COMPRESSED_MODE = zx0
ICON        ?= iconc.png
DESCRIPTION ?= "Ludo"
ARCHIVED ?= YES

L ?= graphx

# ----------------------------
# Specify source and output locations
# ----------------------------

SRCDIR ?= src
OBJDIR ?= obj
BINDIR ?= bin
GFXDIR ?= src/gfx

# ----------------------------
# Use OS helper functions (Advanced)
# ----------------------------

USE_FLASH_FUNCTIONS ?= YES


include $(CEDEV)/meta/makefile.mk
