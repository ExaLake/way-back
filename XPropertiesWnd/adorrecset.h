// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CADORRecordset wrapper class

class CADORRecordset : public COleDispatchDriver
{
public:
	CADORRecordset() {}		// Calls COleDispatchDriver default constructor
	CADORRecordset(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CADORRecordset(const CADORRecordset& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetProperties();
	long GetAbsolutePosition();
	void SetAbsolutePosition(long nNewValue);
	void SetRefActiveConnection(LPDISPATCH newValue);
	void SetActiveConnection(const VARIANT& newValue);
	VARIANT GetActiveConnection();
	BOOL GetBof();
	VARIANT GetBookmark();
	void SetBookmark(const VARIANT& newValue);
	long GetCacheSize();
	void SetCacheSize(long nNewValue);
	long GetCursorType();
	void SetCursorType(long nNewValue);
	BOOL GetEof();
	LPDISPATCH GetFields();
	long GetLockType();
	void SetLockType(long nNewValue);
	long GetMaxRecords();
	void SetMaxRecords(long nNewValue);
	long GetRecordCount();
	void SetRefSource(LPDISPATCH newValue);
	void SetSource(LPCTSTR lpszNewValue);
	VARIANT GetSource();
	void AddNew(const VARIANT& FieldList, const VARIANT& Values);
	void CancelUpdate();
	void Close();
	void Delete(long AffectRecords);
	VARIANT GetRows(long Rows, const VARIANT& Start, const VARIANT& Fields);
	void Move(long NumRecords, const VARIANT& Start);
	void MoveNext();
	void MovePrevious();
	void MoveFirst();
	void MoveLast();
	void Open(const VARIANT& Source, const VARIANT& ActiveConnection, long CursorType, long LockType, long Options);
	void Requery(long Options);
	void Update(const VARIANT& Fields, const VARIANT& Values);
	long GetAbsolutePage();
	void SetAbsolutePage(long nNewValue);
	long GetEditMode();
	VARIANT GetFilter();
	void SetFilter(const VARIANT& newValue);
	long GetPageCount();
	long GetPageSize();
	void SetPageSize(long nNewValue);
	CString GetSort();
	void SetSort(LPCTSTR lpszNewValue);
	long GetStatus();
	long GetState();
	void UpdateBatch(long AffectRecords);
	void CancelBatch(long AffectRecords);
	long GetCursorLocation();
	void SetCursorLocation(long nNewValue);
	LPDISPATCH NextRecordset(VARIANT* RecordsAffected);
	BOOL Supports(long CursorOptions);
	long GetMarshalOptions();
	void SetMarshalOptions(long nNewValue);
	void Find(LPCTSTR Criteria, long SkipRecords, long SearchDirection, const VARIANT& Start);
	void Cancel();
	LPUNKNOWN GetDataSource();
	void SetRefDataSource(LPUNKNOWN newValue);
	void Save(LPCTSTR FileName, long PersistFormat);
	LPDISPATCH GetActiveCommand();
	void SetStayInSync(BOOL bNewValue);
	BOOL GetStayInSync();
	CString GetString(long StringFormat, long NumRows, LPCTSTR ColumnDelimeter, LPCTSTR RowDelimeter, LPCTSTR NullExpr);
	CString GetDataMember();
	void SetDataMember(LPCTSTR lpszNewValue);
	long CompareBookmarks(const VARIANT& Bookmark1, const VARIANT& Bookmark2);
	LPDISPATCH Clone(long LockType);
	void Resync(long AffectRecords, long ResyncValues);
};
/////////////////////////////////////////////////////////////////////////////
// CADORFields wrapper class

class CADORFields : public COleDispatchDriver
{
public:
	CADORFields() {}		// Calls COleDispatchDriver default constructor
	CADORFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CADORFields(const CADORFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	void Refresh();
	LPDISPATCH GetItem(const VARIANT& Index);
	void Append(LPCTSTR Name, long Type, long DefinedSize, long Attrib);
	void Delete(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// CADORField wrapper class

class CADORField : public COleDispatchDriver
{
public:
	CADORField() {}		// Calls COleDispatchDriver default constructor
	CADORField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CADORField(const CADORField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetProperties();
	long GetActualSize();
	long GetAttributes();
	long GetDefinedSize();
	CString GetName();
	long GetType();
	VARIANT GetValue();
	void SetValue(const VARIANT& newValue);
	// method 'GetPrecision' not emitted because of invalid return type or parameter type
	// method 'GetNumericScale' not emitted because of invalid return type or parameter type
	void AppendChunk(const VARIANT& Data);
	VARIANT GetChunk(long Length);
	VARIANT GetOriginalValue();
	VARIANT GetUnderlyingValue();
	LPUNKNOWN GetDataFormat();
	void SetRefDataFormat(LPUNKNOWN newValue);
	// method 'SetPrecision' not emitted because of invalid return type or parameter type
	// method 'SetNumericScale' not emitted because of invalid return type or parameter type
	void SetType(long nNewValue);
	void SetDefinedSize(long nNewValue);
	void SetAttributes(long nNewValue);
};
