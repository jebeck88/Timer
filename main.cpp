#include <QtCore>

#include <stdlib.h>

#include "Application.h"
#include "Dialog.h"

int main( int argc, char *argv[] )
{
    try
    {
        Application app( argc, argv );
        app.getWindow()->show();
        app.getWindow()->raise();
        app.getWindow()->activateWindow();
        return app.exec();
    }
	catch ( ... )
	{
		return 1;
	}
}
