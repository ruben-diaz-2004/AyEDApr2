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


#pragma once

typedef std::pair<int, int> Position;

class Lattice;

class Cell {
  public:
    Cell(const Position position, const char state);
    int GetState();
    void SetState(char state);
    void NextState(Lattice& lattice);
    void UpdateState();
    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
  private:
    Position position_;
    char state_;
    char next_state_;
};

