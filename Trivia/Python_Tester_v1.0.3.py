import socket
import json
from sys import getsizeof

SERVER_ADDR = "127.0.0.1", 2410
BUFF = 1024
SIZEOF_INT = 4

OPERATIONS = [
    "login", "signup", "error", "signout", "get rooms", "get players in room", "get player's stats", "get high score",
    "join room", "create room"
]

CODES = {}


def fill_codes():
    global CODES
    code = 101
    for i in OPERATIONS:
        CODES[i] = chr(code).encode()
        code += 1


def create_message(kind: str, message: dict) -> bytes:
    return CODES[kind] + len(json.dumps(message)).to_bytes(SIZEOF_INT, 'little') + json.dumps(
        message).encode()


def send_message(message: bytes, sock: socket.socket):
    print("Message:", message)
    sock.sendall(message)
    response = sock.recv(BUFF)
    print("Response:", response)


def create_sock_and_send(messages: list, address: tuple):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(address)
        for msg in messages:
            send_message(msg, sock)


def main():
    fill_codes()
    print(CODES)

    real_signup_msg = {
        "username": "alonkh2",
        "password": "1234",
        "mail": "alonkh2@gmail.com"
    }

    real_login_msg = {
        "username": "alonkh2",
        "password": "1234"
    }

    real_create_room_msg = {
        "name": "try",
        "timeout": "100",
        "max": "5",
        "count": "6"
    }

    fake_login_msg = {
        "username": "mikeseg",
        "password": "1234"
    }

    real_signout_msg = {
        "username": "alonkh2"
    }

    real_signup_msg = create_message("signup", real_signup_msg)

    real_login_msg = create_message("login", real_login_msg)

    real_create_room_msg = create_message("create room", real_create_room_msg)
    
    real_signout_msg = create_message("signout", real_signout_msg)
    
    fake_login_msg = create_message("login", fake_login_msg)

    create_sock_and_send([real_signup_msg], SERVER_ADDR)

    create_sock_and_send([real_login_msg, real_create_room_msg, real_signout_msg], SERVER_ADDR)

    create_sock_and_send([fake_login_msg], SERVER_ADDR)


if __name__ == '__main__':
    main()
