import tkinter as tk
from tkinter import messagebox


class MessageWindow:
    @staticmethod
    def show_info(message: str):
        messagebox.showinfo("Information", message)

    @staticmethod
    def show_error(message: str):
        messagebox.showerror("Error", message)

    @staticmethod
    def show_warning(message: str):
        messagebox.showwarning("Warning", message)

    @staticmethod
    def show_question(message: str):
        answer = messagebox.askretrycancel("Try again?", message)
        return answer
