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
#include "my_vector.h"

template <typename T>
void my_vector<T>::resize(std::size_t size) {
  my_vector_.resize(size);
  positive_index_ = size-1;
}

template <typename T>
void my_vector<T>::push_back(const T& value) {
  my_vector_.push_back(value);
}