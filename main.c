
/* ---------------------------------------------
Prog 2: Wumpus
(bats, arrow, and all arrays are dynamic)

Author: Pratik Patel

---------------------------------------------
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // for srand
#include <time.h>

// a struct who stores a values of each character in this game
struct HuntWumpus {
  int player, wumpus, pit1, pit2, bats1, bats2, arrow, numShot;
};

//--------------------------------------------------------------------------------
// displaycave() function prompt the design of cave
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
} // end of displaycave()

//--------------------------------------------------------------------------------
// displayInstructions() function propt the instruction of how to play a game
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
} // end of displayInstructions()

//--------------------------------------------------------------------------------
// hazard() function is checking whether the player is anywhere near the wumpus
// or pits. If so, then it displays associated message as a hazar. The function
// accepts a struct, a pointer, and 2D array as parameters, return the location
// of the player.
void hazards(struct HuntWumpus *checkHarzards, int **adjArr) {

  int playerIndex = checkHarzards->player - 1;
  int room1, room2, room3;
  // assigning each three adjacent rooms near the player's room
  room1 = adjArr[playerIndex][0];
  room2 = adjArr[playerIndex][1];
  room3 = adjArr[playerIndex][2];
  // show player's location no matter what user input is
  printf("You are in room %d. ", checkHarzards->player);
  // if the player is anywhere near a wumpus or the player is in a same room as
  // wumpus, then user receives a message as a hazard
  if (checkHarzards->wumpus == room1 || checkHarzards->wumpus == room2 ||
      checkHarzards->wumpus == room3 ||
      checkHarzards->wumpus == checkHarzards->player) {
    printf("You smell a stench. ");
  }
  // if the player is anywhere near pits, then user receives a message as a
  // hazard
  if (checkHarzards->pit1 == room1 || checkHarzards->pit2 == room1 ||
      checkHarzards->pit1 == room2 || checkHarzards->pit2 == room2 ||
      checkHarzards->pit1 == room3 || checkHarzards->pit2 == room3) {
    printf("You feel a draft. ");
  }
  // if the player is anywhere near bats, then user receives a message as a
  // hazard
  if (checkHarzards->bats1 == room1 || checkHarzards->bats1 == room2 ||
      checkHarzards->bats1 == room3 || checkHarzards->bats2 == room1 ||
      checkHarzards->bats2 == room2 || checkHarzards->bats2 == room3) {
    printf("You hear rustling of bat wings. ");
  }

} // end of hazards()

//--------------------------------------------------------------------------------
// playerMove() function is checking if the player moving into a room has a
// wumpus or pits. If it has wumpus and the number of room is odd then player
// CAN slips away. If it has pits, then player instantaneously die.
void playerMove(struct HuntWumpus *movePlayer, int **adjArr, int move,
                int *count) {

  // if the player is in even number of room with the wumpus then
  // it display a below message.
  if ((move % 2 == 1) && (move == movePlayer->wumpus)) {
    printf("You hear a slithering sound, as the Wumpus slips away. \nWhew, "
           "that was close! \n");
  }
  // if the wumpus is in odd room with the player then the game is over.
  if ((move % 2 == 0) && (move == movePlayer->wumpus)) {
    printf("You briefly feel a slimy tentacled arm as your neck is snapped. "
           "\nIt is over.\n");
    printf("\nExiting Program ...");
    exit(0);
  }
  // Message when the player dies by falling into a pit.
  if (move == movePlayer->pit1 || move == movePlayer->pit2) {
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n\nExiting Program ...");
    exit(0);
  }
  // if player enters a room where any bats present, player flew into some
  // another room by bats
  if (move == movePlayer->bats1 || move == movePlayer->bats2) {
    movePlayer->player = 2;
    printf("Woah... you're flying!\n");
    printf("You've just been transported by bats to room %d.\n",
           movePlayer->player);
    movePlayer->bats1 = rand() % 20 + 1;
    *count = *count + 1;
  }

  // if-else statement to see if the move a player made is valid/invalid.
  else if (move == adjArr[movePlayer->player - 1][0] ||
           move == adjArr[movePlayer->player - 1][1] ||
           move == adjArr[movePlayer->player - 1][2]) {
    movePlayer->player = move;
    *count = *count + 1;
  } else {
    printf("Invalid move.  Please retry. \n");
  }
} // end of playerMove

//--------------------------------------------------------------------------------
// shootArrows() accepts a struct, dynamically allocated array, and two integer
// variables to keep track of some counts, function does not return anything,
// concept is to chech if the arrows that player is shooting is killing the
// wumpus or kills itself.
void shootArrows(struct HuntWumpus *checkArrow, int **adjArr, int *counter,
                 int *countArrow) {

  int playerIndex, adjRoom1, adjRoom2, adjRoom3;
  // checking the first arrow is adjacent to player's room or not
  if (*counter == 0) {
    playerIndex = checkArrow->player - 1;
    *counter = *counter + 1;
  } else {
    playerIndex = checkArrow->arrow - 1;
  }
  // assigning each three adjacent rooms near the player's room
  adjRoom1 = adjArr[playerIndex][0];
  adjRoom2 = adjArr[playerIndex][1];
  adjRoom3 = adjArr[playerIndex][2];

  // as long as the player's arrow goes through adjacent rooms, checking if any
  // of those adjacent rooms has wumpus or player itself
  if (checkArrow->numShot == adjRoom1 || checkArrow->numShot == adjRoom2 ||
      checkArrow->numShot == adjRoom3) {
    // player shot an arrow within the same room, player instantly die, Game
    // Over
    if (checkArrow->numShot == checkArrow->player) {
      printf("You just shot yourself.\nMaybe Darwin was right. You're dead.\n");
      printf("\nExiting Program ...");
      exit(0);
    }
    // player shot an arrow in a room where wumpus is located, player won
    if (checkArrow->numShot == checkArrow->wumpus) {
      printf("Wumpus has just been pierced by your deadly arrow!\n");
      printf("Congratulations on your victory, you awesome hunter you.\n");
      printf("\nExiting Program ...");
      exit(0);
    }
    checkArrow->arrow = checkArrow->numShot;
  }

  // if shotted arrows are not adjacent, notify player a room number, and
  // check if a player shot an arrow with player in the same room, if so, player
  // die, Game Over
  else {
    printf("Room %d is not adjacent. Arrow ricochets...\n",
           checkArrow->numShot);
    checkArrow->arrow = adjRoom1;
    // if the player is in the same room as it shot arrow in, player die, Game
    // Over
    if (checkArrow->player == checkArrow->arrow) {
      printf("You just shot yourself, and are dying.\nIt didn't take long, "
             "you're dead.\n");
      printf("\nExiting Program ...");
      exit(0);
    }
    if (checkArrow->numShot == 5) {
      printf("Your arrow ricochet killed the Wumpus, you lucky "
             "dog!\nAccidental victory, but still you win!\n");
      printf("\nExiting Program ...");
      exit(0);
    }
  }
  // reduce the number of arrows available each time player shoot an arrow
  *countArrow = *countArrow - 1;

} // end of shootArrows()

//--------------------------------------------------------------------------------
int main(void) {
  srand(1);
  // variables
  char userMove = ' ', upperCapsOfUserMove;
  int move, userGuess, numArrow, countArrow = 1, count = 1, counter = 0;

  // dynamically allocating an array
  int **adjRooms = (int **)malloc(20 * sizeof(int *));
  for (int i = 0; i < 20; i++) {
    adjRooms[i] = (int *)malloc(3 * sizeof(int));
  }
  // assigning adjacent rooms to dynamically allocated array
  adjRooms[0][0] = 2, adjRooms[0][1] = 5, adjRooms[0][2] = 8;
  adjRooms[1][0] = 1, adjRooms[1][1] = 3, adjRooms[1][2] = 10;
  adjRooms[2][0] = 2, adjRooms[2][1] = 4, adjRooms[2][2] = 12;
  adjRooms[3][0] = 3, adjRooms[3][1] = 5, adjRooms[3][2] = 14;
  adjRooms[4][0] = 1, adjRooms[4][1] = 4, adjRooms[4][2] = 6;
  adjRooms[5][0] = 5, adjRooms[5][1] = 7, adjRooms[5][2] = 15;
  adjRooms[6][0] = 6, adjRooms[6][1] = 8, adjRooms[6][2] = 17;
  adjRooms[7][0] = 1, adjRooms[7][1] = 7, adjRooms[7][2] = 9;
  adjRooms[8][0] = 8, adjRooms[8][1] = 10, adjRooms[8][2] = 18;
  adjRooms[9][0] = 2, adjRooms[9][1] = 9, adjRooms[9][2] = 11;

  adjRooms[10][0] = 10, adjRooms[10][1] = 12, adjRooms[10][2] = 19;
  adjRooms[11][0] = 3, adjRooms[11][1] = 11, adjRooms[11][2] = 13;
  adjRooms[12][0] = 12, adjRooms[12][1] = 14, adjRooms[12][2] = 20;
  adjRooms[13][0] = 4, adjRooms[13][1] = 13, adjRooms[13][2] = 15;
  adjRooms[14][0] = 6, adjRooms[14][1] = 14, adjRooms[14][2] = 16;
  adjRooms[15][0] = 15, adjRooms[15][1] = 17, adjRooms[15][2] = 20;
  adjRooms[16][0] = 7, adjRooms[16][1] = 16, adjRooms[16][2] = 18;
  adjRooms[17][0] = 9, adjRooms[17][1] = 17, adjRooms[17][2] = 19;
  adjRooms[18][0] = 11, adjRooms[18][1] = 18, adjRooms[18][2] = 20;
  adjRooms[19][0] = 13, adjRooms[19][1] = 16, adjRooms[19][2] = 19;

  // declaring a struct
  struct HuntWumpus huntWumpus;
  // generating random variables and assigning into following order: pit1, pit2,
  // wumpus, player
  huntWumpus.player = rand() % 20 + 1;
  huntWumpus.wumpus = rand() % 20 + 1;
  huntWumpus.pit1 = rand() % 20 + 1;
  huntWumpus.pit2 = rand() % 20 + 1;
  huntWumpus.bats1 = rand() % 20 + 1;
  huntWumpus.bats2 = rand() % 20 + 1;
  huntWumpus.arrow = rand() % 20 + 1;

  while (1) {
    // passing a struct and dynamically allocated array to see if the player is
    // adjacent to any pits or bats or a wumpus
    hazards(&huntWumpus, adjRooms);
    // prompt for user to enter their move
    printf("\n\n%d. Enter your move (or 'D' for directions): ", count);
    scanf(" %c", &userMove);
    // turn any user input char into upper case
    upperCapsOfUserMove = toupper(userMove);

    switch (upperCapsOfUserMove) {

    // Prompt for user when they choose to reset
    case 'R':
      printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, "
             "bats1, bats2, and arrow: \n\n");
      scanf("%d %d %d %d %d %d %d", &huntWumpus.player, &huntWumpus.wumpus,
            &huntWumpus.pit1, &huntWumpus.pit2, &huntWumpus.bats1,
            &huntWumpus.bats2, &huntWumpus.arrow);
      break;

    // prompt for user when they choose to cheat and see all of the locations
    case 'C':
      printf(
          "Cheating! Game elements are in the following rooms: \n"
          "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow \n%4d %5d %6d %5d %5d %5d",
          huntWumpus.player, huntWumpus.wumpus, huntWumpus.pit1,
          huntWumpus.pit2, huntWumpus.bats1, huntWumpus.bats2);
      if (huntWumpus.player == 20) {
        printf("%4d\n\n", -1);
      } else {
        printf("%4d\n\n", huntWumpus.arrow);
      }
      break;

    // prompt for user when they choose to see directions of the game
    case 'D':
      displayCave();
      displayInstructions();
      break;

    // prompt for user when they choose to see display the cave
    case 'P':
      displayCave();
      break;

    // Prompt for guess of where Wumpus room is
    case 'G':
      printf("Enter room (1..20) you think Wumpus is in: ");
      scanf("%d", &userGuess);
      // Both possible messages after the user guesses where the Wumpus is, for
      // a win or loss.
      if (userGuess == huntWumpus.wumpus) {
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

    // let player shoot arrows and sorry messages, if player doesn't have an
    // arrow to shoot
    case 'S':
      count++;
      if (countArrow > 0) {
        printf("Enter the number of rooms (1..3) into which you want to shoot, "
               "followed by the rooms themselves: ");
        scanf("%d", &numArrow);
        // number of time checks the possibility if player hitting a wumpus or
        // itself
        for (int i = 0; i < numArrow; i++) {
          scanf("%d", &huntWumpus.numShot);
          shootArrows(&huntWumpus, adjRooms, &counter, &countArrow);
        }
        huntWumpus.wumpus = adjRooms[huntWumpus.wumpus - 1][0];
      }
      // if no arrows are avilable, sorry message pop up and say look out for an
      // arrow somewhere
      else {
        printf("Sorry, you can't shoot an arrow you don't have. Go find it.\n");
      }
      break;

    // prompt for user to move the player and play a game
    case 'M':
      scanf("%d", &move);
      // as soon as player walks into a room where an arrow is present, congrats
      // a player
      if (move == huntWumpus.arrow) {
        printf(
            "Congratulations, you found the arrow and can once again shoot.\n");
        countArrow = countArrow + 1;
      }
      playerMove(&huntWumpus, adjRooms, move, &count);
      break;

    // by default: message for invalid move
    default:
      printf("Invalid move.  Please retry. \n");
      break;

    } // end of switch() statement

  } // end of while() loop

  // freeing dynamically allocated array (clearing up...)
  free(adjRooms);

  return 0;
} // end of main(void)
