//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Title: Reservation.h
// Course: Computational Problem Solving II (CPET - 321)
// Developer: Josh Skotarczak (CPET)
// Date: 11/20/2022
// Description: Header File For Reservation Class
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Include Guards
#ifndef RESERVATION_Header
#define RESERVATION_Header
// Libraries
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "Vehicle.h"

class Reservation 
{
private:
	// Data Members
	string name;
	string carType;
	string seatPosition;
	int resNum;
	int seatValue;
	int PointsLocation;
	int seatNum;
public:
	// Defualt Constructor 
	Reservation();
	// Default Constructor With Parameters
	Reservation(string name, string carType, int resNum, string seatPosition, 
		int seatValue, int PointsLocation, int seatNum);
	// Accessor Function
	void displayReservation();
	string GetName();
	string GetCarType();
	string GetSeatPositon();
	int GetReservationNumber();
	int GetSeatValue();
	int GetPointsLocation();
	int GetSeatNum();
};

#endif
// Include Guards