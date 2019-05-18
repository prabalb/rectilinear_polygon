# rectilinear_polygon

- Implement a class to represent a rectilinear polygon. Add proper initializers, constructors, verifiers and necessary APIs.
- Implement a distance() function that computes distance between two polygons (distance of polygons is the shortest distance between polygons’ edges)

Assumptions:
1. The polygons are not overlapped.
2. The edges of the polygons are parallel to either X or Y axis.
3. The distance between two edges of two different polygons is non-zero only if the edges are parallel to each other.
4. A legal rectilinear polygon has even number of vertices, even number of edges and equal number of horizontal and vertical edges. Additional checks, for example, number of convex and concave corners, number of knobs and antiknobs etc. can be added. But these are special cases for simple rectilinear polygons.

Related links:
1. https://en.wikipedia.org/wiki/Rectilinear_polygon
2. https://stackoverflow.com/questions/17862162/sort-anticlockwise-the-points-of-rectilinear-polygon?lq=1

- Source files: rect_poly.h, rect_poly.cpp, main.cpp
- Makefile: makefile
- How to compile: make
- How to run: ./runProg (Then enter the input file name)

- Example input files: in.txt, input.txt
