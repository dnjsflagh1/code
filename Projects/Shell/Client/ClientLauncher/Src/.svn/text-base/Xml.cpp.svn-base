#include "StdAfx.h"
#include "xml.h"

//
#include <windows.h>
#define	XmlWarning(x)	MessageBoxA( NULL,x,"错误",MB_OK|MB_ICONERROR );

/*
	Xml单词的属性。
	*/
enum	XmlWordAttrib
{
	XmlLeft		=	1,		//	"<",不能是"</"
	XmlLeftOver	=	1<<1,	//	"</"
	XmlRight	=	1<<2,	//	">"
	XmlRightOver=	1<<3,	//	"/>"
	XmlName		=	1<<4,	//	节点名字，必须为合法的字符。
	XmlSymbol	=	1<<5,	//	节点属性名字，必须合法的字符，不能小于32，不能是'<','>','"','='
	XmlData		=	1<<6,	//	节点数据，非'<','>'的任意字符。
	XmlString	=	1<<7,	//	节点属性数据。'"'。
	XmlEqual	=	1<<8,	//	等号。'='。
	XmlError	=	1<<9	//	返回此标记表示语法错。
};

//	回滚操作。
class	XmlBackroll
{
	char*	m_sBackrollMark;
	char*&	m_sBackroll;
public:
	XmlBackroll(	char*&	sXmlBuffer	)	
		:	m_sBackroll	(	sXmlBuffer	),
			m_sBackrollMark	(	sXmlBuffer	)
	{
	};
	~XmlBackroll()
	{
		m_sBackroll	=	m_sBackrollMark;
	}
};

//	声明回滚。
#define		DECLARE_XML_BACKROLL	XmlBackroll	backroll( sXmlBuffer );
//	回滚数据。
#define		XML_BACKROLL		sXmlBuffer	=	sBackroll_;
//	移动到下一个字符。
#define		XML_NEXT	\
				++	sXmlBuffer;				\
				if(	!*sXmlBuffer	)		\
					return	false;			\

//	移动到前一个字符。
#define		XML_PREV		--sXmlBuffer;	

//	移动到指定的条件下。
#define		XML_TO(	compare_	)		\
				while( 1 )				\
				{						\
					if(	!*sXmlBuffer )	\
						return	false;	\
					if(	compare_ )		\
						break;			\
					++	sXmlBuffer;		\
				}

//	"<",不能是"</"。
bool	IsXmlLeft(	char*&	sXmlBuffer	)
{
	//	定义回滚。
	DECLARE_XML_BACKROLL;

	//
	if(	*sXmlBuffer	==	'<'	)
	{
		XML_NEXT;
		return	*sXmlBuffer	!=	'/';
	}

	//	返回失败。
	return	false;
}

//	到"<"结束，移动一字符。
bool	OverXmlLeft(	char*&	sXmlBuffer	)
{
	XML_NEXT;
	return	true;
};

//	"</"。
bool	IsXmlLeftOver(	char*&	sXmlBuffer	)
{
	//	
	DECLARE_XML_BACKROLL;

	//
	if(	*sXmlBuffer	==	'<'	)
	{
		XML_NEXT;
		return	*sXmlBuffer	==	'/';
	}

	//
	return	false;
}

//	到"</"结束,移动两字符。
bool	OverXmlLeftOver(	char*&	sXmlBuffer	)
{
	XML_NEXT;
	XML_NEXT;
	return	true;
}

//	">"。
bool	IsXmlRight(	char*&	sXmlBuffer	)
{
	return	*sXmlBuffer	==	'>';
}

//	到">"结束，移动一字符。
bool	OverXmlRight(	char*&	sXmlBuffer	)
{
	XML_NEXT;
	return	true;
}

//	"/>"
bool	IsXmlRightOver(	char*&	sXmlBuffer	)
{
	//
	DECLARE_XML_BACKROLL;

	//
	if(	*sXmlBuffer	==	'/'	)
	{
		XML_NEXT;
		return	*sXmlBuffer == '>';
	}

	//
	return	false;
}

//	到"/>"结束，移动两个字节。
bool	OverXmlRightOver(	char*&	sXmlBuffer	)
{
	XML_NEXT;
	XML_NEXT;
	return	true;
}

//	节点名字，合法字符，不能是'=','<','>','/'。
bool	IsXmlName(	char*&	sXmlBuffer	)
{
	return	*sXmlBuffer > 32 && *sXmlBuffer != '=' && *sXmlBuffer != '<' && *sXmlBuffer != '>' && *sXmlBuffer != '/';
};

//	到节点名字结束。
bool	OverXmlName(	char*&	sXmlBuffer	)
{
	XML_TO(	*sXmlBuffer<=32||*sXmlBuffer=='>'||*sXmlBuffer=='/'	);
	return	true;
};

//	节点属性名字，>32，不能是'<','>','"','='
bool	IsXmlSymbol(	char*&	sXmlBuffer	)
{
	return	*sXmlBuffer > 32 && *sXmlBuffer != '=' && *sXmlBuffer != '<' && *sXmlBuffer != '>' && *sXmlBuffer != '/';
}

//	到节点属性名字结束。
bool	OverXmlSymbol(	char*&	sXmlBuffer	)
{
	XML_TO(	*sXmlBuffer<=32||*sXmlBuffer=='=' );
	return	true;
}

//	数据 >32,非'<','>'。
bool	IsXmlData(	char*&	sXmlBuffer	)
{
	return	*sXmlBuffer	>	32	&&	*sXmlBuffer	!=	'<'	&&	*sXmlBuffer	!=	'>';
}

//	到数据结束。
bool	OverXmlData(	char*&	sXmlBuffer	)
{
	XML_TO(	*sXmlBuffer=='<'&&sXmlBuffer[1]=='/' );
	return	true;
}

//	属性。'"',成功移动到'"'的下一个字符。
//	ok!
bool	IsXmlString(	char*&	sXmlBuffer	)
{
	return	*sXmlBuffer	==	'"';
}

//	到属性结束。
bool	OverXmlString(	char*&	sXmlBuffer	)
{
	XML_NEXT;
	XML_TO( *sXmlBuffer=='"'	);
	XML_NEXT;
	return	true;
}

//	等号。'='。
bool	IsXmlEqual(	char*&	sXmlBuffer	)
{
	return	*sXmlBuffer=='=';
}

//	到等号结束。
bool	OverXmlEqual(	char*&	sXmlBuffer	)
{
	XML_NEXT;
	return	true;
}

/*
	获取下一个符号的开始位置。
	*/
XmlWordAttrib	GetToken( char*&	sXmlBuffer,	unsigned	int	flage	)
{
	//	遍历每个字符，如果到达字符串缓冲区结束位置，则返回失败。
	while(	*sXmlBuffer )
	{
		//	查找无效字符。
		if(	*sXmlBuffer	>	32	)
		{
			if(	flage	&	XmlData		&&	IsXmlData(		sXmlBuffer	)	)
			{
				//printf("IsXmlData = %s;",sXmlBuffer);
				return	XmlData;
			}

			if(	flage	&	XmlLeft		&&	IsXmlLeft(		sXmlBuffer	)	)
			{
				//printf("IsXmlLeft = %s;",sXmlBuffer);
				return	XmlLeft;
			}

			if(	flage	&	XmlLeftOver	&&	IsXmlLeftOver(	sXmlBuffer	)	)
			{
				//printf("IsXmlLeftOver = %s;",sXmlBuffer);
				return	XmlLeftOver;
			}

			if(	flage	&	XmlRight	&&	IsXmlRight(		sXmlBuffer	)	)
			{
				//printf("IsXmlRight = %s;",sXmlBuffer);
				return	XmlRight;
			}

			if(	flage	&	XmlRightOver&&	IsXmlRightOver(	sXmlBuffer	)	)
			{
				//printf("IsXmlRightOver = %s;",sXmlBuffer);
				return	XmlRightOver;
			}

			if(	flage	&	XmlName		&&	IsXmlName(		sXmlBuffer	)	)
			{
				//printf("IsXmlName = %s;",sXmlBuffer);
				return	XmlName;
			}

			if(	flage	&	XmlSymbol	&&	IsXmlSymbol(	sXmlBuffer	)	)
			{
				//printf("IsXmlSymbol = %s;",sXmlBuffer);
				return	XmlSymbol;
			}

			if(	flage	&	XmlString	&&	IsXmlString(	sXmlBuffer	)	)
			{
				//printf("IsXmlString = %s;",sXmlBuffer);
				return	XmlString;
			}

			if(	flage	&	XmlEqual	&&	IsXmlEqual(		sXmlBuffer	)	)
			{
				//printf("IsXmlEqual = %s;",sXmlBuffer);
				return	XmlEqual;
			}

			return	XmlError;
		}

		++	sXmlBuffer;
	}

	//	返回失败。
	return	XmlError;
};

//	解析属性,进入时缓冲区位于属性名字的第一个字符。
bool	ParseAttrib(	char*&	sXmlBuffer,	XmlNode&	node	)
{
	//
	XmlAttrib	attrib;

	//	解析符号。
	if(	XmlSymbol	!=	GetToken(	sXmlBuffer,	XmlSymbol	)	)
		return	false;
	attrib.m_sAttribNameBegin	=	sXmlBuffer;
	
	if(	!OverXmlSymbol(	sXmlBuffer	)	)
		return	false;
	attrib.m_sAttribNameEnd		=	sXmlBuffer;

	//	解析等号。
	if(	XmlEqual	!=	GetToken(	sXmlBuffer,	XmlEqual	)	)
		return	false;

	OverXmlEqual(	sXmlBuffer	);

	//	解析串。
	if(	XmlString	!=	GetToken(	sXmlBuffer,	XmlString	)	)
		return	false;
	attrib.m_sAttribDataBegin	=	++	sXmlBuffer;

	if(	!OverXmlString(	sXmlBuffer	)	)
		return	false;
	attrib.m_sAttribDataEnd		=	sXmlBuffer - 1;

	//	添加属性。
	node.m_Attribs.push_back(	attrib	);

	//	如果接下来仍然是符号，则递归。
	if(	XmlSymbol	==	GetToken(	sXmlBuffer,	XmlSymbol|XmlRight|XmlRightOver	)	)
		ParseAttrib(	sXmlBuffer,	node	);

	//	返回成功。
	return	true;
};

//	解析节点。
bool	Parse(	char*&	sXmlBuffer,	XmlNode&	node	)
{
	//	解析名字。
	if(	XmlLeft	!=	GetToken(	sXmlBuffer,	XmlLeft	)		//	检查'<'和跳过'<'
		||	!OverXmlLeft(	sXmlBuffer	)	
		)
	{
		XmlWarning(	"get node name < error!" );
		return	false;
	}

	if(	XmlName	!=	GetToken(	sXmlBuffer,	XmlName	)	)	//	检查名字。
	{
		XmlWarning( "get node name error!" );
		return	false;
	}
	node.m_sNameBegin	=	sXmlBuffer;

	if(	!OverXmlName(	sXmlBuffer	)	)					//	跳过名字。
	{
		XmlWarning( "over node name error!" );
		return	false;
	}
	node.m_sNameEnd		=	sXmlBuffer;

	//	解析属性。
	if(	XmlSymbol	==	GetToken(	sXmlBuffer,	XmlSymbol|XmlRight|XmlRightOver	)	)
		ParseAttrib(	sXmlBuffer,	node	);

	//	解析'/>'。
	if(	XmlRightOver	==	GetToken(	sXmlBuffer,	XmlRight|XmlRightOver	)	)
	{
		if(	!OverXmlRightOver(	sXmlBuffer	)	)
		{
			XmlWarning( "over xml node /> error!" );
			return	false;
		}
		return	true;
	}

	//	解析'>'。
	if(	XmlRight	==	GetToken(	sXmlBuffer,	XmlRight	)
		&&	!OverXmlRight(	sXmlBuffer	)
		)
	{
		XmlWarning( "get node name > error!"	);
		return	false;
	}

	//	解析数据。
	if(	XmlData		==	GetToken(	sXmlBuffer,	XmlData|XmlLeft|XmlLeftOver	)	)
	{
		node.m_sDataBegin	=	sXmlBuffer;
		
		if(	!OverXmlData(	sXmlBuffer	)	)
		{
			XmlWarning( "over node data error!" );
			return	false;
		}

		node.m_sDataEnd	=	sXmlBuffer;
	}

	//	解析子节点。
	while(	XmlLeft		==	GetToken(	sXmlBuffer,	XmlLeft|XmlLeftOver	)	)
	{
		XmlNode		child(	&node	);
		

		if(	!Parse(	sXmlBuffer,	child	)	)
		{
			char	text[256];
			sprintf(	text,	"parse %s child node error!", node.GetName()	);
			XmlWarning( text	);
			return	false;
		}

		node.m_Childs.push_back(	child	);
	}

	//	解析关闭节点。
	if(	XmlLeftOver	!=	GetToken(	sXmlBuffer,	XmlLeftOver	)
		||	!OverXmlLeftOver(	sXmlBuffer	)
		)
	{
		XmlWarning( "get or over </ error!" );
		return	false;
	}

	if(	XmlName	!=	GetToken(	sXmlBuffer,	XmlName	)	)
	{
		XmlWarning( "get over name error!" );
		return	false;
	}

	char*	name	=	sXmlBuffer;

	if(	!OverXmlName(	sXmlBuffer	)	)
	{
		XmlWarning( "over over name error!" );
		return	false;
	}

	char	temp	=	*sXmlBuffer;
	*sXmlBuffer		=	0;

	*node.m_sNameEnd	=	0;
	if(	strcmp(	name,	node.m_sNameBegin	)	)
	{
		XmlWarning( "over name not equal node name!" );
		return	false;
	}

	*sXmlBuffer		=	temp;
	if(	XmlRight	!=	GetToken(	sXmlBuffer,	XmlRight	)	
		||	!OverXmlRight(	sXmlBuffer	)
		)
	{

		XmlWarning( "over name > error!" );
		return	false;
	}
	

	//	解析成功。
	return	true;
};


//	返回节点的名字。
const	char*	XmlNode::GetName( )	const
{
	if(	m_sNameEnd	)
		*m_sNameEnd	=	0;

	return	m_sNameBegin;
}

//	返回节点的文本。
const	char*	XmlNode::GetData()	const
{
	if(	m_sDataEnd )
		*m_sDataEnd	=	0;

	return	m_sDataBegin;
}

//	获取属性总数。
long	XmlNode::GetAttribCount()	const
{
	return	(long)m_Attribs.size();
};

//	获取属性名字。
const	char*	XmlNode::GetAttribName(	long	id	)	const
{
	if(	id	<	0	||	id	>=	GetAttribCount()	)
		return	NULL;

	if(	m_Attribs[id].m_sAttribNameEnd	)
		*m_Attribs[id].m_sAttribNameEnd	=	0;

	return	m_Attribs[id].m_sAttribNameBegin;
};

//	获取属性。
const	char*	XmlNode::GetAttrib(	long	id	)	const
{
	if(	id	<	0	||	id	>=	GetAttribCount()	)
		return	NULL;

	if(	m_Attribs[id].m_sAttribDataEnd	)
		*m_Attribs[id].m_sAttribDataEnd	=	0;

	return	m_Attribs[id].m_sAttribDataBegin;
};

//	查询属性。
const	char*	XmlNode::QueryAttrib(	const	char*	name	)	const
{
	for(	unsigned	int	i	=	0;	i	<	m_Attribs.size();	i	++	)
	{
		*m_Attribs[i].m_sAttribNameEnd	=	0;

#ifdef	DEBUG
		const	char*	c	=	m_Attribs[i].m_sAttribNameBegin;
#endif

		if(	!strcmp(	m_Attribs[i].m_sAttribNameBegin,	name	)	)
		{
			*m_Attribs[i].m_sAttribDataEnd	=	0;
			return	m_Attribs[i].m_sAttribDataBegin;
		}
	}

	return	NULL;
};

//	获取子节点总数。
long	XmlNode::GetChildNodeCount()	const
{
	return	(long)this->m_Childs.size();
}

//	获取父节点。
const	XmlNode*	XmlNode::GetPater()	const
{
	return	this->m_Pater;
}

//	获取子节点。
const	XmlNode*	XmlNode::GetChildNode(	long	id	)	const
{
	if(	id	<	0	||	id	>=	GetChildNodeCount()	)
		return	NULL;

	return	&( m_Childs[id] );
}

//	获取本节点的次序。
long	XmlNode::GetNodeId()	const
{
	//	如果没有父节点，则返回0。
	if(	!m_Pater )
		return	0;

	//	寻找节点。
	for(	unsigned	int	i	=	0;	i	<	m_Pater->m_Childs.size();	i	++	)
	{
		if(	&m_Pater->m_Childs[i]	==	this	)
			return	i;
	}

	//	没找到节点。
	assert( !"没有在父节点的子节点中找到自己。");

	//
	return	-1;
};

//	获取前一个节点。
const	XmlNode*	XmlNode::GetPrevNode()	const
{
	if(	!m_Pater	)
		return	NULL;

	long	id	=	GetNodeId();

	if(	id	<	1	||	id	>=	GetChildNodeCount()	)
		return	NULL;

	return	&this->m_Pater->m_Childs[ id - 1 ];
}

//	获取后一个节点。
const	XmlNode*	XmlNode::GetNextNode()	const
{
	if(	!m_Pater	)
		return	NULL;

	long	id	=	GetNodeId();

	if(	id	<	0	||	id	>=	GetChildNodeCount()	-	1	)
		return	NULL;

	return	&this->m_Pater->m_Childs[ id + 1 ];
}

//	查询子节点。
const	XmlNode*	XmlNode::QueryChild(		const	char*	name	)	const
{
	std::vector< XmlNode >::const_iterator	it	=	m_Childs.begin();

	while(	it	!=	m_Childs.end() )
	{
		if( it->GetName() )
		{
			if(	!strcmp(	it->GetName(),	name	)	)
				return	&*it;
		}
		++	it;
	}

	return	NULL;
};

//	根据缓冲区指针构造节点。
XmlNode::XmlNode(	XmlNode*	pater	)
	:	m_sNameBegin(	NULL	),
		m_sNameEnd(		NULL	),
		m_sDataBegin(	NULL	),
		m_sDataEnd(		NULL	),
		m_Pater(		pater	)
{
};

XmlNode::~XmlNode()
{
};

/*
	构造。
	*/
XmlDocument::XmlDocument(void)
		:	m_sBuffer(NULL),
			m_XmlNodeRoot(NULL)
{
};

/*
	析构。
	*/
XmlDocument::~XmlDocument(void)
{
	if(	m_sBuffer	&&	m_XmlNodeRoot	)
	{
		Close();
	}
};

/*
	说明	打开XML文挡并解析。
	返回	打开是否成功。
	参数	为XML文件名字。
	*/
bool		XmlDocument::Open(	const	char*	sFileName)
{

	FILE* fp = fopen( sFileName, "rb" );
	if ( !fp ) 
	{
		return false;
	}

	fseek( fp, 0, SEEK_END );
	unsigned size = ftell( fp );
	fseek( fp, 0, SEEK_SET );

	if ( size == 0 ) {
		fclose( fp );
		return false;
	}

	m_sBuffer	=	(char*)malloc( size	+ 1 );
	fread( m_sBuffer, size, 1, fp );
	m_sBuffer[size] = 0;
	fclose( fp );
	//	解析。
	m_XmlNodeRoot	=	new	XmlNode( NULL );
	char*	sBuffer	=	m_sBuffer;

	if(		!m_XmlNodeRoot
		||	!Parse(	sBuffer,	*m_XmlNodeRoot	)	
		)
	{
		Close();
		return	false;
	}

	//
	return	true;
};

/*
	说明	关闭XML文挡，释放内存。
	*/
void		XmlDocument::Close(	)
{
	//
	assert(	m_sBuffer	);
	assert(	m_XmlNodeRoot	);

	//	释放
	free(	m_sBuffer	);
	delete	m_XmlNodeRoot;

	m_sBuffer = NULL;
	m_XmlNodeRoot = NULL;
};

/*
	说明	获取引导节点。
	返回	引导节点。
	*/
const	XmlNode*	XmlDocument::GetRoot()
{
	//
	assert(	m_sBuffer	);
	assert(	m_XmlNodeRoot	);

	//
	return	m_XmlNodeRoot;
};
