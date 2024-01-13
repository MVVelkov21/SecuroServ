import os

class DigitalWillMenu:
    def __init__(self):
        self.will_data = {}  

    def display_menu(self):
        print("  ____            _     _                         _ ")
        print(" |  _ \\  __ _ ___| |__ | |__   ___   __ _ _ __ __| |")
        print(" | | | |/ _` / __| '_ \\| '_ \\ / _ \\ / _` | '__/ _` |")
        print(" | |_| | (_| \\__ \\ | | | |_) | (_) | (_| | | | (_| |")
        print(" |____/ \\__,_|___/_| |_|_.__/ \\___/ \\__,_|_|  \\__,_|")

        print("1. Create a new will")
        print("2.View your will")
        print("3. Exit")
        

    def create_will(self):
        
        name = str(input("Enter your name please: "))
        print("I",name,"\nGive away my money to my children split equaly.")
    def view_will(self):
            
            print("Viewing existing will...")
            

    
    def run_menu(self):
        while True:
            self.display_menu()
            choice = input("Enter your choice: ")
            if choice == "1":
                self.create_will()
            elif choice == "2":
                self.view_will()
            elif choice == "3":
                print("Exiting the Digital Will System")
                break
            else:
                print("Invalid choice. Please try again.")


menu = DigitalWillMenu()
menu.run_menu()