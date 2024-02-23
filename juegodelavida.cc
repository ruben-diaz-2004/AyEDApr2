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
#include "parameters.cc"
#include "cell.h"
#include "lattice.h"
#include "fronteras.h"
#include <sstream>
#include <string>


int main(int argc, char *argv[]) {
  parameters options = parse_args(argc, argv);

 // -size <n>, Tamaño del retículo
 // -border <b [v]>, b=open, v=[0|1]. Frontera abierta, fría o caliente. b=periodic
 //  std::ifstream initial_file{argv[3]}; // [-init <file], (opcional) Configuración inicial del retículo

  std::cout << "size: " << options.size_x << " * " << options.size_y << std::endl;
  std::cout << "border: " << options.border << std::endl;
  std::cout << "Options menu:" << std::endl << "'x' to exit.\n's' to save configuration.\n'n' to show next generation.\n";
  std::cout << "'L' to show next 5 generations.\n'c' to show population.\n";

  // Lattice lattice(options.size_x, options.size_y, options.border);
  // if (options.initial_file) {
  //   lattice.SetInitialConfiguration(options.filename);
  // }
  // std::cout << lattice << std::endl;


  Lattice* lattice;
  switch(options.border) {
    case 0:
      lattice = new Lattice_Open(options.size_x, options.size_y, options.open_type);
      break;
    case 2:
      lattice = new Lattice_Reflective(options.size_x, options.size_y);
      break;
  }

  if (options.initial_file) {
    lattice->SetInitialConfiguration(options.filename);
  }

  bool running = true;
  char stop;
  while(running) {
    std::cin >> stop;
    switch (stop) {
      case 'x':
        running = false;
        break;
      case 'n': // Calcula y muestra la siguiente generación
        lattice->NextGeneration();
        std::cout << *lattice << std::endl;
        break;
      case 'L': // Calcula y muestra las siguientes 5 generaciones
        for (int i = 0; i < 5; i++) {
          lattice->NextGeneration();
          std::cout << *lattice << std::endl;
        }
        break;
      case 'c': // Se muestra la población (número de células vivas) actual
        std::cout << lattice->Population() << std::endl;
        break;
      case 's': // Guarda la configuración actual en un fichero
        std::string file_name;
        std::cin >> file_name;
        std::ofstream output_file{file_name};
        output_file << *lattice;
        output_file.close();
        break;
    }
  }

  return 0;
}