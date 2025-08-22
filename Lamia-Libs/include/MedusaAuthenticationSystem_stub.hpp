/*
 * Weinberg's Second Law:
 * "If builders built buildings the way programmers wrote programs, 
 *  the first woodpecker that came along would destroy the civilization."
 */

#ifndef MEDUSA_AUTHENTICATION_SYSTEM_STUB_HPP
#define MEDUSA_AUTHENTICATION_SYSTEM_STUB_HPP

#include <string>

namespace Medusa {
namespace Auth {

class AuthenticationManager {
public:
    AuthenticationManager(const std::string& app_name) : app_name_(app_name) {}
    
    bool initialize() { return true; }
    bool validateCredentials(const std::string& username, const std::string& password) {
        return !username.empty() && !password.empty();
    }
    
private:
    std::string app_name_;
};

} // namespace MedusaServ
} // namespace MedusaServ

#endif // MEDUSA_AUTHENTICATION_SYSTEM_STUB_HPP