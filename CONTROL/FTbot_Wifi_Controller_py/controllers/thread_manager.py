import threading
from typing import Callable, Tuple

class ThreadManager:
    """
    The ThreadManager class is responsible for managing threads in the application.

    Attributes:
        threads: A list of all the threads that have been created.
        stop_event: An event that can be set to signal the threads to stop.
    """

    def __init__(self):
        """
        The constructor for the ThreadManager class.
        """
        self.threads = []
        self.stop_event = threading.Event()

    def start_threads(self, target: Callable, args: Tuple) -> None:
        """
        The method to start a new thread.

        Parameters:
            target: The function to be run in the new thread.
            args: The arguments to be passed to the target function.
        """
        thread = threading.Thread(target=target, args=args)
        self.threads.append(thread)
        thread.start()

    def stop_threads(self) -> None:
        """
        The method to stop all the threads.
        """
        self.stop_event.set()
        for thread in self.threads:
            thread.join()