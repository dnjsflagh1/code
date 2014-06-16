#ifndef _XML_H
#define _XML_H


#include <list>
#include <assert.h>
#include <vector>
#include "MemFileDef.h"
//
class	XmlNode;
bool	Parse(			char*&	sXmlBuffer,	XmlNode&	node	);
bool	ParseAttrib(	char*&	sXmlBuffer,	XmlNode&	node	);
bool	ParseChild(		char*&	sXmlBuffer,	XmlNode&	node	);

/*
	Xml�ڵ����ԡ�
*/
typedef	struct
{
	char*					m_sAttribNameBegin;	//	�������֡�
	mutable	char*			m_sAttribNameEnd;
	char*					m_sAttribDataBegin;	//	�������ݡ�
	mutable	char*			m_sAttribDataEnd;
}XmlAttrib;

/*
	XML�ڵ㣬�������֣����Ժ��ı�������Ϣ��
	���⻹�����ӽڵ㣬���ڵ����Ϣ��
	*/
class	XmlNode
{
	char*						m_sNameBegin;		//	�ڵ����֡�
	mutable	char*				m_sNameEnd;

	std::vector< XmlAttrib >	m_Attribs;			//	���е����ԡ�

	char*						m_sDataBegin;		//	�ڵ����ݡ�
	mutable	char*				m_sDataEnd;

	XmlNode*					m_Pater;			//	���ڵ㡣
	std::vector< XmlNode >		m_Childs;			//	���е��ӽڵ㡣

	friend	bool	Parse(			char*&	sXmlBuffer,	XmlNode&	node	);	//	������
	friend	bool	ParseAttrib(	char*&	sXmlBuffer,	XmlNode&	node	);	//	�������ԡ�
	friend	bool	ParseChild(		char*&	sXmlBuffer,	XmlNode&	node	);	//	�����ӽڵ㡣

public:

	//	���ؽڵ�����֡�
	const	char*		GetName( )	const;
	//	���ؽڵ���ı���
	const	char*		GetData()	const;
	//	��ȡ����������
	long				GetAttribCount()	const;
	//	��ȡ�������֡�
	const	char*		GetAttribName(	long	id	)	const;
	//	��ȡ���ԡ�
	const	char*		GetAttrib(	long	id	)	const;
	//	��ѯ���ԡ�
	const	char*		QueryAttrib(	const	char*	name	)	const;
	//	��ȡ�ӽڵ�������
	long				GetChildNodeCount()	const;
	//	��ȡ���ڵ㡣
	const	XmlNode*	GetPater()	const;
	//	��ȡ�ӽڵ㡣
	const	XmlNode*	GetChildNode(	long	id	)	const;
	//	��ȡ���ڵ�Ĵ���
	long				GetNodeId()	const;
	//	��ȡǰһ���ڵ㡣
	const	XmlNode*	GetPrevNode()	const;
	//	��ȡ��һ���ڵ㡣
	const	XmlNode*	GetNextNode()	const;
	//	��ѯ�ӽڵ㡣
	const	XmlNode*	QueryChild(	const	char*	name	)	const;

public:

	XmlNode(	XmlNode*	pater	);
	~XmlNode();
};

/*
*/
class	XmlDocument
{
	//
	char*			m_sBuffer;		//	��������
	XmlNode*		m_XmlNodeRoot;	//	�����ڵ㡣


public:
	/*
		���졣
		*/
	XmlDocument(void);
	/*
		������
		*/
	~XmlDocument(void);

	/*
		˵��	��XML�ĵ���������
		����	���Ƿ�ɹ���
		����	ΪXML�ļ����֡�
		*/
	bool		Open(	const	char*	sFileName);

	/*
		˵��	�ر�XML�ĵ����ͷ��ڴ档
		*/
	void		Close(	);

	/*
		˵��	��ȡ�����ڵ㡣
		����	�����ڵ㡣
		*/
	const	XmlNode*	GetRoot();

};


//	��ѯXML�ڵ㡣*ʹ�õĺ����������ͱ�����BOOL�ġ�
#define	QUERY_XML_NODE_ATTRIB(	node_,	attrib_,	name_ )				\
			const	char*	attrib_	=	node_->QueryAttrib(	name_	);	\
			if(	!attrib_	)											\
				return	false;

//	��ѯXML�ӽڵ㡣	*ʹ�õĺ����������ͱ�����BOOL�ģ����⸸�ڵ����ֱ�����node
#define	QUERY_XML_CHILD_NODE(	node_,	name_	)							\
			const	XmlNode*	node_	=	node->QueryChild(	name_	);	\
			if(	!node_	)													\
				return	false;

//	��ѯXML�ڵ����ݡ�*ʹ�õĺ����������ͱ�����BOOL�ġ�
#define	QUERY_XML_NODE_DATA(	node_,	data_	)					\
			const	char*	data_	=	node_->GetData(	);	\
			if(	!data_	)									\
				return	false;



#endif // _XML_H











