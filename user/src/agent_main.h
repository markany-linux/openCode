#ifndef __AGENT_MAIN_H__
#define __AGENT_MAIN_H__

#include "agent_data.h"
#include "agent_window.h"
#include "button_box.h"

namespace Gtk {
class Application;
}

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
	static constexpr const char* kAppIdentifier = "com.gnome.opencode";
	static const std::string kConfigFilePath;

	void on_startup( );
	bool on_delete_event(
		GdkEventAny* any_event__
		);

	Glib::RefPtr<Gtk::Application> app_ =
		Gtk::Application::create( kAppIdentifier );
	
	AgentWindow agent_window_{ this };
	AgentData agent_data_{ kConfigFilePath };
};

#endif

