/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 19/02/2024
  * @brief Este programa simula el comportamiento de un autómata celular
  */


#include <iostream>
#include <fstream>
#include <vector>

#pragma once

// Vector que acepta índices negativos
template <typename T>
class my_vector {
  public:
    T& operator[](std::size_t index) {
      return my_vector_[index];
    }
    const T& operator[](std::size_t index) const { return my_vector_[index]; }
    void resize(std::size_t size) { 
      my_vector_.resize(size); 
    }
    int negative_index() const { return negative_index_; }
    void DecrementNegativeIndex() { negative_index_--; }
    void clear() { my_vector_.clear(); }
    std::size_t size() const { return my_vector_.size(); }
    void push_back(const T& value) { my_vector_.push_back(value); }
    void push_front(const T& value) { my_vector_.insert(my_vector_.begin(), value); }
    
  private:
    std::vector<T> my_vector_;
    int negative_index_{-1};
};