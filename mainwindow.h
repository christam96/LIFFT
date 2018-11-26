#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>


// The class mainwindow inherits from Gtk::Window
class mainwindow : public Gtk::Window
{
	// Constructor and destructor
public:    
	mainwindow();
	virtual					~mainwindow();

protected:
	void                    on_button_load();

	//Member widgets:
	Gtk::Button             buttonLoad;
	Gtk::Button             quitButton;
	Gtk::Grid               mainGrid;

};


#endif // MAINWINDOW_H
