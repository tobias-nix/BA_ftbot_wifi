import tkinter as tk
from tkinter import messagebox

class MessageWindow:
    """
    The MessageWindow class provides static methods for displaying different types of message boxes.

    Methods:
        show_info: Displays an information message box.
        show_error: Displays an error message box.
        show_warning: Displays a warning message box.
        show_question: Displays a question message box and returns the user's response.
    """

    @staticmethod
    def show_info(message: str):
        """
        Displays an information message box.

        Parameters:
            message: The message to be displayed in the message box.
        """
        messagebox.showinfo("Information", message)

    @staticmethod
    def show_error(message: str):
        """
        Displays an error message box.

        Parameters:
            message: The message to be displayed in the message box.
        """
        messagebox.showerror("Error", message)

    @staticmethod
    def show_warning(message: str):
        """
        Displays a warning message box.

        Parameters:
            message: The message to be displayed in the message box.
        """
        messagebox.showwarning("Warning", message)

    @staticmethod
    def show_question(message: str):
        """
        Displays a question message box and returns the user's response.

        Parameters:
            message: The message to be displayed in the message box.

        Returns:
            The user's response to the question.
        """
        answer = messagebox.askretrycancel("Try again?", message)
        return answer