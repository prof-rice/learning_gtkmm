#!/usr/bin/env python3
print("Hello World")
import easygui
fav = easygui.buttonbox('Click on your favorite ice cream flavor', 'Favorite Flavor', ('Chocolate', 'Vanilla', 'Strawberry'))
print(fav)

