// For demos, include all of gtkmm with #include <gtkmm.h>
// For production, include only widgets you need, e.g., #include <gtkmm/dialog.h>
#include <gtkmm.h>

int main(int argc, char *argv[])
{
    // Initialize gtkmm. Much of gtkmm is in the Gtk namespace.
    // For trivial programs, you can also do this:
    //     Gtk::Main kit(argc, argv);
    auto app = Gtk::Application::create(argc, argv, "lg.hello.world");

    // Create a simple dialog containing "Hello, World!"
    Gtk::MessageDialog dialog("Hello, World!");

    // Turn control over to gtkmm until the user clicks OK
    dialog.run();
}
