import threading
from typing import Callable, Tuple


class ThreadManager:
    def __init__(self):
        self.threads = []
        self.stop_event = threading.Event()

    def start_threads(self, target: Callable, args: Tuple) -> None:
        thread = threading.Thread(target=target, args=args)
        self.threads.append(thread)
        thread.start()

    def stop_threads(self) -> None:
        self.stop_event.set()
        for thread in self.threads:
            thread.join()
