/*
 * CAGraph_test.cpp
 *
 *  Created on: Aug 19, 2016
 *      Author: fpantale
 */

#include <algorithm>    // std::find

#include <iostream>
#include "CAGraph.h"

// store neighbors in a std::set, vertices in a std::vector

int print_vertices(const CAVertex& vertex)
{
	std::cout << vertex.theData << std::endl;
}

int print_edge(const CAEdge& edge)
{
	std::cout << "visiting edge " << edge.theVertices[0] << " "
			<< edge.theVertices[1] << std::endl;
}


int main()
{
	std::vector<std::array<std::string, 4> > quadruplets;
	quadruplets.reserve(7);

	quadruplets.emplace_back(std::array<std::string,4>{"BPix1", "BPix2",    "BPix3",    "BPix4"   });
	quadruplets.emplace_back(std::array<std::string,4>{"BPix1", "BPix2",    "BPix3",    "FPix1Pos"});
	quadruplets.emplace_back(std::array<std::string,4>{"BPix1", "BPix2",    "FPix1Pos", "FPix2Pos"});
	quadruplets.emplace_back(std::array<std::string,4>{"BPix1", "FPix1Pos", "FPix2Pos", "FPix3Pos"});
	quadruplets.emplace_back(std::array<std::string,4>{"BPix1", "BPix2",    "BPix3",    "FPix1Neg"});
	quadruplets.emplace_back(std::array<std::string,4>{"BPix1", "BPix2",    "FPix1Neg", "FPix2Neg"});
	quadruplets.emplace_back(std::array<std::string,4>{"BPix1", "FPix1Neg", "FPix2Neg", "FPix3Neg"});



	CAGraph g;

	for (std::size_t i = 0; i < quadruplets.size(); ++i)
	{

		for (std::size_t j = 0; j < quadruplets[i].size(); ++j)
		{

			bool isNewRootVertex = false;
			auto vertexIndex = 0;
			auto foundVertex = std::find(g.theVertices.begin(),
					g.theVertices.end(), quadruplets[i][j]);
			if (foundVertex == g.theVertices.end())
			{

				g.theVertices.emplace_back(quadruplets[i][j]);
				vertexIndex = g.theVertices.size()-1;
			}
			else
			{
				vertexIndex = foundVertex - g.theVertices.begin();
			}
			if (j == 0)
			{


					if (std::find(g.theRootVertices.begin(),
							g.theRootVertices.end(), vertexIndex) == g.theRootVertices.end())
						g.theRootVertices.emplace_back(
								vertexIndex);

			}
			else
			{

				auto innerVertex = std::find(g.theVertices.begin(),
						g.theVertices.end(), quadruplets[i][j - 1]);





				CAEdge tmpInnerEdge
				{ innerVertex - g.theVertices.begin(),vertexIndex};


				if (std::find(g.theEdges.begin(), g.theEdges.end(), tmpInnerEdge)
						== g.theEdges.end())
				{

					g.theEdges.push_back(tmpInnerEdge);
					g.theVertices[vertexIndex].theInnerVertices.push_back(
							innerVertex - g.theVertices.begin());
					innerVertex->theOuterVertices.push_back(
							vertexIndex);
					g.theVertices[vertexIndex].theInnerEdges.push_back(g.theEdges.size()-1);
					innerVertex->theOuterEdges.push_back(g.theEdges.size()-1);

				}

			}

		}

	}


	std::cout << "bfs vertex" << std::endl;
	g.bfs_vertex_visitor(print_vertices, 4);
	std::cout << "\nbfs edges" << std::endl;

	g.bfs_edges_visitor(print_edge,3);

}
