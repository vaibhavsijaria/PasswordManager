// Daksh Goel
//23BCI0127

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


#define LOWERCASE_CHARS "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
#define UPPERCASE_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGIT_CHARS "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
#define SPECIAL_CHARS "`~!@#$%^&*()=+_-{}[]:;'\",.<>/?\\|`~!@#$%^&*()=+_-{}[]:;'\",.<>/?\\|`~!@#$%^&*()=+_-{}[]:;'\",.<>/?\\|`~!@#$%^&*()=+_-{}[]:;'\",.<>/?\\|`~!@#$%^&*()=+_-{}[]:;'\",.<>/?\\|`~!@#$%^&*()=+_-{}[]:;'\",.<>/?\\|"
#define MAX_OPTION_SIZE 4
#define MIN_CHAR 4
#define MAX_CHAR 1000


int crypto_random_number(int max);
char *shuffle_characters(const char *input);
char *my_strndup(const char *str, size_t n);
char *random_password(unsigned int size, int include_lowercase, int include_uppercase, int include_digits, int include_special);


int crypto_random_number(int max) {
    return rand() % max; // This will generate a random number up to 'max'
}


//<<-------------------Function to Shuffle the characters in a string------------------->>//

char *shuffle_characters(const char *input) {
    size_t len = strlen(input);
    char *shuffled_array = my_strndup(input, len);

    for (size_t i = len - 1; i > 0; --i) {
        size_t j = crypto_random_number(i + 1);

        // We have to Swap shuffled_array[i] and shuffled_array[j] for shuffling
        // to take place.
        char temp = shuffled_array[i];
        shuffled_array[i] = shuffled_array[j];
        shuffled_array[j] = temp;
    }

    return shuffled_array;
}

//-------------------Function to Shuffle the characters in a string-------------------//


//-------------------Function to Duplicate the characters in a string-------------------//
char *my_strndup(const char *str, size_t n) {
    size_t len = strnlen(str, n);
    char *duplicate = (char *)malloc(len + 1);

    if (duplicate != NULL) {
        strncpy(duplicate, str, len);
        duplicate[len] = '\0';
    }

    return duplicate;
}
//<<-------------------Function to Duplicate the characters in a string------------------->>>//



//<-------function for generating the random pwd by defining size and characters user want--------->
char *random_password(unsigned int size, int include_lowercase,
 int include_uppercase, int include_digits, int include_special) {
    if (size < MIN_CHAR || size > MAX_CHAR) {
        fprintf(stderr, "Error: Invalid password size. Please choose a size between %d and %d.\n",
                MIN_CHAR, MAX_CHAR);
        return NULL;
    }

    if (!include_lowercase && !include_uppercase && !include_digits && !include_special) {
        fprintf(stderr, "Error: Please select at least one character type.\n");
        return NULL;
    }

    // Combine selected character sets into one string
    char char_set[MAX_CHAR * MAX_OPTION_SIZE];
    char *char_set_ptr = char_set;

    if (include_lowercase) {
        strcpy(char_set_ptr, LOWERCASE_CHARS);
        char_set_ptr += strlen(LOWERCASE_CHARS);
    }
    if (include_uppercase) {
        strcpy(char_set_ptr, UPPERCASE_CHARS);
        char_set_ptr += strlen(UPPERCASE_CHARS);
    }
    if (include_digits) {
        strcpy(char_set_ptr, DIGIT_CHARS);
        char_set_ptr += strlen(DIGIT_CHARS);
    }
    if (include_special) {
        strcpy(char_set_ptr, SPECIAL_CHARS);
    }

    const char *shuffled_chars = shuffle_characters(char_set);

    // Copy the first 'size' characters to the result
    char *result = my_strndup(shuffled_chars, size);

    free((void *)shuffled_chars);

    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    return result;
}

//<---------function for generating the random pwd by defining size and characters user want--------->


int main() {
    int password_size;
    int include_lowercase = 1; 
    int include_uppercase = 1; 
    int include_digits = 1;
    int include_special = 1;

    printf("Enter the size of the password you want to consider: ");
    scanf("%d", &password_size);

    printf("Do you want to include lowercase letters? (1 for yes, 0 for no): ");
    scanf("%d", &include_lowercase);

    printf("Do you want to include uppercase letters? (1 for yes, 0 for no): ");
    scanf("%d", &include_uppercase);

    printf("Do you want to include digits? (1 for yes, 0 for no): ");
    scanf("%d", &include_digits);

    printf("Do you want to include special characters? (1 for yes, 0 for no): ");
    scanf("%d", &include_special);

    char *password = random_password(password_size, include_lowercase, include_uppercase, include_digits, include_special);

    if (password != NULL) {
        printf("Your Generated Password: %s\n", password);
        free(password);
    } else {
        printf("Failed to generate password!!!!! Please check your input once.\n");
    }

    return 0;
}