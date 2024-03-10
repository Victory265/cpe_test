// I WILL SPLIT TO MULTI-FILE LATER

/****    HEADER FILE    *****/
#ifndef _LUDO_
#define _LUDO_

#include <string>
#include <iostream>
#include <iomanip>

enum Color {RED, BLUE, YELLOW, GREEN};

struct House
{
	Color color;
	int member;
	bool status;

	// Initiallizer
	House() {
		color = RED;
		member = 4;
		status = false;
	}
};

struct Player
{
	std::string name;
	House house;
	House house2;
};

// Function prototypes
int createPlayers();
int initializePlayers(Player *player, int player_no, int n_house, House *arr, int number_of_player);
void displayStats(Player *player, int n);
void playGame(Player *players, int size);

#endif // _LUDO_




/*****     FUNCTIONS FILE ********/
#include "header.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Function definitions
/**
 * createPlayers - sets up the gaming enviroment
 * Description: This function creates an interface
 * to get the number of players for the game.
 * 
 * It handles all input errors and also validate
 * the input.
 *
 * Return Value: The number of players
 */
int createPlayers()
{
	int n_players;

	cout << "\t\tA SIMPLISTIC AUTOMATED LUDO GAME - CPE 311 EXAM\n";
	cout << "-----------------------------------------------------------------------------------\n" << endl;
	cout << "\tEnter the number of Players (2 or 4)\n\t>> ";

	// Input loop
	cin >> n_players;
	while (cin.fail() || !(n_players == 2 || n_players == 4))
	{
		cout << "\tWrong Value inputed! Number of players should either be:\n";
		cout << "\t2 or\n\t4\n";
		cout << "\tRe-enter the number of players (2 or 4)\n\t>> ";

		// if non-numeric value was entered (ie String)
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin >> n_players;
	}

	cout << "\tGAME SET! NUMBER OF PLAYERS: " << n_players << "\n" << endl;
	return (n_players);
}



/**
 * initialize-player: Assign proper values to a player and house color
 *
 * @player: A pointer to a Player structure
 * @player_no: The position of player between 1 - 4
 * @n_house: The number of available houses to choose from
 * @arr: an arr of the 4 possible different houses
 *
 * Return Value: The number of the house assigned to the player
 */
int initializePlayers(Player *player, int player_no, int n_house, House *arr, int number_of_player)
{
	// Declaring local variables
	static int n_call = 1;
	static int taken1, taken2, taken3 = -1;
	string houses[] = {"RED", "BLUE", "YELLOW", "GREEN"};
	int house_no;

	cin.ignore();
	cout << "\tEnter name of Player " << player_no << ": >> ";
	getline(cin, player->name);

	if (number_of_player == 4)
		cout << "\tWhich house do you choose?\n";
	else
		cout << "\tChoose your first house\n";

	int counter = 6; // USED WHEN NUM_PLAYERS == 2
	do {
		if (counter == 4)
			cout << "\tChoose your second house\n";
		for (int c = 1; c <= 4; c++)
		{
			if (!(c == taken1 || c == taken2 || c == taken3))
				cout << "\t{" << c << "}" << "\t" << houses[c - 1] << endl;
		}
		cout << "\tEnter any of the number in the braces {}: >> ";
		cin >> house_no;

		// Input validation loop
		while (cin.fail() || house_no < 1 || house_no > 4 || house_no == taken1 || house_no == taken2 || house_no == taken3)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\tUnaccepted input! You are to enter a single numeric value alone\n\tRetry: >> ";
			}
			else if (house_no == taken1 || house_no == taken2 || house_no == taken3)
			{
				cout << "\tThat House has already been chosen! Chose another house :>> ";
			}
			else
			{
				cout << "\tWrong Input! Enter any number between 1 and 4 :>> ";
			}
			cin >> house_no;
		}

		if (counter == 4)
			taken3 = taken1;
		if (n_call == 1)
			taken1 = house_no;
		else if (n_call == 2)
			taken2 = house_no;
		else if (n_call == 3)
			taken3 = house_no;

		// Update the player structure
		if (counter == 6)
		{
			player->house = arr[house_no - 1];
			player->house.color = static_cast<Color>(house_no - 1);
			player->house.member = 4;
			player->house.status = true;
		}
		else
		{
			player->house2 = arr[house_no - 1];
			player->house2.color = static_cast<Color>(house_no - 1);
			player->house2.member = 4;
			player->house2.status = true;
		}

		counter -= 2;
	} while (counter != number_of_player);

	n_call++;
	cout << endl;
	return (n_house - 1);
}



/**
 * displayStats player - displayStats details in properly formatted form
 */
void displayStats(Player *player, int n)
{
	string color, color2;
	switch (player->house.color)
	{
	case 0:
		color = "Red";
		break;
	case 1:
		color = "Blue";
		break;
	case 2:
		color = "Yellow";
		break;
	case 3:
		color = "Green";
		break;
	default:
		color = "Red";
		break;
	}

	if (n == 2)
	{
		switch (player->house2.color)
		{
		case 0:
			color2 = "Red";
			break;
		case 1:
			color2 = "Blue";
			break;
		case 2:
			color2 = "Yellow";
			break;
		case 3:
			color2 = "Green";
			break;
		default:
			color2 = "Red";
			break;
		}
	}

	if (n == 1)
	{
		cout << setw(15) << player->name << "\t\t|" << setw(15) << color << "\t\t|\t" << setw(15) << player->house.member << endl;
		cout << "--------------------------------------------------------------------------------------------" << endl;
	}
	else
	{
		cout << setw(15) << player->name << "\t\t|" << setw(15) << color << "\t\t|\t" << setw(15) << player->house.member << endl;
		cout << setw(15) << "" << "\t\t|" << setw(15) << color2 << "\t\t|\t" << setw(15) << player->house2.member << endl;
		cout << "--------------------------------------------------------------------------------------------" << endl;
	}
}




/**
 * playGame - subtracts members from each player
 */
void playGame(Player *players, int size)
{
	for (int c = 0; c < size; c++)
	{
		players[c].house.member -= (c + 1);
		if (players[c].house2.status)
			players[c].house2.member -= (c + 1);
	}
}




/******      MAIN FUNCTION FILE    *********/
#include "header.h"

using namespace std;


/**
 * The Main Function -  Program Entry Point
 * It calls all necessary functions that does the following
 * - ask user for how many players
 * - dynamically create the players and their houses
 * - initialize all created values
 * - Print nicely formatted table
 * - Deallocate the previously allocated memory
 *
 * Return Value: Always 0
 */
int main(void)
{
	// DECLARE VARIABLES
	int n_house = 4;
	int number_of_player;
	House *houses = new House[n_house];
	number_of_player = createPlayers();
	Player *players = new Player[number_of_player];

  
	// INITIALIZE ALL CREATED PLAYERS
	for (int c = 0; c < number_of_player; c++)
	{
		n_house = initializePlayers(&players[c], c + 1, n_house, houses, number_of_player);
	}

  // DISPLAY GAME STATS IN TABULAR FORM
	cout << "\n\n" << setw(15) << "NAME" << "\t\t|" << setw(15) << "HOUSE" << "\t\t|" << setw(15) << "MEMBER" << endl;
	cout << "********************************************************************************************" << endl;
	for (int c = 0; c < number_of_player; c++)
	{
		if (number_of_player == 2)
			displayStats(&players[c], 2);
		else
			displayStats(&players[c], 1);
	}

	// PLAY GAME AND DEDUCT PLAYERS
	playGame(players, number_of_player);
	cout << "\n\t\t\t\tAFTER SUBTRACTING PIECES...\t\t\t\n" << endl;
	for (int c = 0; c < number_of_player; c++)
	{
		if (number_of_player == 2)
			displayStats(&players[c], 2);
		else
			displayStats(&players[c], 1);
	}

	// CLEANUP AND FREE ALLOCATED MEMORY
	system("pause");
	delete [] houses;
	delete [] players;
	return (0);
}
