#include "passserver.h"
#include <fstream>
#include <iostream>

namespace cop4530 {

// Constructor
PassServer::PassServer(size_t size) : hashTable(size) {}

// Destructor
PassServer::~PassServer() {}

// Load a password file into the PassServer
bool PassServer::load(const char* filename) {
    return hashTable.load(filename);
}

// Add a new username and password
bool PassServer::addUser(std::pair<std::string, std::string>& kv) {
    // Encrypt the password before adding
    kv.second = encrypt(kv.second);
    return hashTable.insert(kv);
}

// Move version of addUser
bool PassServer::addUser(std::pair<std::string, std::string>&& kv) {
    // Encrypt the password before adding
    kv.second = encrypt(kv.second);
    return hashTable.insert(std::move(kv));
}

// Delete an existing user with username k
bool PassServer::removeUser(const std::string& k) {
    return hashTable.remove(k);
}

// Change an existing user's password
bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword) {
    // Check if the user exists and the old password matches the current one
    if (!hashTable.contains(p.first) || !hashTable.match(p))
        return false;

    // Encrypt the new password before updating
    std::string encryptedPassword = encrypt(newpassword);
    hashTable.insert({p.first, encryptedPassword});
    return true;
}

// Check if a user exists
bool PassServer::find(const std::string& user) const {
    return hashTable.contains(user);
}

// Show the structure and contents of the PassServer
void PassServer::dump() const {
    hashTable.dump();
}

// Return the size of the PassServer (the number of username/password pairs in the table)
size_t PassServer::size() const {
    return hashTable.size();
}

// Un-encrypt the password from the data structure and save the username and password combination into a file
bool PassServer::write_to_file(const char* filename) const {
    // Create an output file stream
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "** Error: Cannot open file " << filename << " for writing.\n";
        return false;
    }

    // Get all entries from the hash table
    auto entries = hashTable.dump();

    // Write the contents to the file
    for (const auto& entry : entries) {
        // Decrypt the password before writing to the file
        std::string decryptedPassword = encrypt(entry.second);
        file << entry.first << " " << decryptedPassword << "\n";
    }

    // Close the file
    file.close();
    return true;
}

// Private helper function to encrypt a password
std::string PassServer::encrypt(const std::string& str) const {
    std::string encryptedPassword;
    BYTE charin[str.size()]; // Use str.size() to specify the size of the charin array
    BYTE charout[str.size()];

    // Copy the string into the BYTE array
    strncpy(reinterpret_cast<char*>(charin), str.c_str(), str.size());

    // Encrypt the password
    base64_encode(charin, charout, str.size(), 1);

    // Copy the encrypted password back to the string
    encryptedPassword = reinterpret_cast<const char*>(charout);
    return encryptedPassword;
}

} // namespace cop4530