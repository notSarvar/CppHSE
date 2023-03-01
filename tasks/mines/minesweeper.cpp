#include "minesweeper.h"

#include <numeric>
#include <algorithm>
#include <random>
#include <queue>

#include <iostream>

bool Minesweeper::StatusCheck() const {
    return !(game_status_ == GameStatus::DEFEAT || game_status_ == GameStatus::VICTORY);
}

std::vector<Minesweeper::Cell> Minesweeper::GenerateMines(size_t width, size_t height, size_t mines_count) {
    std::vector<Cell> mines;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            mines.push_back({i, j});
        }
    }

    auto rng = std::default_random_engine{};
    std::shuffle(mines.begin(), mines.end(), rng);

    mines.resize(mines_count);
    return mines;
}

size_t Minesweeper::CountMines(size_t x, size_t y) {
    size_t cnt = 0;
    if (x + 1 < field_.size() && field_[x + 1][y] == '*') {
        ++cnt;
    }
    if (y + 1 < field_[x].size() && field_[x][y + 1] == '*') {
        ++cnt;
    }
    if (x > 0 && field_[x - 1][y] == '*') {
        ++cnt;
    }
    if (y > 0 && field_[x][y - 1] == '*') {
        ++cnt;
    }
    if (x + 1 < field_.size() && y > 0 && field_[x + 1][y - 1] == '*') {
        ++cnt;
    }
    if (y + 1 < field_[x].size() && x > 0 && field_[x - 1][y + 1] == '*') {
        ++cnt;
    }
    if (x + 1 < field_.size() && y + 1 < field_[x].size() && field_[x + 1][y + 1] == '*') {
        ++cnt;
    }
    if (y > 0 && x > 0 && field_[x - 1][y - 1] == '*') {
        ++cnt;
    }
    return cnt;
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    cells_left_ = width * height - mines_count;
    field_.resize(height);
    cell_status_.resize(height);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            field_[i].push_back('.');
        }
    }
    auto mines = GenerateMines(width, height, mines_count);
    for (const auto& i : mines) {
        field_[i.x][i.y] = '*';
    }

    for (size_t i = 0; i < field_.size(); ++i) {
        for (size_t j = 0; j < field_[i].size(); ++j) {
            size_t cnt = CountMines(i, j);
            cell_status_[i].push_back({'-', cnt, false});
        }
    }
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    cells_left_ = width * height - cells_with_mines.size();
    field_.resize(height);
    cell_status_.resize(height);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            field_[i].push_back('.');
        }
    }
    for (const auto& i : cells_with_mines) {
        field_[i.y][i.x] = '*';
    }
    for (size_t i = 0; i < field_.size(); ++i) {
        for (size_t j = 0; j < field_[i].size(); ++j) {
            size_t cnt = CountMines(i, j);
            cell_status_[i].push_back({'-', cnt, false});
        }
    }
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    game_status_ = GameStatus::NOT_STARTED;
    start_time_ = 0;
    field_.clear();
    cell_status_.clear();
    field_.resize(height);
    cell_status_.resize(height);
    cells_left_ = width * height - mines_count;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            field_[i].push_back('.');
        }
    }
    auto mines = GenerateMines(width, height, mines_count);
    for (const auto& i : mines) {
        field_[i.x][i.y] = '*';
    }
    for (size_t i = 0; i < field_.size(); ++i) {
        for (size_t j = 0; j < field_[i].size(); ++j) {
            size_t cnt = CountMines(i, j);
            cell_status_[i].push_back({'-', cnt, false});
        }
    }
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Minesweeper::Cell>& cells_with_mines) {
    game_status_ = GameStatus::NOT_STARTED;
    start_time_ = 0;
    field_.clear();
    cell_status_.clear();
    cells_left_ = width * height - cells_with_mines.size();
    field_.resize(height);
    cell_status_.resize(height);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            field_[i].push_back('.');
        }
    }
    for (const auto& i : cells_with_mines) {
        field_[i.y][i.x] = '*';
    }
    for (size_t i = 0; i < field_.size(); ++i) {
        for (size_t j = 0; j < field_[i].size(); ++j) {
            size_t cnt = CountMines(i, j);
            cell_status_[i].push_back({'-', cnt, false});
        }
    }
}

void Minesweeper::OpenCell(const Cell& cell) {
    if (!StatusCheck() || cell_status_[cell.y][cell.x].mark == '?') {
        return;
    }

    if (field_[cell.y][cell.x] == '*') {
        game_status_ = GameStatus::DEFEAT;
        end_time_ = time(nullptr) - start_time_;
        for (size_t i = 0; i < field_.size(); ++i) {
            for (size_t j = 0; j < field_[i].size(); ++j) {
                cell_status_[i][j].is_opened_ = true;
                if (field_[i][j] == '*') {
                    cell_status_[i][j].mark = '*';
                }
            }
        }
        return;
    }

    std::queue<Cell> cells;
    cells.push({cell.y, cell.x});
    while (!cells.empty()) {
        size_t x = cells.front().x;
        size_t y = cells.front().y;
        cells.pop();
        if (cell_status_[x][y].is_opened_ || cell_status_[x][y].mark == '?') {
            continue;
        }
        cell_status_[x][y].is_opened_ = true;
        --cells_left_;

        if (cell_status_[x][y].mines_cnt) {
            continue;
        }

        if (x + 1 < field_.size() && field_[x + 1][y] == '.') {
            cells.push({x + 1, y});
        }
        if (y + 1 < field_[x].size() && field_[x][y + 1] == '.') {
            cells.push({x, y + 1});
        }
        if (x > 0 && field_[x - 1][y] == '.') {
            cells.push({x - 1, y});
        }
        if (y > 0 && field_[x][y - 1] == '.') {
            cells.push({x, y - 1});
        }

        if (x + 1 < field_.size() && y > 0 && field_[x + 1][y - 1] == '.') {
            cells.push({x + 1, y - 1});
        }
        if (y + 1 < field_[x].size() && x > 0 && field_[x - 1][y + 1] == '.') {
            cells.push({x - 1, y + 1});
        }
        if (x + 1 < field_.size() && y + 1 < field_[x].size() && field_[x + 1][y + 1] == '.') {
            cells.push({x + 1, y + 1});
        }
        if (y > 0 && x > 0 && field_[x - 1][y - 1] == '.') {
            cells.push({x - 1, y - 1});
        }
    }
    if (!cells_left_) {
        game_status_ = GameStatus::VICTORY;
        end_time_ = time(nullptr) - start_time_;
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (!StatusCheck()) {
        return;
    }
    if (game_status_ == GameStatus::NOT_STARTED) {
        game_status_ = GameStatus::IN_PROGRESS;
        start_time_ = time(nullptr);
    }
    if (cell_status_[cell.y][cell.x].mark == '-') {
        cell_status_[cell.y][cell.x].mark = '?';
    } else if (cell_status_[cell.y][cell.x].mark == '?') {
        cell_status_[cell.y][cell.x].mark = '-';
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return game_status_;
}

time_t Minesweeper::GetGameTime() const {
    if (game_status_ == GameStatus::NOT_STARTED) {
        return 0;
    }
    if (!StatusCheck()) {
        return end_time_;
    }
    return time(nullptr) - start_time_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    RenderedField cur_field(field_.size());
    for (size_t i = 0; i < field_.size(); ++i) {
        for (size_t j = 0; j < field_[i].size(); ++j) {
            if (cell_status_[i][j].is_opened_ && field_[i][j] != '*') {
                if (cell_status_[i][j].mines_cnt == 0) {
                    cur_field[i].push_back('.');
                } else {
                    cur_field[i].push_back(static_cast<char>(cell_status_[i][j].mines_cnt + '0'));
                }
            } else {
                cur_field[i].push_back(cell_status_[i][j].mark);
            }
        }
    }
    return cur_field;
}
