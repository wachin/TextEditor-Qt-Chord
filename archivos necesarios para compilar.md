

se necestia el paquete :

qt5-make

que ya está instalado, este paquete contiene la siguiente ruta necesaria:

/usr/lib/i386-linux-gnu/qt5/mkspecs/linux-g++

Actualiza las rutas de configuración en tu archivo .pro:

Abre tu archivo .pro en Qt Creator.

Verifica que las rutas de configuración sean correctas. Puedes hacerlo modificando las siguientes líneas:

QMAKE_INCDIR += /usr/include/qt5
QMAKE_LIBDIR += /usr/lib/i386-linux-gnu/qt5

Asegúrate de que estas rutas coincidan con las ubicaciones reales en tu sistema.
