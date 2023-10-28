
int calculate (int **T, int i, int j) {
  if (i <= j) return T[i][j] ;
  return 0 ;
}


// Iterative function to maximize the number of coins collected by a player,
// assuming that the opponent also plays optimally
int findMaxCoins(int* coin, int n) {
  // base case: one pot left, only one choice possible
  if (n == 1) return coin[0] ;

  // if we are left with only two pots, choose one with maximum coins
  if (n == 2) return max(coin[0], coin[1]) ;

  // create a dynamic 2D matrix to store subproblem solutions
  int** T = new int*[n];
  for (int i = 0; i < n; i++) T[i] = new int[n] ;

  // Fill the matrix in a diagonal manner, as shown below
  // Iteration 0: Fill T[][] from T[0][0] to T[n-1][n-1]
  // Iteration 1: Fill T[][] from T[0][1] to T[n-2][n-1]
  // Iteration 2: Fill T[][] from T[0][2] to T[n-3][n-1]
  // ...
  // Iteration n-2: Fill T[][] from T[0][n-2] to T[1][n-1]
  // Iteration n-1: Fill T[][] from T[0][n-1] to T[0][n-1]
  for (int iteration = 0; iteration < n; iteration++) {
    for (int i = 0, j = iteration; j < n; i++, j++) {
      // if a player chooses the front pot `i`, the opponent is left to choose
      // from [i+1, j].
      // 1. If the opponent chooses front pot `i+1`, recur for [i+2, j]
      // 2. If the opponent chooses rear pot `j`, recur for [i+1, j-1]
      int start = coin[i] + min (calculate (T, i + 2, j),
                                 calculate (T, i + 1, j - 1)) ;
      // if a player chooses rear pot `j`, the opponent is left to choose
      // from [i, j-1].
      // 1. If the opponent chooses front pot `i`, recur for [i+1, j-1]
      // 2. If the opponent chooses rear pot `j-1`, recur for [i, j-2]
      int end = coin[j] + min (calculate (T, i + 1, j - 1),
                               calculate (T, i, j - 2)) ;
      T[i][j] = max (start, end) ;
    }
  }

  int result = T[0][n - 1] ;
  // deallocate memory before returning using the delete[] operator
  for (int i = 0; i < n; i++) delete[] T[i] ;
  delete[] T ;

  return result ;
}

// Pots of gold game using dynamic programming
int main () {
  // pots of gold arranged in a line
  int coin[] = { 4, 6, 2, 3 } ;

  // total number of pots (n is even)
  int n = sizeof (coin) / sizeof (coin[0]) ;

  cout << "The Maximum coins collected by player is "
       << findMaxCoins(coin, n) ;

  return 0 ;
}
