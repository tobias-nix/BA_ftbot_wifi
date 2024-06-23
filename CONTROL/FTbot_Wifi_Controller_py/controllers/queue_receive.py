from queue import Queue

class ReceiveQueue:
    """
    The ReceiveQueue class is a wrapper around the built-in Queue class in Python.

    Attributes:
        queue: The queue for storing data.
    """

    def __init__(self):
        """
        The constructor for the ReceiveQueue class.
        """
        self.queue = Queue()

    def put(self, data: bytes):
        """
        The method to add data to the queue.

        Parameters:
            data: The data to be added to the queue.
        """
        self.queue.put(data)

    def get(self):
        """
        The method to get data from the queue.

        Returns:
            The data from the queue.
        """
        return self.queue.get()

    def is_empty(self):
        """
        The method to check if the queue is empty.

        Returns:
            A boolean value indicating whether the queue is empty.
        """
        return self.queue.empty()

    def qsize(self):
        """
        The method to get the size of the queue.

        Returns:
            The size of the queue.
        """
        return self.queue.qsize()

    def clear(self):
        """
        The method to clear the queue.
        """
        with self.queue.mutex:
            self.queue.queue.clear()