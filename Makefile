# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Asignatura: Computabilidad y Algoritmia
# 
# @author Rubén Díaz Marrero
# @date 18/12/2023
# 

CXX = g++
CXXFLAGS = -Wall -std=c++17 -g 



all: CellularAutomaton

CellularAutomaton: CellularAutomaton.cc cell.cc lattice.cc fronteras.cc
		$(CXX) $(CXXFLAGS) -o $@ $^
	

	
.PHONY: all clean
clean:
		rm -f CellularAutomaton