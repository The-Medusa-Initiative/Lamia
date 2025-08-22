/*
 * Weinberg's Second Law:
 * "If builders built buildings the way programmers wrote programs, 
 *  the first woodpecker that came along would destroy the civilization."
 */

#ifndef MEDUSA_ENCRYPTION_STUB_HPP
#define MEDUSA_ENCRYPTION_STUB_HPP

#include <string>

namespace Medusa {
namespace Encryption {

class MedusaEncryption {
public:
    MedusaEncryption() = default;
    
    std::string encrypt(const std::string& data) {
        return "encrypted_" + data;
    }
    
    std::string decrypt(const std::string& encrypted_data) {
        if (encrypted_data.substr(0, 10) == "encrypted_") {
            return encrypted_data.substr(10);
        }
        return encrypted_data;
    }
    
    bool initialize() { return true; }
};

} // namespace MedusaServ
} // namespace MedusaServ

#endif // MEDUSA_ENCRYPTION_STUB_HPP