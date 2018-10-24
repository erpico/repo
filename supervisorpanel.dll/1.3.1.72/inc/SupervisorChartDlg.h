#pragma once

#include "BCGPChartCtrl.h"
#include "ErpicoCTI/ACDClient.h"
#include "Resource.h"

#include "afxwin.h"

#include <list>
#include <vector>

class SUPERVISORPANEL_API CSupervisorChartBase : public CBCGPChartCtrl {
public:
  enum EChartId {
    eChartReadyOperators,
  };

public:
  CSupervisorChartBase() {}
  virtual ~CSupervisorChartBase() {}

  void Init() {
    CBCGPChartVisualObject* pChart = GetChart();

    pChart->SetChartType(BCGPChartArea);
    pChart->SetCurveType(BCGPChartFormatSeries::CCT_LINE);
    pChart->SetThemeOpacity(50);

    CBCGPChartTheme theme(CBCGPChartTheme::CT_BLUE);
    //theme.m_brChartFillColor = CBCGPBrush(CBCGPColor(CBCGPColor::DarkGreen, 0.2));
    pChart->SetColors(theme);

    CBCGPChartSeries* pSeriesCPU =  pChart->CreateSeries(_T("series1"), CBCGPColor::BlueViolet);
    pSeriesCPU->EnableHistoryMode(TRUE, 3600);

    CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
    ASSERT_VALID(pXAxis);

    pXAxis->m_axisLabelType = CBCGPChartAxis::ALT_NO_LABELS;
    pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_NO_TICKS;
    pXAxis->SetFixedIntervalWidth(60, 60);

    CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
    ASSERT_VALID(pYAxis);

    pYAxis->SetFixedDisplayRange(0., 30., 10.);
    pChart->AddChartData(0.0);

    pChart->ShowAxisName(BCGP_CHART_Y_PRIMARY_AXIS, TRUE);

    CBCGPBrush m_brFill1(CBCGPColor::Pink, .3);
    CBCGPChartRangeObject* m_pRange = pChart->AddChartRangeObject(50., 100., TRUE /* Horizontal */, m_brFill1);

    pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);

    pChart->SetDirty();
  }

  void Redraw()
  {
    CBCGPChartVisualObject* pChart = GetChart();
    pChart->SetDirty();
    pChart->Redraw();
  }

  void SetYAxisLabel(const CString& strName)
  {
    CBCGPChartVisualObject* pChart = GetChart();
    ASSERT_VALID(pChart);

    pChart->SetAxisName(BCGP_CHART_Y_PRIMARY_AXIS, strName);
    pChart->ShowAxisName(BCGP_CHART_Y_PRIMARY_AXIS, FALSE);
  }

  void SetXAxisLabel(const CString& strName)
  {
    CBCGPChartVisualObject* pChart = GetChart();
    ASSERT_VALID(pChart);

    pChart->SetChartTitle(strName);
    pChart->ShowChartTitle();
    
    //pChart->SetAxisName(BCGP_CHART_X_PRIMARY_AXIS, strName);
    //pChart->ShowAxisName(BCGP_CHART_X_PRIMARY_AXIS, TRUE);
  }

  void AddDataPoint(double dVal, const CString& legend)
  {
    CBCGPChartVisualObject* pChart = GetChart();
    ASSERT_VALID(pChart);

    CBCGPChartSeries* pSeries =  pChart->GetSeries(0);
    pSeries->AddDataPoint(dVal);

    SetXAxisLabel(legend);

    pChart->SetDirty();

    if(IsWindowVisible())
      Redraw();
  }
};

//////////////////////////////////////////////////////////////////////////
// CSupervisorChartDlg dialog

typedef std::vector<CSupervisorChartBase*> TChartsVector;

class CSupervisorChartDlg : public CDialogEx
{
  TChartsVector m_vecCharts;

  UINT_PTR m_timerId;

  HICON m_hIcon;

  int m_nReadyOperatorsCount;
  int m_nNotReadyOperatorsCount;
  int m_nAfterworkOperatorsCount;
  int m_nTotalOperatorsCount;
  int m_nCallsCount;
  int m_nTotalCallsCount;

  CACDClient &m_acdClient;

  CScrollBar m_sbVert;

private:
  DECLARE_DYNAMIC(CSupervisorChartDlg)

public:
  CSupervisorChartDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~CSupervisorChartDlg();

  void Create();

// Dialog Data
  static const int IDD;

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

  virtual void OnOK() { ShowWindow(SW_HIDE); }
  virtual void OnCancel() { ShowWindow(SW_HIDE); }

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnTimer(UINT_PTR nTimerID);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

  void UpdateCharts();
  void CollectACDData();	

  CSupervisorChartBase* AddNewChart();
  void AlignChartWindows();
  void RecalculateVertSBLimits();
  void AlignVertSB();
};
