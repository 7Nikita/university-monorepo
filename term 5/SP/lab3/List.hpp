
#ifndef List_hpp
#define List_hpp

#include <cstring>
#include <iostream>
#include <stdexcept>


template <typename T>
class Node {
    public:
        T data;
        Node<T> *prev;
        Node<T> *next;
        
        Node(T value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
};

template <typename T>
class List {
    private:
        int size;
        Node<T> *front;
        Node<T> *back;
    
        void copy_list(const List& list) {
            if (list.size != 0) {
                size = 0;
                Node<T> *curr = list.front;
                for (int i = 0; i < list.size; i++) {
                    InsertBack(curr->data);
                    curr = curr->next;
                }
            } else {
                List();
            }
        }
    
        void delete_list() {
            Node<T> *temp = front;
            while (temp != NULL) {
                if (front == back) {
                    delete front;
                    break;
                }
                temp = front->next;
                delete front;
                front = temp;
            }
            size = 0;
            front = NULL;
            back = NULL;
        }
    public:
        List() {
            size = 0;
            front = NULL;
            back = NULL;
        }
    
        List(const List& list) {
            copy_list(list);
        }
    
        ~List() {
            delete_list();
        }
    
        void push_front(T item) {
            if (size == 0) {
                Node<T> *temp = new Node<T>(item);
                front = temp;
                back = temp;
                size++;
            }
            else {
                Node<T> *temp = new Node<T>(item);
                front->prev = temp;
                temp->next = front;
                front = temp;
                size++;
            }
        }
    
        void push_back(T item) {
            if (size == 0) {
                Node<T> *temp = new Node<T>(item);
                front = temp;
                back = temp;
                size++;
            }
            else {
                Node<T> *temp = new Node<T>(item);
                back->next = temp;
                temp->prev = back;
                back = temp;
                size++;
            }
        }
    
        void push(T item, int pos) {
            if (pos == 0) {
                push_front(item);
                return;
            }
            else if (pos == size) {
                push_back(item);
                return;
            }
            else if (0 < pos && pos < size) {
                Node<T> *curr = front;
                for (int i = 0; i < size; i++) {
                    if (i == pos) {
                        Node<T>* temp = new Node<T>(item);
                        temp->prev = curr->prev;
                        curr->prev->next = temp;
                        curr->prev = temp;
                        temp->next = curr;
                        size++;
                        return;
                    }
                    else curr = curr->next;
                }
            }
            else {
                throw std::out_of_range("List::push - index out of range");
            }
        }
    
        T pop(int pos) {
            if (front == back) {
                Node<T> *temp = front;
                T result = temp->data;
                delete temp;
                front = NULL;
                back = NULL;
                size = 0;
                return result;
            }
            else if (pos == 0) {
                Node<T> *temp = front;
                T result = temp->data;
                front = front->next;
                front->prev = NULL;
                delete temp;
                size--;
                return result;
            }
            else if (pos == size-1) {
                Node<T> *temp = back;
                T result = temp->data;
                back = back->prev;
                back->next = NULL;
                delete temp;
                size--;
                return result;
            }
            else if (0 < pos && pos < size - 1) {
                Node<T> *curr = front;
                for (int i = 0; i < size; i++){
                    if (pos == i) {
                        T result = curr->data;
                        curr->prev->next = curr->next;
                        curr->next->prev = curr->prev;
                        curr->prev = NULL;
                        curr->next = NULL;
                        delete curr;
                        size--;
                        return result;
                    }
                    else curr = curr->next;
                }
            }
            throw std::out_of_range("List::pop - index out of range");
        }
    
        int sz() {
            return size;
        }
    
        bool empty() const {
            return size == 0;
        }
    
        bool contains(T item) const {
            Node<T> *curr = front;
            if (curr == NULL) {
                return false;
            } else {
                for (int i = 0; i < size; i++) {
                    if (item == curr->data) {
                        return true;
                    }
                    curr = curr->next;
                }
            }
            return false;
        }
    
        T get(int pos) const {
            if (pos >= 0 && pos < size) {
                Node<T> *curr = front;
                for (int i = 0; i < size; i++) {
                    if (pos == i) {
                        return curr->data;
                    }
                    curr = curr->next;
                }
            }
            throw std::out_of_range("LinkedList::ElementAt - index out of range");
        }
    
        void clear() {
            delete_list();
        }
    
        List& operator=(const List& list) {
            if (this != &list) {
                delete_list()();
                CopyList(list);
            }
            return *this;
        }
    
};

#endif /* List_hpp */
