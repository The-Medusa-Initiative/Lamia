/*
 * Weinberg's Second Law:
 * "If builders built buildings the way programmers wrote programs, 
 *  the first woodpecker that came along would destroy the civilization."
 */

#pragma once

#include <string>
#include <map>

namespace MedusaServ {
namespace Security {

// SECURITY NOTICE: This is a TEMPLATE file for production credentials
// NEVER commit actual production credentials to public repositories
// Use environment variables or secure credential management systems

struct ServerCredentials {
    std::string ip_primary = "SERVER_IP_PLACEHOLDER";
    std::string username = "USERNAME_PLACEHOLDER";  
    std::string password = "PASSWORD_PLACEHOLDER";
    std::map<std::string, std::string> additional_data;
};

struct DatabaseCredentials {
    std::string host = "DATABASE_HOST_PLACEHOLDER";
    std::string username = "DATABASE_USER_PLACEHOLDER";
    std::string password = "DATABASE_PASSWORD_PLACEHOLDER";
    std::string database = "DATABASE_NAME_PLACEHOLDER";
    int port = 5432;
};

class ProductionCredentialsVault {
private:
    ServerCredentials frontend;
    ServerCredentials backend;  
    ServerCredentials database;
    ServerCredentials medlab;
    
    DatabaseCredentials postgresql;
    DatabaseCredentials neo4j;
    
public:
    ProductionCredentialsVault() {
        InitializeCredentials();
    }
    
    void InitializeCredentials() {
        // SECURITY WARNING: Replace these placeholders with actual environment variables
        // NEVER hardcode production credentials in source code
        
        // Frontend Server Configuration
        frontend.ip_primary = "FRONTEND_SERVER_IP";
        frontend.username = "FRONTEND_USERNAME";
        frontend.password = "FRONTEND_PASSWORD";
        frontend.additional_data["role"] = "frontend";
        frontend.additional_data["note"] = "Load environment variables for production";
        
        // Backend Server Configuration
        backend.ip_primary = "BACKEND_SERVER_IP";
        backend.username = "BACKEND_USERNAME"; 
        backend.password = "BACKEND_PASSWORD";
        backend.additional_data["role"] = "backend";
        backend.additional_data["note"] = "Load environment variables for production";
        
        // Database Server Configuration
        database.ip_primary = "DATABASE_SERVER_IP";
        database.username = "DATABASE_USERNAME";
        database.password = "DATABASE_PASSWORD";
        database.additional_data["role"] = "database";
        
        // PostgreSQL Configuration
        postgresql.host = "POSTGRESQL_HOST";
        postgresql.username = "POSTGRESQL_USER";
        postgresql.password = "POSTGRESQL_PASSWORD";
        postgresql.database = "POSTGRESQL_DATABASE";
        postgresql.port = 5432;
        
        // Neo4j Configuration
        neo4j.host = "NEO4J_HOST";
        neo4j.username = "NEO4J_USER";
        neo4j.password = "NEO4J_PASSWORD";
        neo4j.database = "NEO4J_DATABASE";
        neo4j.port = 7687;
    }
    
    // SECURITY: These methods should load from environment variables in production
    ServerCredentials GetFrontendCredentials() const { return frontend; }
    ServerCredentials GetBackendCredentials() const { return backend; }
    ServerCredentials GetDatabaseCredentials() const { return database; }
    DatabaseCredentials GetPostgreSQLCredentials() const { return postgresql; }
    DatabaseCredentials GetNeo4jCredentials() const { return neo4j; }
    
    // Security method to validate credentials are not placeholders
    bool ValidateProductionCredentials() const {
        return frontend.ip_primary != "FRONTEND_SERVER_IP" &&
               backend.ip_primary != "BACKEND_SERVER_IP" &&
               database.ip_primary != "DATABASE_SERVER_IP";
    }
};

} // namespace Security
} // namespace MedusaServ