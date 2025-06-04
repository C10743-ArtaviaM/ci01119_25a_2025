import socket
import os

HOST = '127.0.0.1'
PORT = 12345
USER_FILE = 'users.txt'

# Load users from file
def load_users():
    users = {}
    if os.path.exists(USER_FILE):
        with open(USER_FILE, 'r') as f:
            for line in f:
                if ':' in line:
                    username, password = line.strip().split(':', 1)
                    users[username] = password
    return users

# Save a new user to file
def save_user(username, password):
    with open(USER_FILE, 'a') as f:
        f.write(f"{username}:{password}\n")

users = load_users()

def handle_client(conn, addr):
    print(f"Connected by {addr}")
    try:
        data = conn.recv(1024).decode().strip()
        print(f"Received: {data}")

        if data.startswith("REGISTER:"):
            parts = data.split(":", 2)
            if len(parts) == 3:
                _, username, password = parts
                if username in users:
                    conn.sendall(b"FAIL\n")  # Username already exists
                else:
                    users[username] = password
                    save_user(username, password)
                    print(f"User registered: {username}")
                    conn.sendall(b"OK\n")
            else:
                conn.sendall(b"FAIL\n")

        elif ":" in data:
            username, password = data.split(":", 1)
            if users.get(username) == password:
                conn.sendall(b"OK\n")
            else:
                conn.sendall(b"FAIL\n")
        else:
            conn.sendall(b"FAIL\n")
    except Exception as e:
        print(f"Error handling client {addr}: {e}")
        conn.sendall(b"FAIL\n")
    finally:
        conn.close()
        print(f"Connection with {addr} closed")

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print(f"Server listening on {HOST}:{PORT}")

        while True:
            conn, addr = s.accept()
            handle_client(conn, addr)

if __name__ == "__main__":
    start_server()
