#include "crow_all.h"
#include "sqlite_modern_cpp.h"
#include "ContactRepository.h"
#include <iostream>
#include <vector>

int main() {
    sqlite::database db("kontak.db");
    try {
        db << "CREATE TABLE IF NOT EXISTS contacts ("
            "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "   name TEXT NOT NULL,"
            "   phone TEXT NOT NULL UNIQUE,"
            "   category TEXT NOT NULL"
            ");";

        std::cout << "Database berhasil diinisialisasi." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error inisialisasi database: " << e.what() << std::endl;
        return 1;
    }

    ContactRepository repository(db);
    crow::SimpleApp app;

    CROW_ROUTE(app, "/contacts").methods("POST"_method)
    ([&repository](const crow::request& req){
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("name") || !body.has("phone") || !body.has("category")) {
                return crow::response(400, "{\"error\":\"Invalid JSON format\"}");
            }

            Contact new_contact;
            new_contact.name = body["name"].s();
            new_contact.phone = body["phone"].s();
            new_contact.category = body["category"].s();

            try {
                repository.add(new_contact);
                return crow::response(201, "{\"message\":\"Contact added successfully\"}");
            } catch (const std::exception& e) {
                return crow::response(409, "{\"error\":\"Failed to add contact, phone number might already exist.\"}");
            }
        } catch (const std::exception& e) {
            return crow::response(400, "{\"error\":\"Invalid JSON format or field types. All fields must be strings\"}");
        }
    });

    CROW_ROUTE(app, "/contacts").methods("GET"_method)
    ([&repository](){
        auto contacts = repository.getAll();
        crow::json::wvalue::list contacts_json;
        for (const auto& contact : contacts) {
            crow::json::wvalue c;
            c["id"] = contact.id;
            c["name"] = contact.name;
            c["phone"] = contact.phone;
            c["category"] = contact.category;
            contacts_json.push_back(std::move(c));
        }

        crow::json::wvalue response;
        response["status"] = "success";
        response["data"] = std::move(contacts_json);
        return crow::response(response);
    });

    CROW_ROUTE(app, "/contacts/<int>").methods("GET"_method)
    ([&repository](int id){
        auto contact = repository.getById(id);
        if (!contact) {
            return crow::response(404, "{\"error\":\"Contact not found\"}");
        }

        crow::json::wvalue c;
        c["id"] = contact->id;
        c["name"] = contact->name;
        c["phone"] = contact->phone;
        c["category"] = contact->category;

        crow::json::wvalue response;
        response["status"] = "success";
        response["data"] = std::move(c);
        return crow::response(response);
    });

    CROW_ROUTE(app, "/contacts/search").methods("GET"_method)
    ([&repository](const crow::request& req){
        crow::json::wvalue::list contacts_json;
        std::vector<Contact> contacts;

        if (req.url_params.get("name")) {
            contacts = repository.getByName(req.url_params.get("name"));
        }

        else if (req.url_params.get("category")) {
            contacts = repository.getByCategory(req.url_params.get("category"));
        }

        else {
            return crow::response(400, "{\"error\":\"Invalid search parameter. Use ?name=... or ?category=...\"}");
        }

        for (const auto& contact : contacts) {
            crow::json::wvalue c;
            c["id"] = contact.id;
            c["name"] = contact.name;
            c["phone"] = contact.phone;
            c["category"] = contact.category;
            contacts_json.push_back(std::move(c));
        }

        crow::json::wvalue response_json;
        response_json["status"] = "success";
        response_json["data"] = std::move(contacts_json);
        return crow::response(response_json);
    });

    CROW_ROUTE(app, "/contacts/<int>").methods("PUT"_method)
    ([&repository](const crow::request& req, int id){
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("name") || !body.has("phone") || !body.has("category")) {
                return crow::response(400, "{\"error\":\"Invalid JSON format\"}");
            }

            Contact updated_contact;
            updated_contact.name = body["name"].s();
            updated_contact.phone = body["phone"].s();
            updated_contact.category = body["category"].s();

            if (repository.update(id, updated_contact)) {
                return crow::response(200, "{\"message\":\"Contact updated successfully\"}");
            } else {
                return crow::response(404, "{\"error\":\"Contact not found or no changes made\"}");
            }
        } catch (const std::exception& e) {
            return crow::response(400, "{\"error\":\"Invalid JSON format or field types. All fields must be strings\"}");
        }
    });

    CROW_ROUTE(app, "/contacts/<int>").methods("DELETE"_method)
    ([&repository](int id){
        if (repository.remove(id)) {
            return crow::response(200, "{\"message\":\"Contact deleted successfully\"}");
        } else {
            return crow::response(404, "{\"error\":\"Contact not found\"}");
        }
    });

    CROW_ROUTE(app, "/")([](){
        crow::json::wvalue response;
        response["status"] = "success";
        response["message"] = "Hello, Crow Backend!";
        return response;
    });

    std::cout << "Server berjalan di http://localhost:18080" << std::endl;
    app.port(18080).multithreaded().run();

    return 0;
}