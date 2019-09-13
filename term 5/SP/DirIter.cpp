#include "DirIter.hpp"

DirIter::DirIter(DIR* dir) : m_dir(dir), m_current(nullptr) { }

DirIter::DirIter(const DirIter& other) : m_dir(other.m_dir), m_current(other.m_current) { };

DirIter& DirIter::operator=(const DirIter& other) {
    m_dir = other.m_dir;
    m_current = other.m_current;
    return *this;
}

DirIter& DirIter::operator++() {
    m_current = readdir(m_dir);
    return *this;
}

DirIter& DirIter::operator++(int) {
    m_current = readdir(m_dir);
    return *this;
}

dirent DirIter::operator*() {
    return *m_current;
}

dirent* DirIter::operator->() {
    return m_current;
}

bool DirIter::operator==(const DirIter& other) {
    return m_current == other.m_current;
}

bool DirIter::operator!=(const DirIter& other) {
    return !(*this == other);
}
