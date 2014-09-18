#include <windows.h>
//#include <sys\stat.h>
#include <iostream>
#include <vector>
#include <string>


#include <direct.h>
#include <io.h>

#define __Win32__






#define S_ISDIR(mode) (mode & _A_SUBDIR) 
#define S_ISREG(mode) (mode & _A_ARCH)


/*
#ifdef __Win32__ 
#	ifndef S_ISDIR
#		define S_ISDIR(mode)  (((mode) & S_IFMT) == S_IFDIR)
#	endif

#	ifndef S_ISREG
#		define S_ISREG(mode)  (((mode) & S_IFMT) == S_IFREG)
#	endif
#endif
*/


using namespace std;



	 struct _finddata_t c_file;
	 long hFile;
	 string filespec;



void FindFile (const string& archivo, const string& ruta)
{
	static struct _finddata_t c_file;
	static long hFile;
	static string filespec;

	filespec = ruta + "\\*.*";
	if ((hFile = _findfirst (filespec.c_str(), &c_file )) == -1L )
		return;

	vector<string> carpetas;
	do {
		if (S_ISREG(c_file.attrib)) { // no es un subdirectorio; és un archivo!
			if (c_file.name == archivo)
				cout << '[' << ruta << ']' << endl;
		} else if (S_ISDIR(c_file.attrib) && strcmp (c_file.name, ".") && strcmp (c_file.name, ".."))
			carpetas.push_back (c_file.name);
	} while (_findnext( hFile, &c_file ) == 0);
	_findclose( hFile );

	for (int i = 0; i < carpetas.size (); ++i)
		FindFile (archivo, ruta + "\\" + carpetas[i]);
}

int main(int argc, char* argv[])
{
   FindFile ("Copia (2) de nik-3.o", "D:\\cool\\-desarrollo-");
   return 0;
}


