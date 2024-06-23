import socket
import threading
import keyboard

"""
This Python program is a simple UDP server that listens for incoming messages. 
It runs in a separate thread and can be stopped by pressing the ESCAPE key. The 
server prints each incoming message along with a count of the total messages 
received so far. The server continues to run and receive messages until the ESCAPE key is pressed, 
at which point it stops.
"""

# Global flag to control the server's running state
server_running = True

def start_server(host='192.168.10.2', port=55719):
    """
    This function starts a UDP server that listens for incoming messages.
    The server runs in a loop until the global flag 'server_running' is set to False.

    Args:
        host (str): The host on which the server is to run. Defaults to '192.168.10.2'.
        port (int): The port on which the server is to listen. Defaults to 55719.
    """
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
    """
    This function starts the server in a separate thread and listens for the ESCAPE key press.
    When the ESCAPE key is pressed, it calls the stop_server function to stop the server.
    """
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
    """
    This function sets the global flag 'server_running' to False, signaling the server to stop.
    """
    global server_running
    server_running = False

if __name__ == "__main__":
    """
    This is the entry point of the program.
    It calls the run_server function to start the server.
    """
    run_server()