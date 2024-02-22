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
#include "lattice.h"
#include "cell.h"
#include "fronteras.h"


Lattice_Open::Lattice_Open(int size_x, int size_y, bool open_type) : Lattice(size_x, size_y) {
  open_type_ = open_type;
}

Cell& Lattice_Open::GetCell(const Position& position) const {
    if (position.first < 0 || position.second < 0 || position.first > lattice_[0].size()-1 || position.second > lattice_.size()-1) {
      if (open_type_ == 0) {
        Cell* cell = new Cell(Position(-100,-100), 0);
        return *cell;
      } else if (open_type_ == 1) {
        Cell* cell = new Cell(Position(-100,-100), 1);
        return *cell;
      }
    } else return *lattice_[position.second][position.first];
}