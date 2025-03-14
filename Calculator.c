//Ebrar Çelikkaya , 150123067 , basic Calculator with macros  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define add(x, y) ((x) + (y))
#define sub(x, y) ((x) - (y))

char *getRest(char *str, int i) {
    if (i < 0 || i >= strlen(str)) {
        return NULL;
    }

    int length = strlen(str) - i;
    char *newStr = (char *)malloc((length + 1) * sizeof(char)); // +1 for the null char

    if (newStr == NULL) { // if memory can't be allocated
        return NULL;
    }

    strcpy(newStr, str + i); //copies from i index to end 
   
    return newStr;
}

int calculate(char *str) {
    int index = 0, num = 0, result = 0;
    char preSign = '+'; // first element will be recorded as result (0)+ itself

    while (index < strlen(str)) {
        char ch = str[index];
        index++;

        if (isdigit(ch)) {
            num = ch - '0';
            while (index < strlen(str) && isdigit(str[index])) {
                num = num * 10 + (str[index] - '0');
                index++;
            }

            if (preSign == '+') {
                result = add(result, num);
            } else if (preSign == '-') {
                result = sub(result, num);
            }
        } else if (ch == '+' || ch == '-') {
            preSign = ch;
        } else if (ch == '(') {
            int subResult = calculate(getRest(str, index));
            // catching up the index
            int bracketCount = 1;
            while (index < strlen(str) && bracketCount != 0) {//this works like a boolean and is set to zero when all the paranthesises find their match.
                if (str[index] == '(') bracketCount++; 
                if (str[index] == ')') bracketCount--;
                index++;
            }

            if (preSign == '+') {
                result = add(result, subResult);
            } else if (preSign == '-') {
                result = sub(result, subResult);
            }
        } else if (ch == ')') {
            return result;
        }
    }

    return result;
}

int main(void) {
    char str[100];

    printf("Enter the line to be performed :\n");
   gets(str); 
    printf("\nResult: %d\n", calculate(str));

    return 0;
}

