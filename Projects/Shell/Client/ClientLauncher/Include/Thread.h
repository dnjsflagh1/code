/******************************************************************************/
#ifndef _THREAD_H_
#define _THREAD_H_
/******************************************************************************/

/******************************************************************************/
//单线程处理
/******************************************************************************/
class OneThreadHandle
{
public:
	OneThreadHandle();
	~OneThreadHandle();

	MG::Bool	create(void (*callback)(MG::Ptr),MG::Ptr ptr);
	MG::Bool	destory();
	void*	getParam();
	MG::Bool	isRun();
	MG::Ptr		getHandle();

protected:
	static DWORD API threadFunction(MG::Ptr p);

private:
	void (*mCallback)(MG::Ptr); 
	MG::Ptr mPtr;
	MG::Ptr mHandle;  
	MG::Bool mIsRun;
};

#endif