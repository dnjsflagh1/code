/******************************************************************************/
#include "stdafx.h"
#include "MainForm.h"
/******************************************************************************/

/******************************************************************************/
//class MainForm 
/******************************************************************************/

namespace MG {

	//--------------------------------------------------------------------
	MainForm::MainForm(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
	}
	//--------------------------------------------------------------------
	MainForm::~MainForm()
	{
		if (components)
		{
			delete components;
		}
	}
	//--------------------------------------------------------------------
	void MainForm::initialize()
	{

	}
	//--------------------------------------------------------------------
	void MainForm::clearLayout()
	{

	}
	//--------------------------------------------------------------------
	void MainForm::setLayout( GMLayout gl )
	{

	}
	//--------------------------------------------------------------------
	void MainForm::loadGameTextConfig()
	{

	}
	//--------------------------------------------------------------------
	void MainForm::loadMainUITextConfig()
	{

	}
	//--------------------------------------------------------------------
	void MainForm::loadAuthorityConfig()
	{

	}
	//-----------------------------------------------------------------------------
	void MainForm::log(String^msg)
	{
		BEGINDELEGATE(MainForm,log)
			ADDDELEGATEPARAMETER msg
		ENDDELEGATE

		//get time
		char timeStr[128];
		_strtime_s( timeStr, 128 );
		String ^ time   = Utility::convertAnsiToString(timeStr);

		//insert list
		ListViewItem ^ item = gcnew ListViewItem;
		item->SubItems->default[0]->Text = time;
		item->SubItems->Add(msg);
		this->a_list_msg->Items->Insert(0,item);

		if ( this->a_list_msg->Items->Count > 1000 )
		{
			this->a_list_msg->Items->RemoveAt(1000);
		}
	}
	/******************************************************************************/
	//event
	/******************************************************************************/
	System::Void MainForm::MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
	{
		//GMFormSet::LOGIN_FORM->Close();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::MainForm_Shown(System::Object^  sender, System::EventArgs^  e)
	{
		//if (GMFormSet::bGMorGuestFlag)
		//{
		//	//this->setLayout(GML_Msg_GM_Session_K);
		//	this->setLayout(GML_Msg_Post);
		//}
		//else
		//{
		//	this->setLayout(GML_Player_Move);
		//}
	}
	//-----------------------------------------------------------------------------    
	System::Void MainForm::b_navi_tree_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e)
	{
		if (e->Node->Tag)
		{
			/*String ^ str  = (String ^)e->Node->Tag;
			int     index = Utility::convertStringToInt(str);
			this->setLayout(GMLayout(index));*/
		}
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_player_search_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		c_player_search_player_search_btn->Enabled = false;
		//this->searchMainPlayerList();
		c_player_search_player_search_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_player_search_btn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pk_record_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		//this->selectForbiddenLoginList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pn_record_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		//this->selectClosedNpcList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_type_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_jump_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{

	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_type_cbx_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_cbx_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_type_cbx_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		//this->onSelectMapGroupChanged();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_cbx_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		//this->onSelectMapChanged();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_commit_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_pm_commit_btn->Enabled = false;
		//this->commitMovePlayerCommand();
		d_pm_commit_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_player_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->selectPlayerFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pc_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_pc_commit_reason_btn->Enabled = false;
		//this->commitForbiddenChatCommand();
		d_pc_commit_reason_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pk_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_pk_commit_reason_btn->Enabled = false;
		//this->commitForbiddenLoginCommand();
		d_pk_commit_reason_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pi_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_pi_commit_reason_btn->Enabled = false;
		//this->commitSendItemCommand();
		d_pi_commit_reason_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pn_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_pn_commit_reason_btn->Enabled = false;
		//this->commitSetNpcClosedCommand();
		d_pn_commit_reason_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ph_commit_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_ph_commit_btn->Enabled = false;
		//this->commitHiddenCommand();
		d_ph_commit_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_npc_search_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->searchMainNpcList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_item_search_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->searchMainItemList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_npc_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->selectNpcFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_item_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->selectItemFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mr_sensword_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->selectChatRecordFromChatForGMList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mr_commit_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_mr_commit_btn->Enabled = false;
		//this->commitReplyForGMChat();
		d_mr_commit_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mp_commit_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_mp_commit_btn->Enabled = false;
		//this->commitSetAnnouncement();
		d_mp_commit_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::a_list_msg_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::a_list_msg_DoubleClick(System::Object^  sender, System::EventArgs^  e)
	{
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_player_account_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{   
		c_player_search_player_account_edt->Enabled = c_player_search_player_account_cbx->Checked;  
	}   
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_player_charactor_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{   
		c_player_search_player_charactor_edt->Enabled =c_player_search_player_charactor_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::b_navi_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
	{

	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_am_commit_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->commitCreateGMAccount();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_am_account_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->selectGMAccountList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_am_update_reason_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->commitUpdateGMAccount();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_am_delete_reason_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->commitDeleteGMAccount();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_am_change_password_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_am_change_oldpassword_txt->Enabled = d_am_change_password_cbx->Checked;  
		d_am_change_newpassword_txt->Enabled = d_am_change_password_cbx->Checked;  
		d_am_change_newpasswor2_txt->Enabled = d_am_change_password_cbx->Checked;  

		d_am_change_oldpassword_lbl->Enabled = d_am_change_password_cbx->Checked;  
		d_am_change_newpassword_lbl->Enabled = d_am_change_password_cbx->Checked;  
		d_am_change_newpasswor2_lbl->Enabled = d_am_change_password_cbx->Checked;  
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_am_change_authority_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_am_change_authority_cbo->Enabled = d_am_change_authority_cbx->Checked;  
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ar_search_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->searchGMAccountLog();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_coord_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_pm_offset_cbo->Enabled    = d_pm_coord_rdo->Checked;  
		d_pm_coord_x_num->Enabled   = d_pm_coord_rdo->Checked;  
		d_pm_coord_y_num->Enabled   = d_pm_coord_rdo->Checked;  
		d_pm_coord_z_num->Enabled   = d_pm_coord_rdo->Checked;  
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_map_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_pm_map_type_lbl->Enabled      = d_pm_map_rdo->Checked;  
		d_pm_map_type_cbx->Enabled      = d_pm_map_rdo->Checked;  

		d_pm_map_cbx->Enabled           = d_pm_map_rdo->Checked;  
		d_pm_map_lbl->Enabled           = d_pm_map_rdo->Checked;  

		d_pm_map_jump_lbl->Enabled      = d_pm_map_rdo->Checked;  
		d_pm_map_jump_cbx->Enabled      = d_pm_map_rdo->Checked;  

		d_pm_map_width_lbl->Enabled     = d_pm_map_rdo->Checked;  
		d_pm_map_width_cbx->Enabled     = d_pm_map_rdo->Checked;  
		d_pm_map_height_lbl->Enabled    = d_pm_map_rdo->Checked;  
		d_pm_map_height_cbx->Enabled    = d_pm_map_rdo->Checked;  
		d_pm_map_x_lbl->Enabled         = d_pm_map_rdo->Checked;  
		d_pm_map_x_cbx->Enabled         = d_pm_map_rdo->Checked;  
		d_pm_map_y_lbl->Enabled         = d_pm_map_rdo->Checked;  
		d_pm_map_y_cbx->Enabled         = d_pm_map_rdo->Checked;  


		d_pm_difficulty_lbl->Enabled    = d_pm_map_rdo->Checked;  
		d_pm_difficulty_cbx->Enabled    = d_pm_map_rdo->Checked;  
		d_pm_level_lbl->Enabled         = d_pm_map_rdo->Checked;  
		d_pm_level_cbx->Enabled         = d_pm_map_rdo->Checked;  

		d_pm_is_jump_maze_lbl->Enabled  = d_pm_map_rdo->Checked;  

		if (!d_pm_map_rdo->Checked)
		{
			d_pm_map_x_lbl->Enabled         = false;
			d_pm_map_x_cbx->Enabled         = false;

			d_pm_map_y_lbl->Enabled         = false;
			d_pm_map_y_cbx->Enabled         = false;

			d_pm_map_lbl->Enabled           = false;
			d_pm_map_cbx->Enabled           = false;
		}else
		{
			d_pm_map_x_lbl->Enabled         = d_pm_is_jump_maze_lbl->Checked;
			d_pm_map_x_cbx->Enabled         = d_pm_is_jump_maze_lbl->Checked;

			d_pm_map_y_lbl->Enabled         = d_pm_is_jump_maze_lbl->Checked;
			d_pm_map_y_cbx->Enabled         = d_pm_is_jump_maze_lbl->Checked;

			d_pm_map_lbl->Enabled           = !d_pm_is_jump_maze_lbl->Checked;
			d_pm_map_cbx->Enabled           = !d_pm_is_jump_maze_lbl->Checked;
		}
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_is_jump_maze_lbl_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_pm_map_x_lbl->Enabled         = d_pm_is_jump_maze_lbl->Checked;
		d_pm_map_x_cbx->Enabled         = d_pm_is_jump_maze_lbl->Checked;

		d_pm_map_y_lbl->Enabled         = d_pm_is_jump_maze_lbl->Checked;
		d_pm_map_y_cbx->Enabled         = d_pm_is_jump_maze_lbl->Checked;

		d_pm_map_lbl->Enabled           = !d_pm_is_jump_maze_lbl->Checked;
		d_pm_map_cbx->Enabled           = !d_pm_is_jump_maze_lbl->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ms_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//deleteSelectServerFromChatLogUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mr_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//deleteSelectServerFromGMChatUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pi_id_cbo_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		//onSelectItemChangedForItemUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pi_group_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//deleteSelectPlayerFromItemUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_npc_cbo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		d_pm_movenpc_cbx->Enabled       = d_pm_tonpc_cbo->Checked; 
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_player_cbo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		d_pm_moveplayer_cbx->Enabled   = d_pm_toplayer_cbo->Checked; 
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_npc_edt_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->clearMoveToNpc();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_username_edt_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->clearMovePlayer();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pm_player_edt_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->clearMoveToPlayer();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_player_get_sel_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->selectPlayerFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_player_get_all_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->selectPlayerFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_npc_get_sel_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->selectNpcFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_npc_get_all_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->selectNpcFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_item_get_sel_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->selectItemFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_item_get_all_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->selectItemFromMainPlayerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pc_forbit_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		d_pc_time_lbl->Enabled = d_pc_forbit_rdo->Checked;
		d_pc_time_cbo->Enabled = d_pc_forbit_rdo->Checked;
		d_pc_min_lbl->Enabled = d_pc_forbit_rdo->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pc_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//refreshAllForbiddenChatList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pc_group_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		//selectForbiddenChatList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pk_forbid_lbl_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_pk_time_lbl->Enabled = d_pk_forbid_lbl->Checked;
		d_pk_time_cbo->Enabled = d_pk_forbid_lbl->Checked;
		d_pk_hour_lbl->Enabled = d_pk_forbid_lbl->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pk_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//refreshAllForbiddenLoginList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pn_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//refreshClosedNpcList();
	}   
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_msg_server_search_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//selectServerFromMainServerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_msg_server_getsel_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//selectServerFromMainServerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_msg_server_getall_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//selectServerFromMainServerList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mp_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//deleteSelectServerFromAnnoUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mpr_new_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//preCreateAnnouncementUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mpr_update_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//preUpdateAnnouncementUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mpr_delete_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//commitDeleteAnnouncement();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mpr_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//preUpdateAnnouncementUI();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mp_cycle_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_mp_cycle_gbo->Enabled = d_mp_cycle_rdo->Checked;
		d_mp_pause_ckb->Enabled = d_mp_cycle_rdo->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_mr_common_reply_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//selectReplyFromCommonWordList();
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_pg_commit_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_pg_commit_btn->Enabled = false;
		//commitGMPlayerCommand();
		d_pg_commit_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_npc_id_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		c_player_search_npc_id_edt->Enabled = c_player_search_npc_id_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_npc_name_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		c_player_search_npc_name_edt->Enabled = c_player_search_npc_name_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_item_id_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		c_player_search_item_id_edt->Enabled = c_player_search_item_id_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_player_search_item_name_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		c_player_search_item_name_edt->Enabled = c_player_search_item_name_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::c_ss_server_refresh_btn_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		c_ss_server_refresh_btn->Enabled = false;
		//refreshGameServerList();
		c_ss_server_refresh_btn->Enabled = true;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ar_si_region_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_ar_si_region_cbo->Enabled = d_ar_si_region_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ar_si_gmname_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_ar_si_gmname_cbo->Enabled = d_ar_si_gmname_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ar_si_itemtype_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_ar_si_itemtype_cbo->Enabled = d_ar_si_itemtype_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ar_si_starttime_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_ar_si_starttime_dtp->Enabled = d_ar_si_starttime_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ar_si_endtime_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_ar_si_endtime_dtp->Enabled = d_ar_si_endtime_cbx->Checked;
	}
	//-----------------------------------------------------------------------------
	System::Void MainForm::d_ar_si_search_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		d_ar_si_search_btn->Enabled = false;
		//this->commitSearchLogForSendItem();
		d_ar_si_search_btn->Enabled = true;
	}
	//----------------------------------------------------------------------------------------------
	System::Void MainForm::MainForm_SizeChanged(System::Object^  sender, System::EventArgs^  e)	
	{
		//setLayout(GMLayout(m_curr_layout));
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::c_msg_pri_add_btn_k_Click(System::Object^  sender, System::EventArgs^  e) 
	{	
		//startNewReply(c_msg_pri_region_comb_k->Text,c_msg_pri_character_comb_k->Text);
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_msg_server_list_k_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//selectServerFromMainServerListK();
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::e_msg_gmsession_server_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
	{
		//deleteSelectServerFromGMChatUI_K();
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::e_msg_gmsession_send_btn_k_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		//commitReplyForGMChatK();		
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::e_msg_gmsession_server_session_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
	{
		//m_plySelectItem = e_msg_gmsession_server_session_list_k->SelectedItems[0];
		//if (m_plySelectItem)
		//	e_msg_gmsession_l_box_k->Text = m_plySelectItem->Text;
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::c_msg_sensword_server_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
	{
		//deleteSelectServerFromSensitiveWordUI_K();
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::e_msg_gmsession_person_btn_k_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//if (!m_plySelectItem)
		//{
		//	//....msgbox
		//	return;
		//}
		//String^ region_name;

		//for (int i = 0;i != d_msg_server_list_k->Items->Count; i++)
		//{
		//	ListViewItem ^item = d_msg_server_list_k->Items[i];
		//	if (item->SubItems["d_msg_column_region_id_k"]->Text == m_plySelectItem->SubItems["e_msg_gmsession_column_region_id_k"]->Text)
		//	{
		//		region_name = item->SubItems["d_msg_column_region_name_k"]->Text;
		//	}
		//}
		//if (!region_name)
		//{
		//	return;
		//}
		//m_curr_layout = GML_Msg_Private_Reply_K;
		//setLayout(GMLayout(GML_Msg_Private_Reply_K));
		//startNewReply(region_name,m_plySelectItem->SubItems["e_msg_gmsession_column_plyname_k"]->Text);		 
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::e_msg_privatereply_tab_k_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{	
		//System::Windows::Forms::TabControl ^ tabPage = (System::Windows::Forms::TabPage)sender;
		//int i = 0;
		/*if (e_msg_privatereply_tab_k->SelectedTab)
		{
			System::Windows::Forms::TabPage^ tabPage = e_msg_privatereply_tab_k->SelectedTab;
			if (m_stChat_diction->ContainsKey(tabPage->Name))
			{
				m_stChat_diction->TryGetValue(tabPage->Name,m_curr_node);
			}
		}*/


	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::f_msg_privatereply_send_btn_k_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		//commitReplyForPrivateChat();
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::e_msg_privatereply_tab_k_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
	{
		
		/*if (m_stChat_diction->ContainsKey(e_msg_privatereply_tab_k->SelectedTab->Name))
			m_stChat_diction->Remove(e_msg_privatereply_tab_k->SelectedTab->Name);
		e_msg_privatereply_tab_k->TabPages->Remove(e_msg_privatereply_tab_k->SelectedTab);*/

	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::e_msg_privatereply_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
	{
		//selectReplyFromCommonWordListK();		
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_mp_once_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		d_mp_pause_ckb->Enabled = !d_mp_once_rdo->Checked;
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_mp_repeat_ckb_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		d_mp_play_time_end_cbo->Enabled = d_mp_repeat_ckb->Checked;
		time_distance_box->Enabled = d_mp_repeat_ckb->Checked;
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_ph_server_cmb_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		//refreshAllHiddenList();
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_ph_hidden_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		d_ph_time_lbl->Enabled = d_ph_hidden_rdo->Checked;
		d_ph_time_cbo->Enabled = d_ph_hidden_rdo->Checked;
		d_ph_hour_lbl->Enabled = d_ph_hidden_rdo->Checked;
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_pm_move_map_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		//d_pm_move_map_cbx->SelectedItem
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_pm_move_map_cbx_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//this->onSelectMapNameChanged();
	}
	//-----------------------------------------------------------------------------------------------
	System::Void MainForm::d_pi_all_player_cekb_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (d_pi_all_player_cekb->Checked)
		{
			d_pi_username_edt->Enabled = false;
		}
		else
		{
			d_pi_username_edt->Enabled = true;
		}
	}
	System::Void MainForm::d_pkl_commit_btn_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//this->commitKillNpcCommand();
	}

	System::Void MainForm::f_msg_privatereply_send_chk_k_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
	{
		/*if (f_msg_privatereply_send_chk_k->Checked)
		{
			IGMClient* gmClient = GMToolManager::getInstance().getGMClient();
			String^ content = c_msg_pri_content_edit_k->Text;
			if (String::IsNullOrEmpty(content))
			{
				gmClient->showWarningMessageByC(L"ChatForGM",L"content_null",L"content can't null!");
				f_msg_privatereply_send_chk_k->Checked = 0;
				return;
			}
			if (content->Length > 200)
			{
				gmClient->showWarningMessageByC(L"ChatForGM",L"content_over_maxlen",L"content over_maxlen!");
				f_msg_privatereply_send_chk_k->Checked = 0;
				return;
			}
		}*/
	}
	System::Void MainForm::e_msg_gmsession_person_chk_k_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		/*if (e_msg_gmsession_person_chk_k->Checked)
		{
			IGMClient* gmClient = GMToolManager::getInstance().getGMClient();
			String^ content = e_msg_gmsession_r_box_k->Text;
			if (String::IsNullOrEmpty(content))
			{
				gmClient->showWarningMessageByC(L"ChatForGM",L"content_null",L"content can't null!");
				e_msg_gmsession_person_chk_k->Checked = 0;
				return;
			}
			if (content->Length > 200)
			{
				gmClient->showWarningMessageByC(L"ChatForGM",L"content_over_maxlen",L"content over_maxlen!");
				e_msg_gmsession_person_chk_k->Checked = 0;
				return;
			}
		}*/
	}
	System::Void MainForm::d_pg_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//refreshGMPlayerList();
	}
	System::Void MainForm::d_pg_record_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		//this->selectGMPlayerList();
	}

}

