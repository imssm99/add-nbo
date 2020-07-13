#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include "sum.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 0;
    }

    FILE *fp1, *fp2;

    if((fp1 = fopen(argv[1], "rb")) == NULL || (fp2 = fopen(argv[2], "rb")) == NULL)
    {
        printf("Error in opening files\n");
        return 0;
    }

    uint8_t buffer[4];
    uint32_t *p1, *p2;
    uint32_t num1, num2, result;

    fread(buffer, sizeof(uint8_t), 4, fp1);
    p1 = reinterpret_cast<uint32_t*>(buffer);
    num1 = ntohl(*p1);

    fread(buffer, sizeof(uint8_t), 4, fp2);
    p2 = reinterpret_cast<uint32_t*>(buffer);
    num2 = ntohl(*p2);

    result = sum(num1, num2);

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", num1, num1, num2, num2, result, result);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
