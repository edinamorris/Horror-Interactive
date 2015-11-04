/**********************************************************************
Author: Matt Traynar
Contact: matt.traynar@gmail.com

A couple of notes before the main code starts:

	1)	I have decided that the room keys the player finds
		within the game only open certain doors. This can 
		be changed in time but my connections are as follows
		
		- Kitchen 'Room Key' unlocks Bathroom
		- Bathroom 'Room Key' unlocks the Playroom
		- Playroom 'Room Key' unlocks the Kitchen
		
		One of these keys will be useless in the game upon load 
		as one room already needs to be open. E.g. if the kitchen
		is the first room unlocked then the key in the playroom
		will exist but when the user finds it a message will tell 
		them which room it is for is already unlocked
		
	2)	In this game setup I have pre-chosen the playroom to be open
		this means the player already has the playroom key and so the
		key that they find in the bathroom will have no effect

	3)	Functions start with 'F_' and variables start with a four letter
		descriptor for the function they are part of (followed by an 
		underscore)

	4)	This has been written in VS13 and so some comments have been 
		formatted to fit with the VS interface

	5)	Feel free to make changes if you find any bugs (or even areas
		that could be improved) but please comment out the original code 
		(rather than deleting it) and also include a note with an 
		explaining why the code has been changed and also stating who 
		changed it

**********************************************************************/

#include <iostream>
#include <stdlib.h>

/*******************************************
Structure defintion to store player data in
*******************************************/
struct UserData
{
	/*The flag for the kitchen key*/
	bool K_kitchen = false;

	/*The flag for the playroom key*/
	bool K_playroom = false;

	/*The flag for the bathroom key*/
	bool K_bathroom = false;

	/*The flag for the exit key*/
	bool K_exit = false;

	/*Is the player still alive?*/
	bool alive = true;

	/*Can the player access the basement?*/
	bool basement = false;

	/*Has the player picked up the teddy yet?*/
	bool teddy = false;
};

//-----------------------------------------------
//Write some prototypes so function definition 
//order doesn't matter
//-----------------------------------------------

UserData GameSetup(UserData Player);

UserData F_Corridor(UserData Player);

UserData F_Bathroom(UserData Player);

UserData F_Playroom(UserData Player);

UserData F_Basement(UserData Player);

//-----------------------------------------------
//Function definitions
//-----------------------------------------------

/************************************************
This function sets up the game and introduces it
to the player
************************************************/
UserData GameSetup(UserData Player)
{
	int GAME_UserInput = 0;
	bool GAME_incorrect = false;

	//Having one room unlocked already means the key needs to have
	//already been 'found'
	Player.K_playroom = true;

	//Use a do...while loop to make sure the user puts a correct value in
	do
	{
		//Reset the incorrect flag
		GAME_incorrect = false;

		//Introduce the game
		std::cout << "Welcome to Doll's House" << std::endl;
		std::cout << "You wake up in a corridor, would you like to (1) explore the corridor or (2) try somewhere else?" << std::endl;

		//Read in and act on answers
		std::cin >> GAME_UserInput;

		switch (GAME_UserInput)
		{
		case 1:
			//The user chooses the corridor, run that function
			std::cout << "You've chosen to explore the corridor" << std::endl;
			Player = F_Corridor(Player);
			break;

		case 2:
			//The user chooses somewhere else, in the real game the room that is already
			//open will be random but for ease this option is already set. 
			std::cout << "The playroom is also open, you walk in" << std::endl;
			Player = F_Playroom(Player);
			return Player;
			break;

		default:
			std::cout << "That wasn't a valid option" << std::endl;
			GAME_incorrect = true;

		}
	} while (GAME_incorrect);

	return Player;
}

/***************************************************
This function contains all the decisions that happen
within the corridor
***************************************************/
UserData F_Corridor(UserData Player)
{
	//Set up variables
	int CORR_UsrDecision = 0;
	bool CORR_explore = false;
	bool CORR_incorrectEntry = false;
	bool CORR_press = true;

	while (!CORR_explore)
	{
		std::cout << "\n" << std::endl;

		//Ask some questions
		std::cout << "There are light switches, some stairs, a teddy and a door mat" << std::endl;
		std::cout << "Which would you like to explore further?" << std::endl;
		std::cout << "(1) Lights" << std::endl;
		std::cout << "(2) Stairs" << std::endl;
		std::cout << "(3) Teddy" << std::endl;
		std::cout << "(4) Door Mat" << std::endl;
		std::cout << "(5) Elsewhere" << std::endl;

		//Read in the user's answer
		std::cin >> CORR_UsrDecision;

		//Act on that answer
		switch (CORR_UsrDecision)
		{
		case 1:
			//While the user still wants to press buttons, keep giving them the option to
			while (CORR_press)
			{
				//Ask a simple int-answer question
				std::cout << "There are three light switches, choose an option" << std::endl;
				std::cout << "(1) Light 1" << std::endl;
				std::cout << "(2) Light 2" << std::endl;
				std::cout << "(3) Light 3" << std::endl;
				std::cout << "(4) Don't press any light" << std::endl;

				//Read in the answer
				std::cin >> CORR_UsrDecision;

				//Again, act on the answer
				switch (CORR_UsrDecision)
				{
				case 1:
					//The user chooses the wrong switch and is killed.
					//Their 'alive' flag is changed to false and the function returns
					std::cout << "You chose the wrong switch!!" << std::endl;
					Player.alive = false;
					return Player;
					break;

				case 2:
					//Let the user know what happened
					std::cout << "The light flickers then goes out" << std::endl;
					break;

				case 3:
					//Again tell the user what happened (suggest that the doll might stay away now
					std::cout << "A faint light comes on, you feel safer" << std::endl;
					break;

				case 4:
					//The user has chosen option 4 and so change the state of 'press' to false.
					//This ends the current while loop.
					std::cout << "You choose not to press any of the lights" << std::endl;
					CORR_press = false;
					break;

				default:
					//Make sure there is a default just in case
					std::cout << "You didn't enter a correct value" << std::endl;
				}
			}
			//Reset the press flag incase they want to check the lights again
			CORR_press = true;
			break;

		case 2:
			//If the user chooses an incorrect entry then make sure this loop is repeated.
			//This loop could have been included on the previous case but as there was already
			//a loop for the 'press' state there was no use including a second one
			do
			{
				//Reset incorrectEntry flag
				CORR_incorrectEntry = false;

				//Ask another question
				std::cout << "You notice a door at the top, as you go up the stairs two heads roll down" << std::endl;
				std::cout << "(1) Take the heads back to the top of the stairs" << std::endl;
				std::cout << "(2) Ignore the heads, try the door" << std::endl;

				//Read the answer in and act on it
				std::cin >> CORR_UsrDecision;

				switch (CORR_UsrDecision)
				{
				case 1:
					//In this case the user finds an Exit Key so change the state of the exit flag to true
					std::cout << "You put the heads down and notice a key must've fallen out of one of them" << std::endl;
					std::cout << "Maybe this will help you get out?" << std::endl;
					Player.K_exit = true;
					break;

				case 2:
					//This case ends in the player's death so change their alive state to false and return
					std::cout << "You try the door, it is locked" << std::endl;
					std::cout << "You turn around to notice the doll at the bottom of the stairs" << std::endl;
					Player.alive = false;
					return Player;
					break;

				default:
					//Catch any wrong numbers
					std::cout << "You didn't enter a correct value" << std::endl;
					CORR_incorrectEntry = true;
				}
			} while (CORR_incorrectEntry);

			break;

		case 3:
			//The player finds a teddy, it is suggested that it should be taken elsewhere.
			//Also update the player's teddy flag
			std::cout << "You see a teddy pinned to a wall with a knife. Surely this belongs elsewhere? (You pick it up)" << std::endl;
			Player.teddy = true;
			break;

		case 4:
			//In this case the user finds an Exit Key so as with before the exit flag is updated to true
			std::cout << "You inspect the door mat, there's something under it..." << std::endl;
			std::cout << "You've found a key! Maybe this will help you get out?" << std::endl;
			Player.K_exit = true;
			break;

		case 5:
			//Tell the user of their choice and then change the explore flag to true, ending the while loop
			std::cout << "You've chosen to explore somewhere else" << std::endl;
			CORR_explore = true;
			break;

		default:
			//In case the wrong value has been input. Similar to before a 'incorrectInput' flag could be
			//used here but this is not needed as the switch is already in a while loop
			std::cout << "You didn't enter a correct value" << std::endl;
		}
	}

	//After the user has decided to explore elsewhere (and come out of that while loop)
	//The function returns the structure containing the user's data
	return Player;
	
}

/***************************************************
This function contains all the decisions that happen
within the bathroom
***************************************************/
UserData F_Bathroom(UserData Player)
{
	int BATH_UsrDecision = 0;
	bool BATH_incorrectEntry = false;
	bool BATH_explore = false;

	while (!BATH_explore)
	{
		std::cout << "\n" << std::endl;

		std::cout << "There isn't much here" << std::endl;
		std::cout << "(1) Explore the bath" << std::endl;
		std::cout << "(2) Explore elsewhere" << std::endl;

		std::cin >> BATH_UsrDecision;

		switch (BATH_UsrDecision)
		{
		case 1:
			//The user finds a key so change the appropriate room key flag
			std::cout << "The bath is full of guts" << std::endl;
			std::cout << "You investigate further and find a key" << std::endl;
			Player.K_playroom = true;
			break;

		case 2:
			//The user want to explore elsewhere
			std::cout << "You've chosen to explore somewhere else" << std::endl;
			BATH_explore = true;
			break;

		default:
			std::cout << "You didn't enter a correct value" << std::endl;
		}
	}
	return Player;
}

/***************************************************
This function contains all the decisions that happen
within the kitchen
***************************************************/
UserData F_Kitchen(UserData Player)
{
	int KITC_UsrDecision = 0;
	bool KITC_incorrectEntry = false;
	bool KITC_press = true;
	bool KITC_explore = false;

	while (!KITC_explore)
	{
		std::cout << "\n" << std::endl;

		//Ask some questions to the user
		std::cout << "There's a hob, a hanging body and something that looks like a dog" << std::endl;
		std::cout << "Which would you like to explore further?" << std::endl;
		std::cout << "(1) The hob" << std::endl;
		std::cout << "(2) The body" << std::endl;
		std::cout << "(3) The dog" << std::endl;
		std::cout << "(4) Explore elsewhere" << std::endl;

		if (Player.basement == true)
		{
			std::cout << "(5) See what's under the trapdoor" << std::endl;
		}

		//Read in and act on their response
		std::cin >> KITC_UsrDecision;

		switch (KITC_UsrDecision)
		{
		case 1:
			//They chose to investigate the light switches so start a loop
			//so that they keep getting light switch options until they want
			//to do something else
			while (KITC_press)
			{
				std::cout << "There are four switches" << std::endl;
				std::cout << "(1) Choose switch 1" << std::endl;
				std::cout << "(2) Choose switch 2" << std::endl;
				std::cout << "(3) Choose switch 3" << std::endl;
				std::cout << "(4) Choose switch 4" << std::endl;
				std::cout << "(5) Don't press a switch" << std::endl;

				std::cin >> KITC_UsrDecision;

				switch (KITC_UsrDecision)
				{
				case 1:
					//The user finds a key so change the correct flag in their structure
					std::cout << "You turn the switch and the oven falls open" << std::endl;
					std::cout << "It looks like there is a key inside" << std::endl;
					Player.K_bathroom = true;
					break;

				case 2:
					//The player is killed, change the alive flag and return
					std::cout << "You've called the doll to you!!" << std::endl;
					Player.alive = false;
					return Player;
					break;

				case 3:
					std::cout << "You turn the switch, nothing happens" << std::endl;
					break;

				case 4:
					//The player has found the basement entrance so change the flag in
					//the structure
					std::cout << "You turn the switch and it opens a cupboard door" << std::endl;
					std::cout << "It looks like there is a trapdoor in the cupboard" << std::endl;
					Player.basement = true;
					break;

				case 5:
					//The player doesn't press a switch so end the while loop
					std::cout << "You choose not to press anything" << std::endl;
					KITC_press = false;
					break;

				default:
					//They didn't enter a correct value
					std::cout << "You didn't input a correct number" << std::endl;
				}
			}
			//Reset the press value in case the user wants to come back to the hob
			KITC_press = true;
			break;

		case 2:
			std::cout << "The body is old and decaying" << std::endl;
			break;

		case 3:
			std::cout << "You bring the dog a bone, it disappears, revealing a key" << std::endl;
			std::cout << "Maybe this will help you get out?" << std::endl;
			Player.K_exit = true;
			break;

		case 4:
			std::cout << "You've chosen to explore elsewhere" << std::endl;
			KITC_explore = true;
			break;

		case 5:
			std::cout << "You open the trapdoor and see a ladder into the basement, you climb down" << std::endl;
			Player = F_Basement(Player);

			do
			{
				KITC_incorrectEntry = false;
				std::cout << "\n" << std::endl;

				std::cout << "Do you want to barricade the trapdoor?" << std::endl;
				std::cout << "(1) Yes or (2) No" << std::endl;
				std::cin >> KITC_UsrDecision;

				switch (KITC_UsrDecision)
				{
				case 1:
					std::cout << "You barricade the trapdoor" << std::endl;
					Player.basement = false;
					break;

				case 2:
					break;

				default:
					std::cout << "That input was not valid" << std::endl;
				}
			} while (KITC_incorrectEntry == true);

			break;

		default:
			std::cout << "You didn't input a correct number" << std::endl;
		}
	}

	return Player;

}

/***************************************************
This function contains all the decisions that happen
within the playroom
***************************************************/
UserData F_Playroom(UserData Player)
{
	int PLAY_UsrDecision = 0;
	bool PLAY_explore = false;
	bool PLAY_incorrectEntry = false;

	while (!PLAY_explore)
	{
		std::cout << "\n" << std::endl;
		std::cout << "There is a musical box and a Humpty Dumpty toy" << std::endl;
		std::cout << "(1) Have a look at the musical box" << std::endl;
		std::cout << "(2) Check the toy" << std::endl;
		std::cout << "(3) Explore the room further" << std::endl;
		std::cout << "(4) Explore elsewhere" << std::endl;

		//If the player has found the teddy in the corridor give them an option 
		//to do something with it
		if (Player.teddy == true)
		{
			std::cout << "(5) Put the teddy you found earlier back" << std::endl;
		}

		std::cin >> PLAY_UsrDecision;

		switch (PLAY_UsrDecision)
		{
		case 1:
			std::cout << "The box opens and starts to play music" << std::endl;
			break;

		case 2:
			do
			{
				//Reset incorrectEntry flag
				PLAY_incorrectEntry = false;

				std::cout << "You pick up the toy" << std::endl;
				std::cout << "(1) Drop the toy" << std::endl;
				std::cout << "(2) Put it back" << std::endl;

				std::cin >> PLAY_UsrDecision;

				switch (PLAY_UsrDecision)
				{
				case 1:
					std::cout << "You drop the toy, it smashes and a key falls out" << std::endl;
					Player.K_kitchen = true;
					break;

				case 2:
					std::cout << "You put the toy back" << std::endl;
					break;

				default:
					std::cout << "You didn't put a correct number in" << std::endl;
					PLAY_incorrectEntry = true;

				}
			} while (PLAY_incorrectEntry);
			break;

		case 3:
			std::cout << "You explore the room and notice a key hidden in one of the paintings" << std::endl;
			std::cout << "Maybe this will help you get out?" << std::endl;
			Player.K_exit = true;
			break;

		case 4:
			std::cout << "You've chosen to explore elsewhere" << std::endl;
			PLAY_explore = true;
			break;

		case 5:
			std::cout << "You put the teddy back, it is replaced with a key" << std::endl;
			std::cout << "Maybe this will help you get out?" << std::endl;
			Player.teddy = false;
			Player.K_exit = true;
			break;

		default:
			std::cout << "You didn't make a valid decision" << std::endl;
		}
	}

	return Player;

}

/***************************************************
This function contains all the decisions that happen
within the basement
***************************************************/
UserData F_Basement(UserData Player)
{
	int UsrDecision = 0;
	bool explore = false;

	while (!explore)
	{
		std::cout << "\n" << std::endl;

		std::cout << "The basement is dark and you can't see much" << std::endl;
		std::cout << "(1) Climb back into the kitchen" << std::endl;
		std::cout << "(2) Go deeper into the basement" << std::endl;

		std::cin >> UsrDecision;

		switch (UsrDecision)
		{
		case 1:
			std::cout << "You climb back up the ladder" << std::endl;
			explore = true;
			break;

		case 2:
			std::cout << "There isn't much else in the basement" << std::endl;
			break;

		default:
			std::cout << "That isn't a valid input" << std::endl;
		}
	}

	return Player;
}

//-----------------------------------------------
//Write the main 'game' function
//-----------------------------------------------
void main()
{
	//Create some simple variables which can be used,
	//this includes a structure for the player's data
	//to get stored in
	UserData PersonPlaying;
	int MAIN_UserValue = 0;
	char MAIN_UserInput = 'A';
	bool MAIN_keepPlaying = true;
	bool MAIN_incorrectEntry = false;
	bool MAIN_explore = true;

	//Run an initial 'setup' function
	PersonPlaying = GameSetup(PersonPlaying);

	if (PersonPlaying.K_exit == true)
	{
		MAIN_explore = false;
	}

	//While the player wants to keep playing, keep looping
	while (MAIN_keepPlaying)
	{
		//Insert some whitespace
		std::cout << "\n" << std::endl;

		//If the player is still alive give them some options
		if (PersonPlaying.alive)
		{
			//Let the player know which rooms they can visit
			//Using conditional print statements
			std::cout << "Rooms currently available:" << std::endl;
			std::cout << "(C) Corridor" << std::endl;

			if (PersonPlaying.K_kitchen == true)
			{
				std::cout << "(K) Kitchen" << std::endl;
			}

			if (PersonPlaying.K_bathroom == true)
			{
				std::cout << "(B) Bathroom" << std::endl;
			}

			if (PersonPlaying.K_playroom == true)
			{
				std::cout << "(P) Playroom" << std::endl;
			}

			//If the user has not previously chosen to explore but has an exit key
			//then print the following
			if (!MAIN_explore)
			{
				do
				{
					//Reset values an insert whitespace
					MAIN_incorrectEntry = false;
					std::cout << "\n" << std::endl;

					//The player doesn't neccesarily want to use the key, give them the option
					//to not use it
					std::cout << "You also found an exit key, would you like to use it?" << std::endl;
					std::cout << "(1) Use it" << std::endl;
					std::cout << "(2) Explore elswhere" << std::endl;
					std::cin >> MAIN_UserValue;

					switch (MAIN_UserValue)
					{
					case 1:
						std::cout << "\n" << std::endl;

						std::cout << "You use the key on the front door and you escape!" << std::endl;
						MAIN_keepPlaying = false;
						break;

					case 2:
						//If the user doesn't use it makes sure that for this loop they won't be 
						//asked again (by changing the explore flag to true
						std::cout << "You've chosen to explore somewhere else" << std::endl;
						MAIN_explore = true;
						break;

					default:
						std::cout << "That input wasn't valid" << std::endl;
						MAIN_incorrectEntry = true;

					}
				} while (MAIN_incorrectEntry);
			}

			else
			{
				do
				{
					//Reset value of the entry flag
					MAIN_incorrectEntry = false;

					//Take in the user input and act upon it
					std::cin >> MAIN_UserInput;

					switch (MAIN_UserInput)
					{
					case 'C':
						PersonPlaying = F_Corridor(PersonPlaying);
						break;

					case 'K':
						PersonPlaying = F_Kitchen(PersonPlaying);
						break;

					case 'B':
						PersonPlaying = F_Bathroom(PersonPlaying);
						break;

					case 'P':
						PersonPlaying = F_Playroom(PersonPlaying);
						break;

					default:
						std::cout << "That option is not valid" << std::endl;
						MAIN_incorrectEntry = true;
					}
				} while (MAIN_incorrectEntry == true);

				//At this point the user will have just finished exploring an area of the house
				//and so reset the explore flag to false for the next loop
				MAIN_explore = false;

				//If, at this point, the player is still alive, ask them if they want to continue
				if (PersonPlaying.alive == true)
				{
					do
					{
						MAIN_incorrectEntry = false;
						std::cout << "\n" << std::endl;

						std::cout << "Do you want to keep playing?" << std::endl;
						std::cout << "(1) Yes" << std::endl;
						std::cout << "(2) No" << std::endl;

						std::cin >> MAIN_UserValue;

						switch (MAIN_UserValue)
						{
						case 1:
							break;

						case 2:
							std::cout << "Thanks for playing" << std::endl;
							MAIN_keepPlaying = false;
							break;

						default:
							std::cout << "That wasn't a correct input" << std::endl;
							MAIN_incorrectEntry = true;
						}
					} while (MAIN_incorrectEntry);
				}
			}
		}

		//The player isn't alive any more, tell them that their game is over
		else
		{
			std::cout << "You've been killed!" << std::endl;
			std::cout << "-------- GAME OVER --------" << std::endl;
			MAIN_keepPlaying = false;
		}
	}

	return;

}