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
#include "cell.h"
#include "lattice.h"


/**
 * Constructor de la clase Cell
 * @param position Posición de la célula
 * @param state Estado de la célula
*/
Cell::Cell(const Position position, const char state) {
  position_ = position;
  state_ = state;
}


/**
 * Devuelve el estado de la célula
 * @return Estado de la célula
*/
int Cell::GetState() {
  return state_;
}


/**
 * Establece el estado de la célula
 * @param state Estado de la célula
*/
void Cell::SetState(char state) {
    state_ = state;
}


/**
 * @brief Aplica la función de transición de estados
 * @param lattice Reticulo de células
*/
void Cell::NextState(Lattice& reticulo) {
  int alive_count{0};
  int next_state{0};

  const int C = state_;
  if (C == 1) alive_count++;
  int E = reticulo.GetCell(Position(position_.first-1, position_.second)).GetState();
  if (E == 1) alive_count++;
  int W = reticulo.GetCell(Position(position_.first+1, position_.second)).GetState();
  if (W == 1) alive_count++;
  int N = reticulo.GetCell(Position(position_.first, position_.second-1)).GetState();
  if (N == 1) alive_count++;
  int S = reticulo.GetCell(Position(position_.first, position_.second+1)).GetState();
  if (S == 1) alive_count++;
  int NE = reticulo.GetCell(Position(position_.first-1, position_.second-1)).GetState();
  if (NE == 1) alive_count++;
  int NW = reticulo.GetCell(Position(position_.first+1, position_.second-1)).GetState();
  if (NW == 1) alive_count++;
  int SE = reticulo.GetCell(Position(position_.first-1, position_.second+1)).GetState();
  if (SE == 1) alive_count++;
  int SW = reticulo.GetCell(Position(position_.first+1, position_.second+1)).GetState();
  if (SW == 1) alive_count++;

  if (C == 0) {
    if (alive_count == 3) {
      next_state = 1;
    }
  } else {
    if (alive_count < 2 || alive_count > 3) {
      next_state = 0;
    } else {
      next_state = 1;
    }
  }
  // int L = reticulo.GetCell(position_ - 1).GetState();
  // int R = reticulo.GetCell(position_ + 1).GetState();  


  next_state_ = next_state;
}


/**
 * Actualiza el estado de la célula
*/
void Cell::UpdateState() {
  state_ = next_state_;
}


/**
 * Sobrecarga del operador de salida
 * @param os Flujo de salida
 * @param cell Célula
 * @return Flujo de salida
*/
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  if (cell.state_ == 0) {
    os << "-";
  } else {
    os << "X";
  }
  return os;
}