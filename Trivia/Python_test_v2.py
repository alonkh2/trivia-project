import socket
import json
from sys import getsizeof

SERVER_ADDR = "127.0.0.1", 2410
BUFF = 1024


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

    signup_msg_json = b"f" + len(json.dumps(signup_msg)).to_bytes(4, byteorder="big") + json.dumps(signup_msg).encode()
    login_msg_json = b"e" + len(json.dumps(login_msg)).to_bytes(4, byteorder="big") + json.dumps(login_msg).encode()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(SERVER_ADDR)

        print("Signup msg: ", signup_msg_json)
        sock.sendall(signup_msg_json.encode())
        server_resp = sock.recv(BUFF)
        server_resp = server_resp.decode()
        print("Server message: ", server_resp)


if __name__ == '__main__':
    main()

