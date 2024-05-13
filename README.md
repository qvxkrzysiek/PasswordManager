# Password Manager

This is a simple password manager application implemented in C++.

## Overview

The Password Manager allows users to manage their passwords efficiently. It provides various functionalities such as searching for passwords, sorting them, adding new passwords, editing existing ones, and managing categories.

## Features

- Search for passwords based on keywords
- Sort passwords based on different criteria
- Add new passwords with customizable options
- Edit existing passwords
- Delete passwords or entire categories
- Organize passwords by categories

## Cryptography

The Password Manager employs a basic encryption and decryption mechanism to ensure the security of stored passwords. It uses a simple algorithm to encrypt passwords before storing them and decrypts them when accessed by the user. While this encryption provides a basic level of security, it is recommended to use additional security measures for sensitive data.

## File Handling

The Password Manager offers flexibility in managing password storage locations. It allows users to choose the location of the file from which passwords will be loaded, either from the program folder or from a specified path. Additionally, users can save passwords to the chosen file location after making modifications.
