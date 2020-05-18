#include <iostream>
#include <gtkmm.h>
#include "dialogs.h"


int main(int argc, char *argv[])
{
    // Initialize GTK
    Gtk::Main kit(argc, argv);

    //
    // Test message dialog
    //
    Dialogs::message("This is a <b>test!</b>");

    Dialogs::message("<b>Bold</b>, <u>underlined</u>, and <span fgcolor='#ff0000'>Col</span>" 
        "<span fgcolor='#00ff00'>or</span> <span fgcolor='#0000ff'>ful</span> text!", "Testing 1 2 3");
    
    //
    // Test question dialog
    //
    std::cout << Dialogs::question("Is this OK?") << std::endl;

    std::vector<std::string> buttons = {"No", "Yes", "Guess So"};
    std::cout << Dialogs::question("Karate do?", "Decide", buttons) << std::endl;

    //
    // Test input
    //
    std::cout << Dialogs::input("What is your name?") << std::endl;

    std::cout << Dialogs::input("Where are you from?", "Better Question") << std::endl;

    std::cout << Dialogs::input("Who's your tailor?", "Best Question", "Franz Reichelt") << std::endl;

    std::cout << Dialogs::input("How's the styling?", "Select Cancel", "Rad", "Cancelled") << std::endl;

    //
    // Test image
    //
    Dialogs::image("moon.jpg", "Luna", "Or Selene if you're from ancient Greece");
    Dialogs::image("science.svg", "Science", "It rocks!");

    return EXIT_SUCCESS;
}
