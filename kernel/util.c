#include "util.h"

void memory_copy(char *source, char *dest, int nbytes)
{
    int i;
    for (i = 0; i < nbytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

int string_length(char s[])
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = string_length(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char *int_to_string(int v, char *buffer, int radix_base)
{
    static char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *p = buffer;
    unsigned int n = (v < 0 && radix_base == 10) ? -v : (unsigned int)v;

    while (n >= radix_base)
    {
        *p++ = table[n % radix_base];
        n /= radix_base;
    }
    *p++ = table[n];
    if (v < 0 && radix_base == 10)
        *p++ = '-';

    *p = '\0';
    return buffer;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
