import socket

HOST = 'localhost'  # The server's hostname or IP address
PORT = 8824       # The port used by the server
MESSAGE = b'Hello'

# Create a TCP/IP socket
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    # Connect to the server
    s.connect((HOST, PORT))

    data = s.recv(1024)
    
    # Send the message
    if data.decode() == "Hello":
        s.sendall(MESSAGE)
    



# Print the response received from the server

print('Received', repr(data))
