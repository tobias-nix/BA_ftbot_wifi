from pathlib import Path
from base.constants import *
import tkinter as tk

class View:
    """
    The View class is responsible for the main window of the application.

    Attributes:
        OUTPUT_PATH: The path to the directory of the current file.
        ASSETS_PATH: The path to the resources directory.
        controller: The controller of the application.
        root: The root window of the application.
        viewPanel: The panel of the view.
    """
    OUTPUT_PATH = Path(__file__).parent
    ASSETS_PATH = OUTPUT_PATH / Path(r"resources")

    def __init__(self, root, controller):
        """
        The constructor for the View class.

        Parameters:
            root: The root window of the application.
            controller: The controller of the application.
        """
        self.controller = controller
        self.root = root
        self.configure()
        self.viewPanel = ViewPanel(root, controller)

    def configure(self):
        """
        The method to configure the root window.
        """
        self.root.title("Ftbot Control")

    @staticmethod
    def relative_to_assets(path: str) -> Path:
        """
        The method to get the path relative to the assets directory.

        Parameters:
            path: The relative path from the assets directory.

        Returns:
            The absolute path.
        """
        return View.ASSETS_PATH / Path(path)


class ViewPanel:
    """
    The ViewPanel class is responsible for the panel of the view.

    Attributes:
        controller: The controller of the application.
        root: The root window of the application.
        keys_pressed: The set of keys that are currently being pressed.
        canvas: The canvas of the panel.
        speed_text: The text of the speed.
        voltage_text: The text of the voltage.
        image_1: The first image.
        image_2: The second image.
        image_3: The third image.
        image_4: The fourth image.
        image_5: The fifth image.
        image_6: The sixth image.
        image_7: The seventh image.
    """

    def __init__(self, root, controller):
        """
        The constructor for the ViewPanel class.

        Parameters:
            root: The root window of the application.
            controller: The controller of the application.
        """
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
        """
        The method to create the graphical user interface. It initializes the canvas, text elements, and images.
        """
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

        self.speed_text = self.create_text(250, 40.0, "0", "#FFFFFF", ("LFT Etica Mono", 96))
        self.voltage_text = self.create_text(50.0, 121.0, "0.0", "#FFFFFF", ("LFT Etica Mono", 48 * -1))
        self.image_1 = self.create_image("image_1.png", 150.0, 554.0)
        self.image_2 = self.create_image("image_2.png", 760.0, 554.0)
        self.image_3 = self.create_image("image_3.png", 798.0, 120.0)
        self.image_4 = self.create_image("image_4.png", 450, 460)
        self.image_5 = self.create_image("image_5.png", 450, 355)
        self.image_6 = self.create_image("image_6.png", 450.0, 200.0)
        self.image_7 = self.create_image("image_7.png", 190.0, 155.0)

    def create_image(self, image_path, x, y):
        """
        Creates an image on the canvas at the specified coordinates.

        Parameters:
            image_path: The path to the image file.
            x: The x-coordinate for the image.
            y: The y-coordinate for the image.

        Returns:
            The ID of the created image.
        """
        image = tk.PhotoImage(file=View.relative_to_assets(image_path))
        image_id = self.canvas.create_image(x, y, image=image)
        setattr(self, f"{image_path}_image", image)
        return image_id

    def create_text(self, x, y, text, fill, font):
        """
        Creates a text element on the canvas at the specified coordinates.

        Parameters:
            x: The x-coordinate for the text.
            y: The y-coordinate for the text.
            text: The text to be displayed.
            fill: The color of the text.
            font: The font of the text.

        Returns:
            The ID of the created text element.
        """
        return self.canvas.create_text(x, y, anchor="nw", text=text, fill=fill, font=font)

    def key_press(self, event):
        """
        Handles the event of a key press. Adds the key to the set of keys being pressed.

        Parameters:
            event: The event object containing information about the key press.
        """
        self.keys_pressed.add(event.keysym)

    def key_release(self, event):
        """
        Handles the event of a key release. Removes the key from the set of keys being pressed.

        Parameters:
            event: The event object containing information about the key release.
        """
        self.keys_pressed.remove(event.keysym)

    def game_loop(self):
        """
        The main game loop. It updates the controller and schedules the next iteration of the game loop.
        """
        self.update_controller()
        self.root.after(GAME_LOOP_DELAY, self.game_loop)

    def update_controller(self):
        """
        Updates the controller based on the keys currently being pressed.
        """
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
        """
        Closes the program when the Escape key is pressed.

        Parameters:
            event: The event object containing information about the key press.
        """
        self.root.destroy()

    def update_view(self, x, y, voltage, speed):
        """
        Updates the view with the given parameters.

        Parameters:
            x: The x-coordinate for the image.
            y: The y-coordinate for the image.
            voltage: The voltage value to be displayed.
            speed: The speed value to be displayed.
        """
        self.canvas.coords(self.image_5, x, y)
        self.canvas.itemconfig(self.voltage_text, text="{:.2f}".format(voltage))
        self.canvas.itemconfig(self.speed_text, text="{:.3f}".format(speed))