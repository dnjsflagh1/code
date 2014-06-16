#pragma once
#include "stdafx.h"
#include "Operate.h"

// COperatePage 对话框


enum OperateMode
{
	OperateMode_NULL,
	OperateMode_Order,
	OperateMode_Random
};

struct OperateModeAttribute
{
	MG::Int index;
	MG::U32 lifePeriod;       //millisecond
	
	OperateModeAttribute()
		:index(0),lifePeriod(0)
	{

	}
	
};


class COperatePage : public CPropertyPage
{
	DECLARE_DYNAMIC(COperatePage)

public:
	COperatePage();
	virtual ~COperatePage();

// 对话框数据
	enum { IDD = IDD_DIALOG_OPERATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnStatrOperate();
	afx_msg void OnBnClickedBtnEndOperate();
	afx_msg void OnBnClickedCheckUseSkill();
	afx_msg void OnBnClickedCheckJumpMap();
	afx_msg void OnBnClickedCheckTestNet();
	afx_msg void OnBnClickedCheckRandTest();
	afx_msg void OnBnClickedCheckOrderTest();
	afx_msg void OnBnClickedRadioRandTest();
	afx_msg void OnBnClickedRadioOrderTest();
	afx_msg void OnBnClickedCheckTestRandmove();
	afx_msg void OnBnClickedTestLoginNet();
	afx_msg void OnBnClickedCheckFullserverChat();

public:
	bool					init();
	static OperateMode		getOperateMode();
	static bool				isOperateStart();
	static MG::OperateType	getOneOperate(MG::Int index = 0);
	
	void					pushOperate(MG::OperateType operate);
	void					removeOperate(MG::OperateType operate);
    void                    pushOperateModeAttr(MG::OperateType operate,OperateModeAttribute* operateAttr);
	
	
	
	// 选中状态
	static OperateMode					mOperateMode;
	// 是否开始操作
	static bool							mIsStartOperate;
	static MG::Int						mOperateIndex;
    static MG::Int					    mCurrOperateIndex;


	static std::vector<MG::OperateType> mOperates;
    static std::map<MG::OperateType,OperateModeAttribute*> mOperateModeAttrMap;
	
private:
	void clearOperateModeAttribute(MG::OperateType type);
	void clearAllOperateModeAttribute();
	
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBnClickedBtnCreatesoldier();
	afx_msg void OnBnClickedCheckTestLoginandout();
	afx_msg void OnBnClickedCheckTestCreatecam();
public:

	afx_msg void OnBnClickedBtnCreatesoldier2();
	afx_msg void OnBnClickedCheckRegionChat();
};
