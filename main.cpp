/*
 * Rectilinear Polygon
 * Author: Prabal Basu
 * Contact: prabalb@aggiemail.usu.edu
 */

#include "rect_poly.h"
#include <fstream>

int main() {
  std::cout << "Enter the input file name: ";
  std::string inputFileName;
  std::cin >> inputFileName;
  Utils::getUtils().createPolygons(inputFileName);

  std::vector<RectilinearPolygon*> rp;
  Utils::getUtils().getAllPolygons(rp);
  
  std::cout << "The distance between the two polygons is: " << Utils::getUtils().calculateDistance(*rp[0], *rp[1]) << std::endl;
  return 0;
  
}
