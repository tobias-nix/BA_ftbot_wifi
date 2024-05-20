import socket
import threading
import keyboard

# Global flag to control the server's running state
server_running = True


def start_server(host='192.168.10.2', port=55719):
    global server_running
    message_count = 0  # Initialize message counter
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket:
        server_socket.bind((host, port))
        print(f"Listening for incoming UDP messages on {host}:{port}")

        while server_running:
            server_socket.settimeout(5)
            try:
                message, client_address = server_socket.recvfrom(1024)
                message_count += 1  # Increment message counter
                print(f"Message {message_count} from {client_address}: {message}")
            except socket.timeout:
                continue

def run_server():
    server_thread = threading.Thread(target=start_server)
    server_thread.start()

    print("Press ESCAPE to terminate the program.")
    while True:
        if keyboard.is_pressed('esc'):
            print("ESCAPE key pressed. Exiting...")
            stop_server()
            break

    server_thread.join()


def stop_server():
    global server_running
    server_running = False


if __name__ == "__main__":
    run_server()

