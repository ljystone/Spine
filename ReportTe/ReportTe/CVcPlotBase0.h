// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "c:\\Windows\\SysWow64\\MSCHRT20.OCX" no_namespace
// CVcPlotBase0 wrapper class

class CVcPlotBase0 : public COleDispatchDriver
{
public:
	CVcPlotBase0(){} // Calls COleDispatchDriver default constructor
	CVcPlotBase0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcPlotBase0(const CVcPlotBase0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcPlotBase methods
public:
	float get_BaseHeight()
	{
		float result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_BaseHeight(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Brush()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// IVcPlotBase properties
public:

};
