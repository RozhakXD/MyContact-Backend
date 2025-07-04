#include "ContactRepository.h"

ContactRepository::ContactRepository(sqlite::database& database) : db(database) {}

void ContactRepository::add(const Contact& contact) {
    db << "INSERT INTO contacts (name, phone, category) VALUES (?, ?, ?);"
        << contact.name
        << contact.phone
        << contact.category;
}

std::vector<Contact> ContactRepository::getAll() {
    std::vector<Contact> contacts;
    db << "SELECT id, name, phone, category FROM contacts;"
        >> [&](int id, std::string name, std::string phone, std::string category) {
            contacts.push_back({id, name, phone, category});
        };
    return contacts;
}

std::optional<Contact> ContactRepository::getById(int id) {
    Contact contact;
    bool found = false;
    db << "SELECT id, name, phone, category FROM contacts WHERE id = ?;"
        << id
        >> [&](int c_id, std::string c_name, std::string c_phone, std::string c_category) {
            contact = {c_id, c_name, c_phone, c_category};
            found = true;
        };

    if (found) {
        return contact;
    }
    return std::nullopt;
}

std::vector<Contact> ContactRepository::getByName(const std::string& name) {
    std::vector<Contact> contacts;
    
    std::string query_name = "%" + name + "%";
    db << "SELECT id, name, phone, category FROM contacts WHERE name LIKE ?;"
        << query_name
        >> [&](int id, std::string c_name, std::string phone, std::string category) {
            contacts.push_back({id, c_name, phone, category});
        };
    return contacts;
}

std::vector<Contact> ContactRepository::getByCategory(const std::string& category) {
    std::vector<Contact> contacts;

    std::string query_category = "%" + category + "%";
    db << "SELECT id, name, phone, category FROM contacts WHERE category LIKE ?;"
        << query_category
        >> [&](int id, std::string name, std::string phone, std::string c_category) {
            contacts.push_back({id, name, phone, c_category});
        };
    return contacts;
}

bool ContactRepository::update(int id, const Contact& contact) {
    db << "UPDATE contacts SET name = ?, phone = ?, category = ? WHERE id = ?;"
        << contact.name
        << contact.phone
        << contact.category
        << id;

    return sqlite3_changes(db.connection().get()) > 0;
}

bool ContactRepository::remove(int id) {
    db << "DELETE FROM contacts WHERE id = ?;" << id;

    return sqlite3_changes(db.connection().get()) > 0;
}