from pathlib import Path
from tkinter import Tk, Canvas
from tkinter import Tk, Canvas, PhotoImage

OUTPUT_PATH = Path(__file__).parent
ASSETS_PATH = OUTPUT_PATH / Path(r"build/assets/frame0")

def relative_to_assets(path: str) -> Path:
    return ASSETS_PATH / Path(path)

class View:
    def __init__(self):
        self.window = Tk()
        self.window.geometry("900x600")
        self.window.configure(bg="#494D5B")
        self.canvas = Canvas(
            self.window,
            bg="#494D5B",
            height=600,
            width=900,
            bd=0,
            highlightthickness=0,
            relief="ridge"
        )

        self.canvas.create_text(
            410,
            40.0,
            anchor="nw",
            text="0",
            fill="#FFFFFF",
            font=("LFT Etica Mono", 96)
        )

        self.image_image_1 = PhotoImage(
            file=self.relative_to_assets("image_1.png"))
        self.image_1 = self.canvas.create_image(
            150.0,
            554.0,
            image=self.image_image_1
        )
        
        self.image_image_2 = PhotoImage(
            file=self.relative_to_assets("image_2.png"))
        self.image_2 = self.canvas.create_image(
            760.0,
            554.0,
            image=self.image_image_2
        )

        self.canvas.create_text(
            70.0,
            121.0,
            anchor="nw",
            text="0.0",
            fill="#FFFFFF",
            font=("LFT Etica Mono", 48 * -1)
        )

        self.image_image_3 = PhotoImage(
            file=self.relative_to_assets("image_3.png"))
        self.image_3 = self.canvas.create_image(
            798.0,
            120.0,
            image=self.image_image_3
        )

        self.image_image_4 = PhotoImage(
            file=self.relative_to_assets("image_4.png"))
        self.image_4 = self.canvas.create_image(
            450,
            460,
            image=self.image_image_4
        )

        self.image_image_5 = PhotoImage(
            file=self.relative_to_assets("image_5.png"))
        self.image_5 = self.canvas.create_image(
            450,
            355,
            image=self.image_image_5
        )

        self.image_image_6 = PhotoImage(
            file=self.relative_to_assets("image_6.png"))
        self.image_6 = self.canvas.create_image(
            450.0,
            200.0,
            image=self.image_image_6
        )

        self.image_image_7 = PhotoImage(
            file=self.relative_to_assets("image_7.png"))
        self.image_7 = self.canvas.create_image(
            190.0,
            155.0,
            image=self.image_image_7
        )

        self.window.resizable(False, False)
        self.window.mainloop()
    
    def display(self):
        pass
    def relative_to_assets(self, path: str) -> Path:
        return ASSETS_PATH / Path(path)