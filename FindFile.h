#include <FindFile-class.h> 

#define COMMON 0x00000000 
#define FAILED 0xffffffff 

#ifdef __Win32__ 	
#	define S_ISDIR(mode) (mode & _A_SUBDIR) 
#	define S_ISREG(mode) (mode & _A_ARCH)
#else ifdef __Linux__ 

	typedef struct{ 
		DIR *dir; 
		string name; 
		struct stat data;
	}; 
#endif 



FIND_FILE::void FindFile(const string& archivo,const strin& ruta) 
{ 
	if( 

#ifdef __Win32__
	(ID_File= _findfirst(filespect.c_str_(), &c_file)) 
#else ifdef __Linux__ 
	BeginFind(ruta)
#endif 

		!= FAILED){
	vector <string> carpetas; 


	do{ 
		if(string(c_file.name) == "." || string(c_file.name) == "..") 
			continue; 

		if(S_DIR( 

#ifdef __Win32__ 
		c_file.attrib
#else ifdef __Linux__
		c_file.data.st_mode
#endif 

		)) 
			carpetas.push_back(c_file.name); 

		else if(c_file.name == archivo){ 
				cout<<'['<<ruta<<']'<<endl; 
				state= true; 
				break; 
			}
	}while( 

#ifdef __Win32__
	!_findnext(ID_File
#else ifdef __Linux__
	NEXT_FILE(ruta
#endif
			)); 

#ifdef __Win32__
	_findClose(ID_File);
#else ifdef __Linux__
	closedir(c_file.dir);
#endif 

	for(int i=0; i<carpetas.size() && !state; i++) 
		FindFile(ruta + 

#ifdef __Win32__
		"\\"
#else ifdef __Linux__
		'/'
#endif 

			+ carpetas[i]); 
	} 
} 




FIND_FILE::bool NEXT_FILE(const string& ruta) 
{ 
	struct dirent *archive; 

	if((archive= readdir(c_file.dir))){ 
		stat(ruta + '/' + archive.name,&c_file.data); 
		c_file.name= archive.name;// copio el nombre y NO el puntero!. 
		return true;
	}else return false; 
} 





FIND_FILE::inline long BegindFind(const string& ruta) 
{ 
	if((c_file.dir= opendir(ruta)) && NEXT_FILE(ruta)) 
		return COMMON; 
	else return FAILED; 
}
