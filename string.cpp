#include <iostream>
#include "string.h"
#include <cstring>
#include <ostream>
#include <type_traits>


String::String(const char* c_str) {
    int c_str_size = 0;
    for (; c_str[c_str_size]; ++c_str_size);
    ++c_str_size;
    if (c_str_size <= 16) {
        m_storage = storage_type::STATIC;
        
        for (int i = 0; i < c_str_size; ++i) {
            m_string.onstack[i] = c_str[i];
        }
    }
    else {
        m_storage = storage_type::DYNAMIC;
        m_string.str.size = c_str_size - 1;
        m_string.str.capacity = c_str_size;
        m_string.str.ptr = new char[m_string.str.capacity];

        for (int i = 0; i < c_str_size; ++i) {
            m_string.str.ptr[i] = c_str[i];
        }
    }
}

String::String(const String& str) {
    if (str.m_storage == storage_type::DYNAMIC) {
        m_storage = storage_type::DYNAMIC;
        m_string.str.size = str.m_string.str.size;
        m_string.str.capacity = str.m_string.str.capacity;
        m_string.str.ptr = new char[m_string.str.capacity];
        
        for (int i = 0; i < m_string.str.size; ++i) {
            m_string.str.ptr[i] = str.m_string.str.ptr[i]; 
        }
    }
    else {
        m_storage = storage_type::STATIC;
        for (int i = 0; i < str.m_string.str.size; ++i) {
            m_string.onstack[i] = str.m_string.str.ptr[i];
        }
    }
}

int String::length() const {
    if (m_storage == storage_type::DYNAMIC) {
        return m_string.str.size;
    }
    int result_length = 0;
    for (; m_string.onstack[result_length]; ++result_length);
    return result_length;
}

char* String::string() const {
    int size = length() + 1;
    char* result = new char[size];

    if (m_storage == storage_type::DYNAMIC) { 
        for (int i = 0; i < size; ++i) {
            result[i] = m_string.str.ptr[i];
        }
        return result;
    }
    
    for (int i = 0; i < size; ++i) {
       result[i] = m_string.onstack[i]; 
    }
    return result;
}

String String::operator+(const String& str) const {
    char* c_str_1 = string();
    char* c_str_2 = str.string();
    int new_size = strlen(c_str_1) + strlen(c_str_2) + 1;
    char* tmp = new char[new_size];
    for (int i = 0; i < new_size; ++i) {
        tmp[i] = c_str_1[i];
    }
    delete[] c_str_1;
    c_str_1 = tmp;
    tmp = nullptr;

    strcat(c_str_1, c_str_2);
    
    String result{ c_str_1 };
    
    delete[] c_str_1;
    delete [] c_str_2;
    return result;
}

String& String::operator=(const String& str) {
    if (m_storage == storage_type::DYNAMIC) {
        delete[] m_string.str.ptr;
    } 
    if (str.m_storage == storage_type::DYNAMIC) {
        m_storage = storage_type::DYNAMIC;
        m_string.str.size = str.m_string.str.size;
        m_string.str.capacity = str.m_string.str.capacity;
        m_string.str.ptr = new char[m_string.str.capacity];
        
        for (int i = 0; i < m_string.str.size; ++i) {
            m_string.str.ptr[i] = str.m_string.str.ptr[i]; 
        }
    }
    else {
        m_storage = storage_type::STATIC;
        for (int i = 0; i < str.m_string.str.size; ++i) {
            m_string.onstack[i] = str.m_string.str.ptr[i];
        }
    }
    return *this;
}

bool String::operator==(const String& str) const {
    if (length() != str.length()) {
        return false;
    }

    char* c_str_1 = string();
    char* c_str_2 = str.string();

    int const current_size = str.length();
    for (int i = 0; i < current_size; ++i) {
        if (c_str_1[i] != c_str_2[i]) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
    char* current_str = str.string();
    out << current_str;
    delete [] current_str;
    return out;
}

String::~String() {
    if (m_storage == storage_type::DYNAMIC) {
        delete[] m_string.str.ptr; 
    }
}
