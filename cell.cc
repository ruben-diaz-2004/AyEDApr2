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
Cell::Cell(const Position position, const State state) {
  position_ = position;
  state_ = state;
}


/**
 * Devuelve el estado de la célula
 * @return Estado de la célula
*/
State& Cell::GetState() {
  return state_;
}


/**
 * Establece el estado de la célula
 * @param state Estado de la célula
*/
void Cell::SetState(State state) {
    state_ = state;
}


/**
 * @brief Aplica la función de transición de estados
 * @param lattice Reticulo de células
*/
void Cell::NextState(Lattice& reticulo) {
  int alive_count{0};
  State next_state;

  const State C = state_;
  State E = reticulo.GetCell(Position(position_.first+1, position_.second)).GetState();
  if (E == State::Vivo) alive_count++;
  State W = reticulo.GetCell(Position(position_.first-1, position_.second)).GetState();
  if (W == State::Vivo) alive_count++;
  State N = reticulo.GetCell(Position(position_.first, position_.second-1)).GetState();
  if (N == State::Vivo) alive_count++;
  State S = reticulo.GetCell(Position(position_.first, position_.second+1)).GetState();
  if (S == State::Vivo) alive_count++;
  State NE = reticulo.GetCell(Position(position_.first+1, position_.second-1)).GetState();
  if (NE == State::Vivo) alive_count++;
  State NW = reticulo.GetCell(Position(position_.first-1, position_.second-1)).GetState();
  if (NW == State::Vivo) alive_count++;
  State SE = reticulo.GetCell(Position(position_.first+1, position_.second+1)).GetState();
  if (SE == State::Vivo) alive_count++;
  State SW = reticulo.GetCell(Position(position_.first-1, position_.second+1)).GetState();
  if (SW == State::Vivo) alive_count++;

  if (C == State::Muerto) {
    if (alive_count == 3) {
      next_state = State::Vivo;
    }
    else {
      next_state = State::Muerto;
    }
  } else {
    if (alive_count < 2 || alive_count > 3) {
      next_state = State::Muerto;
    } else {
      next_state = State::Vivo;
    }
  }  
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