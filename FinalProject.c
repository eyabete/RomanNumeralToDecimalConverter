#include <stdio.h>   // Include standard input/output library for file operations and printing
#include <string.h>  // Include string library for handling strings (e.g., strlen, strchr)
#include <ctype.h>   // Include ctype library for character handling (e.g., toupper)

// Function prototypes declare the functions used in the program
int romanToDecimal(char *roman); // Converts a Roman numeral string to its decimal equivalent
int getValue(char romanChar);   // Retrieves the decimal value of a single Roman numeral character
void writeResultToFileAndTerminal(FILE *output, const char *roman, int decimal, int valid); // Writes results to file and displays them on the terminal
void processFile(const char *inputFile, const char *outputFile); // Processes the input file and performs the conversions
int isValidRomanNumeral(const char *roman); // Validates whether a string is a valid Roman numeral

// Main function - program entry point
int main() {
    const char *inputFile = "input.txt";    // Specify the input file containing Roman numerals
    const char *outputFile = "output.txt"; // Specify the output file to save the results

    processFile(inputFile, outputFile);    // Call the function to process the file and convert Roman numerals

    printf("Conversion completed. Results saved to '%s'.\n", outputFile); // Print a message indicating completion
    return 0; // Return 0 to indicate successful program execution
}

// Function to process the input file and write results to the output file
void processFile(const char *inputFile, const char *outputFile) {
    FILE *input = fopen(inputFile, "r"); // Open the input file in read mode
    FILE *output = fopen(outputFile, "w"); // Open the output file in write mode

    if (!input || !output) { // Check if either file failed to open
        printf("Error: Unable to open files.\n"); // Print an error message
        return; // Exit the function if files cannot be opened
    }

    char roman[100]; // Buffer to store a Roman numeral read from the file
    while (fscanf(input, "%s", roman) != EOF) { // Read each Roman numeral from the input file until end of file
        if (isValidRomanNumeral(roman)) { // Check if the Roman numeral is valid
            int decimal = romanToDecimal(roman); // Convert the valid Roman numeral to its decimal value
            writeResultToFileAndTerminal(output, roman, decimal, 1); // Write the valid result to the file and terminal
        } else { // If the Roman numeral is invalid
            writeResultToFileAndTerminal(output, roman, 0, 0); // Write "invalid" result to the file and terminal
        }
    }

    fclose(input); // Close the input file
    fclose(output); // Close the output file
}

// Function to validate if a string is a Roman numeral
int isValidRomanNumeral(const char *roman) {
    for (int i = 0; roman[i] != '\0'; i++) { // Iterate through each character in the Roman numeral string
        if (!strchr("IVXLCDM", toupper(roman[i]))) { // Check if the character is not one of the valid Roman numeral symbols
            return 0; // Return 0 (false) if an invalid character is found
        }
    }
    return 1; // Return 1 (true) if all characters are valid
}

// Function to convert Roman numeral to decimal
int romanToDecimal(char *roman) {
    int total = 0; // Initialize total to store the decimal equivalent
    int length = strlen(roman); // Get the length of the Roman numeral string
    for (int i = 0; i < length; i++) { // Loop through each character in the Roman numeral
        int current = getValue(toupper(roman[i])); // Get the decimal value of the current Roman numeral character
        int next = (i + 1 < length) ? getValue(toupper(roman[i + 1])) : 0; // Get the value of the next character (or 0 if none exists)

        if (current < next) { // Check if the current value is less than the next
            total -= current; // Subtract the current value from the total (e.g., IV = 5 - 1)
        } else { // Otherwise, the current value is greater than or equal to the next
            total += current; // Add the current value to the total
        }
    }
    return total; // Return the total decimal value
}

// Function to get the integer value of a Roman numeral
int getValue(char romanChar) {
    switch (romanChar) { // Use a switch-case to map Roman numeral characters to their decimal values
        case 'I': return 1;    // I represents 1
        case 'V': return 5;    // V represents 5
        case 'X': return 10;   // X represents 10
        case 'L': return 50;   // L represents 50
        case 'C': return 100;  // C represents 100
        case 'D': return 500;  // D represents 500
        case 'M': return 1000; // M represents 1000
        default: return 0; // Return 0 if an invalid character is passed (should not happen after validation)
    }
}

// Function to write the conversion result to the output file and display in terminal
void writeResultToFileAndTerminal(FILE *output, const char *roman, int decimal, int valid) {
    if (valid) { // Check if the Roman numeral is valid
        printf("%s: %d\n", roman, decimal); // Print the Roman numeral and its decimal value to the terminal
        fprintf(output, "%s: %d\n", roman, decimal); // Write the Roman numeral and its decimal value to the output file
    } else { // If the Roman numeral is invalid
        printf("%s: Invalid Roman numeral\n", roman); // Print an "Invalid" message to the terminal
        fprintf(output, "%s: Invalid Roman numeral\n", roman); // Write an "Invalid" message to the output file
    }
}
