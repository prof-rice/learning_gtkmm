#include "mainwin.h"

Mainwin::Mainwin(){    
    auto box =  Gtk::manage(new Gtk::VBox());
    add(*box);
    auto text = Gtk::manage(new Gtk::Label("Hmm. Which button did I click?"));
        box->pack_start(*text);
    label = Gtk::manage(new Gtk::Label(" "));
        box->pack_start(*label);
    auto button = Gtk::manage(new Gtk::Button());
      button->set_vexpand(true);
      button->set_hexpand(true);
      box->pack_start(*button);
      button->set_label("Click me!!");

      //Must use signal_button_press_event to get the struct which has the button info
      //Using std::bind to pass parameters as needed in the function definition
      button->signal_button_press_event().connect(
          sigc::bind(sigc::mem_fun(*this, &Mainwin::update_mouseclick),button->get_label()/*Can be any thing as long as defined*/)
        );
    show_all();

}


Mainwin::~Mainwin(){
    delete label;
}

bool Mainwin::update_mouseclick(GdkEventButton* event, std::string name){
  /*
    According to the docs: 
    the button which was pressed or released, numbered from 1 to 5.
    Normally button 1 is the left mouse button, 2 is the middle button, and 3 is the right button.
    On 2-button mice,the middle button can often be simulated by pressing both mouse buttons together.
    */
  
  std::cout<<"Parameters passed is: "<<name<<std::endl;
  std::cout<<"Button pressed is: "<<event->button<<std::endl;
  if(event->button==3){  
        std::cout<<"Mouse button clicked id = 3 Which is right click"<<std::endl;
        label->set_text("Right Click!");  
        //true to stop other handlers from being invoked for the event. false to propagate the event further.
    return false;
  }
  else{
      std::cout<<"Mouse button clicked: "<<event->button<<std::endl;
      label->set_text("Left Click");
  }
  return true;
}