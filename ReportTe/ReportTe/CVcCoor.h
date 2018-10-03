// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "c:\\Windows\\SysWow64\\MSCHRT20.OCX" no_namespace
// CVcCoor wrapper class

class CVcCoor : public COleDispatchDriver
{
public:
	CVcCoor(){} // Calls COleDispatchDriver default constructor
	CVcCoor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcCoor(const CVcCoor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcCoor methods
public:
	float get_X()
	{
		float result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_X(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Y()
	{
		float result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Y(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Set(float X, float Y)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y);
	}

	// IVcCoor properties
public:

};
