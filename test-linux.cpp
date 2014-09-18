#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include <iostream>
#include <vector>
#include <string>

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

void FindFile (const string& archivo, const string& ruta)
{
	static DIR *dir;
	static struct dirent *mi_dirent;
		
	if( (dir = opendir (ruta.c_str())) == NULL )
		return;

	vector<string> carpetas;
	while ((mi_dirent = readdir (dir)) != NULL) {
		if (string (mi_dirent->d_name) == "." || string (mi_dirent->d_name) == "..")
			continue;
		string cadina = ruta + '/' + mi_dirent->d_name;
		struct stat structura;
		if (stat (cadina.c_str(), &structura) < 0)
			;//cout << "error en stat" << endl;
		else if (S_ISDIR (structura.st_mode))
			carpetas.push_back (mi_dirent->d_name);
		else if (archivo == mi_dirent->d_name)
			cout << '[' << cadina << ']' << endl;
	}
	closedir (dir);

	for (int i = 0; i < carpetas.size(); ++i)
		FindFile (archivo, ruta + '/' + carpetas[i]);
}

int main ( int argc, char *argv[] )
{
	FindFile (argv[1], argv[2]);
	return 0;
}


