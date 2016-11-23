#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class HamiltonCycle {
	 const int MAX_ITERATIONS = 500;
	 const int MAX_RESTARTS = 50;
private:
	double totalDistance;
public:
	class Vertex{
		static int nameCounter;
		int x, y;
		std::string name;
		std::string newName();
	public:
		int getX();
		int getY();
		std::string getName();
		double getDistance(Vertex vertex);
		Vertex(int x = 0, int y = 0) { this->name = newName(); this->x = x; this->y = y; } 
		friend std::ostream& operator<<(std::ostream& os, const Vertex& dt);

		friend bool operator==(const Vertex& dp, const Vertex& dt);
	};
	class Path {
	public:
		double distance;
		Path();
		Path(Path &path);
		Path(std::vector<Vertex> path);
		std::vector<Vertex> path;
		std::vector<Vertex> getPath() { return path; };
		double getTotalDistance();
	};
	std::vector<Vertex> verticesFor128;
	std::vector<Vertex> verticesFor16;


	Path path;


public:
	HamiltonCycle();



	bool readData();

	

	//Nearest neighbor
	void startNearestNeighbor();
	void startNearestNeighborWithTweak();
	HamiltonCycle::Path calcShortestPathNNMethod(Path path);

	
	// HILL CLIMBING
	void startHillClimbing();
	bool calcShortestRoute();
	Path findShortestPath(Path &currPath);
	Path getAdjPath(Path &path);
	void printVertex(std::vector<Vertex> verticies);
	std::vector<Path> getShortestPaths(Path path);

};