/*
 * CAGraph.h
 *
 *  Created on: Aug 19, 2016
 *      Author: fpantale
 */

#ifndef CAGRAPH_H_
#define CAGRAPH_H_

#include <vector>
#include <array>
#include <string>
#include <queue>
#include <functional>

class CAVertex
{
public:
	CAVertex(const std::string& a)
	{
		theData = a;
	}

	bool operator==(const std::string& otherString)
	{
		return otherString == theData;
	}

	std::vector<int> theOuterEdges;
	std::vector<int> theInnerEdges;

	std::vector<int> theOuterVertices;
	std::vector<int> theInnerVertices;

	std::string theData;
};

class CAEdge
{
public:
	CAEdge(long int a, long b)
	{
		theVertices[0] = a;
		theVertices[1] = b;
	}

	bool operator==(const CAEdge& otherEdge)
	{
		return (theVertices[0] == otherEdge.theVertices[0])
				&& (theVertices[1] == otherEdge.theVertices[1]);
	}
	std::array<int, 2> theVertices;
};

class CAGraph
{
public:
	CAGraph()
	{

	}

	void print_vertices() const
	{
		std::cout << "the graph contains the following vertices: "
				<< theVertices.size() << std::endl;
		for (auto const& vert : theVertices)
		{
			std::cout << vert.theData << std::endl;

			for (int innerEdge : vert.theInnerEdges)
			{
				std::cout << "\tinner edge "
						<< theVertices[theEdges[innerEdge].theVertices[0]].theData
						<< " "
						<< theVertices[theEdges[innerEdge].theVertices[1]].theData
						<< std::endl;
			}

			for (int outerEdge : vert.theOuterEdges)
			{
				std::cout << "\touter edge "
						<< theVertices[theEdges[outerEdge].theVertices[0]].theData
						<< " "
						<< theVertices[theEdges[outerEdge].theVertices[1]].theData
						<< std::endl;
			}
		}
	}
	void print_edges()
	{
		std::cout << "the graph contains the following edges : "
				<< theEdges.size() << std::endl;

		for (auto const & edge : theEdges)
			std::cout << theVertices[edge.theVertices[0]].theData << " -> "
					<< theVertices[edge.theVertices[1]].theData << std::endl;

	}

	void bfs_vertex_visitor(std::function<int(CAVertex&)> foo, int maxDepth = 4)
	{

		std::vector<bool> alreadyVisitedVertices;
		alreadyVisitedVertices.resize(theVertices.size());

		for (int rootVertex : theRootVertices)
		{
			std::queue<int> verticesToVisit;
			verticesToVisit.push(rootVertex);
			int depth = 1;
			unsigned int numberOfVerticesToVisitAtThisDepth = 1;
			for (auto visited : alreadyVisitedVertices)
			{
				visited = false;
			}
			while (!verticesToVisit.empty() && depth <= maxDepth)
			{
				std::cout << depth << " depth" << std::endl;

				auto currentVertex = verticesToVisit.front();

				foo(theVertices[currentVertex]);
				for (auto neighbor : theVertices[currentVertex].theOuterVertices)
				{
					if (alreadyVisitedVertices[neighbor] == false)
						verticesToVisit.push(neighbor);
				}
				verticesToVisit.pop();
				numberOfVerticesToVisitAtThisDepth--;
				alreadyVisitedVertices[currentVertex] = true;

				if (numberOfVerticesToVisitAtThisDepth == 0)
				{
					depth++;
					numberOfVerticesToVisitAtThisDepth = verticesToVisit.size();
				}

			}

		}

	}

	void bfs_edges_visitor(std::function<int(CAEdge&)> foo, int maxDepth = 3)
	{

		std::vector<bool> alreadyVisitedEdges;
		alreadyVisitedEdges.resize(theEdges.size());

		for (int rootVertex : theRootVertices)
		{
			for (auto visited : alreadyVisitedEdges)
			{
				visited = false;
			}
			std::queue<int> edgesToVisit;

			for (int edge : theVertices[rootVertex].theOuterEdges)
			{
				edgesToVisit.push(edge);
			}
			int depth = 1;
			unsigned int numberOfEdgesToVisitAtThisDepth = edgesToVisit.size();

			while (!edgesToVisit.empty() && depth <= maxDepth)
			{

				auto currentEdge = edgesToVisit.front();
				if (alreadyVisitedEdges[currentEdge] == false)
				{
					std::cout << depth << " depth" << std::endl;

					foo(theEdges[currentEdge]);
					for (auto outerEdge : theVertices[theEdges[currentEdge].theVertices[1]].theOuterEdges)
					{
						edgesToVisit.push(outerEdge);
					}

					alreadyVisitedEdges[currentEdge] = true;
				}
				edgesToVisit.pop();
				numberOfEdgesToVisitAtThisDepth--;
				if (numberOfEdgesToVisitAtThisDepth == 0)
				{
					depth++;
					numberOfEdgesToVisitAtThisDepth = edgesToVisit.size();
				}

			}

		}

	}
	std::vector<CAVertex> theVertices;
	std::vector<CAEdge> theEdges;
	std::vector<int> theRootVertices;

};

#endif /* CAGRAPH_H_ */
