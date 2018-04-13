# LinDeb - A Debugger for your Debugger

### What is this? 
LinDeb is currently a work in progress for a hybrid between a debugger and an editor for executing and rapidly deploying mathematical functions. I was writing a linear algebra library when I got fed up with how much of my code I'd have to rewrite in order to test simple functions, and asked myself: *is there a *better* way to do this?* Of course there is. 

### But What IS it?
LinDeb is a powerful tool that hopes to allow the user to enter mathematical function, either through a CLI, or a GUI (sometime later when I have a better understanding of Qt.io). Once this function has been created, the user can then place it within a mathematical library, where it can be tested quickly within the interface. 
### The User Never Has to Build The Code Themselves
Similar to how scripting langauges allow you to interact with the shell, LinDeb will interactively accept mathematical functions created by the user, and allow the user to test them. If they are satisfied with their function, they can save it into a library file, where it can be called upon later from another piece of code that imports the library. 
If the user decides to save their function, it will be automatically translated into C++ code by the program, and saved. 
### The User will never have to worry about whether or not the code works.
Once they have tested the function, it will also be checked for domain errors such as division by zero, only being valid on a certain domain. The user can rest assured knowing that so long as they were able to test the function and never found errors, chances are, there won't be any. 
