
#include "Chesscontroller/Chesscontroller.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/ChesspieceComponent.hpp"
#include "Components/ValidationComponent.hpp"


#include "ChessBoard.hpp"

Chesscontroller::Chesscontroller(State* state, std::vector<std::shared_ptr<Entity>> ChessPieces, std::vector<std::shared_ptr<Entity>> ValidationEntities) 
: currentState(state),
 chessPieces(ChessPieces),
 validationEntities(ValidationEntities)
{ }  

Chesscontroller::~Chesscontroller(){ }

void Chesscontroller::SetState(std::unique_ptr<State> state)
{
    currentState = std::move(state);
}

void Chesscontroller::SetMouseClick()
{
    mouseClick = true;
}
bool Chesscontroller::GetMouseClick() const
{
    return mouseClick;
}

void Chesscontroller::Update()
{
    this->currentState->UpdateGame(shared_from_this());
    this->mouseClick = false;
}

void Chesscontroller::SetSelectedPiece(std::shared_ptr<Entity>& entity)
{
    Logger::Log(logging::trivial::debug, log_location, "Selected: " , entity->name);
    this->selectedPiece = entity;
}

void Chesscontroller::SetClickedSquare(const int x, const int y)
{
    clickedSquare = ChessBoard::GetSquareTitleByCoordinates(glm::vec2(x,y));
}

std::shared_ptr<Entity> Chesscontroller::GetSelectedPiece() const
{
    return selectedPiece;
}


std::tuple<std::shared_ptr<Entity>, std::string, std::string> Chesscontroller::GetClickedPieceColorSquare() const
{
    std::string color = "";
    auto piece = this->getClickedEntity();
    if (piece)
        color = this->getColorOfPiece(piece);

    return std::make_tuple(piece, color, clickedSquare);
}


std::shared_ptr<Entity> Chesscontroller::getClickedEntity() const
{
    return GetEntityFromSqaure(clickedSquare);
}

std::shared_ptr<Entity> Chesscontroller::GetEntityFromSqaure(const std::string& square) const
{
    for (const auto& piece : chessPieces)
    {
        if (piece->HasComponent<TransformComponent>())
        {
            TransformComponent* transform = piece->GetComponent<TransformComponent>();
            if (transform->square.compare(square) == 0 && piece->IsActive())
                return piece;
        }
    } 
    return nullptr;
}

bool Chesscontroller::IsValidMove(const std::string& square)
{
    for (const auto& v : validationEntities)
    {
        if ( v->HasComponent<ValidationComponent>() )
        {
            ValidationComponent* vc = v->GetComponent<ValidationComponent>();
            if (square.compare( vc->GetTitle() ) == 0) 
                return v->IsActive();
        }
    }
    return false;
}

bool Chesscontroller::HasValidMoves()
{
    for (const auto& v : validationEntities)
        if (v->IsActive()) 
            return true;
    return false;
}

bool Chesscontroller::MoveSelectedPiece()
{
    TransformComponent* tc = this->selectedPiece->GetComponent<TransformComponent>();
    return tc->SetPosition(clickedSquare);
}

bool Chesscontroller::IsValidPosition(const std::string& square)
{
    return (ChessBoard::squareCoordinates.find(square) == ChessBoard::squareCoordinates.end())
    ? false
    : true ;
}


std::string Chesscontroller::getColorOfPiece(std::shared_ptr<Entity> piece) const
{
    ChesspieceComponent* c = piece->GetComponent<ChesspieceComponent>();
    return c->color_;
}

void Chesscontroller::ResetValidation()
{
    for (auto& entity : validationEntities)
        entity->Deactivate();
} 

void Chesscontroller::SetValidation(const std::string& square, const std::string& assetId)
{
    for (auto& entity : validationEntities)
    {
        auto v = entity->GetComponent<ValidationComponent>();
        if (v->GetTitle().compare(square) == 0)
        {
            v->SetTextureId(assetId);
            entity->Activate();
        }
    }
}


std::tuple<std::string, std::string> Chesscontroller::GetColorAndPosition(const std::shared_ptr<Entity>& entity) const
{
    std::string color = "";
    if (entity->HasComponent<ChesspieceComponent>())
    {
        ChesspieceComponent* cp = entity->GetComponent<ChesspieceComponent>();
        color = cp->color_;
    }   
    std::string square = "";
    if (entity->HasComponent<TransformComponent>())
    {
        TransformComponent* tp = entity->GetComponent<TransformComponent>();
        square = tp->square;
    }
    return std::make_tuple(color, square);
}


void Chesscontroller::CaptureOpponent(const std::string& square)
{
    std::shared_ptr<Entity> entity = this->GetEntityFromSqaure(square);
    if (entity)
    {
        entity->Deactivate();
    }
}