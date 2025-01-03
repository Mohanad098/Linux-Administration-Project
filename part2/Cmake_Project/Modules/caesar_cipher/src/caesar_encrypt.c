#include "caesar_cipher.h"

void caesar_encrypt(char *text, int key) {
    while (*text) {
        if (*text >= 'a' && *text <= 'z') {
            *text = (*text - 'a' + key) % 26 + 'a';
        } else if (*text >= 'A' && *text <= 'Z') {
            *text = (*text - 'A' + key) % 26 + 'A';
        }
        text++;
    }
}
