/*
 * Rectilinear Polygon
 * Author: Prabal Basu
 * Contact: prabalb@aggiemail.usu.edu
 */

#include "rect_poly.h"

#include <fstream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <stdlib.h>

RectilinearPolygon::RectilinearPolygon(VERTEX_VEC vertices) :
  m_num_horizontal_edges(0), m_num_vertical_edges(0) {
  // Number of vertices should be even
  assert(vertices.size() > 0 && vertices.size() % 2 == 0);
  m_vertices = vertices;

  // Group the vertices, form the edges etc.
  assert(createPolygon());
}

bool RectilinearPolygon::createPolygon() {
  if(!createEdges()) {
    return false;
  }
  if(!isLegalPolygon()) {
    return false;
  }
  return true;
}

bool RectilinearPolygon::isLegalPolygon() {
  if(!(m_vertices.size() > 0 && m_vertices.size() % 2 == 0)) return false;
  if(!(m_edges.size() > 0 && m_edges.size() % 2 == 0)) return false;
  if(m_num_horizontal_edges != m_num_vertical_edges) return false;
  return true;
}

bool RectilinearPolygon::createEdges() {
  return groupVertices() && groupVertices(false);
}

bool RectilinearPolygon::groupVertices(bool group_by_y_coord) {
  std::map<float, VERTEX_VEC> group;
  for(size_t i = 0; i < m_vertices.size(); i++) {
    Vertex vertex = m_vertices[i];
    float coord = group_by_y_coord ? vertex.getCoord().second : vertex.getCoord().first;
    group[coord].push_back(vertex);
  }

  // calculate number of horizontal/vertical edges
  for(std::map<float, VERTEX_VEC>::const_iterator iter = group.begin();
      iter != group.end();
      iter++) {
    int num_vertices = (iter->second).size();
    if(group_by_y_coord) {
      m_num_horizontal_edges += num_vertices/2;
    } else {
      m_num_vertical_edges += num_vertices/2;
    }
  }

  return createEdges(group, group_by_y_coord);
}

struct compare_rule_1 {
  bool operator() (Vertex lhs, Vertex rhs) {
    return lhs.getCoord().first < rhs.getCoord().first;
  }
} obj_1;

struct compare_rule_2 {
  bool operator() (Vertex lhs, Vertex rhs) {
    return lhs.getCoord().second < rhs.getCoord().second;
  }
} obj_2;


bool RectilinearPolygon::createEdges(std::map<float, VERTEX_VEC>& group, bool sort_by_x_coord) {
  std::map<float, VERTEX_VEC>::const_iterator iIter = group.begin();
  std::map<float, VERTEX_VEC>::const_iterator endIter = group.end();
  for(; iIter != endIter; iIter++) {
    VERTEX_VEC vvec = iIter->second;
    if(vvec.size() % 2 != 0) {
      std::cout << "Group size for a given X/Y coordinate is not even ..." << std::endl;
      return false;
    }
    if(sort_by_x_coord) {
      std::sort(vvec.begin(), vvec.end(), obj_1);
    } else {
      std::sort(vvec.begin(), vvec.end(), obj_2);
    }
    for(size_t i = 0; i < vvec.size(); i = i + 2) {
      const Vertex& v1 = vvec[i];
      const Vertex& v2 = vvec[i+1];
      m_edges.push_back(Edge(v1, v2));
    }
  }
  return true;
}

bool Utils::parseInputFile(const std::string& inputFileName) {
  std::ifstream inputFile(inputFileName.c_str());

  if(!inputFile.is_open()) {
    std::cerr << "Could not open the input file specified, please try again ..." << std::endl;
    return false;
  }

  int numPolygon = 0;
  bool processedPolygon = false;
  VERTEX_VEC vvec;
  while (!inputFile.eof()) {
    char buf[100];
    inputFile.getline(buf, 100);

    const char* token[8] = {};
    token[0] = strtok(buf, " ");
    if(!token[0]) continue;
    std::string tokStr(token[0]);

    if(tokStr.find(",") == string::npos) {
      assert(tokStr.size() == 1);
      std::stringstream(tokStr) >> numPolygon;
    } else {
      assert(numPolygon > 0);
      const char* tok[8] = {};
      tok[0] = strtok(buf, ",");
      assert(tok[0]);
      std::stringstream x_ss;
      x_ss << tok[0];
      float x_coord;
      x_ss >> x_coord;
      tok[1] = strtok(0, ",");
      assert(tok[1]);
      std::string str(tok[1]);
      float y_coord;
      if(str.find(".") != str.npos) {
        str = str.substr(0, str.size() - 1);
        processedPolygon = true;
        numPolygon--;
      } 
      std::stringstream(str) >> y_coord;
      vvec.push_back(Vertex(x_coord, y_coord));
      if(processedPolygon) {
        assert(vvec.size() > 0);
        allVertices.push_back(vvec);
        vvec.clear();
        processedPolygon = false;
      }
    }
  }
  inputFile.close();
  return true;
}


bool Utils::createPolygons(const std::string& inputFileName) {
  if(!parseInputFile(inputFileName)) {
    return false;
  }
  if(allVertices.size() == 0) {
    std::cout << "Could not collect any vertex ..." << std::endl;
    return false;
  }
  
  for(size_t i = 0; i < allVertices.size(); i++) {
    VERTEX_VEC vvec = allVertices[i];
    assert(vvec.size() > 0);
    RectilinearPolygon *rp = new RectilinearPolygon(vvec);
    allPolygons.push_back(rp);
  }
  assert(allPolygons.size() > 0);
  return true;
}

void RectilinearPolygon::getEdges(EDGE_VEC& edges) const {
  edges = m_edges;
}

float Utils::calculateDistance(const RectilinearPolygon& rp1, const RectilinearPolygon& rp2) {
  EDGE_VEC edges1, edges2;
  rp1.getEdges(edges1);
  rp2.getEdges(edges2);

  float minimum_distance = 100000000.0;
  for(size_t i = 0; i < edges1.size(); i++) {
    const Edge edge_1 = edges1[i];
    for(size_t j = 0; j < edges2.size(); j++) {
      const Edge edge_2 = edges2[j];
      float distance = getDistanceBetweenTwoEdges(edge_1, edge_2);
      if(distance < minimum_distance) {
        minimum_distance = distance;
      }
    }
  }
  return minimum_distance;
}

float Utils::getDistanceBetweenTwoEdges(const Edge& e1, const Edge& e2) {
  float e1_end1_x = e1.getEndPoints().first.getCoord().first;
  float e1_end1_y = e1.getEndPoints().first.getCoord().second;
  float e1_end2_x = e1.getEndPoints().second.getCoord().first;
  float e1_end2_y = e1.getEndPoints().second.getCoord().second;

  float e2_end1_x = e2.getEndPoints().first.getCoord().first;
  float e2_end1_y = e2.getEndPoints().first.getCoord().second;
  float e2_end2_x = e2.getEndPoints().second.getCoord().first;
  float e2_end2_y = e2.getEndPoints().second.getCoord().second;

  if(e1_end1_x == e1_end2_x && e2_end1_x == e2_end2_x) {
    if(e1_end1_x != e2_end1_x) {
      return std::abs(e1_end1_x - e2_end1_x);
    }
  }
  if(e1_end1_y == e1_end2_y && e2_end1_y == e2_end2_y) {
    if(e1_end1_y != e2_end1_y) {
      return std::abs(e1_end1_y - e2_end1_y);
    }
  }
  return 100000000.0;
}

void Utils::getAllPolygons(std::vector<RectilinearPolygon*>& rp) {
  rp = allPolygons;
}
