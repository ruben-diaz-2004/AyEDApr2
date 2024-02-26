/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 19/02/2024
  * @brief Jugador de la vida
  */


#include <iostream>
#include <vector>
#include <fstream>
#include "cell.h"
#include "my_vector.h"

#pragma once

class Cell;

class Lattice {
  public:
    Lattice(int size_x, int size_y);
    Lattice(std::ifstream& initial_file);
    ~Lattice();
    virtual Cell& GetCell(const Position& position) const;
    void SetInitialConfiguration(std::ifstream& initial_file);
    virtual void NextGeneration();
    std::size_t Population() const;
    friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);
    friend std::ofstream& operator<<(std::ofstream& os, const Lattice& lattice);
  protected:
    // std::vector<std::vector<Cell*>> lattice_;
    my_vector<my_vector<Cell*>> lattice_;
};