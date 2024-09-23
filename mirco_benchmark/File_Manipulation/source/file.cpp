#include <stdio.h>
#include <stdlib.h>

// Function to check if a file exists
int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Function to rename a file
void renameFile(const char *oldName, const char *newName) {
    if (rename(oldName, newName) == 0) {
        printf("File renamed successfully from %s to %s.\n", oldName, newName);
    } else {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }
}

// Function to delete a file
void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("File %s deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *filename = "test_file.txt";
    const char *newFilename = "new_test_file.txt";

    // Check if the file exists
    if (fileExists(filename)) {
        printf("File %s exists.\n", filename);
    } else {
        printf("File %s does not exist.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Rename the file
    renameFile(filename, newFilename);

    // Delete the file
    deleteFile(newFilename);

    return 0;
}
