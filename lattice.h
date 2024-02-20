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
#include <vector>
#include <fstream>


#pragma once

class Cell;

class Lattice {
  public:
    Lattice(int size_x, int size_y, std::string& border);
    ~Lattice();
    Cell& GetCell(const Position& position) const;
    void SetInitialConfiguration(std::ifstream& initial_file);
    void NextGeneration();
    friend std::ostream& operator<<(std::ostream& os, const Lattice& lattice);
    friend std::ofstream& operator<<(std::ofstream& os, const Lattice& lattice);
    void SetOpenType(bool open_type);
  private:
    std::vector<std::vector<Cell*>> lattice_;
    int border_; // 0: Abierta, 1: Circular
    bool open_type_; // 0: Fria, 1: Caliente
};