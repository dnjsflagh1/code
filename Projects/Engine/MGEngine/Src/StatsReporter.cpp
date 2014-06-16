///////////////////////////////////////////////////////////////////////  
//  StatsReporter.cpp
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
#include "stdafx.h"
#include "StatsReporter.h"
using namespace SpeedTree;


///////////////////////////////////////////////////////////////////////  
//  CStatsReporter::CStatsReporter

CStatsReporter::CStatsReporter( ) :
    m_nUpdatesSinceLastReport(0),
    m_fLastReportTime(-1.0f),
    m_fReportInterval(1.0f)
{
}


///////////////////////////////////////////////////////////////////////  
//  CStatsReporter::~CStatsReporter

CStatsReporter::~CStatsReporter( )
{
}


///////////////////////////////////////////////////////////////////////  
//  CStatsReporter::Update

st_bool CStatsReporter::Update(st_float32 fCurrentTime, st_float32 fReportInterval)
{
    st_bool bUpdate = false;

    ++m_nUpdatesSinceLastReport;

    if (m_fLastReportTime == -1.0f)
        m_fLastReportTime = fCurrentTime;
    else
    {
        st_float32 fInterval = fCurrentTime - m_fLastReportTime;
        if (fInterval >= fReportInterval)
        {
            m_fReportInterval = fInterval;

            m_fLastReportTime = fCurrentTime;
            bUpdate = true;
        }
    }

    return bUpdate;
}


///////////////////////////////////////////////////////////////////////  
//  GetTriangleReport

CReportString GetTriangleReport(st_int32 nTriangleCount)
{
    if (nTriangleCount < 1000)
        return CReportString::Format("%d tris", nTriangleCount);
    else
        return CReportString::Format("%.1fK tris", nTriangleCount / 1000.0f);
}


///////////////////////////////////////////////////////////////////////  
//  CStatsReporter::Report

const char* CStatsReporter::Report(const SRenderStats& sStats, st_bool bItemized)
{
    // compute statistics
    SRenderStats::SGeometryStats sTotals;
    sStats.GetTotals(sTotals);

    st_float32 fFramesPerSec = m_nUpdatesSinceLastReport / m_fReportInterval;
    st_float32 fMsPerFrame = 1000.0f / fFramesPerSec;
    st_float32 fMTrisPerSec = (fFramesPerSec * sTotals.m_uiNumTriangles) / 1e6f;

    // generate report
    m_strReportText = CReportString::Format("[%.1f fps (%.2f ms), %.2f ms update, %.2fM tris/sec, %s, %d 3D trees, %d draws, %d texbinds, %d vbo binds, %d cells/frustum]\n", 
                        fFramesPerSec, 
                        fMsPerFrame, 
                        sStats.m_fCullAndPopulateTime / 1000.0f, 
                        fMTrisPerSec, 
                        GetTriangleReport(sTotals.m_uiNumTriangles).c_str( ), 
                        sStats.m_aGeometries[0][RENDER_PASS_STANDARD].m_uiNumObjects, 
                        sTotals.m_uiNumDrawCalls, 
                        sTotals.m_uiNumTextureBinds, 
                        sTotals.m_uiNumVboBinds,
                        sStats.m_nNumCellsInFrustum);

    if (bItemized)
    {
        const char* pNames[STATS_CATEGORY_COUNT] = 
        {
            "Branches",
            "Fronds",
            "Leaf Cards",
            "Leaf Meshes",
            "Meshes",
            "Billboards",
            "Terrain",
            "Grass",
            "Sky",
        };

        const char* pPass[RENDER_PASS_NUM_TYPES] =
        {
            "",     // main pass
            "(d)",  // depth-only pass
            "(s)"   // shadow pass
        };

        for (st_int32 i = int(STATS_CATEGORY_BRANCHES); i < int(STATS_CATEGORY_COUNT); ++i)
        {
            for (st_int32 j = 0; j < int(RENDER_PASS_NUM_TYPES); ++j)
            {
                const SRenderStats::SGeometryStats* pGeom = sStats.m_aGeometries[i] + j;
                if (pGeom->m_uiNumTriangles > 0)
                    m_strReportText += CReportString::Format("%15s%3s: [%s, %d insts, %d draw calls, %d texbinds, %d vbo binds]\n",
                        pNames[i], pPass[j], GetTriangleReport(pGeom->m_uiNumTriangles).c_str( ), pGeom->m_uiNumObjects, pGeom->m_uiNumDrawCalls, pGeom->m_uiNumTextureBinds, pGeom->m_uiNumVboBinds);
            }
        }
    }

    // reset for next report
    m_nUpdatesSinceLastReport = 0;

    return m_strReportText.c_str( );
}


