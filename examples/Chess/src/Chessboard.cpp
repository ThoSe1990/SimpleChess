
#include "Chessboard.hpp"

const char* Chessboard::numbers = "87654321";
const char* Chessboard::letters = "ABCDEFGH";

std::map<std::string, anoEngine::Vector2d> Chessboard::squareCoordinates;


void Chessboard::Init()
{
    std::cout << "initializing chessboard" << std::endl;
    int currentSquare = whiteSquare;
    for (int rows = 0 ; rows < Constants::number_of_squares_per_row ; rows++)
    {
        currentSquare = toggleSquareColor(currentSquare);
        for (int cols = 0 ; cols < Constants::number_of_squares_per_row ; cols++)
        {
            int x = cols * Constants::square_sidelength + Constants::chessboard_offset;
            int y = rows * Constants::square_sidelength + Constants::chessboard_offset;
            addSquareCoordinates(cols, rows, x, y);
            currentSquare = toggleSquareColor(currentSquare);         
            addSquare(currentSquare * Constants::square_sidelength, 0, x, y);
        }
    }
}


anoEngine::Vector2d Chessboard::GetCoordinatesFromSquare(const std::string& title)
{
    return squareCoordinates[title] + Constants::offset_figures_squares_vec2;
}


int Chessboard::toggleSquareColor(const int currentSquare)
{
    return (currentSquare == whiteSquare) ? blackSquare : whiteSquare;
}

void Chessboard::addSquareCoordinates(const int col, const int row, const int x, const int y)
{
    std::string squareTitle = "";
    squareTitle += letters[col];
    squareTitle += numbers[row];
    squareCoordinates.emplace(squareTitle, anoEngine::Vector2d{x, y});
}

void Chessboard::addSquare(const int sourceRectX, const int sourceRectY, const int x, const int y)
{

    auto newEntity = anoEngine::CreateEntity();

    anoEngine::Sprite::Create(newEntity,
        std::string("board_squares"),
        anoEngine::Rectangle{sourceRectX, sourceRectY, Constants::square_sidelength, Constants::square_sidelength},
        anoEngine::Rectangle{x, y, Constants::square_sidelength, Constants::square_sidelength},
        anoEngine::Sprite::Flip::none,
        anoEngine::Sprite::Layer::layer_0
    );

    return;
}

bool Chessboard::IsValidSquare(const std::string& square)
{
    return (squareCoordinates.find(square) == squareCoordinates.end()) ? false : true ;
}

std::string Chessboard::GetSquareTitleByCoordinates(anoEngine::Vector2d coordinates)
{   
    if ( (coordinates.x < Constants::chessboard_offset) ||
        (coordinates.x > (Constants::square_sidelength * Constants::number_of_squares_per_col) + Constants::chessboard_offset) ||
        (coordinates.y < Constants::chessboard_offset) ||
        (coordinates.y > (Constants::square_sidelength * Constants::number_of_squares_per_row) + Constants::chessboard_offset) )
            return Constants::invalid_square;
    
    int x = (coordinates.x - Constants::chessboard_offset) / Constants::square_sidelength ;
    int y = (coordinates.y - Constants::chessboard_offset) / Constants::square_sidelength ;

    std::string title = "";
    title += letters[x];
    title += numbers[y];    
    return title;
}
