//
// Created by Tjalle Borgers on 22/04/2026.
//

#include "list.h"

#include <cstdio>
#include <list>
#include <stdexcept>

#define DEBUG

template <typename T>
list<T>::list()
{
    buffer = malloc(sizeof(T*) * capacity);
}

template <typename T>
list<T>::~list()
{
    free(this->buffer);
}

template <typename T>
void list<T>::add(T item)
{
    if (this->size > this->capacity) {
        this->grow();
    }
    this->buffer[this->size] = item;
    this->size += 1;
}

template <typename T>
void list<T>::add_range(T* items, const int n)
{
    for (int i = 0; i < n; i++)
    {
        this->add(items[i]);
    }
}

template <typename T>
void list<T>::remove(T item)
{
    int index = -1;
    for (int i = 0; i < this->size; i++) {
        if (this->buffer[i] == item)
            index = i;
    }
    if (index == -1) {
        return;
    }

    remove_at(index);
}

template <typename T>
void list<T>::remove_range(T* items, const int n)
{
    for (int i = 0; i < n; i++)
    {
        this->remove(items[i]);
    }
}

template <typename T>
void list<T>::remove_at(const int index)
{
    for (int i = index; i < this->size - 1; i++) {
        this->buffer[i] = this->buffer[i + 1];
    }
    this->size -= 1;
}

template <typename T>
void list<T>::clear()
{
    free(this->buffer);
    this->buffer = malloc(sizeof(T*) * LIST_INITIAL_CAPACITY);
    this->size = 0;
    this->capacity = LIST_INITIAL_CAPACITY;
}

template <typename T>
void list<T>::reverse()
{
    T** old = this->buffer;
    this->buffer = malloc(sizeof(T*) * this->capacity);

    for (int i = 0; i < this->size; i++) {
        this->buffer[i] = old[size - i];
    }

    free(old);
}

template <typename T>
void list<T>::trim_excess()
{
    T** old = this->buffer;
    this->capacity = this->size;
    this->buffer = malloc(sizeof(T*) * this->capacity);

    for (int i = 0; i < this->size; i++) {
        this->buffer[i] = old[i];
    }

    free(old);

    #ifdef DEBUG
    printf("Decreased capacity to %d\n",this->capacity);
    #endif

}

template <typename T>
bool list<T>::contains(T* item)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->buffer[i] != item)
            continue;

        return true;
    }
    return false;
}

template <typename T>
T& list<T>::operator[](int index)
{
    if (index >= this->size)
        throw std::out_of_range("");

    return this->buffer[index];
}

template <typename T>
void list<T>::grow()
{
    T* old = this->buffer;
    this->capacity *= 2;
    this->buffer = malloc(sizeof(T) * this->capacity);

    for (int i = 0; i < this->size; i++) {
        this->buffer[i] = old[i];
    }

    free(old);

    #ifdef DEBUG
    printf("Increased capacity to %d\n",this->capacity);
    #endif
}
