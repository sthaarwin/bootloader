#ifndef UTIL_H
#define UTIL_H

void memory_copy(char *source, char *dest, int nbytes)
{
    int i;
    for (i = 0; i < nbytes; i++)
    {
        *(dest + i) = *(source + i);
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

#endif