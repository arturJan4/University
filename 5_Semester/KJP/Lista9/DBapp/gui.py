# left some TODO's for future me
# but sending current (not pretty, but working) version to meet the deadline

import tkinter as tk
from tkinter import ttk
from tkinter.messagebox import showinfo

# TODO: better imports
from model import *


def select_row(event):
    """Copy currently selected row into entries values"""
    clear_entry()

    selected_row = tree.focus()

    # no elements in the table
    if not selected_row:
        return

    values = tree.item(selected_row, 'values')

    title_entry.insert(0, values[1])
    author_entry.insert(0, values[2])
    publisher_entry.insert(0, values[3])
    isbn_entry.insert(0, values[4])
    release_entry.insert(0, values[5])


def clear_entry():
    """Clears all text input"""
    title_entry.delete(0, "end")
    author_entry.delete(0, "end")
    publisher_entry.delete(0, "end")
    isbn_entry.delete(0, "end")
    release_entry.delete(0, "end")


def query_book():
    """fill the table with books in the database"""
    books = get_books()

    count = 0

    for record in books:
        print(record.id)
        vals = (record.id, record.title, record.author, record.publisher, record.isbn, record.release_year)
        tree.insert(parent='', index='end', iid=record.id, text='', values=vals)
        count += 1


def add_book_cmd():
    """Add new book wrapper"""
    add_book(title_entry.get(),
             author_entry.get(),
             release_entry.get(),
             isbn_entry.get(),
             publisher_entry.get()
             )

    clear_entry()
    tree.delete(*tree.get_children())
    query_book()


def update_book_cmd():
    """Update existing book wrapper"""
    if not tree.selection():
        return

    real_id = tree.selection()[0]
    # print(real_id)
    # tree view delete
    select = tree.focus()
    vals = (
    real_id, title_entry.get(), author_entry.get(), publisher_entry.get(), isbn_entry.get(), release_entry.get())
    tree.item(select, text="", values=vals)

    update_book(*vals)

    clear_entry()


def remove_book_cmd():
    """Remove existing book wrapper"""
    if not tree.selection():
        return

    real_id = tree.selection()[0]

    delete_book(real_id)

    clear_entry()
    tree.delete(tree.selection()[0])


def not_implemented_popup():
    showinfo("Error", "Not implemented yet")


def create_menu(root):
    # TODO: to implement (new windows for each table etc.)
    menu = tk.Menu(root)
    root.config(menu=menu)
    # frame = MainFrame(self, self)

    cascade = tk.Menu(menu)

    cascade.add_command(
        label="Books", underline=0, command=not_implemented_popup
    )
    cascade.add_command(
        label="Friends", underline=1, command=not_implemented_popup
    )
    cascade.add_command(
        label="Borrowed Books", underline=2, command=not_implemented_popup
    )
    menu.add_cascade(label="Tables", menu=cascade, underline=0)
    menu.add_command(label="Exit", underline=1, command=root.destroy)


# TODO: !! Split frames into classes to reduce mess inside main !!
# TODO: separate views from controller logic
# TODO: create views for Borrow and Friends to make the app useful
# TODO: better error logging (show info to user instead of raising errors)
# TODO: popups for critical stuff (like removing rows)

root = tk.Tk()
root.title('Books DB project')
root.minsize(600, 400)
create_menu(root)

# Style the table
# TODO: Make it dynamic, prettier and more readable
style = ttk.Style()
style.theme_use('default')
style.configure('Treeview',
                background="grey")
style.map('Treeview', background=[('selected', "blue")])

table_frame = tk.Frame(root).pack()

# Add tree - table
# TODO: scroll for tree
tree = ttk.Treeview(table_frame, selectmode="extended")
tree.bind("<ButtonRelease-1>", select_row)  # to update currently selected row into entries
tree.pack()

# table columns
tree['columns'] = ("Id", "Title", "Author", "Publisher", "ISBN", "Release Year")
tree.column("#0", width=0, stretch="NO")
tree.column("Id", anchor="center", width=50)
tree.column("Title", anchor="center", width=180)
tree.column("Author", anchor="center", width=180)
tree.column("Publisher", anchor="center", width=180)
tree.column("ISBN", anchor="center", width=120)
tree.column("Release Year", anchor="center", width=120)

# table headings
tree.heading("#0", text="")
tree.heading("Id", text="Id", anchor="center")
tree.heading("Title", text="Title", anchor="center")
tree.heading("Author", text="Author", anchor="center")
tree.heading("Publisher", text="Publisher", anchor="center")
tree.heading("ISBN", text="ISBN", anchor="center")
tree.heading("Release Year", text="Release Year", anchor="center")

# Entries
enter_frame = tk.LabelFrame(root, text="Book")
enter_frame.pack(fill="both", expand="yes")

# TODO: Maybe create using a helper function?
title_label = tk.Label(enter_frame, text="Title")
title_label.grid(row=0, column=1, padx=5, pady=5)
title_entry = tk.Entry(enter_frame)
title_entry.grid(row=0, column=2, padx=10, pady=10)

author_label = tk.Label(enter_frame, text="Author")
author_label.grid(row=1, column=1, padx=5, pady=5)
author_entry = tk.Entry(enter_frame)
author_entry.grid(row=1, column=2, padx=10, pady=10)

publisher_label = tk.Label(enter_frame, text="Publisher")
publisher_label.grid(row=2, column=1, padx=5, pady=5)
publisher_entry = tk.Entry(enter_frame)
publisher_entry.grid(row=2, column=2, padx=10, pady=10)

isbn_label = tk.Label(enter_frame, text="ISBN")
isbn_label.grid(row=3, column=1, padx=5, pady=5)
isbn_entry = tk.Entry(enter_frame)
isbn_entry.grid(row=3, column=2, padx=10, pady=10)

release_label = tk.Label(enter_frame, text="Release Year")
release_label.grid(row=4, column=1, padx=5, pady=5)
release_entry = tk.Entry(enter_frame)
release_entry.grid(row=4, column=2, padx=10, pady=10)

# to center
enter_frame.grid_columnconfigure(0, weight=1)
enter_frame.grid_columnconfigure(3, weight=1)

# Buttons
# TODO: Style the buttons
# TODO: more options: delete all, move up/down etc.
buttons_frame = tk.LabelFrame(root, text="Commands")
buttons_frame.pack(fill="x", expand="yes")

add_button = tk.Button(buttons_frame, text="Add Book", command=add_book_cmd)
add_button.grid(row=0, column=1, padx=5, pady=5)

update_button = tk.Button(buttons_frame, text="Update selected", command=update_book_cmd)
update_button.grid(row=0, column=2, padx=5, pady=5)

delete_button = tk.Button(buttons_frame, text="Remove selected", command=remove_book_cmd)
delete_button.grid(row=0, column=3, padx=5, pady=5)

clear_button = tk.Button(buttons_frame, text="Clear entry", command=clear_entry)
clear_button.grid(row=0, column=4, padx=5, pady=5)

# center
buttons_frame.grid_columnconfigure(0, weight=1)
buttons_frame.grid_columnconfigure(5, weight=1)

# fetch all books
query_book()

# run main loop of tkinter frame
root.mainloop()
