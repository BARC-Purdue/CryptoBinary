#include <stdio.h>
#include <stdlib.h>

void writeToFile(const char *filename) {
    FILE *file = fopen(filename, "w"); // Open the file for writing
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "This is a test line.\n");
    fprintf(file, "Writing data to the file.\n");

    fclose(file); // Close the file
}

void readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer); // Print each line from the file
    }

    fclose(file); // Close the file
}

void appendToFile(const char *filename) {
    FILE *file = fopen(filename, "a"); // Open the file for appending
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Appending a new line to the file.\n");

    fclose(file); // Close the file
}

int main() {
    const char *filename = "example.txt";

    // Write to the file
    writeToFile(filename);
    printf("File written successfully.\n");

    // Append to the file
    appendToFile(filename);
    printf("Data appended successfully.\n");

    // Read from the file
    printf("Reading from the file:\n");
    readFromFile(filename);

    return 0;
}
