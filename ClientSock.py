#client example
import socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('172.16.56.196', 5000))
while 1:
	data = input ("SEND( TYPE q or Q to Quit):")
	if (data != 'Q' and data != 'q'):
		client_socket.send(bytes(data+"\n", 'UTF-8'))
		data=client_socket.recv(512).decode("utf-8")
		print(data);
	else:
    		client_socket.send(bytes(data+"\n", 'UTF-8'))
    		client_socket.close()
    		break;
