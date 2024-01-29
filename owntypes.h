#ifndef OWNTYPES_H
#define OWNTYPES_H


struct Cell {
    int x, y;
    double g, h, f;

    Cell(){}

    Cell(int x,int y){
        this->x = x, this->y = y;
    }

    friend bool operator==(const Cell& lhs, const Cell& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator!=(const Cell& lhs, const Cell& rhs) {
        return lhs.x != rhs.x || lhs.y != rhs.y;
    }

    bool operator<(const Cell& cell) {
        return this->f < cell.f;
    }

    bool operator<=(const Cell& cell) {
        return this->f <= cell.f;
    }

    bool operator>(const Cell& cell) {
        return this->f > cell.f;
    }

    bool operator>=(const Cell& cell) {
        return this->f >= cell.f;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
        os << "(x, y): " << "(" << cell.x << ", " << cell.y << ")" << std::endl;
        os << "(g, h, f): " << "(" << cell.g << ", " << cell.h << ", " << cell.f << ")" << std::endl;
        return os;
    }

};

struct Grid2d {
    std::vector<std::vector<bool>> grid;

    Grid2d(int height, int width) {
        grid.resize(height, std::vector<bool>(width, false));
    }

    void operator <<(const Grid2d& grid) {
        for (auto rows : grid.grid) {
            for (bool val : rows) {
                std::string s = val?"X ":"O ";
                std::cout << s;
            }
            std::cout << "\n";
        }
    }
};

struct Path {
    std::vector<Cell> path;

    Path() {}

    void push_back(Cell c) {
        this->path.push_back(c);
    }

    friend std::ostream& operator<<(std::ostream& os, const Path& path) {
        for (Cell p : path.path) {
            os << "(" << p.x << ", " << p.y << ") --> ";
        }
        return os;
    }
};


#endif // OWNTYPES_H
