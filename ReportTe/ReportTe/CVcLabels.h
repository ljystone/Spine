// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "c:\\Windows\\SysWow64\\MSCHRT20.OCX" no_namespace
// CVcLabels wrapper class

class CVcLabels : public COleDispatchDriver
{
public:
	CVcLabels(){} // Calls COleDispatchDriver default constructor
	CVcLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcLabels(const CVcLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcLabels methods
public:
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Item(short LabelIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, LabelIndex);
		return result;
	}
	LPDISPATCH get_Item(short LabelIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, LabelIndex);
		return result;
	}

	// IVcLabels properties
public:

};
