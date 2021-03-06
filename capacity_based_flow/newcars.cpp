#include "newcars.h"

using namespace std;

int selectEnteringRoad(map<int, Road>& Roads, int enterNode) {
	int roadID;
	map<int, Road> roads = Roads;
	for(map<int, Road>::iterator it = roads.begin() ; it != roads.end() ; it++) {
		if(it->second.nodeA() == enterNode) {
			roadID = it->first;
			break;
		}
	}
	return roadID;
}

void addNewCars(vector<Car>& newCars, map<int, Road>& Roads, int t, int timestep) {
	for(vector<Car>::iterator it = newCars.begin() ; it != newCars.end() ;) {
		if(it->enteringTime() < t)
			newCars.erase(it);
		else if(it->enteringTime() >= t + timestep)
			it++;
		else {
			int roadID = selectEnteringRoad(Roads, it->enteringNode());
			Roads[roadID].addCarToTA((*it));
			newCars.erase(it);
		}
		if(newCars.size() == 0)
			break;
	}
}