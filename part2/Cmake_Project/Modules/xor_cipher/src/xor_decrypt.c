#include "xor_cipher.h"

void xor_decrypt(char *text, char key) {
    while (*text) {
        *text = *text ^ key;
        text++;
    }
}
