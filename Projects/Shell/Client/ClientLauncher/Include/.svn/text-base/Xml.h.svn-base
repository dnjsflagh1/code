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
	Xml节点属性。
*/
typedef	struct
{
	char*					m_sAttribNameBegin;	//	属性名字。
	mutable	char*			m_sAttribNameEnd;
	char*					m_sAttribDataBegin;	//	属性数据。
	mutable	char*			m_sAttribDataEnd;
}XmlAttrib;

/*
	XML节点，包括名字，属性和文本三种信息。
	此外还包含子节点，父节点的信息。
	*/
class	XmlNode
{
	char*						m_sNameBegin;		//	节点名字。
	mutable	char*				m_sNameEnd;

	std::vector< XmlAttrib >	m_Attribs;			//	所有的属性。

	char*						m_sDataBegin;		//	节点数据。
	mutable	char*				m_sDataEnd;

	XmlNode*					m_Pater;			//	父节点。
	std::vector< XmlNode >		m_Childs;			//	所有的子节点。

	friend	bool	Parse(			char*&	sXmlBuffer,	XmlNode&	node	);	//	解析。
	friend	bool	ParseAttrib(	char*&	sXmlBuffer,	XmlNode&	node	);	//	解析属性。
	friend	bool	ParseChild(		char*&	sXmlBuffer,	XmlNode&	node	);	//	解析子节点。

public:

	//	返回节点的名字。
	const	char*		GetName( )	const;
	//	返回节点的文本。
	const	char*		GetData()	const;
	//	获取属性总数。
	long				GetAttribCount()	const;
	//	获取属性名字。
	const	char*		GetAttribName(	long	id	)	const;
	//	获取属性。
	const	char*		GetAttrib(	long	id	)	const;
	//	查询属性。
	const	char*		QueryAttrib(	const	char*	name	)	const;
	//	获取子节点总数。
	long				GetChildNodeCount()	const;
	//	获取父节点。
	const	XmlNode*	GetPater()	const;
	//	获取子节点。
	const	XmlNode*	GetChildNode(	long	id	)	const;
	//	获取本节点的次序。
	long				GetNodeId()	const;
	//	获取前一个节点。
	const	XmlNode*	GetPrevNode()	const;
	//	获取后一个节点。
	const	XmlNode*	GetNextNode()	const;
	//	查询子节点。
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
	char*			m_sBuffer;		//	缓冲区。
	XmlNode*		m_XmlNodeRoot;	//	引导节点。


public:
	/*
		构造。
		*/
	XmlDocument(void);
	/*
		析构。
		*/
	~XmlDocument(void);

	/*
		说明	打开XML文挡并解析。
		返回	打开是否成功。
		参数	为XML文件名字。
		*/
	bool		Open(	const	char*	sFileName);

	/*
		说明	关闭XML文挡，释放内存。
		*/
	void		Close(	);

	/*
		说明	获取引导节点。
		返回	引导节点。
		*/
	const	XmlNode*	GetRoot();

};


//	查询XML节点。*使用的函数返回类型必须是BOOL的。
#define	QUERY_XML_NODE_ATTRIB(	node_,	attrib_,	name_ )				\
			const	char*	attrib_	=	node_->QueryAttrib(	name_	);	\
			if(	!attrib_	)											\
				return	false;

//	查询XML子节点。	*使用的函数返回类型必须是BOOL的，此外父节点名字必须是node
#define	QUERY_XML_CHILD_NODE(	node_,	name_	)							\
			const	XmlNode*	node_	=	node->QueryChild(	name_	);	\
			if(	!node_	)													\
				return	false;

//	查询XML节点数据。*使用的函数返回类型必须是BOOL的。
#define	QUERY_XML_NODE_DATA(	node_,	data_	)					\
			const	char*	data_	=	node_->GetData(	);	\
			if(	!data_	)									\
				return	false;



#endif // _XML_H











