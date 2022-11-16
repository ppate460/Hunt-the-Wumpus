/* main.cpp
    Program 1: Wumpus, version 1 (fixed size array)
    Description:

    Course: CS 211, Fall 2022.
    Author: Prof. Reed
    System: Repl.it and VSCode

    Date: Due on Sep. 10th, 2022
    Student Name: Pratik Patel
    UIN: 669224629
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // for srand
#include <time.h>

//--------------------------------------------------------------------------------
// function specifically desined for GitHub changes
void ppate460_ashah297() { printf("Inside Github and making changes"); }

//--------------------------------------------------------------------------------

struct HuntWumpus {
  int wumpus, player, pit1, pit2;
};

//--------------------------------------------------------------------------------
void displayCave() {
  printf("\n");
  printf("       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}

//--------------------------------------------------------------------------------
void displayInstructions() {
  printf(
      "Hunt the Wumpus:                                             \n"
      "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
      "room has 3 tunnels leading to other rooms.                   \n"
      "                                                             \n"
      "Hazards:                                                     \n"
      "1. Two rooms have bottomless pits in them.  If you go there you fall "
      "and die.   \n"
      "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
      "Usually he is \n"
      "   asleep. He will wake up if you enter his room. When you move into "
      "the Wumpus'\n"
      "   room, then he wakes and moves if he is in an odd-numbered room, "
      "but stays    \n"
      "   still otherwise.  After that, if he is in your room, he snaps "
      "your neck and  \n"
      "   you die!                                                          "
      "           \n"
      "                                                                     "
      "           \n"
      "Moves:                                                               "
      "           \n"
      "On each move you can do the following, where input can be upper or "
      "lower-case:  \n"
      "1. Move into an adjacent room.  To move enter 'M' followed by a "
      "space and       \n"
      "   then a room number.                                               "
      "           \n"
      "2. Enter 'R' to reset the person and hazard locations, useful for "
      "testing.      \n"
      "3. Enter 'C' to cheat and display current board positions.           "
      "           \n"
      "4. Enter 'D' to display this set of instructions.                    "
      "           \n"
      "5. Enter 'P' to print the maze room layout.                          "
      "           \n"
      "6. Enter 'G' to guess which room Wumpus is in, to win or lose the game!"
      "           \n"
      "7. Enter 'X' to exit the game.                                       "
      "           \n"
      "                                                                     "
      "           \n"
      "Good luck!                                                           "
      "           \n"
      " \n\n");
} // end displayInstructions()

//--------------------------------------------------------------------------------
void hazards(struct HuntWumpus *checkHarzards, int adjArr[20][3]) {

  int playerIndex = checkHarzards->player - 1;

  // checking adjacent rooms...
  int room1, room2, room3;
  room1 = adjArr[playerIndex][0];
  room2 = adjArr[playerIndex][1];
  room3 = adjArr[playerIndex][2];

  printf("You are in room %d. ", checkHarzards->player);

  if (checkHarzards->wumpus == room1 || checkHarzards->wumpus == room2 ||
      checkHarzards->wumpus == room3 ||
      checkHarzards->wumpus == checkHarzards->player) {
    printf("You smell a stench. ");
  }

  if (checkHarzards->pit1 == room1 || checkHarzards->pit1 == room2 ||
      checkHarzards->pit1 == room3 || checkHarzards->pit2 == room1 ||
      checkHarzards->pit2 == room2 || checkHarzards->pit2 == room3) {
    printf("You feel a draft. ");
  }
};

//--------------------------------------------------------------------------------
void playermove(struct HuntWumpus *movePlayer, int adjArr[20][3], int move,
                int *count) {

  if ((move % 2 == 0) && (move == movePlayer->wumpus)) {
    printf("You briefly feel a slimy tentacled arm as your neck is snapped. "
           "\nIt is over.\n");
    printf("\nExiting Program ...");
    exit(0);
  }
  if ((move % 2 == 1) && (move == movePlayer->wumpus)) {
    printf("You hear a slithering sound, as the Wumpus slips away. \nWhew, "
           "that was close! \n");
  }

  // Message when the player dies by falling into a pit
  if (move == movePlayer->pit1) {
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n");
    printf("\nExiting Program ...");
    exit(0);
  }

  if (move == adjArr[movePlayer->player - 1][0] ||
      move == adjArr[movePlayer->player - 1][1] ||
      move == adjArr[movePlayer->player - 1][2]) {
    movePlayer->player = move;
    *count = *count + 1;
  } else {
    printf("Invalid move.  Please retry. \n");
  }
}

//--------------------------------------------------------------------------------
int main(void) {

  // for GitHub
  ppate460_ashah297();

  char userMove = ' ';
  char upperCapsMove;
  int move;
  int guessMove;
  int count = 1;

  int adjRooms[20][3] = {{2, 5, 8},    {1, 3, 10},  {2, 4, 12},   {3, 5, 14},
                         {1, 4, 6},    {5, 7, 15},  {6, 8, 17},   {1, 7, 9},
                         {8, 10, 18},  {2, 9, 11},  {10, 12, 19}, {3, 11, 13},
                         {12, 14, 20}, {4, 13, 15}, {6, 14, 16},  {15, 17, 20},
                         {7, 16, 18},  {9, 17, 19}, {11, 18, 20}, {13, 16, 19}};

  struct HuntWumpus huntWumpus;
  huntWumpus.pit1 = rand() % 20 + 1;
  huntWumpus.pit2 = rand() % 20 + 1;
  huntWumpus.wumpus = rand() % 20 + 1;
  huntWumpus.player = rand() % 20 + 1;

  while (1) {

    hazards(&huntWumpus, adjRooms);
    printf("\n\n");
    printf("%d. Enter your move (or 'D' for directions): ",
           count); // prompt for user to enter their move
    scanf(" %c", &userMove);
    upperCapsMove = toupper(userMove);

    switch (upperCapsMove) {

    // Prompt for user when they choose to reset
    case 'R':
      printf("Enter the room locations (1..20) for player, wumpus, pit1, and "
             "pit2: \n");
      scanf("%d %d %d %d", &huntWumpus.player, &huntWumpus.wumpus,
            &huntWumpus.pit1, &huntWumpus.pit2);
      printf("\n");
      break;

    case 'C':
      printf("Cheating! Game elements are in the following rooms: \n"
             "Player Wumpus Pit1 Pit2  \n%4d %7d %5d %5d \n\n",
             huntWumpus.player, huntWumpus.wumpus, huntWumpus.pit1,
             huntWumpus.pit2);
      break;

    case 'D':
      displayCave();
      displayInstructions();
      break;

    case 'P':
      displayCave();
      break;

    // Prompt for guess of where Wumpus room is
    case 'G':
      printf("Enter room (1..20) you think Wumpus is in: ");
      scanf("%d", &guessMove);
      // Both possible messages after the user guesses where the Wumpus is, for
      // a win or loss.
      if (guessMove == huntWumpus.wumpus) {
        printf("You won!\n");
      } else {
        printf("You lost.\n");
      }
      printf("\nExiting Program ...\n");
      exit(0);
      break;

    // Message that prints at the end of the program
    case 'X':
      printf("\nExiting Program ...\n");
      exit(0);
      break;

    case 'M':
      scanf("%d", &move);
      playermove(&huntWumpus, adjRooms, move, &count);
      break;

    // message for invalid move
    default:
      printf("Invalid move.  Please retry. \n");
      break;

    } // end of switch statement

  } // end of while()

  return 0;
} // end of main(void)
