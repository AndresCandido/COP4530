#include <iostream>
#include <string>
#include "passserver.h"

// Function prototype for the Menu
void Menu();

int main() {
    char choice;
    size_t size = 101; // Default hash table size
    std::string filename, username, password, newPassword;
    cop4530::PassServer passServer(size);

    do {
        Menu();
        std::cin >> choice;

        switch (choice) {
            case 'l': // Load From File
                std::cout << "Enter password file name to load: ";
                std::cin >> filename;
                if (passServer.load(filename.c_str()))
                    std::cout << "Password file loaded successfully.\n";
                else
                    std::cout << "Error: Could not load password file.\n";
                break;

            case 'a': // Add User
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (passServer.addUser({username, password}))
                    std::cout << "User added successfully.\n";
                else
                    std::cout << "Error: User could not be added.\n";
                break;

            case 'r': // Remove User
                std::cout << "Enter username: ";
                std::cin >> username;
                if (passServer.removeUser(username))
                    std::cout << "User removed successfully.\n";
                else
                    std::cout << "Error: User could not be removed.\n";
                break;

            case 'c': // Change User Password
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter current password: ";
                std::cin >> password;
                std::cout << "Enter new password: ";
                std::cin >> newPassword;
                if (passServer.changePassword({username, password}, newPassword))
                    std::cout << "Password changed successfully.\n";
                else
                    std::cout << "Error: Password could not be changed.\n";
                break;

            case 'f': // Find User
                std::cout << "Enter username: ";
                std::cin >> username;
                if (passServer.find(username))
                    std::cout << "User found.\n";
                else
                    std::cout << "User not found.\n";
                break;

            case 'd': // Dump HashTable
                passServer.dump();
                break;

            case 's': // HashTable Size
                std::cout << "HashTable size: " << passServer.size() << std::endl;
                break;

            case 'w': // Write to Password File
                std::cout << "Enter password file name to write: ";
                std::cin >> filename;
                if (passServer.write_to_file(filename.c_str()))
                    std::cout << "Password file written successfully.\n";
                else
                    std::cout << "Error: Could not write to password file.\n";
                break;

            case 'x': // Exit program
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 'x');

    return 0;
}

// Function definition for the Menu
void Menu() {
    std::cout << "\n\n";
    std::cout << "l - Load From File" << std::endl;
    std::cout << "a - Add User" << std::endl;
    std::cout << "r - Remove User" << std::endl;
    std::cout << "c - Change User Password" << std::endl;
    std::cout << "f - Find User" << std::endl;
    std::cout << "d - Dump HashTable" << std::endl;
    std::cout << "s - HashTable Size" << std::endl;
    std::cout << "w - Write to Password File" << std::endl;
    std::cout << "x - Exit program" << std::endl;
    std::cout << "\nEnter choice: ";
}
