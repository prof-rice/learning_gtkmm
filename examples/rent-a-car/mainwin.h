#ifndef MAINWIN_H
#define MAINWIN_H

#include "controller.h"
#include <gtkmm.h>

class Mainwin : public Gtk::Window
{
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_test_click();            // Add 4 vehicles & 3 renters
        void on_about_click();           // Display About dialog

        // This nested class (Main_window::ModelColums) represents
        //   the columns we'll display as part of our tree view below.
        // We define each column by instancing the TreeModelColumn
        //   template, then (in the constructor) use ColumnRecord's
        //   add() method to set up the columns.

        class ModelColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                ModelColumns() {
                    add(m_vehicle_id);
                    add(m_year);
                    add(m_make);
                    add(m_model);
                    add(m_body_style);
                    add(m_renter);
                    add(m_renter_dl);
                    add(m_renter_phone);
                }

            Gtk::TreeModelColumn<unsigned int> m_vehicle_id;
            Gtk::TreeModelColumn<Glib::ustring> m_year;
            Gtk::TreeModelColumn<Glib::ustring> m_make;
            Gtk::TreeModelColumn<Glib::ustring> m_model;
            Gtk::TreeModelColumn<Glib::ustring> m_body_style;
            Gtk::TreeModelColumn<Glib::ustring> m_renter;
            Gtk::TreeModelColumn<Glib::ustring> m_renter_dl;
            Gtk::TreeModelColumn<Glib::ustring> m_renter_phone;
        };

        // The instance we'll actually use. C programmers would
        //   probably put _columns between the } and ; above,
        //   which is permissible per the language spec.
        ModelColumns _columns;

        // The tree model holds the data to be displayed.
        // In the real world (if we were starting from scratch),
        //   our Library class would implement the Gtk::TreeModel
        //   interface, and thus serve as the tree model directly.
        // As with accounting, keeping 2 sets of books ends badly.
        // But we're easing into GUIs, so... two sets of books it is!

        Glib::RefPtr<Gtk::ListStore> _tree_model;

        // The tree view is one GUI presentation of the tree model data.
        // You can create as many different views as you like, and they
        //   will each dutifully track changes to the tree model data.

        Gtk::TreeView _tree_view;

        // The scroll window is a container that will hold our tree view.
        // Any time the entire tree view won't fit within the scroll
        //   window, the latter will create scroll bars and display only
        //   a moveable portion of the data.

        Gtk::ScrolledWindow _swindow;

        // This utility method syncs a (usually new) row from the library
        //   to the tree model, so that the tree view will display it

        void add_row(int index);

        // This utility method updates the patron name and phone number
        //   for all publications in the library, usually after a check out
        //   or check in.

        void update_rows();
    private:
        Controller _controller;               // Update display
        Gtk::Label *msg;                      // Status message display

        Gtk::ToolButton *rent_vehicle;        // Button to select 1 stick
        Gtk::Image *rent_vehicle_on_image;    //   Image when active
        Gtk::Image *rent_vehicle_off_image;   //   Image when inactive
        Gtk::ToolButton *return_vehicle;      // Button to select 2 sticks
        Gtk::Image *return_vehicle_on_image;  //   Image when active
        Gtk::Image *return_vehicle_off_image; //   Image when inactive
};
#endif 

