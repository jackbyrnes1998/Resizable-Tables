//
// Created by Jack Byrnes on 2019-02-04.
//
#ifndef HW3_TABLE_H
#define HW3_TABLE_H

#include <iostream>
#include <vector>


template<class T>
class Table {

public:
    // TYPEDEFS
    typedef unsigned int size_type;


    // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
    Table(size_type row, size_type column, const T &new_input);

    Table(const Table &new_table) { copy(new_table); }

    Table &operator=(const Table &new_table);

    const T get(size_type row, size_type column);

    const int numRows();

    const int numColumns();

    void print();

    void set(size_type row, size_type column, const T &new_input);

    void push_back_row(const std::vector<T> &new_vector);

    void pop_back_row();

    void pop_back_column();

    void push_back_column(const std::vector<T> &new_vector);

    ~Table() { delete_table(); }

private:
    // Private Function
    void copy(const Table<T> &new_table);

    void delete_table();

    // Representation
    size_type row_size;      // Number of elements stored in the row
    size_type column_size;   // Number of elements stored in the column
    T **value;   // an 2D array of pointers
};


// Declear a private destructor so you don't have to write those delete lines everytime
template<class T>
void Table<T>::delete_table() {
    for (int i = 0; i < row_size; i++) {
        delete[] value[i];
    }
    delete[] value;
}


// Constructor
template<class T>
Table<T>::Table(size_type row, size_type column, const T &new_input) {
    row_size = row;
    column_size = column;

    value = new T *[row_size]; // 2d array, pointer to a pointer

    for (int i = 0; i < row_size; i++) {
        value[i] = new T[column_size];
        for (int j = 0; j < column_size; j++) {
            value[i][j] = new_input;
        }
    }

}


//
template<class T>
const T Table<T>::get(unsigned int arow, unsigned int acolumn) {
    if (arow > row_size or acolumn > column_size) {
        std::cerr << "Index out of range!" << std::endl;  // Check index, if out of range, break out
        exit(1);
    }
    return value[arow][acolumn];
}


template<class T>
void Table<T>::set(unsigned int arow, unsigned int acolumn, const T &new_input) {
    if (arow > row_size or acolumn > column_size) {
        std::cerr << "Index out of range!" << std::endl;  // Check index, if out of range, break out
        exit(1);
    }
    value[arow][acolumn] = new_input;
}


template<class T>
const int Table<T>::numColumns() {
    return column_size;
}


template<class T>
const int Table<T>::numRows() {
    return row_size;
}


template<class T>
void Table<T>::print() {
    std::cout << "table: " << row_size << " rows, " << column_size << " cols" << std::endl;
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < column_size; j++) {
            std::cout << value[i][j] << " ";
            if (j == column_size - 1) std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}


template<class T>
void Table<T>::push_back_row(const std::vector<T> &new_vector) {

    T **temp_vector = new T *[row_size + 1];

    for (int i = 0; i < row_size; i++) {
        temp_vector[i] = value[i];
    }
    temp_vector[row_size] = new T[column_size];
    //std::cout << row_size << " " << row_size + 1 << std::endl;


    delete[] value; // delete row pointer


    value = temp_vector; // make value points to temp to get result

    for (int j = 0; j < column_size; j++) {
        value[row_size][j] = new_vector[j];
    }
    row_size += 1;
}


template<class T>
void Table<T>::pop_back_column() {
    T **temp_vector = new T *[row_size];

    for (int i = 0; i < row_size; i++) {
        temp_vector[i] = new T[column_size - 1];
        for (int j = 0; j < column_size - 1; j++) {
            temp_vector[i][j] = value[i][j];
        }
    }

    for (int i = 0; i < row_size; i++) {
        delete[] value[i];
    }
    delete[] value;

    value = temp_vector;

    column_size -= 1;
}


template<class T>
void Table<T>::push_back_column(const std::vector<T> &new_vector) {
    T **temp_vector = new T *[row_size];

    for (int i = 0; i < row_size; i++) {
        temp_vector[i] = new T[column_size + 1];
        for (int j = 0; j < column_size; j++) {
            temp_vector[i][j] = value[i][j];
        }
    }

    for (int i = 0; i < row_size; i++) {
        // std::cout << value[i] << std::endl;
        delete[] value[i];
    }
    delete[] value;


    value = temp_vector;
    column_size += 1;
    for (int i = 0; i < row_size; i++) {
        value[i][column_size - 1] = new_vector[i];
    }


}


template<class T>
void Table<T>::pop_back_row() {

    T **temp_vector = new T *[row_size - 1];

    for (int i = 0; i < row_size - 1; i++) {
        temp_vector[i] = value[i];
    }

    delete [] value[row_size - 1];

    delete[] value;

    value = temp_vector;
    row_size -= 1;

}


template<class T>
void Table<T>::copy(const Table<T> &new_table) {
    row_size = new_table.row_size;
    column_size = new_table.column_size;
    value = new T *[row_size];

    for (int i = 0; i < row_size; i++) {
        value[i] = new T[column_size];
        for (int j = 0; j < column_size; j++) {
            value[i][j] = new_table.value[i][j];
        }
    }
}


template<class T>
Table<T> &Table<T>::operator=(const Table &new_table) {
    if (this != &new_table) {
        delete_table();
        this->copy(new_table);
    }
    return *this;
}


#endif //HW3_TABLE_H
