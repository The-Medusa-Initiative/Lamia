/**
 * MEDUSASERV FAKE DATABASE HEADER v0.3.0a
 * ========================================
 * Simple File-Based Database System for MedusaServ
 * © 2025 The Medusa Project | Roylepython | D Hargreaves
 */

#ifndef MEDUSASERV_FAKE_DATABASE_H
#define MEDUSASERV_FAKE_DATABASE_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <iomanip>

namespace MedusaServ {

class FakeDatabase {
private:
    std::string database_path;
    std::map<std::string, std::map<std::string, std::string>> tables;
    
    // Internal helpers
    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    std::string escapeField(const std::string& field) {
        std::string escaped = field;
        // Simple escape mechanism - replace | with \|
        size_t pos = 0;
        while ((pos = escaped.find("|", pos)) != std::string::npos) {
            escaped.replace(pos, 1, "\\|");
            pos += 2;
        }
        return escaped;
    }
    
    std::string unescapeField(const std::string& field) {
        std::string unescaped = field;
        // Unescape \| back to |
        size_t pos = 0;
        while ((pos = unescaped.find("\\|", pos)) != std::string::npos) {
            unescaped.replace(pos, 2, "|");
            pos += 1;
        }
        return unescaped;
    }

public:
    FakeDatabase(const std::string& db_path = "/opt/medusaserv/fake-db/") 
        : database_path(db_path) {
        // Ensure database directory exists
        system(("mkdir -p " + database_path).c_str());
    }
    
    // Table operations
    bool createTable(const std::string& table_name, const std::vector<std::string>& columns) {
        std::string table_file = database_path + table_name + ".fake-db";
        std::ofstream file(table_file);
        
        if (!file.is_open()) {
            return false;
        }
        
        // Write header with column definitions
        file << "# MEDUSASERV FAKE DATABASE TABLE: " << table_name << "\n";
        file << "# Created: " << getCurrentTimestamp() << "\n";
        file << "# Columns: ";
        for (size_t i = 0; i < columns.size(); ++i) {
            file << columns[i];
            if (i < columns.size() - 1) file << "|";
        }
        file << "\n";
        file << "# Format: field1|field2|field3|...\n\n";
        
        file.close();
        
        // Set secure permissions
        system(("chmod 600 " + table_file).c_str());
        
        std::cout << "✅ Created fake database table: " << table_name << "\n";
        return true;
    }
    
    // Insert record
    bool insert(const std::string& table_name, const std::map<std::string, std::string>& data) {
        std::string table_file = database_path + table_name + ".fake-db";
        std::ofstream file(table_file, std::ios::app);
        
        if (!file.is_open()) {
            return false;
        }
        
        // Write data row
        bool first = true;
        for (const auto& pair : data) {
            if (!first) file << "|";
            file << escapeField(pair.second);
            first = false;
        }
        file << "\n";
        
        file.close();
        return true;
    }
    
    // Select records (simple key-value matching)
    std::vector<std::map<std::string, std::string>> select(
        const std::string& table_name,
        const std::string& where_column = "",
        const std::string& where_value = ""
    ) {
        std::vector<std::map<std::string, std::string>> results;
        std::string table_file = database_path + table_name + ".fake-db";
        std::ifstream file(table_file);
        
        if (!file.is_open()) {
            return results;
        }
        
        std::string line;
        std::vector<std::string> columns;
        bool header_parsed = false;
        
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                // Extract column names from header comment
                if (line.find("# Columns: ") == 0) {
                    std::string cols = line.substr(11);
                    std::stringstream ss(cols);
                    std::string col;
                    while (std::getline(ss, col, '|')) {
                        columns.push_back(col);
                    }
                    header_parsed = true;
                }
                continue;
            }
            
            if (!header_parsed) continue;
            
            // Parse data line
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;
            
            while (std::getline(ss, field, '|')) {
                fields.push_back(unescapeField(field));
            }
            
            if (fields.size() != columns.size()) continue;
            
            // Create record map
            std::map<std::string, std::string> record;
            for (size_t i = 0; i < columns.size() && i < fields.size(); ++i) {
                record[columns[i]] = fields[i];
            }
            
            // Apply where clause if specified
            if (!where_column.empty() && !where_value.empty()) {
                auto it = record.find(where_column);
                if (it == record.end() || it->second != where_value) {
                    continue;
                }
            }
            
            results.push_back(record);
        }
        
        file.close();
        return results;
    }
    
    // Update records
    bool update(
        const std::string& table_name,
        const std::map<std::string, std::string>& new_data,
        const std::string& where_column,
        const std::string& where_value
    ) {
        // Read all records
        auto all_records = select(table_name);
        
        // Get column structure
        std::string table_file = database_path + table_name + ".fake-db";
        std::ifstream read_file(table_file);
        std::vector<std::string> columns;
        std::string header_lines;
        std::string line;
        
        // Preserve header
        while (std::getline(read_file, line)) {
            header_lines += line + "\n";
            if (line.find("# Columns: ") == 0) {
                std::string cols = line.substr(11);
                std::stringstream ss(cols);
                std::string col;
                while (std::getline(ss, col, '|')) {
                    columns.push_back(col);
                }
            }
            if (!line.empty() && line[0] != '#') break;
        }
        read_file.close();
        
        // Rewrite file
        std::ofstream write_file(table_file);
        write_file << header_lines;
        
        bool updated = false;
        for (auto& record : all_records) {
            // Check if this record matches the where clause
            auto it = record.find(where_column);
            if (it != record.end() && it->second == where_value) {
                // Update the record
                for (const auto& pair : new_data) {
                    record[pair.first] = pair.second;
                }
                updated = true;
            }
            
            // Write record
            bool first = true;
            for (const auto& col : columns) {
                if (!first) write_file << "|";
                auto field_it = record.find(col);
                if (field_it != record.end()) {
                    write_file << escapeField(field_it->second);
                }
                first = false;
            }
            write_file << "\n";
        }
        
        write_file.close();
        return updated;
    }
    
    // Delete records
    bool deleteRecord(
        const std::string& table_name,
        const std::string& where_column,
        const std::string& where_value
    ) {
        // Read all records
        auto all_records = select(table_name);
        
        // Get column structure
        std::string table_file = database_path + table_name + ".fake-db";
        std::ifstream read_file(table_file);
        std::vector<std::string> columns;
        std::string header_lines;
        std::string line;
        
        // Preserve header
        while (std::getline(read_file, line)) {
            header_lines += line + "\n";
            if (line.find("# Columns: ") == 0) {
                std::string cols = line.substr(11);
                std::stringstream ss(cols);
                std::string col;
                while (std::getline(ss, col, '|')) {
                    columns.push_back(col);
                }
            }
            if (!line.empty() && line[0] != '#') break;
        }
        read_file.close();
        
        // Rewrite file without matching records
        std::ofstream write_file(table_file);
        write_file << header_lines;
        
        bool deleted = false;
        for (const auto& record : all_records) {
            // Check if this record matches the where clause
            auto it = record.find(where_column);
            if (it != record.end() && it->second == where_value) {
                deleted = true;
                continue; // Skip this record (delete it)
            }
            
            // Write record
            bool first = true;
            for (const auto& col : columns) {
                if (!first) write_file << "|";
                auto field_it = record.find(col);
                if (field_it != record.end()) {
                    write_file << escapeField(field_it->second);
                }
                first = false;
            }
            write_file << "\n";
        }
        
        write_file.close();
        return deleted;
    }
    
    // Count records
    size_t count(const std::string& table_name) {
        return select(table_name).size();
    }
    
    // Check if table exists
    bool tableExists(const std::string& table_name) {
        std::string table_file = database_path + table_name + ".fake-db";
        std::ifstream file(table_file);
        return file.good();
    }
    
    // List all tables
    std::vector<std::string> listTables() {
        std::vector<std::string> tables;
        std::string command = "ls " + database_path + "*.fake-db 2>/dev/null | sed 's/.*\\///;s/\\.fake-db$//'";
        
        FILE* pipe = popen(command.c_str(), "r");
        if (pipe) {
            char buffer[128];
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                std::string table_name = buffer;
                // Remove newline
                if (!table_name.empty() && table_name.back() == '\n') {
                    table_name.pop_back();
                }
                if (!table_name.empty()) {
                    tables.push_back(table_name);
                }
            }
            pclose(pipe);
        }
        
        return tables;
    }
    
    // Database status
    void showStatus() {
        std::cout << "🔱 MedusaServ Fake Database Status\n";
        std::cout << "==================================\n";
        std::cout << "Database path: " << database_path << "\n";
        
        auto tables = listTables();
        std::cout << "Total tables: " << tables.size() << "\n\n";
        
        for (const auto& table : tables) {
            size_t record_count = count(table);
            std::cout << "📊 " << table << ": " << record_count << " records\n";
        }
        
        if (tables.empty()) {
            std::cout << "No tables found. Database is empty.\n";
        }
        std::cout << "\n";
    }
};

} // namespace MedusaServ

#endif // MEDUSASERV_FAKE_DATABASE_H