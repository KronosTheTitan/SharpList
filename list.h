//
// Created by Tjalle Borgers on 22/04/2026.
//

#ifndef SHARPLIST_LIST_H
#define SHARPLIST_LIST_H

template <typename T> class list {
public:
    const int LIST_INITIAL_CAPACITY = 256;

    list();
    ~list();

    void add(T item);
    void add_range(T* items, int n);
    void remove(T item);
    void remove_range(T* items, int n);
    void remove_at(int index);
    void clear();
    void reverse();
    void trim_excess();

    bool contains(T* item);

    T& operator[](int index);

    const int& count = this->size;
private:
    void grow();

    int size = 0;
    int capacity = 256;

    T* buffer;
};

#endif //SHARPLIST_LIST_H
