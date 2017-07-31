#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <string>

class Arena;

class Player
{
  public:
        // Constructor
    Player(Arena *ap, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    std::string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;

    int    computeDanger(int r, int c) const;
};

#endif //PLAYER_INCLUDED