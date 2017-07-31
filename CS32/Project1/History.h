#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

class History
{
  public:
    History(int nRows, int nCols);
	~History();
    bool record(int r, int c);
    void display() const;

  private:
	int** m_grid;
	int m_cols;
	int m_rows;
};


#endif //HISTORY_INCLUDED