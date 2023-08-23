#pragma once
#include <iostream>

//+, =, +=, ==, length, ctor() datark; ctor(parametr); dtor; copy ctor

const int SIZE = 16;

class String {
public:
    String(const char* = "");
    String(const String&);
    int length() const;
    String operator+(const String&) const;
    String& operator=(const String&);
    String& operator+=(const String&);
    bool operator==(const String&) const;
    ~String();
private:
    friend std::ostream& operator<<(std::ostream&, const String&);
    char* string() const;
    enum class storage_type {
        STATIC,
        DYNAMIC
    };
    typedef struct { 
        int size;
        int capacity;
        char* ptr; 
    } dyn_str;
    storage_type m_storage;
    union {
        char onstack[SIZE];
        dyn_str str;
    } m_string;
};
