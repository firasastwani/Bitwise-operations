#include <stdio.h> 
#include <stdlib.h> // atoi, atof, atol
#include <string.h>



// Converts a decimal number to a binary string
void numToBinaryString(int num, char *binaryStr) {
    int index = 0;
    while (num > 0) {
        binaryStr[index++] = (num % 2) + '0';
        num /= 2;
    }
    binaryStr[index] = '\0';
    // Reverse the string to get the correct binary representation
    for (int i = 0; i < index / 2; i++) {
        char temp = binaryStr[i];
        binaryStr[i] = binaryStr[index - i - 1];
        binaryStr[index - i - 1] = temp;
    }
}



// Pads the shorter binary string with leading zeros
void padBinaryStrings(char *binaryStr1, char *binaryStr2) {
    int len1 = strlen(binaryStr1);
    int len2 = strlen(binaryStr2);
    int maxLen = len1 > len2 ? len1 : len2;

    char paddedStr1[33] = {0};
    char paddedStr2[33] = {0};

    // Pad binaryStr1
    for (int i = 0; i < maxLen - len1; i++) {
        paddedStr1[i] = '0';
    }
    strcpy(paddedStr1 + (maxLen - len1), binaryStr1);

    // Pad binaryStr2
    for (int i = 0; i < maxLen - len2; i++) {
        paddedStr2[i] = '0';
    }
    strcpy(paddedStr2 + (maxLen - len2), binaryStr2);

    // Copy back to original strings
    strcpy(binaryStr1, paddedStr1);
    strcpy(binaryStr2, paddedStr2);
}

// Converts a binary string to a decimal number
int binaryStringToNum(const char *binaryStr) {
    int num = 0;
    int length = strlen(binaryStr);

    int multiplier = 1;     

    for (int i = 0; i < length; i++) {
        if (binaryStr[length - i - 1] == '1') {
            num += multiplier;
        }
        multiplier *= 2;    
    }
    return num;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <binary1> <operator> <binary2>\n", argv[0]);
        return 1;
    }

    char *sign = argv[2];

    char binaryStr1[33] = {0};
    char binaryStr2[33] = {0};

    // Copy the input binary strings to binaryStr1 and binaryStr2
    strncpy(binaryStr1, argv[1], 32);
    strncpy(binaryStr2, argv[3], 32);

    padBinaryStrings(binaryStr1, binaryStr2);

    // Convert padded binary strings to integers for bitwise operations
    int num1 = binaryStringToNum(binaryStr1);
    int num2 = binaryStringToNum(binaryStr2);

    int result;
    if (strcmp(sign, "-and") == 0) {
        result = num1 & num2;
    } else if (strcmp(sign, "-or") == 0) {
        result = num1 | num2;
    } else if (strcmp(sign, "-xor") == 0) {
        result = num1 ^ num2;
    } else {
        fprintf(stderr, "Invalid operator: %s\n", sign);
        return 1;
    }

    char resultBinaryStr[33] = {0};
    numToBinaryString(result, resultBinaryStr);
    padBinaryStrings(binaryStr1, resultBinaryStr);

    int maxLen = strlen(binaryStr1);

    printf("%s %s %s evaluates to %s using bit strings of length %d\n", binaryStr1, sign, binaryStr2, resultBinaryStr, maxLen);
    printf("%d %s %d evaluates to %d using unsigned %d-bit integers\n", binaryStringToNum(binaryStr1), sign, binaryStringToNum(binaryStr2), result, maxLen);
}


