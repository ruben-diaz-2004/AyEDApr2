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
  int x = position.first;
  int y = position.second;
  
  if ( x < 0 || y < 0 || x > lattice_[0].size()-1 || y > lattice_.size()-1) {
    if (open_type_ == 0) {
      Cell* cell = new Cell(Position(-100,-100), State::Muerto);
      return *cell;
    } else if (open_type_ == 1) {
      Cell* cell = new Cell(Position(-100,-100), State::Vivo);
      return *cell;
    }
  } else return *lattice_[y][x];
}




Cell& Lattice_Reflective::GetCell(const Position& position) const {
  int x = position.first;
  int y = position.second;
  
  if ( x < 0 || y < 0 || x > lattice_[0].size()-1 || y > lattice_.size()-1) {
    if (x < 0) {
      x = 0;
      if (y < 0) {
        y = 0;
      } else if (y > lattice_.size()-1) {
        y = lattice_.size()-1;
      }
    }
    if (x > lattice_[0].size()-1) {
      x = lattice_[0].size()-1;
      if (y < 0) {
        y = 0;
      } else if (y > lattice_.size()-1) {
        y = lattice_.size()-1;
      }
    }
    if (y < 0) {
      y = 0;
      if (x < 0) {
        x = 0;
      } else if (x > lattice_[0].size()-1) {
        x = lattice_[0].size()-1;
      }
    }
    if (y > lattice_.size()-1) {
      y = lattice_.size()-1;
      if (x < 0) {
        x = 0;
      } else if (x > lattice_[0].size()-1) {
        x = lattice_[0].size()-1;
      }
    }
  }
  return *lattice_[y][x];
}

