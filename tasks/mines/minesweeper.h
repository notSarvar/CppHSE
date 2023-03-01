#pragma once

#include <string>
#include <vector>
#include <time.h>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    struct CellStatus {
        char mark = '-';
        size_t mines_cnt = 0;
        bool is_opened_ = false;
    };

    RenderedField field_;
    std::vector<std::vector<CellStatus>> cell_status_;
    time_t start_time_;
    time_t end_time_;
    size_t cells_left_;
    GameStatus game_status_ = GameStatus::NOT_STARTED;

    std::vector<Cell> GenerateMines(size_t width, size_t height, size_t mines_count);
    size_t CountMines(size_t x, size_t y);
    bool StatusCheck() const;
};
