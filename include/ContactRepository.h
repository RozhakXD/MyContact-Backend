#pragma once
#include "Contact.h"
#include "sqlite_modern_cpp.h"
#include <vector>
#include <optional>

class ContactRepository {
    private:
        sqlite::database& db;

    public:
        ContactRepository(sqlite::database& database);

        void add(const Contact& contact);

        std::vector<Contact> getAll();

        std::optional<Contact> getById(int id);

        std::vector<Contact> getByName(const std::string& name);

        std::vector<Contact> getByCategory(const std::string& category);

        bool update(int id, const Contact& contact);

        bool remove(int id);
};