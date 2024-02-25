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

#ifndef FRONTERAS_H
#define FRONTERAS_H


class Lattice_Open : public Lattice {
  public:
    Lattice_Open(int size_x, int size_y, bool open_type);
    Lattice_Open(std::ifstream& initial_file, bool open_type) : Lattice(initial_file) {
      open_type_ = open_type;
      if (open_type == 0) {
        cell_ = new Cell(Position(-100,-100), State::Muerto);
      } else if (open_type == 1) {
        cell_ = new Cell(Position(-100,-100), State::Vivo);
      }
    }
    Cell& GetCell(const Position& position) const;
  private:
    Cell* cell_;
    bool open_type_; // 0 = frio, 1 = caliente
};


class Lattice_Periodic : public Lattice {
  public:
    Cell& GetCell(const Position& position) const;
};

class Lattice_Reflective : public Lattice {
  public:
    Lattice_Reflective(int size_x, int size_y) : Lattice(size_x, size_y) {};
    Lattice_Reflective(std::ifstream& initial_file) : Lattice(initial_file) {};
    Cell& GetCell(const Position& position) const;
};

class Lattice_NoBorder : public Lattice {
  public:
    Lattice_NoBorder(int size_x, int size_y) : Lattice(size_x, size_y) {};
    Lattice_NoBorder(std::ifstream& initial_file) : Lattice(initial_file) {};
    Cell& GetCell(const Position& position) const;
    void NextGeneration();
    void CheckBorder();
    void IncrementSize(char direction);
};  







#endif