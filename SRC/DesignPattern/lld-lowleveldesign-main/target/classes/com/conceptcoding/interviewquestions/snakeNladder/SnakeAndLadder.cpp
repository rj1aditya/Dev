#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

// Jump class - represents both snakes and ladders
class Jump
{
public:
    int start;
    int end;

    Jump() : start(0), end(0) {}
    Jump(int s, int e) : start(s), end(e) {}
};

// Cell class - represents each cell on the board
class Cell
{
public:
    Jump *jump;

    Cell() : jump(nullptr) {}

    ~Cell()
    {
        if (jump != nullptr)
        {
            delete jump;
        }
    }
};

// Player class
class Player
{
public:
    string id;
    int currentPosition;

    Player(string playerId, int position) : id(playerId), currentPosition(position) {}
};

// Dice class
class Dice
{
private:
    int diceCount;
    int min;
    int max;
    mt19937 generator;

public:
    Dice(int count) : diceCount(count), min(1), max(6)
    {
        generator.seed(time(0));
    }

    int rollDice()
    {
        int totalSum = 0;
        int diceUsed = 0;

        uniform_int_distribution<int> distribution(min, max);

        while (diceUsed < diceCount)
        {
            totalSum += distribution(generator);
            diceUsed++;
        }

        return totalSum;
    }
};

// Board class
class Board
{
public:
    vector<vector<Cell *>> cells;
    int boardSize;

    Board(int size, int numberOfSnakes, int numberOfLadders) : boardSize(size)
    {
        initializeCells(size);
        addSnakesLadders(numberOfSnakes, numberOfLadders);
    }

    ~Board()
    {
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                delete cells[i][j];
            }
        }
    }

private:
    void initializeCells(int size)
    {
        cells.resize(size, vector<Cell *>(size));

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cells[i][j] = new Cell();
            }
        }
    }

    void addSnakesLadders(int numberOfSnakes, int numberOfLadders)
    {
        mt19937 generator(time(0));
        uniform_int_distribution<int> distribution(1, boardSize * boardSize - 1);

        // Add snakes
        while (numberOfSnakes > 0)
        {
            int snakeHead = distribution(generator);
            int snakeTail = distribution(generator);

            if (snakeTail >= snakeHead)
            {
                continue;
            }

            Jump *snakeObj = new Jump(snakeHead, snakeTail);
            Cell *cell = getCell(snakeHead);
            cell->jump = snakeObj;

            numberOfSnakes--;
        }

        // Add ladders
        while (numberOfLadders > 0)
        {
            int ladderStart = distribution(generator);
            int ladderEnd = distribution(generator);

            if (ladderStart >= ladderEnd)
            {
                continue;
            }

            Jump *ladderObj = new Jump(ladderStart, ladderEnd);
            Cell *cell = getCell(ladderStart);
            cell->jump = ladderObj;

            numberOfLadders--;
        }
    }

public:
    Cell *getCell(int playerPosition)
    {
        int boardRow = playerPosition / boardSize;
        int boardColumn = playerPosition % boardSize;
        return cells[boardRow][boardColumn];
    }
};

// Game class
class Game
{
private:
    Board *board;
    Dice *dice;
    deque<Player *> playersList;
    Player *winner;

public:
    Game()
    {
        board = nullptr;
        dice = nullptr;
        winner = nullptr;
        initializeGame();
    }

    ~Game()
    {
        delete board;
        delete dice;
        for (Player *player : playersList)
        {
            delete player;
        }
    }

private:
    void initializeGame()
    {
        board = new Board(10, 5, 4);
        dice = new Dice(1);
        winner = nullptr;
        addPlayers();
    }

    void addPlayers()
    {
        Player *player1 = new Player("Player-1", 0);
        Player *player2 = new Player("Player-2", 0);
        playersList.push_back(player1);
        playersList.push_back(player2);
    }

    Player *findPlayerTurn()
    {
        Player *playerTurn = playersList.front();
        playersList.pop_front();
        playersList.push_back(playerTurn);
        return playerTurn;
    }

    int jumpCheck(int playerNewPosition)
    {
        if (playerNewPosition > board->boardSize * board->boardSize - 1)
        {
            return playerNewPosition;
        }

        Cell *cell = board->getCell(playerNewPosition);
        if (cell->jump != nullptr && cell->jump->start == playerNewPosition)
        {
            string jumpBy = (cell->jump->start < cell->jump->end) ? "Ladder" : "Snake";
            cout << "[+] Jump done by: " << jumpBy << endl;
            return cell->jump->end;
        }
        return playerNewPosition;
    }

public:
    void startGame()
    {
        while (winner == nullptr)
        {
            // Check whose turn now
            Player *playerTurn = findPlayerTurn();
            cout << "Player turn: " << playerTurn->id << " current position is: " << playerTurn->currentPosition << endl;

            // Roll the dice
            int diceNumbers = dice->rollDice();

            // Get the new position
            int playerNewPosition = playerTurn->currentPosition + diceNumbers;
            playerNewPosition = jumpCheck(playerNewPosition);
            playerTurn->currentPosition = playerNewPosition;

            cout << "Player turn: " << playerTurn->id << " new Position is: " << playerNewPosition << endl;

            // Check for winning condition
            if (playerNewPosition >= board->boardSize * board->boardSize - 1)
            {
                winner = playerTurn;
            }
        }
        cout << "\n===> The Winner is: " << winner->id << endl;
    }
};

// Main function
int main()
{
    Game *game = new Game();
    game->startGame();
    delete game;

    return 0;
}
