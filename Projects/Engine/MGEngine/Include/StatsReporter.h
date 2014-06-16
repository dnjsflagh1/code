///////////////////////////////////////////////////////////////////////  
//  StatsReporter.h
//
//  *** INTERACTIVE DATA VISUALIZATION (IDV) CONFIDENTIAL AND PROPRIETARY INFORMATION ***
//
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Interactive Data Visualization, Inc. and
//  may not be copied, disclosed, or exploited except in accordance with 
//  the terms of that agreement.
//
//      Copyright (c) 2003-2010 IDV, Inc.
//      All rights reserved in all media.
//
//      IDV, Inc.
//      http://www.idvinc.com


///////////////////////////////////////////////////////////////////////  
//  Preprocessor

#pragma once
#include "RenderInterface/ForestRI.h"


///////////////////////////////////////////////////////////////////////  
//  All SpeedTree SDK classes and variables are under the namespace "SpeedTree"

namespace SpeedTree
{

    typedef CBasicFixedString<4096> CReportString;

    ///////////////////////////////////////////////////////////////////////  
    //  Class CStatsReporter

    class CStatsReporter
    {
    public:
                            CStatsReporter( );
    virtual                 ~CStatsReporter( );

            st_bool         Update(st_float32 fCurrentTime, st_float32 fReportInterval = 1.5f); // returns true if a report should be made; interval is in seconds
            const char*     Report(const SRenderStats& sStats, st_bool bItemized);

    private:
            st_int32        m_nUpdatesSinceLastReport;
            st_float32      m_fLastReportTime;
            st_float32      m_fReportInterval;
            CReportString   m_strReportText;
    };

} // end namespace SpeedTree

