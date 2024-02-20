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

#include "cell.h"
#include "lattice.h"



/**
 * Constructor de la clase Lattice
 * @param size Tamaño del retículo
 * @param border Tipo de borde
 */
Lattice::Lattice(int size_x, int size_y, std::string& border) {
  lattice_.resize(size_y);

  for (int i{0}; i < size_y; ++i) {
    lattice_[i].resize(size_x);
    for (int j{0}; j < size_x; ++j) {
      lattice_[i][j] = new Cell(Position(j, i), 0);
    }
  }

  if (border == "open") {
    border_ = 0;
  }
  else if (border == "periodic") {
    border_ = 1;
  }
  else {
    std::cerr << "Error: border no válido" << std::endl;
  }
}


/**
 * Destructor de la clase Lattice
 */
Lattice::~Lattice() {
  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[i].size(); j++) {
      delete lattice_[i][j];
    }
  }
  lattice_.clear();
}

/**
 * Devuelve la célula en la posición indicada
 * @param position Posición de la célula
 * @return Célula en la posición indicada
 */
Cell& Lattice::GetCell(const Position& position) const {

  switch (border_) {
  case 0: // Open border
    if (position.first < 0 || position.second < 0 || position.first > lattice_[0].size()-1 || position.second > lattice_.size()-1) {
      if (open_type_ == 0) {
        Cell* cell = new Cell(Position(-100,-100), 1);
        return *cell;
      } else if (open_type_ == 1) {
        Cell* cell = new Cell(Position(-100,-100), 0);
        return *cell;
      }
    } else return *lattice_[position.second][position.first];
    break;
  // case 1:
  //   if (position < 0) {
  //     return *lattice_[lattice_.size()-1];
  //   } else if (position > lattice_.size()-1) {
  //       return *lattice_[0];
  //     } else return *lattice_[position];
  //   break;
  default:
    break;
  }
}


/**
 * Calcula la siguiente generación del autómata
 */
void Lattice::NextGeneration() {

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


/**
 * Establece el tipo de borde abierto
 * @param open_type Tipo de borde abierto
 */
void Lattice::SetOpenType(bool open_type) {
  open_type_ = open_type;
}



/**
 * Establece la configuración inicial del retículo
 * @param initial_file Archivo con la configuración inicial
 */
void Lattice::SetInitialConfiguration(std::ifstream& initial_file) {
  std::string line;
  int i = 0;
  while (std::getline(initial_file, line)) {
    for (int j = 0; j < line.size(); j++) {
      if (line[j] == '0') {
        lattice_[i][j]->SetState(0);
      } else if (line[j] == '1') {
        lattice_[i][j]->SetState(1);
      }
    }
    i++;
  }
}



/**
 * Sobrecarga del operador de salida
 * @param os Flujo de salida
 * @param lattice Reticulo de células
 * @return Flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.lattice_.size(); i++) {
    for (int j = 0; j < lattice.lattice_[i].size(); j++) {
      os << *lattice.lattice_[i][j];
    }
    os << std::endl;
  }
  return os;
}



/**
 * Sobrecarga del operador de salida
 * @param os Flujo de salida
 * @param lattice Reticulo de células
 * @return Flujo de salida
 */
std::ofstream& operator<<(std::ofstream& os, const Lattice& lattice) {
  for (int i = 0; i < lattice.lattice_.size(); i++) {
    for (int j = 0; j < lattice.lattice_[i].size(); j++) {
      os << lattice.lattice_[i][j]->GetState();
    }
    os << std::endl;
  }
  return os;
}