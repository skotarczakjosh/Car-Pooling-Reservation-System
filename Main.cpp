//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Title: Main.cpp
// Course: Computational Problem Solving II (CPET - 321)
// Developer: Josh Skotarczak (CPET) 
// Date: 11/20/2022
// Description: Main Test File For Parent Reservation And Child Vechile
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Libraries
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
// Include Classes
#include "Vehicle.h"
#include "Reservation.h"
// Namespace
using namespace std;

// Displays Main Menu Options
void defaultMenu() {
	cout << "  Welcome to the Dodgeball Vehicle Reservation System   " << endl;
	cout << "           What would you like to do first?             " << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "                     RESERVATIONS                       " << endl;
	cout << "1) Create a Resevation        2) Modify a Reservation   " << endl;
	cout << "3) Delete a Reservation       4) Display Seats          " << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "                       PRINTING                         " << endl;
	cout << "5) Print Assignments          6) Print Reservations     " << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "                      DIRECTIONS                        " << endl;
	cout << "             7) HOW TO USE THIS PROGRAM?                " << endl;
	cout << "--------------------------------------------------------" << endl;

}

// Displays Directions On How To Use
void readMe() {
	cout << "                                How to use this program:" << endl;
	cout << "                  *Every non-driver must have available credits in order to reserve a seat*" << endl;
	cout << "1) Create a Reservation: Enter a name - shows credits and allow user to choose seat. A reservation number will be given" << endl;
	cout << "2) Modify a Reservation: Enter a reservation number, if exists,  user will be allowed to reselect a seat" << endl;
	cout << "3) Delete a Reservation: Users can delete an existing reservation" << endl;
	cout << "4) Display Seats: Shows current assignments. '-' is drivers seat, 'X' is a taken seat, and numbers are the seat value" << endl;
	cout << "5) Print Assignments: Prints passenger list of that vehicle to a text file" << endl;
	cout << "6) Admin: Print Reservations: Prints a passenger list of all six vehicles to a text file. Needs an admin password" << endl;
}

// Vehicle Color Spelling Checker
bool colorCheck(string vehicleCategory, string vehColor) {
	// Pickup
	if (vehicleCategory == "Pickup") {
		if ((vehColor == "Purple") || (vehColor == "Green") || (vehColor == "Black")) {
			return true;
		}
	}
	// Compact
	else if (vehicleCategory == "Compact") {
		if ((vehColor == "Red") || (vehColor == "Blue") || (vehColor == "Yellow")) {
			return true;
		}
	}
	// Sedan
	else if (vehicleCategory == "Sedan") {
		if ((vehColor == "Blue") || (vehColor == "Black") || (vehColor == "Green")) {
			return true;
		}
	}
	return false;
}

// Vehicle Seat Position Spelling Checker
bool seatCheck(string vehicleCategory, string seatPos) {
	// Pickup
	if (vehicleCategory == "Pickup") {
		if ((seatPos == "Front")) {
			return true;
		}
	}
	// Compact
	else if (vehicleCategory == "Compact") {
		if ((seatPos == "Front") || (seatPos == "Back Window")) {
			return true;
		}
	}
	// Sedan
	else if (vehicleCategory == "Sedan") {
		if ((seatPos == "Front") || (seatPos == "Back Middle") ||  (seatPos == "Back Window")) {
			return true;
		}
	}
	return false;
}

// Displays If Team Member Is A Driver
void isDriverDisplay() {
	system("cls");
	cout << "You are on the Team but also a driver. You cannot make a reservation." << endl;
	system("pause");
}
// Displays If Reservation Is Found
void resFound(string name, int seatPoints) {
	system("cls");
	cout << "                   CREATE RESERVATION" << endl;
	cout << "           ----------------------------------" << endl;
	cout << endl << name << " You Currently Have " << seatPoints << " Seat Credits Remaining" << endl;
	cout << "           But You Already Have A Reservation" << endl;
	cout << "Please Use Modify Or Delete Reservation Options In Main Menu" << endl;
	cout << "              To Change Reserved Seat" << endl;
	system("pause");
}
// Displays If User Has No Credits
void noCredits(string name) {
	cout << "   " << name << " You Currently Have 0 Seat Credits" << endl;
	cout << "Which Means You are Broke and cannot Reserve a Seat" << endl;
	cout << "     Looks like you're Walking to the Game!" << endl;
}
// Displays If Not On Team
void isNotTeam() {
	cout << "You are not on the Team. You cant make a reservation." << endl;
	system("pause");
}
// Displays If Vehicle Chosen Is Full
void vehFull() {
	cout << "   No Available Seats Left!" << endl;
	cout << "Please Choose Different Vechicle" << endl;
	system("pause");
}
// Displays If Not Enough Seat Credits
void notEnough() {
	cout << "   Not Enough Seat Credits To Reserve Seat" << endl;
	cout << "Choose A Seat You Can Afford Or Walk To The Game" << endl;
	system("pause");
}

int main() {
	// List Of Class Reservations --------------------------------
	list<Reservation> ResList;        // List of Reservation Class
	list<Reservation>::iterator iter; // Iterator of the Objects 
	//-----------------------------------------------------------
	// File Read Varibles ---------------------------------------
	ifstream inFile; // File Read Verible
	string line;	 // Temp Getline
	string trash;	 // Used For Ignoring First 9 Lines
	string user;     // File Read Input And User Input
	//-----------------------------------------------------------
	// Booleans -------------------------------------------------
	bool isOnTeam = false;        // True If On Team
	bool isDriver = false;        // True If A Driver
	bool SeatOpen = false;        // True If Seat Is Open
	bool ResFound = false;        // True If Reservation Is Foud
	bool Create = false;          // True If In Create Option
	bool HasReservation = false;  // True If Has Reservation
	// Integers -------------------------------------------------
	int pointsLocation;	// Points Locationation of User In Array
	int openSeats;      // Open Seats In Chosen Vehicle
	int SeatValue;      // Orgianl Seat Value When Reserved
	int SeatPosValue;   // Gets Seat Postion Number
	//-----------------------------------------------------------
	// Strings --------------------------------------------------
	string vehicleCategory;  // Current Vehicle Category
	string vehColor;         // Current Vehicle Color
	string seatPos;          // Current Seat Position
	string menuInput;        // Main Menu Input
	string OpenPositions;    // Open Seat Positions
	// Arrays For Name , Credits , Reservation Numbers ----------
	array<string, 33> names;       // Names 
	array<string, 24> scredits;    // Seat Credits as Strings
	array<int, 24> credits;	       // Seat Credits as Integers
	array<string, 24> ResNum;      // Reservation Numbers Tracker
	//-----------------------------------------------------------
	int GivenResNum;               // Given Num When Reservation
	ResNum.fill("Unassigned"); 	   // Fill Array "Unassigned"
	string ResNumCheck;            // User Input Reservation Num
	//-----------------------------------------------------------
	// Modify Reservation Varibles ------------------------------
	int modRes;                    // Modify Reservation Num Input
	string modName;
	bool isModState = false;
	bool Exit = false;
	//-----------------------------------------------------------
	// Admin Password -------------------------------------------
	string adminInput;            // Password Input
	string adminpass = "941029";  // Admin Password
	int passAttempts = 4;         // Password Attempts
	//-----------------------------------------------------------
	// Print Variables-------------------------------------------
	string vehiclePrintIn;
	//-----------------------------------------------------------
	// Read txt file for NAMES ONLY -----------------------------
	inFile.open("dodgeball.txt");
	for (int i = 0; i < 9; i++) {	// Gets The First 9 Users
		getline(inFile, line);		// No Nums On First 9, So
		names[i] = line;			// Assign First 9 in names[]
	}
	for (int i = 0; i < 24; i++) {	// names[] Remaining 24 Elements
		getline(inFile, line);
		line.pop_back();      // Remove Last 2 Chars
		line.pop_back();      //  (Number and Space)
		names[i + 9] = line;  // Assign To names[] From 9th Element
	}
	inFile.close();
	//------------------------------------------------------------
	// Read txt File For CREDITS ONLY-----------------------------
	inFile.open("dodgeball.txt");
	for (int i = 0; i < 9; i++) {	//For First 9 Drivers, Ignore
		getline(inFile, trash);
	}
	for (int i = 0; i < 24; i++) { // scredits[] Gets Last Char
		getline(inFile, line);	  //  of Each Non Driver
		scredits[i] = line.at(line.size() - 1);	

	}
	inFile.close();
	// Convert From Strings To Ints
	for (int i = 0; i < 24; i++) {	    // Convert scredits[] To Ints 
		credits[i] = stoi(scredits[i]); // Using stoi()
	}
	//-----------------------------------------------------------
	// Vehicle Constructor Inputs -------------------------------
	// Pickups
	Vehicle PurplePickUp(names[0], "Purple", 1);  // Purple, 1 Seat
	Vehicle GreenPickUp(names[1], "Green", 1);    // Green, 1 Seat
	Vehicle BlackPickUp(names[2], "Black", 1);    // Black, 1 Seat
	// Compacts
	Vehicle RedCompact(names[3], "Red", 3);       // Red, 3 Seats
	Vehicle BlueCompact(names[4], "Blue", 3);     // Blue, 3 Seats
	Vehicle YellowCompact(names[5], "Yellow", 3);// Yellow, 3 Seats
	// Sedan
	Vehicle BlueSedan(names[6], "Blue", 4);       // Blue, 4 Seats
	Vehicle BlackSedan(names[7],"Black", 4);     // Black, 4 Seats
	Vehicle GreenSedan(names[8],"Green", 4);     // Green, 4 Seats
	//-----------------------------------------------------------
	// Main User Interface Loop ---------------------------------
	do {
		// If Not In Modification State
		if (isModState == false) {
			// Display Main Menu
			system("cls");
			defaultMenu();
			cout << "Input=> ";
			cin >> menuInput;
		}
		else {
			menuInput = "1";
		}
		if (menuInput == "1") {
			// Display Create Reservation Menu
			system("cls");
			cout << "        CREATE RESERVATION" << endl;
			cout << "----------------------------------" << endl;
			cout << "  Enter Name: ";
			// If In Mod State Clear Screen
			if (isModState) {
				system("cls");
			}
			else {
				// Get Name From User
				cin.ignore();
				getline(cin, user);
			}
			// If User Input Is "-1" Return To Main Menu
			if (user == "-1") {
				continue; // If "-1" Go Back To Main Screen
			}
			// Check If User Input Name Is On List
			for (int i = 0; i < 33; i++) {
				if (user == names[i]) { // If Name Found
					isOnTeam = true;
					if (i < 9) {   // If First 9 Then Is Driver
						isDriver = true;
					}
					else {
						pointsLocation = i - 9; // Else On Team
					}
					break;
				}
				else {
					// Reset Varibles
					isOnTeam = false;
					isDriver = false;
				}
			}
			//Check to see if on Team and if Driver
			if (isOnTeam) {
				if (isDriver) {
					// If Driver Display 
					isDriverDisplay();
					continue;
				}
				else {
					// Check If They Allready Have Reservation In There Name Then Kick Back To Main Menu
					HasReservation = false; //Reset Varible To False
					// If Reservation List Is Not Empty Check If They Have Reservation 
					if (!ResList.empty()) {
						list<Reservation>::iterator Created; // Iterator of the Object 
						for (Created = ResList.begin(); Created != ResList.end(); Created++) {
							if (Created->GetName() == user) { // If Reservation Is Found
								resFound(user, credits[pointsLocation]); // Display Already Have Reservation
								HasReservation = true;
								break;
							}
						}
					}
					// Check to see if they have credits to even reserve seats
					if (credits[pointsLocation] == 0) {
						noCredits(user);
						system("pause");
					}
					// If No Reservation Found Then Can Make Reservation
					if (HasReservation == false && credits[pointsLocation] > 0) {
						system("cls");
						// If Not In Mod State Then Show Create
						if (!isModState) {
						cout << "        CREATE RESERVATION" << endl;
						}
						// Else Show Modify Header
						else {
						cout << "        MODIFY RESERVATION" << endl;
						cout << "(Cancelling Results In No Reservation)" << endl;
						}
						cout << "----------------------------------" << endl;
						// Can Use Any Vehicle Object Here, All Vehicle Objects Are Passed  Through
						PurplePickUp.displayFullLayout(PurplePickUp, GreenPickUp, BlackPickUp, RedCompact,
							BlueCompact, YellowCompact, BlueSedan, BlackSedan, GreenSedan);
						cout << endl;
						//Display Seat Legend, Users Credits and Get User Input
						PurplePickUp.displayLegend();
						cout << "Welcome " << user << ", You have " << credits[pointsLocation] << " Credits" << endl << endl;
						cout << "Please choose a vehicle category: Pickup, Compact, or Sedan" << endl;
						cout << "Input=> ";
						cin >> vehicleCategory;
						//Vehicle Category Spell Checker
						while (1) {
							// If Input Is Not Correct Then Prompt For New Input
							if ((vehicleCategory != "Pickup") && (vehicleCategory != "Compact") && (vehicleCategory != "Sedan") && (vehicleCategory != "-1")) {
								cout << endl<<  "Vehicle type not found. Please try again." << endl;
								cout << "Please choose a vehicle category: Pickup, Compact, or Sedan" << endl;
								cout << "Input =>";
								cin >> vehicleCategory;
								
							}
							else {
								// If Input is -1 Then Exit
								if (vehicleCategory == "-1") {
									Exit = true;
								}
								break;
							}
						}
						// If Exit Is True Then Go Back To Main Menu
						if (Exit) {
							Exit = false;
							isModState = false;
							continue;
						}
						// PICKUP ---------------------------------------------------
						if (vehicleCategory == "Pickup") {
							// Display Color Choices
							cout << endl<<  "Please choose color: Purple, Green, or Black" << endl;
							cout << "Input=> ";
							cin >> vehColor;
							while (1) {
								// If Input is "-1" Exit To Main Menu
								if (vehColor == "-1") {
									Exit = true;
									break;
								}
								// If Color is True Break
								if (colorCheck(vehicleCategory, vehColor) == true) {
									break;
								}
								else {
									// If Color Isnt Found 
									cout << endl << "Color not found. Please try again" << endl;
									cout << "Please choose color: Purple, Green, or Black" << endl;
									cout << "Input=>";
									cin >> vehColor;
								}
							}
							if (Exit) {
								Exit = false;
								isModState = false;
								continue; // Back To Main Menu
							}
							system("cls");
							// If Not In Mod State Then Show Create Else Show
							if (!isModState) {
								cout << "        CREATE RESERVATION" << endl;
							}
							else {
								cout << "        MODIFY RESERVATION" << endl;
								cout << "(Cancelling Results In No Reservation)" << endl;
							}
							cout << "----------------------------------" << endl;
							cout << user << ", You have " << credits[pointsLocation] << " Seat Credits" << endl << endl;
							if (vehColor == "Purple") {
								openSeats = PurplePickUp.GetOpenNumberSeats();         // Get Open Number Of Seats 
								PurplePickUp.displaySeatLayout();                      // Get Vehicle Diagram
								PurplePickUp.displayLegend();                          // Get Seat Legend
								PurplePickUp.displayPassNames();                       // Display Passenger Names
								OpenPositions = PurplePickUp.availableSeatOptions();   // Ger Open Positions
							}
							else if (vehColor == "Green") {
								openSeats = GreenPickUp.GetOpenNumberSeats();          // Get Open Number Of Seats 
								GreenPickUp.displaySeatLayout();                       // Get Vehicle Diagram
								GreenPickUp.displayLegend();                           // Get Seat Legend
								GreenPickUp.displayPassNames();                        // Display Passenger Names
								OpenPositions = GreenPickUp.availableSeatOptions();    // Ger Open Positions
							}
							else if (vehColor == "Black") {
								openSeats = BlackPickUp.GetOpenNumberSeats();          // Get Open Number Of Seats 
								BlackPickUp.displaySeatLayout();                       // Get Vehicle Diagram
								BlackPickUp.displayLegend();                           // Get Seat Legend
								BlackPickUp.displayPassNames();                        // Display Passenger Names
								OpenPositions = BlackPickUp.availableSeatOptions();    // Ger Open Positions
							}
							if (openSeats > 0) {
								cout << endl << OpenPositions << endl;
								cout << "Input =>";
								cin.ignore();
								getline(cin, seatPos);
								// Check Seat Spelling
								while (1) {
									if (seatPos == "-1") {
										Exit = true;
										break;
									}
									if (seatCheck(vehicleCategory, seatPos) == true) {
										// Check If Seat Is Available IF Spelling is Write
										SeatOpen = false;
										if (vehColor == "Purple") {
											SeatOpen = PurplePickUp.GetSeatStatus(seatPos);
										}
										else if (vehColor == "Green") {
											SeatOpen = GreenPickUp.GetSeatStatus(seatPos);
										}
										else if (vehColor == "Black") {
											SeatOpen = BlackPickUp.GetSeatStatus(seatPos);
										}
										if (SeatOpen == false) {
											cout << endl << "Position Already Reserved" << endl;
											cout << OpenPositions << endl;
											cout << "Input=> ";
											cin >> seatPos;
										}
										else {
											break;
										}
									}
									// If Spelling is Wrong
									else {
										cout << endl << "Position Not Found. Please try again" << endl;
										cout << OpenPositions << endl;
										cout << "Input=> ";
										cin >> seatPos;
									}
								}
								// If Exit Is True Then Go Back To Main Menu
								if (Exit) {
									Exit = false;
									isModState = false;
									continue;
								}
								
								// If Seat Is Open Reserve Seat
								if (SeatOpen) {
									// Check to See Enough Credits
									if (credits[pointsLocation] >= 5) {
										credits[pointsLocation] = credits[pointsLocation] - 5;
										// Find Next Unused Reservation Number
										for (int j = 0; j < ResNum.size(); j++) {
											if (ResNum[j] == "Unassigned") {
												GivenResNum = j + 1;
												ResNum[j] = user;
												break;
											}
										}
										// Make Reservation And Push To List
										ResList.push_back(Reservation(user, vehColor + " " + vehicleCategory,
											GivenResNum, seatPos, 5, pointsLocation, 1));
										// Update Display With "X"
										if (vehColor == "Purple") {
											PurplePickUp.ReserveSeat(user, 1);
										}
										else if (vehColor == "Green") {
											GreenPickUp.ReserveSeat(user, 1);
										}
										else if (vehColor == "Black") {
											BlackPickUp.ReserveSeat(user, 1);
										}
										cout << endl;
										// Display Reservation
										list<Reservation>::iterator display =  ResList.end(); // Go to end Of list
										display--;  // Go Back One
										cout << "Reservation Created :" << endl;
										display->displayReservation(); // Pointer to Display Reservation
										cout << endl << user << ", You have " << credits[pointsLocation] << " Seat Credits Left" << endl;
									    system("pause");
										// Reset Mod State 
										isModState = false;
									}
									else {
										// Not Enough Seat Credits To Reserve
										notEnough();
									}
								}
								else {
									// If Seat Is All Ready Reserved
									cout << " Seat Already Reserved, Please Choose Different Seat" << endl;
									system("pause");
								}
							}
							else {
								// Display Vehicle Is Full
								vehFull();
							}
						}
						// COMPACT ---------------------------------------------------
						else if (vehicleCategory == "Compact")
						{
							// Display Color Choices
							cout << "Please choose color: Red, Blue, or Yellow" << endl;
							cout << "Input => ";
							cin >> vehColor;

							while (1) {
								if (vehColor == "-1") {
									Exit = true;
									break;
								}
								if (colorCheck(vehicleCategory, vehColor) == true) {
									break;

								}
								else {
									cout << endl << "Color not found. Please try again" << endl;
									cout << "Please choose color: Red, Blue, or Yellow" << endl;
									cout << "Input=> ";
									cin >> vehColor;
								}
							}
							// If Exit Is True Then Go Back To Main Menu
							if (Exit) {
								Exit = false;
								isModState = false;
								continue;
							}
							system("cls");
							// If Not In Mod State Then Show Create Else Show
							if (!isModState) {
								cout << "        CREATE RESERVATION" << endl;
							}
							else {
								cout << "        MODIFY RESERVATION" << endl;
								cout << "(Cancelling Results In No Reservation)" << endl;
							}
							cout << "----------------------------------" << endl;
							cout << user << ", You have " << credits[pointsLocation] << " Seat Credits" << endl << endl;
							if (vehColor == "Red") {
								openSeats = RedCompact.GetOpenNumberSeats();         // Get Open Number Of Seats 
								RedCompact.displaySeatLayout();                      // Get Vehicle Diagram
								RedCompact.displayLegend();                          // Get Seat Legend
								RedCompact.displayPassNames();                       // Display Passenger Names
								OpenPositions = RedCompact.availableSeatOptions();   // Ger Open Positions
							}
							else if (vehColor == "Blue") {
								openSeats = BlueCompact.GetOpenNumberSeats();         // Get Open Number Of Seats 
								BlueCompact.displaySeatLayout();                      // Get Vehicle Diagram
								BlueCompact.displayLegend();                          // Get Seat Legend
								BlueCompact.displayPassNames();                       // Display Passenger Names
								OpenPositions = BlueCompact.availableSeatOptions();   // Ger Open Positions
							}
							else if (vehColor == "Yellow") {
								openSeats = YellowCompact.GetOpenNumberSeats();       // Get Open Number Of Seats 
								YellowCompact.displaySeatLayout();                    // Get Vehicle Diagram
								YellowCompact.displayLegend();                        // Get Seat Legend
								YellowCompact.displayPassNames();                     // Display Passenger Names
								OpenPositions = YellowCompact.availableSeatOptions(); // Ger Open Positions
							}
							if (openSeats > 0) {
								cout << endl << OpenPositions << endl;
								cout << "Input => ";
								cin.ignore();
								getline(cin, seatPos);
								// Get Seat Status Open Or Reserved
								while (1) {
									if (seatPos == "-1") {
										Exit = true;
										break;
									}
									if (seatCheck(vehicleCategory, seatPos) == true) {
										// Check If Seat Is Available IF Spelling is Write
										SeatOpen = false;
										if (vehColor == "Red") {
											//Get Open Number Of Seats, Seat Cost, Seat Position
											SeatOpen = RedCompact.GetSeatStatus(seatPos);
											SeatValue = RedCompact.GetSeatValueFromString(seatPos);
										    SeatPosValue = RedCompact.GetSeatPosValFromString(seatPos);
										}
										else if (vehColor == "Blue") {
											//Get Open Number Of Seats, Seat Cost, Seat Position
											SeatOpen = BlueCompact.GetSeatStatus(seatPos);
											SeatValue = BlueCompact.GetSeatValueFromString(seatPos);
											SeatPosValue = BlueCompact.GetSeatPosValFromString(seatPos);
										}
										else if (vehColor == "Yellow") {
											//Get Open Number Of Seats, Seat Cost, Seat Position
											SeatOpen = YellowCompact.GetSeatStatus(seatPos);
											SeatValue = YellowCompact.GetSeatValueFromString(seatPos);
											SeatPosValue = YellowCompact.GetSeatPosValFromString(seatPos);
										}
										if (SeatOpen == false) {
											//Get Open Number Of Seats, Seat Cost, Seat Position
											cout << endl << "Position Already Reserved" << endl;
											cout << OpenPositions << endl;
											cout << "Input=> ";
											getline(cin, seatPos);
										}
										else {
											break;
										}
									}
									// If Spelling is Wrong
									else {
										cout << endl << "Position Not Found. Please try again" << endl;
										cout << OpenPositions << endl;
										cout << "Input=> ";
										getline(cin, seatPos);
									}
								}
								// If Exit Is True Then Go Back To Main Menu
								if (Exit) {
									Exit = false;
									isModState = false;
									continue; // Back To Main Menu
								}
								// If Seat Is Open Reserve Seat
								if (SeatOpen) {
									// Check to See Enough Credits
									if (credits[pointsLocation] >= SeatValue) {
										credits[pointsLocation] = credits[pointsLocation] - SeatValue;
										// Find Next Unused Reservation Number
										for (int j = 0; j < ResNum.size(); j++) {
											if (ResNum[j] == "Unassigned") {
												GivenResNum = j + 1;
												ResNum[j] = user;
												break;
											}
										}
										// If Seat Position Value Is 2 Then Add Left, If 3 Then Add Right
										if (SeatPosValue == 2) {
											seatPos = "Right " + seatPos;
										}
										else if (SeatPosValue == 3) {
											seatPos = "Left " + seatPos;
										}
										// Make Reservation And Push To List
										ResList.push_back(Reservation(user, vehColor + " " + vehicleCategory, 
											GivenResNum, seatPos, SeatValue, pointsLocation, SeatPosValue));
										// Update Display With "X"
										if (vehColor == "Red") {
											RedCompact.ReserveSeat(user, SeatPosValue);
										}
										else if (vehColor == "Blue") {
											BlueCompact.ReserveSeat(user, SeatPosValue);
										}
										else if (vehColor == "Yellow") {
											YellowCompact.ReserveSeat(user, SeatPosValue);
										}
										cout << endl;
										// Display Reservation
										list<Reservation>::iterator display = ResList.end(); // Go to end Of list
										display--;  // Go Back One
										cout << "Reservation Created :" << endl;
										display->displayReservation(); // Pointer to Display Reservation
										cout << endl << user << ", You have " << credits[pointsLocation] << " Seat Credits Left" << endl;
										isModState = false;
										system("pause");
									}
									else {
										// Not Enough Seat Credits To Reserve
										notEnough();
									}
								}
								else {
									// If Seat Is All Ready Reserved
									cout << "Seat Already Reserved, Chose Different Seat" << endl;
									system("pause");
								}
							}
							else {
								// Display Vehicle Is Full
								vehFull();
							}
						}
						// SEDAN ---------------------------------------------------
						else if (vehicleCategory == "Sedan")
						{
							// Prompt User With Inputs
							cout << "Please choose color: Blue, Black, or Green" << endl;
							cout << "Input => ";
							cin >> vehColor;
							while (1) {
								if (vehColor == "-1") {
									Exit = true;
									break;
								}
								if (colorCheck(vehicleCategory, vehColor) == true) {
									break;

								}
								else {
									cout << "Color not found. Please try again" << endl;
									cout << "Please choose color: Blue, Black, or Green" << endl;
									cout << "Input=> ";
									cin >> vehColor;
								}
							}
							// If Exit Is True Then Go Back To Main Menu
							if (Exit) {
								Exit = false;
								isModState = false;
								continue; // Back To Main Menu
							}
							system("cls");
							// If Not In Mod State Then Show Create Else Show
							if (!isModState) {
								cout << "        CREATE RESERVATION" << endl;
							}
							else {
								cout << "        MODIFY RESERVATION" << endl;
								cout << "(Cancelling Results In No Reservation)" << endl;
							}
							cout << "----------------------------------" << endl;
							cout << user << ", You have " << credits[pointsLocation] << " Seat Credits" << endl << endl;
							if (vehColor == "Blue") {
								openSeats = BlueSedan.GetOpenNumberSeats();         // Get Open Number Of Seats 
								BlueSedan.displaySeatLayout();                      // Get Vehicle Diagram
								BlueSedan.displayLegend();                          // Get Seat Legend
								BlueSedan.displayPassNames();                       // Display Passenger Names
								OpenPositions = BlueSedan.availableSeatOptions();   // Ger Open Positions
							}
							else if (vehColor == "Black") {
								openSeats = BlackSedan.GetOpenNumberSeats();        // Get Open Number Of Seats 
								BlackSedan.displaySeatLayout();                     // Get Vehicle Diagram
								BlackSedan.displayLegend();                         // Get Seat Legend
								BlackSedan.displayPassNames();                      // Display Passenger Names
								OpenPositions = BlackSedan.availableSeatOptions();  // Ger Open Positions
							}
							else if (vehColor == "Green") {
								openSeats = GreenSedan.GetOpenNumberSeats();        // Get Open Number Of Seats 
								GreenSedan.displaySeatLayout();                     // Get Vehicle Diagram
								GreenSedan.displayLegend();                         // Get Seat Legend
								GreenSedan.displayPassNames();                      // Display Passenger Names
								OpenPositions = GreenSedan.availableSeatOptions();  // Ger Open Positions
							}
							if (openSeats > 0) {
								cout << endl << OpenPositions << endl;
								cout << "Input => ";
								cin.ignore();
								getline(cin, seatPos);
								SeatOpen = false;
								// Get Seat Status Open Or Reserved
								while (1) {
									if (seatPos == "-1") {
										Exit = true;
										break;
									}
									if (seatCheck(vehicleCategory, seatPos) == true) {
										// Check If Seat Is Available IF Spelling is Write
										SeatOpen = false;
										if (vehColor == "Blue") {
											//Get Open Number Of Seats, Seat Cost, Seat Position
											SeatOpen = BlueSedan.GetSeatStatus(seatPos);             
											SeatValue = BlueSedan.GetSeatValueFromString(seatPos);
											SeatPosValue = BlueSedan.GetSeatPosValFromString(seatPos);

										}
										else if (vehColor == "Black") {
											//Get Open Number Of Seats, Seat Cost, Seat Position
											SeatOpen = BlackSedan.GetSeatStatus(seatPos);
											SeatValue = BlackSedan.GetSeatValueFromString(seatPos);
											SeatPosValue = BlackSedan.GetSeatPosValFromString(seatPos);

										}
										else if (vehColor == "Green") {
											//Get Open Number Of Seats, Seat Cost, Seat Position
											SeatOpen = GreenSedan.GetSeatStatus(seatPos);
											SeatValue = GreenSedan.GetSeatValueFromString(seatPos);
											SeatPosValue = GreenSedan.GetSeatPosValFromString(seatPos);
										}
										if (SeatOpen == false) {
											cout << endl << "Position Allready Reserved" << endl;
											cout << OpenPositions << endl;
											cout << "Input=> ";
											getline(cin, seatPos);
										}
										else {
											break;
										}
									}
									// If Spelling is Wrong
									else {
										cout << endl << "Position Not Found. Please try again" << endl;
										cout << OpenPositions << endl;
										cout << "Input=> ";
										getline(cin, seatPos);
									}
								}
								// If Exit Is True Then Go Back To Main Menu
								if (Exit) {
									Exit = false;
									isModState = false;
									continue; // Back To Main Menu
								}
								// If Seat Is Open Reserve Seat
								if (SeatOpen) {
									// Check to See Enough Credits
									if (credits[pointsLocation] >= SeatValue) {
										credits[pointsLocation] = credits[pointsLocation] - SeatValue;
										// Find Next Unused Reservation Number
										for (int j = 0; j < ResNum.size(); j++) {
											if (ResNum[j] == "Unassigned") {
												GivenResNum = j + 1;
												ResNum[j] = user;
												break;
											}
										}
										// If Seat Position Value Is 2 Then Add Right, If 4 Then Add Left
										if (SeatPosValue == 2) {
											seatPos = "Right " + seatPos;
										}
										else if (SeatPosValue == 4) {
											seatPos = "Left " + seatPos;
										}
										ResList.push_back(Reservation(user, vehColor + " " + vehicleCategory, 
											GivenResNum, seatPos, SeatValue, pointsLocation, SeatPosValue));
										if (vehColor == "Blue") {
											BlueSedan.ReserveSeat(user, SeatPosValue);
										}
										else if (vehColor == "Black") {
											BlackSedan.ReserveSeat(user, SeatPosValue);
										}
										else if (vehColor == "Green") {
											GreenSedan.ReserveSeat(user, SeatPosValue);
										}
										cout << endl;
										// Display Reservation
										list<Reservation>::iterator display = ResList.end(); // Go to end of list
										display--;  // Go Back One
										cout << "Reservation Created :" << endl;
										display->displayReservation(); // Pointer to Display Reservation
										cout << endl << user << ", You have " << credits[pointsLocation] << " Seat Credits Left" << endl;
										isModState = false;
										system("pause");
									}
									else {
										// Not Enough Seat Credits To Reserve
										notEnough();
									}
								}
								else {
									// If Seat Is All Ready Reserved
									cout << " Seat Already Reserved, Please Choose Different Seat" << endl;
									system("pause");
								}
							}
							else {
								// Display Vehicle Is Full
								vehFull();
							}
						}
					}
				}
			}
			else {
				// If Not On Team Display
				isNotTeam();
			}
		}
		else if (menuInput == "2") {
			// Display Modify Header
			system("cls");
			cout << "        MODIFY RESERVATION" << endl;
			cout << "----------------------------------" << endl;
			cout << " Please Input Reservation Number:" << endl;
			if (!ResList.empty()) {
				cout << "   Input => ";
				cin >> modRes;
				list<Reservation>::iterator iter; // Iterator of the Object 
				// Find if ResNUm is In The List
				ResFound = false;
				for (iter = ResList.begin(); iter != ResList.end(); iter++) {
					// If Res Num is in List then delete
					if (iter->GetReservationNumber() == modRes) {
						system("cls");
						cout << "        MODIFY RESERVATION" << endl;
						cout << "----------------------------------" << endl;
						cout << "Reservation found: " << endl;
						iter->displayReservation();
						string modName = iter->GetName();
						//Modify Array In Main
						ResNum[modRes - 1] = "Unassigned";
						//Get Orgianl Seat Value
						SeatValue = iter->GetSeatValue();
						//Get Points Location In Array And Update Sea Credits With Orgianl Seat Value
						pointsLocation = iter->GetPointsLocation();
						credits[pointsLocation] = credits[pointsLocation] + SeatValue;
						// Get The Seat Postion Of From Reservation Class
						SeatPosValue = iter->GetSeatNum();
						// Delete Reservaion On Display Based Vehicle And Position 
						if (iter->GetCarType() == "Purple Pickup") {
							PurplePickUp.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Green Pickup") {
							GreenPickUp.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Black Pickup") {
							BlackPickUp.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Red Compact") {
							RedCompact.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Blue Compact") {
							BlueCompact.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Yellow Compact") {
							YellowCompact.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Blue Sedan") {
							BlueSedan.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Black Sedan") {
							BlackSedan.DeleteReservedSeat(SeatPosValue);
						}
						else if (iter->GetCarType() == "Green Sedan") {
							GreenSedan.DeleteReservedSeat(SeatPosValue);
						}
						// Lastly Delete List Reservation
						ResList.erase(iter);
						// Set While To
						system("pause");
						ResFound = true;
						system("cls");
						cout << modName << " please choose a new seat" << endl;
						user = modName;
						isModState = true;
						break;
					}
				}
				if (!ResFound) {
					cout << "Reservation Not Found, Please Try Again" << endl;
					system("pause");
				}
			}
			else {
				cout << "   No Reservations At This Time" << endl;
				system("pause");
			}
		}
		else if (menuInput == "3") {
			do {
				system("cls");
				if (!ResList.empty()) {
					cout << "        DELETE RESERVATION" << endl;
					cout << "----------------------------------" << endl;
					cout << " Please Input Reservation Number:" << endl; 
					cout << "   Input => ";
					cin.ignore();
					getline(cin, ResNumCheck);
					list<Reservation>::iterator Delete; // Iterator of the Object 
					// Find if ResNUm is In The List
					ResFound = false;
					for (Delete = ResList.begin(); Delete != ResList.end(); Delete++) {
						// If Res Num is in List then delete
						if (Delete->GetReservationNumber() == stoi(ResNumCheck)) {
							system("cls");
							cout << "        DELETE RESERVATION" << endl;
							cout << "----------------------------------" << endl;
							cout << "   Reservation Found And Deleted" << endl;
							Delete->displayReservation();
							//Modify Array In Main
							ResNum[stoi(ResNumCheck) - 1] = "Unassigned";
							//Get Orgianl Seat Value
							SeatValue = Delete->GetSeatValue();
							//Get Points Location In Array And Update Sea Credits With Orgianl Seat Value
							pointsLocation = Delete->GetPointsLocation();
							credits[pointsLocation] = credits[pointsLocation] + SeatValue;
							// Get The Seat Postion Of From Reservation Class
							SeatPosValue = Delete->GetSeatNum();
							// Delete Reservaion On Display
							if (Delete->GetCarType() == "Purple Pickup") {
								PurplePickUp.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Green Pickup") {
								GreenPickUp.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Black Pickup") {
								BlackPickUp.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Red Compact") {
								RedCompact.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Blue Compact") {
								BlueCompact.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Yellow Compact") {
								YellowCompact.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Blue Sedan") {
								BlueSedan.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Black Sedan") {
								BlackSedan.DeleteReservedSeat(SeatPosValue);
							}
							else if (Delete->GetCarType() == "Green Sedan") {
								GreenSedan.DeleteReservedSeat(SeatPosValue);
							}
							// Lastly Delete List Reservation
							ResList.erase(Delete);
							// Set While To
							system("pause");
							ResFound = true;
							break;
						}
					}
					if (!ResFound) {
						cout << "Reservation Not Found, Please Try Again" << endl;
						system("pause");
					}
					break;
				}
				else {
					system("cls");
					cout << "        DELETE RESERVATION" << endl;
					cout << "----------------------------------" << endl;
					cout << "   No Reservations At This Time" << endl;
					system("pause");
					break;
				}

			} while (1);
		}
		//Prints Seats
		else if (menuInput == "4") {
			system("cls");
			cout << "           DISPLAY SEATS" << endl;
			cout << "----------------------------------" << endl;
			PurplePickUp.displayFullLayout(PurplePickUp, GreenPickUp, BlackPickUp, RedCompact,
				BlueCompact, YellowCompact, BlueSedan, BlackSedan, GreenSedan);
			PurplePickUp.displayLegend();
			system("pause");
			system("cls");

		}
		else if (menuInput == "5") {
		// Test Reservation
		system("cls");
		cout << " PRINT INDIVIDUAL PASSENGER LISTS" << endl;
		cout << "----------------------------------" << endl;
		cout << "Enter format as: Color Vehicle" << endl;
		cout << "EX: Purple Pickup" << endl << endl;
		cout << "Pickup : Purple, Green, Black" << endl;
		cout << "Compact: Blue, Yellow, Red" << endl;
		cout << "Sedan  : Blue, Black, Green" << endl;
		cout << "Input=> ";
		cin.ignore();
		getline(cin, vehiclePrintIn);

		//Pickups
		if (vehiclePrintIn == "Purple Pickup") {
			ofstream myfile;
			myfile.open("purple_pickup.txt");
			myfile << "Purple Pickup Passenger List: " << endl;
			myfile << PurplePickUp.PassengerPrint();

		}
		if (vehiclePrintIn == "Green Pickup") {
			ofstream myfile;
			myfile.open("green_pickup.txt");
			myfile << "Green Pickup Passenger List: " << endl;
			myfile << GreenPickUp.PassengerPrint();
		}
		if (vehiclePrintIn == "Black Pickup") {
			ofstream myfile;
			myfile.open("black_pickup.txt");
			myfile << "Black Pickup Passenger List: " << endl;
			myfile << BlackPickUp.PassengerPrint();
		}
		//Compacts
		if (vehiclePrintIn == "Blue Compact") {
			ofstream myfile;
			myfile.open("blue_compact.txt");
			myfile << "Blue Compact Passenger List" << endl;
			myfile << BlueCompact.PassengerPrint();
		}
		if (vehiclePrintIn == "Yellow Compact") {
			ofstream myfile;
			myfile.open("yellow_compact.txt");
			myfile << "Yellow Compact Passenger List: " << endl;
			myfile << YellowCompact.PassengerPrint();
		}
		if (vehiclePrintIn == "Red Compact") {
			ofstream myfile;
			myfile.open("red_compact.txt");
			myfile << "Red Compact Passenger List: " << endl;
			myfile << RedCompact.PassengerPrint();
		}
		//Sedan
		if (vehiclePrintIn == "Blue Sedan") {
			ofstream myfile;
			myfile.open("blue_sedan.txt");
			myfile << "Blue Sedan Passenger List: " << endl;
			myfile << BlueSedan.PassengerPrint();
		}
		if (vehiclePrintIn == "Black Sedan") {
			ofstream myfile;
			myfile.open("black_sedan.txt");
			myfile << "Black Sedan Passenger List: " << endl;
			myfile << BlackSedan.PassengerPrint();
		}
		if (vehiclePrintIn == "Green Sedan") {
			ofstream myfile;
			myfile.open("green_sedan.txt");
			myfile << "Green Sedan Passenger List: " << endl;
			myfile << GreenSedan.PassengerPrint();
		}
		system("pause");
		}
		else if (menuInput == "6") {
		system("cls");
		cout << "     ADMIN PRINT RESERVATIONS" << endl;
		cout << "----------------------------------" << endl;
		cout << "Please enter admin password: ";
		passAttempts = 4;
		for (int i = 0; i < 4; i++) {
			cin >> adminInput;
			passAttempts--;
			if (adminpass == adminInput) {
				cout << "Correct Password....Printing all reservations to all_reservations.txt now" << endl << endl;
				// Dsiplay In Command Window
				// Pickups
				PurplePickUp.adminCout();
				GreenPickUp.adminCout();
				BlackPickUp.adminCout();
				// Compacts
				RedCompact.adminCout();
				BlueCompact.adminCout();
				YellowCompact.adminCout();
				// Sedans
				BlueSedan.adminCout();
				BlackSedan.adminCout();
				GreenSedan.adminCout();
				// Open File
				ofstream myfile;
				myfile.open("all_reservations.txt");
				// Pickups
				myfile << PurplePickUp.adminPrint();
				myfile << GreenPickUp.adminPrint();
				myfile << BlackPickUp.adminPrint();
				// Compacts
				myfile << RedCompact.adminPrint();
				myfile << BlueCompact.adminPrint();
				myfile << YellowCompact.adminPrint();
				// Sedan
				myfile << BlueSedan.adminPrint();
				myfile << BlackSedan.adminPrint();
				myfile << GreenSedan.adminPrint() << endl;
				// Display Exiting  Prompt
				cout << "Print Completed...Exiting Now" << endl;
				exit(1);
			}
			else if (adminInput == "1") {
				continue; // If input Is "-1" Go Back To Main Screen
			}
			else {
				cout << "      Incorrect password" << endl;
				cout << "You have " << passAttempts << " attempts remaining" << endl<< endl;
				if (passAttempts != 0) {
					if (passAttempts == 1) {
						cout << "   HINT: Combine Bdays" << endl;
					}
					cout << "Please enter admin password: ";
				}
			}
		}
		cout << "You have reached max attempts. Returning to main menu" << endl;
		system("pause");


		}
		//Prints Program Directions / Tutorial
		else if (menuInput == "7") {
			system("cls");
			readMe();
			system("pause");
			continue;
		}

	} while (1);// Main Menu
	//-----------------------------------------------------------
}