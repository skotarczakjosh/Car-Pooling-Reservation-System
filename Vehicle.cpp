//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Title: Vehicle.cpp
// Course: Computational Problem Solving II (CPET - 321)
// Developer: Josh Skotarczak (CPET)
// Date: 11/20/2022
// Description: Source File For Vehcile Class at Vehcile.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Libraries
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <array>
#include <iostream>
#include <string>
#include <time.h>
// Include Header File
#include "Vehicle.h"

// Defualt Constructor
Vehicle::Vehicle() {
	// Data Members
	vehicleType = "Unassigned";
	vehicleColor = "Unassigned";
	array<string, 4> Seats;
	driverName = "Unassigned";
	Seat1Name = "Unassigned";
	Seat2Name = "Unassigned";
	Seat3Name = "Unassigned";
	Seat4Name = "Unassigned";
	numSeats = 0;
	openSeats = 0;
}
// Default Constructor With Parameters
Vehicle::Vehicle(string driverName, string vehicleColor, int numSeats) {
	// Assign Driver Name
	this->driverName = driverName;
	// Assign How Many Seats There Are
	this->numSeats = numSeats;
	// Assign Vechicle Color
	this->vehicleColor = vehicleColor;
	// Assign Vechile
	// PickUp
	if (numSeats == 1) {
		Seats.at(0) = "5"; // Front Passenger Seat
		vehicleType = "Pickup";
		openSeats = numSeats;
	}
	// Compact
	else if (numSeats == 3) {
		Seats.at(0) = "5"; // Front Passenger Seat
		Seats.at(1) = "3"; // Right Back Window Seat
		Seats.at(2) = "3"; // Left Back Window Seat
		vehicleType = "Compact";
		openSeats = numSeats;
	}
	// Sedan
	else if (numSeats == 4) {
		Seats.at(0) = "5"; // Front Passenger Seat
		Seats.at(1) = "2"; // Right Back Window Seat
		Seats.at(2) = "1"; // Middle Seat
		Seats.at(3) = "2"; // Left Back Window Seart
		vehicleType = "Sedan";
		openSeats = numSeats;
	}
	// Default ALl Seat Names To Unassigned
	Seat1Name = "Unassigned";
	Seat2Name = "Unassigned";
	Seat3Name = "Unassigned";
	Seat4Name = "Unassigned";
}
// Mutator Functions
void Vehicle::ReserveSeat(string name, int seatNum) {
	if (openSeats != 0) {
		// Decrease Number 
		openSeats--;
		// Reserve Seat
		this->Seats.at(seatNum - 1) = "X"; // Fill Spot With X 
		// Update Seat Names
		// Pickup or Compact
		if (numSeats == 1 || numSeats == 3) {
			if (seatNum == 1) {
				Seat1Name = name;    // Assign Name
			}
			else if (seatNum == 2) { 
				Seat2Name = name;    // Assign Name
			}
			else if (seatNum == 3) {
				Seat3Name = name;    // Assign Name
			}
		}
		// Sedan
		else if (numSeats == 4) {
			if (seatNum == 1) {
				Seat1Name = name;     // Assign Name
			}
			else if (seatNum == 2) {
				Seat2Name = name;     // Assign Name
			}
			else if (seatNum == 3) {
				Seat3Name = name;    // Assign Name
			}
			else if (seatNum == 4) {
				Seat4Name = name;   // Assign Name
			} 
		}
	}
	else {
		cout << "No More Open Seats, Please Try Again";
	}
}
// Function to Delete Reservation In Seat Layout Dispaly
void Vehicle::DeleteReservedSeat(int seatNum) {
	// Increase Number Of Open Seats
	openSeats++;
	// Create Temp String To Hold Return Value
	string temp;
	// Find What Value It Needs to Replace With
	    // PickUp , Compact And Sedan
		if (seatNum == 1) {
			temp = "5"; // Front
		}
		if (numSeats == 3) {
			if (seatNum == 2 || seatNum == 3) {
				temp = "3"; // Back Window
			}
		}
		if (numSeats == 4){
		    if (seatNum == 2 || seatNum == 4) {
				temp = "2"; // Back Window
			}
			else if (seatNum == 3) {
				temp = "1"; // Back Middle
			}
		}
	// Un-Reserve Seat In Display
	Seats[seatNum - 1] = temp;
	// Revert Seat#Name To Unassigned
	if (seatNum == 1) {
		Seat1Name = "Unassigned";
	}
	else if (seatNum == 2) {
		Seat2Name = "Unassigned";
	}
	else if (seatNum == 3) {
		Seat3Name = "Unassigned";
	}
	else if (seatNum == 4) {
		Seat4Name = "Unassigned";
	}

}
// Accessor Functions
void Vehicle::displaySeatLayout() {
	cout << "          " << vehicleColor << " " << vehicleType << endl;
	cout << "         -------------" << endl;
	if (numSeats == 1) {
		cout << "            (-)" << "(" << Seats[0] << ")" << endl;
		cout << "            |____|" << endl;
	}
	else if (numSeats == 3) {
		cout << "            (-)" << " (" << Seats[0] << ")" << endl;
		cout << "            (" << Seats[2] << ") " << "(" << Seats[1] << ") ";
		cout << endl;
	}
	else if (numSeats == 4) {
		cout << "          (-)" << "   (" << Seats[0] << ")" << endl;
		cout << "          (" << Seats[3] << ")" << "(" << Seats[2] << ")(";
		cout << Seats[1] << ") " << endl;
	}

}

// Function To Dispaly All Vehicles In A Layout
void Vehicle::displayFullLayout(Vehicle PurplePickUp, Vehicle GreenPickUp, 
	Vehicle BlackPickUp,Vehicle RedCompact, Vehicle BlueCompact, 
	Vehicle YellowCompact, Vehicle BlueSedan,Vehicle BlackSedan, 
	Vehicle GreenSedan) {
	cout << "    Truck   Compact     Sedan  " << endl;
	cout << "   -------  -------    -------- " << endl;
	cout << "   PURPLE     RED       BLUE   " << endl;
	cout << "   (-)(" << PurplePickUp.GetSeat(0) << ")   (-) ("; 
	cout << RedCompact.GetSeat(0) << ")   (-)   (" << BlueSedan.GetSeat(0) << ")" << endl;
	cout << "   |____|   (" << RedCompact.GetSeat(2) << ") (" << RedCompact.GetSeat(1);
	cout << ")   (" << BlueSedan.GetSeat(3) << ")(" << BlueSedan.GetSeat(2) << ")(";
	cout << BlueSedan.GetSeat(1) << ")" << endl;
	cout << endl;
	cout << "   GREEN     BLUE       BLACK  " << endl;
	cout << "   (-)(" << GreenPickUp.GetSeat(0) << ")   (-) (" << BlueCompact.GetSeat(0);
	cout << ")   (-)   (" << BlackSedan.GetSeat(0) << ")" << endl;
	cout << "   |____|   (" << BlueCompact.GetSeat(2) << ") (" << BlueCompact.GetSeat(1);
	cout << ")   (" << BlackSedan.GetSeat(3) << ")(" << BlackSedan.GetSeat(2) << ")(";
	cout << BlackSedan.GetSeat(1) << ")" << endl;
	cout << endl;
	cout << "   BLACK    YELLOW      GREEN  " << endl;
	cout << "   (-)(" << BlackPickUp.GetSeat(0) << ")   (-) (" << YellowCompact.GetSeat(0);
	cout << ")   (-)   (" << GreenSedan.GetSeat(0) << ")" << endl;
	cout << "   |____|   (" << YellowCompact.GetSeat(2) << ") (" << YellowCompact.GetSeat(1);
	cout << ")   (" << GreenSedan.GetSeat(3) << ")(" << GreenSedan.GetSeat(2) << ")(";
	cout << GreenSedan.GetSeat(1) << ")" << endl;
};
// Seat Legend
void Vehicle::displayLegend(){
	cout << endl;
	cout << "          Seat Legend" << endl;
	cout << "      -------------------" << endl;
	cout << "         (-) - Driver" << endl;
	cout << "      (#) - Seat Available" << endl;
	cout << "      (X) - Seat Reserved" << endl;
	cout << endl;
}

// Display Passengers Of Selected Vehicle
void Vehicle::displayPassNames() {
	cout << endl << "    Current Seating Assignments" << endl;
	// Pickup, Compact, And Sedan
	cout << "     Driver : " << driverName << endl;
	cout << "      Front : " << Seat1Name << endl;
	// Compact
	if (numSeats == 3) {
		cout << " Back Right : " << Seat2Name << endl;
		cout << "  Back Left : " << Seat3Name << endl;
	}
	// Sedan
	else if (numSeats == 4) {
		cout << " Back Right : " << Seat2Name << endl;
		cout << "Back Middle : " << Seat3Name << endl;
		cout << "  Back Left : " << Seat4Name << endl;
	}
	// Display Available Selections
	availableSeatOptions();
}

string Vehicle::GetVehicleType() {
	return vehicleType;
}
string Vehicle::GetVehicleColor() {
	return vehicleColor;
}
string Vehicle::GetSeat(int num) {
	return Seats.at(num);
}
int Vehicle::GetOpenNumberSeats() {
	return openSeats;
}

// Based On Strig Input Of Seat Position Returns Int Of Seat Position
int Vehicle::GetSeatValueFromString(string position) {
	int num;
	if (position == "Front") {
		num = 5;
	}
	if (numSeats == 3) {
		if (position == "Back Window") {
			num = 3;
		}
	}
	if (numSeats == 4) {
		if (position == "Back Window") {
			num = 2;
		}
		else if (position == "Back Middle") {
			num = 1;
		}
	}
	return num;
}

// Returns Int Based On String Input
int Vehicle::GetSeatPosValFromString(string position) {
	srand((unsigned)time(NULL)); // For True Random Numbers
	// Pickup, Compact, Sedan
	if (position == "Front") {
		return 1;
	}
	// Compact
	if (numSeats == 3) {
		if (position == "Back Window") {
			// Return Random 
			if (Seat2Name != "Unassigned") {
				return 3;
			}
			if (Seat3Name != "Unassigned") {
				return 2;
			}
			// Randomly Choose 3 Or 2 If Both Seats Are Empty
			return (rand() % 2) + 2; 
		}
	}
	// Sedan
	if (numSeats == 4) {
		if (position == "Back Window") {
			if (Seat2Name != "Unassigned") {
				return 4;
			}
			if (Seat4Name != "Unassigned") {
				return 2;
			}
			// Randomly Choose 4 Or 2 If Both Seats Are Empty
			int temp = (rand() % 2) + 1;
			if (temp == 0) {
				return 4;
			}
			else {
				return 2;
			}
		}
		else if (position == "Back Middle") {
			return 3;
		}
	}
}


// Returns Available Seat Options To Choose From
string Vehicle::availableSeatOptions() {
	string out;
	out = out + "Choose from available seats:";
	// Pickup, Compact, And Sedan
    if(Seat1Name == "Unassigned"){
		out = out + " Front,";
	}
	if (numSeats == 3) {
		if ((Seat2Name == "Unassigned") || (Seat3Name == "Unassigned")) {
			out = out + " Back Window,";
		}
	}
	else if (numSeats == 4) {
		if ((Seat2Name == "Unassigned") || (Seat4Name == "Unassigned")) {
			out = out + " Back Window,";
		}
		if ((Seat3Name == "Unassigned")) {
			out = out + " Back Middle";
		}
	}
	return out;
}
// Returns If Seat Is Open Or Not Boolean Value True For String Input
bool Vehicle::GetSeatStatus(string seatposition) {
	// Pickup, Compact, And Sedan
	if (seatposition == "Front" && Seat1Name == "Unassigned") {
		return true;
	}
	// Compact
	if (numSeats == 3) {
		if (seatposition == "Back Window" && ((Seat2Name == "Unassigned") 
			|| (Seat3Name == "Unassigned"))){
			return true;
		}
	}
	// Sedan
	else if (numSeats == 4) {
		if (seatposition == "Back Window" && ((Seat2Name == "Unassigned") 
			|| (Seat4Name == "Unassigned"))){
			return true;
		}
		else if (seatposition == "Back Middle" && Seat3Name == "Unassigned") {
			return true;
		}
	}
	return false;
}

void Vehicle::adminCout() {
	cout << vehicleColor + " " + vehicleType << endl;
	cout << "-----------------" << endl;
	if (numSeats == 1) {
		cout << "Driver Seat: " << driverName << endl;
		cout << "Front Seat: " << Seat1Name << endl;
	}
	if (numSeats == 3) {
		cout << "Driver Seat: " << driverName << endl;
		cout << "Front Seat: " << Seat1Name << endl;
		cout << "Back Right: " << Seat2Name << endl;
		cout << "Back Left: " << Seat3Name << endl;
	}
	if (numSeats == 4) {
		cout << "Driver Seat: " << driverName << endl;
		cout << "Front Seat: " << Seat1Name << endl;
		cout << "Back Right: " << Seat2Name << endl;
		cout << "Back Middle: " << Seat3Name << endl;
		cout << "Back Left: " << Seat4Name << endl;
	}
	cout << endl;
}

//------Printing------------------------
string Vehicle::adminPrint() {
	string temp;
	if (numSeats == 1) {
		temp =
			vehicleColor + " " + vehicleType + "\n" + "-----------------" + "\n" +
			"Driver Seat: " + driverName + "\n" +
			"Front Seat: " + Seat1Name + "\n";
	}
	if (numSeats == 3) {
		temp =
			vehicleColor + " " + vehicleType + "\n" + "-----------------" + "\n" +
			"Driver Seat: " + driverName + "\n" +
			"Front Seat: " + Seat1Name + "\n" +
			"Back Right: " + Seat2Name + "\n";
	}
	if (numSeats == 4) {
		temp =
			vehicleColor + " " + vehicleType + "\n" + "-----------------" + "\n" +
			"Driver Seat: " + driverName + "\n" +
			"Front Seat: " + Seat1Name + "\n" +
			"Back Right: " + Seat2Name + "\n" +
			"Back Middle: " + Seat3Name + "\n" +
			"Back Left: " + Seat4Name + "\n";
	}
	return temp + "\n";
}

string Vehicle::PassengerPrint() {
	string temp;
	if (numSeats == 1) {
		temp =

			"Driver Seat: " + driverName + "\n" +
			"Front Seat: " + Seat1Name + "\n";
	}
	if (numSeats == 3) {
		temp =

			"Driver Seat: " + driverName + "\n" +
			"Front Seat: " + Seat1Name + "\n" +
			"Back Right: " + Seat2Name + "\n" +
			"Back Left : " + Seat3Name + "\n";
	}
	if (numSeats == 4) {
		temp =

			"Driver Seat: " + driverName + "\n" +
			"Front Seat: " + Seat1Name + "\n" +
			"Back Right: " + Seat2Name + "\n" +
			"Back Middle: " + Seat3Name + "\n" +
			"Back Left: " + Seat4Name + "\n";
	}
	return temp + "\n";
}

