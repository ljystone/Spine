// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "c:\\Windows\\SysWow64\\MSCHRT20.OCX" no_namespace
// CVcAxisGrid wrapper class

class CVcAxisGrid : public COleDispatchDriver
{
public:
	CVcAxisGrid(){} // Calls COleDispatchDriver default constructor
	CVcAxisGrid(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcAxisGrid(const CVcAxisGrid& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcAxisGrid methods
public:
	LPDISPATCH get_MinorPen()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_MajorPen()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// IVcAxisGrid properties
public:

};
