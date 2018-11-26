#include "mainwindow.h"
#include <iostream>


// Constructor for the main Window in order to build the user interface
mainwindow::mainwindow()
{
	// Initialize the main window and hide the title bar
	this->set_border_width(10);

	// Add the load button
	buttonLoad.add_label("Load file");
	buttonLoad.set_size_request(250,75);
	buttonLoad.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::on_button_load));
	mainGrid.attach(buttonLoad,0,0,1,1);

	// Add the Quit button
	quitButton.add_label("Quit");
	quitButton.set_size_request(250,75);
	quitButton.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::close));
	mainGrid.attach(quitButton,0,1,1,1);

	// Display the main grid in the main window
	mainGrid.show_all();

	// Insert the grid in the main window
	add(mainGrid);
}


// Destructor of the class
mainwindow::~mainwindow()
{}


void mainwindow::on_button_load()
{
	// Create the dialog box FileChooser
	Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

	//Add filters, so that only certain file types can be selected:
	Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog.add_filter(filter_text);

	Glib::RefPtr<Gtk::FileFilter> filter_cpp = Gtk::FileFilter::create();
	filter_cpp->set_name("C/C++ files");
	filter_cpp->add_mime_type("text/x-c");
	filter_cpp->add_mime_type("text/x-c++");
	filter_cpp->add_mime_type("text/x-c-header");
	dialog.add_filter(filter_cpp);

	Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog.add_filter(filter_any);

	// Present dialog box and wait for user response:
	int response = dialog.run();

	// Handle the user response:
	switch(response)
	{
	case(Gtk::RESPONSE_CANCEL):
	{
		// User cancel the operation
		std::cout << "Cancel clicked." << std::endl;
		break;
	}
	case(Gtk::RESPONSE_OK):
	{
		// The user selected a file
		std::cout << "Open clicked." << std::endl;
		std::string filename = dialog.get_filename();
		std::cout << "File selected: " <<  filename << std::endl;
		break;
	}
	default:
	{
		// If the user closes the dialog box
		std::cout << "Unexpected button clicked." << std::endl;
		break;
	}
	}
}
