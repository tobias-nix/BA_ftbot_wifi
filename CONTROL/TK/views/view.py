from pathlib import Path
from base.constants import *
import tkinter as tk


class View:
    OUTPUT_PATH = Path(__file__).parent
    ASSETS_PATH = OUTPUT_PATH / Path(r"resources")

    def __init__(self, root, controller):
        self.controller = controller
        self.root = root
        self.configure()
        self.viewPanel = ViewPanel(root, controller)

    def configure(self):
        self.root.title("Ftbot Control")

    @staticmethod
    def relative_to_assets(path: str) -> Path:
        return View.ASSETS_PATH / Path(path)


class ViewPanel:
    def __init__(self, root, controller):
        self.controller = controller
        self.root = root
        self.keys_pressed = set()
        root.bind('<Key>', self.key_press)
        root.bind('<KeyRelease>', self.key_release)
        root.bind('<Escape>', self.close_program)
        self.canvas = None
        self.speed_text = None
        self.voltage_text = None
        self.image_1 = None
        self.image_2 = None
        self.image_3 = None
        self.image_4 = None
        self.image_5 = None
        self.image_6 = None
        self.image_7 = None

        self.create_gui()

    def create_gui(self):
        self.canvas = tk.Canvas(
            self.root,
            bg="#494D5B",
            height=600,
            width=900,
            bd=0,
            highlightthickness=0,
            relief="ridge"
        )
        self.canvas.pack()

        self.speed_text = self.create_text(410, 40.0, "0", "#FFFFFF", ("LFT Etica Mono", 96))
        self.voltage_text = self.create_text(70.0, 121.0, "0.0", "#FFFFFF", ("LFT Etica Mono", 48 * -1))
        self.image_1 = self.create_image("image_1.png", 150.0, 554.0)
        self.image_2 = self.create_image("image_2.png", 760.0, 554.0)
        self.image_3 = self.create_image("image_3.png", 798.0, 120.0)
        self.image_4 = self.create_image("image_4.png", 450, 460)
        self.image_5 = self.create_image("image_5.png", 450, 355)
        self.image_6 = self.create_image("image_6.png", 450.0, 200.0)
        self.image_7 = self.create_image("image_7.png", 190.0, 155.0)

    def create_image(self, image_path, x, y):
        image = tk.PhotoImage(file=View.relative_to_assets(image_path))
        image_id = self.canvas.create_image(x, y, image=image)
        setattr(self, f"{image_path}_image", image)
        return image_id

    def create_text(self, x, y, text, fill, font):
        return self.canvas.create_text(x, y, anchor="nw", text=text, fill=fill, font=font)

    def key_press(self, event):
        self.keys_pressed.add(event.keysym)

    def key_release(self, event):
        self.keys_pressed.remove(event.keysym)

    def game_loop(self):
        self.update_controller()
        self.root.after(GAME_LOOP_DELAY, self.game_loop)

    def update_controller(self):
        key_actions = {
            'w': self.controller.increase_throttle,
            's': self.controller.decrease_throttle,
            'a': self.controller.steering_input_left,
            'd': self.controller.steering_input_right,
        }
        for key, action in key_actions.items():
            if key in self.keys_pressed:
                action()

        if not any(key in self.keys_pressed for key in ['w', 's']):
            self.controller.decrease_throttle_to_zero()

    def close_program(self, event):
        self.root.destroy()

    def update_view(self, x, y, voltage, speed):
        self.canvas.coords(self.image_5, x, y)
        self.canvas.itemconfig(self.voltage_text, text=str(voltage))
        self.canvas.itemconfig(self.speed_text, text=str(speed))
