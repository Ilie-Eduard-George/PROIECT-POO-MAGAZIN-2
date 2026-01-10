#pragma once
#include <stdexcept>
#include <string>

class StoreError : public std::runtime_error {
public:
    explicit StoreError(const std::string& msg) : std::runtime_error(msg) {}
};

class InputError : public StoreError {
public:
    explicit InputError(const std::string& msg) : StoreError("Eroare la input : " + msg) {}
};

class NotFoundError : public StoreError {
public:
    explicit NotFoundError(const std::string& msg) : StoreError("Nu s-a putut gasi acel produs : " + msg) {}
};

class OutOfStockError : public StoreError {
public:
    explicit OutOfStockError(const std::string& msg) : StoreError("Eroare de stoc : " + msg) {}
};
