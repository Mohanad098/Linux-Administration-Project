#include "xor_cipher.h"

void xor_encrypt(char *text, char key) {
    while (*text) {
        *text = *text ^ key;
        text++;
    }
}
