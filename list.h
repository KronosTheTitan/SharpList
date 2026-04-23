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
    list(const T* items, int n);
    list(int initial_capacity);
    ~list();

    void add(T item);
    void add_range(T* items, int n);
    int ensure_capacity(int desired_capacity);
    void remove(T item);
    void remove_range(T* items, int n);
    void remove_at(int index);
    void clear();
    void reverse();
    void trim_excess();

    bool contains(T item);

    T& operator[](int index);

    T* to_array();

    const int& count = this->size;
private:
    void grow();

    int size = 0;
    int capacity = LIST_INITIAL_CAPACITY;

    T* buffer;
};

//Definitions

///Initializes a new instance of the List<T> class that is empty and has the default initial capacity.
template <typename T>
list<T>::list()
{
    buffer = static_cast<T*>(malloc(sizeof(T) * capacity));
}
///Initializes a new instance of the List<T> class that contains elements copied from the specified collection and has sufficient capacity to accommodate the number of elements copied.
template <typename T>
list<T>::list(const T* items, const int n)
{
    capacity = n;
    buffer = static_cast<T*>(malloc(sizeof(T) * capacity));
    memcpy(buffer, items, sizeof(T) * capacity);
}
///Initializes a new instance of the List<T> class that is empty and has the specified initial capacity.
template <typename T>
list<T>::list(const int initial_capacity)
{
    capacity = initial_capacity;
    buffer = static_cast<T*>(malloc(sizeof(T) * capacity));
}

template <typename T>
list<T>::~list()
{
    free(this->buffer);
}
///Adds an object to the end of the List<T>.
template <typename T>
void list<T>::add(T item)
{
    if (this->size > this->capacity) {
        this->grow();
    }
    this->buffer[this->size] = item;
    this->size += 1;
}
///Adds the elements of the specified collection to the end of the List<T>.
template <typename T>
void list<T>::add_range(T* items, const int n)
{
    for (int i = 0; i < n; i++)
    {
        this->add(items[i]);
    }
}
///Ensures that the capacity of this list is at least the specified capacity. If the current capacity is less than capacity, it is increased to at least the specified capacity.
template <typename T>
int list<T>::ensure_capacity(int desired_capacity)
{
    if (desired_capacity < this->capacity)
        return this->capacity;

    this->capacity = desired_capacity;

    const T* old = this->buffer;
    this->buffer = static_cast<T*>(malloc(sizeof(T) * desired_capacity));

    memcpy(this->buffer, old, this->size * sizeof(T));

    return this->capacity;
}
///Removes the first occurrence of a specific object from the List<T>.
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
///Removes all the elements that match the conditions defined by the specified predicate.
template <typename T>
void list<T>::remove_range(T* items, const int n)
{
    for (int i = 0; i < n; i++)
    {
        this->remove(items[i]);
    }
}
///Removes the element at the specified index of the List<T>.
template <typename T>
void list<T>::remove_at(const int index)
{
    for (int i = index; i < this->size - 1; i++) {
        this->buffer[i] = this->buffer[i + 1];
    }
    this->size -= 1;
}
///Removes all elements from the List<T>.
template <typename T>
void list<T>::clear()
{
    free(this->buffer);
    this->buffer = static_cast<T*>(malloc(sizeof(T) * LIST_INITIAL_CAPACITY));
    this->size = 0;
    this->capacity = LIST_INITIAL_CAPACITY;
}
///Reverses the order of the elements in the entire List<T>.
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
///Sets the capacity to the actual number of elements in the List<T>, if that number is less than a threshold value.
template <typename T>
void list<T>::trim_excess()
{
    T* old = this->buffer;
    this->capacity = this->size;
    this->buffer = static_cast<T*>(malloc(sizeof(T) * this->capacity));

    memcpy(this->buffer, old, this->size * sizeof(T));

    free(old);

    #ifdef DEBUG
    printf("Decreased capacity to %d\n",this->capacity);
    #endif

}
///Determines whether an element is in the List<T>.
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
///Copies the elements of the List<T> to a new array.
template <typename T>
T* list<T>::to_array()
{
    T* array = static_cast<T*>(malloc((this->size) * sizeof(T)));

    memcpy(array, this->buffer, this->size * sizeof(T));

    return array;
}

template <typename T>
void list<T>::grow()
{
    T* old = this->buffer;
    this->capacity *= 2;
    this->buffer = static_cast<T*>(malloc(sizeof(T) * this->capacity));

    memcpy(this->buffer, old, this->size * sizeof(T));

    free(old);

#ifdef DEBUG
    printf("Increased capacity to %d\n",this->capacity);
#endif
}

#endif //SHARPLIST_LIST_H
