/*
	Name: Miguel Juarez
	Date: 11/22/2022
	Class: CIS 160 Fundamentals of Computer Science I
	Project Name: Passaic County Contracting Company
	Description: Program receives information from a number of contracts, processes information, 
				 and displays totals of each contract and totals of all contracts combined
*/

//Preprocessor directives needed for program
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

//Function prototypes to take user input, perform calculations, and display output
void Input(string, float&, float&, float&, float&, float&, float&);
void contractProcess(float, float, float, float, float, float, float, float, float, float&, float&, float&);
void contractOutput(string, int, float, float, float);
void Process(float, float, float, float, float, float, float&, float&);
void Output(string, float, float, float, float, float, float, float, float);

//Template functions for addition and subtraction operations
template<class T>
float add(T, T, T, T, T num5 = 0, T num6 = 0, T num7 = 0, T num8 = 0);

template<class T>
float subtract(T, T);

//Used to print output out into a separate text file
ofstream fout("Output.txt");

int main()
{
	float totalElectrical = 0.0; //Total cost of electrical between all contracts
	float totalPlumbing = 0.0; //Total cost of plumbing between all contracts
	float totalRoofing = 0.0; //Total cost of roofing between all contracts
	float totalMaterials = 0.0; //Total cost of materials(wood, concrete, doors, and windows) between all contracts
	float totalSalaries = 0.0; //Total salaries given to every employee between all contracts
	float totalAmount = 0.0; //Total amount received from all contracts
	float totalCost = 0.0; //Total cost of all the contracts
	float totalProfit = 0.0; //Total gain/loss from all contracts

	string line; //Underscore character used for formatting output
	line.assign(55, '_');

	Input(line, totalElectrical, totalPlumbing, totalRoofing, totalMaterials, totalSalaries, totalAmount);
	Process(totalElectrical, totalPlumbing, totalRoofing, totalMaterials, totalSalaries, totalAmount, totalCost, totalProfit);
	Output(line, totalElectrical, totalPlumbing, totalRoofing, totalMaterials, totalSalaries, totalAmount, totalCost, totalProfit);
}

//Prompts user to input contract information, each contract gets calculated and displays output
//Values are saved by variables that are passsed by reference for calculation of all contracts
//All parameters will be passed by reference to store user input, except for the first one "line"
void Input(string line, float& totalElectrical, float& totalPlumbing, float& totalRoofing, float& totalMaterials, float& totalSalaries, float& totalAmount)
{
	int number; //Keeps track of the number of contracts
	float amount; //Amount of money received for a contract
	float electrical; //Cost of electrical for a contract
	float plumbing; //Cost of plumbing for a contract
	float roofing; //Cost of roofing for a contract
	float salary = 0.0; //Amount paid to an employee
	float wood; //Cost of wood
	float concrete; //Cost of concrete
	float windows; //Cost of windows
	float doors; //Cost of doors
	float salaries = 0.0; //Sum of salaries for a contract
	float cost; //Total cost of a contract
	float profit; //Total gain/loss of a contract

	cout << "Contract Number(Press 0 when done): ";
	cin >> number;
	do
	{
		cout << "\nContract Amount: ";
		cin >> amount;
		totalAmount += amount;
		cout << "\nElectrical Cost: ";
		cin >> electrical;
		totalElectrical += electrical;
		cout << "\nPlumbing Cost: ";
		cin >> plumbing;
		totalPlumbing += plumbing;
		cout << "\nRoofing Cost: ";
		cin >> roofing;
		totalRoofing += roofing;
		int x = 1; //counter for while loop, need at least 5 employee salaries before exiting
		while (salary != 0 || x < 6)
		{
			cout << "\nPlease input salary for Employee " << x << "(Press 0 when done):";
			cin >> salary;
			if (salary == 0 && x < 6)
			{
				while (salary == 0)
				{
					cout << "\nA minimum of 5 employees is required, please input salary:";
					cin >> salary;
				}
			}
			salaries += salary;
			x++;
		}
		totalSalaries += salaries;
		cout << "\nWood Cost: ";
		cin >> wood;
		cout << "\nConcrete Cost: ";
		cin >> concrete;
		cout << "\nWindows Cost: ";
		cin >> windows;
		cout << "\nDoors Cost: ";
		cin >> doors;
		contractProcess(amount, electrical, plumbing, roofing, salaries, wood, concrete, windows, doors, cost, profit, totalMaterials);
		contractOutput(line, number, amount, cost, profit);
		salaries = 0;
		cout << "\n\nContract Number(Press 0 when done): ";
		cin >> number;
	} while (number != 0);
}

/* Calculations to find the total cost of a contract and total gain/loss of contract
Material costs is saved for total calulations done later
9 parameters are passed by value and 3 parameters are passed by reference*/
void contractProcess(float amount, float electrical, float plumbing, float roofing, float salaries, float wood, float concrete, float windows, float doors, float& cost, float& profit, float& totalMaterials)
{
	totalMaterials += add(wood, concrete, windows, doors);
	cost = add(electrical, plumbing, roofing, salaries, wood, concrete, windows, doors);
	profit = subtract(amount, cost);
}

//Displays the output of each contract's information on a separate text file
//Parameters are all user input and results from calculations that will be passed by value for displaying output
void contractOutput(string line, int number, float amount, float cost, float profit)
{
	fout << line << endl;
	fout << "\tPassaic County Contracting Company" << endl;
	fout << "\t\t   Contract #" << number << endl;
	fout << line << endl;
	fout << fixed << setprecision(2) << showpoint;
	fout << "Contract Amount:\t\t\t$" << amount << endl;
	fout << "Contract Cost:\t\t\t\t$" << cost << endl;
	fout << "Profit/Loss:\t\t\t\t$" << profit << endl;
	fout << line << "\n\n\n";
}

/* Calculations to find the total cost of all contracts and total gain/loss of all contracts
6 parameters are passed by value and 2 parameters are passed by reference*/
void Process(float totalElectrical, float totalPlumbing, float totalRoofing, float totalMaterials, float totalSalaries, float totalAmount, float& totalCost, float& totalProfit)
{
	totalCost = add(totalElectrical, totalPlumbing, totalRoofing, totalMaterials, totalSalaries);
	totalProfit = subtract(totalAmount, totalCost);
}

//Displays the output of gain, cost, and profit between all contracts
//Parameters are all user input and results from calculations that will be passed by value for displaying output
void Output(string line,  float totalElectrical, float totalPlumbing, float totalRoofing, float totalMaterials, float totalSalaries, float totalAmount, float totalCost, float totalProfit)
{
	fout << line << endl;
	fout << "\tPassaic County Contracting Company" << endl;
	fout << "\t     Totals From Contract(s)" << endl;
	fout << line << endl;
	fout << fixed << setprecision(2) << showpoint;
	fout << "Electrical Total:\t\t\t$" << totalElectrical << endl;
	fout << "Plumbing Total:\t\t\t\t$" << totalPlumbing << endl;
	fout << "Roofing Total:\t\t\t\t$" << totalRoofing << endl;
	fout << "Material Total:\t\t\t\t$" << totalMaterials << endl;
	fout << "Total Salaries:\t\t\t\t$" << totalSalaries << endl;
	fout << "\nTotal Amount From Contracts:\t\t$" << totalAmount << endl;
	fout << "Total Cost of Contracts:\t\t$" << totalCost << endl;
	fout << "Total Profit:\t\t\t\t$" << totalProfit << endl;
	fout << line << "\n\n\n";
	fout.close();
}

//Template function to perform addition with up to eight different values and return a float result
//Last four parameters contains default values to allow the addition of four numbers
template<class T>
float add(T num1, T num2, T num3, T num4, T num5, T num6, T num7, T num8)
{
	return num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8;
}

//Template function to perform subtraction and return a float result
//First parameter will be subtracted by the second parameter
template<class T>
float subtract(T num1, T num2)
{
	return num1 - num2;
}