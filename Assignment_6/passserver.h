#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <string>
#include "hashtable.h"
#include "base64.h" // For encryption and decryption

namespace cop4530 {

class PassServer {
public:
    // Constructor
    explicit PassServer(size_t size = 101);

    // Destructor
    ~PassServer();

    // Load a password file into the PassServer
    bool load(const char* filename);

    // Add a new username and password
    bool addUser(std::pair<std::string, std::string>& kv);

    // Move version of addUser
    bool addUser(std::pair<std::string, std::string>&& kv);

    // Delete an existing user with username k
    bool removeUser(const std::string& k);

    // Change an existing user's password
    bool changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword);

    // Check if a user exists
    bool find(const std::string& user) const;

    // Show the structure and contents of the PassServer
    void dump() const;

    // Return the size of the PassServer (the number of username/password pairs in the table)
    size_t size() const;

    // Un-encrypt the password from the data structure and save the username and password combination into a file
    bool write_to_file(const char* filename) const;

private:
    // Private helper function to encrypt a password
    std::string encrypt(const std::string& str) const;

    HashTable<std::string, std::string> hashTable; // Using HashTable to store username and encrypted password pairs
};

} // namespace cop4530

#include "passserver.hpp"

#endif // PASSSERVER_H