#include "proc_search_dialog.h"

#include <iostream>
#include <memory>

#include <gtkmm/box.h>
#include <gtkmm/enums.h>
#include <gtkmm/textbuffer.h>

#include "agent_data.h"
#include "agent_window.h"

std::unique_ptr< ProcSearchDialog > ProcSearchDialog::Create( )
{
	auto search_dialog = new ProcSearchDialog( );
	std::unique_ptr< ProcSearchDialog > ptr;

	ptr.reset( search_dialog );
	return ptr;
}

ProcSearchDialog::ProcSearchDialog( ) : Gtk::Dialog( "Proc Search" )
{
	std::cout << "[+] ProcSearchDialog::ProcSearchDialog()\n";
	Gtk::Box& main_vbox = *this->get_vbox();

	set_default_size( 300, 200 );
	set_resizable( false );

	main_vbox.set_border_width( 10 );

	main_vbox.pack_start( kernel_module_box_, Gtk::PACK_SHRINK );
	main_vbox.pack_start( kernel_symbol_box_, Gtk::PACK_SHRINK );

	main_vbox.pack_start( button_box_, Gtk::PACK_SHRINK, 10 );
	main_vbox.pack_start( search_result_window_, Gtk::PACK_EXPAND_WIDGET );

	button_box_.pack_start( search_button_, Gtk::PACK_SHRINK );
	button_box_.pack_start( quit_button_, Gtk::PACK_SHRINK );

	button_box_.set_halign( Gtk::ALIGN_CENTER );

	search_button_.signal_clicked( ).connect(
		sigc::mem_fun( *this, &ProcSearchDialog::on_search_button_clicked ) );

	search_result_window_.add( search_result_view_ );

	if( ( search_result_buffer_ = Gtk::TextBuffer::create( ) ) )
	{
		search_result_view_.set_editable( false );
		search_result_view_.set_can_focus( false );
		search_result_view_.set_buffer( search_result_buffer_ );
	}

	kernel_module_input_.set_text( "hid" );
	kernel_symbol_input_.set_text( "printk" );

	kernel_module_input_.signal_activate( ).connect(
		sigc::mem_fun( *this, &ProcSearchDialog::on_search_button_clicked ) );
	kernel_symbol_input_.signal_activate( ).connect(
		sigc::mem_fun( *this, &ProcSearchDialog::on_search_button_clicked ) );

	kernel_module_box_.pack_start( kernel_module_label_, Gtk::PACK_SHRINK );
	kernel_module_box_.pack_start( kernel_module_input_,
								   Gtk::PACK_EXPAND_WIDGET );
	
	kernel_symbol_box_.pack_start( kernel_symbol_label_, Gtk::PACK_SHRINK );
	kernel_symbol_box_.pack_start( kernel_symbol_input_,
								   Gtk::PACK_EXPAND_WIDGET );
	
	signal_delete_event( ).connect(
		sigc::mem_fun( *this, &ProcSearchDialog::on_delete_event ) );

	show_all_children( true );
	std::cout << "[-] ProcSearchDialog::ProcSearchDialog()\n";
}

void ProcSearchDialog::on_search_button_clicked( )
{
	if( !kernel_module_input_.get_text_length( ) &&
		!kernel_symbol_input_.get_text_length( ) )
		return;
	
	std::string search_result = data::GetProcData(
									kernel_module_input_.get_text( ),
						  			kernel_symbol_input_.get_text( ) );
	
	search_result_buffer_->set_text( search_result );
}

bool ProcSearchDialog::on_delete_event(
	GdkEventAny*
	)
{
	/// 사용자가 임의로 종료를 시도할 시 무시
	return true;
}

void ProcSearchDialog::AddQuitButtonHandler(
	AgentWindow&				agent_window__,
	AgentWindow::ProcDialogQuitButtonHandler handler_function__
)
{
	quit_button_.signal_clicked( ).connect(
		sigc::mem_fun( agent_window__, handler_function__ ) );
}
