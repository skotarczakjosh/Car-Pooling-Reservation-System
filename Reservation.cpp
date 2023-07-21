//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Title: Reservation.cpp
// Course: Computational Problem Solving II (CPET - 321)
// Developer: Josh Skotarczak (CPET)
// Date: 11/20/2022
// Description: Source File For Reservation Class at Reservation.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Libraries
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <iostream>
#include <string>
// Include Header File
#include "Reservation.h"
// Namespace
using namespace std;

// Defualt Constructor
Reservation::Reservation() {
// Data Members
this-> name = "Empty";
this-> carType = "Empty";
this-> seatPosition = "Empty";
this-> resNum = 0;
this-> seatValue = 0;
this->PointsLocation = 0;
this->seatNum = 0;
}
// Default Constructor With Parameters
Reservation::Reservation(string name, string carType, int resNum, 
	string seatPosition, int seatValue, int PointsLocation, int seatNum) {
	// Data Members
	this->name = name;
	this->carType = carType;
	this->seatPosition = seatPosition;
	this->resNum = resNum;
	this->seatValue = seatValue;
	this->PointsLocation = PointsLocation;
	this->seatNum = seatNum;
}

// Accessor Functions
void Reservation::displayReservation() {
	cout << "Name : " << name << endl;
	cout << "Vehicle : " << carType << endl;
	cout << "Seat Position : " << seatPosition << endl;
	cout << "Reservation Number : " << resNum << endl;
}

// Returns Name
string Reservation::GetName() {
	return this->name;
}

// Retruns CarTppe, Color And Type *
string Reservation::GetCarType() {
	return this->carType;
}

// Returns Seat Position of The Where the Reservation Was Made
// Example : Front... Rigth Back ...
string Reservation::GetSeatPositon() {
	return this->seatPosition;
}

// Returns Reservation Number
int Reservation::GetReservationNumber() {
	return this->resNum;
}

// Returns Orginal Seat Value
int Reservation::GetSeatValue() {
	return this->seatValue;
}

// Returns Location Where the Points Are In The Array For Credit Updating
int Reservation::GetPointsLocation() {
	return this->PointsLocation;
}

// Retruns Interger Value Of The Seat Positon In Terms of
// Where In The Vehicle
int Reservation::GetSeatNum() {
	return this->seatNum;
}

