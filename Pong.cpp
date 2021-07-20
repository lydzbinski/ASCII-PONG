/*
--------------------------------------------------------------------------------
                                PONG GAME           
--------------------------------------------------------------------------------
A classic game where two paddles on eithe side of the board moves up and down to
prevent a moving ball from passing behind them. 

CREATED BY:     Brandon Lydzbinski
STARTED:        2021-05-18
COMPLETED:      2021-05-20
--------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
                                LIBARIES INCLUDED
--------------------------------------------------------------------------------
*/
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

/*
--------------------------------------------------------------------------------
                                    VARIABLES
--------------------------------------------------------------------------------
*/
int PlayerNumberSelection;
int PlayerOnePaddle = 5;
int PlayerTwoPaddle = 5;
int BallxPosition = 24;
int BallyPosition = 5;
int BallxDirection = rand() % 2 + 1; 
int BallyDirection = rand() % 2 + 1; 
char PlayerOneDirection;
char PlayerTwoDirection;
int PlayerOneScore = 0;
int PlayerTwoScore = 0;
int BallSpeedSelection = 1;
int BallSpeedCount = 0;
int PlayerDifficultitySelection = 0;

/* 
--------------------------------------------------------------------------------
                                    FUNCTIONS
--------------------------------------------------------------------------------
*/
void PrintIntroduction(){
    /* Print welcome message to terminal.
       Purpose is to provide feedback that the program is running.
    
       PrintIntroduction() -> void 
    */
    std::cout << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "              WELCOME TO ASCII PONG" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl << std::endl;
    std::cout << "??? GAME RULES ???" << std::endl;
    std::cout << std::endl;
    std::cout << "- First to 5 Points Wins..." << std::endl;
    std::cout << "- Player One Controls -> W = UP & S = DOWN" << std::endl;
    std::cout << "- Player Two Controls -> O = UP & L = DOWN" << std::endl << std::endl;
    
    std::cout << "<<<< ENTER BALL SPEED >>>>"<< std::endl << std::endl;
    std::cout << "1 = Fast    2 = Medium    3 = Slow    4 = Very Slow    0 = INSANE"<< std::endl;
    std::cout << "... ";
    std::cin >> BallSpeedSelection;
    std::cout << std::endl << std::endl;
    
    std::cout << "<<<< ENTER NUMBER OF PLAYERS >>>>"<< std::endl << std::endl;
    std::cout << "1 = 1 Player    2 = 2 Players"<< std::endl;
    std::cout << "... ";
    std::cin >> PlayerNumberSelection;
    std::cout << std::endl << std::endl;

    if(PlayerNumberSelection == 1){
        std::cout << "//// SELECT YOUR DIFFICULTY ////"<< std::endl << std::endl;
        std::cout << "1 = Normal    2 = Hard"<< std::endl;
        std::cout << "... ";
        std::cin >> PlayerDifficultitySelection;
    }

    std::cout << "GAME START IN" << std::endl;
    Sleep(1000);
    std::cout << "3" << std::endl;
    Sleep(1000);
    std::cout << "2" << std::endl;
    Sleep(1000);
    std::cout << "1" << std::endl;
    Sleep(1000);
    std::cout << "! GO !" << std::endl;
    Sleep(1000);
}

void PrintTop(){
    /* Print the string illustration of the top and bottom rows of the game board.
       PrintTop() -> void
    */
    std::cout << "--------------------------------------------------" << std::endl;
}

void PrintPlayerOnePaddle(){
    /* Print the string illustration for player one paddle.
       PrintPlayerOnePaddle() -> void
    */
    std::cout << "|" << std::endl;
}
void PrintPlayerTwoPaddle(){
    /* Print the string illustration for player two paddles.
       PrintPlayerTwoPaddle() -> void 
    */
    std::cout << "|" << std::endl;
}
void PrintBall(int BallColumnNumber){
    /* Print the illustration of a single row, given the current column/x position of the ball.
       PrintBall(int) -> void 
    */
    for (int row = 1; row <= 46; row++){
        if(row == BallColumnNumber){
            std::cout << "0";
        }
        else{
            std::cout << " ";
        }
    }
}
void PrintBoard(int PlayerOnePaddleColumn, int BallColumn, int BallRow, int PlayerTwoPaddleColumn){
    /*Prints gameboard to terminal 
      Takes 4 inputs; 
        1: Player One Paddles current row location (y coordinate)
        2: Balls currrent column location (x coordinate)
        3: Balls current row location (y coordinate) 
        4: Player Twos Paddle current row location (y coordinate)
      PrintBall(int, int, int, int) -> void 
    */
    PrintTop();
    for (int BoardRowNumber = 1; BoardRowNumber <= 10; BoardRowNumber++){
        std::cout << "-";
        if(BoardRowNumber == PlayerOnePaddleColumn){
            std::cout << "|";
        }
        else{
            std::cout << " ";
        }
        if(BoardRowNumber == BallRow){
            PrintBall(BallColumn);
        }
        else{
            std::cout << "                                              ";
        }
        if(BoardRowNumber == PlayerTwoPaddleColumn){
            std::cout << "|";
        }
        else{
            std::cout << " ";
        }
        std::cout << "-\n";
    }
    PrintTop();
}

void AdvanceBallX(int BallDirectionStateX){
    /*Changes the column location of the ball (x axis) 
      Either foward or backward by one, depending on the direction state.
      State = 1; moves ball foward, State = 2; moves ball backwards.
      AdvanceBallX(int) -> void 
    */
    if(BallDirectionStateX == 1){
        BallxPosition++;
    }
    else if(BallDirectionStateX == 2){
        BallxPosition--;
    }
}
void AdvanceBallY(int BallDirectionStateY){
    /*Changes the row location of the ball (y axis) 
      Either up or down by one, depending on the direction state.
      State = 1; moves ball down, State = 2; moves ball up.
      AdvanceBallY(int) -> void
    */
    if(BallDirectionStateY == 1){
        BallyPosition++;
    }
    else if(BallDirectionStateY == 2){
        BallyPosition--;
    }
}
void AdvanceBallXY(){
    /*Moves the ball in both the x and y directions.  
      AdvanceBallXY() -> void 
    */
    if(BallSpeedCount == BallSpeedSelection){
        AdvanceBallX(BallxDirection);
        AdvanceBallY(BallyDirection);
        BallSpeedCount = 0;
    }
    else{
        BallSpeedCount++;
    }
}

void MovePaddles(){
    /*Updates the paddle position according to the players input. 
      When an input is waiting in the keyboard buffer, the function loads it into the Paddle directions for players one and two. 
      MovePaddels() -> void 
    */
        if(kbhit()){
            PlayerOneDirection = _getch(); 
            PlayerTwoDirection = PlayerOneDirection;
        }
        if(PlayerOneDirection == 'w'){
            PlayerOnePaddle--;
            PlayerOneDirection = 'a';
        }
        else if(PlayerOneDirection == 's'){
            PlayerOnePaddle++;
            PlayerOneDirection = 'a';
        }
        if(PlayerTwoDirection == 'o'){
            PlayerTwoPaddle--;
            PlayerTwoDirection = 'a';
        }
        else if(PlayerTwoDirection == 'l'){
            PlayerTwoPaddle++;
            PlayerTwoDirection = 'a';
        }
}

void PrintCongrats(){
    /*Print Congratulations to terminal.
      PrintCongrats() -> void 
    */
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "                 CONGRATULATIONS" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl << std::endl;
}

void UpdateScore(){
    /*Updates players scores when a point is scored and resets the ball to the start position.
      If a Player or the Computer has won, prints to terminal. 
      UpdateScore() -> void 
    */
    if(BallxPosition < 0){
        PlayerTwoScore++;
        if(PlayerTwoScore < 5){
            BallxPosition = 24;
            BallxDirection = rand() % 2 + 1;
        }
        else{
            if(PlayerNumberSelection == 2){
                PrintCongrats();
                std::cout << "Player Two WINS" << std::endl;
                std::cout << "..." << std::endl;
                Sleep(2000);
            }
            else if(PlayerNumberSelection == 1){
                PrintCongrats();
                std::cout << "The Computer WINS" << std::endl;
                std::cout << "..." << std::endl;
                Sleep(2000);
            }
        }
    }
    else if (BallxPosition > 48){
        PlayerOneScore++;
        if(PlayerOneScore < 5){
            BallxPosition = 25;
            BallxDirection = rand() % 2 + 1;
        }
        else{
            PrintCongrats();
            std::cout << "Player One WINS" << std::endl;
            std::cout << "..." << std::endl;
            Sleep(2000);
        }
    }
}

void PrintScore(){
    /*Prints the current score of the game to the terminal.  
      MovePaddels() -> void
    */
    std::cout << "                      " << PlayerOneScore << " : " << PlayerTwoScore << "                      ";
}

void ReboundBall(){
    /*Determines if the ball has touhced a paddle or the top/bottom wall.
      If so, sets the direction of the ball in the opposite direction.  
      Reboundball() -> void
    */
    if(BallxPosition == 46 && PlayerTwoPaddle == BallyPosition){
        BallxDirection = 2;
    }
    else if(BallxPosition == 1 && PlayerOnePaddle == BallyPosition){
        BallxDirection = 1;
    }
    if(BallyPosition == 10){
        BallyDirection = 2;
    }
    else if(BallyPosition == 1){
        BallyDirection = 1;
    }
}

void MovePlayerTwoPaddle(int DifficultySelection){
    /*Moves player two's paddle according to the difficulty selection.
      Easy Mode 50% chance to suceed.
      Hard Mode 85% chance to suceed.  
      MovePlayerTwoPaddle(int) -> void
    */
    int AiReactionTime = rand() % 2 + 1; 
    if(DifficultySelection == 1){
        if(AiReactionTime == 2){
            if(BallxDirection == 1 && BallxPosition >= 24){
                if(PlayerTwoPaddle < BallyPosition){
                    PlayerTwoPaddle++;
                }
                else if(PlayerTwoPaddle > BallyPosition){
                    PlayerTwoPaddle --;
                }
            }
        }
    }
    else{
        AiReactionTime = rand() % 100 + 1;
        if(AiReactionTime <= 85){
            if(BallxDirection == 1 && BallxPosition >= 35){
                if(PlayerTwoPaddle < BallyPosition){
                    PlayerTwoPaddle++;
                }
                else if(PlayerTwoPaddle > BallyPosition){
                    PlayerTwoPaddle --;
                }
            }    
        }
    }
}
/* 
--------------------------------------------------------------------------------
                            MAIN FUNCTION OF THE PROGRAME
--------------------------------------------------------------------------------
*/
int main(){
    PrintIntroduction();
    while(BallxPosition <= 48 && BallxPosition >= 0){
        PrintBoard(PlayerOnePaddle, BallxPosition, BallyPosition, PlayerTwoPaddle);
        PrintScore();
        Sleep(32);

        ReboundBall();
        AdvanceBallXY();
        
        system("CLS");
        MovePaddles();
        if(PlayerNumberSelection == 1){
            MovePlayerTwoPaddle(PlayerDifficultitySelection);
        }
        UpdateScore();
    }
    return 0;
}