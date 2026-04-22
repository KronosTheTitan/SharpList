//
// Created by Tjalle Borgers on 22/04/2026.
//

#ifndef SHARPLIST_LIST_H
#define SHARPLIST_LIST_H

#define DEBUG

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

    bool contains(T item);

    T& operator[](int index);

    const int& count = this->size;
private:
    void grow();

    int size = 0;
    int capacity = 256;

    T* buffer;
};

//Definitions

template <typename T>
list<T>::list()
{
    buffer = static_cast<T*>(malloc(sizeof(T) * capacity));
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
    this->buffer = static_cast<T*>(malloc(sizeof(T) * LIST_INITIAL_CAPACITY));
    this->size = 0;
    this->capacity = LIST_INITIAL_CAPACITY;
}

template <typename T>
void list<T>::reverse()
{
    int l = 0;
    int r = this->size - 1;
    while (l < r)
    {
        std::swap(buffer[l], buffer[r]);

        l++;
        --r;
    }
}

template <typename T>
void list<T>::trim_excess()
{
    T* old = this->buffer;
    this->capacity = this->size;
    this->buffer = static_cast<T*>(malloc(sizeof(T) * this->capacity));

    for (int i = 0; i < this->size; i++) {
        this->buffer[i] = old[i];
    }

    free(old);

    #ifdef DEBUG
    printf("Decreased capacity to %d\n",this->capacity);
    #endif

}

template <typename T>
bool list<T>::contains(T item)
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
    this->buffer = static_cast<T*>(malloc(sizeof(T) * this->capacity));

    for (int i = 0; i < this->size; i++) {
        this->buffer[i] = old[i];
    }

    free(old);

#ifdef DEBUG
    printf("Increased capacity to %d\n",this->capacity);
#endif
}

#endif //SHARPLIST_LIST_H
