#include "main_window.h"
#include <gtkmm.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // Process program arguments - "mavmart -g" will launch GUI
    // (This is a very simple parser. Notably, it cannot handle
    //  merged single-character options such as "-ga"!)

    bool _gui = true;

    for(int i=1; i<argc; ++i) { // Remember, argv[0] is "mavmart"!
        std::string opt = std::string{argv[i]};
        if (opt == "-g" || opt == "--gui") _gui = true;
        else if (opt == "-c" || opt == "--cli") _gui = false;
        // Invalid argument OR -h / --help (same response)
        else {
            std::cerr << "Usage: " << argv[0] << " [OPTION]" << R"(
Manage a MavMart store.

OPTION:
    -c, --cli       Launch a CLI
    -g, --gui       Launch a GUI (default)
    -h, --help      Show this help message
)";
            exit(!(opt == "-h" || opt == "--help"));
        } 
    }

    // Run the GUI version if -g or --gui was specified...
    if (_gui) {
        auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.paint");
        Main_window win;
        return app->run(win);

    // ...otherwise, run the CLI version
    } else {
        Controller controller;
        controller.cli();
        return 0;
    }
}
