//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Title: Vehicle.h
// Course: Computational Problem Solving II (CPET - 321)
// Developer: Josh Skotarczak (CPET)
// Date: 11/20/2022
// Description: Header File For Vehicle Class
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Include Guards
#ifndef VEHICLE_Header
#define VEHICLE_Header
// Libraries
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <array>
#include <iostream>
#include <string>
// Namespace
using namespace std;
// Class Vechile 
class Vehicle 
{
private:
	// Data Members
	string vehicleType;
	string vehicleColor;
	array<string,4> Seats;
	string driverName;
	string Seat1Name;
	string Seat2Name;
	string Seat3Name;
	string Seat4Name;
	int numSeats;
	int openSeats;
public:
	// Defualt Constructor
	Vehicle();
	// Default Constructor With Parameters
	Vehicle(string driverName, string vehicleColor,  int numSeats);
	// Mutator Functions
	void ReserveSeat(string name, int seatNum);
	void DeleteReservedSeat(int seatNum);
	// Accessor Functions
	void displaySeatLayout();
	void displayFullLayout(Vehicle, Vehicle, Vehicle, Vehicle, Vehicle, 
		Vehicle, Vehicle, Vehicle, Vehicle);
	void displayLegend();
	void displayPassNames();
	void adminCout();
	int GetOpenNumberSeats();
	int GetSeatValueFromString(string);
	int GetSeatPosValFromString(string);
	bool GetSeatStatus(string);
	string GetVehicleType();
	string GetVehicleColor();
	string GetSeat(int);
	string availableSeatOptions();
	string adminPrint();
	string PassengerPrint();
};
// Include Guards
#endif