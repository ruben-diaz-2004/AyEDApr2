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
    Cell& GetCell(const Position& position) const;
  private:
    bool open_type_; // 0 = frio, 1 = caliente
};


class Lattice_Periodic : public Lattice {
  public:
    Cell& GetCell(const Position& position) const;
};

class Lattice_Reflective : public Lattice {
  public:
    Lattice_Reflective(int size_x, int size_y) : Lattice(size_x, size_y) {};
    Cell& GetCell(const Position& position) const;
};

class Lattice_NoBorder : public Lattice {
  public:
    Cell& GetCell(const Position& position) const;
};  







#endif