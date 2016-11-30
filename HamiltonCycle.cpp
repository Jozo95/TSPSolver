#include "HamiltonCycle.h"
#include <math.h>
#include <algorithm>
#include <time.h>
using namespace std;  

HamiltonCycle::HamiltonCycle() {
	
	if (readData())
		std::cout << "Data successfully read" << std::endl;
	else
		std::cout << "Can not proceed. Errors printed above." << std::endl;

//	cout << verticesFor128[2].getDistance(verticesFor128[4]);

	//startHillClimbing();
	
	startNearestNeighborWithTweak();
	calcShortestPathNNMethod(verticesFor16);
}

HamiltonCycle::Path::Path(){

}

HamiltonCycle::Path::Path(Path & path){
	for each (Vertex var in path.path){
		this->path.push_back(var);
	}
}

HamiltonCycle::Path::Path(std::vector<Vertex> path){
	for each (Vertex var in path) {
		this->path.push_back(var);
	}
	std::random_shuffle(this->path.begin(), this->path.end());
}

double HamiltonCycle::Path::getTotalDistance()
{
	double dist = 0.0;
	//cout << "PATH SIZE:" << endl;
	for (int i = 0; i < path.size()-2; i++) {
		dist += path[i].getDistance(path[i + 1]);
	}
	this->distance = dist;
	return dist;
}

void HamiltonCycle::startNearestNeighbor(){
	path = Path(verticesFor128);
	//path.getTotalDistance()
	Path q = calcShortestPathNNMethod(path);
	printVertex(q.path);
	cout << q.getTotalDistance() << endl;
}

void HamiltonCycle::startNearestNeighborWithTweak() {

	path = Path(verticesFor16);
	Path first = calcShortestPathNNMethod(verticesFor16);
	cout << first.getTotalDistance();
	stringstream ss;
	cout << " ---- shortest path: " << first.getTotalDistance() << endl;
	ss << "Path taken: " << endl;
	
	//cout << "SIZE FOR VERTICIES 128: " << verticesFor128.size() << ". Size for first: " << first.path.size() << ". size for adj path: " << (getAdjPath(first)).path.size() << endl;
	Path q;
	std::vector<Path> allPaths;
	time_t startTime, endTime;
	time(&startTime);
	for (int i = 0; i < MAX_RESTARTS; i++) {
		q = calcShortestPathNNMethod(getAdjPath(first));
		double qDist = q.getTotalDistance(), firstDist = first.getTotalDistance();
		if (qDist < firstDist)
			first = q;
	}
	time(&endTime);
	//std::sort(allPaths.begin(), allPaths.end(), igetTotalDistance());

	int counter = 0;
	for each (Vertex var in first.path) {
		ss << " -> " << var.getName();
		if (counter == 6) {
			ss << endl;
			counter = 0;
		}
		else
			counter++;
	}
	cout << ss.str() << endl;
	//path.getTotalDistance()
	double seconds = difftime(endTime, startTime);
	//printVertex(first.path);
	cout << first.getTotalDistance() << endl;
	cout << "Total size: " << first.path.size() <<endl;
	cout << "Total time; in seconds" << seconds << endl;


}


HamiltonCycle::Path HamiltonCycle::calcShortestPathNNMethod(Path path) {
	Path newPath = Path();
	int upperX, lowerX, upperY, lowerY, totalSize = path.path.size();
	int x=0, y=0;
	Vertex closestNeighbor;
	Vertex getMyVals;
	//Path copyOfPath = Path(path);
	Vertex *copyOfPath = new Vertex[totalSize];
	int countFor = 0;
	for each (Vertex var in path.path){
		copyOfPath[countFor++] = var;
	}
	//newPath.path.push_back(copyOfPath.path[0]);

	//totalSize = countFor;
	//copyOfPath.path.erase(copyOfPath.path.begin());
	//bool foundOne = false;
	//for (int i = 1; i < totalSize; i++) {
	//	cout << "i val: " << i << endl;
	//	getMyVals = newPath.getPath().back();
	//	lowerX = getMyVals.getX() - 10;
	//	upperX = getMyVals.getX() + 10;
	//	lowerY = getMyVals.getY() - 10;
	//	upperY = getMyVals.getY() + 10;
	//	int removeThisElement;
	//	for (int q = 0; q < copyOfPath.path.size(); q++) {
	//		x = copyOfPath.path[q].getX();
	//		y = copyOfPath.path[q].getY();
	//		if (x >= lowerX && x <= upperX && y >= lowerY && y <= upperY) {
	//			if (foundOne) {
	//				if (getMyVals.getDistance(closestNeighbor) > getMyVals.getDistance(copyOfPath.path[q])) {
	//					closestNeighbor = copyOfPath.path[q];
	//					foundOne = true;
	//					removeThisElement = q;
	//				}
	//			}
	//			else {
	//				closestNeighbor = copyOfPath.path[q];
	//				foundOne = true;
	//				removeThisElement = q;
	//			}
	//		}
	//		if (copyOfPath.path.size() == 1) {
	//			closestNeighbor = copyOfPath.path[q];
	//			removeThisElement = 0;
	//			break;
	//		}
	//		if (q == copyOfPath.path.size() - 1 && foundOne == false) {
	//			q = 0;
	//			lowerX -= lowerX;
	//			upperY += upperY;
	//			upperX += upperX;
	//			lowerY -= lowerY;
	//		}
	//		
	//	}
	//	if (!(closestNeighbor == getMyVals))
	//		newPath.path.push_back(closestNeighbor);
	//	copyOfPath.path.erase(copyOfPath.path.begin() + removeThisElement);
	//	//cout << "CURRENT PATH: " << endl;
	//	//printVertex(newPath.path);
	//	foundOne = false;

	//}

	newPath.path.push_back(copyOfPath[0]);
	copyOfPath[0] = copyOfPath[--countFor];
	//countFor--;
	//copyOfPath.path.erase(copyOfPath.path.begin());
	bool foundOne = false;
	for (int i = 1; i < totalSize; i++) {
		//cout << "i val: " << i << endl;
		getMyVals = newPath.getPath().back();
		lowerX = getMyVals.getX() - 100;
		upperX = getMyVals.getX() + 100;
		lowerY = getMyVals.getY() - 100;
		upperY = getMyVals.getY() + 100;
		int removeThisElement;
		for (int q = 0; q < countFor; q++) {
			x = copyOfPath[q].getX();
			y = copyOfPath[q].getY();
			if (x >= lowerX && x <= upperX && y >= lowerY && y <= upperY) {
				if (foundOne) {
					if (getMyVals.getDistance(closestNeighbor) > getMyVals.getDistance(copyOfPath[q])) {
						closestNeighbor = copyOfPath[q];
						foundOne = true;
						removeThisElement = q;
					}
				}
				else {
					closestNeighbor = copyOfPath[q];
					foundOne = true;
					removeThisElement = q;
				}
			}
			if (countFor == 1) {
				closestNeighbor = copyOfPath[q];
				removeThisElement = 0;
				break;
			}
			if (q == countFor - 1 && foundOne == false) {
				q = 0;
				lowerX -= lowerX;
				upperY += upperY;
				upperX += upperX;
				lowerY -= lowerY;
			}

		}
		if (!(closestNeighbor == getMyVals))
			newPath.path.push_back(closestNeighbor);
		copyOfPath[removeThisElement] = copyOfPath[--countFor];

		//cout << "CURRENT PATH: " << endl;
		//printVertex(newPath.path);
		foundOne = false;

	}
	newPath.path.push_back(newPath.path.at(0));

	//cout << "FINISHED";

	return newPath;
}


void HamiltonCycle::startHillClimbing(){

	time_t startTime, endTime;
	


	path = Path(verticesFor128);
	printVertex(path.path);
	cout << path.getTotalDistance();
	time(&startTime);
	std::vector<HamiltonCycle::Path> q = getShortestPaths(path);

	Path f;
	
	for (int i = 0; i < q.size(); i++) {
		if (i == 0)
			f = (q[0]);
		else {
			if (f.getTotalDistance() > q.at(i).getTotalDistance()) {
				f = q[i];
				//EXPERIMENT
				//int before = f.getTotalDistance();
				//f = calcShortestPathNNMethod(f.path);
				//cout << "Before dist: " << before << ".  After: " << f.getTotalDistance() << endl;
			}
		}
	}
	time(&endTime);
	double seconds = difftime(endTime, startTime);
	cout << "---------- SHORTEST PATH NOW --------" << endl;
	cout << f.getTotalDistance() << endl;
	cout << "Time take; " << seconds << endl;
	//printVertex(f.path);



}

bool HamiltonCycle::calcShortestRoute()
{
	for (int i = 0; i < MAX_RESTARTS; i++) {

	}



	return false;
}

HamiltonCycle::Path HamiltonCycle::findShortestPath(Path &currPath)
{
	Path adjRoute;
	int counter = 0;
	std::string cmprRoutes;
	stringstream ss;

	while (counter < MAX_ITERATIONS) {
		adjRoute = Path(getAdjPath(currPath));
		//adjRoute = calcShortestPathNNMethod(adjRoute);
		if (adjRoute.getTotalDistance() < currPath.getTotalDistance()) {
			
			ss << "<= found, procceding. Old distance: " << currPath.getTotalDistance() << ". New Dist:" << adjRoute.getTotalDistance() << endl;

			counter = 0;
			currPath = Path(adjRoute);
		}
		else
			counter++;
			//ss << "> found, staying - counter: " <<counter++ << endl;
		
		cout << ss.str();
		ss.str("");
	}
	cout << " ---- shortest path: " << currPath.getTotalDistance() << endl;
	ss << "Path taken: ";
	//for each (Vertex var in currPath.path){
	//	ss << " -> " << var.getName();
	//}
	//cout << ss.str() << endl;
	return currPath;
}

HamiltonCycle::Path HamiltonCycle::getAdjPath(Path &path)
{
	std::vector<Vertex> vertPtr = (path.path);
	srand(time(NULL));
	int x1 = 0, x2 = 0;
	while (x1 == x2) {
		x1 = (int)(rand() % vertPtr.size());
		x2 = (int)(rand() % vertPtr.size());
	}
	//std::iter_swap(path.getPath().begin() + x1, path.getPath().begin() + x2);
	Vertex v1 = vertPtr.at(x1);
	Vertex v2 = vertPtr.at(x2);
	vertPtr.erase(vertPtr.begin() + x1);
	vertPtr.insert(vertPtr.begin() + x1, v2);
	vertPtr.erase(vertPtr.begin() + x2);
	vertPtr.insert(vertPtr.begin() + x2, v1);

	//EXPERIMENT
	//Path q = calcShortestPathNNMethod(vertPtr);

	return vertPtr;
}

void HamiltonCycle::printVertex(std::vector<Vertex> verticies) {
	for (int i = 0; i < verticies.size(); i++) {
		std::cout << verticies[i] << std::endl;
	}
}

std::vector<HamiltonCycle::Path> HamiltonCycle::getShortestPaths(Path path)
{
	std::vector<Path> allPaths;
	for (int i = 0; i < MAX_RESTARTS; i++) {
		allPaths.push_back(findShortestPath(path));
	}
	//std::sort(allPaths.begin(), allPaths.end(), igetTotalDistance());
	return allPaths;
}


bool HamiltonCycle::readData() {

	std::cout << "IN ON READ DATA " << std::endl;
	std::ifstream dataFile;
	dataFile.open("data128.txt", std::ios::in);
	if (!dataFile.is_open()) {
		std::cout << "dataFile wasnt loaded with data128, lets try to open data16k instead." << std::endl;
		dataFile.open("data16k.txt");
		if (!dataFile.is_open())
			std::cout << "data16k wasnt found either, quitting." << std::endl;
		return false;
	}
	else {
		int x, y,c=0;
		while (!dataFile.eof() && c != 128) {
			dataFile >> x;
			dataFile >> y;
			verticesFor128.push_back(Vertex(x, y));
			c++;
		}
		//printVertex();
		std::cout << "Counter: " << c << std::endl;
	}
	dataFile.close();
	dataFile.open("data16k.txt", std::ios::in);
	if (dataFile.is_open()) {
		int x, y, c = 0;
		while (!dataFile.eof()) {
			dataFile >> x;
			dataFile >> y;
			verticesFor16.push_back(Vertex(x, y));
			c++;
		}
		//printVertex();
		std::cout << "Counter: " << c << std::endl;
	}
	return true;
}

ostream& operator<<(std::ostream& os,  const HamiltonCycle::Vertex& dt) {
	std::stringstream ss;
	os << "Name:" << dt.name << ". X:" << dt.x << ". Y:" << dt.y;
	return os;
}

bool operator==(const HamiltonCycle::Vertex & dp, const HamiltonCycle::Vertex & dt)
{
	if (dp.name == dt.name)
		return true;
	return false;
}


std::string HamiltonCycle::Vertex::newName(){
	std::stringstream q;
	q << "_city" << nameCounter++;
	return q.str();
}

int HamiltonCycle::Vertex::getX()
{
	return x;
}

int HamiltonCycle::Vertex::getY()
{
	return y;
}

std::string HamiltonCycle::Vertex::getName()
{
	return this->name;
}

double HamiltonCycle::Vertex::getDistance(Vertex vertex)
{
	double xSteps, ySteps, dist;
	xSteps = vertex.getX() - getX();
	ySteps = vertex.getY() - getY();
	//if (xSteps < 0)
	//	xSteps *= -1;
	//if (ySteps < 0)
	//	ySteps *= -1;
	xSteps = pow(xSteps, 2);
	ySteps = pow(ySteps, 2);
	dist = sqrt(xSteps + ySteps);
	return dist;

}
