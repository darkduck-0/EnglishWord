import tkinter

class MainForm:
    def __init__(self):
        root = tkinter.Tk()
        root.title("EnglishWord")
        root.geometry("800x600")
        root.maxsize(1200, 800)
        root.mainloop()

def main():
    MainForm()

if __name__ == "__main__":
    main()