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
Lattice::Lattice(int size_x, int size_y) {
  lattice_.resize(size_y);

  for (int i{0}; i < size_y; ++i) {
    lattice_[i].resize(size_x);
    for (int j{0}; j < size_x; ++j) {
      lattice_[i][j] = new Cell(Position(j, i), 0);
    }
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



Cell& Lattice::GetCell(const Position& position) const {
  return *lattice_[position.second][position.first];
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



std::size_t Lattice::Population() const {
  std::size_t population = 0;
  for (int i = 0; i < lattice_.size(); i++) {
    for (int j = 0; j < lattice_[i].size(); j++) {
      population += lattice_[i][j]->GetState();
    }
  }
  return population;
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