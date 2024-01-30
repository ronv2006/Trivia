import socket

HOST = 'localhost'  # The server's hostname or IP address
PORT = 8824       # The port used by the server


# Convert ASCII value 83 to a byte
login = bytes([83])
signup = bytes([84])
# Create the JSON message
login_str = "{" + '"' + "username:" + '"' + " : " + '"' + str(1) + '"' + " , "  + '"'+ "password:" + '"' + ": " + '"' + str(5) +'"' + " }"
signup_str = "{" + '"' + "username:" + '"' + " : " + '"' + str(1) + '"' + " , "  + '"'+ "password:" + '"' + ": " + '"' + str(5) +'"' + "," + '"' + "email:" + '"' " :" + " " + '"' + "hi" + '"' + "}"
print(signup_str)
login_ascii_size = bytes([len(login_str)])
signup_ascii_size = bytes([len(signup_str)])
size_0 = bytes([0])
# Combine the parts into a single string

login_message = login + size_0 + size_0 + size_0 + login_ascii_size + login_str.encode()
signup_message = signup + size_0 + size_0 + size_0 + signup_ascii_size + signup_str.encode()

# Create a TCP/IP socket
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

    # Connect to the server
    s.connect((HOST, PORT))



    # Send the message

    s.sendall(login_message)
    messageFromServer = s.recv(1024)

    print(messageFromServer.decode())

    s.sendall(signup_message)
    messageFromServer = s.recv(1024)
    print(messageFromServer.decode())
    while True:
        pass

    



# Print the response received from the server

