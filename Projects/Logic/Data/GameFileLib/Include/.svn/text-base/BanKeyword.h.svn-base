//******************************************************************************************
#ifndef _BANKEYWORD_H_
#define _BANKEYWORD_H_

#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
    
	//-----------------------------------------------------------------------
	struct BanKeywordEnter 
	{
        U32    id;
		Str16  keyWord;
		Int	   nStrLen;

		BanKeywordEnter()
		{
			id = 0;
			nStrLen = 0;
		}
	};
	struct BanKeywordName
	{
		U32    id;
		Str16  keyWord;
		Int	   nStrLen;

		BanKeywordName()
		{
			id = 0;
			nStrLen = 0;
		}
		
	};
	struct BanKeywordShow
	{
		U32    id;
		Str16  keyWord;
		Str16  replaceWord;
		Int    nStrLen;

		BanKeywordShow()
		{
			id = 0;
			nStrLen = 0;
		}
		

	};
	//-----------------------------------------------------------------------
	struct IgnoreChar
	{
		wchar_t		cNoChar;
		int			nIndex;

		IgnoreChar()
		{
			nIndex = 0;
		}
	};
	//-----------------------------------------------------------------------
    template<typename T>
	class BanKeyword
	{
	public:
	     BanKeyword()
		 {

		 }
		 ~BanKeyword()
		 {

		 }
		 SINGLETON_INSTANCE( BanKeyword< T > );
         enum
		 {
             ID,
			 NOTES,
			 KEYWORD

		 };
		 //load csv

		 // MG_CN_MODIFY
		 //template<typename T>
		 Bool       load(Str16 fileName, IMGExternalPackManager* packManager = NULL){
			
			 CsvReader csvreader;
			 // MG_CN_MODIFY
			 if(!csvreader.create(fileName, packManager))
			 {
				 return false;
			 }

			 CsvData* csvdata = NULL;
			 Int rowCount = csvreader.count();
			 for(Int i = 0; i < rowCount; ++i)
			 {
				 csvdata = csvreader.findValue(i);
				 if(!csvdata)
				 {
					 continue;
				 }
                 T* t = MG_NEW T();
				 MGStrOp::toU32(csvdata->mData[ID].c_str(),			t->id);
			     t->keyWord =  csvdata->mData[KEYWORD];
				 t->nStrLen =  WStrLen((t->keyWord).c_str());
				 mVecBanList.push_back(t);
			 }

			 return true;

		 }
         
		 Bool       isBan(CChar16* _src){

			 if(!_src)
			 {
				 return true;
			 }

			 Char16 szStr[1024];
			 memset(szStr, 0, sizeof(szStr));
			 WStrnCpyS(szStr, _src, WStrLen(_src));
			 MGStrOp::makeUpper(Str16(szStr));

			 for(UInt i = 0; i < mVecBanList.size(); ++i)
			 {

				 if(WcsStr(szStr, mVecBanList[i]->keyWord.c_str()))
				 {
					 return true;
				 }
			 }

			 return false;	

		 }

	protected:
	private:
		std::vector<T*>  mVecBanList;

	};

	//-----------------------------------------------------------------------
	//BanKeyword 全特化 增加一个editreplaceban方法
	template<>
	class BanKeyword<BanKeywordShow>
	{
	public:
		BanKeyword()
		{

		}
		~BanKeyword()
		{

		}
		SINGLETON_INSTANCE(BanKeyword<BanKeywordShow>);
		
		enum
		{
			ID,
			NOTES,
			KEYWORD,
            REPLACEWORD
		};
		//load csv

		// MG_CN_MODIFY
		Bool       load(Str16 fileName, IMGExternalPackManager* packManager = NULL)
		{
		
			CsvReader csvreader;
			// MG_CN_MODIFY
			if(!csvreader.create(fileName, packManager))
			{
				return false;
			}

			CsvData* csvdata = NULL;
			Int rowCount = csvreader.count();
			for(Int i = 0; i < rowCount; ++i)
			{
				csvdata = csvreader.findValue(i);
				if(!csvdata)
				{
					continue;
				}
				BanKeywordShow* info = MG_NEW BanKeywordShow();
				MGStrOp::toU32(csvdata->mData[ID].c_str(),			info->id);
				info->keyWord =  csvdata->mData[KEYWORD];
				info->replaceWord = csvdata->mData[REPLACEWORD];
				info->nStrLen =  WStrLen((info->keyWord).c_str());
				mVecBanList.push_back(info);
			}

			return true;
		}

		Bool       isBan(CChar16* _src)
		{

			if(!_src)
			{
				return true;
			}

			Char16 szStr[1024];
			memset(szStr, 0, sizeof(szStr));
			WStrnCpyS(szStr, _src, WStrLen(_src));
			MGStrOp::makeUpper(Str16(szStr));

			for(UInt i = 0; i < mVecBanList.size(); ++i)
			{

				if(WcsStr(szStr, mVecBanList[i]->keyWord.c_str()))
				{
					return true;
				}
			}

			return false;


		}
        
		/*
		parameter:
        strEdit :    检测的文本
		nStrLen :	 检测的文本长度 默认0，表示整个文本的长度
		cSwap   :    用作替换的字符串
		pIgnoreCha : 检测过程中需要忽略的字符 默认为: 空格 下划线 分隔符
		*/

		
		Bool       EditReplaceBan(Char16 *strEdit, Int nStrLen = 0,Char16 cSwap = L'*', Char16* pIgnoreChar = L" _|")
		{
					
			bool blRet = false;

			if(!strEdit || !pIgnoreChar)
			{
				return blRet;
			}

			int nLen = WStrLen(strEdit);
			int nIndex = 0;

			Char16 szTempEdit[1024];
			memset(szTempEdit, 0, sizeof(szTempEdit));
			if(nStrLen == 0)
			{
				nStrLen = WStrLen(strEdit);
			}
			WStrnCpyS(szTempEdit, strEdit, nStrLen);

			MGStrOp::makeUpper(Str16(szTempEdit));

			std::vector<int> vecIndexList;

			for(UInt i = 0; i < WStrLen(szTempEdit); ++i)
			{
				vecIndexList.push_back(i);
			}

			while (nIndex <= nLen)
			{
				for(UInt j = 0; j < WStrLen(pIgnoreChar); ++j)
				{
					if(szTempEdit[nIndex] == pIgnoreChar[j])
					{

						std::vector<int>::iterator it = vecIndexList.begin();
						it += nIndex;
						vecIndexList.erase(it);

						memmove(&szTempEdit[nIndex], &szTempEdit[nIndex+1], (nLen - nIndex) * sizeof(Char16));
						nIndex--;
						nLen--;

						break;
					}
				}

				nIndex++;
			}

			wchar_t* pTemp = NULL;
			pTemp = szTempEdit;

			for(UInt i = 0; i < mVecBanList.size(); ++i)
			{
				wchar_t* p = WcsStr(szTempEdit, mVecBanList[i]->keyWord.c_str());

				while(p)
				{
					blRet = true;

					for(UInt j = 0; j < WStrLen(szTempEdit); ++j)
					{
						if(&szTempEdit[j] == p)
						{
							for(int k = 0; k < mVecBanList[i]->nStrLen; ++k)
							{
								int Index = vecIndexList[j + k];

								if(Index >= nStrLen)
								{
									continue;
								}

								wcsncpy(&strEdit[Index], &cSwap, 1);
								//me
							}
						}
					}

					pTemp = p + mVecBanList[i]->nStrLen;

					p = WcsStr(pTemp, mVecBanList[i]->keyWord.c_str());
				}
			}

			return blRet;

		}

	private:
		std::vector<BanKeywordShow*>  mVecBanList;

	};



}


#endif