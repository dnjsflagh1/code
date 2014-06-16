//***********************************************************************************************
#include "stdafx.h"
#include "ColorResConfig.h"
//***********************************************************************************************
namespace MG
{
    ColorResConfig::~ColorResConfig()
    {
        clear();
    }
    //-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool ColorResConfig::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

            ColorResCsvInfo* tempInfo = new ColorResCsvInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(),      tempInfo->ColorRes_Id     );
			nCol++;
			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->ColorName	  );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(),      (U32&)tempInfo->UseType   );

			Str16 tempStr = csvdata->mData[nCol++];
			MGStrOp::toFlt(tempStr.substr(0,3).c_str(),(tempInfo->ColorValue).r);
			MGStrOp::toFlt(tempStr.substr(3,3).c_str(),(tempInfo->ColorValue).g);
			MGStrOp::toFlt(tempStr.substr(6,3).c_str(),(tempInfo->ColorValue).b);
			MGStrOp::toFlt(tempStr.substr(9,3).c_str(),(tempInfo->ColorValue).a);

			tempInfo->ColorValue.r = tempInfo->ColorValue.r/255.0f;
			tempInfo->ColorValue.g = tempInfo->ColorValue.g/255.0f;
			tempInfo->ColorValue.b = tempInfo->ColorValue.b/255.0f;
			tempInfo->ColorValue.a = tempInfo->ColorValue.a/255.0f;

			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   tempInfo->EscapeChar);

            mColorResCsvMap[tempInfo->ColorRes_Id] = tempInfo;
        }

        return true;
    }
    //-----------------------------------------------------------------------------------
    const ColorResCsvInfo* ColorResConfig::getColorResInfo( U32 id )
    {
		std::map<U32, ColorResCsvInfo*>::iterator it = mColorResCsvMap.find(id);
		if (it != mColorResCsvMap.end())
		{
			return it->second;
		}
		return NULL;
    }
    //-----------------------------------------------------------------------------------
    MG::Bool ColorResConfig::getColorResInfo( U32 id, const ColorResCsvInfo*& info )
    {
		Bool ret = false;
		std::map<U32, ColorResCsvInfo*>::iterator it = mColorResCsvMap.find(id);
		if (it != mColorResCsvMap.end())
		{
			info = it->second;
			if (info)
			{
				ret = true;
			}
		}
		return ret;
    }
	//-----------------------------------------------------------------------------------
	bool ColorResConfig::getColorResInfo(ColorUSeType type,std::map<U32, ColorResCsvInfo*>& mapinfo)
	{
        if (mColorResCsvMap.empty())
          return false;
		std::map<U32, ColorResCsvInfo*>::iterator front = mColorResCsvMap.begin();
		std::map<U32, ColorResCsvInfo*>::iterator back = mColorResCsvMap.end();
		U32 i = 1;
		while (front != back)
		{
			if ((front->second->UseType) == type)
			{
				mapinfo[i] = front->second;
				i++;
			}

			front++;
		}
		return true;
	}
	//-----------------------------------------------------------------------------------
    void ColorResConfig::clear()
    {
        std::map<U32, ColorResCsvInfo*>::iterator front = mColorResCsvMap.begin();
        std::map<U32, ColorResCsvInfo*>::iterator back = mColorResCsvMap.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mColorResCsvMap.clear();
    }
}