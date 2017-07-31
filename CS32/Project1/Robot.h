#ifndef ROBOT_INCLUDED
#define ROBOT_INCLUDED

class Arena;

class Robot
{
  public:
        // Constructor
    Robot(Arena* ap, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
};


#endif //ROBOT_INCLUDED