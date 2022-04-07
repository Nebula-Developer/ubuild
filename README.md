# ubuild
Simple Makefile clone, that is fast and easy.

<br />

## Installing
To install ubuild, simply use the given makefile, and type:
  make build
  make install
  
This will rebuild ubuild, and then add it to the path.

<br />

## Usage
To use ubuild, simply make a file in your project named "ubuild" (No capitals.)
A simple ubuild file will look like this:

  ```
  sep Test
      echo "Hello, world!"
  ```

Then, when we run "ub Test", it will print hello world onto the terminal.
If no seperator is spesified, it will use the first.

<br />

## Important Info
If you like to use custom tab inlining, like the following:
  
  ```
  sep Test
    echo "Hello, world!"
  ```
    
Then, instead use "ub Test -c 2" (You may set the number to anything, and this will set the function start point for running an operation.)
 
Making a fork of ubuild? Be sure to message me any bugs you encounter.
Once ubuild is installed, you can build the project itself, using the provided ubuild file.
