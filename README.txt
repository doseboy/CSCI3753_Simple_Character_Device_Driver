Name: William Anderson
Phone: 720-237-6312
PA2

Hello TA reading this!

The files created for this assignment:
simple_char_driver.c and simple_char_driver_test.c



simple_char_driver.c:

This file is the device driver code that implements read, write, and seek. This file was created by using C libraries and by writing our own functions using our knowledge on how LKM's work! We used the operations and renamed them to our own read, write and seek. The offset was accounted for inside the kernel using this implementation.



simple_char_driver_test.c:

This file is the test file for the previous one. I created a UI so that the user can write to a file and read from a file in the device driver (also seek). PLEASE PRESS ENTER AFTER EXECUTING A.OUT TO ENTER INTO UI. In order to enter the UI you need to press enter. Once inside the UI, it will prompt the user to open (THIS MUST ALWAYS BE DONE IN ORDER TO USE DEVICE) and it closes automatically. REMEMBER THAT THE FIRST THING YOU SHOULD DO ONCE IN THE UI IS PRESS "o". Then you can read, write, and use seek appropriately. When exiting, it takes some time to return to command line, just wait or press enter a few times... Anyways, those are the instructions for this file, sorry about the crappy UI. 
