// No longer required
// #include <iostream>

// Add dialogs (and implicitly gtkmm)
#include "dialogs.h"
#include <sstream>

int main(int argc, char *argv[]) {
    int num;        // The number to be guessed
    int guess = 0;  // The user's guess
    std::string text;    // Temp for holding user's input

    srand ( time(NULL) );
    num = rand() % 100 + 1;

    // Initialize gtkmm, add Dialogs and a title string
    Gtk::Main kit(argc, argv);
    std::string title = "Guess a Number";
    Dialogs::image("guess_a_number.png", title);

    while (num != guess) {

      // std::cout << "What is your guess (0 to 100): ";
      // std::cin >> guess;
      text = Dialogs::input("What is your guess (between 0 and 100):", title);
      if (text == "CANCEL") break;
      std::istringstream ist{text};
      ist >> guess;

      // if (guess < 1 || guess > 100) cerr << "Out of range!" << endl;
      // else if (guess > num) cout << "Too high!" << endl;
      // else if (guess < num) cout << "Too low!" << endl;
      // else cout << "WINNER!" << endl;
      if (guess < 1 || guess > 100) title = "Out of range!";
      else if (guess > num) title = "Too high!";
      else if (guess < num) title = "Too low!";
      else Dialogs::message("WINNER!", "Game Over");
    }
}
