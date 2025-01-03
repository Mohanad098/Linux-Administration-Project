# Main Directories
#ROOT_DIR =   #Not used here
APP_DIR = .
MODULES_DIR = ../Modules

# Modules Directories
CAESAR_CIPHER_DIR = $(MODULES_DIR)/caesar_cipher
XOR_CIPHER_DIR = $(MODULES_DIR)/xor_cipher

# Modules Include Directories
CAESAR_CIPHER_INC_DIR = $(CAESAR_CIPHER_DIR)/inc
XOR_CIPHER_INC_DIR = $(XOR_CIPHER_DIR)/inc

# Modules Source Directories
CAESAR_CIPHER_SRC_DIR = $(CAESAR_CIPHER_DIR)/src
XOR_CIPHER_SRC_DIR = $(XOR_CIPHER_DIR)/src

# Application Directories
APP_OUT_DIR = $(APP_DIR)/out
APP_OBJ_DIR = $(APP_OUT_DIR)/gen
APP_LIB_DIR = $(APP_OUT_DIR)/libs
APP_BIN = $(APP_DIR)/output

# Modules Source files
CAESAR_CIPHER_SRC = $(CAESAR_CIPHER_SRC_DIR)/caesar_encrypt.c $(CAESAR_CIPHER_SRC_DIR)/caesar_decrypt.c
XOR_CIPHER_SRC = $(XOR_CIPHER_SRC_DIR)/xor_encrypt.c $(XOR_CIPHER_SRC_DIR)/xor_decrypt.c

# Modules Object files
CAESAR_CIPHER_OBJ = $(APP_OBJ_DIR)/caesar_encrypt.o $(APP_OBJ_DIR)/caesar_decrypt.o
XOR_CIPHER_OBJ = $(APP_OBJ_DIR)/xor_encrypt.o $(APP_OBJ_DIR)/xor_decrypt.o

# Modules Library files
CAESAR_CIPHER_LIB = $(APP_LIB_DIR)/libcaesar_cipher.a
XOR_CIPHER_LIB = $(APP_LIB_DIR)/libxor_cipher.so

# Application Source files
APP_SRC = $(APP_DIR)/app.c

# Application object files
APP_OBJ = $(APP_OBJ_DIR)/app.o

# Compiling commands
CC = gcc
AR = ar

# Compiler flags
CFLAGS = -I$(CAESAR_CIPHER_INC_DIR) -I$(XOR_CIPHER_INC_DIR)

# Create directories if they don't exist
$(APP_OUT_DIR) $(APP_OBJ_DIR) $(APP_LIB_DIR):
	mkdir -p $@

include $(CAESAR_CIPHER_DIR)/caeser_cipher.mk
include $(XOR_CIPHER_DIR)/xor_cipher.mk

$(APP_OBJ): $(APP_SRC) | $(APP_OBJ_DIR)
	$(CC) $(CFLAGS) -c $(APP_SRC) -o $(APP_OBJ)

# Ensure the libs directory exists before creating the libraries
$(CAESAR_CIPHER_LIB): | $(APP_LIB_DIR)
$(XOR_CIPHER_LIB): | $(APP_LIB_DIR)

all: $(APP_OBJ) $(CAESAR_CIPHER_LIB) $(XOR_CIPHER_LIB)
	$(CC) $(APP_OBJ) -L$(APP_LIB_DIR) -lcaesar_cipher -lxor_cipher -o $(APP_BIN)

# Clean up
clean:
	rm -rf $(APP_OUT_DIR)
