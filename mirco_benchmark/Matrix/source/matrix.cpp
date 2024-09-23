#include <stdio.h>
#include <iostream>

int arr[14] =		{
	0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

int main(){
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate the size of the array

    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}