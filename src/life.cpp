
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

enum GENERATIONTYPE {
  Eve=1,
  Blom
};

struct GameOfLifeInit {
  int gridSizeY;
  int gridSizeX;
  int cellSize;
  Color deadColor;
  Color lifeColor;
  GENERATIONTYPE generationType;
  bool generationByStep;
  bool showGenerationCount;
};

struct Cell {
  bool isAlife;
  Color alifeColor;
  Color deadColor;
  int sizeInPixel;
  int posX;
  int posY;
  int index;
  void draw(RenderWindow& window) {
    RectangleShape rectangle;
    rectangle.setSize(Vector2f(sizeInPixel, sizeInPixel));
    rectangle.setFillColor(isAlife ? alifeColor : deadColor);
    rectangle.setPosition(posX * sizeInPixel, posY * sizeInPixel);
    window.draw(rectangle);
  }
};

void setSetCellToAlife(auto& cells, auto posX, auto posY, auto regionWidth) {
  cells[(posY*regionWidth)+posX].isAlife = true;
}
  
auto getAlifeStatusOf(auto& cells, auto posX, auto posY, auto regionWidth) {
  return cells[(posY*regionWidth)+posX].isAlife;
}

auto getCellNeighborsStatus(auto& cell, auto& cells, auto regionWidth, auto regionHeight) {
  array cellNeighborsStatus {false, false, false, false, false, false, false, false};
  if (cell.posX == 0 && cell.posY == 0) {
    //Top Left Corner
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX+1, 0, regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX  , 1, regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX+1, 1, regionWidth);
  }
  else if (cell.posX == regionWidth-1 && cell.posY == 0) {
    //Top Right Corner
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX-1, 0, regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX  , 1, regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX-1, 1, regionWidth);
  }
  else if (cell.posX == 0 && cell.posY == regionHeight-1) {
    //Bottom Left Corner
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX+1, regionHeight-1, regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX  , regionHeight-2, regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX+1, regionHeight-2, regionWidth);
  }
  else if (cell.posX == regionWidth-1 && cell.posY == regionHeight-1) {
    //Bottom Right Corner
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX-1, regionHeight-1, regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX  , regionHeight-2, regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX-1, regionHeight-2, regionWidth);
  }
  else if (cell.posX == 0) {
    //Left Border
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX,   cell.posY-1, regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX,   cell.posY+1, regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX+1, cell.posY-1, regionWidth);
    cellNeighborsStatus[3] = getAlifeStatusOf(cells, cell.posX+1, cell.posY,   regionWidth);
    cellNeighborsStatus[4] = getAlifeStatusOf(cells, cell.posX+1, cell.posY+1, regionWidth);
  }
  else if (cell.posX == regionWidth-1) {
    //Right Border
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX,   cell.posY-1, regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX,   cell.posY+1, regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX-1, cell.posY-1, regionWidth);
    cellNeighborsStatus[3] = getAlifeStatusOf(cells, cell.posX-1, cell.posY,   regionWidth);
    cellNeighborsStatus[4] = getAlifeStatusOf(cells, cell.posX-1, cell.posY+1, regionWidth);
  }
  else if (cell.posY == 0) {
    //Top Border
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX-1, cell.posY,   regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX+1, cell.posY,   regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX-1, cell.posY+1, regionWidth);
    cellNeighborsStatus[3] = getAlifeStatusOf(cells, cell.posX,   cell.posY+1, regionWidth);
    cellNeighborsStatus[4] = getAlifeStatusOf(cells, cell.posX+1, cell.posY+1, regionWidth);
  }
  else if (cell.posY == regionHeight-1) {
    //Bottom Border
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX-1, cell.posY,   regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX+1, cell.posY,   regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX-1, cell.posY-1, regionWidth);
    cellNeighborsStatus[3] = getAlifeStatusOf(cells, cell.posX,   cell.posY-1, regionWidth);
    cellNeighborsStatus[4] = getAlifeStatusOf(cells, cell.posX+1, cell.posY-1, regionWidth);
  }
  else {
    cellNeighborsStatus[0] = getAlifeStatusOf(cells, cell.posX-1, cell.posY,   regionWidth);
    cellNeighborsStatus[1] = getAlifeStatusOf(cells, cell.posX+1, cell.posY,   regionWidth);
    cellNeighborsStatus[2] = getAlifeStatusOf(cells, cell.posX-1, cell.posY-1, regionWidth);
    cellNeighborsStatus[3] = getAlifeStatusOf(cells, cell.posX,   cell.posY-1, regionWidth);
    cellNeighborsStatus[4] = getAlifeStatusOf(cells, cell.posX+1, cell.posY-1, regionWidth);
    cellNeighborsStatus[5] = getAlifeStatusOf(cells, cell.posX-1, cell.posY+1, regionWidth);
    cellNeighborsStatus[6] = getAlifeStatusOf(cells, cell.posX,   cell.posY+1, regionWidth);
    cellNeighborsStatus[7] = getAlifeStatusOf(cells, cell.posX+1, cell.posY+1, regionWidth);
  }
  return cellNeighborsStatus;
}

auto reCalc(auto& cell, auto& cells, auto regionWidth, auto regionHeight) {
  auto cellNeighborsStatus = getCellNeighborsStatus(cell, cells, regionWidth, regionHeight);
  auto cntLifes = std::count_if(cellNeighborsStatus.begin(), cellNeighborsStatus.end(), [](auto& v){return v;});
  if (!cell.isAlife) {
    return cntLifes == 3;
  }
  else if (cell.isAlife) {
    if (cntLifes < 2 || cntLifes > 3) {
      return false;
    }
    if (cntLifes == 2 || cntLifes == 3) {
      return true;
    }
  }
  return false;
}

void setCellGeneration(auto initCells, auto& cells, auto regionWidth, auto startPosX, auto startPosY) {
  auto X = startPosX;
  auto Y = startPosY;
  for (auto& line : initCells) {
    for (auto& column : line) {
      if (column == 1)
        setSetCellToAlife(cells, X, Y, regionWidth);
      X++;
    }
    Y++;
    X=startPosX;
  }
}
  
auto createCellGeneration(auto generationType) {
  switch (generationType) {
  case Eve: {
    //https://conwaylife.com/wiki/Eve 
    vector<vector<int>> cellsEve {
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0},
      {0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0},
      {0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
      {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    return cellsEve;
  }
  case Blom:
    {
      //https://conwaylife.com/wiki/Blom
      vector<vector<int>> cellsBlom {
        {1,0,0,0,0,0,0,0,0,0,0,1},
        {0,1,1,1,1,0,0,0,0,0,0,1},
        {0,0,1,1,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,0,1,0,0}
      };
      return cellsBlom;
    }
  default:
    {
      vector<vector<int>> defaultUnknownCells;
      return defaultUnknownCells;
    }
  }
}

void initializeLifes(auto& cells, auto initCellsType, auto regionWidth) {
  setCellGeneration(createCellGeneration(initCellsType), cells, regionWidth, 50, 33);
}

void calcNextGeneration(auto& cells, auto regionWidth, auto regionHeight, auto& appearanceCell, auto isFirst) {
  auto cellIndex = 0;
  vector<bool> nextGenerationLifeStaus(cells.size());
  auto p = nextGenerationLifeStaus.begin();
  for (auto& cell : cells) {
    if (isFirst) {
      cell.isAlife = false;
      cell.sizeInPixel = appearanceCell.sizeInPixel;
      cell.alifeColor = appearanceCell.alifeColor;
      cell.deadColor = appearanceCell.deadColor;
      cell.posY = cellIndex / regionWidth;
      cell.posX = cellIndex < regionWidth ? cellIndex : cellIndex - (cell.posY * regionWidth);
      cell.index = cellIndex++;
    }
    else  {
      *p++ = reCalc(cell, cells, regionWidth, regionHeight);
    }
  }
 
  if (isFirst == false) {
    auto p = nextGenerationLifeStaus.begin();
    for (auto& cell : cells) {
      cell.isAlife = *p++;
    }
  }
}

void drawGeneration(auto& cells, auto& window) {
  for_each(cells.begin(), cells.end(), [&](auto& cell) {
    cell.draw(window);
  });
}

auto checkArguments(auto& argumentCount, auto& arguments, auto& golInitValues) {
  auto result = 0;
  if (argumentCount == 1)
    return 0;
  for (int i = 1; i < argumentCount; i++) {
    string checkArgVal { arguments[i] };
    if (checkArgVal == "-h") {
      result = 1;
      break;
    }
    if (checkArgVal == "-step")
      golInitValues.generationByStep = true;

    if (checkArgVal == "-showgen")
      golInitValues.showGenerationCount = true;

    if (checkArgVal.find("-sizewidth") != string::npos) {
      golInitValues.gridSizeX = stoi(checkArgVal.substr(checkArgVal.rfind(":")));
    }

    if (checkArgVal.find("-sizeheight") != string::npos) {
      golInitValues.gridSizeY = stoi(checkArgVal.substr(checkArgVal.rfind(":")));
    }

    if (checkArgVal.find("-sizepixel") != string::npos) {
      golInitValues.cellSize = stoi(checkArgVal.substr(checkArgVal.rfind(":")));
    }
  
    if (checkArgVal.find("-deadcolor") != string::npos) {
      auto colorCode = checkArgVal.substr(checkArgVal.rfind(":"));
      golInitValues.deadColor = Color(stoul(colorCode.substr(1,2), nullptr, 16),
                                      stoul(colorCode.substr(2,4), nullptr, 16),
                                      stoul(colorCode.substr(4,6), nullptr, 16), 255);
    }

    if (checkArgVal.find("-lifecolor") != string::npos) {
      auto colorCode = checkArgVal.substr(checkArgVal.rfind(":"));
      golInitValues.deadColor = Color(stoul(colorCode.substr(1,2), nullptr, 16),
                                      stoul(colorCode.substr(2,4), nullptr, 16),
                                      stoul(colorCode.substr(4,6), nullptr, 16), 255);
    }

    if (checkArgVal.find("-init") != string::npos) {
      if (checkArgVal.substr(checkArgVal.rfind(":")) == "blom")
        golInitValues.generationType = GENERATIONTYPE::Blom;
      if (checkArgVal.substr(checkArgVal.rfind(":")) == "eve")
        golInitValues.generationType = GENERATIONTYPE::Eve;
    }
  }
  return result;
}

auto runLife(auto& In) {
  RenderWindow window(VideoMode(In.gridSizeX, In.gridSizeY), "Life");
  window.clear(In.deadColor);
  window.display();

  auto cellRegionSizeInPixel = window.getSize();
  auto firstRun = true;
  auto generation = 0;
  auto cellRegionWidth = (cellRegionSizeInPixel.x / In.cellSize) + ((cellRegionSizeInPixel.x % In.cellSize) ? 1 : 0);
  auto cellRegionHeight = (cellRegionSizeInPixel.y / In.cellSize) + ((cellRegionSizeInPixel.y % In.cellSize) ? 1 : 0);

  vector<Cell> cells(cellRegionWidth * cellRegionHeight);

  Cell appearanceCell;
  appearanceCell.sizeInPixel = In.cellSize;
  appearanceCell.alifeColor = In.lifeColor;
  appearanceCell.deadColor = In.deadColor;

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if(event.type == Event::Closed) {
        window.close();
        return EXIT_SUCCESS;
      }
      else if(event.type == Event::KeyPressed) {
        if(event.key.code == Keyboard::Key::Escape) {
          if (In.generationByStep) {
            if (In.showGenerationCount)
              cout << "Calc generation : " << ++generation << "\r" << flush;
            calcNextGeneration(cells, cellRegionWidth, cellRegionHeight, appearanceCell, firstRun);
          }
          else {
            window.close();
            return EXIT_SUCCESS;
          }
        }
      }
    }

    if (In.showGenerationCount)
      cout << "Calc generation : " << ++generation << "\r" << flush;
    if (firstRun) {
      calcNextGeneration(cells, cellRegionWidth, cellRegionHeight, appearanceCell, firstRun);
      initializeLifes(cells, In.generationType, cellRegionWidth);
      firstRun = false;
    }
    else {
      if (!In.generationByStep)
        calcNextGeneration(cells, cellRegionWidth, cellRegionHeight, appearanceCell, firstRun);
    }
      
    drawGeneration(cells, window);
    
    window.display();
  }

  return EXIT_SUCCESS;
}

void printHelp() {
  cout << "life [args]" << endl;
  cout << "     [-h]" << endl;
  cout << "     [-sizewidth:1040]" << endl;
  cout << "     [-sizeheight:800]" << endl;
  cout << "     [-sizePixel:8]" << endl;
  cout << "     [-deadColor:#0242FF]" << endl;
  cout << "     [-lifeColor:#5633DE]" << endl;
  cout << "     [-step]" << endl;
  cout << "     [-showgen]" << endl;
  cout << "     [-init:<eve|blom>]" << endl;
}

int main(int argc, char **argv) {
  GameOfLifeInit golInitValues;
  golInitValues.gridSizeX = 1040;
  golInitValues.gridSizeY = 800;
  golInitValues.cellSize = 8;
  golInitValues.generationByStep = false;
  golInitValues.showGenerationCount = false;
  //golInitValues.lifeColor = Color(125, 52,52, 255);
  golInitValues.lifeColor = Color(255, 255, 231, 255);
  golInitValues.deadColor = Color(58, 52, 52, 255);
  golInitValues.generationType = GENERATIONTYPE::Eve;
  auto executeArgs = checkArguments(argc, argv, golInitValues);
  if (executeArgs) {
    printHelp();
    return 0;
  }
  return runLife(golInitValues);
}
