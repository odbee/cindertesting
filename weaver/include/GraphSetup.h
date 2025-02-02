#pragma once

#include "cinder/app/App.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/connected_components.hpp>


struct EdgeProperties
{
	int uniqueIndex;
	float restlength;
	float currentlength;
	int index;
	bool isforbidden;
};

struct EdgeContainer
{
	int uniqueIndex;
	int index;
	float restlength;
	int isForbidden;
	int sourceV;
	int targetV;
	bool isVisbile= false;
	
};

struct RecipeContainer {
	int OldEdgeA, OldEdgeB;
	int NewEdgeA1, NewEdgeA2, NewEdgeB1, NewEdgeB2;
	int NewEdgeC;
	float posA1, posA2;
};
struct VertexContainer {
	int index;
	bool isfixed;
	ci::vec3 pos;
};


struct VertexProperties
{
	std::size_t index;
	bool isfixed;
	ci::vec3 pos;
	ci::vec3 movevec;
	bool isActive = false;
};


struct VertexProperties2 {
	int uniqueIndex;
	std::vector < float > DivEdgeLengths;
	std::vector < int> daughterEdges;
	std::vector < float > interPts;

};


typedef boost::adjacency_list<boost::vecS,
	boost::vecS, boost::undirectedS, VertexProperties, EdgeProperties> Graph;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperties2> EdgesGraph;

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

typedef boost::graph_traits<Graph>::vertex_iterator vertex_ti;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;
typedef boost::graph_traits<Graph>::edge_iterator edge_ti;
typedef std::map<std::array<signed int, 3>, float> voxel_map;
typedef std::vector<ci::vec3> anchor_points;



typedef boost::graph_traits<EdgesGraph>::vertex_iterator evertex_ti;


template <typename T>
std::string stringfromVec(std::vector<T> vec) {
	std::string result = "[ ";
	for (auto it = vec.begin(); it != vec.end(); it++) {
		result.append(std::to_string(*it));
		result.append(" ");
	}
	result.append(" ]");
	return result;
}