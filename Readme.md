Comport to TCP Bridge
======================
connect a serial com port to a tcp server and connect to this tcp server via a telnet console.
data can be forwarded bidirectionally.

possible Arguments:
-------------------
Enter c to see all available Comports
Enter p <comport> to connect to it!
Enter t <port> for where to connect via tcp to it! Default is 9800
Enter b < Baudrate> for the Baudrate of the Comport! Default is 115200
Enter t <ipaddress> for the tcp server you want to connect with

Example:
========
comporttotcpbridge c p COM3 t 6000 b 9600


Can be built with qt4 and newer versions!
------------------------------------------
