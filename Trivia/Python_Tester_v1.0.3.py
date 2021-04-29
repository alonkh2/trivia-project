import socket
import json
from sys import getsizeof

SERVER_ADDR = "127.0.0.1", 2410
BUFF = 1024
SIZEOF_INT = 4


def main():

    real_signup_msg = {
        "username": "alonkh2",
        "password": "1234",
        "mail": "alonkh2@gmail.com"
    }

    real_login_msg = {
        "username": "alonkh2",
        "password": "1234"
    }

    fake_login_msg = {
        "username": "mikeseg",
        "password": "1234"
    }

    real_signup_msg = b"f" + len(json.dumps(real_signup_msg)).to_bytes(SIZEOF_INT, 'little') + json.dumps(real_signup_msg).encode()
    real_login_msg = b"e" + len(json.dumps(real_login_msg)).to_bytes(SIZEOF_INT, 'little') + json.dumps(real_login_msg).encode()

    fake_login_msg = b"e" + len(json.dumps(fake_login_msg)).to_bytes(SIZEOF_INT, 'little') + json.dumps(fake_login_msg).encode()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as real_signup_sock:  # Sending real signup message
        real_signup_sock.connect(SERVER_ADDR)

        print("Real Signup msg: ", real_signup_msg)
        real_signup_sock.sendall(real_signup_msg)
        server_resp = real_signup_sock.recv(BUFF)
        print("Server message: ", server_resp)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as real_login_sock:  # Sending real login message
        real_login_sock.connect(SERVER_ADDR)

        print("Real login msg: ", real_login_msg)
        real_login_sock.sendall(real_login_msg)
        server_resp = real_login_sock.recv(BUFF)
        print("Server message: ", server_resp)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as fake_login_sock:  # Sending fake login message
        fake_login_sock.connect(SERVER_ADDR)

        print("Fake login msg: ", fake_login_msg)
        fake_login_sock.sendall(fake_login_msg)
        server_resp = fake_login_sock.recv(BUFF)
        print("Server message: ", server_resp)


if __name__ == '__main__':
    main()

