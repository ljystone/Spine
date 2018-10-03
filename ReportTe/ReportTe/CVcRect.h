// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "c:\\Windows\\SysWow64\\MSCHRT20.OCX" no_namespace
// CVcRect wrapper class

class CVcRect : public COleDispatchDriver
{
public:
	CVcRect(){} // Calls COleDispatchDriver default constructor
	CVcRect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcRect(const CVcRect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcRect methods
public:
	LPDISPATCH get_Min()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Max()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// IVcRect properties
public:

};
