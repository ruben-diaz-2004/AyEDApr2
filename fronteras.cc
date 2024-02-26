/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 19/02/2024
  * @brief Juego de la vida
  */

#include <iostream>
#include "lattice.h"
#include "cell.h"
#include "fronteras.h"
#include "my_vector.h"


/**
 * @brief Constructor de la clase Lattice_Open
*/
Lattice_Open::Lattice_Open(int size_x, int size_y, bool open_type) : Lattice(size_x, size_y) {
  open_type_ = open_type;
  if (open_type == 0) {
    cell_ = new Cell(Position(-100,-100), State::Muerto);
  } else if (open_type == 1) {
    cell_ = new Cell(Position(-100,-100), State::Vivo);
  }
}


/**
 * @brief GetCell de la clase Lattice_Open
 * @param position
 * @return Cell
*/
Cell& Lattice_Open::GetCell(const Position& position) const {
  int x = position.first;
  int y = position.second;
  
  if ( x < 0 || y < 0 || x > lattice_[0].size()-1 || y > lattice_.size()-1) {
    return *cell_;
  } else return *lattice_[y][x];
}



/**
 * @brief GetCell de la clase Lattice_Reflective
 * @param position
 * @return Cell
*/
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



/**
 * @brief GetCell de la clase Lattice_NoBorder
 * @param position
 * @return Cell
*/
Cell& Lattice_NoBorder::GetCell(const Position& position) const {
  int x = position.first;
  int y = position.second;

  if ( x < lattice_[0].negative_index()+1 || y < lattice_.negative_index()+1 ) {
    return *lattice_[0][0];
  }
  if ( x > (lattice_[0].size()+lattice_[0].negative_index()) && x >= 0) {
    return *lattice_[0][0];
  } 
  if ( y > (lattice_.size()+lattice_.negative_index()) && y >= 0) {
    return *lattice_[0][0];
  }
  return *lattice_[y-(lattice_.negative_index()+1)][x+(-(lattice_[0].negative_index()+1))];
}



/**
 * @brief NextGeneration de la clase Lattice_NoBorder
*/
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
  CheckBorder();
}



/**
 * @brief CheckBorder de la clase Lattice_NoBorder
*/
void Lattice_NoBorder::CheckBorder() {
  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[i].size(); j++) {
      if (i == 0 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una fila arriba
        IncrementSize('N');
      }
      if (i == lattice_.size()-1 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una fila abajo
        IncrementSize('S');
      }
      if (j == 0 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una columna a la izquierda
        IncrementSize('W');
      }
      if (j == lattice_[i].size()-1 && lattice_[i][j]->GetState() == State::Vivo) {
        // Añadir una columna a la derecha
        IncrementSize('E');
      }
    }
  }
}



/**
 * @brief IncrementSize de la clase Lattice_NoBorder
 * @param direction
*/
void Lattice_NoBorder::IncrementSize(char direction) {
  my_vector<Cell*> new_row;
  switch (direction) {
    case 'E':
      for (int i = 0; i < lattice_.size(); i++) {
        lattice_[i].push_back(new Cell(Position(lattice_[i].size()-(-(lattice_[i].negative_index()+1)), i+(lattice_.negative_index()+1)), State::Muerto));
      }
      break;
    case 'W':
      for (int i = 0; i < lattice_.size(); i++) {
        lattice_[i].push_front(new Cell(Position(lattice_[i].negative_index(), i+(lattice_.negative_index()+1)), State::Muerto));
        lattice_[i].DecrementNegativeIndex();
      }
      break;
    case 'N':
      new_row.resize(lattice_[0].size());
      new_row.SetNegativeIndex(lattice_[0].negative_index());
      for (int i = 0; i < lattice_[0].size(); i++) {
        new_row[i] = new Cell(Position(i+(lattice_[0].negative_index()+1), lattice_.negative_index()), State::Muerto);
      }
      lattice_.push_front(new_row);
      lattice_.DecrementNegativeIndex();
      break;
    case 'S':
      new_row.resize(lattice_[0].size());
      new_row.SetNegativeIndex(lattice_[0].negative_index());
      for (int i = 0; i < lattice_[0].size(); i++) {
        new_row[i] = new Cell(Position(i+(lattice_[0].negative_index()+1), (lattice_.size()-(-(lattice_.negative_index()+1)))), State::Muerto);
      }
      lattice_.push_back(new_row);
      break;
  }
}