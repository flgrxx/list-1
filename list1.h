#ifndef LIST
#define LIST
#include <stdio.h>


template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node(T val, Node<T>* next = nullptr);
};

template <class T>
class List {
    Node<T>* _head, * _tail;
    int _count;
public:
    List() : _head(nullptr), _tail(nullptr), _count(0) {}
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(int pos, const T& val);
    void insert(Node<T>* node, const T& val);
    void pop_front() noexcept;
    void pop_back() noexcept;
    void erase(int pos);
    void erase(Node<T>* node);
    bool isEmpty() const;
    Node<T>* find(const T& val);

    T& front();
    T& back();
    int size() const;
    void clear();



    class Iterator {
        Node<T>* current;
    public:
        Iterator() : current(nullptr) {}
        Iterator(Node<T>* pos) : current(pos) {}
        Iterator(const Iterator& other) : current(other.current) {}

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                current = other.current;
            }
            return *this;
        }

        T& operator*() {
            if (current == nullptr) {
                throw std::runtime_error("Null iterator");
            }
            return current->value;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Iterator operator++(int) {
            Iterator tmp(*this);
            current = current->next;
            return tmp;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }
    };

    Iterator begin() {
        return Iterator(_head);
    }

    Iterator end() {
        return Iterator();
    }
    typedef Iterator iterator;
};
template <class T>
Node<T>::Node(T val, Node<T>* next) : value(val), next(next) {}

template <class T>
List<T>::List(const List& other) : _head(nullptr), _tail(nullptr), _count(0) {
    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <class T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        Node<T>* current = other._head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

template <class T>
List<T>::~List() {
    clear();
}

template <class T>
void List<T>::push_front(const T& val) noexcept {
    _head = new Node<T>(val, _head);
    if (_tail == nullptr) {
        _tail = _head;
    }
    _count++;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node<T>* new_node = new Node<T>(val);
    if (_tail == nullptr) {
        _head = _tail = new_node;
    }
    else {
        _tail->next = new_node;
        _tail = new_node;
    }
    _count++;
}

template <class T>
void List<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos > _count) {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0) {
        push_front(val);
    }
    else if (pos == _count) {
        push_back(val);
    }
    else {
        Node<T>* current = _head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        current->next = new Node<T>(val, current->next);
        _count++;
    }
}

template <class T>
void List<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr) {
        push_front(val);
    }
    else {
        Node<T>* new_node = new Node<T>(val, node->next);
        node->next = new_node;
        if (node == _tail) {
            _tail = new_node;
        }
        _count++;
    }
}

template <class T>
void List<T>::pop_front() noexcept {
    if (_head == nullptr) return;

    Node<T>* temp = _head;
    _head = _head->next;
    delete temp;
    _count--;

    if (_head == nullptr) {
        _tail = nullptr;
    }
}

template <class T>
void List<T>::pop_back() noexcept {
    if (_tail == nullptr) return;

    if (_head == _tail) {
        delete _head;
        _head = _tail = nullptr;
    }
    else {
        Node<T>* current = _head;
        while (current->next != _tail) {
            current = current->next;
        }
        delete _tail;
        _tail = current;
        _tail->next = nullptr;
    }
    _count--;
}

template <class T>
void List<T>::erase(int pos) {
    if (pos < 0 || pos >= _count) {
        throw std::out_of_range("Position out of range");
    }

    if (pos == 0) {
        pop_front();
    }
    else {
        Node<T>* current = _head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        Node<T>* to_delete = current->next;
        current->next = to_delete->next;

        if (to_delete == _tail) {
            _tail = current;
        }

        delete to_delete;
        _count--;
    }
}

template <class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr || _head == nullptr) return;

    if (node == _head) {
        pop_front();
    }
    else {
        Node<T>* current = _head;
        while (current->next != node && current->next != nullptr) {
            current = current->next;
        }

        if (current->next == node) {
            current->next = node->next;
            if (node == _tail) {
                _tail = current;
            }
            delete node;
            _count--;
        }
    }
}

template <class T>
bool List<T>::isEmpty() const {
    return _head == nullptr;
}

template <class T>
Node<T>* List<T>::find(const T& val) {
    Node<T>* current = _head;
    while (current != nullptr) {
        if (current->value == val) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
T& List<T>::front() {
    if (_head == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return _head->value;
}

template <class T>
T& List<T>::back() {
    if (_tail == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return _tail->value;
}

template <class T>
int List<T>::size() const {
    return _count;
}

template <class T>
void List<T>::clear() {
    while (_head != nullptr) {
        Node<T>* temp = _head;
        _head = _head->next;
        delete temp;
    }
    _tail = nullptr;
    _count = 0;
}

#endif