


#define DLLClass __declspec(dllexport) 
#define DLLClass __declspec(dllimport) ;  



{
public:	
	testdll() {}
	void setMember(int value);
	int getMember();
private:
	int _member;


};
