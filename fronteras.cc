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
#include "my_vector.h"

Lattice_Open::Lattice_Open(int size_x, int size_y, bool open_type) : Lattice(size_x, size_y) {
  open_type_ = open_type;
  if (open_type == 0) {
    cell_ = new Cell(Position(-100,-100), State::Muerto);
  } else if (open_type == 1) {
    cell_ = new Cell(Position(-100,-100), State::Vivo);
  }
}

Cell& Lattice_Open::GetCell(const Position& position) const {
  int x = position.first;
  int y = position.second;
  
  if ( x < 0 || y < 0 || x > lattice_[0].size()-1 || y > lattice_.size()-1) {
    // if (open_type_ == 0) {
    // } else if (open_type_ == 1) {
    //   Cell* cell = new Cell(Position(-100,-100), State::Vivo);
    //   return *cell;
    // }
    return *cell_;
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




Cell& Lattice_NoBorder::GetCell(const Position& position) const {
  int x = position.first;
  int y = position.second;
  // if ( x < lattice_[0].negative_index() || y < lattice_.negative_index() || x > lattice_[0].positive_index() || y > lattice_.positive_index()) {
  //   return *lattice_[0][0];
  // } else
  // return *lattice_[y][x];

  if ( x < 0 || y < 0 || x > lattice_[0].size()-1 || y > lattice_.size()-1) {
    Cell* cell = new Cell(Position(-100,-100), State::Muerto);
    return *cell;
  } else return *lattice_[y][x];
}


void Lattice_NoBorder::NextGeneration() {

  CheckBorder();

  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[i].size(); j++) {
      lattice_[i][j]->NextState(*this);
    }
  }

  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[i].size(); j++) {
      lattice_[i][j]->UpdateState();
    }
  }
}


void Lattice_NoBorder::CheckBorder() {

  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[i].size(); j++) {
      if (i == 0 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una fila arriba
        std::cout << "Añadir fila arriba\n";
        IncrementSize('N');
      }
      if (i == lattice_.size()-1 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una fila abajo
        std::cout << "Añadir fila abajo\n";
        IncrementSize('S');
      }
      if (j == 0 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una columna a la izquierda
        std::cout << "Añadir columna a la izquierda\n";
        IncrementSize('W');
      }
      if (j == lattice_[i].size()-1 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una columna a la derecha
        std::cout << "Añadir columna a la derecha\n";
        IncrementSize('E');
      }
    }
  }
}

void Lattice_NoBorder::IncrementSize(char direction) {
  my_vector<Cell*> new_row;
  switch (direction) {
    case 'E':
      for (int i = 0; i < lattice_.size(); i++) {
        lattice_[i].push_back(new Cell(Position(lattice_[i].positive_index(), i), State::Muerto));
        lattice_[i].IncrementPositiveIndex();
      }
      break;
    case 'W':
      for (int i = 0; i < lattice_.size(); i++) {
        lattice_[i].push_front(new Cell(Position(lattice_[i].negative_index(), i), State::Muerto));
        lattice_[i].DecrementNegativeIndex();
      }
      break;
    case 'N':
      new_row.resize(lattice_[0].size());
      for (int i = 0; i < lattice_[0].size(); i++) {
        new_row[i] = new Cell(Position(i, lattice_.negative_index()), State::Muerto);
      }
      lattice_.push_front(new_row);
      lattice_.DecrementNegativeIndex();
      break;
    case 'S':
      new_row.resize(lattice_[0].size());
      for (int i = 0; i < lattice_[0].size(); i++) {
        new_row[i] = new Cell(Position(i, lattice_.positive_index()), State::Muerto);
      }
      lattice_.push_back(new_row);
      lattice_.IncrementPositiveIndex();
      break;
  }
}