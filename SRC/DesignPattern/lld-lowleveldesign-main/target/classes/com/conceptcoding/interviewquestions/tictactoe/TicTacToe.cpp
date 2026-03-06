#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <sstream>

// Enums equivalent to Java enums
enum class PieceType
{
    X,
    O
};

enum class GameStatus
{
    DRAW,
    WIN
};

// Forward declarations
class PlayingPiece;
class Player;
class Board;
class TicTacToeGame;

// PlayingPiece base class
class PlayingPiece
{
public:
    PieceType pieceType;

    PlayingPiece(PieceType type) : pieceType(type) {}
    virtual ~PlayingPiece() = default;
};

// PlayingPieceX class
class PlayingPieceX : public PlayingPiece
{
public:
    PlayingPieceX() : PlayingPiece(PieceType::X) {}
};

// PlayingPieceO class
class PlayingPieceO : public PlayingPiece
{
public:
    PlayingPieceO() : PlayingPiece(PieceType::O) {}
};

// Player class
class Player
{
public:
    std::string name;
    PlayingPiece *playingPiece;

    Player(const std::string &playerName, PlayingPiece *piece)
        : name(playerName), playingPiece(piece) {}

    ~Player()
    {
        delete playingPiece;
    }

    // Getters and setters
    std::string getName() const { return name; }
    void setName(const std::string &playerName) { name = playerName; }
    PlayingPiece *getPlayingPiece() const { return playingPiece; }
    void setPlayingPiece(PlayingPiece *piece) { playingPiece = piece; }
};

// Board class
class Board
{
public:
    int size;
    std::vector<std::vector<PlayingPiece *>> board;

    Board(int boardSize) : size(boardSize)
    {
        board = std::vector<std::vector<PlayingPiece *>>(size, std::vector<PlayingPiece *>(size, nullptr));
    }

    bool addPiece(int row, int column, PlayingPiece *playingPiece)
    {
        if (board[row][column] != nullptr)
        {
            return false;
        }
        board[row][column] = playingPiece;
        return true;
    }

    std::vector<std::pair<int, int>> getFreeCells()
    {
        std::vector<std::pair<int, int>> freeCells;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == nullptr)
                {
                    freeCells.push_back(std::make_pair(i, j));
                }
            }
        }
        return freeCells;
    }

    void printBoard()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] != nullptr)
                {
                    char pieceChar = (board[i][j]->pieceType == PieceType::X) ? 'X' : 'O';
                    std::cout << pieceChar << "   ";
                }
                else
                {
                    std::cout << "    ";
                }
                std::cout << " | ";
            }
            std::cout << std::endl;
        }
    }
};

// TicTacToeGame class
class TicTacToeGame
{
private:
    std::deque<Player *> players;
    Board *gameBoard;
    Player *winner;

public:
    TicTacToeGame() : gameBoard(nullptr), winner(nullptr) {}

    ~TicTacToeGame()
    {
        // Clean up players
        while (!players.empty())
        {
            delete players.front();
            players.pop_front();
        }
        delete gameBoard;
    }

    void initializeGame()
    {
        // Creating 2 Players
        PlayingPieceX *crossPiece = new PlayingPieceX();
        Player *player1 = new Player("Player1", crossPiece);

        PlayingPieceO *noughtsPiece = new PlayingPieceO();
        Player *player2 = new Player("Player2", noughtsPiece);

        players.push_back(player1);
        players.push_back(player2);

        // Initialize Board of size 3
        gameBoard = new Board(3);
    }

    GameStatus startGame()
    {
        bool noWinner = true;

        while (noWinner)
        {
            // Remove the player whose turn it is and put the player back in the list
            Player *currentPlayer = players.front();
            players.pop_front();

            // Get the free space from the board
            gameBoard->printBoard();
            std::vector<std::pair<int, int>> freeSpaces = gameBoard->getFreeCells();
            if (freeSpaces.empty())
            {
                noWinner = false;
                players.push_front(currentPlayer); // Put the player back
                continue;
            }

            // Read user input
            std::cout << "Player: " << currentPlayer->name << " - Please enter [row, column]: ";
            std::string input;
            std::getline(std::cin, input);

            // Parse input
            std::stringstream ss(input);
            std::string rowStr, colStr;
            std::getline(ss, rowStr, ',');
            std::getline(ss, colStr);

            int inputRow, inputColumn;
            try
            {
                inputRow = std::stoi(rowStr);
                inputColumn = std::stoi(colStr);
            }
            catch (const std::exception &e)
            {
                std::cout << "Invalid input format, try again!" << std::endl;
                players.push_front(currentPlayer); // Add the player back to the front
                continue;
            }

            // Validate coordinates
            if (inputRow < 0 || inputRow >= gameBoard->size ||
                inputColumn < 0 || inputColumn >= gameBoard->size)
            {
                std::cout << "Invalid coordinates, try again!" << std::endl;
                players.push_front(currentPlayer); // Add the player back to the front
                continue;
            }

            // Place the piece on the board
            bool validMove = gameBoard->addPiece(inputRow, inputColumn, currentPlayer->playingPiece);
            if (!validMove)
            {
                // Invalid Move: Player cannot insert the piece into this cell
                std::cout << "Incorrect position chosen, try again!" << std::endl;
                players.push_front(currentPlayer); // Add the player back to the front
                continue;
            }
            players.push_back(currentPlayer); // Add the player to the end of the queue

            // Check if the valid move is a winning move
            bool isWinner = checkForWinner(inputRow, inputColumn, currentPlayer->playingPiece->pieceType);
            if (isWinner)
            {
                gameBoard->printBoard();
                winner = currentPlayer;
                return GameStatus::WIN;
            }
        }

        return GameStatus::DRAW;
    }

    bool checkForWinner(int row, int column, PieceType pieceType)
    {
        bool rowMatch = true;
        bool columnMatch = true;
        bool diagonalMatch = true;
        bool antiDiagonalMatch = true;

        // Check Row
        for (int i = 0; i < gameBoard->size; i++)
        {
            if (gameBoard->board[row][i] == nullptr ||
                gameBoard->board[row][i]->pieceType != pieceType)
            {
                rowMatch = false;
                break;
            }
        }

        // Check Column
        for (int i = 0; i < gameBoard->size; i++)
        {
            if (gameBoard->board[i][column] == nullptr ||
                gameBoard->board[i][column]->pieceType != pieceType)
            {
                columnMatch = false;
                break;
            }
        }

        // Check Diagonal
        for (int i = 0, j = 0; i < gameBoard->size; i++, j++)
        {
            if (gameBoard->board[i][j] == nullptr ||
                gameBoard->board[i][j]->pieceType != pieceType)
            {
                diagonalMatch = false;
                break;
            }
        }

        // Check Anti-Diagonal
        for (int i = 0, j = gameBoard->size - 1; i < gameBoard->size; i++, j--)
        {
            if (gameBoard->board[i][j] == nullptr ||
                gameBoard->board[i][j]->pieceType != pieceType)
            {
                antiDiagonalMatch = false;
                break;
            }
        }

        return rowMatch || columnMatch || diagonalMatch || antiDiagonalMatch;
    }

    Player *getWinner() const { return winner; }
};

// Main function (equivalent to PlayGame.java)
int main()
{
    std::cout << "\n===>>> TicTacToe Game\n"
              << std::endl;

    TicTacToeGame game;
    game.initializeGame();
    GameStatus status = game.startGame();

    std::cout << "\n===>>> GAME OVER: ";
    switch (status)
    {
    case GameStatus::WIN:
        std::cout << game.getWinner()->getName() << " won the game" << std::endl;
        break;
    case GameStatus::DRAW:
        std::cout << "Its a Draw!" << std::endl;
        break;
    }

    return 0;
}