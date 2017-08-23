# StockEvaluator
Uses the Quandl Finance API, Node.js, and Electron to create a native application that allows users to create and follow a porfolio of stocks.

# TODO
- Create C/C++ Native Node.js modules that:
                                                            - Create and edit an sqlite database
                                                            - 
                                                            - Make HTTP requests to the Quandl Finance API
                                                              for company data.
                                                            
- Design a simple Stock Portfolio user page that features: 
                                                            - Title (across top of page)
                                                            - Text box (below title, and left of page)
                                                            - Add / Delete button (below title, and left of page)
                                                            - An area for displaying data (below title, and right of page)
                                                            
                                            
                                            
# Getting Started
We use a few libraries, tools, and technologies that you will need to install such as CppRestSDK, SQLite, Node.js, and Electron.

Steps:

1. Install CppRestSDK: Go to https://github.com/Microsoft/cpprestsdk and scroll down to the "Getting Started section", and click        vcpkg. If you are using a non-windows operating system choose the method that cooresponds to your devices' OS.

2. Install the 64-bit versions of sqlite3 and cpprestsdk by using the command "vcpkg install sqlite3:x64-windows" (For windows users).
