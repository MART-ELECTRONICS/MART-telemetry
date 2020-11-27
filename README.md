# Grabación de datos de sensores con Raspberry Pi 3B+

En este documento explico como conectar una Arduino a una Rasperry Pi por puerto serie para obtener los datos y grabarlos en la microSD.

## Empezando desde 0 con la Raspberry Pi

Para empezar hace falta instalar el SO en la RPi. Para grabar el SO en la microSD, se recomiendo usar el software proporcionado por los creadores, [Raspberry Pi Imager](https://www.raspberrypi.org/software/). 

Para instalar el sistema:

1. Meter la microSD en el PC
2. Seleccionar el SO, se recomienda usar el Raspberry Pi OS (32-bits).
3. Seleccionar la microSD
4. Pulsar write

Para iniciar el sistema, encendemos la Raspberry Pi. Ésta necesita 5V/700mA para correr, por lo que con un adaptador de móvil conectado al puerto micro USB basta.

Al conectar el cable ésta se enciende automáticamente y se inicia el sistema. Hay que conectar un teclado, un ratón y una pantalla a la Raspberry para poder usarla, al menos al principio. Ahora contaré como no necesitarlos. Para iniciar el usuario las credenciales son las siguientes:

- usuario: `pi`
- contraseña: `raspberry`

## Configurar SSH para usar la Raspberry Pi desde remoto (opcional)

Si ya has conectado el teclado y la pantalla a tu Raspberry, también puedes habilitar el acceso SSH desde la terminal. Para ello, inicia la línea de comandos **(Ctrl+Alt+T)** y escribe el siguiente comando:

```bash
sudo raspi-config
```

Aparecerá un menú así:

![raspi-config](./assets/1.png)

En el menú, selecciona primero el punto `3 ("Interface Options")` y después `P2 ("SSH")`.

![raspi-config](./assets/2.png)

La herramienta te preguntará si deseas activar el servidor SSH, lo que deberás confirmar antes de cerrar los ajustes con "Finish".

Para conectarte desde otro PC saber la IP de la Raspberry Pi. Para verla, escribe en la terminal:

```bash
hostname –I`
```

En mi caso la IP es `192.168.0.159`. Para conectarme desde mi PC, instalé [PuTTY](https://www.putty.org/) (un cliente SSH para Windows.) y en la terminal pongo:

```powershell
ssh pi@192.168.0.159
```

Te pedirá la contraseña, que es la de antes, y listo, ya puedes acceder a toda la funcionalidad de la RPi sin necesidad de pantallas y teclados.

## Acceder a los puertos serie

Para ver los puertos serie de la Raspberry Pi hace falta escribir el siguiente comando:

```bash
ls /dev/tty*
```

La salida será más o menos así:

![dev/tty](./assets/3.png)

Para encontrar la Arduino por USB a la Raspberry Pi, la conectas, y vuelves a ejecutar el comando para ver la lista y encontrar el nuevo elemento.

En mi caso (y seguramente en el tuyo) es `ACM0`.

## Acceso a puerto serie desde Python (opcional)

Para probar si funciona todo bien, usaré Python para hacerlo rápido y no tener que usar C++.

Para ello, necesitaremos las librerías `python-serial` para la Raspberry Pi y `pyserial` para Python. Para instalarlas:

```bash
sudo apt-get install python-serial
sudo pip install pyserial
```

Para escribir el script desde la terminal, usaremos ´nano´.

```bash
nano serial_read.py
```

Se abrirá la ventana para editar y el código será el siguiente:

```python
import serial
# Inicio del puerto serie en dev/ttyACM0 a 9600 baudios
ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    read_serial=ser.readline()
    print(read_serial)
```

Para guardar el archivo, **Ctrl+S** y para salir,   **Ctrl+X**. Para ejecutarlo, hay que escribir:

```bash
python serial_read.py
```
