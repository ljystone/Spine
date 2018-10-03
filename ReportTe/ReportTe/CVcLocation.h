// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "c:\\Windows\\SysWow64\\MSCHRT20.OCX" no_namespace
// CVcLocation wrapper class

class CVcLocation : public COleDispatchDriver
{
public:
	CVcLocation(){} // Calls COleDispatchDriver default constructor
	CVcLocation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcLocation(const CVcLocation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcLocation methods
public:
	LPDISPATCH get_Rect()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_LocationType()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_LocationType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// IVcLocation properties
public:

};
