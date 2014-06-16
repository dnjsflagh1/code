#pragma once


namespace MG {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/******************************************************************************/
	//class GMLayout 
	/******************************************************************************/
	enum GMLayout
	{
		GML_Player_Move = 0,
		GML_Player_Chat = 1,
		GML_Player_Kick = 2,
		GML_Player_SendItem = 3,
		GML_Player_Npc = 4,
		GML_Player_Hidden = 5,
		GML_Player_GM   = 6,
		GML_Player_State = 7,

		GML_Msg_Post = 8,
		GML_Msg_SensitiveWord = 9,
		GML_Msg_Reply = 10,

		GML_Server_State = 11,

		GML_Account_Manager = 12,
		GML_Account_OpRecord = 13,

		GML_Msg_Post_K = 14,
		GML_Msg_SensitiveWord_K = 15,
		GML_Msg_Private_Reply_K = 16,
		GML_Msg_GM_Session_K = 17,

		GML_Player_Kill_Npc = 18,
		GML_MAX,
	};
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm();

	public: 
		/*-------------------------------
		//------     Login     --------//
		--------------------------------*/
		//@
		//@  Init
		//@
		void initialize();
		void clearLayout();
		void setLayout(GMLayout gl);

		/*-------------------------------
		//------     Main     --------//
		--------------------------------*/
		//@
		//@  loadGameTextConfig
		//@
		DELEGATEFUNC(loadGameTextConfig)();
		void loadGameTextConfig();
		void loadMainUITextConfig();
		void loadAuthorityConfig();

		
		/*-------------------------------
		//---------     log     --------//
		--------------------------------*/
		DELEGATEFUNC(log)(String^msg);
		void log(String^msg);

	protected: 

	private: System::Windows::Forms::TabPage^		c_msg_pag_k;
	private: System::Windows::Forms::TabControl^	c_msg_server_tab_k;
	private: System::Windows::Forms::TabControl^	c_msg_play_tab_k;//add by king.wang
	private: System::Windows::Forms::TabPage^		c_msg_server_right_pag_k;
	private: System::Windows::Forms::TabControl^	c_msg_tab_k;
	private: System::Windows::Forms::TabPage^		c_msg_post_pag_k;
	private: System::Windows::Forms::TabPage^		c_msg_sensword_pag_k;
	private: System::Windows::Forms::TabPage^		c_msg_private_reply_pag_k;
	private: System::Windows::Forms::TabPage^		c_msg_gmsession_pag_k;
	private: System::Windows::Forms::ListView^		d_msg_server_list_k;
	private: System::Windows::Forms::ColumnHeader^  d_msg_column_region_name_k;
	private: System::Windows::Forms::ColumnHeader^  d_msg_column_region_id_k;
	private: System::Windows::Forms::ListView^		c_msg_sensword_session_list_k;
	private: System::Windows::Forms::ColumnHeader^  c_msg_sensword_column_plyname_k;
	private: System::Windows::Forms::ColumnHeader^  c_msg_sensword_column_content_k;
	private: System::Windows::Forms::Button^		e_msg_gmsession_person_btn_k;
	private: System::Windows::Forms::Button^		e_msg_gmsession_send_btn_k;
	private: System::Windows::Forms::TextBox^		e_msg_gmsession_r_box_k;
	private: System::Windows::Forms::TextBox^		e_msg_gmsession_l_box_k;
	private: System::Windows::Forms::ListView^		e_msg_gmsession_server_session_list_k;
	private: System::Windows::Forms::ColumnHeader^  e_msg_gmsession_column_plyname_k;
	private: System::Windows::Forms::ColumnHeader^  e_msg_gmsession_column_content_k;
	private: System::Windows::Forms::Button^		f_msg_senswords_load_config_k;
	private: System::Windows::Forms::Button^		f_msg_senswords_open_config_k;
	private: System::Windows::Forms::GroupBox^		e_msg_privatereply_l_group_k;
	private: System::Windows::Forms::ListView^		e_msg_privatereply_list_k;
	private: System::Windows::Forms::ListView^		listView2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::GroupBox^		d_msg_sensword_group_k;
	private: System::Windows::Forms::ListView^		c_msg_sensword_server_list_k;
	private: System::Windows::Forms::ColumnHeader^  c_msg_sensword_name_k;
	private: System::Windows::Forms::ColumnHeader^  c_msg_sensword_id_k;
	private: System::Windows::Forms::GroupBox^		e_msg_sensword_group_k;
	private: System::Windows::Forms::GroupBox^		e_msg_gmsession_r_group_k;
	private: System::Windows::Forms::GroupBox^		e_msg_gmsession_l_group_k;
	private: System::Windows::Forms::ListView^		e_msg_gmsession_server_list_k;
	private: System::Windows::Forms::ColumnHeader^  e_msg_gmsession_server_column_region_name_k;
	private: System::Windows::Forms::ColumnHeader^  e_msg_gmsession_server_column_region_id_k;
	private: System::Windows::Forms::GroupBox^		e_msg_privatereply_r_group_k;
	private: System::Windows::Forms::TextBox^		c_msg_pri_content_edit_k;
	private: System::Windows::Forms::Button^		f_msg_privatereply_send_btn_k;
	private: System::Windows::Forms::Label^			c_msg_pri_region_lab_k;
	private: System::Windows::Forms::Button^		c_msg_pri_add_btn_k;
	private: System::Windows::Forms::ComboBox^		c_msg_pri_character_comb_k;
	private: System::Windows::Forms::ComboBox^		c_msg_pri_region_comb_k;
	private: System::Windows::Forms::Label^			c_msg_pri_character_lab_k;
	private: System::Windows::Forms::Panel^			d_msg_senswords_pal_k;
	private: System::Windows::Forms::Panel^			c_msg_server_pal_k;
	private: System::Windows::Forms::Panel^			e_msg_senswords_r_pal_k;
	private: System::Windows::Forms::Panel^			f_msg_senswords_b_pal_k;
	private: System::Windows::Forms::Panel^			e_msg_gmsession_b_pal_k;
	private: System::Windows::Forms::Panel^			e_msg_gmsession_t_pal_k;
	private: System::Windows::Forms::Panel^			d_msg_gmsession_pal_k;
	private: System::Windows::Forms::ColumnHeader^  e_msg_sensword_commom_chat_k;
	private: System::Windows::Forms::TabControl^	e_msg_privatereply_tab_k;
	private: System::Windows::Forms::Panel^			d_msg_privatereply_pal_k;
	private: System::Windows::Forms::Panel^			e_msg_privatereply_t_pal_k;
	private: System::Windows::Forms::Panel^			e_msg_privatereply_b_pal_k;
	private: System::Windows::Forms::Panel^			f_msg_privatereply_b_pal_k;
	private: System::Windows::Forms::CheckBox^		d_mp_pause_ckb;
	private: System::Windows::Forms::CheckBox^		d_mp_repeat_ckb;
	private: System::Windows::Forms::DateTimePicker^d_mp_play_time_end_cbo;
	private: System::Windows::Forms::Label^			d_mp_time_distance_lbl;
	private: System::Windows::Forms::Label^			d_mp_end_time_k_lbl;
	private: System::Windows::Forms::TextBox^		time_distance_box;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_pause;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_repeat;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_end_hours;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_end_minutes;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_time_distance;
	private: System::Windows::Forms::ComboBox^		d_ph_time_cbo;
	private: System::Windows::Forms::Label^			d_ph_time_lbl;
	private: System::Windows::Forms::GroupBox^		d_ph_record_gbo;
	private: System::Windows::Forms::ListView^		d_ph_record_list;
	private: System::Windows::Forms::ColumnHeader^  dph_column_player_name;
	private: System::Windows::Forms::ColumnHeader^  dph_column_end_time;
	private: System::Windows::Forms::Panel^			d_ph_record_pnl;
	private: System::Windows::Forms::Label^			label1;
	private: System::Windows::Forms::ComboBox^		d_ph_filter_server_cbo;
	private: System::Windows::Forms::Label^			d_ph_hour_lbl;
	private: System::Windows::Forms::GroupBox^		d_pm_position_gbo_k;
	private: System::Windows::Forms::ComboBox^		d_pm_move_map_cbx;
	private: System::Windows::Forms::ComboBox^		d_pm_move_pt_cbx;
	private: System::Windows::Forms::Label^			d_pm_jump_pt_lab;
	private: System::Windows::Forms::Label^			d_pm_map_name_lab;
	private: System::Windows::Forms::CheckBox^		d_pi_all_player_cekb;
	private: System::Windows::Forms::TabPage^		c_player_kill_npc_pag;
	private: System::Windows::Forms::Panel^			d_pkl_pal;
	private: System::Windows::Forms::Button^		d_pkl_commit_btn;
	private: System::Windows::Forms::ComboBox^		d_pkl_username_cbo;
	private: System::Windows::Forms::ComboBox^		d_pkl_server_cbo;
	private: System::Windows::Forms::Label^			d_pkl_username_lbl;
	private: System::Windows::Forms::Label^			d_pkl_server_lbl;
	private: System::Windows::Forms::GroupBox^		d_pkl_commit_gbo;
	private: System::Windows::Forms::GroupBox^		d_pkl_config_gbo;
	private: System::Windows::Forms::Panel^			c_player_kill_npc_pal;
	private: System::Windows::Forms::TabControl^	d_ps_state_equip_tab;
	private: System::Windows::Forms::TabPage^		d_ps_se_cha_tab;
	private: System::Windows::Forms::TabPage^		d_ps_se_fashion_tab;
	private: System::Windows::Forms::Label^  		label17;
	private: System::Windows::Forms::Label^  		label16;
	private: System::Windows::Forms::Label^  		label9;
	private: System::Windows::Forms::Label^  		label8;
	private: System::Windows::Forms::Label^  		label7;
	private: System::Windows::Forms::Label^  		label6;
	private: System::Windows::Forms::Label^  		label5;
	private: System::Windows::Forms::Label^  		label4;
	private: System::Windows::Forms::Label^  		label3;
	private: System::Windows::Forms::TextBox^  		textBox9;
	private: System::Windows::Forms::TextBox^  		textBox6;
	private: System::Windows::Forms::TextBox^  		textBox3;
	private: System::Windows::Forms::TextBox^  		textBox8;
	private: System::Windows::Forms::TextBox^  		textBox5;
	private: System::Windows::Forms::TextBox^  		textBox2;
	private: System::Windows::Forms::TextBox^  		textBox7;
	private: System::Windows::Forms::TextBox^  		textBox4;
	private: System::Windows::Forms::TextBox^  		textBox1;
	private: System::Windows::Forms::TextBox^  		textBox18;
	private: System::Windows::Forms::TextBox^  		textBox17;
	private: System::Windows::Forms::TextBox^  		textBox16;
	private: System::Windows::Forms::TextBox^  		textBox15;
	private: System::Windows::Forms::TextBox^  		textBox14;
	private: System::Windows::Forms::TextBox^  		textBox13;
	private: System::Windows::Forms::TextBox^  		textBox12;
	private: System::Windows::Forms::TextBox^  		textBox11;
	private: System::Windows::Forms::TextBox^  		textBox10;
	private: System::Windows::Forms::Label^  		label19;
	private: System::Windows::Forms::Label^  		label18;
	private: System::Windows::Forms::Label^  		label15;
	private: System::Windows::Forms::Label^  		label14;
	private: System::Windows::Forms::Label^  		label13;
	private: System::Windows::Forms::Label^  		label12;
	private: System::Windows::Forms::Label^  		label11;
	private: System::Windows::Forms::Label^  		label10;
	private: System::Windows::Forms::Label^  		label2;
	private: System::Windows::Forms::ListView^		listView1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader5;
	private: System::Windows::Forms::ColumnHeader^  columnHeader6;
	private: System::Windows::Forms::ColumnHeader^  columnHeader7;
	private: System::Windows::Forms::ColumnHeader^  columnHeader8;
	private: System::Windows::Forms::ColumnHeader^  columnHeader9;
	private: System::Windows::Forms::ColumnHeader^  columnHeader10;
	private: System::Windows::Forms::ColumnHeader^  columnHeader11;
	private: System::Windows::Forms::ColumnHeader^  columnHeader12;
	private: System::Windows::Forms::ColumnHeader^  columnHeader13;
	private: System::Windows::Forms::ColumnHeader^  columnHeader14;
	private: System::Windows::Forms::ColumnHeader^  columnHeader15;
	private: System::Windows::Forms::ColumnHeader^  columnHeader16;
	private: System::Windows::Forms::ColumnHeader^  columnHeader17;
	private: System::Windows::Forms::ColumnHeader^  columnHeader18;
	private: System::Windows::Forms::ListView^  	listView4;
	private: System::Windows::Forms::ListView^  	listView3;
	private: System::Windows::Forms::CheckBox^  	f_msg_privatereply_send_chk_k;
	private: System::Windows::Forms::CheckBox^  	e_msg_gmsession_person_chk_k;
	private: System::Windows::Forms::GroupBox^  	d_pg_record_gbo;
	private: System::Windows::Forms::Panel^			panel1;
	private: System::Windows::Forms::ListView^		d_pg_record_list;
	private: System::Windows::Forms::ComboBox^		d_pg_filter_server_cbo;
	private: System::Windows::Forms::Label^			d_pg_record_pnl;
	private: System::Windows::Forms::ColumnHeader^  dpg_column_player_name;
	private: System::Windows::Forms::ColumnHeader^  dpg_column_gm_level;

	 //----------------------------------------------------------------
	private: System::Windows::Forms::TabControl^	d_pi_type_tab;
	private: System::Windows::Forms::TabPage^		d_pi_item_pag;
	private: System::Windows::Forms::TabPage^		d_pi_money_pag;
	private: System::Windows::Forms::ComboBox^		d_pi_id_cbo;
	private: System::Windows::Forms::ComboBox^		d_pi_name_cbo;
	private: System::Windows::Forms::NumericUpDown^ d_pi_number_num;
	private: System::Windows::Forms::Label^			d_pi_number_lbl;
	private: System::Windows::Forms::ComboBox^		d_pi_lvl_cbo;
	private: System::Windows::Forms::Label^			d_pi_lvl_lbl;
	private: System::Windows::Forms::Label^			d_pi_name_lbl;
	private: System::Windows::Forms::ComboBox^		d_pi_quality_cbo;
	private: System::Windows::Forms::Label^			d_pi_quality_lbl;
	private: System::Windows::Forms::Label^			d_pi_id_lbl;
	private: System::Windows::Forms::ComboBox^		d_pi_money_cbo;
	private: System::Windows::Forms::Label^			d_pi_money_lbl;
	private: System::Windows::Forms::Panel^			d_ar_filter_pal;
	private: System::Windows::Forms::GroupBox^		d_ar_filter_gbo;
	private: System::Windows::Forms::CheckBox^		d_ar_si_endtime_cbx;
	private: System::Windows::Forms::CheckBox^		d_ar_si_starttime_cbx;
	private: System::Windows::Forms::DateTimePicker^d_ar_si_endtime_dtp;
	private: System::Windows::Forms::DateTimePicker^d_ar_si_starttime_dtp;
	private: System::Windows::Forms::ComboBox^  	d_ar_si_region_cbo;
	private: System::Windows::Forms::CheckBox^  	d_ar_si_region_cbx;
	private: System::Windows::Forms::ComboBox^  	d_ar_si_gmname_cbo;
	private: System::Windows::Forms::CheckBox^  	d_ar_si_gmname_cbx;
	private: System::Windows::Forms::TabControl^	d_ar_log_tab;
	private: System::Windows::Forms::TabPage^		d_ar_log_senditem_pag;
	private: System::Windows::Forms::GroupBox^		d_ar_si_log_gbo;
	private: System::Windows::Forms::ListView^		d_ar_si_log_list;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_log_id;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_sendtime;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_gm_name;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_region;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_playername;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_playerid;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_itemname;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_itemcount;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_itemlvl;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_itemgrad;
	private: System::Windows::Forms::ColumnHeader^  column_ar_si_itemuin;
	private: System::Windows::Forms::Panel^			d_ar_si_filter_pal;
	private: System::Windows::Forms::GroupBox^  	d_ar_si_filter_gbo;
	private: System::Windows::Forms::ComboBox^  	d_ar_si_itemtype_cbo;
	private: System::Windows::Forms::CheckBox^  	d_ar_si_itemtype_cbx;
	private: System::Windows::Forms::Button^		d_ar_si_search_btn;
	private: System::Windows::Forms::ColumnHeader^  dms_column_region_name;
	private: System::Windows::Forms::ColumnHeader^  dms_column_region_id;
	private: System::Windows::Forms::ColumnHeader^  dmr_server_column_region_name;
	private: System::Windows::Forms::ColumnHeader^  dmr_server_column_region_id;
	private: System::Windows::Forms::ComboBox^  	d_pm_level_cbx;
	private: System::Windows::Forms::Label^			d_pm_level_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pm_difficulty_cbx;
	private: System::Windows::Forms::Label^			d_pm_difficulty_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pm_map_width_cbx;
	private: System::Windows::Forms::Label^			d_pm_map_width_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pm_map_height_cbx;
	private: System::Windows::Forms::Label^			d_pm_map_height_lbl;
	private: System::Windows::Forms::CheckBox^  	d_pm_is_jump_maze_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pm_map_y_cbx;
	private: System::Windows::Forms::Label^			d_pm_map_y_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pm_map_x_cbx;
	private: System::Windows::Forms::Label^			d_pm_map_x_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pm_map_jump_cbx;
	private: System::Windows::Forms::Label^			d_pm_map_jump_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pm_map_cbx;
	private: System::Windows::Forms::Label^			d_pm_map_lbl;
	private: System::Windows::Forms::Panel^			c_ss_server_pal;
	private: System::Windows::Forms::Button^		c_ss_server_refresh_btn;
	private: System::Windows::Forms::TabPage^		c_gm_player_pag;
	private: System::Windows::Forms::Panel^			c_gm_player_pal;
	private: System::Windows::Forms::Panel^			d_pg_pal;
	private: System::Windows::Forms::GroupBox^  	d_pg_config_gbo;
	private: System::Windows::Forms::TextBox^		d_pg_username_edt;
	private: System::Windows::Forms::ComboBox^  	d_pg_server_cbo;
	private: System::Windows::Forms::Label^			d_pg_username_lbl;
	private: System::Windows::Forms::Label^			d_pg_server_lbl;
	private: System::Windows::Forms::GroupBox^  	d_pg_commit_gbo;
	private: System::Windows::Forms::Button^		d_pg_commit_btn;
	private: System::Windows::Forms::GroupBox^  	d_pg_setting_gbo;
	private: System::Windows::Forms::RadioButton^	d_pg_open_rdo;
	private: System::Windows::Forms::RadioButton^	d_pg_close_rdo;
	private: System::Windows::Forms::DateTimePicker^d_mp_play_time_cbo;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_id;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_content;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_region_group;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_start_date;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_end_date;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_hour;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_minute;
	private: System::Windows::Forms::ColumnHeader^  dmpr_column_play_num;
	private: System::Windows::Forms::ColumnHeader^  cmsg_column_region_name;
	private: System::Windows::Forms::ColumnHeader^  cmsg_column_region_id;
	private: System::Windows::Forms::ColumnHeader^  dmp_column_region_name;
	private: System::Windows::Forms::ColumnHeader^  dmp_column_region_id;
	private: System::Windows::Forms::GroupBox^  	d_mr_player_info_gbo;
	private: System::Windows::Forms::ComboBox^  	d_mr_player_cbo;
	private: System::Windows::Forms::ComboBox^  	d_mr_server_cbo;
	private: System::Windows::Forms::Label^  		d_mr_charactor_lbl;
	private: System::Windows::Forms::Label^  		d_mr_server_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pn_server_cbo;
	private: System::Windows::Forms::Label^			d_pn_server_lbl;
	private: System::Windows::Forms::ListView^  	d_pn_record_list;
	private: System::Windows::Forms::ColumnHeader^  dpn_column_id;
	private: System::Windows::Forms::ColumnHeader^  dpn_column_name;
	private: System::Windows::Forms::Panel^  		d_pn_filter_server_pnl;
	private: System::Windows::Forms::Label^  		d_pn_filter_server_lbl;
	private: System::Windows::Forms::ComboBox^		d_pn_filter_server_cbo;
	private: System::Windows::Forms::ColumnHeader^  dpk_column_account_name;
	private: System::Windows::Forms::ColumnHeader^  dpk_column_end_time;
	private: System::Windows::Forms::Label^			d_pc_min_lbl;
	private: System::Windows::Forms::GroupBox^  	d_pk_player_info_gbo;
	private: System::Windows::Forms::TextBox^		d_pk_username_edt;
	private: System::Windows::Forms::ComboBox^  	d_pk_server_cbo;
	private: System::Windows::Forms::Label^  		d_pk_username_lbl;
	private: System::Windows::Forms::Label^  		d_pk_server_lbl;
	private: System::Windows::Forms::ListView^		d_pk_record_list;
	private: System::Windows::Forms::Panel^ 		d_pk_record_pnl;
	private: System::Windows::Forms::Label^ 		d_pk_filter_server_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pk_filter_server_cbo;
	private: System::Windows::Forms::Label^			d_pk_hour_lbl;
	private: System::Windows::Forms::ColumnHeader^  dpi_column_region_name;
	private: System::Windows::Forms::ColumnHeader^  dpi_column_name;
	private: System::Windows::Forms::GroupBox^  	d_pn_npc_info_gbo;
	private: System::Windows::Forms::ComboBox^  	d_pn_npcid_cbo;
	private: System::Windows::Forms::ComboBox^  	d_pn_npcname_cbo;
	private: System::Windows::Forms::Label^  		d_pn_npcid_lbl;
	private: System::Windows::Forms::Label^  		d_pn_npcname_lbl;
	private: System::Windows::Forms::ColumnHeader^  cps_player_column_region_id;
	private: System::Windows::Forms::GroupBox^  	d_pc_player_info_gbo;
	private: System::Windows::Forms::ComboBox^  	d_pc_username_edt;
	private: System::Windows::Forms::ComboBox^  	d_pc_server_cbo;
	private: System::Windows::Forms::Label^			d_pc_playername_lbl;
	private: System::Windows::Forms::Label^			d_pc_server_lbl;
	private: System::Windows::Forms::Panel^			d_pc_filter_pnl;
	private: System::Windows::Forms::ComboBox^  	d_pc_filter_server_cbo;
	private: System::Windows::Forms::Label^			d_pc_filter_server_lbl;
	private: System::Windows::Forms::ListView^  	d_pc_group_list;
	private: System::Windows::Forms::ColumnHeader^  dpc_column_account_name;
	private: System::Windows::Forms::ColumnHeader^  dpc_column_player_name;
	private: System::Windows::Forms::ColumnHeader^  dpc_column_time;
	private: System::Windows::Forms::ComboBox^		d_pm_map_type_cbx;
	private: System::Windows::Forms::Label^			d_pm_map_type_lbl;
	private: System::Windows::Forms::CheckBox^  	c_player_search_player_blur_cbx;
	private: System::Windows::Forms::ComboBox^  	d_pm_username_cbx;
	private: System::Windows::Forms::ComboBox^  	d_pm_moveplayer_cbx;
	private: System::Windows::Forms::ComboBox^  	d_pm_movenpc_cbx;
	private: System::Windows::Forms::RadioButton^	d_pm_map_rdo;
	private: System::Windows::Forms::CheckBox^		d_am_change_authority_cbx;
	private: System::Windows::Forms::CheckBox^		d_am_change_password_cbx;
	private: System::Windows::Forms::ColumnHeader^  d_am_column_name;
	private: System::Windows::Forms::ColumnHeader^  d_am_column_authority;
	private: System::Windows::Forms::ColumnHeader^  d_am_column_gm_id;
	private: System::Windows::Forms::ListView^		c_ss_server_list;
	private: System::Windows::Forms::ColumnHeader^  ss_column_name;
	private: System::Windows::Forms::ColumnHeader^  ss_column_online_count;
	private: System::Windows::Forms::ColumnHeader^  ss_column_region_id;
	private: System::Windows::Forms::ColumnHeader^  ss_column_id;
	private: System::Windows::Forms::ColumnHeader^  log_column_time;
	private: System::Windows::Forms::ColumnHeader^  log_column_log;
	private: System::Windows::Forms::Panel^			c_player_search_npc_list_pal;
	private: System::Windows::Forms::ListView^		c_player_search_npc_list;
	private: System::Windows::Forms::ColumnHeader^  cps_column_npc_name;
	private: System::Windows::Forms::ColumnHeader^  cps_column_npc_id;
	private: System::Windows::Forms::Panel^			c_player_search_npc_op_pal;
	private: System::Windows::Forms::Button^		c_player_search_npc_get_all_btn;
	private: System::Windows::Forms::Button^		c_player_search_npc_get_sel_btn;
	private: System::Windows::Forms::Panel^			c_player_search_npc_filter_pal;
	private: System::Windows::Forms::Button^		c_player_search_npc_search_btn;
	private: System::Windows::Forms::GroupBox^  	c_player_search_npc_gbo;
	private: System::Windows::Forms::TextBox^		c_player_search_npc_id_edt;
	private: System::Windows::Forms::TextBox^		c_player_search_npc_name_edt;
	private: System::Windows::Forms::CheckBox^  	c_player_search_npc_id_cbx;
	private: System::Windows::Forms::CheckBox^  	c_player_search_npc_name_cbx;
	private: System::Windows::Forms::Panel^			c_player_search_item_filter_pal;
	private: System::Windows::Forms::Button^		c_player_search_item_search_btn;
	private: System::Windows::Forms::GroupBox^  	c_player_search_item_gbo;
	private: System::Windows::Forms::TextBox^		c_player_search_item_id_edt;
	private: System::Windows::Forms::TextBox^		c_player_search_item_name_edt;
	private: System::Windows::Forms::CheckBox^  	c_player_search_item_id_cbx;
	private: System::Windows::Forms::CheckBox^  	c_player_search_item_name_cbx;
	private: System::Windows::Forms::Panel^			c_player_search_item_list_pal;
	private: System::Windows::Forms::ListView^		c_player_search_item_list;
	private: System::Windows::Forms::ColumnHeader^  cps_column_item_name;
	private: System::Windows::Forms::ColumnHeader^  cps_column_item_id;
	private: System::Windows::Forms::Panel^			c_player_search_item_op_pal;
	private: System::Windows::Forms::Button^		c_player_search_item_get_all_btn;
	private: System::Windows::Forms::Button^		c_player_search_item_get_sel_btn;
	private: System::Windows::Forms::ColumnHeader^  cps_player_column_account_name;
	private: System::Windows::Forms::ColumnHeader^  cps_player_column_name;
	private: System::Windows::Forms::ColumnHeader^  cps_player_column_id;
	private: System::Windows::Forms::Panel^			a_main_pal;
	private: System::Windows::Forms::Splitter^		a_spl_center;
	private: System::Windows::Forms::Panel^			a_pal_bottom;
	private: System::Windows::Forms::ListView^		a_list_msg;
	private: System::Windows::Forms::Panel^			a_pal_full;
	private: System::Windows::Forms::Panel^			b_main_pal_right;
	private: System::Windows::Forms::Panel^			b_navi_pal_left;
	private: System::Windows::Forms::TreeView^		b_navi_tree;
	private: System::Windows::Forms::TabControl^	b_main_tab;
	private: System::Windows::Forms::TabPage^		c_palyer_pag;
	private: System::Windows::Forms::TabPage^		c_msg_pag;
	private: System::Windows::Forms::TabPage^		c_server_pag;
	private: System::Windows::Forms::TabPage^		c_account_pag;
	private: System::Windows::Forms::Panel^			c_player_pal;
	private: System::Windows::Forms::Splitter^		c_player_spl;
	private: System::Windows::Forms::Panel^			c_player_left_pal;
	private: System::Windows::Forms::Panel^			c_palyer_main_pal;
	private: System::Windows::Forms::TabControl^	c_player_search_tab;
	private: System::Windows::Forms::TabPage^		c_player_search_player_pag;
	private: System::Windows::Forms::TabPage^		c_player_search_npc_pag;
	private: System::Windows::Forms::TabControl^	c_player_tab;


	private: System::Windows::Forms::TabPage^		c_player_move_pag;
	private: System::Windows::Forms::Panel^			c_player_move_pal;
	private: System::Windows::Forms::TabPage^		c_player_chat_pag;
	private: System::Windows::Forms::Panel^			d_pm_pal;
	private: System::Windows::Forms::GroupBox^  	d_pm_commit_gbo;
	private: System::Windows::Forms::Button^		d_pm_commit_btn;
	private: System::Windows::Forms::GroupBox^		d_pm_position_gbo;
	private: System::Windows::Forms::RadioButton^	d_pm_toplayer_cbo;
	private: System::Windows::Forms::RadioButton^	d_pm_tonpc_cbo;
	private: System::Windows::Forms::RadioButton^	d_pm_coord_rdo;
	private: System::Windows::Forms::Label^  		d_pm_coord_z_lbl;
	private: System::Windows::Forms::Label^  		d_pm_coord_y_lbl;
	private: System::Windows::Forms::Label^  		d_pm_coord_x_lbl;
	private: System::Windows::Forms::GroupBox^  	d_pm_config_gbo;
	private: System::Windows::Forms::ComboBox^  	d_pm_server_cbx;
	private: System::Windows::Forms::Label^  		d_pm_username_lbl;
	private: System::Windows::Forms::Label^  		d_pm_server_lbl;
	private: System::Windows::Forms::NumericUpDown^ d_pm_coord_z_num;
	private: System::Windows::Forms::NumericUpDown^ d_pm_coord_y_num;
	private: System::Windows::Forms::NumericUpDown^ d_pm_coord_x_num;
	private: System::Windows::Forms::Panel^  		c_msg_pal;
	private: System::Windows::Forms::Panel^  		c_server_pal;
	private: System::Windows::Forms::Panel^  		c_account_pal;
	private: System::Windows::Forms::Panel^  		c_msg_server_right_pal;
	private: System::Windows::Forms::Panel^			c_msg_main_pal;
	private: System::Windows::Forms::Splitter^		c_msg_center_spl;
	private: System::Windows::Forms::TabControl^	c_msg_main_tab;
	private: System::Windows::Forms::TabPage^		c_msg_post_pag;
	private: System::Windows::Forms::TabPage^		c_msg_sensword_pag;
	private: System::Windows::Forms::Panel^			c_player_chat_pal;
	private: System::Windows::Forms::TabPage^  		c_player_kick_pag;
	private: System::Windows::Forms::TabPage^  		c_player_item_pag;
	private: System::Windows::Forms::TabPage^  		c_player_npc_pag;
	private: System::Windows::Forms::TabPage^  		c_player_hidden_pag;
	private: System::Windows::Forms::TabPage^  		c_player_state_pag;
	private: System::Windows::Forms::Panel^  		c_player_kick_pal;
	private: System::Windows::Forms::Panel^  		c_player_item_pal;
	private: System::Windows::Forms::Panel^  		c_player_npc_pal;
	private: System::Windows::Forms::Panel^  		c_player_hidden_pal;
	private: System::Windows::Forms::Panel^  		c_player_state_pal;
	private: System::Windows::Forms::TabPage^		c_msg_reply_pag;
	private: System::Windows::Forms::Panel^			c_msg_post_pal;
	private: System::Windows::Forms::Panel^			c_msg_sensword_pal;
	private: System::Windows::Forms::Panel^			c_msg_reply_pal;
	private: System::Windows::Forms::TabControl^	c_account_tab;
	private: System::Windows::Forms::TabPage^  		c_account_manager_pag;
	private: System::Windows::Forms::TabPage^  		c_account_record_pag;
	private: System::Windows::Forms::Panel^  		c_account_manager_pal;
	private: System::Windows::Forms::Panel^  		c_account_record_pal;
	private: System::Windows::Forms::Panel^  		c_player_search_player_pal;
	private: System::Windows::Forms::Panel^  		c_player_search_npc_pal;
	private: System::Windows::Forms::TabPage^		c_player_search_item_pag;
	private: System::Windows::Forms::Panel^  		c_player_search_item_pal;
	private: System::Windows::Forms::Panel^  		c_player_search_player_list_pal;
	private: System::Windows::Forms::ListView^  	c_player_search_player_list;
	private: System::Windows::Forms::Panel^			c_player_search_player_op_pal;
	private: System::Windows::Forms::Panel^			c_player_search_player_filter_pal;
	private: System::Windows::Forms::Button^		c_player_search_player_get_sel_btn;
	private: System::Windows::Forms::Button^		c_player_search_player_get_all_btn;
	private: System::Windows::Forms::GroupBox^  	c_player_search_player_gbo;
	private: System::Windows::Forms::TextBox^		c_player_search_player_charactor_edt;
	private: System::Windows::Forms::TextBox^		c_player_search_player_account_edt;
	private: System::Windows::Forms::ComboBox^  	c_player_search_player_server_cbo;
	private: System::Windows::Forms::CheckBox^  	c_player_search_player_charactor_cbx;
	private: System::Windows::Forms::CheckBox^  	c_player_search_player_account_cbx;
	private: System::Windows::Forms::Label^			c_player_search_player_server_lbl;
	private: System::Windows::Forms::Button^		c_player_search_player_search_btn;
	private: System::Windows::Forms::Panel^			d_pc_pal;
	private: System::Windows::Forms::GroupBox^  	d_pc_record_gbo;
	private: System::Windows::Forms::GroupBox^  	d_pc_commit_gbo;
	private: System::Windows::Forms::Button^		d_pc_commit_reason_btn;
	private: System::Windows::Forms::GroupBox^  	d_pc_forbid_gbo;
	private: System::Windows::Forms::Label^			d_pc_time_lbl;
	private: System::Windows::Forms::ComboBox^  	d_pc_time_cbo;
	private: System::Windows::Forms::Panel^			d_pk_pal;
	private: System::Windows::Forms::GroupBox^  	d_pk_record_gbo;
	private: System::Windows::Forms::GroupBox^  	d_pk_commit_gbo;
	private: System::Windows::Forms::Button^		d_pk_commit_reason_btn;
	private: System::Windows::Forms::GroupBox^  	d_pk_forbid_gbo;
	private: System::Windows::Forms::ComboBox^  	d_pk_time_cbo;
	private: System::Windows::Forms::Label^			d_pk_time_lbl;
	private: System::Windows::Forms::Panel^			d_pi_pal;
	private: System::Windows::Forms::GroupBox^  	d_pi_config_gbo;
	private: System::Windows::Forms::TabControl^	d_pi_config_tab;
	private: System::Windows::Forms::TabPage^		d_pi_single_pag;
	private: System::Windows::Forms::TextBox^		d_pi_username_edt;
	private: System::Windows::Forms::ComboBox^  	d_pi_server_cbo;
	private: System::Windows::Forms::Label^			d_pi_username_lbl;
	private: System::Windows::Forms::Label^			d_pi_server_lbl;
	private: System::Windows::Forms::TabPage^		d_pi_group_pag;
	private: System::Windows::Forms::ListView^  	d_pi_group_list;
	private: System::Windows::Forms::GroupBox^  	d_pi_commit_gbo;
	private: System::Windows::Forms::Button^		d_pi_commit_reason_btn;
	private: System::Windows::Forms::GroupBox^  	d_pi_item_info_gbo;
	private: System::Windows::Forms::Panel^			d_pn_pal;
	private: System::Windows::Forms::GroupBox^  	d_pn_record_gbo;
	private: System::Windows::Forms::GroupBox^  	d_pn_commit_gbo;
	private: System::Windows::Forms::Button^		d_pn_commit_reason_btn;
	private: System::Windows::Forms::GroupBox^  	d_pn_npc_setting_gbo;
	private: System::Windows::Forms::Panel^			d_ph_pal;
	private: System::Windows::Forms::GroupBox^  	d_ph_config_gbo;
	private: System::Windows::Forms::TextBox^		d_ph_username_edt;
	private: System::Windows::Forms::ComboBox^  	d_ph_server_cbo;
	private: System::Windows::Forms::Label^			d_ph_username_lbl;
	private: System::Windows::Forms::Label^			d_ph_server_lbl;
	private: System::Windows::Forms::GroupBox^  	d_ph_commit_gbo;
	private: System::Windows::Forms::Button^		d_ph_commit_btn;
	private: System::Windows::Forms::GroupBox^  	d_ph_hidden_gbo;
	private: System::Windows::Forms::Panel^			d_ps_pal;
	private: System::Windows::Forms::GroupBox^  	d_ps_config_gbo;
	private: System::Windows::Forms::Button^		d_ps_search_btn;
	private: System::Windows::Forms::TextBox^		d_ps_username_edt;
	private: System::Windows::Forms::ComboBox^  	d_ps_server_cbo;
	private: System::Windows::Forms::Label^			d_ps_username_lbl;
	private: System::Windows::Forms::Label^			d_ps_server_lbl;
	private: System::Windows::Forms::GroupBox^  	d_ps_state_gbo;
	private: System::Windows::Forms::TabControl^	d_ps_state_tab;
	private: System::Windows::Forms::TabPage^		d_ps_property_pag;
	private: System::Windows::Forms::TabPage^		d_ps_equip_pag;
	private: System::Windows::Forms::TabPage^		d_ps_bag_pag;
	private: System::Windows::Forms::TabPage^		d_ps_skill_pag;
	private: System::Windows::Forms::TabPage^		d_ps_task_pag;
	private: System::Windows::Forms::Panel^			d_mp_pal;
	private: System::Windows::Forms::TabControl^	d_mp_tab;
	private: System::Windows::Forms::TabPage^		d_mp_record_pag;
	private: System::Windows::Forms::Button^		d_mpr_delete_btn;
	private: System::Windows::Forms::Button^		d_mpr_new_btn;
	private: System::Windows::Forms::TabPage^		d_mp_create_pag;
	private: System::Windows::Forms::Panel^			d_mp_create_pal;
	private: System::Windows::Forms::GroupBox^  	d_mp_title_gbo;
	private: System::Windows::Forms::Label^			d_mp_id_value_lbl;
	private: System::Windows::Forms::Label^			d_mp_id_lbl;
	private: System::Windows::Forms::Label^			d_mp_state_value_lbl;
	private: System::Windows::Forms::Label^			d_mp_state_lbl;
	private: System::Windows::Forms::GroupBox^  	d_mp_commit_gbo;
	private: System::Windows::Forms::Button^		d_mp_commit_btn;
	private: System::Windows::Forms::GroupBox^  	d_mp_post_gbo;
	private: System::Windows::Forms::GroupBox^  	d_mp_cycle_gbo;
	private: System::Windows::Forms::Label^			d_mp_time_lbl;
	private: System::Windows::Forms::DateTimePicker^d_mp_end_time_dtp;
	private: System::Windows::Forms::Label^			d_mp_end_time_lbl;
	private: System::Windows::Forms::DateTimePicker^d_mp_start_time_dtp;
	private: System::Windows::Forms::ComboBox^		d_mp_num_cbo;
	private: System::Windows::Forms::Label^			d_mp_num_lbl;
	private: System::Windows::Forms::Label^			d_mp_start_time_lbl;
	private: System::Windows::Forms::GroupBox^  	d_mp_server_gbo;
	private: System::Windows::Forms::ListView^  	d_mp_server_list;
	private: System::Windows::Forms::RadioButton^	d_mp_cycle_rdo;
	private: System::Windows::Forms::RadioButton^	d_mp_once_rdo;
	private: System::Windows::Forms::GroupBox^		d_mp_text_gbo;
	private: System::Windows::Forms::RichTextBox^	d_mp_text_mno;
	private: System::Windows::Forms::Panel^			d_mpr_create_pal;
	private: System::Windows::Forms::GroupBox^  	d_mpr_server_gbo;
	private: System::Windows::Forms::ListView^  	d_mpr_server_list;
	private: System::Windows::Forms::GroupBox^  	d_mpr_commit_gbo;
	private: System::Windows::Forms::Button^		d_mpr_update_btn;
	private: System::Windows::Forms::TabControl^	c_msg_server_search_tab;
	private: System::Windows::Forms::TabPage^		c_msg_server_right_pag;
	private: System::Windows::Forms::Panel^			c_msg_server_search_op_pal;
	private: System::Windows::Forms::Button^		c_msg_server_getall_btn;
	private: System::Windows::Forms::Button^		c_msg_server_getsel_btn;
	private: System::Windows::Forms::Panel^			c_msg_server_search_pal;
	private: System::Windows::Forms::ListView^  	c_msg_server_search_list;
	private: System::Windows::Forms::Panel^			d_ms_pal;
	private: System::Windows::Forms::GroupBox^  	d_ms_server_gbo;
	private: System::Windows::Forms::ListView^  	d_ms_server_list;
	private: System::Windows::Forms::GroupBox^  	d_ms_sensword_gbo;
	private: System::Windows::Forms::ListView^  	d_ms_sensword_list;
	private: System::Windows::Forms::Panel^			d_mr_pal;
	private: System::Windows::Forms::GroupBox^  	d_mr_reply_gbo;
	private: System::Windows::Forms::GroupBox^  	d_mr_common_reply_gbo;
	private: System::Windows::Forms::ListBox^		d_mr_common_reply_list;
	private: System::Windows::Forms::Button^		d_mr_commit_btn;
	private: System::Windows::Forms::GroupBox^  	d_mr_one_reply_gbo;
	private: System::Windows::Forms::RichTextBox^	d_mr_one_reply_edt;
	private: System::Windows::Forms::GroupBox^		d_mr_one_question_gbo;
	private: System::Windows::Forms::RichTextBox^	d_mr_one_question_txt;
	private: System::Windows::Forms::GroupBox^  	d_mr_server_gbo;
	private: System::Windows::Forms::ListView^  	d_mr_server_list;
	private: System::Windows::Forms::GroupBox^  	d_mr_question_gbo;
	private: System::Windows::Forms::ListView^  	d_mr_question_list;
	private: System::Windows::Forms::Panel^			d_am_pal;
	private: System::Windows::Forms::TabControl^	d_am_tab;
	private: System::Windows::Forms::TabPage^		d_am_create_pag;
	private: System::Windows::Forms::Panel^			d_am_create_pal;
	private: System::Windows::Forms::GroupBox^		d_am_user_gbo;
	private: System::Windows::Forms::TextBox^		d_am_password_edt;
	private: System::Windows::Forms::Label^			d_am_password_lbl;
	private: System::Windows::Forms::TextBox^		d_am_username_edt;
	private: System::Windows::Forms::Label^			d_am_username_lbl;
	private: System::Windows::Forms::TextBox^		d_am_password2_edt;
	private: System::Windows::Forms::ComboBox^  	d_am_authority_cbo;
	private: System::Windows::Forms::Label^			d_am_password2_lbl;
	private: System::Windows::Forms::Label^			d_am_authority_lbl;
	private: System::Windows::Forms::GroupBox^  	d_am_commit_gbo;
	private: System::Windows::Forms::Button^		d_am_commit_btn;
	private: System::Windows::Forms::TabPage^		d_am_record_pag;
	private: System::Windows::Forms::Panel^			d_am_record_pal;
	private: System::Windows::Forms::GroupBox^  	d_am_account_gbo;
	private: System::Windows::Forms::ListView^  	d_am_account_list;
	private: System::Windows::Forms::GroupBox^  	d_am_change_gbo;
	private: System::Windows::Forms::Label^			d_am_change_name_content_lbl;
	private: System::Windows::Forms::Label^			d_am_change_name_lbl;
	private: System::Windows::Forms::GroupBox^  	d_am_change_delete_gbo;
	private: System::Windows::Forms::Button^		d_am_delete_reason_btn;
	private: System::Windows::Forms::GroupBox^  	d_am_change_update_gbo;
	private: System::Windows::Forms::Button^		d_am_update_reason_btn;
	private: System::Windows::Forms::GroupBox^  	d_am_change_info_gbo;
	private: System::Windows::Forms::TextBox^		d_am_change_newpasswor2_txt;
	private: System::Windows::Forms::Label^			d_am_change_newpasswor2_lbl;
	private: System::Windows::Forms::TextBox^		d_am_change_oldpassword_txt;
	private: System::Windows::Forms::Label^			d_am_change_oldpassword_lbl;
	private: System::Windows::Forms::TextBox^		d_am_change_newpassword_txt;
	private: System::Windows::Forms::ComboBox^  	d_am_change_authority_cbo;
	private: System::Windows::Forms::Label^			d_am_change_newpassword_lbl;
	private: System::Windows::Forms::Panel^			d_ar_pal;
	private: System::Windows::Forms::Panel^			d_ar_record_pal;
	private: System::Windows::Forms::ColumnHeader^  cps_player_column_uin;
	private: System::Windows::Forms::ColumnHeader^  cps_column_item_type;
	private: System::Windows::Forms::ColumnHeader^  cps_column_npc_type;
	private: System::Windows::Forms::ColumnHeader^  ms_sens_column_uin;
	private: System::Windows::Forms::ColumnHeader^  ms_sens_column_id;
	private: System::Windows::Forms::ColumnHeader^  ms_sens_column_name;
	private: System::Windows::Forms::ColumnHeader^  ms_sens_column_type;
	private: System::Windows::Forms::ColumnHeader^  ms_sens_column_content;
	private: System::Windows::Forms::ColumnHeader^  mr_column_player_uin;
	private: System::Windows::Forms::ColumnHeader^  mr_column_player_id;
	private: System::Windows::Forms::ColumnHeader^  mr_column_player_name;
	private: System::Windows::Forms::ColumnHeader^  mr_column_gm_name;
	private: System::Windows::Forms::ColumnHeader^  mr_column_content;
	private: System::Windows::Forms::ColumnHeader^  ms_sens_column_region_id;
	private: System::Windows::Forms::ColumnHeader^  mr_column_region_id;
	private: System::Windows::Forms::CheckBox^		d_pm_offset_cbo;
	private: System::Windows::Forms::RadioButton^  d_pc_unforbit_rdo;
	private: System::Windows::Forms::RadioButton^  d_pc_forbit_rdo;
	private: System::Windows::Forms::RadioButton^  d_pk_forbid_lbl;
	private: System::Windows::Forms::RadioButton^  d_pk_unforbid_lbl;
	private: System::Windows::Forms::RadioButton^  d_pn_closed_rdo;
	private: System::Windows::Forms::RadioButton^  d_pn_unclosed_gbo;
	private: System::Windows::Forms::RadioButton^  d_ph_hidden_rdo;
	private: System::Windows::Forms::RadioButton^  d_ph_show_rdo;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion

	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
	private: System::Void MainForm_Shown(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void b_navi_tree_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e);
	private: System::Void c_player_search_player_search_btn_Click(System::Object^  sender, System::EventArgs^  e);  
	private: System::Void d_pm_commit_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void c_player_search_player_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void d_pc_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pk_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pi_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pn_commit_reason_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_ph_commit_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_npc_search_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void c_player_search_item_search_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_npc_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void c_player_search_item_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void d_mr_sensword_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void d_mr_commit_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_mp_commit_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void a_list_msg_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void a_list_msg_DoubleClick(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_player_account_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_player_charactor_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void b_navi_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
	private: System::Void d_am_commit_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_am_account_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_am_update_reason_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_am_delete_reason_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_am_change_password_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_am_change_authority_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_ar_search_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_coord_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_player_cbo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_npc_cbo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_npc_edt_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void d_pm_username_edt_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void d_pm_player_edt_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_pm_map_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;         
	private: System::Void c_player_search_player_get_sel_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void c_player_search_player_get_all_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_npc_get_sel_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_npc_get_all_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_item_get_sel_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_item_get_all_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pc_forbit_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pc_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pc_group_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_pk_forbid_lbl_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pk_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pn_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) ;  
	private: System::Void c_msg_server_search_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void c_msg_server_getsel_btn_Click(System::Object^  sender, System::EventArgs^  e) ; 
	private: System::Void c_msg_server_getall_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_mp_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void d_mpr_new_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_mpr_update_btn_Click(System::Object^  sender, System::EventArgs^  e) ;    
	private: System::Void d_mpr_delete_btn_Click(System::Object^  sender, System::EventArgs^  e) ;  
	private: System::Void d_mpr_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_mp_cycle_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_mr_common_reply_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_pg_commit_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_npc_id_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_npc_name_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_item_id_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_item_name_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_ss_server_refresh_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void c_player_search_player_search_btn_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;  
	private: System::Void d_pk_record_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_pn_record_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_pm_map_type_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_map_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_map_jump_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) ;  
	private: System::Void d_pm_map_type_cbx_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_map_cbx_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_map_type_cbx_TextChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_map_cbx_TextChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pm_is_jump_maze_lbl_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_ms_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_mr_server_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;
	private: System::Void d_pi_id_cbo_TextChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_pi_group_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) ;  
	private: System::Void d_ar_si_region_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_ar_si_gmname_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_ar_si_itemtype_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_ar_si_starttime_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_ar_si_endtime_cbx_CheckedChanged(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void d_ar_si_search_btn_Click(System::Object^  sender, System::EventArgs^  e) ;
	private: System::Void MainForm_SizeChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void c_msg_pri_add_btn_k_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_msg_server_list_k_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void e_msg_gmsession_server_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void e_msg_gmsession_send_btn_k_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void e_msg_gmsession_server_session_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void c_msg_sensword_server_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void e_msg_gmsession_person_btn_k_Click(System::Object^  sender, System::EventArgs^  e); 
	private: System::Void e_msg_privatereply_tab_k_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void f_msg_privatereply_send_btn_k_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void e_msg_privatereply_tab_k_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void e_msg_privatereply_list_k_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_mp_once_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_mp_repeat_ckb_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_ph_server_cmb_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_ph_hidden_rdo_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pm_move_map_cbx_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pm_move_map_cbx_TextChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pi_all_player_cekb_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pkl_commit_btn_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void f_msg_privatereply_send_chk_k_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void e_msg_gmsession_person_chk_k_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pg_filter_server_cbo_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void d_pg_record_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);


	};
}

