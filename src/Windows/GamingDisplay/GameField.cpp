#include "../include/Windows/GamingDisplay/GameField.hpp"

void game::Chip::SetCellItem(CellDefinitions cellItem)
{
    std::string sample = GameSetup::GetFieldSize() == 8 ? "60px.png" : GameSetup::GetFieldSize() == 10 ? "50px.png" : "40px.png";
    _cellItem = cellItem;
    auto position = _chipSprite.getPosition();
    _chipSprite = sf::Sprite();
    _chipSprite.setPosition(position);
    
    switch (_cellItem)
    {
    case CellDefinitions::Black:
        _chipSprite.setTexture(ResourceLoader::GetTexture("../Images/BlackChip/" + sample));
        break;
    case CellDefinitions::White:
        _chipSprite.setTexture(ResourceLoader::GetTexture("../Images/WhiteChip/" + sample));
        break;
    case CellDefinitions::Hole:
        _chipSprite.setTexture(ResourceLoader::GetTexture("../Images/BlackHole/" + sample));
        break;
    default:
        break;
    }

    Origin();
}

void game::Chip::SetSprite(const sf::Sprite& sprite)
{
    auto position = _chipSprite.getPosition();
    _chipSprite = sprite;
    Origin();
    _chipSprite.setPosition(position);
}

void game::Cell::init()
{
    _tip.setFillColor(sf::Color(0, 0, 0, 0));
    _tip.setOrigin(_tip.getGlobalBounds().width / 2.f, _tip.getGlobalBounds().height / 2.f);
    ShowPossibleMove(false);
}

game::Cell::Cell(CellOptions cellOptions, sf::Vector2i coordinates, 
        std::vector<std::vector<game::Cell>>& cells, CellDefinitions& playerColor,
            CellDefinitions& opponentColor, CellDefinitions& moveColor, std::vector<Cell*>& cellsWithFlippedChips)

    : _background(cellOptions._size), 
    _chip(cellOptions._cellItem), _coordinates(coordinates), _cells(cells), _tip(_background.getSize().x / 3.f),
    _playerColor(_playerColor), _opponentColor(opponentColor), _moveColor(moveColor), _cellsWithFlippedChips(cellsWithFlippedChips)
{
    _background.setOrigin(cellOptions._size.x / 2, cellOptions._size.y / 2);
    _background.setFillColor(cellOptions._backgroundColor);
    
    init();
}

void game::Cell::ShowPossibleMove(bool isPossibleMove)
{
    _tip.setOutlineThickness(isPossibleMove ? 3.f : 0.f);
    _tip.setOutlineColor(_moveColor == CellDefinitions::Black ? sf::Color::Black : sf::Color::White);
}


bool game::Cell::IsPossibleMove()
{
    CellDefinitions opponentColor = _moveColor == CellDefinitions::Black ? CellDefinitions::White : CellDefinitions::Black;

    if (_cells[_coordinates.x][_coordinates.y].GetCellDefinition() != CellDefinitions::Empty)
        return false;

    for (auto& step : steps)
    {
        bool series = false;
        for (int i = 1; i < fieldSize; ++i)
        {
            if (!IsStepInBounds(_coordinates.x + i * step.first, _coordinates.y + i * step.second))
                break;

            if (_cells[_coordinates.x + i * step.first][_coordinates.y + i * step.second].GetCellDefinition() == opponentColor)
                series = true;
            else if (_cells[_coordinates.x + i * step.first][_coordinates.y + i * step.second].GetCellDefinition() == _moveColor)
            {
                if (series)
                    return true;
                break;
            }
            else
                break;
        }
    }

    return false;
}

void game::Cell::Move()
{
    CellDefinitions opponentColor = _moveColor == CellDefinitions::Black ? CellDefinitions::White : CellDefinitions::Black;
    _cells[_coordinates.x][_coordinates.y].SetCellItem(_moveColor);
    for (auto& step : steps)
    {
        bool series = false;
        for (int i = 1; i < fieldSize; ++i)
        {
            if (!IsStepInBounds(_coordinates.x + i * step.first, _coordinates.y + i * step.second))
                break;

            if (_cells[_coordinates.x + i * step.first][_coordinates.y + i * step.second].GetCellDefinition() == opponentColor)
                series = true;
            else if (_cells[_coordinates.x + i * step.first][_coordinates.y + i * step.second].GetCellDefinition() == _moveColor)
            {
                if (series)
                {
                    for (int i = 1; _moveColor != 
                                    _cells[_coordinates.x + i * step.first][_coordinates.y + i * step.second].GetCellDefinition(); ++i)
                    {
                        _cells[_coordinates.x + i * step.first][_coordinates.y + i * step.second].ChangeCellItem();
                    }  
                }
                break;
            }
            else
                break;
        }
    }
}

bool game::Cell::Update(const sf::Vector2f& mousePos, const sf::Event& event) 
{
    bool isPossibleMove = false;
    if (GameSetup::GetGameTypeID() == GameTypeID::Multiplayer ||  _moveColor != _opponentColor)
        isPossibleMove = IsPossibleMove();

    if (!_background.getGlobalBounds().contains(mousePos))
        return false;

    if (isPossibleMove && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {   
        Move();
        return true;
    }

    return false;
}


void game::Cell::SetPosition(float x, float y)
{
    _background.setPosition(x, y);
    _chip.SetPosition(x, y);
    _tip.setPosition(x, y);
}

void game::Cell::Draw(sf::RenderTarget* target) const
{
    target->draw(_background);

    if (BoardSetup::GetTips())
        target->draw(_tip);

    _chip.Draw(target);
}

void game::GameField::init()
{
    float paddingWidth = (_backgroundField.getBounds().width - Decor.cellSize * fieldSize - (fieldSize - 1) * Decor.stepBetweenCells) / 2.f;
    float paddingHeight = (_backgroundField.getBounds().height - Decor.cellSize * fieldSize - (fieldSize - 1) * Decor.stepBetweenCells) / 2.f;
    for (int i = 0; i < fieldSize; i++)
    {
        _cells.push_back(std::vector<game::Cell>{});
        for (int j = 0; j < fieldSize; j++)
        {
            _cells[i].push_back(game::Cell
            (
                Cell::CellOptions((i + j) % 2 == 0 ? BoardSetup::GetColors().at(BoardSetup::GetTheme()).y : 
                                                    BoardSetup::GetColors().at(BoardSetup::GetTheme()).z,
                {Decor.cellSize, Decor.cellSize}, CellDefinitions::Empty),
                sf::Vector2i({i, j}),
                _cells,
                _playerColor,
                _opponentColor,
                _moveColor, 
                _cellsWithFlippedChips
            ));
            _cells[i][j].SetPosition(-_backgroundField.getBounds().width / 2.f + (2 * j + 1) * Decor.cellSize / 2.f + paddingWidth + j * Decor.stepBetweenCells, 
            -_backgroundField.getBounds().height / 2.f + (2 * i + 1) * Decor.cellSize / 2.f + paddingHeight + i * Decor.stepBetweenCells);
        }
    }
    
    SetStartPosition();
    
}

game::GameField::GameField(CellDefinitions& playerColor,
        CellDefinitions& opponentColor, CellDefinitions& moveColor, float outlineThickness, sf::Color outlineColor)

    : _playerColor(playerColor), _opponentColor(opponentColor), _moveColor(moveColor), 
    _backgroundField(Decor.backgroundSize, Decor.backgroundRadius, outlineThickness, outlineColor, Decor.backgroundColor, Decor.backgroundColor), 
    _computerRun(&game::GameField::ComputerRun, this)
{
    init();
}

void game::GameField::SetStartPosition()
{
    _moveColor = CellDefinitions::Black;
    _isComputerRunning = false;
    ResetTips();
    ShowPossibleMoves();

    for (auto &row : _cells)
        for (auto &cell : row)
            cell.SetCellItem(CellDefinitions::Empty);

    if (GameSetup::GetGameParametersID() == GameParametersID::ReversiWithBlackHole)
            _cells[GameSetup::GetBlackHolePosition().x][GameSetup::GetBlackHolePosition().y].SetCellItem(CellDefinitions::Hole);

    switch (fieldSize)
    {
    case 8:
        _cells[4][3].SetCellItem(CellDefinitions::Black);
        _cells[3][3].SetCellItem(CellDefinitions::White);
        _cells[3][4].SetCellItem(CellDefinitions::Black);
        _cells[4][4].SetCellItem(CellDefinitions::White);
        break;
    case 10:
        _cells[5][4].SetCellItem(CellDefinitions::White);
        _cells[4][4].SetCellItem(CellDefinitions::White);
        _cells[4][5].SetCellItem(CellDefinitions::Black);
        _cells[5][5].SetCellItem(CellDefinitions::Black);
        break;
    default:
        _cells[6][5].SetCellItem(CellDefinitions::White);
        _cells[5][5].SetCellItem(CellDefinitions::White);
        _cells[5][6].SetCellItem(CellDefinitions::Black);
        _cells[6][6].SetCellItem(CellDefinitions::Black);
        break;
    }
}

void game::GameField::Draw(sf::RenderTarget* target) const
{
    _backgroundField.Draw(target);
    
    for (auto &row : _cells)
    {
        for (auto &cell : row)
        {   
            cell.Draw(target);
        }
    }
}

void game::GameField::SetOffset(float OXOffset, float OYOffset)
{
    _backgroundField.SetPosition(_backgroundField.GetPosition().x + OXOffset, _backgroundField.GetPosition().y + OYOffset);

    for (auto &row : _cells)
    {
        for (auto &cell : row)
        {
            cell.SetPosition(cell.GetPosition().x + OXOffset, cell.GetPosition().y + OYOffset);
        }
    }
}

void game::GameField::ResetTips()
{
    for (auto &row : _cells)
        for (auto &cell : row)
            cell.ShowPossibleMove(false);
}

bool game::GameField::IsPossibleMoves()
{
    for (auto &row : _cells)
        for (auto &cell : row)
            if(cell.IsPossibleMove())
                return true;

    return false;
}

bool game::GameField::ChangeMoveColor()
{
    _moveColor = _moveColor == CellDefinitions::Black ? CellDefinitions::White : CellDefinitions::Black;
    if (IsPossibleMoves())
        return true;

    _moveColor = _moveColor == CellDefinitions::Black ? CellDefinitions::White : CellDefinitions::Black;
    return IsPossibleMoves();
}

game::GameField::Computer::Computer(const GameField& gameFiled)
    : currentMove(gameFiled._moveColor == CellDefinitions::White ? WHITE : BLACK)
{
    for (int i = 0; i < (fieldSize + 2) * (fieldSize + 2); i++)
    {
        int x = i / (fieldSize + 2), y = i % (fieldSize + 2);
        if ((x < 1) || x > fieldSize || y < 1 || y > fieldSize)
            Board[i] = OFF;
        else
        {
            switch (gameFiled._cells[x - 1][y - 1].GetCellDefinition())
            {
            case CellDefinitions::White:
                Board[i] = WHITE;
                break;
            case CellDefinitions::Black:
                Board[i] = BLACK;
                break;
            case CellDefinitions::Empty:
                Board[i] = EMPTY;
                break;
            default:
                break;
            }
        }
    }

}

int game::GameField::Computer::Eval()
{
    int score = 0;
    for (int i = TOPLEFT; i <= BOTTOMRIGHT; i++)
    {
        if (Board[i] == WHITE)
            score += 1 ;
        else if (Board[i] == BLACK)
            score -= 1;
    }

    return score * anti;
}

bool game::GameField::Computer::IsCapture(int move, int dir)
{
    int s = move + dir;
    while (Board[s] == 1 - currentMove)
        s += dir;

    return s != move + dir && Board[s] == currentMove;
}

bool game::GameField::Computer::IsCapture(int sq)
{
    for (auto &&dir : Dirs)
        if (IsCapture(sq, dir)) 
            return true; 

    return false;
}

int game::GameField::Computer::GenMoves(int moves[])
{
    int n = 0;
    for (int i = TOPLEFT; i <= BOTTOMRIGHT; i++)
        if (Board[i] == EMPTY && IsCapture(i))
            moves[n++] = i;

    return n;
}

void game::GameField::Computer::Capture(int m, int dir, int caps[], int &n)
{
    int sq = m + dir;
    while (Board[sq] == 1 - currentMove) 
        sq += dir;

    if (Board[sq] == currentMove)
    {
        for (int s = m + dir; s != sq; s += dir)
        {
            caps[n++] = s;
            Board[s] = currentMove;
        }
    }
}

int game::GameField::Computer::MakeMove(int m, int caps[])
{
    Board[m] = currentMove;

    int n = 0;
    for (auto &&dir : Dirs)
        Capture(m, dir, caps, n);

    currentMove = 1 - currentMove;

    return n;
}

void game::GameField::Computer::UnmakeMove(int m, int caps[], int n)
{
    Board[m] = EMPTY;

    for (int i = 0; i < n; i++) 
        Board[caps[i]] = currentMove;

    currentMove = 1 - currentMove;
}

int game::GameField::Computer::Search(int depth, bool pass)
{
    if (depth == 0) 
        return Eval();

    int moves[(fieldSize + 2) * (fieldSize + 2)];
    int n = GenMoves(moves);
    
    if (!n)
    {
        if (pass) 
            return Eval();

        currentMove = 1 - currentMove;
        int score = Search(depth, true);
        currentMove = 1 - currentMove;
        return score;
    }

    int bestScore = (currentMove == WHITE) ? INT_MIN : INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int caps[(fieldSize + 2) * (fieldSize + 2)];
        int nc = MakeMove(moves[i], caps);

        int score = Search(depth - 1, false);
        UnmakeMove(moves[i], caps, nc);

        if (currentMove == WHITE)
            bestScore = std::max(bestScore, score);

        else
            bestScore = std::min(bestScore, score);
    }

    return bestScore;
}

int game::GameField::Computer::RootSearch(int depth)
{
    int moves[(fieldSize + 2) * (fieldSize + 2)];
    int n = GenMoves(moves);

    if (!n) 
        return 0;
    if (n == 1) 
        return moves[0];

    for (int i = 0; i < n; i++)
        std::swap(moves[n - i - 1], moves[rand() % (n - 1)]);

    int bestMove;
    int best = currentMove ? INT_MIN : INT_MAX;
    for (int i = 0; i < n; ++i)
    {
        int caps[(fieldSize + 2) * (fieldSize + 2)];
        int nc = MakeMove(moves[i], caps);

        int score = Search(depth - 1, false);

        UnmakeMove(moves[i], caps, nc);

        if ((currentMove && score >= best) || (!currentMove && score <= best))
        {
            best = score;
            bestMove = moves[i];
        }
        
    }

    return bestMove;
}

void game::GameField::ComputerRun()
{
    sf::Clock clock;
    Computer computer(*this);
    int move;
    switch (GameSetup::GetComputerDifficulty())
    {
    case 1:
        move = computer.RootSearch(3);
        break;
    case 2:
        move = computer.RootSearch(4);
        break;
    default:
        move = computer.RootSearch(5);
        break;
    }
    
    while(clock.getElapsedTime().asSeconds() < 1.5f);
    _cells[move / (fieldSize + 2) - 1][move % (fieldSize + 2) - 1].Move();
}

void game::GameField::ShowPossibleMoves()
{
    if (GameSetup::GetGameTypeID() != GameTypeID::Multiplayer &&  _moveColor == _opponentColor) ///////////////////////
        return;

    for (auto &row : _cells)
    {
        for (auto &cell : row)
        { cell.ShowPossibleMove(cell.IsPossibleMove());
        }
    }
}

void game::GameField::Update(const sf::Vector2f& mousePosition, const sf::Event& event)
{
    for (auto &row : _cells)
    {
        for (auto &cell : row)
        {
            if(cell.Update(mousePosition, event))
            {
                ResetTips();
                return;
            }
                
        }
    }
}