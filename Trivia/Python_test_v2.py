import socket
import json
from sys import getsizeof

SERVER_ADDR = "127.0.0.1", 2410
BUFF = 1024
SIZEOF_INT = 4


def main():

    signup_msg = {
        "username": "alonkh2",
        "password": "1234",
        "mail": "alonkh2@gmail.com"
    }

    login_msg = {
        "username": "alonkh2",
        "password": "1234"
    }

    signup_msg_json = b"f" + len(json.dumps(signup_msg)).to_bytes(SIZEOF_INT, 'little') + json.dumps(signup_msg).encode()
    login_msg_json = b"e" + len(json.dumps(signup_msg)).to_bytes(SIZEOF_INT, 'little') + json.dumps(login_msg).encode()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(SERVER_ADDR)

        print("Signup msg: ", signup_msg_json)
        sock.sendall(signup_msg_json)
        server_resp = sock.recv(BUFF)
        print("Server message: code:", ord(server_resp[:1]), ", len:", int.from_bytes(server_resp[1:5], 'little'), "content: ", server_resp[5:].decode())  # Formatting server message
    

if __name__ == '__main__':
    main()

