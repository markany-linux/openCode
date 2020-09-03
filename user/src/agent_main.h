#ifndef __AGENT_MAIN_H__
#define __AGENT_MAIN_H__

#include <gtkmm/application.h>

#include "agent_window.h"
#include "button_box.h"

class AgentMain
{
public:
	AgentMain( );
	~AgentMain( );

	AgentMain(
		const AgentMain&
		) = delete;
	AgentMain& operator=(
		const AgentMain&
		) = delete;
	
	AgentMain(
		AgentMain&&
		) = delete;
	AgentMain& operator=(
		AgentMain&&
		) = delete;

	int Run( );
	void on_button_clicked(
		AgentButtonType			button_type__
		);

private:
	void on_startup( );
	bool on_delete_event(
		GdkEventAny* any_event__
		);

	static constexpr const char* kAppIdentifier = "com.gnome.opencode";

	Glib::RefPtr<Gtk::Application> app_ =
		Gtk::Application::create( kAppIdentifier );
	
	AgentWindow agent_window_{ this };
};

#endif

