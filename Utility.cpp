// Utility.cpp

#include "Utility.hpp"

QString ExtractFileName(QString path)
{
	int index = -1;
	path.replace('\\', '/');
	index = path.lastIndexOf('/');

	if (index == -1) {
		return path;
	} else {
		return path.mid(index+1);
	}
}
