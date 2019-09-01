#include <iostream>
#include <vector>

using std::vector;

// 0 for no stress test
// 1 for random stress test
// 2 for input stress test
int stress_test = 2;

int lcs2(vector<int> &a, vector<int> &b) {

  // Use the vector sizes to set up memoization array and array to track previous values
  auto m = a.size(), n = b.size();
  int distances[m+1][n+1], previous[m+1][n+1][2];

  // Fill out first row/column with index
  for (size_t i = 0; i <= m; i++){
    distances[i][0] = i; // "Deletion" of first string
    previous[i][0][0] = 0;
    previous[i][0][1] = 0;
  }
  for (size_t j = 0; j <= n; j++){
    distances[0][j] = j; // "Insertion" into first string
    previous[0][j][0] = 0;
    previous[0][j][1] = 0;
  }

  size_t i = 0, j = 0;
  // Fill out rest of matrices
  for (size_t k = 0; k < (m*n); k++){

    // Instead of nested for loop, condense to one vector of size mxn
    i = (k/n) + 1;   //row
    j = (k % n) + 1; //col
    
    // If in top right, go up
    if (i < j){
      if (distances[i-1][j] < distances[i-1][j-1]){
	distances[i][j] = distances[i-1][j] + 1;
	previous[i][j][0] = i-1;
	previous[i][j][1] = j;
      }
      else{
	distances[i][j] = distances[i-1][j-1] + 1;
	previous[i][j][0] = i-1;
	previous[i][j][1] = j-1;
      }
    }
    // If bottom left, go right
    else if (i > j){
      if (distances[i][j-1] < distances[i-1][j-1]){
	distances[i][j] = distances[i][j-1] + 1;
	previous[i][j][0] = i;
	previous[i][j][1] = j-1;
      }
      else{
	distances[i][j] = distances[i-1][j-1] + 1;
	previous[i][j][0] = i-1;
	previous[i][j][1] = j-1;
      }
    }
    // If on diagonal, go to diagonal
    else {
      distances[i][j] = distances[i-1][j-1] + 1;
      previous[i][j][0] = i-1;
      previous[i][j][1] = j-1;
    }
    // Check for match
    if (a[i-1] == b[j-1]){
      distances[i][j] = distances[i-1][j-1];
      previous[i][j][0] = i-1;
      previous[i][j][1] = j-1;
    }
  }

  // Show matrices 
  if(stress_test != 0){
    for (size_t i = 0; i <= m; i++){
      for (size_t j = 0; j <= n; j++){
	std::cout << previous[i][j][0] << "," << previous[i][j][1] << " ";
      }
      std::cout << std::endl;
    }
    for (size_t i = 0; i <= m; i++){
      for (size_t j = 0; j <= n; j++){
	std::cout << distances[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  // Find the chain that was used to get the minimum distance, and count the number of matches here
  int row = m, col = n, temp_col, temp_row, match = 0;
  while (row != 0 || col != 0){
    temp_row = row;
    temp_col = col;    
    std::cout << temp_row << "," << temp_col << " ";
    row = previous[temp_row][temp_col][0];
    col = previous[temp_row][temp_col][1];
    if (distances[temp_row][temp_col] == distances[row][col]){
      match++;
    }
  }
  
  return match;
}

int main() {

  vector<int> a, b;
  
  // For testing, generate random strings and check distance manually by
  // printing output
  if (stress_test == 1){
      srand(time(NULL));

      size_t n = rand() % 10, m = rand() % 10;
      for (size_t i = 0; i < n; i++) {
	a.push_back(rand() % 10);
	std::cout << a[i] << " ";
      }
      std::cout << std::endl;
      
      for (size_t i = 0; i < m; i++) {
	b.push_back(rand() % 10);
	std::cout << b[i] << " ";
      }
      std::cout << std::endl;
  }
  // User input
  else{
    size_t n;
    std::cin >> n;
    vector<int> temp_a(n);
    for (size_t i = 0; i < n; i++) {
      std::cin >> temp_a[i];
    }
    for (size_t i = 0; i < n; i++) {
      a.push_back(temp_a[i]);
    }
    
    size_t m;
    std::cin >> m;
    vector<int> temp_b(m);
    for (size_t i = 0; i < m; i++) {
      std::cin >> temp_b[i];
    }
    for (size_t i = 0; i < m; i++) {
      b.push_back(temp_b[i]);
    }
  }

  std::cout << lcs2(a, b) << std::endl;
}
