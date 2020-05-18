#include <iostream>

int main() {
    int num;        // The number to be guessed
    int guess = 0;  // The user's guess

    srand ( time(NULL) );
    num = rand() % 100 + 1;

    while (num != guess) {
      std::cout << "What is your guess (0 to 100): ";
      std::cin >> guess; 
      if (guess < 1 || guess > 100) std::cerr << "Out of range!" << std::endl;
      else if (guess > num) std::cout << "Too high!" << std::endl;
      else if (guess < num) std::cout << "Too low!" << std::endl;
      else std::cout << "WINNER!" << std::endl;
    }
}
