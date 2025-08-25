// polygonal_surface_reconstruction_test.cpp
//
// Test the Polygonal Surface Reconstruction method with different
//    - kernels(Simple_cartesian, EPICK)
//    - solvers(GLPK, SCIP)
//    - use/ignore provided planar segmentation
//    - input file formats (pwn, ply). For ply format, a property "segment_index"
//      must be present storing the plane index for each point(-1 if the point is
//      not assigned to a plane).

#include <iostream>


//#include <CGAL/GLPK_mixed_integer_program_traits.h>
//typedef CGAL::GLPK_mixed_integer_program_traits<double>                                GLPK_Solver;

#include <CGAL/SCIP_mixed_integer_program_traits.h>

typedef CGAL::SCIP_mixed_integer_program_traits < double > SCIP_Solver;

#include <CGAL/Simple_cartesian.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include "polygonal_surface_reconstruction_test_framework.h"

// kernels:
typedef CGAL::Simple_cartesian < double > Cartesian;
typedef CGAL::Exact_predicates_inexact_constructions_kernel Epick;

int main(int argc, char * argv[]) {
  if (argc < 4) {
    std::cerr << "NOT ENOUGH ARGUMENTS" << std::endl;
    std::cerr << "THE CALL OF PROGRAMM SHOULD MUST LOOK LIKE: " << argv[0] << " <input_file> <solver_name> <kernel_name>" << std::endl;
    std::cerr << "AVALIABLE SOLVERS: \n SCIP \n GLPK" << std::endl;
    std::cerr << "AVALIABLE KERNELS: \n Cartesian \n Epick" << std::endl;
    return 1;
  }

  const std::string input_file = argv[1];
  const std::string solverName = argv[2];
  const std::string kernelName = argv[3];

  std::cout << "Input file: " << input_file << std::endl;
  std::cout << "Name of solver: " << solverName << std::endl;
  std::cout << "Name of kernel: " << kernelName << std::endl;
  std::cerr << "Testing the Polygonal Surface Reconstruction method...\n";

  if (kernelName == "Cartesian") {
    std::cerr << "--- Using Simple cartesian kernel";
    // if (solverName=="GLPK") {
    //     std::cerr << "\n\t---- Using GLPK solver\n";
    //
    //     std::cerr << "\t\t---- using provided planes\n";
    //     reconstruct<Cartesian, GLPK_Solver>(input_file, false);
    //
    //     std::cerr << "\t\t---- re-extract planes\n";
    //     reconstruct<Cartesian, GLPK_Solver>(input_file, true);
    // }

    if (solverName == "SCIP") {
      std::cerr << "\n\t---- Using SCIP solver\n";

      std::cerr << "\t\t---- using provided planes\n";
      reconstruct < Cartesian, SCIP_Solver > (input_file, false);

      std::cerr << "\t\t---- re-extract planes\n";
      reconstruct < Cartesian, SCIP_Solver > (input_file, true);
    }

    #if!defined(CGAL_USE_GLPK) && !defined(CGAL_USE_SCIP)
    std::cerr << "\n\t---- Using no solver (partial test)\n";

    std::cerr << "\t\t---- using provided planes\n";
    reconstruct < Cartesian, int > (input_file, false);

    std::cerr << "\t\t---- re-extract planes\n";
    reconstruct < Cartesian, int > (input_file, true);
    #endif
  } else if (kernelName == "Epick") {

    std::cerr << "\n--- Using Epick kernel";

    // if (solverName == "GLPK") {
    //     std::cerr << "\n\t---- Using GLPK solver\n";
    //
    //         std::cerr << "\t\t---- using provided planes\n";
    //         reconstruct<Epick, GLPK_Solver>(input_file, false);
    //
    //     std::cerr << "\t\t---- re-extract planes\n";
    //         reconstruct<Epick, GLPK_Solver>(input_file, true);
    // }

    if (solverName == "SCIP") {
      std::cerr << "\n\t---- Using SCIP solver\n";

      std::cerr << "\t\t---- using provided planes\n";
      reconstruct < Epick, SCIP_Solver > (input_file, false);

      std::cerr << "\t\t---- re-extract planes\n";
      reconstruct < Epick, SCIP_Solver > (input_file, true);
    }

    #if!defined(CGAL_USE_GLPK) && !defined(CGAL_USE_SCIP)
    std::cerr << "\n\t---- Using no solver (partial test)\n";

    std::cerr << "\t\t---- using provided planes\n";
    reconstruct < Epick, int > (input_file, false);

    std::cerr << "\t\t---- re-extract planes\n";
    reconstruct < Epick, int > (input_file, true);
    #endif
  }

  return EXIT_SUCCESS;
}