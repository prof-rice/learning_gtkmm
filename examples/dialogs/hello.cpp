#include <gtkmm.h>

int main(int argc, char *argv[])
{
    // Initialize GTK for dialogs – we’ll use a factory for apps 
    Gtk::Main kit(argc, argv);

    // Create a simple dialog containing "Hello, World!"
    Gtk::MessageDialog *dialog = new Gtk::MessageDialog{"Hello, World!"};

    // Turn control over to gtkmm until the user clicks OK
    dialog->run();
}
