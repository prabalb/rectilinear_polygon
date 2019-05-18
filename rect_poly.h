/*
 * Rectilinear Polygon
 * Author: Prabal Basu
 * Contact: prabalb@aggiemail.usu.edu
 */

#include <iostream>

#include <vector>
#include <map>
#include <utility>

using namespace std;

#ifndef RECTILINEAR_H
#define RECTILINEAR_H

class Vertex {

  private:
    float coord_x;
    float coord_y;

  public:
    Vertex(float x, float y) : coord_x(x), coord_y(y) {}
    std::pair<float, float> getCoord() const { return std::make_pair(coord_x, coord_y); }
};

class Edge {

  private:
    Vertex end_1;
    Vertex end_2;

  public:
    Edge(const Vertex& m, const Vertex& n) : end_1(m), end_2(n) {}
    const std::pair<Vertex, Vertex> getEndPoints() const { return std::make_pair(end_1, end_2); }
};

typedef std::vector<Vertex> VERTEX_VEC;
typedef std::vector<Edge> EDGE_VEC;

class RectilinearPolygon {

  private:
    VERTEX_VEC m_vertices;
    EDGE_VEC m_edges;

    unsigned int m_num_horizontal_edges;
    unsigned int m_num_vertical_edges;

  public:
    RectilinearPolygon(VERTEX_VEC vertices);

    bool createPolygon();
    bool createEdges();
    bool createEdges(std::map<float, VERTEX_VEC>& group, bool sort_by_x_coord=true);
    bool isLegalPolygon();
    bool groupVertices(bool group_by_y_coord=true);

    void getEdges(EDGE_VEC& edges) const;

};

class Utils {

  private:
    Utils() {}
    void operator=(Utils&);
    Utils (const Utils&);

    std::vector<VERTEX_VEC> allVertices;
    std::vector<RectilinearPolygon*> allPolygons;

  public:
    static Utils& getUtils() {
      static Utils utils;
      return utils;
    }

    float calculateDistance(const RectilinearPolygon& rp1, const RectilinearPolygon& rp2);
    float getDistanceBetweenTwoEdges(const Edge& e1, const Edge& e2);

    bool parseInputFile(const std::string& inputFileName);
    bool createPolygons(const std::string& inputFileName);

    void getAllPolygons(std::vector<RectilinearPolygon*>& rp);
};

#endif // RECTILINEAR_H
