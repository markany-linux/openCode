#ifndef __AGENT_MAIN_H__
#define __AGENT_MAIN_H__

#include <glibmm/refptr.h>
#include <gtkmm/application.h>

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

private:
	static constexpr const char* kAppIdentifier = "com.gnome.opencode";

	Glib::RefPtr<Gtk::Application> app_ =
		Gtk::Application::create( kAppIdentifier );
};

#endif

