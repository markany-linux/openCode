#include <iostream>
#include <gtkmm/application.h>

#include "main_window.h"

int main(
	int							argc,
	char**						argv
	)
{
	std::cout << "[+] main()\n";
	auto app = Gtk::Application::create( argc, argv, "org.gtkmm.opencode" );

	std::vector<ButtonInfo> button_list{};

	button_list.emplace_back( ButtonInfo{.text = "Hello"} );
	button_list.emplace_back( ButtonInfo{.text = "World"} );
	button_list.emplace_back( ButtonInfo{.text = "Everone"} );

	MainWindow main_window{"Hello World!", button_list, app};

	return app->run( main_window );
}
