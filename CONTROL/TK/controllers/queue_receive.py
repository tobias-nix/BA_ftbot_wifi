from queue import Queue


class ReceiveQueue:
    def __init__(self):
        self.queue = Queue()

    def put(self, data: bytes):
        self.queue.put(data)

    def get(self):
        return self.queue.get()

    def is_empty(self):
        return self.queue.empty()

    def qsize(self):
        return self.queue.qsize()

    def clear(self):
        with self.queue.mutex:
            self.queue.queue.clear()
