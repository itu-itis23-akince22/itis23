class Library:
    def __init__(self, file_name="books.txt"):
        self.file_name = file_name
        try:
            self.file = open(self.file_name, "a+")
            self.file.seek(0)
        except FileNotFoundError:
            print(f"File '{self.file_name}' not found.")
            exit(1)
        except Exception as e:
            print(f"An error occurred while opening the file: {e}")
            exit(1)

    def __del__(self):
        try:
            self.file.close()
        except Exception as e:
            print(f"An error occurred while closing the file: {e}")

    def list_books(self):
        try:
            self.file.seek(0)
            book_lines = self.file.read().splitlines()
            for line in book_lines:
                book_info = line.split(',')
                book_title = book_info[0]
                book_author = book_info[1]
                print(f"Book Title: {book_title}, Author: {book_author}")
        except Exception as e:
            print(f"An error occurred while listing books: {e}")

    def add_book(self):
        try:
            book_title = input("Enter book title: ")
            book_author = input("Enter book author: ")
            release_year = input("Enter release year: ")
            num_pages = input("Enter number of pages: ")
            book_info = f"{book_title},{book_author},{release_year},{num_pages}\n"
            self.file.write(book_info)
            print("Book added successfully.")
        except Exception as e:
            print(f"An error occurred while adding the book: {e}")

    def remove_book(self, book_title):
        try:
            self.file.seek(0)
            book_lines = self.file.read().splitlines()
            updated_book_lines = [line for line in book_lines if book_title not in line.split(',')[0]]
            self.file.seek(0)
            self.file.truncate()
            for line in updated_book_lines:
                self.file.write(line + '\n')
            print(f"Book '{book_title}' removed successfully.")
        except Exception as e:
            print(f"An error occurred while removing the book: {e}")



def menu(lib):
    print("*** MENU ***")
    print("1) List Books")
    print("2) Add Book")
    print("3) Remove Book")

    choice = input("Enter your choice (1/2/3): ")

    if choice == '1':
        lib.list_books()
    elif choice == '2':
        lib.add_book()
    elif choice == '3':
        book_to_remove = input("Enter the title of the book to remove: ")
        lib.remove_book(book_to_remove)
    else:
        print("Invalid choice!")



lib = Library()

while True:
    menu(lib)
    cont = input("Do you want to continue? (yes/no): ")
    if cont.lower() != 'yes':
        break
