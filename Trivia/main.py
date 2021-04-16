import socket

SERVER_ADDR = "127.0.0.1", 2410


def main():
    msg = "Hello"

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(SERVER_ADDR)

        print("Client message: ", msg)
        sock.sendall(msg.encode())
        server_resp = sock.recv(1024)
        server_resp = server_resp.decode()
        print("Server message: ", server_resp)

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s2:  # Checking that the threads work
            s2.connect(SERVER_ADDR)

            print("Client2 message: ", msg)
            s2.sendall(msg.encode())
            server_resp = s2.recv(1024)
            server_resp = server_resp.decode()
            print("Server message: ", server_resp)

if __name__ == '__main__':
    main()