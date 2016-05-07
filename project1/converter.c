/* Mat Sharff
 * HW 1
 * mrsharff
 */

#include <stdio.h>


int hexToDec(char char1) {
    char char2;
    int value;

    scanf("%c", &char2);
    value = (((char1 - '0') * 16) + (char2 - '0'));
    return value;
}

int alphToDec(char character) {
    return character;
}

int binToDec(char character) {
    int i, value, product;
    value = 0;
    for (i = 7; i >= 0; i--) {
        product = (1 << i);
        if (character == '1') {
            value += product;
        }
        if (i > 0) {
            scanf("%c", &character);
        }
    }
    return value;
}

char decToAlph(int the_number) {
    return the_number;
}

void decToBin(int the_number) {
    int i, product;
    for (i = 7; i >= 0; i--) {
        product = (1 << i);
        if (the_number >= product) {
            the_number = the_number - product;
            printf("1");
        } else {
            printf("0");
        }
    }
}

void decToHex(int the_number) {
    printf("%x", decToAlph(the_number));
}

int main(void)
{
    char input_type, output_type, input;

    printf("Welcome to the coder.\n");
    printf("Choose Input (H,A,B,Q): ");
    scanf(" %c", &input_type);

    while (input_type != 'Q') {

        printf("Choose Output (H,A,B): ");
        scanf(" %c", &output_type);
        printf("Enter your input with a $ at the end.\n");

        if (input_type == output_type) { /* check if we even need to convert */
            scanf(" %c", &input);         /* print if we don't */

            while (input != '$') {
                printf("%c", input);
                scanf("%c", &input);
            }

        printf("\n");

        } else {
            switch (input_type) {
            case 'H':
                switch (output_type) {
                case 'A':
                    /* Hex to Alph */
                    scanf(" %c", &input);

                    while (input != '$') {
                        printf("%c", decToAlph(hexToDec(input)));
                        scanf("%c", &input);
                    }
                    break;
                case 'B':
                    /* Hex to Binary */
                    scanf(" %c", &input);
                    while (input != '$') {
                        decToBin(hexToDec(input));
                        scanf("%c", &input);
                    }
                    break;
                }
                break;
            case 'A':
                switch (output_type) {
                case 'H':
                    scanf(" %c", &input);

                    while (input != '$') {
                        printf("%x", input);
                        scanf("%c", &input);
                    }
                    break;
                case 'B':
                    scanf(" %c", &input);

                    while (input != '$') {
                        decToBin(alphToDec(input));
                        scanf("%c", &input);
                    }
                    break;
                }
                break;
            case 'B':
                switch (output_type) {
                case 'A':
                    scanf(" %c", &input);

                    while (input != '$') {
                        printf("%c", decToAlph(binToDec(input)));
                        scanf("%c", &input);
                    }
                    break;
                case 'H':
                    scanf(" %c", &input);

                    while (input != '$') {
                        decToHex(binToDec(input));
                        scanf("%c", &input);
                    }
                    break;
                }
                break;
            default:
                printf("Invalid input type.\n"); /* debug */
                break;
            }
            printf("\n");
        }
        printf("Choose Input (H,A,B,Q): ");
        scanf(" %c", &input_type);
    }

    return 0;
}
