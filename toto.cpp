
std::vector<std::vector<int> > Game::swipe_base(std::vector<std::vector<int> > givenGrid) const
// swipes the given grid in the up direction, doing all the necessary additions
{

  for (int columnNbr = 0; columnNbr < size; columnNbr++)
  {
    //we start by putting every tile up
    for (int lineNbr = 0; lineNbr < size; lineNbr++)
    {
      int counter = 0;
      while ((givenGrid[lineNbr][columnNbr] == 0) && (counter < size))
      {
        counter += 1;

        int nbrNonZero = 0;           //corresponds to the numbers of non-zero values in the columnPart
        for (int k = lineNbr; k < size; k++)
        {
          if (givenGrid[k][columnNbr] != 0)
          {
            nbrNonZero++;
          }
        }
        if (nbrNonZero != 0)
        {
          for (int remainingLine = lineNbr; remainingLine < size-1; remainingLine++)
          {
            givenGrid[remainingLine][columnNbr] = givenGrid[remainingLine+1][columnNbr];
          }
          givenGrid[size-1][columnNbr] = 0;
        }
      }
    }

    // now we do the additions
    for (int lineNbr = 0; lineNbr < size-1; lineNbr++)
    {
      if (givenGrid[lineNbr][columnNbr] == givenGrid[lineNbr+1][columnNbr])
      {
        givenGrid[lineNbr][columnNbr] *= 2;
        for (int remainingLine = lineNbr+1; remainingLine < size-1; remainingLine++)
        {
          givenGrid[remainingLine][columnNbr] = givenGrid[remainingLine+1][columnNbr];
        }
        givenGrid[size-1][columnNbr] = 0;
      }
    }
  }
  return (givenGrid); // A CHANGER
}
