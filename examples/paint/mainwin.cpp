#include "mainwin.h"
#include "canvas.h"
#include <istream>
#include <ostream>
#include <fstream>
#include <exception>

Mainwin::Mainwin() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////
    set_title("CSE1325 Paint");
    set_default_size(800, 600);

    // 
    // V B O X -- The window contains a vertical box
    //
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box{Gtk::ORIENTATION_VERTICAL, 0});
    add(*vbox);

    // 
    // M E N U -- The VBox contains a menu at the top
    //
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar{});
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem{"_File", true});
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu{});
    menuitem_file->set_submenu(*filemenu);

    //         N E W
    // Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem{"_New", true});
    menuitem_new->signal_activate().connect(sigc::mem_fun(*this,
        &Mainwin::on_new_click));
    filemenu->append(*menuitem_new);

    //         O P E N
    // Append Open to the File menu
    Gtk::MenuItem *menuitem_open = 
        Gtk::manage(new Gtk::MenuItem{"_Open", true});
    menuitem_open->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_open_click));
    filemenu->append(*menuitem_open);

    //         S A V E
    // Append Save to the File menu
    Gtk::MenuItem *menuitem_save = 
        Gtk::manage(new Gtk::MenuItem{"_Save", true});
    menuitem_save->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_save_click));
    filemenu->append(*menuitem_save);

    //         S A V E   A S
    // Append Save As to the File menu
    Gtk::MenuItem *menuitem_save_as = 
        Gtk::manage(new Gtk::MenuItem{"Save _As", true});
    menuitem_save_as->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_save_as_click));
    filemenu->append(*menuitem_save_as);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem{"_Quit", true});
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, 
        &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    //     E D I T
    // Create an Edit menu and add to the menu bar
    Gtk::MenuItem *menuitem_edit = 
        Gtk::manage(new Gtk::MenuItem{"_Edit", true});
    menubar->append(*menuitem_edit);
    Gtk::Menu *editmenu = Gtk::manage(new Gtk::Menu{});
    menuitem_edit->set_submenu(*editmenu);

    //         U N D O
    // Append Undo to the Edit menu
    Gtk::MenuItem *menuitem_undo = Gtk::manage(new Gtk::MenuItem{"_Undo", true});
    menuitem_undo->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_undo_click));
    editmenu->append(*menuitem_undo);

    //     P E N
    // Create a Pen menu and add to the menu bar
    Gtk::MenuItem *menuitem_pen = Gtk::manage(new Gtk::MenuItem{"_Pen", true});
    menubar->append(*menuitem_pen);
    Gtk::Menu *penmenu = Gtk::manage(new Gtk::Menu{});
    menuitem_pen->set_submenu(*penmenu);

    //         C O L O R
    // Append Color to the Pen menu
    Gtk::MenuItem *menuitem_color = Gtk::manage(new Gtk::MenuItem{"_Color", true});
    menuitem_color->signal_activate().connect(sigc::mem_fun(*this,
        &Mainwin::on_color_click));
    penmenu->append(*menuitem_color);

    //         W I D T H
    // Append Width to the Pen menu
    Gtk::MenuItem *menuitem_width = Gtk::manage(new Gtk::MenuItem{"_Width", true});
    menuitem_width->signal_activate().connect(sigc::mem_fun(*this,
        &Mainwin::on_width_click));
    penmenu->append(*menuitem_width);

    //        D A S H   P A T T E R N S
    // Append dash patterns to the Pen menu
    Gtk::MenuItem *menuitem_dash_pattern = 
        Gtk::manage(new Gtk::MenuItem{"_Dash Pattern", true});
    menuitem_dash_pattern->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_dash_pattern_click));
    penmenu->append(*menuitem_dash_pattern);

    //         P E N   M O D E : S E G M E N T
    // Append Segment to the Pen menu
    Gtk::MenuItem *menuitem_pen_mode_segment = 
        Gtk::manage(new Gtk::MenuItem{"Line _Segments", true});
    menuitem_pen_mode_segment->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_pen_mode_segment_click));
    penmenu->append(*menuitem_pen_mode_segment);

    //         P E N   M O D E : C O N T I G U O U S
    // Append Contiguous to the Pen menu
    Gtk::MenuItem *menuitem_pen_mode_contiguous = 
        Gtk::manage(new Gtk::MenuItem{"_Contiguous Lines", true});
    menuitem_pen_mode_contiguous->signal_activate().connect(
        sigc::mem_fun(*this,&Mainwin::on_pen_mode_contiguous_click));
    penmenu->append(*menuitem_pen_mode_contiguous);

    //         P E N   M O D E : F R E E H A N D
    // Append Freehand to the Pen menu
    Gtk::MenuItem *menuitem_pen_mode_freehand = 
        Gtk::manage(new Gtk::MenuItem{"_Freehand", true});
    menuitem_pen_mode_freehand->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_pen_mode_freehand_click));
    penmenu->append(*menuitem_pen_mode_freehand);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = 
        Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);
    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    // /////////////
    // T O O L B A R -- Add a toolbar to the vertical box below the menu
    //
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     N E W   D R A W I N G
    // Start a new drawing
    Gtk::ToolButton *new_button = Gtk::manage(
        new Gtk::ToolButton(Gtk::Stock::NEW));
    new_button->set_tooltip_markup("Start a new drawing");
    new_button->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_new_click));
    toolbar->append(*new_button);

    //     O P E N   D R A W I N G
    // Open a drawing from disk
    Gtk::ToolButton *open_button = 
        Gtk::manage(new Gtk::ToolButton(Gtk::Stock::OPEN));
    open_button->set_tooltip_markup("Open a drawing");
    open_button->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_open_click));
    toolbar->append(*open_button);

    //     S A V E   D R A W I N G
    // Save a drawing to the default filename
    Gtk::ToolButton *save_button = 
        Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE));
    save_button->set_tooltip_markup("Save drawing to the default filename");
    save_button->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_save_click));
    toolbar->append(*save_button);

    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);

    //     P E N   C O L O R
    // Add a new pen color icon
    Gtk::Image *button_pen_color_image = 
        Gtk::manage(new Gtk::Image("select_pen_color.png"));
    Gtk::ToolButton *button_pen_color = 
        Gtk::manage(new Gtk::ToolButton(*button_pen_color_image));
    button_pen_color->set_tooltip_markup("Select pen color");
    button_pen_color->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_color_click));
    toolbar->append(*button_pen_color);

    //     P E N   W I D T H
    // Add a set pen width icon
    Gtk::Image *button_pen_width_image = 
        Gtk::manage(new Gtk::Image("select_pen_width.png"));
    Gtk::ToolButton *button_pen_width = 
        Gtk::manage(new Gtk::ToolButton(*button_pen_width_image));
    button_pen_width->set_tooltip_markup("Select pen width");
    button_pen_width->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_width_click));
    toolbar->append(*button_pen_width);

    //     P E N   M O D E : S E G M E N T
    // Add a toggle button to enable segment pen mode
    Gtk::Image *segment_image = Gtk::manage(new Gtk::Image("segment.png"));
    Gtk::RadioToolButton* button_segment = Gtk::manage(new Gtk::RadioToolButton(*segment_image));
    button_segment->set_tooltip_markup("Draw line segments");
    auto group = button_segment->get_group();
    button_segment->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_pen_mode_segment_click));
    toolbar->append(*button_segment);

    //     P E N   M O D E : C O N T I G U O U S
    // Add a toggle button to enable contiguous pen mode
    Gtk::Image *contiguous_image = 
        Gtk::manage(new Gtk::Image("contiguous.png"));
    Gtk::RadioToolButton* button_contiguous = 
        Gtk::manage(new Gtk::RadioToolButton(*contiguous_image));
    button_contiguous->set_tooltip_markup("Draw contiguous lines");
    button_contiguous->set_group(group);
    button_contiguous->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_pen_mode_contiguous_click));
    toolbar->append(*button_contiguous);

    //     P E N   M O D E : F R E E H A N D
    // Add a toggle button to enable freehand pen mode
    Gtk::Image *freehand_image = Gtk::manage(new Gtk::Image("freehand.png"));
    Gtk::RadioToolButton *button_freehand = 
        Gtk::manage(new Gtk::RadioToolButton(*freehand_image));
    button_freehand->set_tooltip_markup("Scribble");
    button_freehand->set_group(group);
    button_freehand->signal_clicked().connect(
        sigc::mem_fun(*this, &Mainwin::on_pen_mode_freehand_click));
    toolbar->append(*button_freehand);

    // /////////////
    // C A N V A S -- The VBox contains a Canvas (DrawingArea) as its next member
    //
    canvas = Gtk::manage(new Canvas{*this});
    vbox->pack_start(*canvas);

    vbox->show_all();

    // /////////////
    // S I G N A L S 
    // /////////////

    // Allow the canvas to determine if closing is permitted
    signal_delete_event().connect(sigc::mem_fun(canvas, &Canvas::on_my_delete_event));

   // Set for segment mode initially
   on_pen_mode_segment_click();
}

Mainwin::~Mainwin() { }

// /////////////////////////////
// S I G N A L   H A N D L E R S
// /////////////////////////////

////////////
// File I/O

//
// The user wants a clean, unmarked canvas
//
void Mainwin::on_new_click() {
    canvas->new_drawing();
    canvas->queue_draw(); // refresh the DrawingArea with loaded drawing
}

//
// The user wants to save the current drawing to the default filename
//
void Mainwin::on_save_click() {
    std::ofstream ofs{canvas->get_filename()};
    canvas->save(ofs);
}

//
// The user wants to save the current drawing to a new filename
//
void Mainwin::on_save_as_click() {
    Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    auto filter_ctp = Gtk::FileFilter::create();
    filter_ctp->set_name("CTP files");
    filter_ctp->add_pattern("*.ctp");
    dialog.add_filter(filter_ctp);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename(canvas->get_filename());

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Save", 1);

    int result = dialog.run();

    // Obtain permission to overwrite existing file, if needed
    if (std::ifstream{dialog.get_filename()}) {
        Gtk::MessageDialog dialog("File exists - overwrite?", true, 
            Gtk::MessageType::MESSAGE_WARNING, Gtk::ButtonsType::BUTTONS_YES_NO);
        dialog.set_transient_for(*this);
        if (dialog.run() != Gtk::RESPONSE_YES) return;
    }

    //Handle the response:
    if (result == 1) {
        canvas->set_filename(dialog.get_filename());
        on_save_click();
  }
}
//
// The user wants to open a drawing from the filesystem
//
void Mainwin::on_open_click() {
    Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    auto filter_ctp = Gtk::FileFilter::create();
    filter_ctp->set_name("CTP files");
    filter_ctp->add_pattern("*.ctp");
    dialog.add_filter(filter_ctp);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename(canvas->get_filename());

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Open", 1);

    int result = dialog.run();

    if (result == 1) {
        try {
            std::ifstream ifs{dialog.get_filename(), std::ifstream::in};
            canvas->load(ifs);
            canvas->queue_draw(); // refresh the DrawingArea with loaded drawing
            canvas->set_filename(dialog.get_filename());
        } catch (std::exception& e) {
            std::string msg = "Unable to open <b>" + dialog.get_filename() + "</b>: " + e.what();
            Gtk::MessageDialog dialog("Error on File Open", true, Gtk::MessageType::MESSAGE_ERROR);
            dialog.set_secondary_text(msg, true);
            dialog.run();
        }
    }
}

void Mainwin::on_quit_click() {
    close();  // This is equivalent to clicking the 'x' in the window manager
              // (Otherwise, we might use hide() instead.)
}


// /////////
// Edit Menu
//
// The user wants to undo the last operation
//
void Mainwin::on_undo_click() {
    canvas->undo();
}


// ////////
// Pen Menu
void Mainwin::on_color_click() {
  Gtk::ColorChooserDialog dialog("Please choose a color");
  dialog.set_transient_for(*this);  // Avoid the “discouraging” warning

  dialog.set_rgba(canvas->get_pen_color());  // Set the current color as default

  int result = dialog.run();

  if (result == Gtk::RESPONSE_OK)
      canvas->set_pen_color(dialog.get_rgba());
}

void Mainwin::on_width_click() {
    // Create a custom dialog for setting line width
    Gtk::Dialog dialog{"Select Pen Width", *this};

    // The lower widget is a slider (Gtk "scale"), so the user can mouse the new width
    Gtk::Scale scale{};
    scale.set_range(1.0,10.0);
    scale.set_value(canvas->get_pen_width());  // Preset scale to current width
    scale.show();
    dialog.get_vbox()->pack_start(scale);

    // OK and Cancel buttons
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.set_default_response(1);

    // Show the dialog, get the button pressed
    dialog.show_all();
    int result = dialog.run();
    if (result == 1) canvas->set_pen_width(scale.get_value());
    dialog.close();
}

void Mainwin::on_dash_pattern_click() {
    Gtk::Dialog dialog{"Select Dash Pattern", *this};

    Gtk::ComboBoxText c_dash;
    c_dash.set_size_request(160);
    c_dash.append("Solid Line");
    c_dash.append("Alternating");
    c_dash.append("Mostly Dash");
    c_dash.append("Dash Dot");
    dialog.get_vbox()->pack_start(c_dash, Gtk::PACK_SHRINK);

    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.show_all();
    int result = dialog.run();

    if (result == 1) canvas->set_pen_dash(c_dash.get_active_row_number());
    dialog.close();
}

void Mainwin::on_pen_mode_segment_click() {
    canvas->set_pen_mode(Canvas::PEN_MODE_SEGMENT);
}

void Mainwin::on_pen_mode_contiguous_click() {
    canvas->set_pen_mode(Canvas::PEN_MODE_CONTIGUOUS);
}

void Mainwin::on_pen_mode_freehand_click() {
    canvas->set_pen_mode(Canvas::PEN_MODE_FREEHAND);
}


// /////////
// Help Menu

void Mainwin::on_about_click() {
    Gtk::AboutDialog dialog{};
    dialog.set_transient_for(*this);
    dialog.set_program_name("CSE1325 Paint");
    auto logo = Gdk::Pixbuf::create_from_file("logo.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 2.0.0");
    dialog.set_copyright("Copyright 2017-2018");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"George F. Rice"};
    dialog.set_authors(authors);
    std::vector< Glib::ustring > artists = {"color by Saeful Muslim from the Noun Project",
                                            "Pen by iconsmind.com from the Noun Project",
                                            "Paint Palette by елизавета екимова from the Noun Project"};
    dialog.set_artists(artists);
    dialog.run();
}



