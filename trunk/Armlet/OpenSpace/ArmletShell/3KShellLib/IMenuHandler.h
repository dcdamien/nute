#ifndef _NAMESPACE_PROTECT_
	#error "Use ThreeKShell.h"
#endif

class IMenuHandler
{
public:
	virtual fresult OnClick(IMenuItem* sender)=0;
};


template<class T> class MenuHandlerFunctionPtr {
	typedef fresult (T::*MENU_HANDLER_DELEGATE)(IMenuItem* sender);
	MENU_HANDLER_DELEGATE _handler;
public:
	MenuHandlerFunctionPtr(MENU_HANDLER_DELEGATE handler) {_handler = handler;}
	int Execute(T* _this) {return (_this->*_handler)();}
};

template<class T> class MenuHandlerDelegate : public IMenuHandler {
	typedef fresult (T::*MENU_HANDLER_DELEGATE)(IMenuItem* sender);
	MENU_HANDLER_DELEGATE _handler;
	T* _this;
public:
	MenuHandlerDelegate(T* __this,MENU_HANDLER_DELEGATE handler) {_handler = handler; _this=__this;}
	int Execute() {return (_this->*_handler)();}
	virtual int OnClick(void* sender) { return Execute();}
};

#define CREATE_PFM(R,T,F)					MenuHandlerFunctionPtr<T>* R = new MenuHandlerFunctionPtr<T>(&T::F)
#define CREATE_DELEGATE(R,T,_this,F)		MenuHandlerDelegate<T>* R = new MenuHandlerDelegate<T>(_this,&T::F)
#define CREATE_MENU_HANDLER_ANY(T,_this,F)	new MenuHandlerDelegate<T>(_this,&T::F)
#define CREATE_MENU_HANDLER(T,F)			new MenuHandlerDelegate<T>(this,&T::F)