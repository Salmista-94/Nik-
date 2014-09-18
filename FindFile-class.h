class FIND_FILE{
#ifdef __Win32__
	_finddata_t c_file;
	
#else ifdef __Linux__
	DIR *dir;
	struct stat data;
	dirent file, *auxfile;
#endif
	string name;
	
	void FindFile(void);
	void FindFile(const string& archivo, const string& ruta);
	
#ifdef __Linux__
	FIND_FILE(void);
	FIND_FILE(struct F_DATA dat);
	
	bool NEXT_FILE(void)
	long BegindFind(void);
#endif
};

/*

	static struct
#ifdef __Win32__
		_finddata_t
#else ifdef __Linux__
		FIND_DATA
#endif
		c_file;
		
#ifdef __Win32__
	static long ID_File;
	static string filespect= ruta + "\\*.*";
#endif

	static bool state= false;
	*/
