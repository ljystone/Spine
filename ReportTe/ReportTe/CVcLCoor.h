// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "c:\\Windows\\SysWow64\\MSCHRT20.OCX" no_namespace
// CVcLCoor wrapper class

class CVcLCoor : public COleDispatchDriver
{
public:
	CVcLCoor(){} // Calls COleDispatchDriver default constructor
	CVcLCoor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcLCoor(const CVcLCoor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcLCoor methods
public:
	long get_X()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_X(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Y()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Y(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Set(long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y);
	}

	// IVcLCoor properties
public:

};
