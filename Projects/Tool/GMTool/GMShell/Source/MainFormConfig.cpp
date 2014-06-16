
/******************************************************************************/
#include "stdafx.h"
#include "MainForm.h"
/******************************************************************************/

namespace MG {

    /******************************************************************************/
    //class MainForm 
    /******************************************************************************/
    //-----------------------------------------------------------------------------
    void MainForm::InitializeComponent(void)
    {
		System::Windows::Forms::TreeNode^  treeNode1 = (gcnew System::Windows::Forms::TreeNode(L"move"));
		System::Windows::Forms::TreeNode^  treeNode2 = (gcnew System::Windows::Forms::TreeNode(L"chat"));
		System::Windows::Forms::TreeNode^  treeNode3 = (gcnew System::Windows::Forms::TreeNode(L"kick"));
		System::Windows::Forms::TreeNode^  treeNode4 = (gcnew System::Windows::Forms::TreeNode(L"item"));
		System::Windows::Forms::TreeNode^  treeNode5 = (gcnew System::Windows::Forms::TreeNode(L"npc"));
		System::Windows::Forms::TreeNode^  treeNode6 = (gcnew System::Windows::Forms::TreeNode(L"hidden"));
		System::Windows::Forms::TreeNode^  treeNode7 = (gcnew System::Windows::Forms::TreeNode(L"gm_player"));
		System::Windows::Forms::TreeNode^  treeNode8 = (gcnew System::Windows::Forms::TreeNode(L"state"));
		System::Windows::Forms::TreeNode^  treeNode9 = (gcnew System::Windows::Forms::TreeNode(L"kill"));
		System::Windows::Forms::TreeNode^  treeNode10 = (gcnew System::Windows::Forms::TreeNode(L"player", gcnew cli::array< System::Windows::Forms::TreeNode^  >(9) {treeNode1, 
			treeNode2, treeNode3, treeNode4, treeNode5, treeNode6, treeNode7, treeNode8, treeNode9}));
		System::Windows::Forms::TreeNode^  treeNode11 = (gcnew System::Windows::Forms::TreeNode(L"post"));
		System::Windows::Forms::TreeNode^  treeNode12 = (gcnew System::Windows::Forms::TreeNode(L"senstive"));
		System::Windows::Forms::TreeNode^  treeNode13 = (gcnew System::Windows::Forms::TreeNode(L"reply"));
		System::Windows::Forms::TreeNode^  treeNode14 = (gcnew System::Windows::Forms::TreeNode(L"message", gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) {treeNode11, 
			treeNode12, treeNode13}));
		System::Windows::Forms::TreeNode^  treeNode15 = (gcnew System::Windows::Forms::TreeNode(L"post"));
		System::Windows::Forms::TreeNode^  treeNode16 = (gcnew System::Windows::Forms::TreeNode(L"senstive"));
		System::Windows::Forms::TreeNode^  treeNode17 = (gcnew System::Windows::Forms::TreeNode(L"reply"));
		System::Windows::Forms::TreeNode^  treeNode18 = (gcnew System::Windows::Forms::TreeNode(L"gmsession"));
		System::Windows::Forms::TreeNode^  treeNode19 = (gcnew System::Windows::Forms::TreeNode(L"message", gcnew cli::array< System::Windows::Forms::TreeNode^  >(4) {treeNode15, 
			treeNode16, treeNode17, treeNode18}));
		System::Windows::Forms::TreeNode^  treeNode20 = (gcnew System::Windows::Forms::TreeNode(L"state"));
		System::Windows::Forms::TreeNode^  treeNode21 = (gcnew System::Windows::Forms::TreeNode(L"server", gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) {treeNode20}));
		System::Windows::Forms::TreeNode^  treeNode22 = (gcnew System::Windows::Forms::TreeNode(L"manager"));
		System::Windows::Forms::TreeNode^  treeNode23 = (gcnew System::Windows::Forms::TreeNode(L"log"));
		System::Windows::Forms::TreeNode^  treeNode24 = (gcnew System::Windows::Forms::TreeNode(L"account", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {treeNode22, 
			treeNode23}));
		this->a_main_pal = (gcnew System::Windows::Forms::Panel());
		this->a_pal_full = (gcnew System::Windows::Forms::Panel());
		this->b_main_pal_right = (gcnew System::Windows::Forms::Panel());
		this->b_main_tab = (gcnew System::Windows::Forms::TabControl());
		this->c_palyer_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_pal = (gcnew System::Windows::Forms::Panel());
		this->c_palyer_main_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_tab = (gcnew System::Windows::Forms::TabControl());
		this->c_player_move_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_move_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pm_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pm_position_gbo_k = (gcnew System::Windows::Forms::GroupBox());
		this->d_pm_jump_pt_lab = (gcnew System::Windows::Forms::Label());
		this->d_pm_map_name_lab = (gcnew System::Windows::Forms::Label());
		this->d_pm_move_map_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_position_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pm_level_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_level_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_difficulty_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_difficulty_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_is_jump_maze_lbl = (gcnew System::Windows::Forms::CheckBox());
		this->d_pm_map_y_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_y_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_map_x_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_x_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_map_height_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_height_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_map_width_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_width_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_map_jump_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_jump_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_map_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_map_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pm_moveplayer_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_movenpc_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_type_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_map_type_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_offset_cbo = (gcnew System::Windows::Forms::CheckBox());
		this->d_pm_coord_z_num = (gcnew System::Windows::Forms::NumericUpDown());
		this->d_pm_coord_y_num = (gcnew System::Windows::Forms::NumericUpDown());
		this->d_pm_coord_x_num = (gcnew System::Windows::Forms::NumericUpDown());
		this->d_pm_coord_z_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_coord_y_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_coord_x_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_toplayer_cbo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pm_tonpc_cbo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pm_coord_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pm_move_pt_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_config_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pm_username_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_server_cbx = (gcnew System::Windows::Forms::ComboBox());
		this->d_pm_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pm_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pm_commit_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_chat_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_chat_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pc_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pc_player_info_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pc_username_edt = (gcnew System::Windows::Forms::ComboBox());
		this->d_pc_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pc_playername_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pc_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pc_record_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pc_group_list = (gcnew System::Windows::Forms::ListView());
		this->dpc_column_account_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dpc_column_player_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dpc_column_time = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_pc_filter_pnl = (gcnew System::Windows::Forms::Panel());
		this->d_pc_filter_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pc_filter_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pc_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pc_commit_reason_btn = (gcnew System::Windows::Forms::Button());
		this->d_pc_forbid_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pc_min_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pc_unforbit_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pc_forbit_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pc_time_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pc_time_lbl = (gcnew System::Windows::Forms::Label());
		this->c_player_kick_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_kick_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pk_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pk_player_info_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pk_username_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_pk_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pk_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pk_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pk_record_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pk_record_list = (gcnew System::Windows::Forms::ListView());
		this->dpk_column_account_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dpk_column_end_time = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_pk_record_pnl = (gcnew System::Windows::Forms::Panel());
		this->d_pk_filter_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pk_filter_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pk_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pk_commit_reason_btn = (gcnew System::Windows::Forms::Button());
		this->d_pk_forbid_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pk_hour_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pk_forbid_lbl = (gcnew System::Windows::Forms::RadioButton());
		this->d_pk_unforbid_lbl = (gcnew System::Windows::Forms::RadioButton());
		this->d_pk_time_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pk_time_lbl = (gcnew System::Windows::Forms::Label());
		this->c_player_item_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_item_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pi_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pi_config_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pi_config_tab = (gcnew System::Windows::Forms::TabControl());
		this->d_pi_single_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_pi_all_player_cekb = (gcnew System::Windows::Forms::CheckBox());
		this->d_pi_username_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_pi_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pi_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pi_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pi_group_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_pi_group_list = (gcnew System::Windows::Forms::ListView());
		this->dpi_column_region_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dpi_column_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_pi_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pi_commit_reason_btn = (gcnew System::Windows::Forms::Button());
		this->d_pi_item_info_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pi_type_tab = (gcnew System::Windows::Forms::TabControl());
		this->d_pi_item_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_pi_id_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pi_name_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pi_number_num = (gcnew System::Windows::Forms::NumericUpDown());
		this->d_pi_number_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pi_lvl_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pi_lvl_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pi_name_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pi_quality_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pi_quality_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pi_id_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pi_money_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_pi_money_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pi_money_lbl = (gcnew System::Windows::Forms::Label());
		this->c_player_npc_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_npc_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pn_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pn_npc_info_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pn_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pn_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pn_npcid_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pn_npcname_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pn_npcid_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pn_npcname_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pn_record_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pn_record_list = (gcnew System::Windows::Forms::ListView());
		this->dpn_column_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->dpn_column_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_pn_filter_server_pnl = (gcnew System::Windows::Forms::Panel());
		this->d_pn_filter_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pn_filter_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pn_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pn_commit_reason_btn = (gcnew System::Windows::Forms::Button());
		this->d_pn_npc_setting_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pn_closed_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pn_unclosed_gbo = (gcnew System::Windows::Forms::RadioButton());
		this->c_player_hidden_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_hidden_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ph_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ph_record_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ph_record_list = (gcnew System::Windows::Forms::ListView());
		this->dph_column_player_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dph_column_end_time = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_ph_record_pnl = (gcnew System::Windows::Forms::Panel());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->d_ph_filter_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_ph_config_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ph_username_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_ph_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_ph_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_ph_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_ph_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ph_commit_btn = (gcnew System::Windows::Forms::Button());
		this->d_ph_hidden_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ph_hour_lbl = (gcnew System::Windows::Forms::Label());
		this->d_ph_hidden_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_ph_time_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_ph_show_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_ph_time_lbl = (gcnew System::Windows::Forms::Label());
		this->c_player_state_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_ps_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ps_config_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ps_search_btn = (gcnew System::Windows::Forms::Button());
		this->d_ps_username_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_ps_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_ps_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_ps_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_ps_state_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ps_state_tab = (gcnew System::Windows::Forms::TabControl());
		this->d_ps_property_pag = (gcnew System::Windows::Forms::TabPage());
		this->textBox18 = (gcnew System::Windows::Forms::TextBox());
		this->textBox9 = (gcnew System::Windows::Forms::TextBox());
		this->textBox17 = (gcnew System::Windows::Forms::TextBox());
		this->textBox6 = (gcnew System::Windows::Forms::TextBox());
		this->textBox16 = (gcnew System::Windows::Forms::TextBox());
		this->textBox3 = (gcnew System::Windows::Forms::TextBox());
		this->textBox15 = (gcnew System::Windows::Forms::TextBox());
		this->textBox8 = (gcnew System::Windows::Forms::TextBox());
		this->textBox14 = (gcnew System::Windows::Forms::TextBox());
		this->textBox5 = (gcnew System::Windows::Forms::TextBox());
		this->textBox13 = (gcnew System::Windows::Forms::TextBox());
		this->textBox2 = (gcnew System::Windows::Forms::TextBox());
		this->textBox12 = (gcnew System::Windows::Forms::TextBox());
		this->textBox7 = (gcnew System::Windows::Forms::TextBox());
		this->textBox11 = (gcnew System::Windows::Forms::TextBox());
		this->textBox4 = (gcnew System::Windows::Forms::TextBox());
		this->textBox10 = (gcnew System::Windows::Forms::TextBox());
		this->textBox1 = (gcnew System::Windows::Forms::TextBox());
		this->label19 = (gcnew System::Windows::Forms::Label());
		this->label17 = (gcnew System::Windows::Forms::Label());
		this->label18 = (gcnew System::Windows::Forms::Label());
		this->label16 = (gcnew System::Windows::Forms::Label());
		this->label15 = (gcnew System::Windows::Forms::Label());
		this->label9 = (gcnew System::Windows::Forms::Label());
		this->label14 = (gcnew System::Windows::Forms::Label());
		this->label8 = (gcnew System::Windows::Forms::Label());
		this->label13 = (gcnew System::Windows::Forms::Label());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label12 = (gcnew System::Windows::Forms::Label());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->label11 = (gcnew System::Windows::Forms::Label());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->d_ps_equip_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_ps_state_equip_tab = (gcnew System::Windows::Forms::TabControl());
		this->d_ps_se_cha_tab = (gcnew System::Windows::Forms::TabPage());
		this->d_ps_se_fashion_tab = (gcnew System::Windows::Forms::TabPage());
		this->d_ps_bag_pag = (gcnew System::Windows::Forms::TabPage());
		this->listView1 = (gcnew System::Windows::Forms::ListView());
		this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader8 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader9 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader10 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader11 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader12 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader13 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader14 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader15 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader16 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader17 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader18 = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_ps_skill_pag = (gcnew System::Windows::Forms::TabPage());
		this->listView4 = (gcnew System::Windows::Forms::ListView());
		this->d_ps_task_pag = (gcnew System::Windows::Forms::TabPage());
		this->listView3 = (gcnew System::Windows::Forms::ListView());
		this->c_player_state_pal = (gcnew System::Windows::Forms::Panel());
		this->c_gm_player_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_gm_player_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pg_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pg_record_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->panel1 = (gcnew System::Windows::Forms::Panel());
		this->d_pg_filter_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pg_record_pnl = (gcnew System::Windows::Forms::Label());
		this->d_pg_record_list = (gcnew System::Windows::Forms::ListView());
		this->dpg_column_player_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dpg_column_gm_level = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_pg_config_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pg_username_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_pg_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pg_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pg_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pg_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pg_commit_btn = (gcnew System::Windows::Forms::Button());
		this->d_pg_setting_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pg_open_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_pg_close_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->c_player_kill_npc_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_kill_npc_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pkl_pal = (gcnew System::Windows::Forms::Panel());
		this->d_pkl_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pkl_commit_btn = (gcnew System::Windows::Forms::Button());
		this->d_pkl_config_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_pkl_username_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pkl_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_pkl_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_pkl_server_lbl = (gcnew System::Windows::Forms::Label());
		this->c_player_spl = (gcnew System::Windows::Forms::Splitter());
		this->c_player_left_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_tab = (gcnew System::Windows::Forms::TabControl());
		this->c_player_search_player_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_search_player_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_player_list_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_player_list = (gcnew System::Windows::Forms::ListView());
		this->cps_player_column_account_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_player_column_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_player_column_uin = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_player_column_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_player_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_player_search_player_op_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_player_get_all_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_player_get_sel_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_player_filter_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_player_blur_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_player_search_player_search_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_player_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->c_player_search_player_charactor_edt = (gcnew System::Windows::Forms::TextBox());
		this->c_player_search_player_account_edt = (gcnew System::Windows::Forms::TextBox());
		this->c_player_search_player_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->c_player_search_player_charactor_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_player_search_player_account_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_player_search_player_server_lbl = (gcnew System::Windows::Forms::Label());
		this->c_player_search_npc_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_search_npc_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_npc_list_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_npc_list = (gcnew System::Windows::Forms::ListView());
		this->cps_column_npc_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_column_npc_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_column_npc_type = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_player_search_npc_op_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_npc_get_all_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_npc_get_sel_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_npc_filter_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_npc_search_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_npc_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->c_player_search_npc_id_edt = (gcnew System::Windows::Forms::TextBox());
		this->c_player_search_npc_name_edt = (gcnew System::Windows::Forms::TextBox());
		this->c_player_search_npc_id_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_player_search_npc_name_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_player_search_item_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_player_search_item_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_item_list_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_item_list = (gcnew System::Windows::Forms::ListView());
		this->cps_column_item_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_column_item_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->cps_column_item_type = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_player_search_item_op_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_item_get_all_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_item_get_sel_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_item_filter_pal = (gcnew System::Windows::Forms::Panel());
		this->c_player_search_item_search_btn = (gcnew System::Windows::Forms::Button());
		this->c_player_search_item_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->c_player_search_item_id_edt = (gcnew System::Windows::Forms::TextBox());
		this->c_player_search_item_name_edt = (gcnew System::Windows::Forms::TextBox());
		this->c_player_search_item_id_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_player_search_item_name_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_msg_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_msg_pal = (gcnew System::Windows::Forms::Panel());
		this->c_msg_main_pal = (gcnew System::Windows::Forms::Panel());
		this->c_msg_main_tab = (gcnew System::Windows::Forms::TabControl());
		this->c_msg_post_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_msg_sensword_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_msg_sensword_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ms_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ms_server_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ms_server_list = (gcnew System::Windows::Forms::ListView());
		this->dms_column_region_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dms_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_ms_sensword_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ms_sensword_list = (gcnew System::Windows::Forms::ListView());
		this->ms_sens_column_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->ms_sens_column_content = (gcnew System::Windows::Forms::ColumnHeader());
		this->ms_sens_column_type = (gcnew System::Windows::Forms::ColumnHeader());
		this->ms_sens_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->ms_sens_column_uin = (gcnew System::Windows::Forms::ColumnHeader());
		this->ms_sens_column_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_msg_reply_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_msg_reply_pal = (gcnew System::Windows::Forms::Panel());
		this->d_mr_pal = (gcnew System::Windows::Forms::Panel());
		this->d_mr_reply_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mr_player_info_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mr_player_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_mr_server_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_mr_charactor_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mr_server_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mr_common_reply_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mr_common_reply_list = (gcnew System::Windows::Forms::ListBox());
		this->d_mr_commit_btn = (gcnew System::Windows::Forms::Button());
		this->d_mr_one_reply_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mr_one_reply_edt = (gcnew System::Windows::Forms::RichTextBox());
		this->d_mr_one_question_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mr_one_question_txt = (gcnew System::Windows::Forms::RichTextBox());
		this->d_mr_server_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mr_server_list = (gcnew System::Windows::Forms::ListView());
		this->dmr_server_column_region_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmr_server_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_mr_question_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mr_question_list = (gcnew System::Windows::Forms::ListView());
		this->mr_column_player_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->mr_column_content = (gcnew System::Windows::Forms::ColumnHeader());
		this->mr_column_gm_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->mr_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->mr_column_player_uin = (gcnew System::Windows::Forms::ColumnHeader());
		this->mr_column_player_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_msg_center_spl = (gcnew System::Windows::Forms::Splitter());
		this->c_msg_server_right_pal = (gcnew System::Windows::Forms::Panel());
		this->c_msg_server_search_tab = (gcnew System::Windows::Forms::TabControl());
		this->c_msg_server_right_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_msg_server_search_op_pal = (gcnew System::Windows::Forms::Panel());
		this->c_msg_server_getall_btn = (gcnew System::Windows::Forms::Button());
		this->c_msg_server_getsel_btn = (gcnew System::Windows::Forms::Button());
		this->c_msg_server_search_pal = (gcnew System::Windows::Forms::Panel());
		this->c_msg_server_search_list = (gcnew System::Windows::Forms::ListView());
		this->cmsg_column_region_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->cmsg_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_server_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_server_pal = (gcnew System::Windows::Forms::Panel());
		this->c_ss_server_pal = (gcnew System::Windows::Forms::Panel());
		this->c_ss_server_refresh_btn = (gcnew System::Windows::Forms::Button());
		this->c_ss_server_list = (gcnew System::Windows::Forms::ListView());
		this->ss_column_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->ss_column_online_count = (gcnew System::Windows::Forms::ColumnHeader());
		this->ss_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->ss_column_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_account_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_account_pal = (gcnew System::Windows::Forms::Panel());
		this->c_account_tab = (gcnew System::Windows::Forms::TabControl());
		this->c_account_manager_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_account_manager_pal = (gcnew System::Windows::Forms::Panel());
		this->d_am_pal = (gcnew System::Windows::Forms::Panel());
		this->d_am_tab = (gcnew System::Windows::Forms::TabControl());
		this->d_am_create_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_am_create_pal = (gcnew System::Windows::Forms::Panel());
		this->d_am_user_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_am_password_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_am_password_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_username_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_am_username_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_password2_edt = (gcnew System::Windows::Forms::TextBox());
		this->d_am_authority_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_am_password2_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_authority_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_am_commit_btn = (gcnew System::Windows::Forms::Button());
		this->d_am_record_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_am_record_pal = (gcnew System::Windows::Forms::Panel());
		this->d_am_account_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_am_account_list = (gcnew System::Windows::Forms::ListView());
		this->d_am_column_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_am_column_authority = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_am_column_gm_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_am_change_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_am_change_name_content_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_change_name_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_change_delete_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_am_delete_reason_btn = (gcnew System::Windows::Forms::Button());
		this->d_am_change_update_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_am_update_reason_btn = (gcnew System::Windows::Forms::Button());
		this->d_am_change_info_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_am_change_authority_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->d_am_change_password_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->d_am_change_newpasswor2_txt = (gcnew System::Windows::Forms::TextBox());
		this->d_am_change_newpasswor2_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_change_oldpassword_txt = (gcnew System::Windows::Forms::TextBox());
		this->d_am_change_oldpassword_lbl = (gcnew System::Windows::Forms::Label());
		this->d_am_change_newpassword_txt = (gcnew System::Windows::Forms::TextBox());
		this->d_am_change_authority_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_am_change_newpassword_lbl = (gcnew System::Windows::Forms::Label());
		this->c_account_record_pag = (gcnew System::Windows::Forms::TabPage());
		this->c_account_record_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ar_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ar_record_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ar_log_tab = (gcnew System::Windows::Forms::TabControl());
		this->d_ar_log_senditem_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_ar_si_log_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ar_si_log_list = (gcnew System::Windows::Forms::ListView());
		this->column_ar_si_log_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_sendtime = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_gm_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_region = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_playername = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_playerid = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_itemname = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_itemcount = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_itemlvl = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_itemgrad = (gcnew System::Windows::Forms::ColumnHeader());
		this->column_ar_si_itemuin = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_ar_si_filter_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ar_si_filter_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ar_si_itemtype_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_ar_si_itemtype_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->d_ar_si_search_btn = (gcnew System::Windows::Forms::Button());
		this->d_ar_filter_pal = (gcnew System::Windows::Forms::Panel());
		this->d_ar_filter_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_ar_si_endtime_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->d_ar_si_starttime_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->d_ar_si_endtime_dtp = (gcnew System::Windows::Forms::DateTimePicker());
		this->d_ar_si_starttime_dtp = (gcnew System::Windows::Forms::DateTimePicker());
		this->d_ar_si_region_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_ar_si_region_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->d_ar_si_gmname_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_ar_si_gmname_cbx = (gcnew System::Windows::Forms::CheckBox());
		this->c_msg_pag_k = (gcnew System::Windows::Forms::TabPage());
		this->c_msg_server_pal_k = (gcnew System::Windows::Forms::Panel());
		this->c_msg_server_tab_k = (gcnew System::Windows::Forms::TabControl());
		this->c_msg_server_right_pag_k = (gcnew System::Windows::Forms::TabPage());
		this->d_msg_server_list_k = (gcnew System::Windows::Forms::ListView());
		this->d_msg_column_region_name_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_msg_column_region_id_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_msg_tab_k = (gcnew System::Windows::Forms::TabControl());
		this->c_msg_post_pag_k = (gcnew System::Windows::Forms::TabPage());
		this->c_msg_post_pal = (gcnew System::Windows::Forms::Panel());
		this->d_mp_pal = (gcnew System::Windows::Forms::Panel());
		this->d_mp_tab = (gcnew System::Windows::Forms::TabControl());
		this->d_mp_record_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_mpr_create_pal = (gcnew System::Windows::Forms::Panel());
		this->d_mpr_server_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mpr_server_list = (gcnew System::Windows::Forms::ListView());
		this->dmpr_column_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_content = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_region_group = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_start_date = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_end_date = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_hour = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_minute = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_num = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_pause = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_repeat = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_end_hours = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_end_minutes = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmpr_column_play_time_distance = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_mpr_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mpr_delete_btn = (gcnew System::Windows::Forms::Button());
		this->d_mpr_new_btn = (gcnew System::Windows::Forms::Button());
		this->d_mpr_update_btn = (gcnew System::Windows::Forms::Button());
		this->d_mp_create_pag = (gcnew System::Windows::Forms::TabPage());
		this->d_mp_create_pal = (gcnew System::Windows::Forms::Panel());
		this->d_mp_title_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mp_id_value_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_id_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_state_value_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_state_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_commit_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mp_commit_btn = (gcnew System::Windows::Forms::Button());
		this->d_mp_post_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mp_pause_ckb = (gcnew System::Windows::Forms::CheckBox());
		this->d_mp_cycle_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->time_distance_box = (gcnew System::Windows::Forms::TextBox());
		this->d_mp_repeat_ckb = (gcnew System::Windows::Forms::CheckBox());
		this->d_mp_play_time_cbo = (gcnew System::Windows::Forms::DateTimePicker());
		this->d_mp_end_time_k_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_time_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_play_time_end_cbo = (gcnew System::Windows::Forms::DateTimePicker());
		this->d_mp_time_distance_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_end_time_dtp = (gcnew System::Windows::Forms::DateTimePicker());
		this->d_mp_end_time_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_start_time_dtp = (gcnew System::Windows::Forms::DateTimePicker());
		this->d_mp_start_time_lbl = (gcnew System::Windows::Forms::Label());
		this->d_mp_server_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mp_server_list = (gcnew System::Windows::Forms::ListView());
		this->dmp_column_region_name = (gcnew System::Windows::Forms::ColumnHeader());
		this->dmp_column_region_id = (gcnew System::Windows::Forms::ColumnHeader());
		this->d_mp_cycle_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_mp_once_rdo = (gcnew System::Windows::Forms::RadioButton());
		this->d_mp_text_gbo = (gcnew System::Windows::Forms::GroupBox());
		this->d_mp_text_mno = (gcnew System::Windows::Forms::RichTextBox());
		this->d_mp_num_cbo = (gcnew System::Windows::Forms::ComboBox());
		this->d_mp_num_lbl = (gcnew System::Windows::Forms::Label());
		this->c_msg_sensword_pag_k = (gcnew System::Windows::Forms::TabPage());
		this->d_msg_senswords_pal_k = (gcnew System::Windows::Forms::Panel());
		this->e_msg_senswords_r_pal_k = (gcnew System::Windows::Forms::Panel());
		this->e_msg_sensword_group_k = (gcnew System::Windows::Forms::GroupBox());
		this->c_msg_sensword_session_list_k = (gcnew System::Windows::Forms::ListView());
		this->c_msg_sensword_column_plyname_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_msg_sensword_column_content_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->f_msg_senswords_b_pal_k = (gcnew System::Windows::Forms::Panel());
		this->f_msg_senswords_open_config_k = (gcnew System::Windows::Forms::Button());
		this->f_msg_senswords_load_config_k = (gcnew System::Windows::Forms::Button());
		this->d_msg_sensword_group_k = (gcnew System::Windows::Forms::GroupBox());
		this->c_msg_sensword_server_list_k = (gcnew System::Windows::Forms::ListView());
		this->c_msg_sensword_name_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_msg_sensword_id_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_msg_gmsession_pag_k = (gcnew System::Windows::Forms::TabPage());
		this->d_msg_gmsession_pal_k = (gcnew System::Windows::Forms::Panel());
		this->e_msg_gmsession_b_pal_k = (gcnew System::Windows::Forms::Panel());
		this->e_msg_gmsession_person_chk_k = (gcnew System::Windows::Forms::CheckBox());
		this->e_msg_gmsession_l_box_k = (gcnew System::Windows::Forms::TextBox());
		this->e_msg_gmsession_r_box_k = (gcnew System::Windows::Forms::TextBox());
		this->e_msg_gmsession_send_btn_k = (gcnew System::Windows::Forms::Button());
		this->e_msg_gmsession_person_btn_k = (gcnew System::Windows::Forms::Button());
		this->e_msg_gmsession_t_pal_k = (gcnew System::Windows::Forms::Panel());
		this->e_msg_gmsession_l_group_k = (gcnew System::Windows::Forms::GroupBox());
		this->e_msg_gmsession_server_list_k = (gcnew System::Windows::Forms::ListView());
		this->e_msg_gmsession_server_column_region_name_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->e_msg_gmsession_server_column_region_id_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->e_msg_gmsession_r_group_k = (gcnew System::Windows::Forms::GroupBox());
		this->e_msg_gmsession_server_session_list_k = (gcnew System::Windows::Forms::ListView());
		this->e_msg_gmsession_column_plyname_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->e_msg_gmsession_column_content_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->c_msg_private_reply_pag_k = (gcnew System::Windows::Forms::TabPage());
		this->d_msg_privatereply_pal_k = (gcnew System::Windows::Forms::Panel());
		this->e_msg_privatereply_b_pal_k = (gcnew System::Windows::Forms::Panel());
		this->e_msg_privatereply_l_group_k = (gcnew System::Windows::Forms::GroupBox());
		this->f_msg_privatereply_b_pal_k = (gcnew System::Windows::Forms::Panel());
		this->f_msg_privatereply_send_chk_k = (gcnew System::Windows::Forms::CheckBox());
		this->c_msg_pri_content_edit_k = (gcnew System::Windows::Forms::TextBox());
		this->f_msg_privatereply_send_btn_k = (gcnew System::Windows::Forms::Button());
		this->e_msg_privatereply_tab_k = (gcnew System::Windows::Forms::TabControl());
		this->e_msg_privatereply_r_group_k = (gcnew System::Windows::Forms::GroupBox());
		this->e_msg_privatereply_list_k = (gcnew System::Windows::Forms::ListView());
		this->e_msg_sensword_commom_chat_k = (gcnew System::Windows::Forms::ColumnHeader());
		this->e_msg_privatereply_t_pal_k = (gcnew System::Windows::Forms::Panel());
		this->c_msg_pri_region_comb_k = (gcnew System::Windows::Forms::ComboBox());
		this->c_msg_pri_add_btn_k = (gcnew System::Windows::Forms::Button());
		this->c_msg_pri_region_lab_k = (gcnew System::Windows::Forms::Label());
		this->c_msg_pri_character_comb_k = (gcnew System::Windows::Forms::ComboBox());
		this->c_msg_pri_character_lab_k = (gcnew System::Windows::Forms::Label());
		this->b_navi_pal_left = (gcnew System::Windows::Forms::Panel());
		this->b_navi_tree = (gcnew System::Windows::Forms::TreeView());
		this->a_spl_center = (gcnew System::Windows::Forms::Splitter());
		this->a_pal_bottom = (gcnew System::Windows::Forms::Panel());
		this->a_list_msg = (gcnew System::Windows::Forms::ListView());
		this->log_column_time = (gcnew System::Windows::Forms::ColumnHeader());
		this->log_column_log = (gcnew System::Windows::Forms::ColumnHeader());
		this->a_main_pal->SuspendLayout();
		this->a_pal_full->SuspendLayout();
		this->b_main_pal_right->SuspendLayout();
		this->b_main_tab->SuspendLayout();
		this->c_palyer_pag->SuspendLayout();
		this->c_player_pal->SuspendLayout();
		this->c_palyer_main_pal->SuspendLayout();
		this->c_player_tab->SuspendLayout();
		this->c_player_move_pag->SuspendLayout();
		this->c_player_move_pal->SuspendLayout();
		this->d_pm_pal->SuspendLayout();
		this->d_pm_position_gbo_k->SuspendLayout();
		this->d_pm_position_gbo->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pm_coord_z_num))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pm_coord_y_num))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pm_coord_x_num))->BeginInit();
		this->d_pm_config_gbo->SuspendLayout();
		this->d_pm_commit_gbo->SuspendLayout();
		this->c_player_chat_pag->SuspendLayout();
		this->c_player_chat_pal->SuspendLayout();
		this->d_pc_pal->SuspendLayout();
		this->d_pc_player_info_gbo->SuspendLayout();
		this->d_pc_record_gbo->SuspendLayout();
		this->d_pc_filter_pnl->SuspendLayout();
		this->d_pc_commit_gbo->SuspendLayout();
		this->d_pc_forbid_gbo->SuspendLayout();
		this->c_player_kick_pag->SuspendLayout();
		this->c_player_kick_pal->SuspendLayout();
		this->d_pk_pal->SuspendLayout();
		this->d_pk_player_info_gbo->SuspendLayout();
		this->d_pk_record_gbo->SuspendLayout();
		this->d_pk_record_pnl->SuspendLayout();
		this->d_pk_commit_gbo->SuspendLayout();
		this->d_pk_forbid_gbo->SuspendLayout();
		this->c_player_item_pag->SuspendLayout();
		this->c_player_item_pal->SuspendLayout();
		this->d_pi_pal->SuspendLayout();
		this->d_pi_config_gbo->SuspendLayout();
		this->d_pi_config_tab->SuspendLayout();
		this->d_pi_single_pag->SuspendLayout();
		this->d_pi_group_pag->SuspendLayout();
		this->d_pi_commit_gbo->SuspendLayout();
		this->d_pi_item_info_gbo->SuspendLayout();
		this->d_pi_type_tab->SuspendLayout();
		this->d_pi_item_pag->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pi_number_num))->BeginInit();
		this->d_pi_money_pag->SuspendLayout();
		this->c_player_npc_pag->SuspendLayout();
		this->c_player_npc_pal->SuspendLayout();
		this->d_pn_pal->SuspendLayout();
		this->d_pn_npc_info_gbo->SuspendLayout();
		this->d_pn_record_gbo->SuspendLayout();
		this->d_pn_filter_server_pnl->SuspendLayout();
		this->d_pn_commit_gbo->SuspendLayout();
		this->d_pn_npc_setting_gbo->SuspendLayout();
		this->c_player_hidden_pag->SuspendLayout();
		this->c_player_hidden_pal->SuspendLayout();
		this->d_ph_pal->SuspendLayout();
		this->d_ph_record_gbo->SuspendLayout();
		this->d_ph_record_pnl->SuspendLayout();
		this->d_ph_config_gbo->SuspendLayout();
		this->d_ph_commit_gbo->SuspendLayout();
		this->d_ph_hidden_gbo->SuspendLayout();
		this->c_player_state_pag->SuspendLayout();
		this->d_ps_pal->SuspendLayout();
		this->d_ps_config_gbo->SuspendLayout();
		this->d_ps_state_gbo->SuspendLayout();
		this->d_ps_state_tab->SuspendLayout();
		this->d_ps_property_pag->SuspendLayout();
		this->d_ps_equip_pag->SuspendLayout();
		this->d_ps_state_equip_tab->SuspendLayout();
		this->d_ps_bag_pag->SuspendLayout();
		this->d_ps_skill_pag->SuspendLayout();
		this->d_ps_task_pag->SuspendLayout();
		this->c_gm_player_pag->SuspendLayout();
		this->c_gm_player_pal->SuspendLayout();
		this->d_pg_pal->SuspendLayout();
		this->d_pg_record_gbo->SuspendLayout();
		this->panel1->SuspendLayout();
		this->d_pg_config_gbo->SuspendLayout();
		this->d_pg_commit_gbo->SuspendLayout();
		this->d_pg_setting_gbo->SuspendLayout();
		this->c_player_kill_npc_pag->SuspendLayout();
		this->c_player_kill_npc_pal->SuspendLayout();
		this->d_pkl_pal->SuspendLayout();
		this->d_pkl_commit_gbo->SuspendLayout();
		this->d_pkl_config_gbo->SuspendLayout();
		this->c_player_left_pal->SuspendLayout();
		this->c_player_search_tab->SuspendLayout();
		this->c_player_search_player_pag->SuspendLayout();
		this->c_player_search_player_pal->SuspendLayout();
		this->c_player_search_player_list_pal->SuspendLayout();
		this->c_player_search_player_op_pal->SuspendLayout();
		this->c_player_search_player_filter_pal->SuspendLayout();
		this->c_player_search_player_gbo->SuspendLayout();
		this->c_player_search_npc_pag->SuspendLayout();
		this->c_player_search_npc_pal->SuspendLayout();
		this->c_player_search_npc_list_pal->SuspendLayout();
		this->c_player_search_npc_op_pal->SuspendLayout();
		this->c_player_search_npc_filter_pal->SuspendLayout();
		this->c_player_search_npc_gbo->SuspendLayout();
		this->c_player_search_item_pag->SuspendLayout();
		this->c_player_search_item_pal->SuspendLayout();
		this->c_player_search_item_list_pal->SuspendLayout();
		this->c_player_search_item_op_pal->SuspendLayout();
		this->c_player_search_item_filter_pal->SuspendLayout();
		this->c_player_search_item_gbo->SuspendLayout();
		this->c_msg_pag->SuspendLayout();
		this->c_msg_pal->SuspendLayout();
		this->c_msg_main_pal->SuspendLayout();
		this->c_msg_main_tab->SuspendLayout();
		this->c_msg_sensword_pag->SuspendLayout();
		this->c_msg_sensword_pal->SuspendLayout();
		this->d_ms_pal->SuspendLayout();
		this->d_ms_server_gbo->SuspendLayout();
		this->d_ms_sensword_gbo->SuspendLayout();
		this->c_msg_reply_pag->SuspendLayout();
		this->c_msg_reply_pal->SuspendLayout();
		this->d_mr_pal->SuspendLayout();
		this->d_mr_reply_gbo->SuspendLayout();
		this->d_mr_player_info_gbo->SuspendLayout();
		this->d_mr_common_reply_gbo->SuspendLayout();
		this->d_mr_one_reply_gbo->SuspendLayout();
		this->d_mr_one_question_gbo->SuspendLayout();
		this->d_mr_server_gbo->SuspendLayout();
		this->d_mr_question_gbo->SuspendLayout();
		this->c_msg_server_right_pal->SuspendLayout();
		this->c_msg_server_search_tab->SuspendLayout();
		this->c_msg_server_right_pag->SuspendLayout();
		this->c_msg_server_search_op_pal->SuspendLayout();
		this->c_msg_server_search_pal->SuspendLayout();
		this->c_server_pag->SuspendLayout();
		this->c_server_pal->SuspendLayout();
		this->c_ss_server_pal->SuspendLayout();
		this->c_account_pag->SuspendLayout();
		this->c_account_pal->SuspendLayout();
		this->c_account_tab->SuspendLayout();
		this->c_account_manager_pag->SuspendLayout();
		this->c_account_manager_pal->SuspendLayout();
		this->d_am_pal->SuspendLayout();
		this->d_am_tab->SuspendLayout();
		this->d_am_create_pag->SuspendLayout();
		this->d_am_create_pal->SuspendLayout();
		this->d_am_user_gbo->SuspendLayout();
		this->d_am_commit_gbo->SuspendLayout();
		this->d_am_record_pag->SuspendLayout();
		this->d_am_record_pal->SuspendLayout();
		this->d_am_account_gbo->SuspendLayout();
		this->d_am_change_gbo->SuspendLayout();
		this->d_am_change_delete_gbo->SuspendLayout();
		this->d_am_change_update_gbo->SuspendLayout();
		this->d_am_change_info_gbo->SuspendLayout();
		this->c_account_record_pag->SuspendLayout();
		this->c_account_record_pal->SuspendLayout();
		this->d_ar_pal->SuspendLayout();
		this->d_ar_record_pal->SuspendLayout();
		this->d_ar_log_tab->SuspendLayout();
		this->d_ar_log_senditem_pag->SuspendLayout();
		this->d_ar_si_log_gbo->SuspendLayout();
		this->d_ar_si_filter_pal->SuspendLayout();
		this->d_ar_si_filter_gbo->SuspendLayout();
		this->d_ar_filter_pal->SuspendLayout();
		this->d_ar_filter_gbo->SuspendLayout();
		this->c_msg_pag_k->SuspendLayout();
		this->c_msg_server_pal_k->SuspendLayout();
		this->c_msg_server_tab_k->SuspendLayout();
		this->c_msg_server_right_pag_k->SuspendLayout();
		this->c_msg_tab_k->SuspendLayout();
		this->c_msg_post_pag_k->SuspendLayout();
		this->c_msg_post_pal->SuspendLayout();
		this->d_mp_pal->SuspendLayout();
		this->d_mp_tab->SuspendLayout();
		this->d_mp_record_pag->SuspendLayout();
		this->d_mpr_create_pal->SuspendLayout();
		this->d_mpr_server_gbo->SuspendLayout();
		this->d_mpr_commit_gbo->SuspendLayout();
		this->d_mp_create_pag->SuspendLayout();
		this->d_mp_create_pal->SuspendLayout();
		this->d_mp_title_gbo->SuspendLayout();
		this->d_mp_commit_gbo->SuspendLayout();
		this->d_mp_post_gbo->SuspendLayout();
		this->d_mp_cycle_gbo->SuspendLayout();
		this->d_mp_server_gbo->SuspendLayout();
		this->d_mp_text_gbo->SuspendLayout();
		this->c_msg_sensword_pag_k->SuspendLayout();
		this->d_msg_senswords_pal_k->SuspendLayout();
		this->e_msg_senswords_r_pal_k->SuspendLayout();
		this->e_msg_sensword_group_k->SuspendLayout();
		this->f_msg_senswords_b_pal_k->SuspendLayout();
		this->d_msg_sensword_group_k->SuspendLayout();
		this->c_msg_gmsession_pag_k->SuspendLayout();
		this->d_msg_gmsession_pal_k->SuspendLayout();
		this->e_msg_gmsession_b_pal_k->SuspendLayout();
		this->e_msg_gmsession_t_pal_k->SuspendLayout();
		this->e_msg_gmsession_l_group_k->SuspendLayout();
		this->e_msg_gmsession_r_group_k->SuspendLayout();
		this->c_msg_private_reply_pag_k->SuspendLayout();
		this->d_msg_privatereply_pal_k->SuspendLayout();
		this->e_msg_privatereply_b_pal_k->SuspendLayout();
		this->e_msg_privatereply_l_group_k->SuspendLayout();
		this->f_msg_privatereply_b_pal_k->SuspendLayout();
		this->e_msg_privatereply_r_group_k->SuspendLayout();
		this->e_msg_privatereply_t_pal_k->SuspendLayout();
		this->b_navi_pal_left->SuspendLayout();
		this->a_pal_bottom->SuspendLayout();
		this->SuspendLayout();
		// 
		// a_main_pal
		// 
		this->a_main_pal->Controls->Add(this->a_pal_full);
		this->a_main_pal->Controls->Add(this->a_spl_center);
		this->a_main_pal->Controls->Add(this->a_pal_bottom);
		this->a_main_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->a_main_pal->Location = System::Drawing::Point(0, 0);
		this->a_main_pal->Name = L"a_main_pal";
		this->a_main_pal->Size = System::Drawing::Size(792, 566);
		this->a_main_pal->TabIndex = 5;
		// 
		// a_pal_full
		// 
		this->a_pal_full->Controls->Add(this->b_main_pal_right);
		this->a_pal_full->Controls->Add(this->b_navi_pal_left);
		this->a_pal_full->Dock = System::Windows::Forms::DockStyle::Fill;
		this->a_pal_full->Location = System::Drawing::Point(0, 0);
		this->a_pal_full->Name = L"a_pal_full";
		this->a_pal_full->Size = System::Drawing::Size(792, 502);
		this->a_pal_full->TabIndex = 8;
		// 
		// b_main_pal_right
		// 
		this->b_main_pal_right->BackColor = System::Drawing::Color::LightSteelBlue;
		this->b_main_pal_right->Controls->Add(this->b_main_tab);
		this->b_main_pal_right->Dock = System::Windows::Forms::DockStyle::Fill;
		this->b_main_pal_right->Location = System::Drawing::Point(134, 0);
		this->b_main_pal_right->Name = L"b_main_pal_right";
		this->b_main_pal_right->Size = System::Drawing::Size(658, 502);
		this->b_main_pal_right->TabIndex = 3;
		// 
		// b_main_tab
		// 
		this->b_main_tab->Controls->Add(this->c_palyer_pag);
		this->b_main_tab->Controls->Add(this->c_msg_pag);
		this->b_main_tab->Controls->Add(this->c_server_pag);
		this->b_main_tab->Controls->Add(this->c_account_pag);
		this->b_main_tab->Controls->Add(this->c_msg_pag_k);
		this->b_main_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->b_main_tab->Location = System::Drawing::Point(0, 0);
		this->b_main_tab->Name = L"b_main_tab";
		this->b_main_tab->SelectedIndex = 0;
		this->b_main_tab->Size = System::Drawing::Size(658, 502);
		this->b_main_tab->TabIndex = 0;
		// 
		// c_palyer_pag
		// 
		this->c_palyer_pag->Controls->Add(this->c_player_pal);
		this->c_palyer_pag->Location = System::Drawing::Point(4, 21);
		this->c_palyer_pag->Name = L"c_palyer_pag";
		this->c_palyer_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_palyer_pag->Size = System::Drawing::Size(650, 477);
		this->c_palyer_pag->TabIndex = 0;
		this->c_palyer_pag->Text = L"player";
		this->c_palyer_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_pal
		// 
		this->c_player_pal->Controls->Add(this->c_palyer_main_pal);
		this->c_player_pal->Controls->Add(this->c_player_spl);
		this->c_player_pal->Controls->Add(this->c_player_left_pal);
		this->c_player_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_pal->Name = L"c_player_pal";
		this->c_player_pal->Size = System::Drawing::Size(644, 471);
		this->c_player_pal->TabIndex = 3;
		// 
		// c_palyer_main_pal
		// 
		this->c_palyer_main_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->c_palyer_main_pal->Controls->Add(this->c_player_tab);
		this->c_palyer_main_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_palyer_main_pal->Location = System::Drawing::Point(0, 0);
		this->c_palyer_main_pal->Name = L"c_palyer_main_pal";
		this->c_palyer_main_pal->Size = System::Drawing::Size(463, 471);
		this->c_palyer_main_pal->TabIndex = 6;
		// 
		// c_player_tab
		// 
		this->c_player_tab->Controls->Add(this->c_player_move_pag);
		this->c_player_tab->Controls->Add(this->c_player_chat_pag);
		this->c_player_tab->Controls->Add(this->c_player_kick_pag);
		this->c_player_tab->Controls->Add(this->c_player_item_pag);
		this->c_player_tab->Controls->Add(this->c_player_npc_pag);
		this->c_player_tab->Controls->Add(this->c_player_hidden_pag);
		this->c_player_tab->Controls->Add(this->c_player_state_pag);
		this->c_player_tab->Controls->Add(this->c_gm_player_pag);
		this->c_player_tab->Controls->Add(this->c_player_kill_npc_pag);
		this->c_player_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_tab->Location = System::Drawing::Point(0, 0);
		this->c_player_tab->Name = L"c_player_tab";
		this->c_player_tab->SelectedIndex = 0;
		this->c_player_tab->Size = System::Drawing::Size(461, 469);
		this->c_player_tab->TabIndex = 1;
		// 
		// c_player_move_pag
		// 
		this->c_player_move_pag->Controls->Add(this->c_player_move_pal);
		this->c_player_move_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_move_pag->Name = L"c_player_move_pag";
		this->c_player_move_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_move_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_move_pag->TabIndex = 0;
		this->c_player_move_pag->Text = L"move";
		this->c_player_move_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_move_pal
		// 
		this->c_player_move_pal->Controls->Add(this->d_pm_pal);
		this->c_player_move_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_move_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_move_pal->Name = L"c_player_move_pal";
		this->c_player_move_pal->Size = System::Drawing::Size(447, 438);
		this->c_player_move_pal->TabIndex = 0;
		// 
		// d_pm_pal
		// 
		this->d_pm_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_pm_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_pm_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_pm_pal->Controls->Add(this->d_pm_position_gbo_k);
		this->d_pm_pal->Controls->Add(this->d_pm_config_gbo);
		this->d_pm_pal->Controls->Add(this->d_pm_commit_gbo);
		this->d_pm_pal->Location = System::Drawing::Point(12, 14);
		this->d_pm_pal->Name = L"d_pm_pal";
		this->d_pm_pal->Size = System::Drawing::Size(423, 411);
		this->d_pm_pal->TabIndex = 0;
		// 
		// d_pm_position_gbo_k
		// 
		this->d_pm_position_gbo_k->Controls->Add(this->d_pm_jump_pt_lab);
		this->d_pm_position_gbo_k->Controls->Add(this->d_pm_map_name_lab);
		this->d_pm_position_gbo_k->Controls->Add(this->d_pm_move_map_cbx);
		this->d_pm_position_gbo_k->Controls->Add(this->d_pm_position_gbo);
		this->d_pm_position_gbo_k->Controls->Add(this->d_pm_move_pt_cbx);
		this->d_pm_position_gbo_k->Location = System::Drawing::Point(23, 142);
		this->d_pm_position_gbo_k->Name = L"d_pm_position_gbo_k";
		this->d_pm_position_gbo_k->Size = System::Drawing::Size(381, 80);
		this->d_pm_position_gbo_k->TabIndex = 10;
		this->d_pm_position_gbo_k->TabStop = false;
		this->d_pm_position_gbo_k->Text = L"type";
		// 
		// d_pm_jump_pt_lab
		// 
		this->d_pm_jump_pt_lab->AutoSize = true;
		this->d_pm_jump_pt_lab->Location = System::Drawing::Point(238, 20);
		this->d_pm_jump_pt_lab->Name = L"d_pm_jump_pt_lab";
		this->d_pm_jump_pt_lab->Size = System::Drawing::Size(41, 12);
		this->d_pm_jump_pt_lab->TabIndex = 22;
		this->d_pm_jump_pt_lab->Text = L"jumpId";
		// 
		// d_pm_map_name_lab
		// 
		this->d_pm_map_name_lab->AutoSize = true;
		this->d_pm_map_name_lab->Location = System::Drawing::Point(59, 20);
		this->d_pm_map_name_lab->Name = L"d_pm_map_name_lab";
		this->d_pm_map_name_lab->Size = System::Drawing::Size(47, 12);
		this->d_pm_map_name_lab->TabIndex = 22;
		this->d_pm_map_name_lab->Text = L"mapName";
		// 
		// d_pm_move_map_cbx
		// 
		this->d_pm_move_map_cbx->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_pm_move_map_cbx->FormattingEnabled = true;
		this->d_pm_move_map_cbx->Location = System::Drawing::Point(61, 47);
		this->d_pm_move_map_cbx->Name = L"d_pm_move_map_cbx";
		this->d_pm_move_map_cbx->Size = System::Drawing::Size(99, 20);
		this->d_pm_move_map_cbx->TabIndex = 21;
		this->d_pm_move_map_cbx->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pm_move_map_cbx_SelectedIndexChanged);
		this->d_pm_move_map_cbx->TextChanged += gcnew System::EventHandler(this, &MainForm::d_pm_move_map_cbx_TextChanged);
		// 
		// d_pm_position_gbo
		// 
		this->d_pm_position_gbo->Controls->Add(this->d_pm_level_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_level_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_difficulty_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_difficulty_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_is_jump_maze_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_y_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_y_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_x_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_x_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_height_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_height_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_width_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_width_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_jump_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_jump_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_rdo);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_moveplayer_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_movenpc_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_type_cbx);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_map_type_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_offset_cbo);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_coord_z_num);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_coord_y_num);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_coord_x_num);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_coord_z_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_coord_y_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_coord_x_lbl);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_toplayer_cbo);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_tonpc_cbo);
		this->d_pm_position_gbo->Controls->Add(this->d_pm_coord_rdo);
		this->d_pm_position_gbo->Location = System::Drawing::Point(0, 171);
		this->d_pm_position_gbo->Name = L"d_pm_position_gbo";
		this->d_pm_position_gbo->Size = System::Drawing::Size(385, 10);
		this->d_pm_position_gbo->TabIndex = 6;
		this->d_pm_position_gbo->TabStop = false;
		this->d_pm_position_gbo->Text = L"type";
		this->d_pm_position_gbo->Visible = false;
		// 
		// d_pm_level_cbx
		// 
		this->d_pm_level_cbx->Enabled = false;
		this->d_pm_level_cbx->FormattingEnabled = true;
		this->d_pm_level_cbx->Location = System::Drawing::Point(315, 238);
		this->d_pm_level_cbx->Name = L"d_pm_level_cbx";
		this->d_pm_level_cbx->Size = System::Drawing::Size(46, 20);
		this->d_pm_level_cbx->TabIndex = 39;
		// 
		// d_pm_level_lbl
		// 
		this->d_pm_level_lbl->AutoSize = true;
		this->d_pm_level_lbl->Enabled = false;
		this->d_pm_level_lbl->Location = System::Drawing::Point(260, 240);
		this->d_pm_level_lbl->Name = L"d_pm_level_lbl";
		this->d_pm_level_lbl->Size = System::Drawing::Size(35, 12);
		this->d_pm_level_lbl->TabIndex = 38;
		this->d_pm_level_lbl->Text = L"level";
		// 
		// d_pm_difficulty_cbx
		// 
		this->d_pm_difficulty_cbx->Enabled = false;
		this->d_pm_difficulty_cbx->FormattingEnabled = true;
		this->d_pm_difficulty_cbx->Location = System::Drawing::Point(196, 238);
		this->d_pm_difficulty_cbx->Name = L"d_pm_difficulty_cbx";
		this->d_pm_difficulty_cbx->Size = System::Drawing::Size(56, 20);
		this->d_pm_difficulty_cbx->TabIndex = 37;
		// 
		// d_pm_difficulty_lbl
		// 
		this->d_pm_difficulty_lbl->AutoSize = true;
		this->d_pm_difficulty_lbl->Enabled = false;
		this->d_pm_difficulty_lbl->Location = System::Drawing::Point(128, 241);
		this->d_pm_difficulty_lbl->Name = L"d_pm_difficulty_lbl";
		this->d_pm_difficulty_lbl->Size = System::Drawing::Size(65, 12);
		this->d_pm_difficulty_lbl->TabIndex = 36;
		this->d_pm_difficulty_lbl->Text = L"difficulty";
		// 
		// d_pm_is_jump_maze_lbl
		// 
		this->d_pm_is_jump_maze_lbl->AutoSize = true;
		this->d_pm_is_jump_maze_lbl->Enabled = false;
		this->d_pm_is_jump_maze_lbl->Location = System::Drawing::Point(31, 180);
		this->d_pm_is_jump_maze_lbl->Name = L"d_pm_is_jump_maze_lbl";
		this->d_pm_is_jump_maze_lbl->Size = System::Drawing::Size(84, 16);
		this->d_pm_is_jump_maze_lbl->TabIndex = 35;
		this->d_pm_is_jump_maze_lbl->Text = L"isJumpMaze";
		this->d_pm_is_jump_maze_lbl->UseVisualStyleBackColor = true;
		this->d_pm_is_jump_maze_lbl->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pm_is_jump_maze_lbl_CheckedChanged);
		// 
		// d_pm_map_y_cbx
		// 
		this->d_pm_map_y_cbx->Enabled = false;
		this->d_pm_map_y_cbx->FormattingEnabled = true;
		this->d_pm_map_y_cbx->Location = System::Drawing::Point(315, 176);
		this->d_pm_map_y_cbx->Name = L"d_pm_map_y_cbx";
		this->d_pm_map_y_cbx->Size = System::Drawing::Size(42, 20);
		this->d_pm_map_y_cbx->TabIndex = 34;
		// 
		// d_pm_map_y_lbl
		// 
		this->d_pm_map_y_lbl->AutoSize = true;
		this->d_pm_map_y_lbl->Enabled = false;
		this->d_pm_map_y_lbl->Location = System::Drawing::Point(259, 180);
		this->d_pm_map_y_lbl->Name = L"d_pm_map_y_lbl";
		this->d_pm_map_y_lbl->Size = System::Drawing::Size(47, 12);
		this->d_pm_map_y_lbl->TabIndex = 33;
		this->d_pm_map_y_lbl->Text = L"y_index";
		// 
		// d_pm_map_x_cbx
		// 
		this->d_pm_map_x_cbx->Enabled = false;
		this->d_pm_map_x_cbx->FormattingEnabled = true;
		this->d_pm_map_x_cbx->Location = System::Drawing::Point(196, 176);
		this->d_pm_map_x_cbx->Name = L"d_pm_map_x_cbx";
		this->d_pm_map_x_cbx->Size = System::Drawing::Size(42, 20);
		this->d_pm_map_x_cbx->TabIndex = 32;
		// 
		// d_pm_map_x_lbl
		// 
		this->d_pm_map_x_lbl->AutoSize = true;
		this->d_pm_map_x_lbl->Enabled = false;
		this->d_pm_map_x_lbl->Location = System::Drawing::Point(128, 180);
		this->d_pm_map_x_lbl->Name = L"d_pm_map_x_lbl";
		this->d_pm_map_x_lbl->Size = System::Drawing::Size(47, 12);
		this->d_pm_map_x_lbl->TabIndex = 31;
		this->d_pm_map_x_lbl->Text = L"x_index";
		// 
		// d_pm_map_height_cbx
		// 
		this->d_pm_map_height_cbx->Enabled = false;
		this->d_pm_map_height_cbx->FormattingEnabled = true;
		this->d_pm_map_height_cbx->Location = System::Drawing::Point(314, 142);
		this->d_pm_map_height_cbx->Name = L"d_pm_map_height_cbx";
		this->d_pm_map_height_cbx->Size = System::Drawing::Size(56, 20);
		this->d_pm_map_height_cbx->TabIndex = 30;
		// 
		// d_pm_map_height_lbl
		// 
		this->d_pm_map_height_lbl->AutoSize = true;
		this->d_pm_map_height_lbl->Enabled = false;
		this->d_pm_map_height_lbl->Location = System::Drawing::Point(243, 147);
		this->d_pm_map_height_lbl->Name = L"d_pm_map_height_lbl";
		this->d_pm_map_height_lbl->Size = System::Drawing::Size(65, 12);
		this->d_pm_map_height_lbl->TabIndex = 29;
		this->d_pm_map_height_lbl->Text = L"map_height";
		// 
		// d_pm_map_width_cbx
		// 
		this->d_pm_map_width_cbx->Enabled = false;
		this->d_pm_map_width_cbx->FormattingEnabled = true;
		this->d_pm_map_width_cbx->Location = System::Drawing::Point(175, 143);
		this->d_pm_map_width_cbx->Name = L"d_pm_map_width_cbx";
		this->d_pm_map_width_cbx->Size = System::Drawing::Size(56, 20);
		this->d_pm_map_width_cbx->TabIndex = 28;
		// 
		// d_pm_map_width_lbl
		// 
		this->d_pm_map_width_lbl->AutoSize = true;
		this->d_pm_map_width_lbl->Enabled = false;
		this->d_pm_map_width_lbl->Location = System::Drawing::Point(102, 147);
		this->d_pm_map_width_lbl->Name = L"d_pm_map_width_lbl";
		this->d_pm_map_width_lbl->Size = System::Drawing::Size(59, 12);
		this->d_pm_map_width_lbl->TabIndex = 27;
		this->d_pm_map_width_lbl->Text = L"map_width";
		// 
		// d_pm_map_jump_cbx
		// 
		this->d_pm_map_jump_cbx->Enabled = false;
		this->d_pm_map_jump_cbx->FormattingEnabled = true;
		this->d_pm_map_jump_cbx->Location = System::Drawing::Point(315, 207);
		this->d_pm_map_jump_cbx->Name = L"d_pm_map_jump_cbx";
		this->d_pm_map_jump_cbx->Size = System::Drawing::Size(46, 20);
		this->d_pm_map_jump_cbx->TabIndex = 26;
		this->d_pm_map_jump_cbx->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_jump_cbx_SelectedIndexChanged);
		// 
		// d_pm_map_jump_lbl
		// 
		this->d_pm_map_jump_lbl->AutoSize = true;
		this->d_pm_map_jump_lbl->Enabled = false;
		this->d_pm_map_jump_lbl->Location = System::Drawing::Point(260, 209);
		this->d_pm_map_jump_lbl->Name = L"d_pm_map_jump_lbl";
		this->d_pm_map_jump_lbl->Size = System::Drawing::Size(29, 12);
		this->d_pm_map_jump_lbl->TabIndex = 25;
		this->d_pm_map_jump_lbl->Text = L"jump";
		// 
		// d_pm_map_cbx
		// 
		this->d_pm_map_cbx->Enabled = false;
		this->d_pm_map_cbx->FormattingEnabled = true;
		this->d_pm_map_cbx->Location = System::Drawing::Point(196, 207);
		this->d_pm_map_cbx->Name = L"d_pm_map_cbx";
		this->d_pm_map_cbx->Size = System::Drawing::Size(56, 20);
		this->d_pm_map_cbx->TabIndex = 24;
		this->d_pm_map_cbx->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_cbx_SelectedIndexChanged);
		this->d_pm_map_cbx->SelectedValueChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_cbx_SelectedValueChanged);
		this->d_pm_map_cbx->TextChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_cbx_TextChanged);
		// 
		// d_pm_map_lbl
		// 
		this->d_pm_map_lbl->AutoSize = true;
		this->d_pm_map_lbl->Enabled = false;
		this->d_pm_map_lbl->Location = System::Drawing::Point(128, 210);
		this->d_pm_map_lbl->Name = L"d_pm_map_lbl";
		this->d_pm_map_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pm_map_lbl->TabIndex = 23;
		this->d_pm_map_lbl->Text = L"map_id";
		// 
		// d_pm_map_rdo
		// 
		this->d_pm_map_rdo->AutoSize = true;
		this->d_pm_map_rdo->Location = System::Drawing::Point(12, 114);
		this->d_pm_map_rdo->Name = L"d_pm_map_rdo";
		this->d_pm_map_rdo->Size = System::Drawing::Size(41, 16);
		this->d_pm_map_rdo->TabIndex = 22;
		this->d_pm_map_rdo->TabStop = true;
		this->d_pm_map_rdo->Text = L"map";
		this->d_pm_map_rdo->UseVisualStyleBackColor = true;
		this->d_pm_map_rdo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_rdo_CheckedChanged);
		// 
		// d_pm_moveplayer_cbx
		// 
		this->d_pm_moveplayer_cbx->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_pm_moveplayer_cbx->Enabled = false;
		this->d_pm_moveplayer_cbx->FormattingEnabled = true;
		this->d_pm_moveplayer_cbx->Location = System::Drawing::Point(121, 20);
		this->d_pm_moveplayer_cbx->Name = L"d_pm_moveplayer_cbx";
		this->d_pm_moveplayer_cbx->Size = System::Drawing::Size(67, 20);
		this->d_pm_moveplayer_cbx->TabIndex = 20;
		// 
		// d_pm_movenpc_cbx
		// 
		this->d_pm_movenpc_cbx->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_pm_movenpc_cbx->Enabled = false;
		this->d_pm_movenpc_cbx->FormattingEnabled = true;
		this->d_pm_movenpc_cbx->Location = System::Drawing::Point(294, 21);
		this->d_pm_movenpc_cbx->Name = L"d_pm_movenpc_cbx";
		this->d_pm_movenpc_cbx->Size = System::Drawing::Size(82, 20);
		this->d_pm_movenpc_cbx->TabIndex = 19;
		// 
		// d_pm_map_type_cbx
		// 
		this->d_pm_map_type_cbx->Enabled = false;
		this->d_pm_map_type_cbx->FormattingEnabled = true;
		this->d_pm_map_type_cbx->Location = System::Drawing::Point(161, 114);
		this->d_pm_map_type_cbx->Name = L"d_pm_map_type_cbx";
		this->d_pm_map_type_cbx->Size = System::Drawing::Size(103, 20);
		this->d_pm_map_type_cbx->TabIndex = 16;
		this->d_pm_map_type_cbx->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_type_cbx_SelectedIndexChanged);
		this->d_pm_map_type_cbx->SelectedValueChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_type_cbx_SelectedValueChanged);
		this->d_pm_map_type_cbx->TextChanged += gcnew System::EventHandler(this, &MainForm::d_pm_map_type_cbx_TextChanged);
		// 
		// d_pm_map_type_lbl
		// 
		this->d_pm_map_type_lbl->AutoSize = true;
		this->d_pm_map_type_lbl->Enabled = false;
		this->d_pm_map_type_lbl->Location = System::Drawing::Point(102, 116);
		this->d_pm_map_type_lbl->Name = L"d_pm_map_type_lbl";
		this->d_pm_map_type_lbl->Size = System::Drawing::Size(53, 12);
		this->d_pm_map_type_lbl->TabIndex = 15;
		this->d_pm_map_type_lbl->Text = L"map_type";
		// 
		// d_pm_offset_cbo
		// 
		this->d_pm_offset_cbo->AutoSize = true;
		this->d_pm_offset_cbo->Checked = true;
		this->d_pm_offset_cbo->CheckState = System::Windows::Forms::CheckState::Checked;
		this->d_pm_offset_cbo->Enabled = false;
		this->d_pm_offset_cbo->Location = System::Drawing::Point(121, 54);
		this->d_pm_offset_cbo->Name = L"d_pm_offset_cbo";
		this->d_pm_offset_cbo->Size = System::Drawing::Size(72, 16);
		this->d_pm_offset_cbo->TabIndex = 14;
		this->d_pm_offset_cbo->Text = L"isOffset";
		this->d_pm_offset_cbo->UseVisualStyleBackColor = true;
		// 
		// d_pm_coord_z_num
		// 
		this->d_pm_coord_z_num->DecimalPlaces = 3;
		this->d_pm_coord_z_num->Enabled = false;
		this->d_pm_coord_z_num->Location = System::Drawing::Point(265, 80);
		this->d_pm_coord_z_num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99999, 0, 0, 0});
		this->d_pm_coord_z_num->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99999, 0, 0, System::Int32::MinValue});
		this->d_pm_coord_z_num->Name = L"d_pm_coord_z_num";
		this->d_pm_coord_z_num->Size = System::Drawing::Size(52, 21);
		this->d_pm_coord_z_num->TabIndex = 13;
		// 
		// d_pm_coord_y_num
		// 
		this->d_pm_coord_y_num->DecimalPlaces = 3;
		this->d_pm_coord_y_num->Enabled = false;
		this->d_pm_coord_y_num->Location = System::Drawing::Point(200, 80);
		this->d_pm_coord_y_num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99999, 0, 0, 0});
		this->d_pm_coord_y_num->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99999, 0, 0, System::Int32::MinValue});
		this->d_pm_coord_y_num->Name = L"d_pm_coord_y_num";
		this->d_pm_coord_y_num->Size = System::Drawing::Size(52, 21);
		this->d_pm_coord_y_num->TabIndex = 12;
		// 
		// d_pm_coord_x_num
		// 
		this->d_pm_coord_x_num->DecimalPlaces = 3;
		this->d_pm_coord_x_num->Enabled = false;
		this->d_pm_coord_x_num->Location = System::Drawing::Point(132, 80);
		this->d_pm_coord_x_num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99999, 0, 0, 0});
		this->d_pm_coord_x_num->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99999, 0, 0, System::Int32::MinValue});
		this->d_pm_coord_x_num->Name = L"d_pm_coord_x_num";
		this->d_pm_coord_x_num->Size = System::Drawing::Size(52, 21);
		this->d_pm_coord_x_num->TabIndex = 11;
		// 
		// d_pm_coord_z_lbl
		// 
		this->d_pm_coord_z_lbl->AutoSize = true;
		this->d_pm_coord_z_lbl->Location = System::Drawing::Point(254, 83);
		this->d_pm_coord_z_lbl->Name = L"d_pm_coord_z_lbl";
		this->d_pm_coord_z_lbl->Size = System::Drawing::Size(11, 12);
		this->d_pm_coord_z_lbl->TabIndex = 10;
		this->d_pm_coord_z_lbl->Text = L"z";
		// 
		// d_pm_coord_y_lbl
		// 
		this->d_pm_coord_y_lbl->AutoSize = true;
		this->d_pm_coord_y_lbl->Location = System::Drawing::Point(188, 82);
		this->d_pm_coord_y_lbl->Name = L"d_pm_coord_y_lbl";
		this->d_pm_coord_y_lbl->Size = System::Drawing::Size(11, 12);
		this->d_pm_coord_y_lbl->TabIndex = 9;
		this->d_pm_coord_y_lbl->Text = L"y";
		// 
		// d_pm_coord_x_lbl
		// 
		this->d_pm_coord_x_lbl->AutoSize = true;
		this->d_pm_coord_x_lbl->Location = System::Drawing::Point(121, 82);
		this->d_pm_coord_x_lbl->Name = L"d_pm_coord_x_lbl";
		this->d_pm_coord_x_lbl->Size = System::Drawing::Size(11, 12);
		this->d_pm_coord_x_lbl->TabIndex = 8;
		this->d_pm_coord_x_lbl->Text = L"x";
		// 
		// d_pm_toplayer_cbo
		// 
		this->d_pm_toplayer_cbo->AutoSize = true;
		this->d_pm_toplayer_cbo->Location = System::Drawing::Point(12, 22);
		this->d_pm_toplayer_cbo->Name = L"d_pm_toplayer_cbo";
		this->d_pm_toplayer_cbo->Size = System::Drawing::Size(107, 16);
		this->d_pm_toplayer_cbo->TabIndex = 2;
		this->d_pm_toplayer_cbo->TabStop = true;
		this->d_pm_toplayer_cbo->Text = L"移动到角色位置";
		this->d_pm_toplayer_cbo->UseVisualStyleBackColor = true;
		this->d_pm_toplayer_cbo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pm_player_cbo_CheckedChanged);
		// 
		// d_pm_tonpc_cbo
		// 
		this->d_pm_tonpc_cbo->AutoSize = true;
		this->d_pm_tonpc_cbo->Location = System::Drawing::Point(192, 23);
		this->d_pm_tonpc_cbo->Name = L"d_pm_tonpc_cbo";
		this->d_pm_tonpc_cbo->Size = System::Drawing::Size(101, 16);
		this->d_pm_tonpc_cbo->TabIndex = 1;
		this->d_pm_tonpc_cbo->TabStop = true;
		this->d_pm_tonpc_cbo->Text = L"移动到NPC位置";
		this->d_pm_tonpc_cbo->UseVisualStyleBackColor = true;
		this->d_pm_tonpc_cbo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pm_npc_cbo_CheckedChanged);
		// 
		// d_pm_coord_rdo
		// 
		this->d_pm_coord_rdo->AutoSize = true;
		this->d_pm_coord_rdo->Location = System::Drawing::Point(12, 53);
		this->d_pm_coord_rdo->Name = L"d_pm_coord_rdo";
		this->d_pm_coord_rdo->Size = System::Drawing::Size(83, 16);
		this->d_pm_coord_rdo->TabIndex = 0;
		this->d_pm_coord_rdo->TabStop = true;
		this->d_pm_coord_rdo->Text = L"coordinate";
		this->d_pm_coord_rdo->UseVisualStyleBackColor = true;
		this->d_pm_coord_rdo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pm_coord_rdo_CheckedChanged);
		// 
		// d_pm_move_pt_cbx
		// 
		this->d_pm_move_pt_cbx->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_pm_move_pt_cbx->FormattingEnabled = true;
		this->d_pm_move_pt_cbx->Location = System::Drawing::Point(240, 47);
		this->d_pm_move_pt_cbx->Name = L"d_pm_move_pt_cbx";
		this->d_pm_move_pt_cbx->Size = System::Drawing::Size(112, 20);
		this->d_pm_move_pt_cbx->TabIndex = 21;
		// 
		// d_pm_config_gbo
		// 
		this->d_pm_config_gbo->Controls->Add(this->d_pm_username_cbx);
		this->d_pm_config_gbo->Controls->Add(this->d_pm_server_cbx);
		this->d_pm_config_gbo->Controls->Add(this->d_pm_username_lbl);
		this->d_pm_config_gbo->Controls->Add(this->d_pm_server_lbl);
		this->d_pm_config_gbo->Location = System::Drawing::Point(19, 58);
		this->d_pm_config_gbo->Name = L"d_pm_config_gbo";
		this->d_pm_config_gbo->Size = System::Drawing::Size(385, 78);
		this->d_pm_config_gbo->TabIndex = 9;
		this->d_pm_config_gbo->TabStop = false;
		this->d_pm_config_gbo->Text = L"config";
		// 
		// d_pm_username_cbx
		// 
		this->d_pm_username_cbx->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_pm_username_cbx->FormattingEnabled = true;
		this->d_pm_username_cbx->Location = System::Drawing::Point(243, 44);
		this->d_pm_username_cbx->Name = L"d_pm_username_cbx";
		this->d_pm_username_cbx->Size = System::Drawing::Size(106, 20);
		this->d_pm_username_cbx->TabIndex = 14;
		// 
		// d_pm_server_cbx
		// 
		this->d_pm_server_cbx->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_pm_server_cbx->FormattingEnabled = true;
		this->d_pm_server_cbx->Location = System::Drawing::Point(57, 44);
		this->d_pm_server_cbx->Name = L"d_pm_server_cbx";
		this->d_pm_server_cbx->Size = System::Drawing::Size(106, 20);
		this->d_pm_server_cbx->TabIndex = 12;
		// 
		// d_pm_username_lbl
		// 
		this->d_pm_username_lbl->AutoSize = true;
		this->d_pm_username_lbl->Location = System::Drawing::Point(241, 19);
		this->d_pm_username_lbl->Name = L"d_pm_username_lbl";
		this->d_pm_username_lbl->Size = System::Drawing::Size(53, 12);
		this->d_pm_username_lbl->TabIndex = 10;
		this->d_pm_username_lbl->Text = L"username";
		// 
		// d_pm_server_lbl
		// 
		this->d_pm_server_lbl->AutoSize = true;
		this->d_pm_server_lbl->Location = System::Drawing::Point(55, 19);
		this->d_pm_server_lbl->Name = L"d_pm_server_lbl";
		this->d_pm_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pm_server_lbl->TabIndex = 9;
		this->d_pm_server_lbl->Text = L"server";
		// 
		// d_pm_commit_gbo
		// 
		this->d_pm_commit_gbo->Controls->Add(this->d_pm_commit_btn);
		this->d_pm_commit_gbo->Location = System::Drawing::Point(19, 234);
		this->d_pm_commit_gbo->Name = L"d_pm_commit_gbo";
		this->d_pm_commit_gbo->Size = System::Drawing::Size(385, 73);
		this->d_pm_commit_gbo->TabIndex = 7;
		this->d_pm_commit_gbo->TabStop = false;
		this->d_pm_commit_gbo->Text = L"commit";
		// 
		// d_pm_commit_btn
		// 
		this->d_pm_commit_btn->Location = System::Drawing::Point(281, 44);
		this->d_pm_commit_btn->Name = L"d_pm_commit_btn";
		this->d_pm_commit_btn->Size = System::Drawing::Size(75, 23);
		this->d_pm_commit_btn->TabIndex = 0;
		this->d_pm_commit_btn->Text = L"commint";
		this->d_pm_commit_btn->UseVisualStyleBackColor = true;
		this->d_pm_commit_btn->Click += gcnew System::EventHandler(this, &MainForm::d_pm_commit_btn_Click);
		// 
		// c_player_chat_pag
		// 
		this->c_player_chat_pag->Controls->Add(this->c_player_chat_pal);
		this->c_player_chat_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_chat_pag->Name = L"c_player_chat_pag";
		this->c_player_chat_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_chat_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_chat_pag->TabIndex = 1;
		this->c_player_chat_pag->Text = L"chat";
		this->c_player_chat_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_chat_pal
		// 
		this->c_player_chat_pal->Controls->Add(this->d_pc_pal);
		this->c_player_chat_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_chat_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_chat_pal->Name = L"c_player_chat_pal";
		this->c_player_chat_pal->Size = System::Drawing::Size(447, 438);
		this->c_player_chat_pal->TabIndex = 0;
		// 
		// d_pc_pal
		// 
		this->d_pc_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_pc_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_pc_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_pc_pal->Controls->Add(this->d_pc_player_info_gbo);
		this->d_pc_pal->Controls->Add(this->d_pc_record_gbo);
		this->d_pc_pal->Controls->Add(this->d_pc_commit_gbo);
		this->d_pc_pal->Controls->Add(this->d_pc_forbid_gbo);
		this->d_pc_pal->Location = System::Drawing::Point(25, 14);
		this->d_pc_pal->Name = L"d_pc_pal";
		this->d_pc_pal->Size = System::Drawing::Size(392, 394);
		this->d_pc_pal->TabIndex = 1;
		// 
		// d_pc_player_info_gbo
		// 
		this->d_pc_player_info_gbo->Controls->Add(this->d_pc_username_edt);
		this->d_pc_player_info_gbo->Controls->Add(this->d_pc_server_cbo);
		this->d_pc_player_info_gbo->Controls->Add(this->d_pc_playername_lbl);
		this->d_pc_player_info_gbo->Controls->Add(this->d_pc_server_lbl);
		this->d_pc_player_info_gbo->Location = System::Drawing::Point(178, 66);
		this->d_pc_player_info_gbo->Name = L"d_pc_player_info_gbo";
		this->d_pc_player_info_gbo->Size = System::Drawing::Size(197, 87);
		this->d_pc_player_info_gbo->TabIndex = 10;
		this->d_pc_player_info_gbo->TabStop = false;
		this->d_pc_player_info_gbo->Text = L"player info";
		// 
		// d_pc_username_edt
		// 
		this->d_pc_username_edt->FormattingEnabled = true;
		this->d_pc_username_edt->Location = System::Drawing::Point(84, 54);
		this->d_pc_username_edt->Name = L"d_pc_username_edt";
		this->d_pc_username_edt->Size = System::Drawing::Size(103, 20);
		this->d_pc_username_edt->TabIndex = 22;
		// 
		// d_pc_server_cbo
		// 
		this->d_pc_server_cbo->FormattingEnabled = true;
		this->d_pc_server_cbo->Location = System::Drawing::Point(84, 21);
		this->d_pc_server_cbo->Name = L"d_pc_server_cbo";
		this->d_pc_server_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pc_server_cbo->TabIndex = 21;
		// 
		// d_pc_playername_lbl
		// 
		this->d_pc_playername_lbl->AutoSize = true;
		this->d_pc_playername_lbl->Location = System::Drawing::Point(11, 56);
		this->d_pc_playername_lbl->Name = L"d_pc_playername_lbl";
		this->d_pc_playername_lbl->Size = System::Drawing::Size(65, 12);
		this->d_pc_playername_lbl->TabIndex = 20;
		this->d_pc_playername_lbl->Text = L"playername";
		// 
		// d_pc_server_lbl
		// 
		this->d_pc_server_lbl->AutoSize = true;
		this->d_pc_server_lbl->Location = System::Drawing::Point(11, 25);
		this->d_pc_server_lbl->Name = L"d_pc_server_lbl";
		this->d_pc_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pc_server_lbl->TabIndex = 19;
		this->d_pc_server_lbl->Text = L"server";
		// 
		// d_pc_record_gbo
		// 
		this->d_pc_record_gbo->Controls->Add(this->d_pc_group_list);
		this->d_pc_record_gbo->Controls->Add(this->d_pc_filter_pnl);
		this->d_pc_record_gbo->Location = System::Drawing::Point(12, 11);
		this->d_pc_record_gbo->Name = L"d_pc_record_gbo";
		this->d_pc_record_gbo->Size = System::Drawing::Size(154, 369);
		this->d_pc_record_gbo->TabIndex = 9;
		this->d_pc_record_gbo->TabStop = false;
		this->d_pc_record_gbo->Text = L"record";
		// 
		// d_pc_group_list
		// 
		this->d_pc_group_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->dpc_column_account_name, 
			this->dpc_column_player_name, this->dpc_column_time});
		this->d_pc_group_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_pc_group_list->FullRowSelect = true;
		this->d_pc_group_list->GridLines = true;
		this->d_pc_group_list->HideSelection = false;
		this->d_pc_group_list->Location = System::Drawing::Point(3, 74);
		this->d_pc_group_list->Name = L"d_pc_group_list";
		this->d_pc_group_list->Size = System::Drawing::Size(148, 292);
		this->d_pc_group_list->TabIndex = 25;
		this->d_pc_group_list->UseCompatibleStateImageBehavior = false;
		this->d_pc_group_list->View = System::Windows::Forms::View::Details;
		this->d_pc_group_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_pc_group_list_MouseDoubleClick);
		// 
		// dpc_column_account_name
		// 
		this->dpc_column_account_name->Text = L"account name";
		// 
		// dpc_column_player_name
		// 
		this->dpc_column_player_name->Text = L"player name";
		// 
		// dpc_column_time
		// 
		this->dpc_column_time->Text = L"forbidden time";
		this->dpc_column_time->Width = 200;
		// 
		// d_pc_filter_pnl
		// 
		this->d_pc_filter_pnl->Controls->Add(this->d_pc_filter_server_cbo);
		this->d_pc_filter_pnl->Controls->Add(this->d_pc_filter_server_lbl);
		this->d_pc_filter_pnl->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_pc_filter_pnl->Location = System::Drawing::Point(3, 17);
		this->d_pc_filter_pnl->Name = L"d_pc_filter_pnl";
		this->d_pc_filter_pnl->Size = System::Drawing::Size(148, 57);
		this->d_pc_filter_pnl->TabIndex = 24;
		// 
		// d_pc_filter_server_cbo
		// 
		this->d_pc_filter_server_cbo->FormattingEnabled = true;
		this->d_pc_filter_server_cbo->Location = System::Drawing::Point(11, 26);
		this->d_pc_filter_server_cbo->Name = L"d_pc_filter_server_cbo";
		this->d_pc_filter_server_cbo->Size = System::Drawing::Size(125, 20);
		this->d_pc_filter_server_cbo->TabIndex = 25;
		this->d_pc_filter_server_cbo->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pc_filter_server_cbo_SelectedIndexChanged);
		// 
		// d_pc_filter_server_lbl
		// 
		this->d_pc_filter_server_lbl->AutoSize = true;
		this->d_pc_filter_server_lbl->Location = System::Drawing::Point(9, 7);
		this->d_pc_filter_server_lbl->Name = L"d_pc_filter_server_lbl";
		this->d_pc_filter_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pc_filter_server_lbl->TabIndex = 24;
		this->d_pc_filter_server_lbl->Text = L"server";
		// 
		// d_pc_commit_gbo
		// 
		this->d_pc_commit_gbo->Controls->Add(this->d_pc_commit_reason_btn);
		this->d_pc_commit_gbo->Location = System::Drawing::Point(179, 283);
		this->d_pc_commit_gbo->Name = L"d_pc_commit_gbo";
		this->d_pc_commit_gbo->Size = System::Drawing::Size(197, 45);
		this->d_pc_commit_gbo->TabIndex = 7;
		this->d_pc_commit_gbo->TabStop = false;
		this->d_pc_commit_gbo->Text = L"commit";
		// 
		// d_pc_commit_reason_btn
		// 
		this->d_pc_commit_reason_btn->Location = System::Drawing::Point(112, 15);
		this->d_pc_commit_reason_btn->Name = L"d_pc_commit_reason_btn";
		this->d_pc_commit_reason_btn->Size = System::Drawing::Size(75, 23);
		this->d_pc_commit_reason_btn->TabIndex = 0;
		this->d_pc_commit_reason_btn->Text = L"commint";
		this->d_pc_commit_reason_btn->UseVisualStyleBackColor = true;
		this->d_pc_commit_reason_btn->Click += gcnew System::EventHandler(this, &MainForm::d_pc_commit_reason_btn_Click);
		// 
		// d_pc_forbid_gbo
		// 
		this->d_pc_forbid_gbo->Controls->Add(this->d_pc_min_lbl);
		this->d_pc_forbid_gbo->Controls->Add(this->d_pc_unforbit_rdo);
		this->d_pc_forbid_gbo->Controls->Add(this->d_pc_forbit_rdo);
		this->d_pc_forbid_gbo->Controls->Add(this->d_pc_time_cbo);
		this->d_pc_forbid_gbo->Controls->Add(this->d_pc_time_lbl);
		this->d_pc_forbid_gbo->Location = System::Drawing::Point(179, 159);
		this->d_pc_forbid_gbo->Name = L"d_pc_forbid_gbo";
		this->d_pc_forbid_gbo->Size = System::Drawing::Size(197, 118);
		this->d_pc_forbid_gbo->TabIndex = 6;
		this->d_pc_forbid_gbo->TabStop = false;
		this->d_pc_forbid_gbo->Text = L"forbid";
		// 
		// d_pc_min_lbl
		// 
		this->d_pc_min_lbl->AutoSize = true;
		this->d_pc_min_lbl->Enabled = false;
		this->d_pc_min_lbl->Location = System::Drawing::Point(146, 90);
		this->d_pc_min_lbl->Name = L"d_pc_min_lbl";
		this->d_pc_min_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pc_min_lbl->TabIndex = 9;
		this->d_pc_min_lbl->Text = L"minute";
		// 
		// d_pc_unforbit_rdo
		// 
		this->d_pc_unforbit_rdo->AutoSize = true;
		this->d_pc_unforbit_rdo->Location = System::Drawing::Point(17, 22);
		this->d_pc_unforbit_rdo->Name = L"d_pc_unforbit_rdo";
		this->d_pc_unforbit_rdo->Size = System::Drawing::Size(71, 16);
		this->d_pc_unforbit_rdo->TabIndex = 8;
		this->d_pc_unforbit_rdo->TabStop = true;
		this->d_pc_unforbit_rdo->Text = L"unForbid";
		this->d_pc_unforbit_rdo->UseVisualStyleBackColor = true;
		// 
		// d_pc_forbit_rdo
		// 
		this->d_pc_forbit_rdo->AutoSize = true;
		this->d_pc_forbit_rdo->Location = System::Drawing::Point(17, 46);
		this->d_pc_forbit_rdo->Name = L"d_pc_forbit_rdo";
		this->d_pc_forbit_rdo->Size = System::Drawing::Size(59, 16);
		this->d_pc_forbit_rdo->TabIndex = 7;
		this->d_pc_forbit_rdo->TabStop = true;
		this->d_pc_forbit_rdo->Text = L"Forbid";
		this->d_pc_forbit_rdo->UseVisualStyleBackColor = true;
		this->d_pc_forbit_rdo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pc_forbit_rdo_CheckedChanged);
		// 
		// d_pc_time_cbo
		// 
		this->d_pc_time_cbo->Enabled = false;
		this->d_pc_time_cbo->FormattingEnabled = true;
		this->d_pc_time_cbo->Location = System::Drawing::Point(83, 87);
		this->d_pc_time_cbo->Name = L"d_pc_time_cbo";
		this->d_pc_time_cbo->Size = System::Drawing::Size(57, 20);
		this->d_pc_time_cbo->TabIndex = 2;
		// 
		// d_pc_time_lbl
		// 
		this->d_pc_time_lbl->AutoSize = true;
		this->d_pc_time_lbl->Enabled = false;
		this->d_pc_time_lbl->Location = System::Drawing::Point(81, 69);
		this->d_pc_time_lbl->Name = L"d_pc_time_lbl";
		this->d_pc_time_lbl->Size = System::Drawing::Size(29, 12);
		this->d_pc_time_lbl->TabIndex = 0;
		this->d_pc_time_lbl->Text = L"time";
		// 
		// c_player_kick_pag
		// 
		this->c_player_kick_pag->Controls->Add(this->c_player_kick_pal);
		this->c_player_kick_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_kick_pag->Name = L"c_player_kick_pag";
		this->c_player_kick_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_kick_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_kick_pag->TabIndex = 2;
		this->c_player_kick_pag->Text = L"kick";
		this->c_player_kick_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_kick_pal
		// 
		this->c_player_kick_pal->Controls->Add(this->d_pk_pal);
		this->c_player_kick_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_kick_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_kick_pal->Name = L"c_player_kick_pal";
		this->c_player_kick_pal->Size = System::Drawing::Size(447, 438);
		this->c_player_kick_pal->TabIndex = 1;
		// 
		// d_pk_pal
		// 
		this->d_pk_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_pk_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_pk_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_pk_pal->Controls->Add(this->d_pk_player_info_gbo);
		this->d_pk_pal->Controls->Add(this->d_pk_record_gbo);
		this->d_pk_pal->Controls->Add(this->d_pk_commit_gbo);
		this->d_pk_pal->Controls->Add(this->d_pk_forbid_gbo);
		this->d_pk_pal->Location = System::Drawing::Point(22, 14);
		this->d_pk_pal->Name = L"d_pk_pal";
		this->d_pk_pal->Size = System::Drawing::Size(392, 394);
		this->d_pk_pal->TabIndex = 3;
		// 
		// d_pk_player_info_gbo
		// 
		this->d_pk_player_info_gbo->Controls->Add(this->d_pk_username_edt);
		this->d_pk_player_info_gbo->Controls->Add(this->d_pk_server_cbo);
		this->d_pk_player_info_gbo->Controls->Add(this->d_pk_username_lbl);
		this->d_pk_player_info_gbo->Controls->Add(this->d_pk_server_lbl);
		this->d_pk_player_info_gbo->Location = System::Drawing::Point(176, 85);
		this->d_pk_player_info_gbo->Name = L"d_pk_player_info_gbo";
		this->d_pk_player_info_gbo->Size = System::Drawing::Size(203, 93);
		this->d_pk_player_info_gbo->TabIndex = 10;
		this->d_pk_player_info_gbo->TabStop = false;
		this->d_pk_player_info_gbo->Text = L"player info";
		// 
		// d_pk_username_edt
		// 
		this->d_pk_username_edt->Location = System::Drawing::Point(88, 57);
		this->d_pk_username_edt->Name = L"d_pk_username_edt";
		this->d_pk_username_edt->Size = System::Drawing::Size(103, 21);
		this->d_pk_username_edt->TabIndex = 21;
		// 
		// d_pk_server_cbo
		// 
		this->d_pk_server_cbo->FormattingEnabled = true;
		this->d_pk_server_cbo->Location = System::Drawing::Point(88, 27);
		this->d_pk_server_cbo->Name = L"d_pk_server_cbo";
		this->d_pk_server_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pk_server_cbo->TabIndex = 20;
		// 
		// d_pk_username_lbl
		// 
		this->d_pk_username_lbl->AutoSize = true;
		this->d_pk_username_lbl->Location = System::Drawing::Point(16, 60);
		this->d_pk_username_lbl->Name = L"d_pk_username_lbl";
		this->d_pk_username_lbl->Size = System::Drawing::Size(77, 12);
		this->d_pk_username_lbl->TabIndex = 19;
		this->d_pk_username_lbl->Text = L"account name";
		// 
		// d_pk_server_lbl
		// 
		this->d_pk_server_lbl->AutoSize = true;
		this->d_pk_server_lbl->Location = System::Drawing::Point(16, 30);
		this->d_pk_server_lbl->Name = L"d_pk_server_lbl";
		this->d_pk_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pk_server_lbl->TabIndex = 18;
		this->d_pk_server_lbl->Text = L"server";
		// 
		// d_pk_record_gbo
		// 
		this->d_pk_record_gbo->Controls->Add(this->d_pk_record_list);
		this->d_pk_record_gbo->Controls->Add(this->d_pk_record_pnl);
		this->d_pk_record_gbo->Location = System::Drawing::Point(12, 11);
		this->d_pk_record_gbo->Name = L"d_pk_record_gbo";
		this->d_pk_record_gbo->Size = System::Drawing::Size(154, 369);
		this->d_pk_record_gbo->TabIndex = 9;
		this->d_pk_record_gbo->TabStop = false;
		this->d_pk_record_gbo->Text = L"record";
		// 
		// d_pk_record_list
		// 
		this->d_pk_record_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dpk_column_account_name, 
			this->dpk_column_end_time});
		this->d_pk_record_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_pk_record_list->FullRowSelect = true;
		this->d_pk_record_list->GridLines = true;
		this->d_pk_record_list->HideSelection = false;
		this->d_pk_record_list->Location = System::Drawing::Point(3, 74);
		this->d_pk_record_list->Name = L"d_pk_record_list";
		this->d_pk_record_list->Size = System::Drawing::Size(148, 292);
		this->d_pk_record_list->TabIndex = 3;
		this->d_pk_record_list->UseCompatibleStateImageBehavior = false;
		this->d_pk_record_list->View = System::Windows::Forms::View::Details;
		this->d_pk_record_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_pk_record_list_MouseDoubleClick);
		// 
		// dpk_column_account_name
		// 
		this->dpk_column_account_name->Text = L"account name";
		this->dpk_column_account_name->Width = 76;
		// 
		// dpk_column_end_time
		// 
		this->dpk_column_end_time->Text = L"end tiem";
		this->dpk_column_end_time->Width = 200;
		// 
		// d_pk_record_pnl
		// 
		this->d_pk_record_pnl->Controls->Add(this->d_pk_filter_server_lbl);
		this->d_pk_record_pnl->Controls->Add(this->d_pk_filter_server_cbo);
		this->d_pk_record_pnl->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_pk_record_pnl->Location = System::Drawing::Point(3, 17);
		this->d_pk_record_pnl->Name = L"d_pk_record_pnl";
		this->d_pk_record_pnl->Size = System::Drawing::Size(148, 57);
		this->d_pk_record_pnl->TabIndex = 2;
		// 
		// d_pk_filter_server_lbl
		// 
		this->d_pk_filter_server_lbl->AutoSize = true;
		this->d_pk_filter_server_lbl->Location = System::Drawing::Point(5, 7);
		this->d_pk_filter_server_lbl->Name = L"d_pk_filter_server_lbl";
		this->d_pk_filter_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pk_filter_server_lbl->TabIndex = 25;
		this->d_pk_filter_server_lbl->Text = L"server";
		// 
		// d_pk_filter_server_cbo
		// 
		this->d_pk_filter_server_cbo->FormattingEnabled = true;
		this->d_pk_filter_server_cbo->Location = System::Drawing::Point(7, 25);
		this->d_pk_filter_server_cbo->Name = L"d_pk_filter_server_cbo";
		this->d_pk_filter_server_cbo->Size = System::Drawing::Size(134, 20);
		this->d_pk_filter_server_cbo->TabIndex = 21;
		this->d_pk_filter_server_cbo->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pk_filter_server_cbo_SelectedIndexChanged);
		// 
		// d_pk_commit_gbo
		// 
		this->d_pk_commit_gbo->Controls->Add(this->d_pk_commit_reason_btn);
		this->d_pk_commit_gbo->Location = System::Drawing::Point(176, 310);
		this->d_pk_commit_gbo->Name = L"d_pk_commit_gbo";
		this->d_pk_commit_gbo->Size = System::Drawing::Size(203, 45);
		this->d_pk_commit_gbo->TabIndex = 7;
		this->d_pk_commit_gbo->TabStop = false;
		this->d_pk_commit_gbo->Text = L"commit";
		// 
		// d_pk_commit_reason_btn
		// 
		this->d_pk_commit_reason_btn->Location = System::Drawing::Point(118, 14);
		this->d_pk_commit_reason_btn->Name = L"d_pk_commit_reason_btn";
		this->d_pk_commit_reason_btn->Size = System::Drawing::Size(75, 23);
		this->d_pk_commit_reason_btn->TabIndex = 0;
		this->d_pk_commit_reason_btn->Text = L"commint";
		this->d_pk_commit_reason_btn->UseVisualStyleBackColor = true;
		this->d_pk_commit_reason_btn->Click += gcnew System::EventHandler(this, &MainForm::d_pk_commit_reason_btn_Click);
		// 
		// d_pk_forbid_gbo
		// 
		this->d_pk_forbid_gbo->Controls->Add(this->d_pk_hour_lbl);
		this->d_pk_forbid_gbo->Controls->Add(this->d_pk_forbid_lbl);
		this->d_pk_forbid_gbo->Controls->Add(this->d_pk_unforbid_lbl);
		this->d_pk_forbid_gbo->Controls->Add(this->d_pk_time_cbo);
		this->d_pk_forbid_gbo->Controls->Add(this->d_pk_time_lbl);
		this->d_pk_forbid_gbo->Location = System::Drawing::Point(176, 193);
		this->d_pk_forbid_gbo->Name = L"d_pk_forbid_gbo";
		this->d_pk_forbid_gbo->Size = System::Drawing::Size(203, 111);
		this->d_pk_forbid_gbo->TabIndex = 6;
		this->d_pk_forbid_gbo->TabStop = false;
		this->d_pk_forbid_gbo->Text = L"kick";
		// 
		// d_pk_hour_lbl
		// 
		this->d_pk_hour_lbl->AutoSize = true;
		this->d_pk_hour_lbl->Enabled = false;
		this->d_pk_hour_lbl->Location = System::Drawing::Point(152, 84);
		this->d_pk_hour_lbl->Name = L"d_pk_hour_lbl";
		this->d_pk_hour_lbl->Size = System::Drawing::Size(29, 12);
		this->d_pk_hour_lbl->TabIndex = 11;
		this->d_pk_hour_lbl->Text = L"hour";
		// 
		// d_pk_forbid_lbl
		// 
		this->d_pk_forbid_lbl->AutoSize = true;
		this->d_pk_forbid_lbl->Location = System::Drawing::Point(18, 42);
		this->d_pk_forbid_lbl->Name = L"d_pk_forbid_lbl";
		this->d_pk_forbid_lbl->Size = System::Drawing::Size(59, 16);
		this->d_pk_forbid_lbl->TabIndex = 10;
		this->d_pk_forbid_lbl->TabStop = true;
		this->d_pk_forbid_lbl->Text = L"forbid";
		this->d_pk_forbid_lbl->UseVisualStyleBackColor = true;
		this->d_pk_forbid_lbl->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pk_forbid_lbl_CheckedChanged);
		// 
		// d_pk_unforbid_lbl
		// 
		this->d_pk_unforbid_lbl->AutoSize = true;
		this->d_pk_unforbid_lbl->Location = System::Drawing::Point(18, 20);
		this->d_pk_unforbid_lbl->Name = L"d_pk_unforbid_lbl";
		this->d_pk_unforbid_lbl->Size = System::Drawing::Size(71, 16);
		this->d_pk_unforbid_lbl->TabIndex = 9;
		this->d_pk_unforbid_lbl->TabStop = true;
		this->d_pk_unforbid_lbl->Text = L"unForbid";
		this->d_pk_unforbid_lbl->UseVisualStyleBackColor = true;
		// 
		// d_pk_time_cbo
		// 
		this->d_pk_time_cbo->Enabled = false;
		this->d_pk_time_cbo->FormattingEnabled = true;
		this->d_pk_time_cbo->Location = System::Drawing::Point(88, 80);
		this->d_pk_time_cbo->Name = L"d_pk_time_cbo";
		this->d_pk_time_cbo->Size = System::Drawing::Size(57, 20);
		this->d_pk_time_cbo->TabIndex = 2;
		// 
		// d_pk_time_lbl
		// 
		this->d_pk_time_lbl->AutoSize = true;
		this->d_pk_time_lbl->Enabled = false;
		this->d_pk_time_lbl->Location = System::Drawing::Point(86, 60);
		this->d_pk_time_lbl->Name = L"d_pk_time_lbl";
		this->d_pk_time_lbl->Size = System::Drawing::Size(29, 12);
		this->d_pk_time_lbl->TabIndex = 0;
		this->d_pk_time_lbl->Text = L"time";
		// 
		// c_player_item_pag
		// 
		this->c_player_item_pag->Controls->Add(this->c_player_item_pal);
		this->c_player_item_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_item_pag->Name = L"c_player_item_pag";
		this->c_player_item_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_item_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_item_pag->TabIndex = 3;
		this->c_player_item_pag->Text = L"item";
		this->c_player_item_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_item_pal
		// 
		this->c_player_item_pal->Controls->Add(this->d_pi_pal);
		this->c_player_item_pal->Location = System::Drawing::Point(26, 43);
		this->c_player_item_pal->Name = L"c_player_item_pal";
		this->c_player_item_pal->Size = System::Drawing::Size(424, 398);
		this->c_player_item_pal->TabIndex = 1;
		// 
		// d_pi_pal
		// 
		this->d_pi_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_pi_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_pi_pal->Controls->Add(this->d_pi_config_gbo);
		this->d_pi_pal->Controls->Add(this->d_pi_commit_gbo);
		this->d_pi_pal->Controls->Add(this->d_pi_item_info_gbo);
		this->d_pi_pal->Location = System::Drawing::Point(28, 14);
		this->d_pi_pal->Name = L"d_pi_pal";
		this->d_pi_pal->Size = System::Drawing::Size(392, 394);
		this->d_pi_pal->TabIndex = 3;
		// 
		// d_pi_config_gbo
		// 
		this->d_pi_config_gbo->Controls->Add(this->d_pi_config_tab);
		this->d_pi_config_gbo->Location = System::Drawing::Point(16, 8);
		this->d_pi_config_gbo->Name = L"d_pi_config_gbo";
		this->d_pi_config_gbo->Size = System::Drawing::Size(357, 196);
		this->d_pi_config_gbo->TabIndex = 9;
		this->d_pi_config_gbo->TabStop = false;
		this->d_pi_config_gbo->Text = L"config";
		// 
		// d_pi_config_tab
		// 
		this->d_pi_config_tab->Controls->Add(this->d_pi_single_pag);
		this->d_pi_config_tab->Controls->Add(this->d_pi_group_pag);
		this->d_pi_config_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_pi_config_tab->Location = System::Drawing::Point(3, 17);
		this->d_pi_config_tab->Name = L"d_pi_config_tab";
		this->d_pi_config_tab->SelectedIndex = 0;
		this->d_pi_config_tab->Size = System::Drawing::Size(351, 176);
		this->d_pi_config_tab->TabIndex = 0;
		// 
		// d_pi_single_pag
		// 
		this->d_pi_single_pag->Controls->Add(this->d_pi_all_player_cekb);
		this->d_pi_single_pag->Controls->Add(this->d_pi_username_edt);
		this->d_pi_single_pag->Controls->Add(this->d_pi_server_cbo);
		this->d_pi_single_pag->Controls->Add(this->d_pi_username_lbl);
		this->d_pi_single_pag->Controls->Add(this->d_pi_server_lbl);
		this->d_pi_single_pag->Location = System::Drawing::Point(4, 21);
		this->d_pi_single_pag->Name = L"d_pi_single_pag";
		this->d_pi_single_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_pi_single_pag->Size = System::Drawing::Size(343, 151);
		this->d_pi_single_pag->TabIndex = 0;
		this->d_pi_single_pag->Text = L"single";
		this->d_pi_single_pag->UseVisualStyleBackColor = true;
		// 
		// d_pi_all_player_cekb
		// 
		this->d_pi_all_player_cekb->AutoSize = true;
		this->d_pi_all_player_cekb->Location = System::Drawing::Point(6, 132);
		this->d_pi_all_player_cekb->Name = L"d_pi_all_player_cekb";
		this->d_pi_all_player_cekb->Size = System::Drawing::Size(114, 16);
		this->d_pi_all_player_cekb->TabIndex = 18;
		this->d_pi_all_player_cekb->Text = L"send all player";
		this->d_pi_all_player_cekb->UseVisualStyleBackColor = true;
		this->d_pi_all_player_cekb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_pi_all_player_cekb_CheckedChanged);
		// 
		// d_pi_username_edt
		// 
		this->d_pi_username_edt->Location = System::Drawing::Point(116, 66);
		this->d_pi_username_edt->Name = L"d_pi_username_edt";
		this->d_pi_username_edt->Size = System::Drawing::Size(103, 21);
		this->d_pi_username_edt->TabIndex = 17;
		// 
		// d_pi_server_cbo
		// 
		this->d_pi_server_cbo->FormattingEnabled = true;
		this->d_pi_server_cbo->Location = System::Drawing::Point(116, 36);
		this->d_pi_server_cbo->Name = L"d_pi_server_cbo";
		this->d_pi_server_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pi_server_cbo->TabIndex = 16;
		// 
		// d_pi_username_lbl
		// 
		this->d_pi_username_lbl->AutoSize = true;
		this->d_pi_username_lbl->Location = System::Drawing::Point(57, 69);
		this->d_pi_username_lbl->Name = L"d_pi_username_lbl";
		this->d_pi_username_lbl->Size = System::Drawing::Size(53, 12);
		this->d_pi_username_lbl->TabIndex = 15;
		this->d_pi_username_lbl->Text = L"username";
		// 
		// d_pi_server_lbl
		// 
		this->d_pi_server_lbl->AutoSize = true;
		this->d_pi_server_lbl->Location = System::Drawing::Point(57, 39);
		this->d_pi_server_lbl->Name = L"d_pi_server_lbl";
		this->d_pi_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pi_server_lbl->TabIndex = 14;
		this->d_pi_server_lbl->Text = L"server";
		// 
		// d_pi_group_pag
		// 
		this->d_pi_group_pag->Controls->Add(this->d_pi_group_list);
		this->d_pi_group_pag->Location = System::Drawing::Point(4, 21);
		this->d_pi_group_pag->Name = L"d_pi_group_pag";
		this->d_pi_group_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_pi_group_pag->Size = System::Drawing::Size(343, 151);
		this->d_pi_group_pag->TabIndex = 1;
		this->d_pi_group_pag->Text = L"group";
		this->d_pi_group_pag->UseVisualStyleBackColor = true;
		// 
		// d_pi_group_list
		// 
		this->d_pi_group_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dpi_column_region_name, 
			this->dpi_column_name});
		this->d_pi_group_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_pi_group_list->FullRowSelect = true;
		this->d_pi_group_list->GridLines = true;
		this->d_pi_group_list->HideSelection = false;
		this->d_pi_group_list->Location = System::Drawing::Point(3, 3);
		this->d_pi_group_list->Name = L"d_pi_group_list";
		this->d_pi_group_list->Size = System::Drawing::Size(337, 145);
		this->d_pi_group_list->TabIndex = 0;
		this->d_pi_group_list->UseCompatibleStateImageBehavior = false;
		this->d_pi_group_list->View = System::Windows::Forms::View::Details;
		this->d_pi_group_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_pi_group_list_MouseDoubleClick);
		// 
		// dpi_column_region_name
		// 
		this->dpi_column_region_name->Text = L"region_name";
		this->dpi_column_region_name->Width = 100;
		// 
		// dpi_column_name
		// 
		this->dpi_column_name->Text = L"name";
		this->dpi_column_name->Width = 120;
		// 
		// d_pi_commit_gbo
		// 
		this->d_pi_commit_gbo->Controls->Add(this->d_pi_commit_reason_btn);
		this->d_pi_commit_gbo->Location = System::Drawing::Point(16, 335);
		this->d_pi_commit_gbo->Name = L"d_pi_commit_gbo";
		this->d_pi_commit_gbo->Size = System::Drawing::Size(357, 45);
		this->d_pi_commit_gbo->TabIndex = 7;
		this->d_pi_commit_gbo->TabStop = false;
		this->d_pi_commit_gbo->Text = L"commit";
		// 
		// d_pi_commit_reason_btn
		// 
		this->d_pi_commit_reason_btn->Location = System::Drawing::Point(267, 15);
		this->d_pi_commit_reason_btn->Name = L"d_pi_commit_reason_btn";
		this->d_pi_commit_reason_btn->Size = System::Drawing::Size(75, 23);
		this->d_pi_commit_reason_btn->TabIndex = 0;
		this->d_pi_commit_reason_btn->Text = L"commint";
		this->d_pi_commit_reason_btn->UseVisualStyleBackColor = true;
		this->d_pi_commit_reason_btn->Click += gcnew System::EventHandler(this, &MainForm::d_pi_commit_reason_btn_Click);
		// 
		// d_pi_item_info_gbo
		// 
		this->d_pi_item_info_gbo->Controls->Add(this->d_pi_type_tab);
		this->d_pi_item_info_gbo->Location = System::Drawing::Point(16, 210);
		this->d_pi_item_info_gbo->Name = L"d_pi_item_info_gbo";
		this->d_pi_item_info_gbo->Size = System::Drawing::Size(357, 119);
		this->d_pi_item_info_gbo->TabIndex = 6;
		this->d_pi_item_info_gbo->TabStop = false;
		this->d_pi_item_info_gbo->Text = L"item";
		// 
		// d_pi_type_tab
		// 
		this->d_pi_type_tab->Controls->Add(this->d_pi_item_pag);
		this->d_pi_type_tab->Controls->Add(this->d_pi_money_pag);
		this->d_pi_type_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_pi_type_tab->Location = System::Drawing::Point(3, 17);
		this->d_pi_type_tab->Name = L"d_pi_type_tab";
		this->d_pi_type_tab->SelectedIndex = 0;
		this->d_pi_type_tab->Size = System::Drawing::Size(351, 99);
		this->d_pi_type_tab->TabIndex = 22;
		// 
		// d_pi_item_pag
		// 
		this->d_pi_item_pag->Controls->Add(this->d_pi_id_cbo);
		this->d_pi_item_pag->Controls->Add(this->d_pi_name_cbo);
		this->d_pi_item_pag->Controls->Add(this->d_pi_number_num);
		this->d_pi_item_pag->Controls->Add(this->d_pi_number_lbl);
		this->d_pi_item_pag->Controls->Add(this->d_pi_lvl_cbo);
		this->d_pi_item_pag->Controls->Add(this->d_pi_lvl_lbl);
		this->d_pi_item_pag->Controls->Add(this->d_pi_name_lbl);
		this->d_pi_item_pag->Controls->Add(this->d_pi_quality_cbo);
		this->d_pi_item_pag->Controls->Add(this->d_pi_quality_lbl);
		this->d_pi_item_pag->Controls->Add(this->d_pi_id_lbl);
		this->d_pi_item_pag->Location = System::Drawing::Point(4, 21);
		this->d_pi_item_pag->Name = L"d_pi_item_pag";
		this->d_pi_item_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_pi_item_pag->Size = System::Drawing::Size(343, 74);
		this->d_pi_item_pag->TabIndex = 0;
		this->d_pi_item_pag->Text = L"item";
		this->d_pi_item_pag->UseVisualStyleBackColor = true;
		// 
		// d_pi_id_cbo
		// 
		this->d_pi_id_cbo->FormattingEnabled = true;
		this->d_pi_id_cbo->Location = System::Drawing::Point(261, 12);
		this->d_pi_id_cbo->Name = L"d_pi_id_cbo";
		this->d_pi_id_cbo->Size = System::Drawing::Size(73, 20);
		this->d_pi_id_cbo->TabIndex = 31;
		this->d_pi_id_cbo->TextChanged += gcnew System::EventHandler(this, &MainForm::d_pi_id_cbo_TextChanged);
		// 
		// d_pi_name_cbo
		// 
		this->d_pi_name_cbo->FormattingEnabled = true;
		this->d_pi_name_cbo->Location = System::Drawing::Point(59, 12);
		this->d_pi_name_cbo->Name = L"d_pi_name_cbo";
		this->d_pi_name_cbo->Size = System::Drawing::Size(160, 20);
		this->d_pi_name_cbo->TabIndex = 30;
		// 
		// d_pi_number_num
		// 
		this->d_pi_number_num->Location = System::Drawing::Point(59, 42);
		this->d_pi_number_num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99, 0, 0, 0});
		this->d_pi_number_num->Name = L"d_pi_number_num";
		this->d_pi_number_num->Size = System::Drawing::Size(38, 21);
		this->d_pi_number_num->TabIndex = 29;
		// 
		// d_pi_number_lbl
		// 
		this->d_pi_number_lbl->AutoSize = true;
		this->d_pi_number_lbl->Location = System::Drawing::Point(9, 45);
		this->d_pi_number_lbl->Name = L"d_pi_number_lbl";
		this->d_pi_number_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pi_number_lbl->TabIndex = 28;
		this->d_pi_number_lbl->Text = L"number";
		// 
		// d_pi_lvl_cbo
		// 
		this->d_pi_lvl_cbo->FormattingEnabled = true;
		this->d_pi_lvl_cbo->Location = System::Drawing::Point(278, 43);
		this->d_pi_lvl_cbo->Name = L"d_pi_lvl_cbo";
		this->d_pi_lvl_cbo->Size = System::Drawing::Size(56, 20);
		this->d_pi_lvl_cbo->TabIndex = 27;
		this->d_pi_lvl_cbo->Visible = false;
		// 
		// d_pi_lvl_lbl
		// 
		this->d_pi_lvl_lbl->AutoSize = true;
		this->d_pi_lvl_lbl->Location = System::Drawing::Point(233, 46);
		this->d_pi_lvl_lbl->Name = L"d_pi_lvl_lbl";
		this->d_pi_lvl_lbl->Size = System::Drawing::Size(23, 12);
		this->d_pi_lvl_lbl->TabIndex = 26;
		this->d_pi_lvl_lbl->Text = L"lvl";
		this->d_pi_lvl_lbl->Visible = false;
		// 
		// d_pi_name_lbl
		// 
		this->d_pi_name_lbl->AutoSize = true;
		this->d_pi_name_lbl->Location = System::Drawing::Point(10, 15);
		this->d_pi_name_lbl->Name = L"d_pi_name_lbl";
		this->d_pi_name_lbl->Size = System::Drawing::Size(29, 12);
		this->d_pi_name_lbl->TabIndex = 25;
		this->d_pi_name_lbl->Text = L"name";
		// 
		// d_pi_quality_cbo
		// 
		this->d_pi_quality_cbo->FormattingEnabled = true;
		this->d_pi_quality_cbo->Location = System::Drawing::Point(163, 43);
		this->d_pi_quality_cbo->Name = L"d_pi_quality_cbo";
		this->d_pi_quality_cbo->Size = System::Drawing::Size(56, 20);
		this->d_pi_quality_cbo->TabIndex = 24;
		this->d_pi_quality_cbo->Visible = false;
		// 
		// d_pi_quality_lbl
		// 
		this->d_pi_quality_lbl->AutoSize = true;
		this->d_pi_quality_lbl->Location = System::Drawing::Point(114, 46);
		this->d_pi_quality_lbl->Name = L"d_pi_quality_lbl";
		this->d_pi_quality_lbl->Size = System::Drawing::Size(47, 12);
		this->d_pi_quality_lbl->TabIndex = 23;
		this->d_pi_quality_lbl->Text = L"quality";
		this->d_pi_quality_lbl->Visible = false;
		// 
		// d_pi_id_lbl
		// 
		this->d_pi_id_lbl->AutoSize = true;
		this->d_pi_id_lbl->Location = System::Drawing::Point(233, 15);
		this->d_pi_id_lbl->Name = L"d_pi_id_lbl";
		this->d_pi_id_lbl->Size = System::Drawing::Size(17, 12);
		this->d_pi_id_lbl->TabIndex = 22;
		this->d_pi_id_lbl->Text = L"id";
		// 
		// d_pi_money_pag
		// 
		this->d_pi_money_pag->Controls->Add(this->d_pi_money_cbo);
		this->d_pi_money_pag->Controls->Add(this->d_pi_money_lbl);
		this->d_pi_money_pag->Location = System::Drawing::Point(4, 21);
		this->d_pi_money_pag->Name = L"d_pi_money_pag";
		this->d_pi_money_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_pi_money_pag->Size = System::Drawing::Size(343, 74);
		this->d_pi_money_pag->TabIndex = 1;
		this->d_pi_money_pag->Text = L"money";
		this->d_pi_money_pag->UseVisualStyleBackColor = true;
		// 
		// d_pi_money_cbo
		// 
		this->d_pi_money_cbo->FormattingEnabled = true;
		this->d_pi_money_cbo->Location = System::Drawing::Point(146, 27);
		this->d_pi_money_cbo->Name = L"d_pi_money_cbo";
		this->d_pi_money_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pi_money_cbo->TabIndex = 32;
		// 
		// d_pi_money_lbl
		// 
		this->d_pi_money_lbl->AutoSize = true;
		this->d_pi_money_lbl->Location = System::Drawing::Point(90, 30);
		this->d_pi_money_lbl->Name = L"d_pi_money_lbl";
		this->d_pi_money_lbl->Size = System::Drawing::Size(35, 12);
		this->d_pi_money_lbl->TabIndex = 31;
		this->d_pi_money_lbl->Text = L"money";
		// 
		// c_player_npc_pag
		// 
		this->c_player_npc_pag->Controls->Add(this->c_player_npc_pal);
		this->c_player_npc_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_npc_pag->Name = L"c_player_npc_pag";
		this->c_player_npc_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_npc_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_npc_pag->TabIndex = 4;
		this->c_player_npc_pag->Text = L"npc";
		this->c_player_npc_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_npc_pal
		// 
		this->c_player_npc_pal->Controls->Add(this->d_pn_pal);
		this->c_player_npc_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_npc_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_npc_pal->Name = L"c_player_npc_pal";
		this->c_player_npc_pal->Size = System::Drawing::Size(447, 438);
		this->c_player_npc_pal->TabIndex = 1;
		// 
		// d_pn_pal
		// 
		this->d_pn_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_pn_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_pn_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_pn_pal->Controls->Add(this->d_pn_npc_info_gbo);
		this->d_pn_pal->Controls->Add(this->d_pn_record_gbo);
		this->d_pn_pal->Controls->Add(this->d_pn_commit_gbo);
		this->d_pn_pal->Controls->Add(this->d_pn_npc_setting_gbo);
		this->d_pn_pal->Location = System::Drawing::Point(32, 18);
		this->d_pn_pal->Name = L"d_pn_pal";
		this->d_pn_pal->Size = System::Drawing::Size(392, 394);
		this->d_pn_pal->TabIndex = 3;
		// 
		// d_pn_npc_info_gbo
		// 
		this->d_pn_npc_info_gbo->Controls->Add(this->d_pn_server_cbo);
		this->d_pn_npc_info_gbo->Controls->Add(this->d_pn_server_lbl);
		this->d_pn_npc_info_gbo->Controls->Add(this->d_pn_npcid_cbo);
		this->d_pn_npc_info_gbo->Controls->Add(this->d_pn_npcname_cbo);
		this->d_pn_npc_info_gbo->Controls->Add(this->d_pn_npcid_lbl);
		this->d_pn_npc_info_gbo->Controls->Add(this->d_pn_npcname_lbl);
		this->d_pn_npc_info_gbo->Location = System::Drawing::Point(175, 44);
		this->d_pn_npc_info_gbo->Name = L"d_pn_npc_info_gbo";
		this->d_pn_npc_info_gbo->Size = System::Drawing::Size(203, 146);
		this->d_pn_npc_info_gbo->TabIndex = 10;
		this->d_pn_npc_info_gbo->TabStop = false;
		this->d_pn_npc_info_gbo->Text = L"npc info";
		// 
		// d_pn_server_cbo
		// 
		this->d_pn_server_cbo->FormattingEnabled = true;
		this->d_pn_server_cbo->Location = System::Drawing::Point(86, 26);
		this->d_pn_server_cbo->Name = L"d_pn_server_cbo";
		this->d_pn_server_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pn_server_cbo->TabIndex = 28;
		// 
		// d_pn_server_lbl
		// 
		this->d_pn_server_lbl->AutoSize = true;
		this->d_pn_server_lbl->Location = System::Drawing::Point(14, 29);
		this->d_pn_server_lbl->Name = L"d_pn_server_lbl";
		this->d_pn_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pn_server_lbl->TabIndex = 27;
		this->d_pn_server_lbl->Text = L"server";
		// 
		// d_pn_npcid_cbo
		// 
		this->d_pn_npcid_cbo->FormattingEnabled = true;
		this->d_pn_npcid_cbo->Location = System::Drawing::Point(86, 110);
		this->d_pn_npcid_cbo->Name = L"d_pn_npcid_cbo";
		this->d_pn_npcid_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pn_npcid_cbo->TabIndex = 26;
		// 
		// d_pn_npcname_cbo
		// 
		this->d_pn_npcname_cbo->FormattingEnabled = true;
		this->d_pn_npcname_cbo->Location = System::Drawing::Point(86, 68);
		this->d_pn_npcname_cbo->Name = L"d_pn_npcname_cbo";
		this->d_pn_npcname_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pn_npcname_cbo->TabIndex = 25;
		// 
		// d_pn_npcid_lbl
		// 
		this->d_pn_npcid_lbl->AutoSize = true;
		this->d_pn_npcid_lbl->Location = System::Drawing::Point(14, 111);
		this->d_pn_npcid_lbl->Name = L"d_pn_npcid_lbl";
		this->d_pn_npcid_lbl->Size = System::Drawing::Size(35, 12);
		this->d_pn_npcid_lbl->TabIndex = 24;
		this->d_pn_npcid_lbl->Text = L"npcid";
		// 
		// d_pn_npcname_lbl
		// 
		this->d_pn_npcname_lbl->AutoSize = true;
		this->d_pn_npcname_lbl->Location = System::Drawing::Point(14, 69);
		this->d_pn_npcname_lbl->Name = L"d_pn_npcname_lbl";
		this->d_pn_npcname_lbl->Size = System::Drawing::Size(47, 12);
		this->d_pn_npcname_lbl->TabIndex = 22;
		this->d_pn_npcname_lbl->Text = L"npcname";
		// 
		// d_pn_record_gbo
		// 
		this->d_pn_record_gbo->Controls->Add(this->d_pn_record_list);
		this->d_pn_record_gbo->Controls->Add(this->d_pn_filter_server_pnl);
		this->d_pn_record_gbo->Location = System::Drawing::Point(12, 11);
		this->d_pn_record_gbo->Name = L"d_pn_record_gbo";
		this->d_pn_record_gbo->Size = System::Drawing::Size(154, 369);
		this->d_pn_record_gbo->TabIndex = 9;
		this->d_pn_record_gbo->TabStop = false;
		this->d_pn_record_gbo->Text = L"record";
		// 
		// d_pn_record_list
		// 
		this->d_pn_record_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dpn_column_id, 
			this->dpn_column_name});
		this->d_pn_record_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_pn_record_list->FullRowSelect = true;
		this->d_pn_record_list->GridLines = true;
		this->d_pn_record_list->HideSelection = false;
		this->d_pn_record_list->Location = System::Drawing::Point(3, 74);
		this->d_pn_record_list->Name = L"d_pn_record_list";
		this->d_pn_record_list->Size = System::Drawing::Size(148, 292);
		this->d_pn_record_list->TabIndex = 4;
		this->d_pn_record_list->UseCompatibleStateImageBehavior = false;
		this->d_pn_record_list->View = System::Windows::Forms::View::Details;
		this->d_pn_record_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_pn_record_list_MouseDoubleClick);
		// 
		// dpn_column_id
		// 
		this->dpn_column_id->Text = L"id";
		// 
		// dpn_column_name
		// 
		this->dpn_column_name->Text = L"name";
		this->dpn_column_name->Width = 100;
		// 
		// d_pn_filter_server_pnl
		// 
		this->d_pn_filter_server_pnl->Controls->Add(this->d_pn_filter_server_lbl);
		this->d_pn_filter_server_pnl->Controls->Add(this->d_pn_filter_server_cbo);
		this->d_pn_filter_server_pnl->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_pn_filter_server_pnl->Location = System::Drawing::Point(3, 17);
		this->d_pn_filter_server_pnl->Name = L"d_pn_filter_server_pnl";
		this->d_pn_filter_server_pnl->Size = System::Drawing::Size(148, 57);
		this->d_pn_filter_server_pnl->TabIndex = 3;
		// 
		// d_pn_filter_server_lbl
		// 
		this->d_pn_filter_server_lbl->AutoSize = true;
		this->d_pn_filter_server_lbl->Location = System::Drawing::Point(5, 7);
		this->d_pn_filter_server_lbl->Name = L"d_pn_filter_server_lbl";
		this->d_pn_filter_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pn_filter_server_lbl->TabIndex = 25;
		this->d_pn_filter_server_lbl->Text = L"server";
		// 
		// d_pn_filter_server_cbo
		// 
		this->d_pn_filter_server_cbo->FormattingEnabled = true;
		this->d_pn_filter_server_cbo->Location = System::Drawing::Point(7, 25);
		this->d_pn_filter_server_cbo->Name = L"d_pn_filter_server_cbo";
		this->d_pn_filter_server_cbo->Size = System::Drawing::Size(134, 20);
		this->d_pn_filter_server_cbo->TabIndex = 21;
		this->d_pn_filter_server_cbo->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pn_filter_server_cbo_SelectedIndexChanged);
		// 
		// d_pn_commit_gbo
		// 
		this->d_pn_commit_gbo->Controls->Add(this->d_pn_commit_reason_btn);
		this->d_pn_commit_gbo->Location = System::Drawing::Point(175, 288);
		this->d_pn_commit_gbo->Name = L"d_pn_commit_gbo";
		this->d_pn_commit_gbo->Size = System::Drawing::Size(201, 45);
		this->d_pn_commit_gbo->TabIndex = 7;
		this->d_pn_commit_gbo->TabStop = false;
		this->d_pn_commit_gbo->Text = L"commit";
		// 
		// d_pn_commit_reason_btn
		// 
		this->d_pn_commit_reason_btn->Location = System::Drawing::Point(114, 15);
		this->d_pn_commit_reason_btn->Name = L"d_pn_commit_reason_btn";
		this->d_pn_commit_reason_btn->Size = System::Drawing::Size(75, 23);
		this->d_pn_commit_reason_btn->TabIndex = 0;
		this->d_pn_commit_reason_btn->Text = L"commint";
		this->d_pn_commit_reason_btn->UseVisualStyleBackColor = true;
		this->d_pn_commit_reason_btn->Click += gcnew System::EventHandler(this, &MainForm::d_pn_commit_reason_btn_Click);
		// 
		// d_pn_npc_setting_gbo
		// 
		this->d_pn_npc_setting_gbo->Controls->Add(this->d_pn_closed_rdo);
		this->d_pn_npc_setting_gbo->Controls->Add(this->d_pn_unclosed_gbo);
		this->d_pn_npc_setting_gbo->Location = System::Drawing::Point(175, 211);
		this->d_pn_npc_setting_gbo->Name = L"d_pn_npc_setting_gbo";
		this->d_pn_npc_setting_gbo->Size = System::Drawing::Size(201, 49);
		this->d_pn_npc_setting_gbo->TabIndex = 6;
		this->d_pn_npc_setting_gbo->TabStop = false;
		this->d_pn_npc_setting_gbo->Text = L"setting";
		// 
		// d_pn_closed_rdo
		// 
		this->d_pn_closed_rdo->AutoSize = true;
		this->d_pn_closed_rdo->Location = System::Drawing::Point(16, 21);
		this->d_pn_closed_rdo->Name = L"d_pn_closed_rdo";
		this->d_pn_closed_rdo->Size = System::Drawing::Size(59, 16);
		this->d_pn_closed_rdo->TabIndex = 12;
		this->d_pn_closed_rdo->TabStop = true;
		this->d_pn_closed_rdo->Text = L"closed";
		this->d_pn_closed_rdo->UseVisualStyleBackColor = true;
		// 
		// d_pn_unclosed_gbo
		// 
		this->d_pn_unclosed_gbo->AutoSize = true;
		this->d_pn_unclosed_gbo->Location = System::Drawing::Point(118, 21);
		this->d_pn_unclosed_gbo->Name = L"d_pn_unclosed_gbo";
		this->d_pn_unclosed_gbo->Size = System::Drawing::Size(71, 16);
		this->d_pn_unclosed_gbo->TabIndex = 11;
		this->d_pn_unclosed_gbo->TabStop = true;
		this->d_pn_unclosed_gbo->Text = L"unClosed";
		this->d_pn_unclosed_gbo->UseVisualStyleBackColor = true;
		// 
		// c_player_hidden_pag
		// 
		this->c_player_hidden_pag->Controls->Add(this->c_player_hidden_pal);
		this->c_player_hidden_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_hidden_pag->Name = L"c_player_hidden_pag";
		this->c_player_hidden_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_hidden_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_hidden_pag->TabIndex = 5;
		this->c_player_hidden_pag->Text = L"hidden";
		this->c_player_hidden_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_hidden_pal
		// 
		this->c_player_hidden_pal->Controls->Add(this->d_ph_pal);
		this->c_player_hidden_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_hidden_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_hidden_pal->Name = L"c_player_hidden_pal";
		this->c_player_hidden_pal->Size = System::Drawing::Size(447, 438);
		this->c_player_hidden_pal->TabIndex = 1;
		// 
		// d_ph_pal
		// 
		this->d_ph_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_ph_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_ph_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_ph_pal->Controls->Add(this->d_ph_record_gbo);
		this->d_ph_pal->Controls->Add(this->d_ph_config_gbo);
		this->d_ph_pal->Controls->Add(this->d_ph_commit_gbo);
		this->d_ph_pal->Controls->Add(this->d_ph_hidden_gbo);
		this->d_ph_pal->Location = System::Drawing::Point(29, 18);
		this->d_ph_pal->Name = L"d_ph_pal";
		this->d_ph_pal->Size = System::Drawing::Size(392, 394);
		this->d_ph_pal->TabIndex = 2;
		// 
		// d_ph_record_gbo
		// 
		this->d_ph_record_gbo->Controls->Add(this->d_ph_record_list);
		this->d_ph_record_gbo->Controls->Add(this->d_ph_record_pnl);
		this->d_ph_record_gbo->Location = System::Drawing::Point(13, 20);
		this->d_ph_record_gbo->Name = L"d_ph_record_gbo";
		this->d_ph_record_gbo->Size = System::Drawing::Size(154, 369);
		this->d_ph_record_gbo->TabIndex = 10;
		this->d_ph_record_gbo->TabStop = false;
		this->d_ph_record_gbo->Text = L"record";
		// 
		// d_ph_record_list
		// 
		this->d_ph_record_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dph_column_player_name, 
			this->dph_column_end_time});
		this->d_ph_record_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ph_record_list->FullRowSelect = true;
		this->d_ph_record_list->GridLines = true;
		this->d_ph_record_list->HideSelection = false;
		this->d_ph_record_list->Location = System::Drawing::Point(3, 78);
		this->d_ph_record_list->Name = L"d_ph_record_list";
		this->d_ph_record_list->Size = System::Drawing::Size(148, 288);
		this->d_ph_record_list->TabIndex = 3;
		this->d_ph_record_list->UseCompatibleStateImageBehavior = false;
		this->d_ph_record_list->View = System::Windows::Forms::View::Details;
		// 
		// dph_column_player_name
		// 
		this->dph_column_player_name->Text = L"player name";
		this->dph_column_player_name->Width = 78;
		// 
		// dph_column_end_time
		// 
		this->dph_column_end_time->Text = L"end tiem";
		this->dph_column_end_time->Width = 200;
		// 
		// d_ph_record_pnl
		// 
		this->d_ph_record_pnl->Controls->Add(this->label1);
		this->d_ph_record_pnl->Controls->Add(this->d_ph_filter_server_cbo);
		this->d_ph_record_pnl->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_ph_record_pnl->Location = System::Drawing::Point(3, 17);
		this->d_ph_record_pnl->Name = L"d_ph_record_pnl";
		this->d_ph_record_pnl->Size = System::Drawing::Size(148, 61);
		this->d_ph_record_pnl->TabIndex = 2;
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(5, 7);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(41, 12);
		this->label1->TabIndex = 25;
		this->label1->Text = L"server";
		// 
		// d_ph_filter_server_cbo
		// 
		this->d_ph_filter_server_cbo->FormattingEnabled = true;
		this->d_ph_filter_server_cbo->Location = System::Drawing::Point(7, 25);
		this->d_ph_filter_server_cbo->Name = L"d_ph_filter_server_cbo";
		this->d_ph_filter_server_cbo->Size = System::Drawing::Size(134, 20);
		this->d_ph_filter_server_cbo->TabIndex = 21;
		this->d_ph_filter_server_cbo->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_ph_server_cmb_SelectedIndexChanged);
		// 
		// d_ph_config_gbo
		// 
		this->d_ph_config_gbo->Controls->Add(this->d_ph_username_edt);
		this->d_ph_config_gbo->Controls->Add(this->d_ph_server_cbo);
		this->d_ph_config_gbo->Controls->Add(this->d_ph_username_lbl);
		this->d_ph_config_gbo->Controls->Add(this->d_ph_server_lbl);
		this->d_ph_config_gbo->Location = System::Drawing::Point(173, 64);
		this->d_ph_config_gbo->Name = L"d_ph_config_gbo";
		this->d_ph_config_gbo->Size = System::Drawing::Size(192, 93);
		this->d_ph_config_gbo->TabIndex = 9;
		this->d_ph_config_gbo->TabStop = false;
		this->d_ph_config_gbo->Text = L"config";
		// 
		// d_ph_username_edt
		// 
		this->d_ph_username_edt->Location = System::Drawing::Point(81, 51);
		this->d_ph_username_edt->Name = L"d_ph_username_edt";
		this->d_ph_username_edt->Size = System::Drawing::Size(103, 21);
		this->d_ph_username_edt->TabIndex = 13;
		// 
		// d_ph_server_cbo
		// 
		this->d_ph_server_cbo->FormattingEnabled = true;
		this->d_ph_server_cbo->Location = System::Drawing::Point(81, 20);
		this->d_ph_server_cbo->Name = L"d_ph_server_cbo";
		this->d_ph_server_cbo->Size = System::Drawing::Size(103, 20);
		this->d_ph_server_cbo->TabIndex = 12;
		// 
		// d_ph_username_lbl
		// 
		this->d_ph_username_lbl->AutoSize = true;
		this->d_ph_username_lbl->Location = System::Drawing::Point(22, 54);
		this->d_ph_username_lbl->Name = L"d_ph_username_lbl";
		this->d_ph_username_lbl->Size = System::Drawing::Size(53, 12);
		this->d_ph_username_lbl->TabIndex = 10;
		this->d_ph_username_lbl->Text = L"username";
		// 
		// d_ph_server_lbl
		// 
		this->d_ph_server_lbl->AutoSize = true;
		this->d_ph_server_lbl->Location = System::Drawing::Point(22, 23);
		this->d_ph_server_lbl->Name = L"d_ph_server_lbl";
		this->d_ph_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_ph_server_lbl->TabIndex = 9;
		this->d_ph_server_lbl->Text = L"server";
		// 
		// d_ph_commit_gbo
		// 
		this->d_ph_commit_gbo->Controls->Add(this->d_ph_commit_btn);
		this->d_ph_commit_gbo->Location = System::Drawing::Point(173, 280);
		this->d_ph_commit_gbo->Name = L"d_ph_commit_gbo";
		this->d_ph_commit_gbo->Size = System::Drawing::Size(192, 44);
		this->d_ph_commit_gbo->TabIndex = 7;
		this->d_ph_commit_gbo->TabStop = false;
		this->d_ph_commit_gbo->Text = L"commit";
		// 
		// d_ph_commit_btn
		// 
		this->d_ph_commit_btn->Location = System::Drawing::Point(109, 15);
		this->d_ph_commit_btn->Name = L"d_ph_commit_btn";
		this->d_ph_commit_btn->Size = System::Drawing::Size(75, 23);
		this->d_ph_commit_btn->TabIndex = 0;
		this->d_ph_commit_btn->Text = L"commint";
		this->d_ph_commit_btn->UseVisualStyleBackColor = true;
		this->d_ph_commit_btn->Click += gcnew System::EventHandler(this, &MainForm::d_ph_commit_btn_Click);
		// 
		// d_ph_hidden_gbo
		// 
		this->d_ph_hidden_gbo->Controls->Add(this->d_ph_hour_lbl);
		this->d_ph_hidden_gbo->Controls->Add(this->d_ph_hidden_rdo);
		this->d_ph_hidden_gbo->Controls->Add(this->d_ph_time_cbo);
		this->d_ph_hidden_gbo->Controls->Add(this->d_ph_show_rdo);
		this->d_ph_hidden_gbo->Controls->Add(this->d_ph_time_lbl);
		this->d_ph_hidden_gbo->Location = System::Drawing::Point(173, 163);
		this->d_ph_hidden_gbo->Name = L"d_ph_hidden_gbo";
		this->d_ph_hidden_gbo->Size = System::Drawing::Size(192, 111);
		this->d_ph_hidden_gbo->TabIndex = 6;
		this->d_ph_hidden_gbo->TabStop = false;
		this->d_ph_hidden_gbo->Text = L"hidden";
		// 
		// d_ph_hour_lbl
		// 
		this->d_ph_hour_lbl->AutoSize = true;
		this->d_ph_hour_lbl->Enabled = false;
		this->d_ph_hour_lbl->Location = System::Drawing::Point(144, 88);
		this->d_ph_hour_lbl->Name = L"d_ph_hour_lbl";
		this->d_ph_hour_lbl->Size = System::Drawing::Size(41, 12);
		this->d_ph_hour_lbl->TabIndex = 15;
		this->d_ph_hour_lbl->Text = L"minute";
		// 
		// d_ph_hidden_rdo
		// 
		this->d_ph_hidden_rdo->AutoSize = true;
		this->d_ph_hidden_rdo->Location = System::Drawing::Point(20, 20);
		this->d_ph_hidden_rdo->Name = L"d_ph_hidden_rdo";
		this->d_ph_hidden_rdo->Size = System::Drawing::Size(59, 16);
		this->d_ph_hidden_rdo->TabIndex = 14;
		this->d_ph_hidden_rdo->TabStop = true;
		this->d_ph_hidden_rdo->Text = L"hidden";
		this->d_ph_hidden_rdo->UseVisualStyleBackColor = true;
		this->d_ph_hidden_rdo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_ph_hidden_rdo_CheckedChanged);
		// 
		// d_ph_time_cbo
		// 
		this->d_ph_time_cbo->Enabled = false;
		this->d_ph_time_cbo->FormattingEnabled = true;
		this->d_ph_time_cbo->Location = System::Drawing::Point(52, 85);
		this->d_ph_time_cbo->Name = L"d_ph_time_cbo";
		this->d_ph_time_cbo->Size = System::Drawing::Size(86, 20);
		this->d_ph_time_cbo->TabIndex = 12;
		// 
		// d_ph_show_rdo
		// 
		this->d_ph_show_rdo->AutoSize = true;
		this->d_ph_show_rdo->Location = System::Drawing::Point(20, 42);
		this->d_ph_show_rdo->Name = L"d_ph_show_rdo";
		this->d_ph_show_rdo->Size = System::Drawing::Size(47, 16);
		this->d_ph_show_rdo->TabIndex = 13;
		this->d_ph_show_rdo->TabStop = true;
		this->d_ph_show_rdo->Text = L"show";
		this->d_ph_show_rdo->UseVisualStyleBackColor = true;
		// 
		// d_ph_time_lbl
		// 
		this->d_ph_time_lbl->AutoSize = true;
		this->d_ph_time_lbl->Enabled = false;
		this->d_ph_time_lbl->Location = System::Drawing::Point(50, 70);
		this->d_ph_time_lbl->Name = L"d_ph_time_lbl";
		this->d_ph_time_lbl->Size = System::Drawing::Size(29, 12);
		this->d_ph_time_lbl->TabIndex = 9;
		this->d_ph_time_lbl->Text = L"time";
		// 
		// c_player_state_pag
		// 
		this->c_player_state_pag->Controls->Add(this->d_ps_pal);
		this->c_player_state_pag->Controls->Add(this->c_player_state_pal);
		this->c_player_state_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_state_pag->Name = L"c_player_state_pag";
		this->c_player_state_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_state_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_state_pag->TabIndex = 6;
		this->c_player_state_pag->Text = L"state";
		this->c_player_state_pag->UseVisualStyleBackColor = true;
		// 
		// d_ps_pal
		// 
		this->d_ps_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_ps_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_ps_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_ps_pal->Controls->Add(this->d_ps_config_gbo);
		this->d_ps_pal->Controls->Add(this->d_ps_state_gbo);
		this->d_ps_pal->Location = System::Drawing::Point(3, 2);
		this->d_ps_pal->Name = L"d_ps_pal";
		this->d_ps_pal->Size = System::Drawing::Size(454, 436);
		this->d_ps_pal->TabIndex = 2;
		// 
		// d_ps_config_gbo
		// 
		this->d_ps_config_gbo->Controls->Add(this->d_ps_search_btn);
		this->d_ps_config_gbo->Controls->Add(this->d_ps_username_edt);
		this->d_ps_config_gbo->Controls->Add(this->d_ps_server_cbo);
		this->d_ps_config_gbo->Controls->Add(this->d_ps_username_lbl);
		this->d_ps_config_gbo->Controls->Add(this->d_ps_server_lbl);
		this->d_ps_config_gbo->Location = System::Drawing::Point(16, 3);
		this->d_ps_config_gbo->Name = L"d_ps_config_gbo";
		this->d_ps_config_gbo->Size = System::Drawing::Size(420, 41);
		this->d_ps_config_gbo->TabIndex = 9;
		this->d_ps_config_gbo->TabStop = false;
		this->d_ps_config_gbo->Text = L"config";
		// 
		// d_ps_search_btn
		// 
		this->d_ps_search_btn->Location = System::Drawing::Point(340, 9);
		this->d_ps_search_btn->Name = L"d_ps_search_btn";
		this->d_ps_search_btn->Size = System::Drawing::Size(54, 23);
		this->d_ps_search_btn->TabIndex = 14;
		this->d_ps_search_btn->Text = L"search";
		this->d_ps_search_btn->UseVisualStyleBackColor = true;
		// 
		// d_ps_username_edt
		// 
		this->d_ps_username_edt->Location = System::Drawing::Point(221, 10);
		this->d_ps_username_edt->Name = L"d_ps_username_edt";
		this->d_ps_username_edt->Size = System::Drawing::Size(103, 21);
		this->d_ps_username_edt->TabIndex = 13;
		// 
		// d_ps_server_cbo
		// 
		this->d_ps_server_cbo->FormattingEnabled = true;
		this->d_ps_server_cbo->Location = System::Drawing::Point(53, 11);
		this->d_ps_server_cbo->Name = L"d_ps_server_cbo";
		this->d_ps_server_cbo->Size = System::Drawing::Size(103, 20);
		this->d_ps_server_cbo->TabIndex = 12;
		// 
		// d_ps_username_lbl
		// 
		this->d_ps_username_lbl->AutoSize = true;
		this->d_ps_username_lbl->Location = System::Drawing::Point(162, 17);
		this->d_ps_username_lbl->Name = L"d_ps_username_lbl";
		this->d_ps_username_lbl->Size = System::Drawing::Size(53, 12);
		this->d_ps_username_lbl->TabIndex = 10;
		this->d_ps_username_lbl->Text = L"username";
		// 
		// d_ps_server_lbl
		// 
		this->d_ps_server_lbl->AutoSize = true;
		this->d_ps_server_lbl->Location = System::Drawing::Point(6, 17);
		this->d_ps_server_lbl->Name = L"d_ps_server_lbl";
		this->d_ps_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_ps_server_lbl->TabIndex = 9;
		this->d_ps_server_lbl->Text = L"server";
		// 
		// d_ps_state_gbo
		// 
		this->d_ps_state_gbo->Controls->Add(this->d_ps_state_tab);
		this->d_ps_state_gbo->Location = System::Drawing::Point(16, 50);
		this->d_ps_state_gbo->Name = L"d_ps_state_gbo";
		this->d_ps_state_gbo->Size = System::Drawing::Size(423, 381);
		this->d_ps_state_gbo->TabIndex = 6;
		this->d_ps_state_gbo->TabStop = false;
		this->d_ps_state_gbo->Text = L"state";
		// 
		// d_ps_state_tab
		// 
		this->d_ps_state_tab->Controls->Add(this->d_ps_property_pag);
		this->d_ps_state_tab->Controls->Add(this->d_ps_equip_pag);
		this->d_ps_state_tab->Controls->Add(this->d_ps_bag_pag);
		this->d_ps_state_tab->Controls->Add(this->d_ps_skill_pag);
		this->d_ps_state_tab->Controls->Add(this->d_ps_task_pag);
		this->d_ps_state_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ps_state_tab->Location = System::Drawing::Point(3, 17);
		this->d_ps_state_tab->Name = L"d_ps_state_tab";
		this->d_ps_state_tab->SelectedIndex = 0;
		this->d_ps_state_tab->Size = System::Drawing::Size(417, 361);
		this->d_ps_state_tab->TabIndex = 0;
		// 
		// d_ps_property_pag
		// 
		this->d_ps_property_pag->Controls->Add(this->textBox18);
		this->d_ps_property_pag->Controls->Add(this->textBox9);
		this->d_ps_property_pag->Controls->Add(this->textBox17);
		this->d_ps_property_pag->Controls->Add(this->textBox6);
		this->d_ps_property_pag->Controls->Add(this->textBox16);
		this->d_ps_property_pag->Controls->Add(this->textBox3);
		this->d_ps_property_pag->Controls->Add(this->textBox15);
		this->d_ps_property_pag->Controls->Add(this->textBox8);
		this->d_ps_property_pag->Controls->Add(this->textBox14);
		this->d_ps_property_pag->Controls->Add(this->textBox5);
		this->d_ps_property_pag->Controls->Add(this->textBox13);
		this->d_ps_property_pag->Controls->Add(this->textBox2);
		this->d_ps_property_pag->Controls->Add(this->textBox12);
		this->d_ps_property_pag->Controls->Add(this->textBox7);
		this->d_ps_property_pag->Controls->Add(this->textBox11);
		this->d_ps_property_pag->Controls->Add(this->textBox4);
		this->d_ps_property_pag->Controls->Add(this->textBox10);
		this->d_ps_property_pag->Controls->Add(this->textBox1);
		this->d_ps_property_pag->Controls->Add(this->label19);
		this->d_ps_property_pag->Controls->Add(this->label17);
		this->d_ps_property_pag->Controls->Add(this->label18);
		this->d_ps_property_pag->Controls->Add(this->label16);
		this->d_ps_property_pag->Controls->Add(this->label15);
		this->d_ps_property_pag->Controls->Add(this->label9);
		this->d_ps_property_pag->Controls->Add(this->label14);
		this->d_ps_property_pag->Controls->Add(this->label8);
		this->d_ps_property_pag->Controls->Add(this->label13);
		this->d_ps_property_pag->Controls->Add(this->label7);
		this->d_ps_property_pag->Controls->Add(this->label12);
		this->d_ps_property_pag->Controls->Add(this->label6);
		this->d_ps_property_pag->Controls->Add(this->label11);
		this->d_ps_property_pag->Controls->Add(this->label5);
		this->d_ps_property_pag->Controls->Add(this->label10);
		this->d_ps_property_pag->Controls->Add(this->label4);
		this->d_ps_property_pag->Controls->Add(this->label2);
		this->d_ps_property_pag->Controls->Add(this->label3);
		this->d_ps_property_pag->Location = System::Drawing::Point(4, 21);
		this->d_ps_property_pag->Name = L"d_ps_property_pag";
		this->d_ps_property_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_ps_property_pag->Size = System::Drawing::Size(409, 336);
		this->d_ps_property_pag->TabIndex = 0;
		this->d_ps_property_pag->Text = L"property";
		this->d_ps_property_pag->UseVisualStyleBackColor = true;
		// 
		// textBox18
		// 
		this->textBox18->Location = System::Drawing::Point(186, 287);
		this->textBox18->Name = L"textBox18";
		this->textBox18->Size = System::Drawing::Size(69, 21);
		this->textBox18->TabIndex = 1;
		// 
		// textBox9
		// 
		this->textBox9->Location = System::Drawing::Point(66, 287);
		this->textBox9->Name = L"textBox9";
		this->textBox9->Size = System::Drawing::Size(69, 21);
		this->textBox9->TabIndex = 1;
		// 
		// textBox17
		// 
		this->textBox17->Location = System::Drawing::Point(186, 188);
		this->textBox17->Name = L"textBox17";
		this->textBox17->Size = System::Drawing::Size(69, 21);
		this->textBox17->TabIndex = 1;
		// 
		// textBox6
		// 
		this->textBox6->Location = System::Drawing::Point(66, 188);
		this->textBox6->Name = L"textBox6";
		this->textBox6->Size = System::Drawing::Size(69, 21);
		this->textBox6->TabIndex = 1;
		// 
		// textBox16
		// 
		this->textBox16->Location = System::Drawing::Point(186, 89);
		this->textBox16->Name = L"textBox16";
		this->textBox16->Size = System::Drawing::Size(69, 21);
		this->textBox16->TabIndex = 1;
		// 
		// textBox3
		// 
		this->textBox3->Location = System::Drawing::Point(66, 89);
		this->textBox3->Name = L"textBox3";
		this->textBox3->Size = System::Drawing::Size(69, 21);
		this->textBox3->TabIndex = 1;
		// 
		// textBox15
		// 
		this->textBox15->Location = System::Drawing::Point(186, 254);
		this->textBox15->Name = L"textBox15";
		this->textBox15->Size = System::Drawing::Size(69, 21);
		this->textBox15->TabIndex = 1;
		// 
		// textBox8
		// 
		this->textBox8->Location = System::Drawing::Point(66, 254);
		this->textBox8->Name = L"textBox8";
		this->textBox8->Size = System::Drawing::Size(69, 21);
		this->textBox8->TabIndex = 1;
		// 
		// textBox14
		// 
		this->textBox14->Location = System::Drawing::Point(186, 155);
		this->textBox14->Name = L"textBox14";
		this->textBox14->Size = System::Drawing::Size(69, 21);
		this->textBox14->TabIndex = 1;
		// 
		// textBox5
		// 
		this->textBox5->Location = System::Drawing::Point(66, 155);
		this->textBox5->Name = L"textBox5";
		this->textBox5->Size = System::Drawing::Size(69, 21);
		this->textBox5->TabIndex = 1;
		// 
		// textBox13
		// 
		this->textBox13->Location = System::Drawing::Point(186, 56);
		this->textBox13->Name = L"textBox13";
		this->textBox13->Size = System::Drawing::Size(69, 21);
		this->textBox13->TabIndex = 1;
		// 
		// textBox2
		// 
		this->textBox2->Location = System::Drawing::Point(66, 56);
		this->textBox2->Name = L"textBox2";
		this->textBox2->Size = System::Drawing::Size(69, 21);
		this->textBox2->TabIndex = 1;
		// 
		// textBox12
		// 
		this->textBox12->Location = System::Drawing::Point(186, 221);
		this->textBox12->Name = L"textBox12";
		this->textBox12->Size = System::Drawing::Size(69, 21);
		this->textBox12->TabIndex = 1;
		// 
		// textBox7
		// 
		this->textBox7->Location = System::Drawing::Point(66, 221);
		this->textBox7->Name = L"textBox7";
		this->textBox7->Size = System::Drawing::Size(69, 21);
		this->textBox7->TabIndex = 1;
		// 
		// textBox11
		// 
		this->textBox11->Location = System::Drawing::Point(186, 122);
		this->textBox11->Name = L"textBox11";
		this->textBox11->Size = System::Drawing::Size(69, 21);
		this->textBox11->TabIndex = 1;
		// 
		// textBox4
		// 
		this->textBox4->Location = System::Drawing::Point(66, 122);
		this->textBox4->Name = L"textBox4";
		this->textBox4->Size = System::Drawing::Size(69, 21);
		this->textBox4->TabIndex = 1;
		// 
		// textBox10
		// 
		this->textBox10->Location = System::Drawing::Point(186, 23);
		this->textBox10->Name = L"textBox10";
		this->textBox10->Size = System::Drawing::Size(69, 21);
		this->textBox10->TabIndex = 1;
		// 
		// textBox1
		// 
		this->textBox1->Location = System::Drawing::Point(66, 23);
		this->textBox1->Name = L"textBox1";
		this->textBox1->Size = System::Drawing::Size(69, 21);
		this->textBox1->TabIndex = 1;
		// 
		// label19
		// 
		this->label19->AutoSize = true;
		this->label19->Location = System::Drawing::Point(141, 263);
		this->label19->Name = L"label19";
		this->label19->Size = System::Drawing::Size(41, 12);
		this->label19->TabIndex = 0;
		this->label19->Text = L"label2";
		// 
		// label17
		// 
		this->label17->AutoSize = true;
		this->label17->Location = System::Drawing::Point(21, 263);
		this->label17->Name = L"label17";
		this->label17->Size = System::Drawing::Size(23, 12);
		this->label17->TabIndex = 0;
		this->label17->Text = L"exp";
		// 
		// label18
		// 
		this->label18->AutoSize = true;
		this->label18->Location = System::Drawing::Point(141, 296);
		this->label18->Name = L"label18";
		this->label18->Size = System::Drawing::Size(41, 12);
		this->label18->TabIndex = 0;
		this->label18->Text = L"label2";
		// 
		// label16
		// 
		this->label16->AutoSize = true;
		this->label16->Location = System::Drawing::Point(21, 296);
		this->label16->Name = L"label16";
		this->label16->Size = System::Drawing::Size(17, 12);
		this->label16->TabIndex = 0;
		this->label16->Text = L"hp";
		// 
		// label15
		// 
		this->label15->AutoSize = true;
		this->label15->Location = System::Drawing::Point(141, 230);
		this->label15->Name = L"label15";
		this->label15->Size = System::Drawing::Size(41, 12);
		this->label15->TabIndex = 0;
		this->label15->Text = L"talent";
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Location = System::Drawing::Point(21, 230);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(35, 12);
		this->label9->TabIndex = 0;
		this->label9->Text = L"level";
		// 
		// label14
		// 
		this->label14->AutoSize = true;
		this->label14->Location = System::Drawing::Point(141, 197);
		this->label14->Name = L"label14";
		this->label14->Size = System::Drawing::Size(35, 12);
		this->label14->TabIndex = 0;
		this->label14->Text = L"pkwin";
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Location = System::Drawing::Point(21, 197);
		this->label8->Name = L"label8";
		this->label8->Size = System::Drawing::Size(35, 12);
		this->label8->TabIndex = 0;
		this->label8->Text = L"title";
		// 
		// label13
		// 
		this->label13->AutoSize = true;
		this->label13->Location = System::Drawing::Point(141, 164);
		this->label13->Name = L"label13";
		this->label13->Size = System::Drawing::Size(41, 12);
		this->label13->TabIndex = 0;
		this->label13->Text = L"pklost";
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = System::Drawing::Point(21, 164);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(23, 12);
		this->label7->TabIndex = 0;
		this->label7->Text = L"sex";
		// 
		// label12
		// 
		this->label12->AutoSize = true;
		this->label12->Location = System::Drawing::Point(141, 131);
		this->label12->Name = L"label12";
		this->label12->Size = System::Drawing::Size(53, 12);
		this->label12->TabIndex = 0;
		this->label12->Text = L"guildexp";
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = System::Drawing::Point(21, 131);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(23, 12);
		this->label6->TabIndex = 0;
		this->label6->Text = L"job";
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Location = System::Drawing::Point(141, 98);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(35, 12);
		this->label11->TabIndex = 0;
		this->label11->Text = L"guild";
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(21, 98);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(29, 12);
		this->label5->TabIndex = 0;
		this->label5->Text = L"name";
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Location = System::Drawing::Point(141, 65);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(29, 12);
		this->label10->TabIndex = 0;
		this->label10->Text = L"home";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(21, 65);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(23, 12);
		this->label4->TabIndex = 0;
		this->label4->Text = L"uin";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(141, 32);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(17, 12);
		this->label2->TabIndex = 0;
		this->label2->Text = L"mp";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(21, 32);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(23, 12);
		this->label3->TabIndex = 0;
		this->label3->Text = L"uid";
		// 
		// d_ps_equip_pag
		// 
		this->d_ps_equip_pag->Controls->Add(this->d_ps_state_equip_tab);
		this->d_ps_equip_pag->Location = System::Drawing::Point(4, 21);
		this->d_ps_equip_pag->Name = L"d_ps_equip_pag";
		this->d_ps_equip_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_ps_equip_pag->Size = System::Drawing::Size(409, 336);
		this->d_ps_equip_pag->TabIndex = 1;
		this->d_ps_equip_pag->Text = L"equip";
		this->d_ps_equip_pag->UseVisualStyleBackColor = true;
		// 
		// d_ps_state_equip_tab
		// 
		this->d_ps_state_equip_tab->Controls->Add(this->d_ps_se_cha_tab);
		this->d_ps_state_equip_tab->Controls->Add(this->d_ps_se_fashion_tab);
		this->d_ps_state_equip_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ps_state_equip_tab->Location = System::Drawing::Point(3, 3);
		this->d_ps_state_equip_tab->Name = L"d_ps_state_equip_tab";
		this->d_ps_state_equip_tab->SelectedIndex = 0;
		this->d_ps_state_equip_tab->Size = System::Drawing::Size(403, 330);
		this->d_ps_state_equip_tab->TabIndex = 0;
		// 
		// d_ps_se_cha_tab
		// 
		this->d_ps_se_cha_tab->Location = System::Drawing::Point(4, 21);
		this->d_ps_se_cha_tab->Name = L"d_ps_se_cha_tab";
		this->d_ps_se_cha_tab->Padding = System::Windows::Forms::Padding(3);
		this->d_ps_se_cha_tab->Size = System::Drawing::Size(395, 305);
		this->d_ps_se_cha_tab->TabIndex = 0;
		this->d_ps_se_cha_tab->Text = L"character";
		this->d_ps_se_cha_tab->UseVisualStyleBackColor = true;
		// 
		// d_ps_se_fashion_tab
		// 
		this->d_ps_se_fashion_tab->Location = System::Drawing::Point(4, 21);
		this->d_ps_se_fashion_tab->Name = L"d_ps_se_fashion_tab";
		this->d_ps_se_fashion_tab->Padding = System::Windows::Forms::Padding(3);
		this->d_ps_se_fashion_tab->Size = System::Drawing::Size(395, 305);
		this->d_ps_se_fashion_tab->TabIndex = 1;
		this->d_ps_se_fashion_tab->Text = L"fashion";
		this->d_ps_se_fashion_tab->UseVisualStyleBackColor = true;
		// 
		// d_ps_bag_pag
		// 
		this->d_ps_bag_pag->Controls->Add(this->listView1);
		this->d_ps_bag_pag->Location = System::Drawing::Point(4, 21);
		this->d_ps_bag_pag->Name = L"d_ps_bag_pag";
		this->d_ps_bag_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_ps_bag_pag->Size = System::Drawing::Size(409, 336);
		this->d_ps_bag_pag->TabIndex = 2;
		this->d_ps_bag_pag->Text = L"bag";
		this->d_ps_bag_pag->UseVisualStyleBackColor = true;
		// 
		// listView1
		// 
		this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(16) {this->columnHeader1, this->columnHeader2, 
			this->columnHeader5, this->columnHeader6, this->columnHeader7, this->columnHeader8, this->columnHeader9, this->columnHeader10, 
			this->columnHeader11, this->columnHeader12, this->columnHeader13, this->columnHeader14, this->columnHeader15, this->columnHeader16, 
			this->columnHeader17, this->columnHeader18});
		this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->listView1->FullRowSelect = true;
		this->listView1->GridLines = true;
		this->listView1->HideSelection = false;
		this->listView1->Location = System::Drawing::Point(3, 3);
		this->listView1->Name = L"listView1";
		this->listView1->Size = System::Drawing::Size(403, 330);
		this->listView1->TabIndex = 0;
		this->listView1->UseCompatibleStateImageBehavior = false;
		this->listView1->View = System::Windows::Forms::View::Details;
		// 
		// columnHeader1
		// 
		this->columnHeader1->Text = L"key";
		// 
		// columnHeader2
		// 
		this->columnHeader2->Text = L"bid";
		// 
		// columnHeader5
		// 
		this->columnHeader5->Text = L"dura";
		// 
		// columnHeader6
		// 
		this->columnHeader6->Text = L"solt";
		// 
		// columnHeader7
		// 
		this->columnHeader7->Text = L"geminfoid";
		// 
		// columnHeader8
		// 
		this->columnHeader8->Text = L"gemid1";
		// 
		// columnHeader9
		// 
		this->columnHeader9->Text = L"gemid2";
		// 
		// columnHeader10
		// 
		this->columnHeader10->Text = L"gemid3";
		// 
		// columnHeader11
		// 
		this->columnHeader11->Text = L"strengthen";
		// 
		// columnHeader12
		// 
		this->columnHeader12->Text = L"maker";
		// 
		// columnHeader13
		// 
		this->columnHeader13->Text = L"deadline";
		// 
		// columnHeader14
		// 
		this->columnHeader14->Text = L"del";
		// 
		// columnHeader15
		// 
		this->columnHeader15->Text = L"bind";
		// 
		// columnHeader16
		// 
		this->columnHeader16->Text = L"attrexid";
		// 
		// columnHeader17
		// 
		this->columnHeader17->Text = L"stradd";
		// 
		// columnHeader18
		// 
		this->columnHeader18->Text = L"strid";
		// 
		// d_ps_skill_pag
		// 
		this->d_ps_skill_pag->Controls->Add(this->listView4);
		this->d_ps_skill_pag->Location = System::Drawing::Point(4, 21);
		this->d_ps_skill_pag->Name = L"d_ps_skill_pag";
		this->d_ps_skill_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_ps_skill_pag->Size = System::Drawing::Size(409, 336);
		this->d_ps_skill_pag->TabIndex = 3;
		this->d_ps_skill_pag->Text = L"skill";
		this->d_ps_skill_pag->UseVisualStyleBackColor = true;
		// 
		// listView4
		// 
		this->listView4->Dock = System::Windows::Forms::DockStyle::Fill;
		this->listView4->GridLines = true;
		this->listView4->Location = System::Drawing::Point(3, 3);
		this->listView4->Name = L"listView4";
		this->listView4->Size = System::Drawing::Size(403, 330);
		this->listView4->TabIndex = 1;
		this->listView4->UseCompatibleStateImageBehavior = false;
		this->listView4->View = System::Windows::Forms::View::Details;
		// 
		// d_ps_task_pag
		// 
		this->d_ps_task_pag->Controls->Add(this->listView3);
		this->d_ps_task_pag->Location = System::Drawing::Point(4, 21);
		this->d_ps_task_pag->Name = L"d_ps_task_pag";
		this->d_ps_task_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_ps_task_pag->Size = System::Drawing::Size(409, 336);
		this->d_ps_task_pag->TabIndex = 4;
		this->d_ps_task_pag->Text = L"task";
		this->d_ps_task_pag->UseVisualStyleBackColor = true;
		// 
		// listView3
		// 
		this->listView3->Dock = System::Windows::Forms::DockStyle::Fill;
		this->listView3->GridLines = true;
		this->listView3->Location = System::Drawing::Point(3, 3);
		this->listView3->Name = L"listView3";
		this->listView3->Size = System::Drawing::Size(403, 330);
		this->listView3->TabIndex = 0;
		this->listView3->UseCompatibleStateImageBehavior = false;
		this->listView3->View = System::Windows::Forms::View::Details;
		// 
		// c_player_state_pal
		// 
		this->c_player_state_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_state_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_state_pal->Name = L"c_player_state_pal";
		this->c_player_state_pal->Size = System::Drawing::Size(447, 438);
		this->c_player_state_pal->TabIndex = 1;
		// 
		// c_gm_player_pag
		// 
		this->c_gm_player_pag->Controls->Add(this->c_gm_player_pal);
		this->c_gm_player_pag->Location = System::Drawing::Point(4, 21);
		this->c_gm_player_pag->Name = L"c_gm_player_pag";
		this->c_gm_player_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_gm_player_pag->Size = System::Drawing::Size(453, 444);
		this->c_gm_player_pag->TabIndex = 7;
		this->c_gm_player_pag->Text = L"gmplayer";
		this->c_gm_player_pag->UseVisualStyleBackColor = true;
		// 
		// c_gm_player_pal
		// 
		this->c_gm_player_pal->Controls->Add(this->d_pg_pal);
		this->c_gm_player_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_gm_player_pal->Location = System::Drawing::Point(3, 3);
		this->c_gm_player_pal->Name = L"c_gm_player_pal";
		this->c_gm_player_pal->Size = System::Drawing::Size(447, 438);
		this->c_gm_player_pal->TabIndex = 5;
		// 
		// d_pg_pal
		// 
		this->d_pg_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_pg_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_pg_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_pg_pal->Controls->Add(this->d_pg_record_gbo);
		this->d_pg_pal->Controls->Add(this->d_pg_config_gbo);
		this->d_pg_pal->Controls->Add(this->d_pg_commit_gbo);
		this->d_pg_pal->Controls->Add(this->d_pg_setting_gbo);
		this->d_pg_pal->Location = System::Drawing::Point(29, 18);
		this->d_pg_pal->Name = L"d_pg_pal";
		this->d_pg_pal->Size = System::Drawing::Size(392, 394);
		this->d_pg_pal->TabIndex = 5;
		// 
		// d_pg_record_gbo
		// 
		this->d_pg_record_gbo->Controls->Add(this->panel1);
		this->d_pg_record_gbo->Controls->Add(this->d_pg_record_list);
		this->d_pg_record_gbo->Location = System::Drawing::Point(29, 21);
		this->d_pg_record_gbo->Name = L"d_pg_record_gbo";
		this->d_pg_record_gbo->Size = System::Drawing::Size(160, 338);
		this->d_pg_record_gbo->TabIndex = 10;
		this->d_pg_record_gbo->TabStop = false;
		this->d_pg_record_gbo->Text = L"record";
		// 
		// panel1
		// 
		this->panel1->Controls->Add(this->d_pg_filter_server_cbo);
		this->panel1->Controls->Add(this->d_pg_record_pnl);
		this->panel1->Location = System::Drawing::Point(0, 21);
		this->panel1->Name = L"panel1";
		this->panel1->Size = System::Drawing::Size(154, 50);
		this->panel1->TabIndex = 1;
		// 
		// d_pg_filter_server_cbo
		// 
		this->d_pg_filter_server_cbo->FormattingEnabled = true;
		this->d_pg_filter_server_cbo->Location = System::Drawing::Point(3, 21);
		this->d_pg_filter_server_cbo->Name = L"d_pg_filter_server_cbo";
		this->d_pg_filter_server_cbo->Size = System::Drawing::Size(145, 20);
		this->d_pg_filter_server_cbo->TabIndex = 1;
		this->d_pg_filter_server_cbo->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::d_pg_filter_server_cbo_SelectedIndexChanged);
		// 
		// d_pg_record_pnl
		// 
		this->d_pg_record_pnl->AutoSize = true;
		this->d_pg_record_pnl->Location = System::Drawing::Point(7, 6);
		this->d_pg_record_pnl->Name = L"d_pg_record_pnl";
		this->d_pg_record_pnl->Size = System::Drawing::Size(41, 12);
		this->d_pg_record_pnl->TabIndex = 0;
		this->d_pg_record_pnl->Text = L"server";
		// 
		// d_pg_record_list
		// 
		this->d_pg_record_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dpg_column_player_name, 
			this->dpg_column_gm_level});
		this->d_pg_record_list->FullRowSelect = true;
		this->d_pg_record_list->GridLines = true;
		this->d_pg_record_list->HideSelection = false;
		this->d_pg_record_list->Location = System::Drawing::Point(6, 77);
		this->d_pg_record_list->Name = L"d_pg_record_list";
		this->d_pg_record_list->Size = System::Drawing::Size(148, 261);
		this->d_pg_record_list->TabIndex = 0;
		this->d_pg_record_list->UseCompatibleStateImageBehavior = false;
		this->d_pg_record_list->View = System::Windows::Forms::View::Details;
		this->d_pg_record_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_pg_record_list_MouseDoubleClick);
		// 
		// dpg_column_player_name
		// 
		this->dpg_column_player_name->Text = L"player_name";
		// 
		// dpg_column_gm_level
		// 
		this->dpg_column_gm_level->Text = L"gm_level";
		this->dpg_column_gm_level->Width = 69;
		// 
		// d_pg_config_gbo
		// 
		this->d_pg_config_gbo->Controls->Add(this->d_pg_username_edt);
		this->d_pg_config_gbo->Controls->Add(this->d_pg_server_cbo);
		this->d_pg_config_gbo->Controls->Add(this->d_pg_username_lbl);
		this->d_pg_config_gbo->Controls->Add(this->d_pg_server_lbl);
		this->d_pg_config_gbo->Location = System::Drawing::Point(195, 79);
		this->d_pg_config_gbo->Name = L"d_pg_config_gbo";
		this->d_pg_config_gbo->Size = System::Drawing::Size(180, 84);
		this->d_pg_config_gbo->TabIndex = 9;
		this->d_pg_config_gbo->TabStop = false;
		this->d_pg_config_gbo->Text = L"config";
		// 
		// d_pg_username_edt
		// 
		this->d_pg_username_edt->Location = System::Drawing::Point(73, 51);
		this->d_pg_username_edt->Name = L"d_pg_username_edt";
		this->d_pg_username_edt->Size = System::Drawing::Size(103, 21);
		this->d_pg_username_edt->TabIndex = 13;
		// 
		// d_pg_server_cbo
		// 
		this->d_pg_server_cbo->FormattingEnabled = true;
		this->d_pg_server_cbo->Location = System::Drawing::Point(73, 20);
		this->d_pg_server_cbo->Name = L"d_pg_server_cbo";
		this->d_pg_server_cbo->Size = System::Drawing::Size(103, 20);
		this->d_pg_server_cbo->TabIndex = 12;
		// 
		// d_pg_username_lbl
		// 
		this->d_pg_username_lbl->AutoSize = true;
		this->d_pg_username_lbl->Location = System::Drawing::Point(14, 54);
		this->d_pg_username_lbl->Name = L"d_pg_username_lbl";
		this->d_pg_username_lbl->Size = System::Drawing::Size(53, 12);
		this->d_pg_username_lbl->TabIndex = 10;
		this->d_pg_username_lbl->Text = L"username";
		// 
		// d_pg_server_lbl
		// 
		this->d_pg_server_lbl->AutoSize = true;
		this->d_pg_server_lbl->Location = System::Drawing::Point(14, 23);
		this->d_pg_server_lbl->Name = L"d_pg_server_lbl";
		this->d_pg_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pg_server_lbl->TabIndex = 9;
		this->d_pg_server_lbl->Text = L"server";
		// 
		// d_pg_commit_gbo
		// 
		this->d_pg_commit_gbo->Controls->Add(this->d_pg_commit_btn);
		this->d_pg_commit_gbo->Location = System::Drawing::Point(195, 255);
		this->d_pg_commit_gbo->Name = L"d_pg_commit_gbo";
		this->d_pg_commit_gbo->Size = System::Drawing::Size(180, 53);
		this->d_pg_commit_gbo->TabIndex = 7;
		this->d_pg_commit_gbo->TabStop = false;
		this->d_pg_commit_gbo->Text = L"commit";
		// 
		// d_pg_commit_btn
		// 
		this->d_pg_commit_btn->Location = System::Drawing::Point(62, 15);
		this->d_pg_commit_btn->Name = L"d_pg_commit_btn";
		this->d_pg_commit_btn->Size = System::Drawing::Size(75, 23);
		this->d_pg_commit_btn->TabIndex = 0;
		this->d_pg_commit_btn->Text = L"commint";
		this->d_pg_commit_btn->UseVisualStyleBackColor = true;
		this->d_pg_commit_btn->Click += gcnew System::EventHandler(this, &MainForm::d_pg_commit_btn_Click);
		// 
		// d_pg_setting_gbo
		// 
		this->d_pg_setting_gbo->Controls->Add(this->d_pg_open_rdo);
		this->d_pg_setting_gbo->Controls->Add(this->d_pg_close_rdo);
		this->d_pg_setting_gbo->Location = System::Drawing::Point(195, 180);
		this->d_pg_setting_gbo->Name = L"d_pg_setting_gbo";
		this->d_pg_setting_gbo->Size = System::Drawing::Size(180, 69);
		this->d_pg_setting_gbo->TabIndex = 6;
		this->d_pg_setting_gbo->TabStop = false;
		this->d_pg_setting_gbo->Text = L"setting";
		// 
		// d_pg_open_rdo
		// 
		this->d_pg_open_rdo->AutoSize = true;
		this->d_pg_open_rdo->Location = System::Drawing::Point(27, 20);
		this->d_pg_open_rdo->Name = L"d_pg_open_rdo";
		this->d_pg_open_rdo->Size = System::Drawing::Size(47, 16);
		this->d_pg_open_rdo->TabIndex = 14;
		this->d_pg_open_rdo->TabStop = true;
		this->d_pg_open_rdo->Text = L"open";
		this->d_pg_open_rdo->UseVisualStyleBackColor = true;
		// 
		// d_pg_close_rdo
		// 
		this->d_pg_close_rdo->AutoSize = true;
		this->d_pg_close_rdo->Location = System::Drawing::Point(27, 47);
		this->d_pg_close_rdo->Name = L"d_pg_close_rdo";
		this->d_pg_close_rdo->Size = System::Drawing::Size(53, 16);
		this->d_pg_close_rdo->TabIndex = 13;
		this->d_pg_close_rdo->TabStop = true;
		this->d_pg_close_rdo->Text = L"close";
		this->d_pg_close_rdo->UseVisualStyleBackColor = true;
		// 
		// c_player_kill_npc_pag
		// 
		this->c_player_kill_npc_pag->Controls->Add(this->c_player_kill_npc_pal);
		this->c_player_kill_npc_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_kill_npc_pag->Name = L"c_player_kill_npc_pag";
		this->c_player_kill_npc_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_kill_npc_pag->Size = System::Drawing::Size(453, 444);
		this->c_player_kill_npc_pag->TabIndex = 8;
		this->c_player_kill_npc_pag->Text = L"kill";
		this->c_player_kill_npc_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_kill_npc_pal
		// 
		this->c_player_kill_npc_pal->Controls->Add(this->d_pkl_pal);
		this->c_player_kill_npc_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_kill_npc_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_kill_npc_pal->Name = L"c_player_kill_npc_pal";
		this->c_player_kill_npc_pal->Size = System::Drawing::Size(447, 438);
		this->c_player_kill_npc_pal->TabIndex = 1;
		// 
		// d_pkl_pal
		// 
		this->d_pkl_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_pkl_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_pkl_pal->Controls->Add(this->d_pkl_commit_gbo);
		this->d_pkl_pal->Controls->Add(this->d_pkl_config_gbo);
		this->d_pkl_pal->Location = System::Drawing::Point(28, 97);
		this->d_pkl_pal->Name = L"d_pkl_pal";
		this->d_pkl_pal->Size = System::Drawing::Size(388, 246);
		this->d_pkl_pal->TabIndex = 0;
		// 
		// d_pkl_commit_gbo
		// 
		this->d_pkl_commit_gbo->Controls->Add(this->d_pkl_commit_btn);
		this->d_pkl_commit_gbo->Location = System::Drawing::Point(34, 141);
		this->d_pkl_commit_gbo->Name = L"d_pkl_commit_gbo";
		this->d_pkl_commit_gbo->Size = System::Drawing::Size(315, 75);
		this->d_pkl_commit_gbo->TabIndex = 5;
		this->d_pkl_commit_gbo->TabStop = false;
		this->d_pkl_commit_gbo->Text = L"commit";
		// 
		// d_pkl_commit_btn
		// 
		this->d_pkl_commit_btn->Location = System::Drawing::Point(102, 30);
		this->d_pkl_commit_btn->Name = L"d_pkl_commit_btn";
		this->d_pkl_commit_btn->Size = System::Drawing::Size(119, 28);
		this->d_pkl_commit_btn->TabIndex = 3;
		this->d_pkl_commit_btn->Text = L"commint";
		this->d_pkl_commit_btn->UseVisualStyleBackColor = true;
		this->d_pkl_commit_btn->Click += gcnew System::EventHandler(this, &MainForm::d_pkl_commit_btn_Click);
		// 
		// d_pkl_config_gbo
		// 
		this->d_pkl_config_gbo->Controls->Add(this->d_pkl_username_cbo);
		this->d_pkl_config_gbo->Controls->Add(this->d_pkl_server_cbo);
		this->d_pkl_config_gbo->Controls->Add(this->d_pkl_username_lbl);
		this->d_pkl_config_gbo->Controls->Add(this->d_pkl_server_lbl);
		this->d_pkl_config_gbo->Location = System::Drawing::Point(34, 27);
		this->d_pkl_config_gbo->Name = L"d_pkl_config_gbo";
		this->d_pkl_config_gbo->Size = System::Drawing::Size(315, 108);
		this->d_pkl_config_gbo->TabIndex = 4;
		this->d_pkl_config_gbo->TabStop = false;
		this->d_pkl_config_gbo->Text = L"config";
		// 
		// d_pkl_username_cbo
		// 
		this->d_pkl_username_cbo->FormattingEnabled = true;
		this->d_pkl_username_cbo->Location = System::Drawing::Point(121, 75);
		this->d_pkl_username_cbo->Name = L"d_pkl_username_cbo";
		this->d_pkl_username_cbo->Size = System::Drawing::Size(121, 20);
		this->d_pkl_username_cbo->TabIndex = 2;
		// 
		// d_pkl_server_cbo
		// 
		this->d_pkl_server_cbo->FormattingEnabled = true;
		this->d_pkl_server_cbo->Location = System::Drawing::Point(121, 37);
		this->d_pkl_server_cbo->Name = L"d_pkl_server_cbo";
		this->d_pkl_server_cbo->Size = System::Drawing::Size(121, 20);
		this->d_pkl_server_cbo->TabIndex = 1;
		// 
		// d_pkl_username_lbl
		// 
		this->d_pkl_username_lbl->AutoSize = true;
		this->d_pkl_username_lbl->Location = System::Drawing::Point(52, 78);
		this->d_pkl_username_lbl->Name = L"d_pkl_username_lbl";
		this->d_pkl_username_lbl->Size = System::Drawing::Size(53, 12);
		this->d_pkl_username_lbl->TabIndex = 0;
		this->d_pkl_username_lbl->Text = L"username";
		// 
		// d_pkl_server_lbl
		// 
		this->d_pkl_server_lbl->AutoSize = true;
		this->d_pkl_server_lbl->Location = System::Drawing::Point(52, 40);
		this->d_pkl_server_lbl->Name = L"d_pkl_server_lbl";
		this->d_pkl_server_lbl->Size = System::Drawing::Size(41, 12);
		this->d_pkl_server_lbl->TabIndex = 0;
		this->d_pkl_server_lbl->Text = L"server";
		// 
		// c_player_spl
		// 
		this->c_player_spl->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->c_player_spl->Dock = System::Windows::Forms::DockStyle::Right;
		this->c_player_spl->Location = System::Drawing::Point(463, 0);
		this->c_player_spl->Name = L"c_player_spl";
		this->c_player_spl->Size = System::Drawing::Size(2, 471);
		this->c_player_spl->TabIndex = 5;
		this->c_player_spl->TabStop = false;
		// 
		// c_player_left_pal
		// 
		this->c_player_left_pal->Controls->Add(this->c_player_search_tab);
		this->c_player_left_pal->Dock = System::Windows::Forms::DockStyle::Right;
		this->c_player_left_pal->Location = System::Drawing::Point(465, 0);
		this->c_player_left_pal->Name = L"c_player_left_pal";
		this->c_player_left_pal->Size = System::Drawing::Size(179, 471);
		this->c_player_left_pal->TabIndex = 3;
		// 
		// c_player_search_tab
		// 
		this->c_player_search_tab->Controls->Add(this->c_player_search_player_pag);
		this->c_player_search_tab->Controls->Add(this->c_player_search_npc_pag);
		this->c_player_search_tab->Controls->Add(this->c_player_search_item_pag);
		this->c_player_search_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_tab->Location = System::Drawing::Point(0, 0);
		this->c_player_search_tab->Name = L"c_player_search_tab";
		this->c_player_search_tab->SelectedIndex = 0;
		this->c_player_search_tab->Size = System::Drawing::Size(179, 471);
		this->c_player_search_tab->TabIndex = 6;
		// 
		// c_player_search_player_pag
		// 
		this->c_player_search_player_pag->Controls->Add(this->c_player_search_player_pal);
		this->c_player_search_player_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_search_player_pag->Name = L"c_player_search_player_pag";
		this->c_player_search_player_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_search_player_pag->Size = System::Drawing::Size(171, 446);
		this->c_player_search_player_pag->TabIndex = 0;
		this->c_player_search_player_pag->Text = L"player";
		this->c_player_search_player_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_search_player_pal
		// 
		this->c_player_search_player_pal->Controls->Add(this->c_player_search_player_list_pal);
		this->c_player_search_player_pal->Controls->Add(this->c_player_search_player_op_pal);
		this->c_player_search_player_pal->Controls->Add(this->c_player_search_player_filter_pal);
		this->c_player_search_player_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_player_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_search_player_pal->Name = L"c_player_search_player_pal";
		this->c_player_search_player_pal->Size = System::Drawing::Size(165, 440);
		this->c_player_search_player_pal->TabIndex = 0;
		// 
		// c_player_search_player_list_pal
		// 
		this->c_player_search_player_list_pal->Controls->Add(this->c_player_search_player_list);
		this->c_player_search_player_list_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_player_list_pal->Location = System::Drawing::Point(0, 138);
		this->c_player_search_player_list_pal->Name = L"c_player_search_player_list_pal";
		this->c_player_search_player_list_pal->Size = System::Drawing::Size(165, 275);
		this->c_player_search_player_list_pal->TabIndex = 2;
		// 
		// c_player_search_player_list
		// 
		this->c_player_search_player_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->cps_player_column_account_name, 
			this->cps_player_column_name, this->cps_player_column_uin, this->cps_player_column_id, this->cps_player_column_region_id});
		this->c_player_search_player_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_player_list->FullRowSelect = true;
		this->c_player_search_player_list->GridLines = true;
		this->c_player_search_player_list->HideSelection = false;
		this->c_player_search_player_list->Location = System::Drawing::Point(0, 0);
		this->c_player_search_player_list->Name = L"c_player_search_player_list";
		this->c_player_search_player_list->Size = System::Drawing::Size(165, 275);
		this->c_player_search_player_list->TabIndex = 0;
		this->c_player_search_player_list->UseCompatibleStateImageBehavior = false;
		this->c_player_search_player_list->View = System::Windows::Forms::View::Details;
		this->c_player_search_player_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::c_player_search_player_list_MouseDoubleClick);
		// 
		// cps_player_column_account_name
		// 
		this->cps_player_column_account_name->Text = L"AccountName";
		// 
		// cps_player_column_name
		// 
		this->cps_player_column_name->Text = L"Name";
		this->cps_player_column_name->Width = 100;
		// 
		// cps_player_column_uin
		// 
		this->cps_player_column_uin->Text = L"uin";
		this->cps_player_column_uin->Width = 120;
		// 
		// cps_player_column_id
		// 
		this->cps_player_column_id->Text = L"ID";
		this->cps_player_column_id->Width = 80;
		// 
		// c_player_search_player_op_pal
		// 
		this->c_player_search_player_op_pal->Controls->Add(this->c_player_search_player_get_all_btn);
		this->c_player_search_player_op_pal->Controls->Add(this->c_player_search_player_get_sel_btn);
		this->c_player_search_player_op_pal->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->c_player_search_player_op_pal->Location = System::Drawing::Point(0, 413);
		this->c_player_search_player_op_pal->Name = L"c_player_search_player_op_pal";
		this->c_player_search_player_op_pal->Size = System::Drawing::Size(165, 27);
		this->c_player_search_player_op_pal->TabIndex = 1;
		// 
		// c_player_search_player_get_all_btn
		// 
		this->c_player_search_player_get_all_btn->Location = System::Drawing::Point(85, 3);
		this->c_player_search_player_get_all_btn->Name = L"c_player_search_player_get_all_btn";
		this->c_player_search_player_get_all_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_player_get_all_btn->TabIndex = 1;
		this->c_player_search_player_get_all_btn->Text = L"get all";
		this->c_player_search_player_get_all_btn->UseVisualStyleBackColor = true;
		this->c_player_search_player_get_all_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_player_get_all_btn_Click);
		// 
		// c_player_search_player_get_sel_btn
		// 
		this->c_player_search_player_get_sel_btn->Location = System::Drawing::Point(6, 3);
		this->c_player_search_player_get_sel_btn->Name = L"c_player_search_player_get_sel_btn";
		this->c_player_search_player_get_sel_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_player_get_sel_btn->TabIndex = 0;
		this->c_player_search_player_get_sel_btn->Text = L"get sel";
		this->c_player_search_player_get_sel_btn->UseVisualStyleBackColor = true;
		this->c_player_search_player_get_sel_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_player_get_sel_btn_Click);
		// 
		// c_player_search_player_filter_pal
		// 
		this->c_player_search_player_filter_pal->Controls->Add(this->c_player_search_player_blur_cbx);
		this->c_player_search_player_filter_pal->Controls->Add(this->c_player_search_player_search_btn);
		this->c_player_search_player_filter_pal->Controls->Add(this->c_player_search_player_gbo);
		this->c_player_search_player_filter_pal->Dock = System::Windows::Forms::DockStyle::Top;
		this->c_player_search_player_filter_pal->Location = System::Drawing::Point(0, 0);
		this->c_player_search_player_filter_pal->Name = L"c_player_search_player_filter_pal";
		this->c_player_search_player_filter_pal->Size = System::Drawing::Size(165, 138);
		this->c_player_search_player_filter_pal->TabIndex = 0;
		// 
		// c_player_search_player_blur_cbx
		// 
		this->c_player_search_player_blur_cbx->AutoSize = true;
		this->c_player_search_player_blur_cbx->Location = System::Drawing::Point(6, 113);
		this->c_player_search_player_blur_cbx->Name = L"c_player_search_player_blur_cbx";
		this->c_player_search_player_blur_cbx->Size = System::Drawing::Size(48, 16);
		this->c_player_search_player_blur_cbx->TabIndex = 7;
		this->c_player_search_player_blur_cbx->Text = L"blur";
		this->c_player_search_player_blur_cbx->UseVisualStyleBackColor = true;
		// 
		// c_player_search_player_search_btn
		// 
		this->c_player_search_player_search_btn->Location = System::Drawing::Point(85, 109);
		this->c_player_search_player_search_btn->Name = L"c_player_search_player_search_btn";
		this->c_player_search_player_search_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_player_search_btn->TabIndex = 6;
		this->c_player_search_player_search_btn->Text = L"search";
		this->c_player_search_player_search_btn->UseVisualStyleBackColor = true;
		this->c_player_search_player_search_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_player_search_btn_Click);
		this->c_player_search_player_search_btn->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::c_player_search_player_search_btn_MouseClick);
		// 
		// c_player_search_player_gbo
		// 
		this->c_player_search_player_gbo->Controls->Add(this->c_player_search_player_charactor_edt);
		this->c_player_search_player_gbo->Controls->Add(this->c_player_search_player_account_edt);
		this->c_player_search_player_gbo->Controls->Add(this->c_player_search_player_server_cbo);
		this->c_player_search_player_gbo->Controls->Add(this->c_player_search_player_charactor_cbx);
		this->c_player_search_player_gbo->Controls->Add(this->c_player_search_player_account_cbx);
		this->c_player_search_player_gbo->Controls->Add(this->c_player_search_player_server_lbl);
		this->c_player_search_player_gbo->Dock = System::Windows::Forms::DockStyle::Top;
		this->c_player_search_player_gbo->Location = System::Drawing::Point(0, 0);
		this->c_player_search_player_gbo->Name = L"c_player_search_player_gbo";
		this->c_player_search_player_gbo->Size = System::Drawing::Size(165, 103);
		this->c_player_search_player_gbo->TabIndex = 0;
		this->c_player_search_player_gbo->TabStop = false;
		this->c_player_search_player_gbo->Text = L"search";
		// 
		// c_player_search_player_charactor_edt
		// 
		this->c_player_search_player_charactor_edt->Location = System::Drawing::Point(81, 68);
		this->c_player_search_player_charactor_edt->Name = L"c_player_search_player_charactor_edt";
		this->c_player_search_player_charactor_edt->Size = System::Drawing::Size(78, 21);
		this->c_player_search_player_charactor_edt->TabIndex = 8;
		// 
		// c_player_search_player_account_edt
		// 
		this->c_player_search_player_account_edt->Enabled = false;
		this->c_player_search_player_account_edt->Location = System::Drawing::Point(81, 41);
		this->c_player_search_player_account_edt->Name = L"c_player_search_player_account_edt";
		this->c_player_search_player_account_edt->Size = System::Drawing::Size(78, 21);
		this->c_player_search_player_account_edt->TabIndex = 7;
		// 
		// c_player_search_player_server_cbo
		// 
		this->c_player_search_player_server_cbo->FormattingEnabled = true;
		this->c_player_search_player_server_cbo->Location = System::Drawing::Point(81, 15);
		this->c_player_search_player_server_cbo->Name = L"c_player_search_player_server_cbo";
		this->c_player_search_player_server_cbo->Size = System::Drawing::Size(78, 20);
		this->c_player_search_player_server_cbo->TabIndex = 6;
		// 
		// c_player_search_player_charactor_cbx
		// 
		this->c_player_search_player_charactor_cbx->AutoSize = true;
		this->c_player_search_player_charactor_cbx->Checked = true;
		this->c_player_search_player_charactor_cbx->CheckState = System::Windows::Forms::CheckState::Checked;
		this->c_player_search_player_charactor_cbx->Location = System::Drawing::Point(4, 70);
		this->c_player_search_player_charactor_cbx->Name = L"c_player_search_player_charactor_cbx";
		this->c_player_search_player_charactor_cbx->Size = System::Drawing::Size(78, 16);
		this->c_player_search_player_charactor_cbx->TabIndex = 2;
		this->c_player_search_player_charactor_cbx->Text = L"charactor";
		this->c_player_search_player_charactor_cbx->UseVisualStyleBackColor = true;
		this->c_player_search_player_charactor_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::c_player_search_player_charactor_cbx_CheckedChanged);
		// 
		// c_player_search_player_account_cbx
		// 
		this->c_player_search_player_account_cbx->AutoSize = true;
		this->c_player_search_player_account_cbx->Location = System::Drawing::Point(4, 43);
		this->c_player_search_player_account_cbx->Name = L"c_player_search_player_account_cbx";
		this->c_player_search_player_account_cbx->Size = System::Drawing::Size(66, 16);
		this->c_player_search_player_account_cbx->TabIndex = 1;
		this->c_player_search_player_account_cbx->Text = L"account";
		this->c_player_search_player_account_cbx->UseVisualStyleBackColor = true;
		this->c_player_search_player_account_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::c_player_search_player_account_cbx_CheckedChanged);
		// 
		// c_player_search_player_server_lbl
		// 
		this->c_player_search_player_server_lbl->AutoSize = true;
		this->c_player_search_player_server_lbl->Location = System::Drawing::Point(21, 19);
		this->c_player_search_player_server_lbl->Name = L"c_player_search_player_server_lbl";
		this->c_player_search_player_server_lbl->Size = System::Drawing::Size(41, 12);
		this->c_player_search_player_server_lbl->TabIndex = 0;
		this->c_player_search_player_server_lbl->Text = L"server";
		// 
		// c_player_search_npc_pag
		// 
		this->c_player_search_npc_pag->Controls->Add(this->c_player_search_npc_pal);
		this->c_player_search_npc_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_search_npc_pag->Name = L"c_player_search_npc_pag";
		this->c_player_search_npc_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_search_npc_pag->Size = System::Drawing::Size(171, 446);
		this->c_player_search_npc_pag->TabIndex = 1;
		this->c_player_search_npc_pag->Text = L"npc";
		this->c_player_search_npc_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_search_npc_pal
		// 
		this->c_player_search_npc_pal->Controls->Add(this->c_player_search_npc_list_pal);
		this->c_player_search_npc_pal->Controls->Add(this->c_player_search_npc_op_pal);
		this->c_player_search_npc_pal->Controls->Add(this->c_player_search_npc_filter_pal);
		this->c_player_search_npc_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_npc_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_search_npc_pal->Name = L"c_player_search_npc_pal";
		this->c_player_search_npc_pal->Size = System::Drawing::Size(165, 440);
		this->c_player_search_npc_pal->TabIndex = 0;
		// 
		// c_player_search_npc_list_pal
		// 
		this->c_player_search_npc_list_pal->Controls->Add(this->c_player_search_npc_list);
		this->c_player_search_npc_list_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_npc_list_pal->Location = System::Drawing::Point(0, 113);
		this->c_player_search_npc_list_pal->Name = L"c_player_search_npc_list_pal";
		this->c_player_search_npc_list_pal->Size = System::Drawing::Size(165, 300);
		this->c_player_search_npc_list_pal->TabIndex = 3;
		// 
		// c_player_search_npc_list
		// 
		this->c_player_search_npc_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->cps_column_npc_name, 
			this->cps_column_npc_id, this->cps_column_npc_type});
		this->c_player_search_npc_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_npc_list->FullRowSelect = true;
		this->c_player_search_npc_list->GridLines = true;
		this->c_player_search_npc_list->HideSelection = false;
		this->c_player_search_npc_list->Location = System::Drawing::Point(0, 0);
		this->c_player_search_npc_list->Name = L"c_player_search_npc_list";
		this->c_player_search_npc_list->Size = System::Drawing::Size(165, 300);
		this->c_player_search_npc_list->TabIndex = 0;
		this->c_player_search_npc_list->UseCompatibleStateImageBehavior = false;
		this->c_player_search_npc_list->View = System::Windows::Forms::View::Details;
		this->c_player_search_npc_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::c_player_search_npc_list_MouseDoubleClick);
		// 
		// cps_column_npc_name
		// 
		this->cps_column_npc_name->Text = L"npc_name";
		this->cps_column_npc_name->Width = 100;
		// 
		// cps_column_npc_id
		// 
		this->cps_column_npc_id->Text = L"npc_id";
		this->cps_column_npc_id->Width = 80;
		// 
		// cps_column_npc_type
		// 
		this->cps_column_npc_type->Text = L"type";
		// 
		// c_player_search_npc_op_pal
		// 
		this->c_player_search_npc_op_pal->Controls->Add(this->c_player_search_npc_get_all_btn);
		this->c_player_search_npc_op_pal->Controls->Add(this->c_player_search_npc_get_sel_btn);
		this->c_player_search_npc_op_pal->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->c_player_search_npc_op_pal->Location = System::Drawing::Point(0, 413);
		this->c_player_search_npc_op_pal->Name = L"c_player_search_npc_op_pal";
		this->c_player_search_npc_op_pal->Size = System::Drawing::Size(165, 27);
		this->c_player_search_npc_op_pal->TabIndex = 2;
		// 
		// c_player_search_npc_get_all_btn
		// 
		this->c_player_search_npc_get_all_btn->Location = System::Drawing::Point(85, 3);
		this->c_player_search_npc_get_all_btn->Name = L"c_player_search_npc_get_all_btn";
		this->c_player_search_npc_get_all_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_npc_get_all_btn->TabIndex = 1;
		this->c_player_search_npc_get_all_btn->Text = L"get all";
		this->c_player_search_npc_get_all_btn->UseVisualStyleBackColor = true;
		this->c_player_search_npc_get_all_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_npc_get_all_btn_Click);
		// 
		// c_player_search_npc_get_sel_btn
		// 
		this->c_player_search_npc_get_sel_btn->Location = System::Drawing::Point(6, 3);
		this->c_player_search_npc_get_sel_btn->Name = L"c_player_search_npc_get_sel_btn";
		this->c_player_search_npc_get_sel_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_npc_get_sel_btn->TabIndex = 0;
		this->c_player_search_npc_get_sel_btn->Text = L"get sel";
		this->c_player_search_npc_get_sel_btn->UseVisualStyleBackColor = true;
		this->c_player_search_npc_get_sel_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_npc_get_sel_btn_Click);
		// 
		// c_player_search_npc_filter_pal
		// 
		this->c_player_search_npc_filter_pal->Controls->Add(this->c_player_search_npc_search_btn);
		this->c_player_search_npc_filter_pal->Controls->Add(this->c_player_search_npc_gbo);
		this->c_player_search_npc_filter_pal->Dock = System::Windows::Forms::DockStyle::Top;
		this->c_player_search_npc_filter_pal->Location = System::Drawing::Point(0, 0);
		this->c_player_search_npc_filter_pal->Name = L"c_player_search_npc_filter_pal";
		this->c_player_search_npc_filter_pal->Size = System::Drawing::Size(165, 113);
		this->c_player_search_npc_filter_pal->TabIndex = 1;
		// 
		// c_player_search_npc_search_btn
		// 
		this->c_player_search_npc_search_btn->Location = System::Drawing::Point(82, 84);
		this->c_player_search_npc_search_btn->Name = L"c_player_search_npc_search_btn";
		this->c_player_search_npc_search_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_npc_search_btn->TabIndex = 6;
		this->c_player_search_npc_search_btn->Text = L"search";
		this->c_player_search_npc_search_btn->UseVisualStyleBackColor = true;
		this->c_player_search_npc_search_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_npc_search_btn_Click);
		// 
		// c_player_search_npc_gbo
		// 
		this->c_player_search_npc_gbo->Controls->Add(this->c_player_search_npc_id_edt);
		this->c_player_search_npc_gbo->Controls->Add(this->c_player_search_npc_name_edt);
		this->c_player_search_npc_gbo->Controls->Add(this->c_player_search_npc_id_cbx);
		this->c_player_search_npc_gbo->Controls->Add(this->c_player_search_npc_name_cbx);
		this->c_player_search_npc_gbo->Dock = System::Windows::Forms::DockStyle::Top;
		this->c_player_search_npc_gbo->Location = System::Drawing::Point(0, 0);
		this->c_player_search_npc_gbo->Name = L"c_player_search_npc_gbo";
		this->c_player_search_npc_gbo->Size = System::Drawing::Size(165, 79);
		this->c_player_search_npc_gbo->TabIndex = 0;
		this->c_player_search_npc_gbo->TabStop = false;
		this->c_player_search_npc_gbo->Text = L"search";
		// 
		// c_player_search_npc_id_edt
		// 
		this->c_player_search_npc_id_edt->Enabled = false;
		this->c_player_search_npc_id_edt->Location = System::Drawing::Point(78, 46);
		this->c_player_search_npc_id_edt->Name = L"c_player_search_npc_id_edt";
		this->c_player_search_npc_id_edt->Size = System::Drawing::Size(78, 21);
		this->c_player_search_npc_id_edt->TabIndex = 8;
		// 
		// c_player_search_npc_name_edt
		// 
		this->c_player_search_npc_name_edt->Enabled = false;
		this->c_player_search_npc_name_edt->Location = System::Drawing::Point(78, 18);
		this->c_player_search_npc_name_edt->Name = L"c_player_search_npc_name_edt";
		this->c_player_search_npc_name_edt->Size = System::Drawing::Size(78, 21);
		this->c_player_search_npc_name_edt->TabIndex = 7;
		// 
		// c_player_search_npc_id_cbx
		// 
		this->c_player_search_npc_id_cbx->AutoSize = true;
		this->c_player_search_npc_id_cbx->Location = System::Drawing::Point(11, 50);
		this->c_player_search_npc_id_cbx->Name = L"c_player_search_npc_id_cbx";
		this->c_player_search_npc_id_cbx->Size = System::Drawing::Size(36, 16);
		this->c_player_search_npc_id_cbx->TabIndex = 2;
		this->c_player_search_npc_id_cbx->Text = L"id";
		this->c_player_search_npc_id_cbx->UseVisualStyleBackColor = true;
		this->c_player_search_npc_id_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::c_player_search_npc_id_cbx_CheckedChanged);
		// 
		// c_player_search_npc_name_cbx
		// 
		this->c_player_search_npc_name_cbx->AutoSize = true;
		this->c_player_search_npc_name_cbx->Location = System::Drawing::Point(11, 21);
		this->c_player_search_npc_name_cbx->Name = L"c_player_search_npc_name_cbx";
		this->c_player_search_npc_name_cbx->Size = System::Drawing::Size(48, 16);
		this->c_player_search_npc_name_cbx->TabIndex = 1;
		this->c_player_search_npc_name_cbx->Text = L"name";
		this->c_player_search_npc_name_cbx->UseVisualStyleBackColor = true;
		this->c_player_search_npc_name_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::c_player_search_npc_name_cbx_CheckedChanged);
		// 
		// c_player_search_item_pag
		// 
		this->c_player_search_item_pag->Controls->Add(this->c_player_search_item_pal);
		this->c_player_search_item_pag->Location = System::Drawing::Point(4, 21);
		this->c_player_search_item_pag->Name = L"c_player_search_item_pag";
		this->c_player_search_item_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_player_search_item_pag->Size = System::Drawing::Size(171, 446);
		this->c_player_search_item_pag->TabIndex = 2;
		this->c_player_search_item_pag->Text = L"item";
		this->c_player_search_item_pag->UseVisualStyleBackColor = true;
		// 
		// c_player_search_item_pal
		// 
		this->c_player_search_item_pal->Controls->Add(this->c_player_search_item_list_pal);
		this->c_player_search_item_pal->Controls->Add(this->c_player_search_item_op_pal);
		this->c_player_search_item_pal->Controls->Add(this->c_player_search_item_filter_pal);
		this->c_player_search_item_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_item_pal->Location = System::Drawing::Point(3, 3);
		this->c_player_search_item_pal->Name = L"c_player_search_item_pal";
		this->c_player_search_item_pal->Size = System::Drawing::Size(165, 440);
		this->c_player_search_item_pal->TabIndex = 0;
		// 
		// c_player_search_item_list_pal
		// 
		this->c_player_search_item_list_pal->Controls->Add(this->c_player_search_item_list);
		this->c_player_search_item_list_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_item_list_pal->Location = System::Drawing::Point(0, 112);
		this->c_player_search_item_list_pal->Name = L"c_player_search_item_list_pal";
		this->c_player_search_item_list_pal->Size = System::Drawing::Size(165, 301);
		this->c_player_search_item_list_pal->TabIndex = 3;
		// 
		// c_player_search_item_list
		// 
		this->c_player_search_item_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->cps_column_item_name, 
			this->cps_column_item_id, this->cps_column_item_type});
		this->c_player_search_item_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_player_search_item_list->FullRowSelect = true;
		this->c_player_search_item_list->GridLines = true;
		this->c_player_search_item_list->HideSelection = false;
		this->c_player_search_item_list->Location = System::Drawing::Point(0, 0);
		this->c_player_search_item_list->Name = L"c_player_search_item_list";
		this->c_player_search_item_list->Size = System::Drawing::Size(165, 301);
		this->c_player_search_item_list->TabIndex = 0;
		this->c_player_search_item_list->UseCompatibleStateImageBehavior = false;
		this->c_player_search_item_list->View = System::Windows::Forms::View::Details;
		this->c_player_search_item_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::c_player_search_item_list_MouseDoubleClick);
		// 
		// cps_column_item_name
		// 
		this->cps_column_item_name->Text = L"item_name";
		this->cps_column_item_name->Width = 100;
		// 
		// cps_column_item_id
		// 
		this->cps_column_item_id->Text = L"item_id";
		this->cps_column_item_id->Width = 80;
		// 
		// cps_column_item_type
		// 
		this->cps_column_item_type->Text = L"type";
		// 
		// c_player_search_item_op_pal
		// 
		this->c_player_search_item_op_pal->Controls->Add(this->c_player_search_item_get_all_btn);
		this->c_player_search_item_op_pal->Controls->Add(this->c_player_search_item_get_sel_btn);
		this->c_player_search_item_op_pal->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->c_player_search_item_op_pal->Location = System::Drawing::Point(0, 413);
		this->c_player_search_item_op_pal->Name = L"c_player_search_item_op_pal";
		this->c_player_search_item_op_pal->Size = System::Drawing::Size(165, 27);
		this->c_player_search_item_op_pal->TabIndex = 2;
		// 
		// c_player_search_item_get_all_btn
		// 
		this->c_player_search_item_get_all_btn->Location = System::Drawing::Point(85, 3);
		this->c_player_search_item_get_all_btn->Name = L"c_player_search_item_get_all_btn";
		this->c_player_search_item_get_all_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_item_get_all_btn->TabIndex = 1;
		this->c_player_search_item_get_all_btn->Text = L"get all";
		this->c_player_search_item_get_all_btn->UseVisualStyleBackColor = true;
		this->c_player_search_item_get_all_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_item_get_all_btn_Click);
		// 
		// c_player_search_item_get_sel_btn
		// 
		this->c_player_search_item_get_sel_btn->Location = System::Drawing::Point(6, 3);
		this->c_player_search_item_get_sel_btn->Name = L"c_player_search_item_get_sel_btn";
		this->c_player_search_item_get_sel_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_item_get_sel_btn->TabIndex = 0;
		this->c_player_search_item_get_sel_btn->Text = L"get sel";
		this->c_player_search_item_get_sel_btn->UseVisualStyleBackColor = true;
		this->c_player_search_item_get_sel_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_item_get_sel_btn_Click);
		// 
		// c_player_search_item_filter_pal
		// 
		this->c_player_search_item_filter_pal->Controls->Add(this->c_player_search_item_search_btn);
		this->c_player_search_item_filter_pal->Controls->Add(this->c_player_search_item_gbo);
		this->c_player_search_item_filter_pal->Dock = System::Windows::Forms::DockStyle::Top;
		this->c_player_search_item_filter_pal->Location = System::Drawing::Point(0, 0);
		this->c_player_search_item_filter_pal->Name = L"c_player_search_item_filter_pal";
		this->c_player_search_item_filter_pal->Size = System::Drawing::Size(165, 112);
		this->c_player_search_item_filter_pal->TabIndex = 1;
		// 
		// c_player_search_item_search_btn
		// 
		this->c_player_search_item_search_btn->Location = System::Drawing::Point(87, 83);
		this->c_player_search_item_search_btn->Name = L"c_player_search_item_search_btn";
		this->c_player_search_item_search_btn->Size = System::Drawing::Size(75, 23);
		this->c_player_search_item_search_btn->TabIndex = 6;
		this->c_player_search_item_search_btn->Text = L"search";
		this->c_player_search_item_search_btn->UseVisualStyleBackColor = true;
		this->c_player_search_item_search_btn->Click += gcnew System::EventHandler(this, &MainForm::c_player_search_item_search_btn_Click);
		// 
		// c_player_search_item_gbo
		// 
		this->c_player_search_item_gbo->Controls->Add(this->c_player_search_item_id_edt);
		this->c_player_search_item_gbo->Controls->Add(this->c_player_search_item_name_edt);
		this->c_player_search_item_gbo->Controls->Add(this->c_player_search_item_id_cbx);
		this->c_player_search_item_gbo->Controls->Add(this->c_player_search_item_name_cbx);
		this->c_player_search_item_gbo->Dock = System::Windows::Forms::DockStyle::Top;
		this->c_player_search_item_gbo->Location = System::Drawing::Point(0, 0);
		this->c_player_search_item_gbo->Name = L"c_player_search_item_gbo";
		this->c_player_search_item_gbo->Size = System::Drawing::Size(165, 77);
		this->c_player_search_item_gbo->TabIndex = 0;
		this->c_player_search_item_gbo->TabStop = false;
		this->c_player_search_item_gbo->Text = L"search";
		// 
		// c_player_search_item_id_edt
		// 
		this->c_player_search_item_id_edt->Enabled = false;
		this->c_player_search_item_id_edt->Location = System::Drawing::Point(76, 46);
		this->c_player_search_item_id_edt->Name = L"c_player_search_item_id_edt";
		this->c_player_search_item_id_edt->Size = System::Drawing::Size(82, 21);
		this->c_player_search_item_id_edt->TabIndex = 8;
		// 
		// c_player_search_item_name_edt
		// 
		this->c_player_search_item_name_edt->Enabled = false;
		this->c_player_search_item_name_edt->Location = System::Drawing::Point(76, 17);
		this->c_player_search_item_name_edt->Name = L"c_player_search_item_name_edt";
		this->c_player_search_item_name_edt->Size = System::Drawing::Size(82, 21);
		this->c_player_search_item_name_edt->TabIndex = 7;
		// 
		// c_player_search_item_id_cbx
		// 
		this->c_player_search_item_id_cbx->AutoSize = true;
		this->c_player_search_item_id_cbx->Location = System::Drawing::Point(9, 49);
		this->c_player_search_item_id_cbx->Name = L"c_player_search_item_id_cbx";
		this->c_player_search_item_id_cbx->Size = System::Drawing::Size(36, 16);
		this->c_player_search_item_id_cbx->TabIndex = 2;
		this->c_player_search_item_id_cbx->Text = L"id";
		this->c_player_search_item_id_cbx->UseVisualStyleBackColor = true;
		this->c_player_search_item_id_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::c_player_search_item_id_cbx_CheckedChanged);
		// 
		// c_player_search_item_name_cbx
		// 
		this->c_player_search_item_name_cbx->AutoSize = true;
		this->c_player_search_item_name_cbx->Location = System::Drawing::Point(8, 21);
		this->c_player_search_item_name_cbx->Name = L"c_player_search_item_name_cbx";
		this->c_player_search_item_name_cbx->Size = System::Drawing::Size(48, 16);
		this->c_player_search_item_name_cbx->TabIndex = 1;
		this->c_player_search_item_name_cbx->Text = L"name";
		this->c_player_search_item_name_cbx->UseVisualStyleBackColor = true;
		this->c_player_search_item_name_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::c_player_search_item_name_cbx_CheckedChanged);
		// 
		// c_msg_pag
		// 
		this->c_msg_pag->Controls->Add(this->c_msg_pal);
		this->c_msg_pag->Location = System::Drawing::Point(4, 21);
		this->c_msg_pag->Name = L"c_msg_pag";
		this->c_msg_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_pag->Size = System::Drawing::Size(650, 477);
		this->c_msg_pag->TabIndex = 1;
		this->c_msg_pag->Text = L"msg";
		this->c_msg_pag->UseVisualStyleBackColor = true;
		// 
		// c_msg_pal
		// 
		this->c_msg_pal->Controls->Add(this->c_msg_main_pal);
		this->c_msg_pal->Controls->Add(this->c_msg_center_spl);
		this->c_msg_pal->Controls->Add(this->c_msg_server_right_pal);
		this->c_msg_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_pal->Location = System::Drawing::Point(3, 3);
		this->c_msg_pal->Name = L"c_msg_pal";
		this->c_msg_pal->Size = System::Drawing::Size(644, 471);
		this->c_msg_pal->TabIndex = 0;
		// 
		// c_msg_main_pal
		// 
		this->c_msg_main_pal->Controls->Add(this->c_msg_main_tab);
		this->c_msg_main_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_main_pal->Location = System::Drawing::Point(0, 0);
		this->c_msg_main_pal->Name = L"c_msg_main_pal";
		this->c_msg_main_pal->Size = System::Drawing::Size(470, 471);
		this->c_msg_main_pal->TabIndex = 2;
		// 
		// c_msg_main_tab
		// 
		this->c_msg_main_tab->Controls->Add(this->c_msg_post_pag);
		this->c_msg_main_tab->Controls->Add(this->c_msg_sensword_pag);
		this->c_msg_main_tab->Controls->Add(this->c_msg_reply_pag);
		this->c_msg_main_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_main_tab->Location = System::Drawing::Point(0, 0);
		this->c_msg_main_tab->Name = L"c_msg_main_tab";
		this->c_msg_main_tab->SelectedIndex = 0;
		this->c_msg_main_tab->Size = System::Drawing::Size(470, 471);
		this->c_msg_main_tab->TabIndex = 0;
		// 
		// c_msg_post_pag
		// 
		this->c_msg_post_pag->Location = System::Drawing::Point(4, 21);
		this->c_msg_post_pag->Name = L"c_msg_post_pag";
		this->c_msg_post_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_post_pag->Size = System::Drawing::Size(462, 446);
		this->c_msg_post_pag->TabIndex = 0;
		this->c_msg_post_pag->Text = L"post";
		this->c_msg_post_pag->UseVisualStyleBackColor = true;
		// 
		// c_msg_sensword_pag
		// 
		this->c_msg_sensword_pag->Controls->Add(this->c_msg_sensword_pal);
		this->c_msg_sensword_pag->Location = System::Drawing::Point(4, 21);
		this->c_msg_sensword_pag->Name = L"c_msg_sensword_pag";
		this->c_msg_sensword_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_sensword_pag->Size = System::Drawing::Size(462, 446);
		this->c_msg_sensword_pag->TabIndex = 1;
		this->c_msg_sensword_pag->Text = L"sens word";
		this->c_msg_sensword_pag->UseVisualStyleBackColor = true;
		// 
		// c_msg_sensword_pal
		// 
		this->c_msg_sensword_pal->Controls->Add(this->d_ms_pal);
		this->c_msg_sensword_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_sensword_pal->Location = System::Drawing::Point(3, 3);
		this->c_msg_sensword_pal->Name = L"c_msg_sensword_pal";
		this->c_msg_sensword_pal->Size = System::Drawing::Size(456, 440);
		this->c_msg_sensword_pal->TabIndex = 0;
		// 
		// d_ms_pal
		// 
		this->d_ms_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_ms_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_ms_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_ms_pal->Controls->Add(this->d_ms_server_gbo);
		this->d_ms_pal->Controls->Add(this->d_ms_sensword_gbo);
		this->d_ms_pal->Location = System::Drawing::Point(3, 47);
		this->d_ms_pal->Name = L"d_ms_pal";
		this->d_ms_pal->Size = System::Drawing::Size(450, 347);
		this->d_ms_pal->TabIndex = 4;
		// 
		// d_ms_server_gbo
		// 
		this->d_ms_server_gbo->Controls->Add(this->d_ms_server_list);
		this->d_ms_server_gbo->Location = System::Drawing::Point(21, 11);
		this->d_ms_server_gbo->Name = L"d_ms_server_gbo";
		this->d_ms_server_gbo->Size = System::Drawing::Size(410, 111);
		this->d_ms_server_gbo->TabIndex = 9;
		this->d_ms_server_gbo->TabStop = false;
		this->d_ms_server_gbo->Text = L"server";
		// 
		// d_ms_server_list
		// 
		this->d_ms_server_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dms_column_region_name, 
			this->dms_column_region_id});
		this->d_ms_server_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ms_server_list->FullRowSelect = true;
		this->d_ms_server_list->GridLines = true;
		this->d_ms_server_list->HideSelection = false;
		this->d_ms_server_list->Location = System::Drawing::Point(3, 17);
		this->d_ms_server_list->Name = L"d_ms_server_list";
		this->d_ms_server_list->Size = System::Drawing::Size(404, 91);
		this->d_ms_server_list->TabIndex = 0;
		this->d_ms_server_list->UseCompatibleStateImageBehavior = false;
		this->d_ms_server_list->View = System::Windows::Forms::View::Details;
		this->d_ms_server_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_ms_server_list_MouseDoubleClick);
		// 
		// dms_column_region_name
		// 
		this->dms_column_region_name->Text = L"region_name";
		this->dms_column_region_name->Width = 150;
		// 
		// dms_column_region_id
		// 
		this->dms_column_region_id->Text = L"region_id";
		this->dms_column_region_id->Width = 100;
		// 
		// d_ms_sensword_gbo
		// 
		this->d_ms_sensword_gbo->Controls->Add(this->d_ms_sensword_list);
		this->d_ms_sensword_gbo->Location = System::Drawing::Point(23, 128);
		this->d_ms_sensword_gbo->Name = L"d_ms_sensword_gbo";
		this->d_ms_sensword_gbo->Size = System::Drawing::Size(408, 204);
		this->d_ms_sensword_gbo->TabIndex = 6;
		this->d_ms_sensword_gbo->TabStop = false;
		this->d_ms_sensword_gbo->Text = L"senstive word";
		// 
		// d_ms_sensword_list
		// 
		this->d_ms_sensword_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->ms_sens_column_name, 
			this->ms_sens_column_content, this->ms_sens_column_type, this->ms_sens_column_region_id, this->ms_sens_column_uin, this->ms_sens_column_id});
		this->d_ms_sensword_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ms_sensword_list->FullRowSelect = true;
		this->d_ms_sensword_list->GridLines = true;
		this->d_ms_sensword_list->HideSelection = false;
		this->d_ms_sensword_list->Location = System::Drawing::Point(3, 17);
		this->d_ms_sensword_list->Name = L"d_ms_sensword_list";
		this->d_ms_sensword_list->Size = System::Drawing::Size(402, 184);
		this->d_ms_sensword_list->TabIndex = 1;
		this->d_ms_sensword_list->UseCompatibleStateImageBehavior = false;
		this->d_ms_sensword_list->View = System::Windows::Forms::View::Details;
		// 
		// ms_sens_column_name
		// 
		this->ms_sens_column_name->Text = L"name";
		// 
		// ms_sens_column_content
		// 
		this->ms_sens_column_content->Text = L"content";
		this->ms_sens_column_content->Width = 200;
		// 
		// ms_sens_column_type
		// 
		this->ms_sens_column_type->Text = L"type";
		// 
		// ms_sens_column_region_id
		// 
		this->ms_sens_column_region_id->Text = L"region_id";
		// 
		// ms_sens_column_uin
		// 
		this->ms_sens_column_uin->Text = L"uin";
		this->ms_sens_column_uin->Width = 150;
		// 
		// ms_sens_column_id
		// 
		this->ms_sens_column_id->Text = L"id";
		this->ms_sens_column_id->Width = 100;
		// 
		// c_msg_reply_pag
		// 
		this->c_msg_reply_pag->Controls->Add(this->c_msg_reply_pal);
		this->c_msg_reply_pag->Location = System::Drawing::Point(4, 21);
		this->c_msg_reply_pag->Name = L"c_msg_reply_pag";
		this->c_msg_reply_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_reply_pag->Size = System::Drawing::Size(462, 446);
		this->c_msg_reply_pag->TabIndex = 2;
		this->c_msg_reply_pag->Text = L"reply";
		this->c_msg_reply_pag->UseVisualStyleBackColor = true;
		// 
		// c_msg_reply_pal
		// 
		this->c_msg_reply_pal->Controls->Add(this->d_mr_pal);
		this->c_msg_reply_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_reply_pal->Location = System::Drawing::Point(3, 3);
		this->c_msg_reply_pal->Name = L"c_msg_reply_pal";
		this->c_msg_reply_pal->Size = System::Drawing::Size(456, 440);
		this->c_msg_reply_pal->TabIndex = 0;
		// 
		// d_mr_pal
		// 
		this->d_mr_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_mr_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_mr_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_mr_pal->Controls->Add(this->d_mr_reply_gbo);
		this->d_mr_pal->Controls->Add(this->d_mr_server_gbo);
		this->d_mr_pal->Controls->Add(this->d_mr_question_gbo);
		this->d_mr_pal->Location = System::Drawing::Point(-7, 0);
		this->d_mr_pal->Name = L"d_mr_pal";
		this->d_mr_pal->Size = System::Drawing::Size(477, 437);
		this->d_mr_pal->TabIndex = 4;
		// 
		// d_mr_reply_gbo
		// 
		this->d_mr_reply_gbo->Controls->Add(this->d_mr_player_info_gbo);
		this->d_mr_reply_gbo->Controls->Add(this->d_mr_common_reply_gbo);
		this->d_mr_reply_gbo->Controls->Add(this->d_mr_commit_btn);
		this->d_mr_reply_gbo->Controls->Add(this->d_mr_one_reply_gbo);
		this->d_mr_reply_gbo->Controls->Add(this->d_mr_one_question_gbo);
		this->d_mr_reply_gbo->Location = System::Drawing::Point(140, 11);
		this->d_mr_reply_gbo->Name = L"d_mr_reply_gbo";
		this->d_mr_reply_gbo->Size = System::Drawing::Size(320, 411);
		this->d_mr_reply_gbo->TabIndex = 10;
		this->d_mr_reply_gbo->TabStop = false;
		this->d_mr_reply_gbo->Text = L"reply";
		// 
		// d_mr_player_info_gbo
		// 
		this->d_mr_player_info_gbo->Controls->Add(this->d_mr_player_cbo);
		this->d_mr_player_info_gbo->Controls->Add(this->d_mr_server_cbo);
		this->d_mr_player_info_gbo->Controls->Add(this->d_mr_charactor_lbl);
		this->d_mr_player_info_gbo->Controls->Add(this->d_mr_server_lbl);
		this->d_mr_player_info_gbo->Location = System::Drawing::Point(14, 17);
		this->d_mr_player_info_gbo->Name = L"d_mr_player_info_gbo";
		this->d_mr_player_info_gbo->Size = System::Drawing::Size(291, 72);
		this->d_mr_player_info_gbo->TabIndex = 15;
		this->d_mr_player_info_gbo->TabStop = false;
		this->d_mr_player_info_gbo->Text = L"player info";
		// 
		// d_mr_player_cbo
		// 
		this->d_mr_player_cbo->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_mr_player_cbo->FormattingEnabled = true;
		this->d_mr_player_cbo->Location = System::Drawing::Point(145, 44);
		this->d_mr_player_cbo->Name = L"d_mr_player_cbo";
		this->d_mr_player_cbo->Size = System::Drawing::Size(106, 20);
		this->d_mr_player_cbo->TabIndex = 18;
		// 
		// d_mr_server_cbo
		// 
		this->d_mr_server_cbo->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->d_mr_server_cbo->FormattingEnabled = true;
		this->d_mr_server_cbo->Location = System::Drawing::Point(145, 17);
		this->d_mr_server_cbo->Name = L"d_mr_server_cbo";
		this->d_mr_server_cbo->Size = System::Drawing::Size(106, 20);
		this->d_mr_server_cbo->TabIndex = 17;
		// 
		// d_mr_charactor_lbl
		// 
		this->d_mr_charactor_lbl->AutoSize = true;
		this->d_mr_charactor_lbl->Location = System::Drawing::Point(40, 47);
		this->d_mr_charactor_lbl->Name = L"d_mr_charactor_lbl";
		this->d_mr_charactor_lbl->Size = System::Drawing::Size(65, 12);
		this->d_mr_charactor_lbl->TabIndex = 16;
		this->d_mr_charactor_lbl->Text = L"charactor:";
		// 
		// d_mr_server_lbl
		// 
		this->d_mr_server_lbl->AutoSize = true;
		this->d_mr_server_lbl->Location = System::Drawing::Point(40, 21);
		this->d_mr_server_lbl->Name = L"d_mr_server_lbl";
		this->d_mr_server_lbl->Size = System::Drawing::Size(47, 12);
		this->d_mr_server_lbl->TabIndex = 15;
		this->d_mr_server_lbl->Text = L"server:";
		// 
		// d_mr_common_reply_gbo
		// 
		this->d_mr_common_reply_gbo->Controls->Add(this->d_mr_common_reply_list);
		this->d_mr_common_reply_gbo->Location = System::Drawing::Point(174, 178);
		this->d_mr_common_reply_gbo->Name = L"d_mr_common_reply_gbo";
		this->d_mr_common_reply_gbo->Size = System::Drawing::Size(131, 198);
		this->d_mr_common_reply_gbo->TabIndex = 11;
		this->d_mr_common_reply_gbo->TabStop = false;
		this->d_mr_common_reply_gbo->Text = L"common";
		// 
		// d_mr_common_reply_list
		// 
		this->d_mr_common_reply_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mr_common_reply_list->FormattingEnabled = true;
		this->d_mr_common_reply_list->ItemHeight = 12;
		this->d_mr_common_reply_list->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"请查询官网！", L"休息中！"});
		this->d_mr_common_reply_list->Location = System::Drawing::Point(3, 17);
		this->d_mr_common_reply_list->Name = L"d_mr_common_reply_list";
		this->d_mr_common_reply_list->Size = System::Drawing::Size(125, 172);
		this->d_mr_common_reply_list->TabIndex = 0;
		this->d_mr_common_reply_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_mr_common_reply_list_MouseDoubleClick);
		// 
		// d_mr_commit_btn
		// 
		this->d_mr_commit_btn->Location = System::Drawing::Point(228, 382);
		this->d_mr_commit_btn->Name = L"d_mr_commit_btn";
		this->d_mr_commit_btn->Size = System::Drawing::Size(75, 23);
		this->d_mr_commit_btn->TabIndex = 10;
		this->d_mr_commit_btn->Text = L"commint";
		this->d_mr_commit_btn->UseVisualStyleBackColor = true;
		this->d_mr_commit_btn->Click += gcnew System::EventHandler(this, &MainForm::d_mr_commit_btn_Click);
		// 
		// d_mr_one_reply_gbo
		// 
		this->d_mr_one_reply_gbo->Controls->Add(this->d_mr_one_reply_edt);
		this->d_mr_one_reply_gbo->Location = System::Drawing::Point(14, 178);
		this->d_mr_one_reply_gbo->Name = L"d_mr_one_reply_gbo";
		this->d_mr_one_reply_gbo->Size = System::Drawing::Size(154, 198);
		this->d_mr_one_reply_gbo->TabIndex = 9;
		this->d_mr_one_reply_gbo->TabStop = false;
		this->d_mr_one_reply_gbo->Text = L"reply";
		// 
		// d_mr_one_reply_edt
		// 
		this->d_mr_one_reply_edt->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mr_one_reply_edt->Location = System::Drawing::Point(3, 17);
		this->d_mr_one_reply_edt->Name = L"d_mr_one_reply_edt";
		this->d_mr_one_reply_edt->Size = System::Drawing::Size(148, 178);
		this->d_mr_one_reply_edt->TabIndex = 0;
		this->d_mr_one_reply_edt->Text = L"";
		// 
		// d_mr_one_question_gbo
		// 
		this->d_mr_one_question_gbo->Controls->Add(this->d_mr_one_question_txt);
		this->d_mr_one_question_gbo->Location = System::Drawing::Point(14, 96);
		this->d_mr_one_question_gbo->Name = L"d_mr_one_question_gbo";
		this->d_mr_one_question_gbo->Size = System::Drawing::Size(294, 76);
		this->d_mr_one_question_gbo->TabIndex = 8;
		this->d_mr_one_question_gbo->TabStop = false;
		this->d_mr_one_question_gbo->Text = L"question";
		// 
		// d_mr_one_question_txt
		// 
		this->d_mr_one_question_txt->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_mr_one_question_txt->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_mr_one_question_txt->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mr_one_question_txt->Location = System::Drawing::Point(3, 17);
		this->d_mr_one_question_txt->Name = L"d_mr_one_question_txt";
		this->d_mr_one_question_txt->Size = System::Drawing::Size(288, 56);
		this->d_mr_one_question_txt->TabIndex = 1;
		this->d_mr_one_question_txt->Text = L"";
		// 
		// d_mr_server_gbo
		// 
		this->d_mr_server_gbo->Controls->Add(this->d_mr_server_list);
		this->d_mr_server_gbo->Location = System::Drawing::Point(10, 11);
		this->d_mr_server_gbo->Name = L"d_mr_server_gbo";
		this->d_mr_server_gbo->Size = System::Drawing::Size(124, 111);
		this->d_mr_server_gbo->TabIndex = 9;
		this->d_mr_server_gbo->TabStop = false;
		this->d_mr_server_gbo->Text = L"server";
		// 
		// d_mr_server_list
		// 
		this->d_mr_server_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dmr_server_column_region_name, 
			this->dmr_server_column_region_id});
		this->d_mr_server_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mr_server_list->FullRowSelect = true;
		this->d_mr_server_list->GridLines = true;
		this->d_mr_server_list->HideSelection = false;
		this->d_mr_server_list->Location = System::Drawing::Point(3, 17);
		this->d_mr_server_list->Name = L"d_mr_server_list";
		this->d_mr_server_list->Size = System::Drawing::Size(118, 91);
		this->d_mr_server_list->TabIndex = 0;
		this->d_mr_server_list->UseCompatibleStateImageBehavior = false;
		this->d_mr_server_list->View = System::Windows::Forms::View::Details;
		this->d_mr_server_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_mr_server_list_MouseDoubleClick);
		// 
		// dmr_server_column_region_name
		// 
		this->dmr_server_column_region_name->Text = L"region_name";
		this->dmr_server_column_region_name->Width = 80;
		// 
		// dmr_server_column_region_id
		// 
		this->dmr_server_column_region_id->Text = L"region_id";
		this->dmr_server_column_region_id->Width = 80;
		// 
		// d_mr_question_gbo
		// 
		this->d_mr_question_gbo->Controls->Add(this->d_mr_question_list);
		this->d_mr_question_gbo->Location = System::Drawing::Point(12, 128);
		this->d_mr_question_gbo->Name = L"d_mr_question_gbo";
		this->d_mr_question_gbo->Size = System::Drawing::Size(122, 294);
		this->d_mr_question_gbo->TabIndex = 6;
		this->d_mr_question_gbo->TabStop = false;
		this->d_mr_question_gbo->Text = L"question";
		// 
		// d_mr_question_list
		// 
		this->d_mr_question_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->mr_column_player_name, 
			this->mr_column_content, this->mr_column_gm_name, this->mr_column_region_id, this->mr_column_player_uin, this->mr_column_player_id});
		this->d_mr_question_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mr_question_list->FullRowSelect = true;
		this->d_mr_question_list->GridLines = true;
		this->d_mr_question_list->HideSelection = false;
		this->d_mr_question_list->Location = System::Drawing::Point(3, 17);
		this->d_mr_question_list->Name = L"d_mr_question_list";
		this->d_mr_question_list->Size = System::Drawing::Size(116, 274);
		this->d_mr_question_list->TabIndex = 1;
		this->d_mr_question_list->UseCompatibleStateImageBehavior = false;
		this->d_mr_question_list->View = System::Windows::Forms::View::Details;
		this->d_mr_question_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_mr_sensword_list_MouseDoubleClick);
		// 
		// mr_column_player_name
		// 
		this->mr_column_player_name->Text = L"playername";
		this->mr_column_player_name->Width = 65;
		// 
		// mr_column_content
		// 
		this->mr_column_content->Text = L"content";
		this->mr_column_content->Width = 200;
		// 
		// mr_column_gm_name
		// 
		this->mr_column_gm_name->Text = L"gm_name";
		// 
		// mr_column_region_id
		// 
		this->mr_column_region_id->Text = L"region_id";
		// 
		// mr_column_player_uin
		// 
		this->mr_column_player_uin->Text = L"player_uin";
		this->mr_column_player_uin->Width = 150;
		// 
		// mr_column_player_id
		// 
		this->mr_column_player_id->Text = L"player_id";
		this->mr_column_player_id->Width = 100;
		// 
		// c_msg_center_spl
		// 
		this->c_msg_center_spl->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->c_msg_center_spl->Dock = System::Windows::Forms::DockStyle::Right;
		this->c_msg_center_spl->Location = System::Drawing::Point(470, 0);
		this->c_msg_center_spl->Name = L"c_msg_center_spl";
		this->c_msg_center_spl->Size = System::Drawing::Size(2, 471);
		this->c_msg_center_spl->TabIndex = 1;
		this->c_msg_center_spl->TabStop = false;
		// 
		// c_msg_server_right_pal
		// 
		this->c_msg_server_right_pal->Controls->Add(this->c_msg_server_search_tab);
		this->c_msg_server_right_pal->Dock = System::Windows::Forms::DockStyle::Right;
		this->c_msg_server_right_pal->Location = System::Drawing::Point(472, 0);
		this->c_msg_server_right_pal->Name = L"c_msg_server_right_pal";
		this->c_msg_server_right_pal->Size = System::Drawing::Size(172, 471);
		this->c_msg_server_right_pal->TabIndex = 0;
		// 
		// c_msg_server_search_tab
		// 
		this->c_msg_server_search_tab->Controls->Add(this->c_msg_server_right_pag);
		this->c_msg_server_search_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_server_search_tab->Location = System::Drawing::Point(0, 0);
		this->c_msg_server_search_tab->Name = L"c_msg_server_search_tab";
		this->c_msg_server_search_tab->SelectedIndex = 0;
		this->c_msg_server_search_tab->Size = System::Drawing::Size(172, 471);
		this->c_msg_server_search_tab->TabIndex = 2;
		// 
		// c_msg_server_right_pag
		// 
		this->c_msg_server_right_pag->Controls->Add(this->c_msg_server_search_op_pal);
		this->c_msg_server_right_pag->Controls->Add(this->c_msg_server_search_pal);
		this->c_msg_server_right_pag->Location = System::Drawing::Point(4, 21);
		this->c_msg_server_right_pag->Name = L"c_msg_server_right_pag";
		this->c_msg_server_right_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_server_right_pag->Size = System::Drawing::Size(164, 446);
		this->c_msg_server_right_pag->TabIndex = 0;
		this->c_msg_server_right_pag->Text = L"server";
		this->c_msg_server_right_pag->UseVisualStyleBackColor = true;
		// 
		// c_msg_server_search_op_pal
		// 
		this->c_msg_server_search_op_pal->Controls->Add(this->c_msg_server_getall_btn);
		this->c_msg_server_search_op_pal->Controls->Add(this->c_msg_server_getsel_btn);
		this->c_msg_server_search_op_pal->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->c_msg_server_search_op_pal->Location = System::Drawing::Point(3, 411);
		this->c_msg_server_search_op_pal->Name = L"c_msg_server_search_op_pal";
		this->c_msg_server_search_op_pal->Size = System::Drawing::Size(158, 32);
		this->c_msg_server_search_op_pal->TabIndex = 3;
		// 
		// c_msg_server_getall_btn
		// 
		this->c_msg_server_getall_btn->Location = System::Drawing::Point(82, 5);
		this->c_msg_server_getall_btn->Name = L"c_msg_server_getall_btn";
		this->c_msg_server_getall_btn->Size = System::Drawing::Size(75, 23);
		this->c_msg_server_getall_btn->TabIndex = 3;
		this->c_msg_server_getall_btn->Text = L"get all";
		this->c_msg_server_getall_btn->UseVisualStyleBackColor = true;
		this->c_msg_server_getall_btn->Click += gcnew System::EventHandler(this, &MainForm::c_msg_server_getall_btn_Click);
		// 
		// c_msg_server_getsel_btn
		// 
		this->c_msg_server_getsel_btn->Location = System::Drawing::Point(5, 5);
		this->c_msg_server_getsel_btn->Name = L"c_msg_server_getsel_btn";
		this->c_msg_server_getsel_btn->Size = System::Drawing::Size(75, 23);
		this->c_msg_server_getsel_btn->TabIndex = 2;
		this->c_msg_server_getsel_btn->Text = L"get sel";
		this->c_msg_server_getsel_btn->UseVisualStyleBackColor = true;
		this->c_msg_server_getsel_btn->Click += gcnew System::EventHandler(this, &MainForm::c_msg_server_getsel_btn_Click);
		// 
		// c_msg_server_search_pal
		// 
		this->c_msg_server_search_pal->Controls->Add(this->c_msg_server_search_list);
		this->c_msg_server_search_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_server_search_pal->Location = System::Drawing::Point(3, 3);
		this->c_msg_server_search_pal->Name = L"c_msg_server_search_pal";
		this->c_msg_server_search_pal->Size = System::Drawing::Size(158, 440);
		this->c_msg_server_search_pal->TabIndex = 2;
		// 
		// c_msg_server_search_list
		// 
		this->c_msg_server_search_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->cmsg_column_region_name, 
			this->cmsg_column_region_id});
		this->c_msg_server_search_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_server_search_list->FullRowSelect = true;
		this->c_msg_server_search_list->GridLines = true;
		this->c_msg_server_search_list->HideSelection = false;
		this->c_msg_server_search_list->Location = System::Drawing::Point(0, 0);
		this->c_msg_server_search_list->Name = L"c_msg_server_search_list";
		this->c_msg_server_search_list->Size = System::Drawing::Size(158, 440);
		this->c_msg_server_search_list->TabIndex = 0;
		this->c_msg_server_search_list->UseCompatibleStateImageBehavior = false;
		this->c_msg_server_search_list->View = System::Windows::Forms::View::Details;
		this->c_msg_server_search_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::c_msg_server_search_list_MouseDoubleClick);
		// 
		// cmsg_column_region_name
		// 
		this->cmsg_column_region_name->Text = L"region_name";
		this->cmsg_column_region_name->Width = 100;
		// 
		// cmsg_column_region_id
		// 
		this->cmsg_column_region_id->Text = L"region_id";
		// 
		// c_server_pag
		// 
		this->c_server_pag->Controls->Add(this->c_server_pal);
		this->c_server_pag->Location = System::Drawing::Point(4, 21);
		this->c_server_pag->Name = L"c_server_pag";
		this->c_server_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_server_pag->Size = System::Drawing::Size(650, 477);
		this->c_server_pag->TabIndex = 2;
		this->c_server_pag->Text = L"server";
		this->c_server_pag->UseVisualStyleBackColor = true;
		// 
		// c_server_pal
		// 
		this->c_server_pal->Controls->Add(this->c_ss_server_pal);
		this->c_server_pal->Controls->Add(this->c_ss_server_list);
		this->c_server_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_server_pal->Location = System::Drawing::Point(3, 3);
		this->c_server_pal->Name = L"c_server_pal";
		this->c_server_pal->Size = System::Drawing::Size(644, 471);
		this->c_server_pal->TabIndex = 0;
		// 
		// c_ss_server_pal
		// 
		this->c_ss_server_pal->Controls->Add(this->c_ss_server_refresh_btn);
		this->c_ss_server_pal->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->c_ss_server_pal->Location = System::Drawing::Point(0, 438);
		this->c_ss_server_pal->Name = L"c_ss_server_pal";
		this->c_ss_server_pal->Size = System::Drawing::Size(644, 33);
		this->c_ss_server_pal->TabIndex = 2;
		// 
		// c_ss_server_refresh_btn
		// 
		this->c_ss_server_refresh_btn->Location = System::Drawing::Point(552, 6);
		this->c_ss_server_refresh_btn->Name = L"c_ss_server_refresh_btn";
		this->c_ss_server_refresh_btn->Size = System::Drawing::Size(75, 23);
		this->c_ss_server_refresh_btn->TabIndex = 0;
		this->c_ss_server_refresh_btn->Text = L"refresh";
		this->c_ss_server_refresh_btn->UseVisualStyleBackColor = true;
		this->c_ss_server_refresh_btn->Click += gcnew System::EventHandler(this, &MainForm::c_ss_server_refresh_btn_Click);
		// 
		// c_ss_server_list
		// 
		this->c_ss_server_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->ss_column_name, 
			this->ss_column_online_count, this->ss_column_region_id, this->ss_column_id});
		this->c_ss_server_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_ss_server_list->FullRowSelect = true;
		this->c_ss_server_list->GridLines = true;
		this->c_ss_server_list->HideSelection = false;
		this->c_ss_server_list->Location = System::Drawing::Point(0, 0);
		this->c_ss_server_list->Name = L"c_ss_server_list";
		this->c_ss_server_list->Size = System::Drawing::Size(644, 471);
		this->c_ss_server_list->TabIndex = 1;
		this->c_ss_server_list->UseCompatibleStateImageBehavior = false;
		this->c_ss_server_list->View = System::Windows::Forms::View::Details;
		// 
		// ss_column_name
		// 
		this->ss_column_name->Text = L"name";
		this->ss_column_name->Width = 130;
		// 
		// ss_column_online_count
		// 
		this->ss_column_online_count->Text = L"online count";
		this->ss_column_online_count->Width = 100;
		// 
		// ss_column_region_id
		// 
		this->ss_column_region_id->Text = L"region_id";
		this->ss_column_region_id->Width = 100;
		// 
		// ss_column_id
		// 
		this->ss_column_id->Text = L"id";
		this->ss_column_id->Width = 100;
		// 
		// c_account_pag
		// 
		this->c_account_pag->Controls->Add(this->c_account_pal);
		this->c_account_pag->Location = System::Drawing::Point(4, 21);
		this->c_account_pag->Name = L"c_account_pag";
		this->c_account_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_account_pag->Size = System::Drawing::Size(650, 477);
		this->c_account_pag->TabIndex = 3;
		this->c_account_pag->Text = L"account";
		this->c_account_pag->UseVisualStyleBackColor = true;
		// 
		// c_account_pal
		// 
		this->c_account_pal->Controls->Add(this->c_account_tab);
		this->c_account_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_account_pal->Location = System::Drawing::Point(3, 3);
		this->c_account_pal->Name = L"c_account_pal";
		this->c_account_pal->Size = System::Drawing::Size(644, 471);
		this->c_account_pal->TabIndex = 0;
		// 
		// c_account_tab
		// 
		this->c_account_tab->Controls->Add(this->c_account_manager_pag);
		this->c_account_tab->Controls->Add(this->c_account_record_pag);
		this->c_account_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_account_tab->Location = System::Drawing::Point(0, 0);
		this->c_account_tab->Name = L"c_account_tab";
		this->c_account_tab->SelectedIndex = 0;
		this->c_account_tab->Size = System::Drawing::Size(644, 471);
		this->c_account_tab->TabIndex = 0;
		// 
		// c_account_manager_pag
		// 
		this->c_account_manager_pag->Controls->Add(this->c_account_manager_pal);
		this->c_account_manager_pag->Location = System::Drawing::Point(4, 21);
		this->c_account_manager_pag->Name = L"c_account_manager_pag";
		this->c_account_manager_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_account_manager_pag->Size = System::Drawing::Size(636, 446);
		this->c_account_manager_pag->TabIndex = 0;
		this->c_account_manager_pag->Text = L"mamanger";
		this->c_account_manager_pag->UseVisualStyleBackColor = true;
		// 
		// c_account_manager_pal
		// 
		this->c_account_manager_pal->Controls->Add(this->d_am_pal);
		this->c_account_manager_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_account_manager_pal->Location = System::Drawing::Point(3, 3);
		this->c_account_manager_pal->Name = L"c_account_manager_pal";
		this->c_account_manager_pal->Size = System::Drawing::Size(630, 440);
		this->c_account_manager_pal->TabIndex = 0;
		// 
		// d_am_pal
		// 
		this->d_am_pal->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->d_am_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_am_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_am_pal->Controls->Add(this->d_am_tab);
		this->d_am_pal->Location = System::Drawing::Point(80, 3);
		this->d_am_pal->Name = L"d_am_pal";
		this->d_am_pal->Size = System::Drawing::Size(470, 434);
		this->d_am_pal->TabIndex = 2;
		// 
		// d_am_tab
		// 
		this->d_am_tab->Controls->Add(this->d_am_create_pag);
		this->d_am_tab->Controls->Add(this->d_am_record_pag);
		this->d_am_tab->Location = System::Drawing::Point(9, 9);
		this->d_am_tab->Name = L"d_am_tab";
		this->d_am_tab->SelectedIndex = 0;
		this->d_am_tab->Size = System::Drawing::Size(453, 414);
		this->d_am_tab->TabIndex = 0;
		// 
		// d_am_create_pag
		// 
		this->d_am_create_pag->Controls->Add(this->d_am_create_pal);
		this->d_am_create_pag->Location = System::Drawing::Point(4, 21);
		this->d_am_create_pag->Name = L"d_am_create_pag";
		this->d_am_create_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_am_create_pag->Size = System::Drawing::Size(445, 389);
		this->d_am_create_pag->TabIndex = 0;
		this->d_am_create_pag->Text = L"create";
		this->d_am_create_pag->UseVisualStyleBackColor = true;
		// 
		// d_am_create_pal
		// 
		this->d_am_create_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_am_create_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_am_create_pal->Controls->Add(this->d_am_user_gbo);
		this->d_am_create_pal->Controls->Add(this->d_am_commit_gbo);
		this->d_am_create_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_am_create_pal->Location = System::Drawing::Point(3, 3);
		this->d_am_create_pal->Name = L"d_am_create_pal";
		this->d_am_create_pal->Size = System::Drawing::Size(439, 383);
		this->d_am_create_pal->TabIndex = 2;
		// 
		// d_am_user_gbo
		// 
		this->d_am_user_gbo->Controls->Add(this->d_am_password_edt);
		this->d_am_user_gbo->Controls->Add(this->d_am_password_lbl);
		this->d_am_user_gbo->Controls->Add(this->d_am_username_edt);
		this->d_am_user_gbo->Controls->Add(this->d_am_username_lbl);
		this->d_am_user_gbo->Controls->Add(this->d_am_password2_edt);
		this->d_am_user_gbo->Controls->Add(this->d_am_authority_cbo);
		this->d_am_user_gbo->Controls->Add(this->d_am_password2_lbl);
		this->d_am_user_gbo->Controls->Add(this->d_am_authority_lbl);
		this->d_am_user_gbo->Location = System::Drawing::Point(107, 50);
		this->d_am_user_gbo->Name = L"d_am_user_gbo";
		this->d_am_user_gbo->Size = System::Drawing::Size(234, 183);
		this->d_am_user_gbo->TabIndex = 9;
		this->d_am_user_gbo->TabStop = false;
		this->d_am_user_gbo->Text = L"user";
		// 
		// d_am_password_edt
		// 
		this->d_am_password_edt->Location = System::Drawing::Point(105, 72);
		this->d_am_password_edt->Name = L"d_am_password_edt";
		this->d_am_password_edt->Size = System::Drawing::Size(103, 21);
		this->d_am_password_edt->TabIndex = 21;
		// 
		// d_am_password_lbl
		// 
		this->d_am_password_lbl->AutoSize = true;
		this->d_am_password_lbl->Location = System::Drawing::Point(19, 75);
		this->d_am_password_lbl->Name = L"d_am_password_lbl";
		this->d_am_password_lbl->Size = System::Drawing::Size(53, 12);
		this->d_am_password_lbl->TabIndex = 20;
		this->d_am_password_lbl->Text = L"password";
		// 
		// d_am_username_edt
		// 
		this->d_am_username_edt->Location = System::Drawing::Point(105, 35);
		this->d_am_username_edt->Name = L"d_am_username_edt";
		this->d_am_username_edt->Size = System::Drawing::Size(103, 21);
		this->d_am_username_edt->TabIndex = 19;
		// 
		// d_am_username_lbl
		// 
		this->d_am_username_lbl->AutoSize = true;
		this->d_am_username_lbl->Location = System::Drawing::Point(19, 37);
		this->d_am_username_lbl->Name = L"d_am_username_lbl";
		this->d_am_username_lbl->Size = System::Drawing::Size(53, 12);
		this->d_am_username_lbl->TabIndex = 18;
		this->d_am_username_lbl->Text = L"username";
		// 
		// d_am_password2_edt
		// 
		this->d_am_password2_edt->Location = System::Drawing::Point(105, 106);
		this->d_am_password2_edt->Name = L"d_am_password2_edt";
		this->d_am_password2_edt->Size = System::Drawing::Size(103, 21);
		this->d_am_password2_edt->TabIndex = 17;
		// 
		// d_am_authority_cbo
		// 
		this->d_am_authority_cbo->FormattingEnabled = true;
		this->d_am_authority_cbo->Location = System::Drawing::Point(105, 142);
		this->d_am_authority_cbo->Name = L"d_am_authority_cbo";
		this->d_am_authority_cbo->Size = System::Drawing::Size(103, 20);
		this->d_am_authority_cbo->TabIndex = 16;
		// 
		// d_am_password2_lbl
		// 
		this->d_am_password2_lbl->AutoSize = true;
		this->d_am_password2_lbl->Location = System::Drawing::Point(19, 109);
		this->d_am_password2_lbl->Name = L"d_am_password2_lbl";
		this->d_am_password2_lbl->Size = System::Drawing::Size(53, 12);
		this->d_am_password2_lbl->TabIndex = 15;
		this->d_am_password2_lbl->Text = L"password";
		// 
		// d_am_authority_lbl
		// 
		this->d_am_authority_lbl->AutoSize = true;
		this->d_am_authority_lbl->Location = System::Drawing::Point(19, 142);
		this->d_am_authority_lbl->Name = L"d_am_authority_lbl";
		this->d_am_authority_lbl->Size = System::Drawing::Size(59, 12);
		this->d_am_authority_lbl->TabIndex = 14;
		this->d_am_authority_lbl->Text = L"authority";
		// 
		// d_am_commit_gbo
		// 
		this->d_am_commit_gbo->Controls->Add(this->d_am_commit_btn);
		this->d_am_commit_gbo->Location = System::Drawing::Point(107, 281);
		this->d_am_commit_gbo->Name = L"d_am_commit_gbo";
		this->d_am_commit_gbo->Size = System::Drawing::Size(234, 45);
		this->d_am_commit_gbo->TabIndex = 7;
		this->d_am_commit_gbo->TabStop = false;
		this->d_am_commit_gbo->Text = L"commit";
		// 
		// d_am_commit_btn
		// 
		this->d_am_commit_btn->Location = System::Drawing::Point(140, 16);
		this->d_am_commit_btn->Name = L"d_am_commit_btn";
		this->d_am_commit_btn->Size = System::Drawing::Size(75, 23);
		this->d_am_commit_btn->TabIndex = 0;
		this->d_am_commit_btn->Text = L"commint";
		this->d_am_commit_btn->UseVisualStyleBackColor = true;
		this->d_am_commit_btn->Click += gcnew System::EventHandler(this, &MainForm::d_am_commit_btn_Click);
		// 
		// d_am_record_pag
		// 
		this->d_am_record_pag->Controls->Add(this->d_am_record_pal);
		this->d_am_record_pag->Location = System::Drawing::Point(4, 21);
		this->d_am_record_pag->Name = L"d_am_record_pag";
		this->d_am_record_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_am_record_pag->Size = System::Drawing::Size(445, 389);
		this->d_am_record_pag->TabIndex = 1;
		this->d_am_record_pag->Text = L"record";
		this->d_am_record_pag->UseVisualStyleBackColor = true;
		// 
		// d_am_record_pal
		// 
		this->d_am_record_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_am_record_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_am_record_pal->Controls->Add(this->d_am_account_gbo);
		this->d_am_record_pal->Controls->Add(this->d_am_change_gbo);
		this->d_am_record_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_am_record_pal->Location = System::Drawing::Point(3, 3);
		this->d_am_record_pal->Name = L"d_am_record_pal";
		this->d_am_record_pal->Size = System::Drawing::Size(439, 383);
		this->d_am_record_pal->TabIndex = 4;
		// 
		// d_am_account_gbo
		// 
		this->d_am_account_gbo->Controls->Add(this->d_am_account_list);
		this->d_am_account_gbo->Location = System::Drawing::Point(10, 6);
		this->d_am_account_gbo->Name = L"d_am_account_gbo";
		this->d_am_account_gbo->Size = System::Drawing::Size(106, 365);
		this->d_am_account_gbo->TabIndex = 9;
		this->d_am_account_gbo->TabStop = false;
		this->d_am_account_gbo->Text = L"account";
		// 
		// d_am_account_list
		// 
		this->d_am_account_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->d_am_column_name, 
			this->d_am_column_authority, this->d_am_column_gm_id});
		this->d_am_account_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_am_account_list->FullRowSelect = true;
		this->d_am_account_list->GridLines = true;
		this->d_am_account_list->HideSelection = false;
		this->d_am_account_list->Location = System::Drawing::Point(3, 17);
		this->d_am_account_list->Name = L"d_am_account_list";
		this->d_am_account_list->Size = System::Drawing::Size(100, 345);
		this->d_am_account_list->TabIndex = 0;
		this->d_am_account_list->UseCompatibleStateImageBehavior = false;
		this->d_am_account_list->View = System::Windows::Forms::View::Details;
		this->d_am_account_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_am_account_list_MouseDoubleClick);
		// 
		// d_am_column_name
		// 
		this->d_am_column_name->Text = L"name";
		this->d_am_column_name->Width = 80;
		// 
		// d_am_column_authority
		// 
		this->d_am_column_authority->Text = L"authority";
		// 
		// d_am_column_gm_id
		// 
		this->d_am_column_gm_id->Text = L"gm_id";
		// 
		// d_am_change_gbo
		// 
		this->d_am_change_gbo->Controls->Add(this->d_am_change_name_content_lbl);
		this->d_am_change_gbo->Controls->Add(this->d_am_change_name_lbl);
		this->d_am_change_gbo->Controls->Add(this->d_am_change_delete_gbo);
		this->d_am_change_gbo->Controls->Add(this->d_am_change_update_gbo);
		this->d_am_change_gbo->Controls->Add(this->d_am_change_info_gbo);
		this->d_am_change_gbo->Location = System::Drawing::Point(126, 6);
		this->d_am_change_gbo->Name = L"d_am_change_gbo";
		this->d_am_change_gbo->Size = System::Drawing::Size(301, 364);
		this->d_am_change_gbo->TabIndex = 6;
		this->d_am_change_gbo->TabStop = false;
		this->d_am_change_gbo->Text = L"account";
		// 
		// d_am_change_name_content_lbl
		// 
		this->d_am_change_name_content_lbl->AutoSize = true;
		this->d_am_change_name_content_lbl->Location = System::Drawing::Point(104, 19);
		this->d_am_change_name_content_lbl->Name = L"d_am_change_name_content_lbl";
		this->d_am_change_name_content_lbl->Size = System::Drawing::Size(29, 12);
		this->d_am_change_name_content_lbl->TabIndex = 20;
		this->d_am_change_name_content_lbl->Text = L"null";
		// 
		// d_am_change_name_lbl
		// 
		this->d_am_change_name_lbl->AutoSize = true;
		this->d_am_change_name_lbl->Location = System::Drawing::Point(22, 20);
		this->d_am_change_name_lbl->Name = L"d_am_change_name_lbl";
		this->d_am_change_name_lbl->Size = System::Drawing::Size(35, 12);
		this->d_am_change_name_lbl->TabIndex = 19;
		this->d_am_change_name_lbl->Text = L"name:";
		// 
		// d_am_change_delete_gbo
		// 
		this->d_am_change_delete_gbo->Controls->Add(this->d_am_delete_reason_btn);
		this->d_am_change_delete_gbo->Location = System::Drawing::Point(23, 295);
		this->d_am_change_delete_gbo->Name = L"d_am_change_delete_gbo";
		this->d_am_change_delete_gbo->Size = System::Drawing::Size(257, 45);
		this->d_am_change_delete_gbo->TabIndex = 18;
		this->d_am_change_delete_gbo->TabStop = false;
		this->d_am_change_delete_gbo->Text = L"delete";
		// 
		// d_am_delete_reason_btn
		// 
		this->d_am_delete_reason_btn->Location = System::Drawing::Point(165, 15);
		this->d_am_delete_reason_btn->Name = L"d_am_delete_reason_btn";
		this->d_am_delete_reason_btn->Size = System::Drawing::Size(75, 23);
		this->d_am_delete_reason_btn->TabIndex = 0;
		this->d_am_delete_reason_btn->Text = L"delete";
		this->d_am_delete_reason_btn->UseVisualStyleBackColor = true;
		this->d_am_delete_reason_btn->Click += gcnew System::EventHandler(this, &MainForm::d_am_delete_reason_btn_Click);
		// 
		// d_am_change_update_gbo
		// 
		this->d_am_change_update_gbo->Controls->Add(this->d_am_update_reason_btn);
		this->d_am_change_update_gbo->Location = System::Drawing::Point(23, 239);
		this->d_am_change_update_gbo->Name = L"d_am_change_update_gbo";
		this->d_am_change_update_gbo->Size = System::Drawing::Size(257, 45);
		this->d_am_change_update_gbo->TabIndex = 17;
		this->d_am_change_update_gbo->TabStop = false;
		this->d_am_change_update_gbo->Text = L"update";
		// 
		// d_am_update_reason_btn
		// 
		this->d_am_update_reason_btn->Location = System::Drawing::Point(165, 15);
		this->d_am_update_reason_btn->Name = L"d_am_update_reason_btn";
		this->d_am_update_reason_btn->Size = System::Drawing::Size(75, 23);
		this->d_am_update_reason_btn->TabIndex = 0;
		this->d_am_update_reason_btn->Text = L"update";
		this->d_am_update_reason_btn->UseVisualStyleBackColor = true;
		this->d_am_update_reason_btn->Click += gcnew System::EventHandler(this, &MainForm::d_am_update_reason_btn_Click);
		// 
		// d_am_change_info_gbo
		// 
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_authority_cbx);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_password_cbx);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_newpasswor2_txt);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_newpasswor2_lbl);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_oldpassword_txt);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_oldpassword_lbl);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_newpassword_txt);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_authority_cbo);
		this->d_am_change_info_gbo->Controls->Add(this->d_am_change_newpassword_lbl);
		this->d_am_change_info_gbo->Location = System::Drawing::Point(22, 37);
		this->d_am_change_info_gbo->Name = L"d_am_change_info_gbo";
		this->d_am_change_info_gbo->Size = System::Drawing::Size(260, 187);
		this->d_am_change_info_gbo->TabIndex = 16;
		this->d_am_change_info_gbo->TabStop = false;
		this->d_am_change_info_gbo->Text = L"account";
		// 
		// d_am_change_authority_cbx
		// 
		this->d_am_change_authority_cbx->AutoSize = true;
		this->d_am_change_authority_cbx->Location = System::Drawing::Point(16, 155);
		this->d_am_change_authority_cbx->Name = L"d_am_change_authority_cbx";
		this->d_am_change_authority_cbx->Size = System::Drawing::Size(120, 16);
		this->d_am_change_authority_cbx->TabIndex = 33;
		this->d_am_change_authority_cbx->Text = L"change authority";
		this->d_am_change_authority_cbx->UseVisualStyleBackColor = true;
		this->d_am_change_authority_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_am_change_authority_cbx_CheckedChanged);
		// 
		// d_am_change_password_cbx
		// 
		this->d_am_change_password_cbx->AutoSize = true;
		this->d_am_change_password_cbx->Location = System::Drawing::Point(17, 20);
		this->d_am_change_password_cbx->Name = L"d_am_change_password_cbx";
		this->d_am_change_password_cbx->Size = System::Drawing::Size(114, 16);
		this->d_am_change_password_cbx->TabIndex = 32;
		this->d_am_change_password_cbx->Text = L"change password";
		this->d_am_change_password_cbx->UseVisualStyleBackColor = true;
		this->d_am_change_password_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_am_change_password_cbx_CheckedChanged);
		// 
		// d_am_change_newpasswor2_txt
		// 
		this->d_am_change_newpasswor2_txt->Enabled = false;
		this->d_am_change_newpasswor2_txt->Location = System::Drawing::Point(150, 117);
		this->d_am_change_newpasswor2_txt->Name = L"d_am_change_newpasswor2_txt";
		this->d_am_change_newpasswor2_txt->Size = System::Drawing::Size(90, 21);
		this->d_am_change_newpasswor2_txt->TabIndex = 31;
		// 
		// d_am_change_newpasswor2_lbl
		// 
		this->d_am_change_newpasswor2_lbl->AutoSize = true;
		this->d_am_change_newpasswor2_lbl->Enabled = false;
		this->d_am_change_newpasswor2_lbl->Location = System::Drawing::Point(54, 121);
		this->d_am_change_newpasswor2_lbl->Name = L"d_am_change_newpasswor2_lbl";
		this->d_am_change_newpasswor2_lbl->Size = System::Drawing::Size(71, 12);
		this->d_am_change_newpasswor2_lbl->TabIndex = 30;
		this->d_am_change_newpasswor2_lbl->Text = L"newpassword";
		// 
		// d_am_change_oldpassword_txt
		// 
		this->d_am_change_oldpassword_txt->Enabled = false;
		this->d_am_change_oldpassword_txt->Location = System::Drawing::Point(150, 42);
		this->d_am_change_oldpassword_txt->Name = L"d_am_change_oldpassword_txt";
		this->d_am_change_oldpassword_txt->Size = System::Drawing::Size(90, 21);
		this->d_am_change_oldpassword_txt->TabIndex = 29;
		// 
		// d_am_change_oldpassword_lbl
		// 
		this->d_am_change_oldpassword_lbl->AutoSize = true;
		this->d_am_change_oldpassword_lbl->Enabled = false;
		this->d_am_change_oldpassword_lbl->Location = System::Drawing::Point(54, 46);
		this->d_am_change_oldpassword_lbl->Name = L"d_am_change_oldpassword_lbl";
		this->d_am_change_oldpassword_lbl->Size = System::Drawing::Size(71, 12);
		this->d_am_change_oldpassword_lbl->TabIndex = 28;
		this->d_am_change_oldpassword_lbl->Text = L"oldpassword";
		// 
		// d_am_change_newpassword_txt
		// 
		this->d_am_change_newpassword_txt->Enabled = false;
		this->d_am_change_newpassword_txt->Location = System::Drawing::Point(150, 80);
		this->d_am_change_newpassword_txt->Name = L"d_am_change_newpassword_txt";
		this->d_am_change_newpassword_txt->Size = System::Drawing::Size(90, 21);
		this->d_am_change_newpassword_txt->TabIndex = 25;
		// 
		// d_am_change_authority_cbo
		// 
		this->d_am_change_authority_cbo->Enabled = false;
		this->d_am_change_authority_cbo->FormattingEnabled = true;
		this->d_am_change_authority_cbo->Location = System::Drawing::Point(150, 153);
		this->d_am_change_authority_cbo->Name = L"d_am_change_authority_cbo";
		this->d_am_change_authority_cbo->Size = System::Drawing::Size(90, 20);
		this->d_am_change_authority_cbo->TabIndex = 24;
		// 
		// d_am_change_newpassword_lbl
		// 
		this->d_am_change_newpassword_lbl->AutoSize = true;
		this->d_am_change_newpassword_lbl->Enabled = false;
		this->d_am_change_newpassword_lbl->Location = System::Drawing::Point(54, 83);
		this->d_am_change_newpassword_lbl->Name = L"d_am_change_newpassword_lbl";
		this->d_am_change_newpassword_lbl->Size = System::Drawing::Size(71, 12);
		this->d_am_change_newpassword_lbl->TabIndex = 23;
		this->d_am_change_newpassword_lbl->Text = L"newpassword";
		// 
		// c_account_record_pag
		// 
		this->c_account_record_pag->Controls->Add(this->c_account_record_pal);
		this->c_account_record_pag->Location = System::Drawing::Point(4, 21);
		this->c_account_record_pag->Name = L"c_account_record_pag";
		this->c_account_record_pag->Padding = System::Windows::Forms::Padding(3);
		this->c_account_record_pag->Size = System::Drawing::Size(636, 446);
		this->c_account_record_pag->TabIndex = 1;
		this->c_account_record_pag->Text = L"record";
		this->c_account_record_pag->UseVisualStyleBackColor = true;
		// 
		// c_account_record_pal
		// 
		this->c_account_record_pal->Controls->Add(this->d_ar_pal);
		this->c_account_record_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_account_record_pal->Location = System::Drawing::Point(3, 3);
		this->c_account_record_pal->Name = L"c_account_record_pal";
		this->c_account_record_pal->Size = System::Drawing::Size(630, 440);
		this->c_account_record_pal->TabIndex = 0;
		// 
		// d_ar_pal
		// 
		this->d_ar_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_ar_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_ar_pal->Controls->Add(this->d_ar_record_pal);
		this->d_ar_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ar_pal->Location = System::Drawing::Point(0, 0);
		this->d_ar_pal->Name = L"d_ar_pal";
		this->d_ar_pal->Size = System::Drawing::Size(630, 440);
		this->d_ar_pal->TabIndex = 6;
		// 
		// d_ar_record_pal
		// 
		this->d_ar_record_pal->Controls->Add(this->d_ar_log_tab);
		this->d_ar_record_pal->Controls->Add(this->d_ar_filter_pal);
		this->d_ar_record_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ar_record_pal->Location = System::Drawing::Point(0, 0);
		this->d_ar_record_pal->Name = L"d_ar_record_pal";
		this->d_ar_record_pal->Size = System::Drawing::Size(628, 438);
		this->d_ar_record_pal->TabIndex = 11;
		// 
		// d_ar_log_tab
		// 
		this->d_ar_log_tab->Controls->Add(this->d_ar_log_senditem_pag);
		this->d_ar_log_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ar_log_tab->Location = System::Drawing::Point(0, 87);
		this->d_ar_log_tab->Name = L"d_ar_log_tab";
		this->d_ar_log_tab->SelectedIndex = 0;
		this->d_ar_log_tab->Size = System::Drawing::Size(628, 351);
		this->d_ar_log_tab->TabIndex = 12;
		// 
		// d_ar_log_senditem_pag
		// 
		this->d_ar_log_senditem_pag->Controls->Add(this->d_ar_si_log_gbo);
		this->d_ar_log_senditem_pag->Controls->Add(this->d_ar_si_filter_pal);
		this->d_ar_log_senditem_pag->Location = System::Drawing::Point(4, 21);
		this->d_ar_log_senditem_pag->Name = L"d_ar_log_senditem_pag";
		this->d_ar_log_senditem_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_ar_log_senditem_pag->Size = System::Drawing::Size(620, 326);
		this->d_ar_log_senditem_pag->TabIndex = 0;
		this->d_ar_log_senditem_pag->Text = L"send item";
		this->d_ar_log_senditem_pag->UseVisualStyleBackColor = true;
		// 
		// d_ar_si_log_gbo
		// 
		this->d_ar_si_log_gbo->Controls->Add(this->d_ar_si_log_list);
		this->d_ar_si_log_gbo->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ar_si_log_gbo->Location = System::Drawing::Point(3, 54);
		this->d_ar_si_log_gbo->Name = L"d_ar_si_log_gbo";
		this->d_ar_si_log_gbo->Size = System::Drawing::Size(614, 269);
		this->d_ar_si_log_gbo->TabIndex = 12;
		this->d_ar_si_log_gbo->TabStop = false;
		this->d_ar_si_log_gbo->Text = L"record";
		// 
		// d_ar_si_log_list
		// 
		this->d_ar_si_log_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(11) {this->column_ar_si_log_id, 
			this->column_ar_si_sendtime, this->column_ar_si_gm_name, this->column_ar_si_region, this->column_ar_si_playername, this->column_ar_si_playerid, 
			this->column_ar_si_itemname, this->column_ar_si_itemcount, this->column_ar_si_itemlvl, this->column_ar_si_itemgrad, this->column_ar_si_itemuin});
		this->d_ar_si_log_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ar_si_log_list->FullRowSelect = true;
		this->d_ar_si_log_list->GridLines = true;
		this->d_ar_si_log_list->HideSelection = false;
		this->d_ar_si_log_list->Location = System::Drawing::Point(3, 17);
		this->d_ar_si_log_list->Name = L"d_ar_si_log_list";
		this->d_ar_si_log_list->Size = System::Drawing::Size(608, 249);
		this->d_ar_si_log_list->TabIndex = 1;
		this->d_ar_si_log_list->UseCompatibleStateImageBehavior = false;
		this->d_ar_si_log_list->View = System::Windows::Forms::View::Details;
		// 
		// column_ar_si_log_id
		// 
		this->column_ar_si_log_id->Text = L"log_id";
		this->column_ar_si_log_id->Width = 40;
		// 
		// column_ar_si_sendtime
		// 
		this->column_ar_si_sendtime->Text = L"time";
		this->column_ar_si_sendtime->Width = 160;
		// 
		// column_ar_si_gm_name
		// 
		this->column_ar_si_gm_name->Text = L"gm name";
		// 
		// column_ar_si_region
		// 
		this->column_ar_si_region->Text = L"region";
		this->column_ar_si_region->Width = 80;
		// 
		// column_ar_si_playername
		// 
		this->column_ar_si_playername->Text = L"playername";
		// 
		// column_ar_si_playerid
		// 
		this->column_ar_si_playerid->Text = L"playerid";
		this->column_ar_si_playerid->Width = 70;
		// 
		// column_ar_si_itemname
		// 
		this->column_ar_si_itemname->Text = L"item name";
		this->column_ar_si_itemname->Width = 100;
		// 
		// column_ar_si_itemcount
		// 
		this->column_ar_si_itemcount->Text = L"count";
		this->column_ar_si_itemcount->Width = 40;
		// 
		// column_ar_si_itemlvl
		// 
		this->column_ar_si_itemlvl->Text = L"level";
		this->column_ar_si_itemlvl->Width = 40;
		// 
		// column_ar_si_itemgrad
		// 
		this->column_ar_si_itemgrad->Text = L"grad";
		this->column_ar_si_itemgrad->Width = 40;
		// 
		// column_ar_si_itemuin
		// 
		this->column_ar_si_itemuin->Text = L"item uin";
		this->column_ar_si_itemuin->Width = 120;
		// 
		// d_ar_si_filter_pal
		// 
		this->d_ar_si_filter_pal->Controls->Add(this->d_ar_si_filter_gbo);
		this->d_ar_si_filter_pal->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_ar_si_filter_pal->Location = System::Drawing::Point(3, 3);
		this->d_ar_si_filter_pal->Name = L"d_ar_si_filter_pal";
		this->d_ar_si_filter_pal->Size = System::Drawing::Size(614, 51);
		this->d_ar_si_filter_pal->TabIndex = 11;
		// 
		// d_ar_si_filter_gbo
		// 
		this->d_ar_si_filter_gbo->Controls->Add(this->d_ar_si_itemtype_cbo);
		this->d_ar_si_filter_gbo->Controls->Add(this->d_ar_si_itemtype_cbx);
		this->d_ar_si_filter_gbo->Controls->Add(this->d_ar_si_search_btn);
		this->d_ar_si_filter_gbo->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_ar_si_filter_gbo->Location = System::Drawing::Point(0, 0);
		this->d_ar_si_filter_gbo->Name = L"d_ar_si_filter_gbo";
		this->d_ar_si_filter_gbo->Size = System::Drawing::Size(614, 51);
		this->d_ar_si_filter_gbo->TabIndex = 10;
		this->d_ar_si_filter_gbo->TabStop = false;
		this->d_ar_si_filter_gbo->Text = L"filter";
		// 
		// d_ar_si_itemtype_cbo
		// 
		this->d_ar_si_itemtype_cbo->Enabled = false;
		this->d_ar_si_itemtype_cbo->FormattingEnabled = true;
		this->d_ar_si_itemtype_cbo->Location = System::Drawing::Point(273, 19);
		this->d_ar_si_itemtype_cbo->Name = L"d_ar_si_itemtype_cbo";
		this->d_ar_si_itemtype_cbo->Size = System::Drawing::Size(118, 20);
		this->d_ar_si_itemtype_cbo->TabIndex = 18;
		// 
		// d_ar_si_itemtype_cbx
		// 
		this->d_ar_si_itemtype_cbx->AutoSize = true;
		this->d_ar_si_itemtype_cbx->Location = System::Drawing::Point(178, 21);
		this->d_ar_si_itemtype_cbx->Name = L"d_ar_si_itemtype_cbx";
		this->d_ar_si_itemtype_cbx->Size = System::Drawing::Size(78, 16);
		this->d_ar_si_itemtype_cbx->TabIndex = 17;
		this->d_ar_si_itemtype_cbx->Text = L"item type";
		this->d_ar_si_itemtype_cbx->UseVisualStyleBackColor = true;
		this->d_ar_si_itemtype_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_ar_si_itemtype_cbx_CheckedChanged);
		// 
		// d_ar_si_search_btn
		// 
		this->d_ar_si_search_btn->Location = System::Drawing::Point(502, 19);
		this->d_ar_si_search_btn->Name = L"d_ar_si_search_btn";
		this->d_ar_si_search_btn->Size = System::Drawing::Size(75, 23);
		this->d_ar_si_search_btn->TabIndex = 14;
		this->d_ar_si_search_btn->Text = L"search";
		this->d_ar_si_search_btn->UseVisualStyleBackColor = true;
		this->d_ar_si_search_btn->Click += gcnew System::EventHandler(this, &MainForm::d_ar_si_search_btn_Click);
		// 
		// d_ar_filter_pal
		// 
		this->d_ar_filter_pal->Controls->Add(this->d_ar_filter_gbo);
		this->d_ar_filter_pal->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_ar_filter_pal->Location = System::Drawing::Point(0, 0);
		this->d_ar_filter_pal->Name = L"d_ar_filter_pal";
		this->d_ar_filter_pal->Size = System::Drawing::Size(628, 87);
		this->d_ar_filter_pal->TabIndex = 11;
		// 
		// d_ar_filter_gbo
		// 
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_endtime_cbx);
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_starttime_cbx);
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_endtime_dtp);
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_starttime_dtp);
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_region_cbo);
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_region_cbx);
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_gmname_cbo);
		this->d_ar_filter_gbo->Controls->Add(this->d_ar_si_gmname_cbx);
		this->d_ar_filter_gbo->Location = System::Drawing::Point(54, 7);
		this->d_ar_filter_gbo->Name = L"d_ar_filter_gbo";
		this->d_ar_filter_gbo->Size = System::Drawing::Size(530, 70);
		this->d_ar_filter_gbo->TabIndex = 10;
		this->d_ar_filter_gbo->TabStop = false;
		this->d_ar_filter_gbo->Text = L"filter";
		// 
		// d_ar_si_endtime_cbx
		// 
		this->d_ar_si_endtime_cbx->AutoSize = true;
		this->d_ar_si_endtime_cbx->Location = System::Drawing::Point(274, 51);
		this->d_ar_si_endtime_cbx->Name = L"d_ar_si_endtime_cbx";
		this->d_ar_si_endtime_cbx->Size = System::Drawing::Size(72, 16);
		this->d_ar_si_endtime_cbx->TabIndex = 44;
		this->d_ar_si_endtime_cbx->Text = L"end time";
		this->d_ar_si_endtime_cbx->UseVisualStyleBackColor = true;
		this->d_ar_si_endtime_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_ar_si_endtime_cbx_CheckedChanged);
		// 
		// d_ar_si_starttime_cbx
		// 
		this->d_ar_si_starttime_cbx->AutoSize = true;
		this->d_ar_si_starttime_cbx->Location = System::Drawing::Point(44, 51);
		this->d_ar_si_starttime_cbx->Name = L"d_ar_si_starttime_cbx";
		this->d_ar_si_starttime_cbx->Size = System::Drawing::Size(84, 16);
		this->d_ar_si_starttime_cbx->TabIndex = 43;
		this->d_ar_si_starttime_cbx->Text = L"start time";
		this->d_ar_si_starttime_cbx->UseVisualStyleBackColor = true;
		this->d_ar_si_starttime_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_ar_si_starttime_cbx_CheckedChanged);
		// 
		// d_ar_si_endtime_dtp
		// 
		this->d_ar_si_endtime_dtp->Enabled = false;
		this->d_ar_si_endtime_dtp->Location = System::Drawing::Point(363, 49);
		this->d_ar_si_endtime_dtp->Name = L"d_ar_si_endtime_dtp";
		this->d_ar_si_endtime_dtp->Size = System::Drawing::Size(117, 21);
		this->d_ar_si_endtime_dtp->TabIndex = 42;
		// 
		// d_ar_si_starttime_dtp
		// 
		this->d_ar_si_starttime_dtp->Enabled = false;
		this->d_ar_si_starttime_dtp->Location = System::Drawing::Point(134, 49);
		this->d_ar_si_starttime_dtp->Name = L"d_ar_si_starttime_dtp";
		this->d_ar_si_starttime_dtp->Size = System::Drawing::Size(121, 21);
		this->d_ar_si_starttime_dtp->TabIndex = 41;
		// 
		// d_ar_si_region_cbo
		// 
		this->d_ar_si_region_cbo->Enabled = false;
		this->d_ar_si_region_cbo->FormattingEnabled = true;
		this->d_ar_si_region_cbo->Location = System::Drawing::Point(117, 17);
		this->d_ar_si_region_cbo->Name = L"d_ar_si_region_cbo";
		this->d_ar_si_region_cbo->Size = System::Drawing::Size(94, 20);
		this->d_ar_si_region_cbo->TabIndex = 40;
		// 
		// d_ar_si_region_cbx
		// 
		this->d_ar_si_region_cbx->AutoSize = true;
		this->d_ar_si_region_cbx->Location = System::Drawing::Point(44, 20);
		this->d_ar_si_region_cbx->Name = L"d_ar_si_region_cbx";
		this->d_ar_si_region_cbx->Size = System::Drawing::Size(60, 16);
		this->d_ar_si_region_cbx->TabIndex = 39;
		this->d_ar_si_region_cbx->Text = L"region";
		this->d_ar_si_region_cbx->UseVisualStyleBackColor = true;
		this->d_ar_si_region_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_ar_si_region_cbx_CheckedChanged);
		// 
		// d_ar_si_gmname_cbo
		// 
		this->d_ar_si_gmname_cbo->Enabled = false;
		this->d_ar_si_gmname_cbo->FormattingEnabled = true;
		this->d_ar_si_gmname_cbo->Location = System::Drawing::Point(306, 17);
		this->d_ar_si_gmname_cbo->Name = L"d_ar_si_gmname_cbo";
		this->d_ar_si_gmname_cbo->Size = System::Drawing::Size(94, 20);
		this->d_ar_si_gmname_cbo->TabIndex = 38;
		// 
		// d_ar_si_gmname_cbx
		// 
		this->d_ar_si_gmname_cbx->AutoSize = true;
		this->d_ar_si_gmname_cbx->Location = System::Drawing::Point(236, 20);
		this->d_ar_si_gmname_cbx->Name = L"d_ar_si_gmname_cbx";
		this->d_ar_si_gmname_cbx->Size = System::Drawing::Size(48, 16);
		this->d_ar_si_gmname_cbx->TabIndex = 37;
		this->d_ar_si_gmname_cbx->Text = L"name";
		this->d_ar_si_gmname_cbx->UseVisualStyleBackColor = true;
		this->d_ar_si_gmname_cbx->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_ar_si_gmname_cbx_CheckedChanged);
		// 
		// c_msg_pag_k
		// 
		this->c_msg_pag_k->Controls->Add(this->c_msg_server_pal_k);
		this->c_msg_pag_k->Controls->Add(this->c_msg_tab_k);
		this->c_msg_pag_k->Location = System::Drawing::Point(4, 21);
		this->c_msg_pag_k->Name = L"c_msg_pag_k";
		this->c_msg_pag_k->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_pag_k->Size = System::Drawing::Size(650, 477);
		this->c_msg_pag_k->TabIndex = 4;
		this->c_msg_pag_k->Text = L"msg_k";
		this->c_msg_pag_k->UseVisualStyleBackColor = true;
		// 
		// c_msg_server_pal_k
		// 
		this->c_msg_server_pal_k->BackColor = System::Drawing::Color::White;
		this->c_msg_server_pal_k->Controls->Add(this->c_msg_server_tab_k);
		this->c_msg_server_pal_k->Dock = System::Windows::Forms::DockStyle::Right;
		this->c_msg_server_pal_k->Location = System::Drawing::Point(464, 3);
		this->c_msg_server_pal_k->Name = L"c_msg_server_pal_k";
		this->c_msg_server_pal_k->Size = System::Drawing::Size(183, 471);
		this->c_msg_server_pal_k->TabIndex = 4;
		// 
		// c_msg_server_tab_k
		// 
		this->c_msg_server_tab_k->Controls->Add(this->c_msg_server_right_pag_k);
		this->c_msg_server_tab_k->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_server_tab_k->Location = System::Drawing::Point(0, 0);
		this->c_msg_server_tab_k->Name = L"c_msg_server_tab_k";
		this->c_msg_server_tab_k->SelectedIndex = 0;
		this->c_msg_server_tab_k->Size = System::Drawing::Size(183, 471);
		this->c_msg_server_tab_k->TabIndex = 2;
		// 
		// c_msg_server_right_pag_k
		// 
		this->c_msg_server_right_pag_k->Controls->Add(this->d_msg_server_list_k);
		this->c_msg_server_right_pag_k->Location = System::Drawing::Point(4, 21);
		this->c_msg_server_right_pag_k->Name = L"c_msg_server_right_pag_k";
		this->c_msg_server_right_pag_k->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_server_right_pag_k->Size = System::Drawing::Size(175, 446);
		this->c_msg_server_right_pag_k->TabIndex = 0;
		this->c_msg_server_right_pag_k->Text = L"server";
		this->c_msg_server_right_pag_k->UseVisualStyleBackColor = true;
		// 
		// d_msg_server_list_k
		// 
		this->d_msg_server_list_k->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->d_msg_column_region_name_k, 
			this->d_msg_column_region_id_k});
		this->d_msg_server_list_k->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_msg_server_list_k->FullRowSelect = true;
		this->d_msg_server_list_k->GridLines = true;
		this->d_msg_server_list_k->HideSelection = false;
		this->d_msg_server_list_k->Location = System::Drawing::Point(3, 3);
		this->d_msg_server_list_k->Name = L"d_msg_server_list_k";
		this->d_msg_server_list_k->Size = System::Drawing::Size(169, 440);
		this->d_msg_server_list_k->TabIndex = 1;
		this->d_msg_server_list_k->UseCompatibleStateImageBehavior = false;
		this->d_msg_server_list_k->View = System::Windows::Forms::View::Details;
		this->d_msg_server_list_k->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_msg_server_list_k_MouseDoubleClick);
		// 
		// d_msg_column_region_name_k
		// 
		this->d_msg_column_region_name_k->Text = L"region_name";
		this->d_msg_column_region_name_k->Width = 89;
		// 
		// d_msg_column_region_id_k
		// 
		this->d_msg_column_region_id_k->Text = L"region_id";
		this->d_msg_column_region_id_k->Width = 75;
		// 
		// c_msg_tab_k
		// 
		this->c_msg_tab_k->Controls->Add(this->c_msg_post_pag_k);
		this->c_msg_tab_k->Controls->Add(this->c_msg_sensword_pag_k);
		this->c_msg_tab_k->Controls->Add(this->c_msg_gmsession_pag_k);
		this->c_msg_tab_k->Controls->Add(this->c_msg_private_reply_pag_k);
		this->c_msg_tab_k->Dock = System::Windows::Forms::DockStyle::Left;
		this->c_msg_tab_k->Location = System::Drawing::Point(3, 3);
		this->c_msg_tab_k->Name = L"c_msg_tab_k";
		this->c_msg_tab_k->SelectedIndex = 0;
		this->c_msg_tab_k->Size = System::Drawing::Size(459, 471);
		this->c_msg_tab_k->TabIndex = 1;
		// 
		// c_msg_post_pag_k
		// 
		this->c_msg_post_pag_k->Controls->Add(this->c_msg_post_pal);
		this->c_msg_post_pag_k->Location = System::Drawing::Point(4, 21);
		this->c_msg_post_pag_k->Name = L"c_msg_post_pag_k";
		this->c_msg_post_pag_k->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_post_pag_k->Size = System::Drawing::Size(451, 446);
		this->c_msg_post_pag_k->TabIndex = 0;
		this->c_msg_post_pag_k->Text = L"post";
		this->c_msg_post_pag_k->UseVisualStyleBackColor = true;
		// 
		// c_msg_post_pal
		// 
		this->c_msg_post_pal->Controls->Add(this->d_mp_pal);
		this->c_msg_post_pal->Dock = System::Windows::Forms::DockStyle::Left;
		this->c_msg_post_pal->Location = System::Drawing::Point(3, 3);
		this->c_msg_post_pal->Name = L"c_msg_post_pal";
		this->c_msg_post_pal->Size = System::Drawing::Size(448, 440);
		this->c_msg_post_pal->TabIndex = 0;
		// 
		// d_mp_pal
		// 
		this->d_mp_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_mp_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_mp_pal->Controls->Add(this->d_mp_tab);
		this->d_mp_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mp_pal->Location = System::Drawing::Point(0, 0);
		this->d_mp_pal->Name = L"d_mp_pal";
		this->d_mp_pal->Size = System::Drawing::Size(448, 440);
		this->d_mp_pal->TabIndex = 0;
		// 
		// d_mp_tab
		// 
		this->d_mp_tab->Controls->Add(this->d_mp_record_pag);
		this->d_mp_tab->Controls->Add(this->d_mp_create_pag);
		this->d_mp_tab->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mp_tab->Location = System::Drawing::Point(0, 0);
		this->d_mp_tab->Name = L"d_mp_tab";
		this->d_mp_tab->SelectedIndex = 0;
		this->d_mp_tab->Size = System::Drawing::Size(446, 438);
		this->d_mp_tab->TabIndex = 0;
		// 
		// d_mp_record_pag
		// 
		this->d_mp_record_pag->Controls->Add(this->d_mpr_create_pal);
		this->d_mp_record_pag->Location = System::Drawing::Point(4, 21);
		this->d_mp_record_pag->Name = L"d_mp_record_pag";
		this->d_mp_record_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_mp_record_pag->Size = System::Drawing::Size(438, 413);
		this->d_mp_record_pag->TabIndex = 1;
		this->d_mp_record_pag->Text = L"list";
		this->d_mp_record_pag->UseVisualStyleBackColor = true;
		// 
		// d_mpr_create_pal
		// 
		this->d_mpr_create_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_mpr_create_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_mpr_create_pal->Controls->Add(this->d_mpr_server_gbo);
		this->d_mpr_create_pal->Controls->Add(this->d_mpr_commit_gbo);
		this->d_mpr_create_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mpr_create_pal->Location = System::Drawing::Point(3, 3);
		this->d_mpr_create_pal->Name = L"d_mpr_create_pal";
		this->d_mpr_create_pal->Size = System::Drawing::Size(432, 407);
		this->d_mpr_create_pal->TabIndex = 4;
		// 
		// d_mpr_server_gbo
		// 
		this->d_mpr_server_gbo->Controls->Add(this->d_mpr_server_list);
		this->d_mpr_server_gbo->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_mpr_server_gbo->Location = System::Drawing::Point(0, 0);
		this->d_mpr_server_gbo->Name = L"d_mpr_server_gbo";
		this->d_mpr_server_gbo->Size = System::Drawing::Size(430, 345);
		this->d_mpr_server_gbo->TabIndex = 9;
		this->d_mpr_server_gbo->TabStop = false;
		this->d_mpr_server_gbo->Text = L"server";
		// 
		// d_mpr_server_list
		// 
		this->d_mpr_server_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(13) {this->dmpr_column_id, 
			this->dmpr_column_content, this->dmpr_column_region_group, this->dmpr_column_start_date, this->dmpr_column_end_date, this->dmpr_column_play_hour, 
			this->dmpr_column_play_minute, this->dmpr_column_play_num, this->dmpr_column_play_pause, this->dmpr_column_play_repeat, this->dmpr_column_play_end_hours, 
			this->dmpr_column_play_end_minutes, this->dmpr_column_play_time_distance});
		this->d_mpr_server_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mpr_server_list->FullRowSelect = true;
		this->d_mpr_server_list->GridLines = true;
		this->d_mpr_server_list->HideSelection = false;
		this->d_mpr_server_list->Location = System::Drawing::Point(3, 17);
		this->d_mpr_server_list->Name = L"d_mpr_server_list";
		this->d_mpr_server_list->Size = System::Drawing::Size(424, 325);
		this->d_mpr_server_list->TabIndex = 0;
		this->d_mpr_server_list->UseCompatibleStateImageBehavior = false;
		this->d_mpr_server_list->View = System::Windows::Forms::View::Details;
		this->d_mpr_server_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_mpr_server_list_MouseDoubleClick);
		// 
		// dmpr_column_id
		// 
		this->dmpr_column_id->Text = L"id";
		this->dmpr_column_id->Width = 50;
		// 
		// dmpr_column_content
		// 
		this->dmpr_column_content->Text = L"content";
		this->dmpr_column_content->Width = 150;
		// 
		// dmpr_column_region_group
		// 
		this->dmpr_column_region_group->Text = L"region group";
		this->dmpr_column_region_group->Width = 150;
		// 
		// dmpr_column_start_date
		// 
		this->dmpr_column_start_date->Text = L"start_data";
		this->dmpr_column_start_date->Width = 180;
		// 
		// dmpr_column_end_date
		// 
		this->dmpr_column_end_date->Text = L"end date";
		this->dmpr_column_end_date->Width = 180;
		// 
		// dmpr_column_play_hour
		// 
		this->dmpr_column_play_hour->Text = L"hour";
		this->dmpr_column_play_hour->Width = 40;
		// 
		// dmpr_column_play_minute
		// 
		this->dmpr_column_play_minute->Text = L"minute";
		this->dmpr_column_play_minute->Width = 40;
		// 
		// dmpr_column_play_num
		// 
		this->dmpr_column_play_num->Text = L"num";
		this->dmpr_column_play_num->Width = 40;
		// 
		// dmpr_column_play_pause
		// 
		this->dmpr_column_play_pause->Text = L"is_pause";
		// 
		// dmpr_column_play_repeat
		// 
		this->dmpr_column_play_repeat->Text = L"is_repeat";
		// 
		// dmpr_column_play_end_hours
		// 
		this->dmpr_column_play_end_hours->Text = L"play_end_hours";
		// 
		// dmpr_column_play_end_minutes
		// 
		this->dmpr_column_play_end_minutes->Text = L"play_end_minutes";
		// 
		// dmpr_column_play_time_distance
		// 
		this->dmpr_column_play_time_distance->Text = L"time_distance";
		// 
		// d_mpr_commit_gbo
		// 
		this->d_mpr_commit_gbo->Controls->Add(this->d_mpr_delete_btn);
		this->d_mpr_commit_gbo->Controls->Add(this->d_mpr_new_btn);
		this->d_mpr_commit_gbo->Controls->Add(this->d_mpr_update_btn);
		this->d_mpr_commit_gbo->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->d_mpr_commit_gbo->Location = System::Drawing::Point(0, 362);
		this->d_mpr_commit_gbo->Name = L"d_mpr_commit_gbo";
		this->d_mpr_commit_gbo->Size = System::Drawing::Size(430, 43);
		this->d_mpr_commit_gbo->TabIndex = 7;
		this->d_mpr_commit_gbo->TabStop = false;
		this->d_mpr_commit_gbo->Text = L"commit";
		// 
		// d_mpr_delete_btn
		// 
		this->d_mpr_delete_btn->Location = System::Drawing::Point(311, 15);
		this->d_mpr_delete_btn->Name = L"d_mpr_delete_btn";
		this->d_mpr_delete_btn->Size = System::Drawing::Size(75, 23);
		this->d_mpr_delete_btn->TabIndex = 11;
		this->d_mpr_delete_btn->Text = L"delete";
		this->d_mpr_delete_btn->UseVisualStyleBackColor = true;
		this->d_mpr_delete_btn->Click += gcnew System::EventHandler(this, &MainForm::d_mpr_delete_btn_Click);
		// 
		// d_mpr_new_btn
		// 
		this->d_mpr_new_btn->Location = System::Drawing::Point(149, 15);
		this->d_mpr_new_btn->Name = L"d_mpr_new_btn";
		this->d_mpr_new_btn->Size = System::Drawing::Size(75, 23);
		this->d_mpr_new_btn->TabIndex = 10;
		this->d_mpr_new_btn->Text = L"new";
		this->d_mpr_new_btn->UseVisualStyleBackColor = true;
		this->d_mpr_new_btn->Click += gcnew System::EventHandler(this, &MainForm::d_mpr_new_btn_Click);
		// 
		// d_mpr_update_btn
		// 
		this->d_mpr_update_btn->Location = System::Drawing::Point(230, 15);
		this->d_mpr_update_btn->Name = L"d_mpr_update_btn";
		this->d_mpr_update_btn->Size = System::Drawing::Size(75, 23);
		this->d_mpr_update_btn->TabIndex = 0;
		this->d_mpr_update_btn->Text = L"update";
		this->d_mpr_update_btn->UseVisualStyleBackColor = true;
		this->d_mpr_update_btn->Click += gcnew System::EventHandler(this, &MainForm::d_mpr_update_btn_Click);
		// 
		// d_mp_create_pag
		// 
		this->d_mp_create_pag->Controls->Add(this->d_mp_create_pal);
		this->d_mp_create_pag->Location = System::Drawing::Point(4, 21);
		this->d_mp_create_pag->Name = L"d_mp_create_pag";
		this->d_mp_create_pag->Padding = System::Windows::Forms::Padding(3);
		this->d_mp_create_pag->Size = System::Drawing::Size(438, 413);
		this->d_mp_create_pag->TabIndex = 2;
		this->d_mp_create_pag->Text = L"record";
		this->d_mp_create_pag->UseVisualStyleBackColor = true;
		// 
		// d_mp_create_pal
		// 
		this->d_mp_create_pal->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_mp_create_pal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->d_mp_create_pal->Controls->Add(this->d_mp_title_gbo);
		this->d_mp_create_pal->Controls->Add(this->d_mp_commit_gbo);
		this->d_mp_create_pal->Controls->Add(this->d_mp_post_gbo);
		this->d_mp_create_pal->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mp_create_pal->Location = System::Drawing::Point(3, 3);
		this->d_mp_create_pal->Name = L"d_mp_create_pal";
		this->d_mp_create_pal->Size = System::Drawing::Size(432, 407);
		this->d_mp_create_pal->TabIndex = 3;
		// 
		// d_mp_title_gbo
		// 
		this->d_mp_title_gbo->Controls->Add(this->d_mp_id_value_lbl);
		this->d_mp_title_gbo->Controls->Add(this->d_mp_id_lbl);
		this->d_mp_title_gbo->Controls->Add(this->d_mp_state_value_lbl);
		this->d_mp_title_gbo->Controls->Add(this->d_mp_state_lbl);
		this->d_mp_title_gbo->Dock = System::Windows::Forms::DockStyle::Top;
		this->d_mp_title_gbo->Location = System::Drawing::Point(0, 0);
		this->d_mp_title_gbo->Name = L"d_mp_title_gbo";
		this->d_mp_title_gbo->Size = System::Drawing::Size(430, 37);
		this->d_mp_title_gbo->TabIndex = 8;
		this->d_mp_title_gbo->TabStop = false;
		this->d_mp_title_gbo->Text = L"title";
		// 
		// d_mp_id_value_lbl
		// 
		this->d_mp_id_value_lbl->AutoSize = true;
		this->d_mp_id_value_lbl->Location = System::Drawing::Point(232, 17);
		this->d_mp_id_value_lbl->Name = L"d_mp_id_value_lbl";
		this->d_mp_id_value_lbl->Size = System::Drawing::Size(29, 12);
		this->d_mp_id_value_lbl->TabIndex = 3;
		this->d_mp_id_value_lbl->Text = L"null";
		// 
		// d_mp_id_lbl
		// 
		this->d_mp_id_lbl->AutoSize = true;
		this->d_mp_id_lbl->Location = System::Drawing::Point(172, 17);
		this->d_mp_id_lbl->Name = L"d_mp_id_lbl";
		this->d_mp_id_lbl->Size = System::Drawing::Size(41, 12);
		this->d_mp_id_lbl->TabIndex = 2;
		this->d_mp_id_lbl->Text = L"state:";
		// 
		// d_mp_state_value_lbl
		// 
		this->d_mp_state_value_lbl->AutoSize = true;
		this->d_mp_state_value_lbl->Location = System::Drawing::Point(79, 17);
		this->d_mp_state_value_lbl->Name = L"d_mp_state_value_lbl";
		this->d_mp_state_value_lbl->Size = System::Drawing::Size(29, 12);
		this->d_mp_state_value_lbl->TabIndex = 1;
		this->d_mp_state_value_lbl->Text = L"null";
		// 
		// d_mp_state_lbl
		// 
		this->d_mp_state_lbl->AutoSize = true;
		this->d_mp_state_lbl->Location = System::Drawing::Point(23, 17);
		this->d_mp_state_lbl->Name = L"d_mp_state_lbl";
		this->d_mp_state_lbl->Size = System::Drawing::Size(41, 12);
		this->d_mp_state_lbl->TabIndex = 0;
		this->d_mp_state_lbl->Text = L"state:";
		// 
		// d_mp_commit_gbo
		// 
		this->d_mp_commit_gbo->Controls->Add(this->d_mp_commit_btn);
		this->d_mp_commit_gbo->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->d_mp_commit_gbo->Location = System::Drawing::Point(0, 360);
		this->d_mp_commit_gbo->Name = L"d_mp_commit_gbo";
		this->d_mp_commit_gbo->Size = System::Drawing::Size(430, 45);
		this->d_mp_commit_gbo->TabIndex = 7;
		this->d_mp_commit_gbo->TabStop = false;
		this->d_mp_commit_gbo->Text = L"commit";
		// 
		// d_mp_commit_btn
		// 
		this->d_mp_commit_btn->Location = System::Drawing::Point(321, 16);
		this->d_mp_commit_btn->Name = L"d_mp_commit_btn";
		this->d_mp_commit_btn->Size = System::Drawing::Size(75, 23);
		this->d_mp_commit_btn->TabIndex = 0;
		this->d_mp_commit_btn->Text = L"commint";
		this->d_mp_commit_btn->UseVisualStyleBackColor = true;
		this->d_mp_commit_btn->Click += gcnew System::EventHandler(this, &MainForm::d_mp_commit_btn_Click);
		// 
		// d_mp_post_gbo
		// 
		this->d_mp_post_gbo->Controls->Add(this->d_mp_pause_ckb);
		this->d_mp_post_gbo->Controls->Add(this->d_mp_cycle_gbo);
		this->d_mp_post_gbo->Controls->Add(this->d_mp_server_gbo);
		this->d_mp_post_gbo->Controls->Add(this->d_mp_cycle_rdo);
		this->d_mp_post_gbo->Controls->Add(this->d_mp_once_rdo);
		this->d_mp_post_gbo->Controls->Add(this->d_mp_text_gbo);
		this->d_mp_post_gbo->Controls->Add(this->d_mp_num_cbo);
		this->d_mp_post_gbo->Controls->Add(this->d_mp_num_lbl);
		this->d_mp_post_gbo->Location = System::Drawing::Point(3, 43);
		this->d_mp_post_gbo->Name = L"d_mp_post_gbo";
		this->d_mp_post_gbo->Size = System::Drawing::Size(424, 311);
		this->d_mp_post_gbo->TabIndex = 6;
		this->d_mp_post_gbo->TabStop = false;
		this->d_mp_post_gbo->Text = L"post";
		// 
		// d_mp_pause_ckb
		// 
		this->d_mp_pause_ckb->AutoSize = true;
		this->d_mp_pause_ckb->Enabled = false;
		this->d_mp_pause_ckb->Location = System::Drawing::Point(171, 175);
		this->d_mp_pause_ckb->Name = L"d_mp_pause_ckb";
		this->d_mp_pause_ckb->Size = System::Drawing::Size(54, 16);
		this->d_mp_pause_ckb->TabIndex = 30;
		this->d_mp_pause_ckb->Text = L"pause";
		this->d_mp_pause_ckb->UseVisualStyleBackColor = true;
		// 
		// d_mp_cycle_gbo
		// 
		this->d_mp_cycle_gbo->Controls->Add(this->time_distance_box);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_repeat_ckb);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_play_time_cbo);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_end_time_k_lbl);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_time_lbl);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_play_time_end_cbo);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_time_distance_lbl);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_end_time_dtp);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_end_time_lbl);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_start_time_dtp);
		this->d_mp_cycle_gbo->Controls->Add(this->d_mp_start_time_lbl);
		this->d_mp_cycle_gbo->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->d_mp_cycle_gbo->Enabled = false;
		this->d_mp_cycle_gbo->Location = System::Drawing::Point(3, 197);
		this->d_mp_cycle_gbo->Name = L"d_mp_cycle_gbo";
		this->d_mp_cycle_gbo->Size = System::Drawing::Size(418, 111);
		this->d_mp_cycle_gbo->TabIndex = 27;
		this->d_mp_cycle_gbo->TabStop = false;
		this->d_mp_cycle_gbo->Text = L"cycle";
		// 
		// time_distance_box
		// 
		this->time_distance_box->Enabled = false;
		this->time_distance_box->Location = System::Drawing::Point(314, 39);
		this->time_distance_box->Name = L"time_distance_box";
		this->time_distance_box->Size = System::Drawing::Size(78, 21);
		this->time_distance_box->TabIndex = 36;
		this->time_distance_box->Text = L"5";
		// 
		// d_mp_repeat_ckb
		// 
		this->d_mp_repeat_ckb->AutoSize = true;
		this->d_mp_repeat_ckb->Location = System::Drawing::Point(127, 41);
		this->d_mp_repeat_ckb->Name = L"d_mp_repeat_ckb";
		this->d_mp_repeat_ckb->Size = System::Drawing::Size(60, 16);
		this->d_mp_repeat_ckb->TabIndex = 35;
		this->d_mp_repeat_ckb->Text = L"repeat";
		this->d_mp_repeat_ckb->UseVisualStyleBackColor = true;
		this->d_mp_repeat_ckb->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_mp_repeat_ckb_CheckedChanged);
		// 
		// d_mp_play_time_cbo
		// 
		this->d_mp_play_time_cbo->Format = System::Windows::Forms::DateTimePickerFormat::Time;
		this->d_mp_play_time_cbo->Location = System::Drawing::Point(19, 38);
		this->d_mp_play_time_cbo->Name = L"d_mp_play_time_cbo";
		this->d_mp_play_time_cbo->Size = System::Drawing::Size(79, 21);
		this->d_mp_play_time_cbo->TabIndex = 34;
		// 
		// d_mp_end_time_k_lbl
		// 
		this->d_mp_end_time_k_lbl->AutoSize = true;
		this->d_mp_end_time_k_lbl->Location = System::Drawing::Point(204, 18);
		this->d_mp_end_time_k_lbl->Name = L"d_mp_end_time_k_lbl";
		this->d_mp_end_time_k_lbl->Size = System::Drawing::Size(53, 12);
		this->d_mp_end_time_k_lbl->TabIndex = 33;
		this->d_mp_end_time_k_lbl->Text = L"end_time";
		// 
		// d_mp_time_lbl
		// 
		this->d_mp_time_lbl->AutoSize = true;
		this->d_mp_time_lbl->Location = System::Drawing::Point(17, 17);
		this->d_mp_time_lbl->Name = L"d_mp_time_lbl";
		this->d_mp_time_lbl->Size = System::Drawing::Size(65, 12);
		this->d_mp_time_lbl->TabIndex = 33;
		this->d_mp_time_lbl->Text = L"start_time";
		// 
		// d_mp_play_time_end_cbo
		// 
		this->d_mp_play_time_end_cbo->Enabled = false;
		this->d_mp_play_time_end_cbo->Format = System::Windows::Forms::DateTimePickerFormat::Time;
		this->d_mp_play_time_end_cbo->Location = System::Drawing::Point(202, 39);
		this->d_mp_play_time_end_cbo->Name = L"d_mp_play_time_end_cbo";
		this->d_mp_play_time_end_cbo->Size = System::Drawing::Size(79, 21);
		this->d_mp_play_time_end_cbo->TabIndex = 34;
		// 
		// d_mp_time_distance_lbl
		// 
		this->d_mp_time_distance_lbl->AutoSize = true;
		this->d_mp_time_distance_lbl->Location = System::Drawing::Point(312, 18);
		this->d_mp_time_distance_lbl->Name = L"d_mp_time_distance_lbl";
		this->d_mp_time_distance_lbl->Size = System::Drawing::Size(83, 12);
		this->d_mp_time_distance_lbl->TabIndex = 33;
		this->d_mp_time_distance_lbl->Text = L"time_distance";
		// 
		// d_mp_end_time_dtp
		// 
		this->d_mp_end_time_dtp->Location = System::Drawing::Point(164, 84);
		this->d_mp_end_time_dtp->Name = L"d_mp_end_time_dtp";
		this->d_mp_end_time_dtp->Size = System::Drawing::Size(117, 21);
		this->d_mp_end_time_dtp->TabIndex = 32;
		// 
		// d_mp_end_time_lbl
		// 
		this->d_mp_end_time_lbl->AutoSize = true;
		this->d_mp_end_time_lbl->Location = System::Drawing::Point(162, 67);
		this->d_mp_end_time_lbl->Name = L"d_mp_end_time_lbl";
		this->d_mp_end_time_lbl->Size = System::Drawing::Size(53, 12);
		this->d_mp_end_time_lbl->TabIndex = 31;
		this->d_mp_end_time_lbl->Text = L"end_date";
		// 
		// d_mp_start_time_dtp
		// 
		this->d_mp_start_time_dtp->Location = System::Drawing::Point(19, 84);
		this->d_mp_start_time_dtp->Name = L"d_mp_start_time_dtp";
		this->d_mp_start_time_dtp->Size = System::Drawing::Size(121, 21);
		this->d_mp_start_time_dtp->TabIndex = 30;
		// 
		// d_mp_start_time_lbl
		// 
		this->d_mp_start_time_lbl->AutoSize = true;
		this->d_mp_start_time_lbl->Location = System::Drawing::Point(17, 67);
		this->d_mp_start_time_lbl->Name = L"d_mp_start_time_lbl";
		this->d_mp_start_time_lbl->Size = System::Drawing::Size(65, 12);
		this->d_mp_start_time_lbl->TabIndex = 26;
		this->d_mp_start_time_lbl->Text = L"start_date";
		// 
		// d_mp_server_gbo
		// 
		this->d_mp_server_gbo->Controls->Add(this->d_mp_server_list);
		this->d_mp_server_gbo->Location = System::Drawing::Point(16, 16);
		this->d_mp_server_gbo->Name = L"d_mp_server_gbo";
		this->d_mp_server_gbo->Size = System::Drawing::Size(107, 123);
		this->d_mp_server_gbo->TabIndex = 26;
		this->d_mp_server_gbo->TabStop = false;
		this->d_mp_server_gbo->Text = L"server";
		// 
		// d_mp_server_list
		// 
		this->d_mp_server_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->dmp_column_region_name, 
			this->dmp_column_region_id});
		this->d_mp_server_list->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mp_server_list->FullRowSelect = true;
		this->d_mp_server_list->GridLines = true;
		this->d_mp_server_list->HideSelection = false;
		this->d_mp_server_list->Location = System::Drawing::Point(3, 17);
		this->d_mp_server_list->Name = L"d_mp_server_list";
		this->d_mp_server_list->Size = System::Drawing::Size(101, 103);
		this->d_mp_server_list->TabIndex = 0;
		this->d_mp_server_list->UseCompatibleStateImageBehavior = false;
		this->d_mp_server_list->View = System::Windows::Forms::View::Details;
		this->d_mp_server_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::d_mp_server_list_MouseDoubleClick);
		// 
		// dmp_column_region_name
		// 
		this->dmp_column_region_name->Text = L"name";
		this->dmp_column_region_name->Width = 100;
		// 
		// dmp_column_region_id
		// 
		this->dmp_column_region_id->Text = L"id";
		// 
		// d_mp_cycle_rdo
		// 
		this->d_mp_cycle_rdo->AutoSize = true;
		this->d_mp_cycle_rdo->Location = System::Drawing::Point(91, 175);
		this->d_mp_cycle_rdo->Name = L"d_mp_cycle_rdo";
		this->d_mp_cycle_rdo->Size = System::Drawing::Size(53, 16);
		this->d_mp_cycle_rdo->TabIndex = 22;
		this->d_mp_cycle_rdo->TabStop = true;
		this->d_mp_cycle_rdo->Text = L"cycle";
		this->d_mp_cycle_rdo->UseVisualStyleBackColor = true;
		this->d_mp_cycle_rdo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_mp_cycle_rdo_CheckedChanged);
		// 
		// d_mp_once_rdo
		// 
		this->d_mp_once_rdo->AutoSize = true;
		this->d_mp_once_rdo->Location = System::Drawing::Point(11, 175);
		this->d_mp_once_rdo->Name = L"d_mp_once_rdo";
		this->d_mp_once_rdo->Size = System::Drawing::Size(47, 16);
		this->d_mp_once_rdo->TabIndex = 21;
		this->d_mp_once_rdo->TabStop = true;
		this->d_mp_once_rdo->Text = L"once";
		this->d_mp_once_rdo->UseVisualStyleBackColor = true;
		this->d_mp_once_rdo->CheckedChanged += gcnew System::EventHandler(this, &MainForm::d_mp_once_rdo_CheckedChanged);
		// 
		// d_mp_text_gbo
		// 
		this->d_mp_text_gbo->Controls->Add(this->d_mp_text_mno);
		this->d_mp_text_gbo->Location = System::Drawing::Point(141, 16);
		this->d_mp_text_gbo->Name = L"d_mp_text_gbo";
		this->d_mp_text_gbo->Size = System::Drawing::Size(253, 123);
		this->d_mp_text_gbo->TabIndex = 16;
		this->d_mp_text_gbo->TabStop = false;
		this->d_mp_text_gbo->Text = L"text";
		// 
		// d_mp_text_mno
		// 
		this->d_mp_text_mno->Dock = System::Windows::Forms::DockStyle::Fill;
		this->d_mp_text_mno->Location = System::Drawing::Point(3, 17);
		this->d_mp_text_mno->Name = L"d_mp_text_mno";
		this->d_mp_text_mno->Size = System::Drawing::Size(247, 103);
		this->d_mp_text_mno->TabIndex = 0;
		this->d_mp_text_mno->Text = L"";
		// 
		// d_mp_num_cbo
		// 
		this->d_mp_num_cbo->FormattingEnabled = true;
		this->d_mp_num_cbo->Location = System::Drawing::Point(64, 142);
		this->d_mp_num_cbo->Name = L"d_mp_num_cbo";
		this->d_mp_num_cbo->Size = System::Drawing::Size(67, 20);
		this->d_mp_num_cbo->TabIndex = 29;
		this->d_mp_num_cbo->Visible = false;
		// 
		// d_mp_num_lbl
		// 
		this->d_mp_num_lbl->AutoSize = true;
		this->d_mp_num_lbl->Location = System::Drawing::Point(17, 150);
		this->d_mp_num_lbl->Name = L"d_mp_num_lbl";
		this->d_mp_num_lbl->Size = System::Drawing::Size(41, 12);
		this->d_mp_num_lbl->TabIndex = 27;
		this->d_mp_num_lbl->Text = L"number";
		this->d_mp_num_lbl->Visible = false;
		// 
		// c_msg_sensword_pag_k
		// 
		this->c_msg_sensword_pag_k->Controls->Add(this->d_msg_senswords_pal_k);
		this->c_msg_sensword_pag_k->Location = System::Drawing::Point(4, 21);
		this->c_msg_sensword_pag_k->Name = L"c_msg_sensword_pag_k";
		this->c_msg_sensword_pag_k->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_sensword_pag_k->Size = System::Drawing::Size(451, 446);
		this->c_msg_sensword_pag_k->TabIndex = 1;
		this->c_msg_sensword_pag_k->Text = L"sens word";
		this->c_msg_sensword_pag_k->UseVisualStyleBackColor = true;
		// 
		// d_msg_senswords_pal_k
		// 
		this->d_msg_senswords_pal_k->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_msg_senswords_pal_k->Controls->Add(this->e_msg_senswords_r_pal_k);
		this->d_msg_senswords_pal_k->Controls->Add(this->d_msg_sensword_group_k);
		this->d_msg_senswords_pal_k->Dock = System::Windows::Forms::DockStyle::Left;
		this->d_msg_senswords_pal_k->Location = System::Drawing::Point(3, 3);
		this->d_msg_senswords_pal_k->Name = L"d_msg_senswords_pal_k";
		this->d_msg_senswords_pal_k->Size = System::Drawing::Size(457, 440);
		this->d_msg_senswords_pal_k->TabIndex = 3;
		// 
		// e_msg_senswords_r_pal_k
		// 
		this->e_msg_senswords_r_pal_k->Controls->Add(this->e_msg_sensword_group_k);
		this->e_msg_senswords_r_pal_k->Controls->Add(this->f_msg_senswords_b_pal_k);
		this->e_msg_senswords_r_pal_k->Dock = System::Windows::Forms::DockStyle::Right;
		this->e_msg_senswords_r_pal_k->Location = System::Drawing::Point(147, 0);
		this->e_msg_senswords_r_pal_k->Name = L"e_msg_senswords_r_pal_k";
		this->e_msg_senswords_r_pal_k->Size = System::Drawing::Size(310, 440);
		this->e_msg_senswords_r_pal_k->TabIndex = 6;
		// 
		// e_msg_sensword_group_k
		// 
		this->e_msg_sensword_group_k->Controls->Add(this->c_msg_sensword_session_list_k);
		this->e_msg_sensword_group_k->Dock = System::Windows::Forms::DockStyle::Top;
		this->e_msg_sensword_group_k->Location = System::Drawing::Point(0, 0);
		this->e_msg_sensword_group_k->Name = L"e_msg_sensword_group_k";
		this->e_msg_sensword_group_k->Size = System::Drawing::Size(310, 408);
		this->e_msg_sensword_group_k->TabIndex = 5;
		this->e_msg_sensword_group_k->TabStop = false;
		this->e_msg_sensword_group_k->Text = L"session";
		// 
		// c_msg_sensword_session_list_k
		// 
		this->c_msg_sensword_session_list_k->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->c_msg_sensword_column_plyname_k, 
			this->c_msg_sensword_column_content_k});
		this->c_msg_sensword_session_list_k->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_sensword_session_list_k->FullRowSelect = true;
		this->c_msg_sensword_session_list_k->GridLines = true;
		this->c_msg_sensword_session_list_k->HideSelection = false;
		this->c_msg_sensword_session_list_k->Location = System::Drawing::Point(3, 17);
		this->c_msg_sensword_session_list_k->Name = L"c_msg_sensword_session_list_k";
		this->c_msg_sensword_session_list_k->Size = System::Drawing::Size(304, 388);
		this->c_msg_sensword_session_list_k->TabIndex = 2;
		this->c_msg_sensword_session_list_k->UseCompatibleStateImageBehavior = false;
		this->c_msg_sensword_session_list_k->View = System::Windows::Forms::View::Details;
		// 
		// c_msg_sensword_column_plyname_k
		// 
		this->c_msg_sensword_column_plyname_k->Text = L"ply";
		this->c_msg_sensword_column_plyname_k->Width = 91;
		// 
		// c_msg_sensword_column_content_k
		// 
		this->c_msg_sensword_column_content_k->Text = L"content";
		this->c_msg_sensword_column_content_k->Width = 254;
		// 
		// f_msg_senswords_b_pal_k
		// 
		this->f_msg_senswords_b_pal_k->Controls->Add(this->f_msg_senswords_open_config_k);
		this->f_msg_senswords_b_pal_k->Controls->Add(this->f_msg_senswords_load_config_k);
		this->f_msg_senswords_b_pal_k->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->f_msg_senswords_b_pal_k->Location = System::Drawing::Point(0, 414);
		this->f_msg_senswords_b_pal_k->Name = L"f_msg_senswords_b_pal_k";
		this->f_msg_senswords_b_pal_k->Size = System::Drawing::Size(310, 26);
		this->f_msg_senswords_b_pal_k->TabIndex = 7;
		// 
		// f_msg_senswords_open_config_k
		// 
		this->f_msg_senswords_open_config_k->Location = System::Drawing::Point(73, 3);
		this->f_msg_senswords_open_config_k->Name = L"f_msg_senswords_open_config_k";
		this->f_msg_senswords_open_config_k->Size = System::Drawing::Size(108, 23);
		this->f_msg_senswords_open_config_k->TabIndex = 3;
		this->f_msg_senswords_open_config_k->Text = L"open config";
		this->f_msg_senswords_open_config_k->UseVisualStyleBackColor = true;
		// 
		// f_msg_senswords_load_config_k
		// 
		this->f_msg_senswords_load_config_k->Location = System::Drawing::Point(205, 3);
		this->f_msg_senswords_load_config_k->Name = L"f_msg_senswords_load_config_k";
		this->f_msg_senswords_load_config_k->Size = System::Drawing::Size(108, 23);
		this->f_msg_senswords_load_config_k->TabIndex = 3;
		this->f_msg_senswords_load_config_k->Text = L"load config";
		this->f_msg_senswords_load_config_k->UseVisualStyleBackColor = true;
		// 
		// d_msg_sensword_group_k
		// 
		this->d_msg_sensword_group_k->Controls->Add(this->c_msg_sensword_server_list_k);
		this->d_msg_sensword_group_k->Dock = System::Windows::Forms::DockStyle::Left;
		this->d_msg_sensword_group_k->Location = System::Drawing::Point(0, 0);
		this->d_msg_sensword_group_k->Name = L"d_msg_sensword_group_k";
		this->d_msg_sensword_group_k->Size = System::Drawing::Size(141, 440);
		this->d_msg_sensword_group_k->TabIndex = 4;
		this->d_msg_sensword_group_k->TabStop = false;
		this->d_msg_sensword_group_k->Text = L"server";
		// 
		// c_msg_sensword_server_list_k
		// 
		this->c_msg_sensword_server_list_k->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->c_msg_sensword_name_k, 
			this->c_msg_sensword_id_k});
		this->c_msg_sensword_server_list_k->Dock = System::Windows::Forms::DockStyle::Fill;
		this->c_msg_sensword_server_list_k->FullRowSelect = true;
		this->c_msg_sensword_server_list_k->GridLines = true;
		this->c_msg_sensword_server_list_k->HideSelection = false;
		this->c_msg_sensword_server_list_k->Location = System::Drawing::Point(3, 17);
		this->c_msg_sensword_server_list_k->Name = L"c_msg_sensword_server_list_k";
		this->c_msg_sensword_server_list_k->Size = System::Drawing::Size(135, 420);
		this->c_msg_sensword_server_list_k->TabIndex = 1;
		this->c_msg_sensword_server_list_k->UseCompatibleStateImageBehavior = false;
		this->c_msg_sensword_server_list_k->View = System::Windows::Forms::View::Details;
		this->c_msg_sensword_server_list_k->DoubleClick += gcnew System::EventHandler(this, &MainForm::c_msg_sensword_server_list_k_DoubleClick);
		// 
		// c_msg_sensword_name_k
		// 
		this->c_msg_sensword_name_k->Text = L"region_name";
		this->c_msg_sensword_name_k->Width = 70;
		// 
		// c_msg_sensword_id_k
		// 
		this->c_msg_sensword_id_k->Text = L"region_id";
		// 
		// c_msg_gmsession_pag_k
		// 
		this->c_msg_gmsession_pag_k->Controls->Add(this->d_msg_gmsession_pal_k);
		this->c_msg_gmsession_pag_k->Location = System::Drawing::Point(4, 21);
		this->c_msg_gmsession_pag_k->Name = L"c_msg_gmsession_pag_k";
		this->c_msg_gmsession_pag_k->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_gmsession_pag_k->Size = System::Drawing::Size(451, 446);
		this->c_msg_gmsession_pag_k->TabIndex = 3;
		this->c_msg_gmsession_pag_k->Text = L"gm session";
		this->c_msg_gmsession_pag_k->UseVisualStyleBackColor = true;
		// 
		// d_msg_gmsession_pal_k
		// 
		this->d_msg_gmsession_pal_k->BackColor = System::Drawing::Color::White;
		this->d_msg_gmsession_pal_k->Controls->Add(this->e_msg_gmsession_b_pal_k);
		this->d_msg_gmsession_pal_k->Controls->Add(this->e_msg_gmsession_t_pal_k);
		this->d_msg_gmsession_pal_k->Dock = System::Windows::Forms::DockStyle::Left;
		this->d_msg_gmsession_pal_k->Location = System::Drawing::Point(3, 3);
		this->d_msg_gmsession_pal_k->Name = L"d_msg_gmsession_pal_k";
		this->d_msg_gmsession_pal_k->Size = System::Drawing::Size(451, 440);
		this->d_msg_gmsession_pal_k->TabIndex = 9;
		// 
		// e_msg_gmsession_b_pal_k
		// 
		this->e_msg_gmsession_b_pal_k->Controls->Add(this->e_msg_gmsession_person_chk_k);
		this->e_msg_gmsession_b_pal_k->Controls->Add(this->e_msg_gmsession_l_box_k);
		this->e_msg_gmsession_b_pal_k->Controls->Add(this->e_msg_gmsession_r_box_k);
		this->e_msg_gmsession_b_pal_k->Controls->Add(this->e_msg_gmsession_send_btn_k);
		this->e_msg_gmsession_b_pal_k->Controls->Add(this->e_msg_gmsession_person_btn_k);
		this->e_msg_gmsession_b_pal_k->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->e_msg_gmsession_b_pal_k->Location = System::Drawing::Point(0, 407);
		this->e_msg_gmsession_b_pal_k->Name = L"e_msg_gmsession_b_pal_k";
		this->e_msg_gmsession_b_pal_k->Size = System::Drawing::Size(451, 33);
		this->e_msg_gmsession_b_pal_k->TabIndex = 8;
		// 
		// e_msg_gmsession_person_chk_k
		// 
		this->e_msg_gmsession_person_chk_k->AutoSize = true;
		this->e_msg_gmsession_person_chk_k->Location = System::Drawing::Point(238, 7);
		this->e_msg_gmsession_person_chk_k->Name = L"e_msg_gmsession_person_chk_k";
		this->e_msg_gmsession_person_chk_k->Size = System::Drawing::Size(90, 16);
		this->e_msg_gmsession_person_chk_k->TabIndex = 6;
		this->e_msg_gmsession_person_chk_k->Text = L"auto answer";
		this->e_msg_gmsession_person_chk_k->UseVisualStyleBackColor = true;
		this->e_msg_gmsession_person_chk_k->CheckedChanged += gcnew System::EventHandler(this, &MainForm::e_msg_gmsession_person_chk_k_CheckedChanged);
		// 
		// e_msg_gmsession_l_box_k
		// 
		this->e_msg_gmsession_l_box_k->Location = System::Drawing::Point(3, 3);
		this->e_msg_gmsession_l_box_k->Name = L"e_msg_gmsession_l_box_k";
		this->e_msg_gmsession_l_box_k->ReadOnly = true;
		this->e_msg_gmsession_l_box_k->Size = System::Drawing::Size(65, 21);
		this->e_msg_gmsession_l_box_k->TabIndex = 4;
		// 
		// e_msg_gmsession_r_box_k
		// 
		this->e_msg_gmsession_r_box_k->Location = System::Drawing::Point(74, 3);
		this->e_msg_gmsession_r_box_k->Name = L"e_msg_gmsession_r_box_k";
		this->e_msg_gmsession_r_box_k->Size = System::Drawing::Size(158, 21);
		this->e_msg_gmsession_r_box_k->TabIndex = 4;
		// 
		// e_msg_gmsession_send_btn_k
		// 
		this->e_msg_gmsession_send_btn_k->Location = System::Drawing::Point(394, 3);
		this->e_msg_gmsession_send_btn_k->Name = L"e_msg_gmsession_send_btn_k";
		this->e_msg_gmsession_send_btn_k->Size = System::Drawing::Size(54, 23);
		this->e_msg_gmsession_send_btn_k->TabIndex = 5;
		this->e_msg_gmsession_send_btn_k->Text = L"send";
		this->e_msg_gmsession_send_btn_k->UseVisualStyleBackColor = true;
		this->e_msg_gmsession_send_btn_k->Click += gcnew System::EventHandler(this, &MainForm::e_msg_gmsession_send_btn_k_Click);
		// 
		// e_msg_gmsession_person_btn_k
		// 
		this->e_msg_gmsession_person_btn_k->Location = System::Drawing::Point(334, 3);
		this->e_msg_gmsession_person_btn_k->Name = L"e_msg_gmsession_person_btn_k";
		this->e_msg_gmsession_person_btn_k->Size = System::Drawing::Size(54, 23);
		this->e_msg_gmsession_person_btn_k->TabIndex = 5;
		this->e_msg_gmsession_person_btn_k->Text = L"personal";
		this->e_msg_gmsession_person_btn_k->UseVisualStyleBackColor = true;
		this->e_msg_gmsession_person_btn_k->Click += gcnew System::EventHandler(this, &MainForm::e_msg_gmsession_person_btn_k_Click);
		// 
		// e_msg_gmsession_t_pal_k
		// 
		this->e_msg_gmsession_t_pal_k->BackColor = System::Drawing::SystemColors::ControlLight;
		this->e_msg_gmsession_t_pal_k->Controls->Add(this->e_msg_gmsession_l_group_k);
		this->e_msg_gmsession_t_pal_k->Controls->Add(this->e_msg_gmsession_r_group_k);
		this->e_msg_gmsession_t_pal_k->Dock = System::Windows::Forms::DockStyle::Top;
		this->e_msg_gmsession_t_pal_k->Location = System::Drawing::Point(0, 0);
		this->e_msg_gmsession_t_pal_k->Name = L"e_msg_gmsession_t_pal_k";
		this->e_msg_gmsession_t_pal_k->Size = System::Drawing::Size(451, 404);
		this->e_msg_gmsession_t_pal_k->TabIndex = 7;
		// 
		// e_msg_gmsession_l_group_k
		// 
		this->e_msg_gmsession_l_group_k->Controls->Add(this->e_msg_gmsession_server_list_k);
		this->e_msg_gmsession_l_group_k->Dock = System::Windows::Forms::DockStyle::Left;
		this->e_msg_gmsession_l_group_k->Location = System::Drawing::Point(0, 0);
		this->e_msg_gmsession_l_group_k->Name = L"e_msg_gmsession_l_group_k";
		this->e_msg_gmsession_l_group_k->Size = System::Drawing::Size(147, 404);
		this->e_msg_gmsession_l_group_k->TabIndex = 6;
		this->e_msg_gmsession_l_group_k->TabStop = false;
		this->e_msg_gmsession_l_group_k->Text = L"server";
		// 
		// e_msg_gmsession_server_list_k
		// 
		this->e_msg_gmsession_server_list_k->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->e_msg_gmsession_server_column_region_name_k, 
			this->e_msg_gmsession_server_column_region_id_k});
		this->e_msg_gmsession_server_list_k->Dock = System::Windows::Forms::DockStyle::Fill;
		this->e_msg_gmsession_server_list_k->FullRowSelect = true;
		this->e_msg_gmsession_server_list_k->GridLines = true;
		this->e_msg_gmsession_server_list_k->HideSelection = false;
		this->e_msg_gmsession_server_list_k->Location = System::Drawing::Point(3, 17);
		this->e_msg_gmsession_server_list_k->Name = L"e_msg_gmsession_server_list_k";
		this->e_msg_gmsession_server_list_k->Size = System::Drawing::Size(141, 384);
		this->e_msg_gmsession_server_list_k->TabIndex = 2;
		this->e_msg_gmsession_server_list_k->UseCompatibleStateImageBehavior = false;
		this->e_msg_gmsession_server_list_k->View = System::Windows::Forms::View::Details;
		this->e_msg_gmsession_server_list_k->DoubleClick += gcnew System::EventHandler(this, &MainForm::e_msg_gmsession_server_list_k_DoubleClick);
		// 
		// e_msg_gmsession_server_column_region_name_k
		// 
		this->e_msg_gmsession_server_column_region_name_k->Text = L"region_name";
		this->e_msg_gmsession_server_column_region_name_k->Width = 70;
		// 
		// e_msg_gmsession_server_column_region_id_k
		// 
		this->e_msg_gmsession_server_column_region_id_k->Text = L"region_id";
		this->e_msg_gmsession_server_column_region_id_k->Width = 82;
		// 
		// e_msg_gmsession_r_group_k
		// 
		this->e_msg_gmsession_r_group_k->Controls->Add(this->e_msg_gmsession_server_session_list_k);
		this->e_msg_gmsession_r_group_k->Dock = System::Windows::Forms::DockStyle::Right;
		this->e_msg_gmsession_r_group_k->Location = System::Drawing::Point(168, 0);
		this->e_msg_gmsession_r_group_k->Name = L"e_msg_gmsession_r_group_k";
		this->e_msg_gmsession_r_group_k->Size = System::Drawing::Size(283, 404);
		this->e_msg_gmsession_r_group_k->TabIndex = 6;
		this->e_msg_gmsession_r_group_k->TabStop = false;
		this->e_msg_gmsession_r_group_k->Text = L"session";
		// 
		// e_msg_gmsession_server_session_list_k
		// 
		this->e_msg_gmsession_server_session_list_k->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->e_msg_gmsession_column_plyname_k, 
			this->e_msg_gmsession_column_content_k});
		this->e_msg_gmsession_server_session_list_k->Dock = System::Windows::Forms::DockStyle::Fill;
		this->e_msg_gmsession_server_session_list_k->FullRowSelect = true;
		this->e_msg_gmsession_server_session_list_k->GridLines = true;
		this->e_msg_gmsession_server_session_list_k->HideSelection = false;
		this->e_msg_gmsession_server_session_list_k->Location = System::Drawing::Point(3, 17);
		this->e_msg_gmsession_server_session_list_k->Name = L"e_msg_gmsession_server_session_list_k";
		this->e_msg_gmsession_server_session_list_k->Size = System::Drawing::Size(277, 384);
		this->e_msg_gmsession_server_session_list_k->TabIndex = 3;
		this->e_msg_gmsession_server_session_list_k->UseCompatibleStateImageBehavior = false;
		this->e_msg_gmsession_server_session_list_k->View = System::Windows::Forms::View::Details;
		this->e_msg_gmsession_server_session_list_k->DoubleClick += gcnew System::EventHandler(this, &MainForm::e_msg_gmsession_server_session_list_k_DoubleClick);
		// 
		// e_msg_gmsession_column_plyname_k
		// 
		this->e_msg_gmsession_column_plyname_k->Text = L"ply";
		this->e_msg_gmsession_column_plyname_k->Width = 91;
		// 
		// e_msg_gmsession_column_content_k
		// 
		this->e_msg_gmsession_column_content_k->Text = L"content";
		this->e_msg_gmsession_column_content_k->Width = 500;
		// 
		// c_msg_private_reply_pag_k
		// 
		this->c_msg_private_reply_pag_k->Controls->Add(this->d_msg_privatereply_pal_k);
		this->c_msg_private_reply_pag_k->Location = System::Drawing::Point(4, 21);
		this->c_msg_private_reply_pag_k->Name = L"c_msg_private_reply_pag_k";
		this->c_msg_private_reply_pag_k->Padding = System::Windows::Forms::Padding(3);
		this->c_msg_private_reply_pag_k->Size = System::Drawing::Size(451, 446);
		this->c_msg_private_reply_pag_k->TabIndex = 2;
		this->c_msg_private_reply_pag_k->Text = L"pri reply";
		this->c_msg_private_reply_pag_k->UseVisualStyleBackColor = true;
		// 
		// d_msg_privatereply_pal_k
		// 
		this->d_msg_privatereply_pal_k->BackColor = System::Drawing::SystemColors::ControlLight;
		this->d_msg_privatereply_pal_k->Controls->Add(this->e_msg_privatereply_b_pal_k);
		this->d_msg_privatereply_pal_k->Controls->Add(this->e_msg_privatereply_t_pal_k);
		this->d_msg_privatereply_pal_k->Dock = System::Windows::Forms::DockStyle::Left;
		this->d_msg_privatereply_pal_k->Location = System::Drawing::Point(3, 3);
		this->d_msg_privatereply_pal_k->Name = L"d_msg_privatereply_pal_k";
		this->d_msg_privatereply_pal_k->Size = System::Drawing::Size(448, 440);
		this->d_msg_privatereply_pal_k->TabIndex = 6;
		// 
		// e_msg_privatereply_b_pal_k
		// 
		this->e_msg_privatereply_b_pal_k->Controls->Add(this->e_msg_privatereply_l_group_k);
		this->e_msg_privatereply_b_pal_k->Controls->Add(this->e_msg_privatereply_r_group_k);
		this->e_msg_privatereply_b_pal_k->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->e_msg_privatereply_b_pal_k->Location = System::Drawing::Point(0, 57);
		this->e_msg_privatereply_b_pal_k->Name = L"e_msg_privatereply_b_pal_k";
		this->e_msg_privatereply_b_pal_k->Size = System::Drawing::Size(448, 383);
		this->e_msg_privatereply_b_pal_k->TabIndex = 6;
		// 
		// e_msg_privatereply_l_group_k
		// 
		this->e_msg_privatereply_l_group_k->Controls->Add(this->f_msg_privatereply_b_pal_k);
		this->e_msg_privatereply_l_group_k->Controls->Add(this->e_msg_privatereply_tab_k);
		this->e_msg_privatereply_l_group_k->Dock = System::Windows::Forms::DockStyle::Left;
		this->e_msg_privatereply_l_group_k->Location = System::Drawing::Point(0, 0);
		this->e_msg_privatereply_l_group_k->Name = L"e_msg_privatereply_l_group_k";
		this->e_msg_privatereply_l_group_k->Size = System::Drawing::Size(329, 383);
		this->e_msg_privatereply_l_group_k->TabIndex = 0;
		this->e_msg_privatereply_l_group_k->TabStop = false;
		this->e_msg_privatereply_l_group_k->Text = L"session";
		// 
		// f_msg_privatereply_b_pal_k
		// 
		this->f_msg_privatereply_b_pal_k->Controls->Add(this->f_msg_privatereply_send_chk_k);
		this->f_msg_privatereply_b_pal_k->Controls->Add(this->c_msg_pri_content_edit_k);
		this->f_msg_privatereply_b_pal_k->Controls->Add(this->f_msg_privatereply_send_btn_k);
		this->f_msg_privatereply_b_pal_k->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->f_msg_privatereply_b_pal_k->Location = System::Drawing::Point(3, 344);
		this->f_msg_privatereply_b_pal_k->Name = L"f_msg_privatereply_b_pal_k";
		this->f_msg_privatereply_b_pal_k->Size = System::Drawing::Size(323, 36);
		this->f_msg_privatereply_b_pal_k->TabIndex = 3;
		// 
		// f_msg_privatereply_send_chk_k
		// 
		this->f_msg_privatereply_send_chk_k->AutoSize = true;
		this->f_msg_privatereply_send_chk_k->Location = System::Drawing::Point(157, 10);
		this->f_msg_privatereply_send_chk_k->Name = L"f_msg_privatereply_send_chk_k";
		this->f_msg_privatereply_send_chk_k->Size = System::Drawing::Size(90, 16);
		this->f_msg_privatereply_send_chk_k->TabIndex = 3;
		this->f_msg_privatereply_send_chk_k->Text = L"auto answer";
		this->f_msg_privatereply_send_chk_k->UseVisualStyleBackColor = true;
		this->f_msg_privatereply_send_chk_k->CheckedChanged += gcnew System::EventHandler(this, &MainForm::f_msg_privatereply_send_chk_k_CheckedChanged);
		// 
		// c_msg_pri_content_edit_k
		// 
		this->c_msg_pri_content_edit_k->Location = System::Drawing::Point(3, 7);
		this->c_msg_pri_content_edit_k->Name = L"c_msg_pri_content_edit_k";
		this->c_msg_pri_content_edit_k->Size = System::Drawing::Size(148, 21);
		this->c_msg_pri_content_edit_k->TabIndex = 1;
		// 
		// f_msg_privatereply_send_btn_k
		// 
		this->f_msg_privatereply_send_btn_k->Location = System::Drawing::Point(250, 6);
		this->f_msg_privatereply_send_btn_k->Name = L"f_msg_privatereply_send_btn_k";
		this->f_msg_privatereply_send_btn_k->Size = System::Drawing::Size(70, 23);
		this->f_msg_privatereply_send_btn_k->TabIndex = 0;
		this->f_msg_privatereply_send_btn_k->Text = L"send";
		this->f_msg_privatereply_send_btn_k->UseVisualStyleBackColor = true;
		this->f_msg_privatereply_send_btn_k->Click += gcnew System::EventHandler(this, &MainForm::f_msg_privatereply_send_btn_k_Click);
		// 
		// e_msg_privatereply_tab_k
		// 
		this->e_msg_privatereply_tab_k->Dock = System::Windows::Forms::DockStyle::Top;
		this->e_msg_privatereply_tab_k->Location = System::Drawing::Point(3, 17);
		this->e_msg_privatereply_tab_k->Name = L"e_msg_privatereply_tab_k";
		this->e_msg_privatereply_tab_k->SelectedIndex = 0;
		this->e_msg_privatereply_tab_k->Size = System::Drawing::Size(323, 324);
		this->e_msg_privatereply_tab_k->TabIndex = 2;
		this->e_msg_privatereply_tab_k->DoubleClick += gcnew System::EventHandler(this, &MainForm::e_msg_privatereply_tab_k_DoubleClick);
		this->e_msg_privatereply_tab_k->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::e_msg_privatereply_tab_k_SelectedIndexChanged);
		// 
		// e_msg_privatereply_r_group_k
		// 
		this->e_msg_privatereply_r_group_k->Controls->Add(this->e_msg_privatereply_list_k);
		this->e_msg_privatereply_r_group_k->Dock = System::Windows::Forms::DockStyle::Right;
		this->e_msg_privatereply_r_group_k->Location = System::Drawing::Point(323, 0);
		this->e_msg_privatereply_r_group_k->Name = L"e_msg_privatereply_r_group_k";
		this->e_msg_privatereply_r_group_k->Size = System::Drawing::Size(125, 383);
		this->e_msg_privatereply_r_group_k->TabIndex = 1;
		this->e_msg_privatereply_r_group_k->TabStop = false;
		this->e_msg_privatereply_r_group_k->Text = L"common dialogue";
		// 
		// e_msg_privatereply_list_k
		// 
		this->e_msg_privatereply_list_k->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->e_msg_sensword_commom_chat_k});
		this->e_msg_privatereply_list_k->Dock = System::Windows::Forms::DockStyle::Fill;
		this->e_msg_privatereply_list_k->FullRowSelect = true;
		this->e_msg_privatereply_list_k->GridLines = true;
		this->e_msg_privatereply_list_k->HideSelection = false;
		this->e_msg_privatereply_list_k->Location = System::Drawing::Point(3, 17);
		this->e_msg_privatereply_list_k->Name = L"e_msg_privatereply_list_k";
		this->e_msg_privatereply_list_k->Size = System::Drawing::Size(119, 363);
		this->e_msg_privatereply_list_k->TabIndex = 0;
		this->e_msg_privatereply_list_k->UseCompatibleStateImageBehavior = false;
		this->e_msg_privatereply_list_k->View = System::Windows::Forms::View::Details;
		this->e_msg_privatereply_list_k->DoubleClick += gcnew System::EventHandler(this, &MainForm::e_msg_privatereply_list_k_DoubleClick);
		// 
		// e_msg_sensword_commom_chat_k
		// 
		this->e_msg_sensword_commom_chat_k->Text = L"comm dialogue";
		this->e_msg_sensword_commom_chat_k->Width = 120;
		// 
		// e_msg_privatereply_t_pal_k
		// 
		this->e_msg_privatereply_t_pal_k->Controls->Add(this->c_msg_pri_region_comb_k);
		this->e_msg_privatereply_t_pal_k->Controls->Add(this->c_msg_pri_add_btn_k);
		this->e_msg_privatereply_t_pal_k->Controls->Add(this->c_msg_pri_region_lab_k);
		this->e_msg_privatereply_t_pal_k->Controls->Add(this->c_msg_pri_character_comb_k);
		this->e_msg_privatereply_t_pal_k->Controls->Add(this->c_msg_pri_character_lab_k);
		this->e_msg_privatereply_t_pal_k->Dock = System::Windows::Forms::DockStyle::Top;
		this->e_msg_privatereply_t_pal_k->Location = System::Drawing::Point(0, 0);
		this->e_msg_privatereply_t_pal_k->Name = L"e_msg_privatereply_t_pal_k";
		this->e_msg_privatereply_t_pal_k->Size = System::Drawing::Size(448, 43);
		this->e_msg_privatereply_t_pal_k->TabIndex = 5;
		// 
		// c_msg_pri_region_comb_k
		// 
		this->c_msg_pri_region_comb_k->FormattingEnabled = true;
		this->c_msg_pri_region_comb_k->Location = System::Drawing::Point(62, 18);
		this->c_msg_pri_region_comb_k->Name = L"c_msg_pri_region_comb_k";
		this->c_msg_pri_region_comb_k->Size = System::Drawing::Size(113, 20);
		this->c_msg_pri_region_comb_k->TabIndex = 3;
		// 
		// c_msg_pri_add_btn_k
		// 
		this->c_msg_pri_add_btn_k->Location = System::Drawing::Point(396, 16);
		this->c_msg_pri_add_btn_k->Name = L"c_msg_pri_add_btn_k";
		this->c_msg_pri_add_btn_k->Size = System::Drawing::Size(75, 23);
		this->c_msg_pri_add_btn_k->TabIndex = 4;
		this->c_msg_pri_add_btn_k->Text = L"add";
		this->c_msg_pri_add_btn_k->UseVisualStyleBackColor = true;
		this->c_msg_pri_add_btn_k->Click += gcnew System::EventHandler(this, &MainForm::c_msg_pri_add_btn_k_Click);
		// 
		// c_msg_pri_region_lab_k
		// 
		this->c_msg_pri_region_lab_k->AutoSize = true;
		this->c_msg_pri_region_lab_k->Location = System::Drawing::Point(13, 21);
		this->c_msg_pri_region_lab_k->Name = L"c_msg_pri_region_lab_k";
		this->c_msg_pri_region_lab_k->Size = System::Drawing::Size(47, 12);
		this->c_msg_pri_region_lab_k->TabIndex = 2;
		this->c_msg_pri_region_lab_k->Text = L"region:";
		// 
		// c_msg_pri_character_comb_k
		// 
		this->c_msg_pri_character_comb_k->FormattingEnabled = true;
		this->c_msg_pri_character_comb_k->Location = System::Drawing::Point(253, 18);
		this->c_msg_pri_character_comb_k->Name = L"c_msg_pri_character_comb_k";
		this->c_msg_pri_character_comb_k->Size = System::Drawing::Size(121, 20);
		this->c_msg_pri_character_comb_k->TabIndex = 3;
		// 
		// c_msg_pri_character_lab_k
		// 
		this->c_msg_pri_character_lab_k->AutoSize = true;
		this->c_msg_pri_character_lab_k->Location = System::Drawing::Point(185, 22);
		this->c_msg_pri_character_lab_k->Name = L"c_msg_pri_character_lab_k";
		this->c_msg_pri_character_lab_k->Size = System::Drawing::Size(65, 12);
		this->c_msg_pri_character_lab_k->TabIndex = 2;
		this->c_msg_pri_character_lab_k->Text = L"character:";
		// 
		// b_navi_pal_left
		// 
		this->b_navi_pal_left->Controls->Add(this->b_navi_tree);
		this->b_navi_pal_left->Dock = System::Windows::Forms::DockStyle::Left;
		this->b_navi_pal_left->Location = System::Drawing::Point(0, 0);
		this->b_navi_pal_left->Name = L"b_navi_pal_left";
		this->b_navi_pal_left->Size = System::Drawing::Size(134, 502);
		this->b_navi_pal_left->TabIndex = 2;
		// 
		// b_navi_tree
		// 
		this->b_navi_tree->Dock = System::Windows::Forms::DockStyle::Fill;
		this->b_navi_tree->Location = System::Drawing::Point(0, 0);
		this->b_navi_tree->Name = L"b_navi_tree";
		treeNode1->Name = L"op_move";
		treeNode1->Tag = L"0";
		treeNode1->Text = L"move";
		treeNode2->Name = L"op_chat";
		treeNode2->Tag = L"1";
		treeNode2->Text = L"chat";
		treeNode3->Name = L"op_kick";
		treeNode3->Tag = L"2";
		treeNode3->Text = L"kick";
		treeNode4->Name = L"op_item";
		treeNode4->Tag = L"3";
		treeNode4->Text = L"item";
		treeNode5->Name = L"op_npc";
		treeNode5->Tag = L"4";
		treeNode5->Text = L"npc";
		treeNode6->Name = L"op_hidden";
		treeNode6->Tag = L"5";
		treeNode6->Text = L"hidden";
		treeNode7->Name = L"op_gm_player";
		treeNode7->Tag = L"6";
		treeNode7->Text = L"gm_player";
		treeNode8->Name = L"op_state";
		treeNode8->Tag = L"7";
		treeNode8->Text = L"state";
		treeNode9->Name = L"op_kill";
		treeNode9->Tag = L"18";
		treeNode9->Text = L"kill";
		treeNode10->Name = L"fold_player";
		treeNode10->Tag = L"-1";
		treeNode10->Text = L"player";
		treeNode11->Name = L"op_post";
		treeNode11->Tag = L"8";
		treeNode11->Text = L"post";
		treeNode12->Name = L"op_senstive";
		treeNode12->Tag = L"9";
		treeNode12->Text = L"senstive";
		treeNode13->Name = L"op_reply";
		treeNode13->Tag = L"10";
		treeNode13->Text = L"reply";
		treeNode14->Name = L"fold_message";
		treeNode14->Tag = L"-1";
		treeNode14->Text = L"message";
		treeNode15->Name = L"op_post_k";
		treeNode15->Tag = L"14";
		treeNode15->Text = L"post";
		treeNode16->Name = L"op_senstive_k";
		treeNode16->Tag = L"15";
		treeNode16->Text = L"senstive";
		treeNode17->Name = L"op_reply_k";
		treeNode17->Tag = L"16";
		treeNode17->Text = L"reply";
		treeNode18->Name = L"op_gmsenstive_k";
		treeNode18->Tag = L"17";
		treeNode18->Text = L"gmsession";
		treeNode19->Name = L"fold_message_k";
		treeNode19->Text = L"message";
		treeNode20->Name = L"op_server_state";
		treeNode20->Tag = L"11";
		treeNode20->Text = L"state";
		treeNode21->Name = L"fold_server";
		treeNode21->Tag = L"-1";
		treeNode21->Text = L"server";
		treeNode22->Name = L"op_gm_manager";
		treeNode22->Tag = L"12";
		treeNode22->Text = L"manager";
		treeNode23->Name = L"op_gm_log";
		treeNode23->Tag = L"13";
		treeNode23->Text = L"log";
		treeNode24->Name = L"fold_account";
		treeNode24->Tag = L"-1";
		treeNode24->Text = L"account";
		this->b_navi_tree->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(5) {treeNode10, treeNode14, treeNode19, 
			treeNode21, treeNode24});
		this->b_navi_tree->Size = System::Drawing::Size(134, 502);
		this->b_navi_tree->TabIndex = 8;
		this->b_navi_tree->NodeMouseDoubleClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::b_navi_tree_NodeMouseDoubleClick);
		this->b_navi_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::b_navi_tree_AfterSelect);
		// 
		// a_spl_center
		// 
		this->a_spl_center->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->a_spl_center->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->a_spl_center->Location = System::Drawing::Point(0, 502);
		this->a_spl_center->Name = L"a_spl_center";
		this->a_spl_center->Size = System::Drawing::Size(792, 2);
		this->a_spl_center->TabIndex = 5;
		this->a_spl_center->TabStop = false;
		// 
		// a_pal_bottom
		// 
		this->a_pal_bottom->Controls->Add(this->a_list_msg);
		this->a_pal_bottom->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->a_pal_bottom->Location = System::Drawing::Point(0, 504);
		this->a_pal_bottom->Name = L"a_pal_bottom";
		this->a_pal_bottom->Size = System::Drawing::Size(792, 62);
		this->a_pal_bottom->TabIndex = 4;
		// 
		// a_list_msg
		// 
		this->a_list_msg->AllowColumnReorder = true;
		this->a_list_msg->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->log_column_time, 
			this->log_column_log});
		this->a_list_msg->Dock = System::Windows::Forms::DockStyle::Fill;
		this->a_list_msg->FullRowSelect = true;
		this->a_list_msg->GridLines = true;
		this->a_list_msg->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->a_list_msg->HideSelection = false;
		this->a_list_msg->Location = System::Drawing::Point(0, 0);
		this->a_list_msg->Name = L"a_list_msg";
		this->a_list_msg->Size = System::Drawing::Size(792, 62);
		this->a_list_msg->Sorting = System::Windows::Forms::SortOrder::Descending;
		this->a_list_msg->TabIndex = 7;
		this->a_list_msg->UseCompatibleStateImageBehavior = false;
		this->a_list_msg->View = System::Windows::Forms::View::Details;
		this->a_list_msg->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::a_list_msg_MouseDoubleClick);
		this->a_list_msg->DoubleClick += gcnew System::EventHandler(this, &MainForm::a_list_msg_DoubleClick);
		// 
		// log_column_time
		// 
		this->log_column_time->Text = L"time";
		this->log_column_time->Width = 120;
		// 
		// log_column_log
		// 
		this->log_column_log->Text = L"log";
		this->log_column_log->Width = 600;
		// 
		// MainForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(792, 566);
		this->Controls->Add(this->a_main_pal);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
		this->Name = L"MainForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"GMTool";
		this->SizeChanged += gcnew System::EventHandler(this, &MainForm::MainForm_SizeChanged);
		this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
		this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
		this->a_main_pal->ResumeLayout(false);
		this->a_pal_full->ResumeLayout(false);
		this->b_main_pal_right->ResumeLayout(false);
		this->b_main_tab->ResumeLayout(false);
		this->c_palyer_pag->ResumeLayout(false);
		this->c_player_pal->ResumeLayout(false);
		this->c_palyer_main_pal->ResumeLayout(false);
		this->c_player_tab->ResumeLayout(false);
		this->c_player_move_pag->ResumeLayout(false);
		this->c_player_move_pal->ResumeLayout(false);
		this->d_pm_pal->ResumeLayout(false);
		this->d_pm_position_gbo_k->ResumeLayout(false);
		this->d_pm_position_gbo_k->PerformLayout();
		this->d_pm_position_gbo->ResumeLayout(false);
		this->d_pm_position_gbo->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pm_coord_z_num))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pm_coord_y_num))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pm_coord_x_num))->EndInit();
		this->d_pm_config_gbo->ResumeLayout(false);
		this->d_pm_config_gbo->PerformLayout();
		this->d_pm_commit_gbo->ResumeLayout(false);
		this->c_player_chat_pag->ResumeLayout(false);
		this->c_player_chat_pal->ResumeLayout(false);
		this->d_pc_pal->ResumeLayout(false);
		this->d_pc_player_info_gbo->ResumeLayout(false);
		this->d_pc_player_info_gbo->PerformLayout();
		this->d_pc_record_gbo->ResumeLayout(false);
		this->d_pc_filter_pnl->ResumeLayout(false);
		this->d_pc_filter_pnl->PerformLayout();
		this->d_pc_commit_gbo->ResumeLayout(false);
		this->d_pc_forbid_gbo->ResumeLayout(false);
		this->d_pc_forbid_gbo->PerformLayout();
		this->c_player_kick_pag->ResumeLayout(false);
		this->c_player_kick_pal->ResumeLayout(false);
		this->d_pk_pal->ResumeLayout(false);
		this->d_pk_player_info_gbo->ResumeLayout(false);
		this->d_pk_player_info_gbo->PerformLayout();
		this->d_pk_record_gbo->ResumeLayout(false);
		this->d_pk_record_pnl->ResumeLayout(false);
		this->d_pk_record_pnl->PerformLayout();
		this->d_pk_commit_gbo->ResumeLayout(false);
		this->d_pk_forbid_gbo->ResumeLayout(false);
		this->d_pk_forbid_gbo->PerformLayout();
		this->c_player_item_pag->ResumeLayout(false);
		this->c_player_item_pal->ResumeLayout(false);
		this->d_pi_pal->ResumeLayout(false);
		this->d_pi_config_gbo->ResumeLayout(false);
		this->d_pi_config_tab->ResumeLayout(false);
		this->d_pi_single_pag->ResumeLayout(false);
		this->d_pi_single_pag->PerformLayout();
		this->d_pi_group_pag->ResumeLayout(false);
		this->d_pi_commit_gbo->ResumeLayout(false);
		this->d_pi_item_info_gbo->ResumeLayout(false);
		this->d_pi_type_tab->ResumeLayout(false);
		this->d_pi_item_pag->ResumeLayout(false);
		this->d_pi_item_pag->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->d_pi_number_num))->EndInit();
		this->d_pi_money_pag->ResumeLayout(false);
		this->d_pi_money_pag->PerformLayout();
		this->c_player_npc_pag->ResumeLayout(false);
		this->c_player_npc_pal->ResumeLayout(false);
		this->d_pn_pal->ResumeLayout(false);
		this->d_pn_npc_info_gbo->ResumeLayout(false);
		this->d_pn_npc_info_gbo->PerformLayout();
		this->d_pn_record_gbo->ResumeLayout(false);
		this->d_pn_filter_server_pnl->ResumeLayout(false);
		this->d_pn_filter_server_pnl->PerformLayout();
		this->d_pn_commit_gbo->ResumeLayout(false);
		this->d_pn_npc_setting_gbo->ResumeLayout(false);
		this->d_pn_npc_setting_gbo->PerformLayout();
		this->c_player_hidden_pag->ResumeLayout(false);
		this->c_player_hidden_pal->ResumeLayout(false);
		this->d_ph_pal->ResumeLayout(false);
		this->d_ph_record_gbo->ResumeLayout(false);
		this->d_ph_record_pnl->ResumeLayout(false);
		this->d_ph_record_pnl->PerformLayout();
		this->d_ph_config_gbo->ResumeLayout(false);
		this->d_ph_config_gbo->PerformLayout();
		this->d_ph_commit_gbo->ResumeLayout(false);
		this->d_ph_hidden_gbo->ResumeLayout(false);
		this->d_ph_hidden_gbo->PerformLayout();
		this->c_player_state_pag->ResumeLayout(false);
		this->d_ps_pal->ResumeLayout(false);
		this->d_ps_config_gbo->ResumeLayout(false);
		this->d_ps_config_gbo->PerformLayout();
		this->d_ps_state_gbo->ResumeLayout(false);
		this->d_ps_state_tab->ResumeLayout(false);
		this->d_ps_property_pag->ResumeLayout(false);
		this->d_ps_property_pag->PerformLayout();
		this->d_ps_equip_pag->ResumeLayout(false);
		this->d_ps_state_equip_tab->ResumeLayout(false);
		this->d_ps_bag_pag->ResumeLayout(false);
		this->d_ps_skill_pag->ResumeLayout(false);
		this->d_ps_task_pag->ResumeLayout(false);
		this->c_gm_player_pag->ResumeLayout(false);
		this->c_gm_player_pal->ResumeLayout(false);
		this->d_pg_pal->ResumeLayout(false);
		this->d_pg_record_gbo->ResumeLayout(false);
		this->panel1->ResumeLayout(false);
		this->panel1->PerformLayout();
		this->d_pg_config_gbo->ResumeLayout(false);
		this->d_pg_config_gbo->PerformLayout();
		this->d_pg_commit_gbo->ResumeLayout(false);
		this->d_pg_setting_gbo->ResumeLayout(false);
		this->d_pg_setting_gbo->PerformLayout();
		this->c_player_kill_npc_pag->ResumeLayout(false);
		this->c_player_kill_npc_pal->ResumeLayout(false);
		this->d_pkl_pal->ResumeLayout(false);
		this->d_pkl_commit_gbo->ResumeLayout(false);
		this->d_pkl_config_gbo->ResumeLayout(false);
		this->d_pkl_config_gbo->PerformLayout();
		this->c_player_left_pal->ResumeLayout(false);
		this->c_player_search_tab->ResumeLayout(false);
		this->c_player_search_player_pag->ResumeLayout(false);
		this->c_player_search_player_pal->ResumeLayout(false);
		this->c_player_search_player_list_pal->ResumeLayout(false);
		this->c_player_search_player_op_pal->ResumeLayout(false);
		this->c_player_search_player_filter_pal->ResumeLayout(false);
		this->c_player_search_player_filter_pal->PerformLayout();
		this->c_player_search_player_gbo->ResumeLayout(false);
		this->c_player_search_player_gbo->PerformLayout();
		this->c_player_search_npc_pag->ResumeLayout(false);
		this->c_player_search_npc_pal->ResumeLayout(false);
		this->c_player_search_npc_list_pal->ResumeLayout(false);
		this->c_player_search_npc_op_pal->ResumeLayout(false);
		this->c_player_search_npc_filter_pal->ResumeLayout(false);
		this->c_player_search_npc_gbo->ResumeLayout(false);
		this->c_player_search_npc_gbo->PerformLayout();
		this->c_player_search_item_pag->ResumeLayout(false);
		this->c_player_search_item_pal->ResumeLayout(false);
		this->c_player_search_item_list_pal->ResumeLayout(false);
		this->c_player_search_item_op_pal->ResumeLayout(false);
		this->c_player_search_item_filter_pal->ResumeLayout(false);
		this->c_player_search_item_gbo->ResumeLayout(false);
		this->c_player_search_item_gbo->PerformLayout();
		this->c_msg_pag->ResumeLayout(false);
		this->c_msg_pal->ResumeLayout(false);
		this->c_msg_main_pal->ResumeLayout(false);
		this->c_msg_main_tab->ResumeLayout(false);
		this->c_msg_sensword_pag->ResumeLayout(false);
		this->c_msg_sensword_pal->ResumeLayout(false);
		this->d_ms_pal->ResumeLayout(false);
		this->d_ms_server_gbo->ResumeLayout(false);
		this->d_ms_sensword_gbo->ResumeLayout(false);
		this->c_msg_reply_pag->ResumeLayout(false);
		this->c_msg_reply_pal->ResumeLayout(false);
		this->d_mr_pal->ResumeLayout(false);
		this->d_mr_reply_gbo->ResumeLayout(false);
		this->d_mr_player_info_gbo->ResumeLayout(false);
		this->d_mr_player_info_gbo->PerformLayout();
		this->d_mr_common_reply_gbo->ResumeLayout(false);
		this->d_mr_one_reply_gbo->ResumeLayout(false);
		this->d_mr_one_question_gbo->ResumeLayout(false);
		this->d_mr_server_gbo->ResumeLayout(false);
		this->d_mr_question_gbo->ResumeLayout(false);
		this->c_msg_server_right_pal->ResumeLayout(false);
		this->c_msg_server_search_tab->ResumeLayout(false);
		this->c_msg_server_right_pag->ResumeLayout(false);
		this->c_msg_server_search_op_pal->ResumeLayout(false);
		this->c_msg_server_search_pal->ResumeLayout(false);
		this->c_server_pag->ResumeLayout(false);
		this->c_server_pal->ResumeLayout(false);
		this->c_ss_server_pal->ResumeLayout(false);
		this->c_account_pag->ResumeLayout(false);
		this->c_account_pal->ResumeLayout(false);
		this->c_account_tab->ResumeLayout(false);
		this->c_account_manager_pag->ResumeLayout(false);
		this->c_account_manager_pal->ResumeLayout(false);
		this->d_am_pal->ResumeLayout(false);
		this->d_am_tab->ResumeLayout(false);
		this->d_am_create_pag->ResumeLayout(false);
		this->d_am_create_pal->ResumeLayout(false);
		this->d_am_user_gbo->ResumeLayout(false);
		this->d_am_user_gbo->PerformLayout();
		this->d_am_commit_gbo->ResumeLayout(false);
		this->d_am_record_pag->ResumeLayout(false);
		this->d_am_record_pal->ResumeLayout(false);
		this->d_am_account_gbo->ResumeLayout(false);
		this->d_am_change_gbo->ResumeLayout(false);
		this->d_am_change_gbo->PerformLayout();
		this->d_am_change_delete_gbo->ResumeLayout(false);
		this->d_am_change_update_gbo->ResumeLayout(false);
		this->d_am_change_info_gbo->ResumeLayout(false);
		this->d_am_change_info_gbo->PerformLayout();
		this->c_account_record_pag->ResumeLayout(false);
		this->c_account_record_pal->ResumeLayout(false);
		this->d_ar_pal->ResumeLayout(false);
		this->d_ar_record_pal->ResumeLayout(false);
		this->d_ar_log_tab->ResumeLayout(false);
		this->d_ar_log_senditem_pag->ResumeLayout(false);
		this->d_ar_si_log_gbo->ResumeLayout(false);
		this->d_ar_si_filter_pal->ResumeLayout(false);
		this->d_ar_si_filter_gbo->ResumeLayout(false);
		this->d_ar_si_filter_gbo->PerformLayout();
		this->d_ar_filter_pal->ResumeLayout(false);
		this->d_ar_filter_gbo->ResumeLayout(false);
		this->d_ar_filter_gbo->PerformLayout();
		this->c_msg_pag_k->ResumeLayout(false);
		this->c_msg_server_pal_k->ResumeLayout(false);
		this->c_msg_server_tab_k->ResumeLayout(false);
		this->c_msg_server_right_pag_k->ResumeLayout(false);
		this->c_msg_tab_k->ResumeLayout(false);
		this->c_msg_post_pag_k->ResumeLayout(false);
		this->c_msg_post_pal->ResumeLayout(false);
		this->d_mp_pal->ResumeLayout(false);
		this->d_mp_tab->ResumeLayout(false);
		this->d_mp_record_pag->ResumeLayout(false);
		this->d_mpr_create_pal->ResumeLayout(false);
		this->d_mpr_server_gbo->ResumeLayout(false);
		this->d_mpr_commit_gbo->ResumeLayout(false);
		this->d_mp_create_pag->ResumeLayout(false);
		this->d_mp_create_pal->ResumeLayout(false);
		this->d_mp_title_gbo->ResumeLayout(false);
		this->d_mp_title_gbo->PerformLayout();
		this->d_mp_commit_gbo->ResumeLayout(false);
		this->d_mp_post_gbo->ResumeLayout(false);
		this->d_mp_post_gbo->PerformLayout();
		this->d_mp_cycle_gbo->ResumeLayout(false);
		this->d_mp_cycle_gbo->PerformLayout();
		this->d_mp_server_gbo->ResumeLayout(false);
		this->d_mp_text_gbo->ResumeLayout(false);
		this->c_msg_sensword_pag_k->ResumeLayout(false);
		this->d_msg_senswords_pal_k->ResumeLayout(false);
		this->e_msg_senswords_r_pal_k->ResumeLayout(false);
		this->e_msg_sensword_group_k->ResumeLayout(false);
		this->f_msg_senswords_b_pal_k->ResumeLayout(false);
		this->d_msg_sensword_group_k->ResumeLayout(false);
		this->c_msg_gmsession_pag_k->ResumeLayout(false);
		this->d_msg_gmsession_pal_k->ResumeLayout(false);
		this->e_msg_gmsession_b_pal_k->ResumeLayout(false);
		this->e_msg_gmsession_b_pal_k->PerformLayout();
		this->e_msg_gmsession_t_pal_k->ResumeLayout(false);
		this->e_msg_gmsession_l_group_k->ResumeLayout(false);
		this->e_msg_gmsession_r_group_k->ResumeLayout(false);
		this->c_msg_private_reply_pag_k->ResumeLayout(false);
		this->d_msg_privatereply_pal_k->ResumeLayout(false);
		this->e_msg_privatereply_b_pal_k->ResumeLayout(false);
		this->e_msg_privatereply_l_group_k->ResumeLayout(false);
		this->f_msg_privatereply_b_pal_k->ResumeLayout(false);
		this->f_msg_privatereply_b_pal_k->PerformLayout();
		this->e_msg_privatereply_r_group_k->ResumeLayout(false);
		this->e_msg_privatereply_t_pal_k->ResumeLayout(false);
		this->e_msg_privatereply_t_pal_k->PerformLayout();
		this->b_navi_pal_left->ResumeLayout(false);
		this->a_pal_bottom->ResumeLayout(false);
		this->ResumeLayout(false);

	}



}