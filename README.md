# MemoryScanner
Simple memory scanner project for Linux distributions with GUI based on Qt framework inspired by GameConqueror

# Screenshot: 
![alt text](https://github.com/b00m-b00m/MemoryScanner/blob/master/Screenshot%20from%202018-07-07%2018-38-40.png "")

# Build:
### Build from source:
* clone or download source code
* go to directory that contains source code
* open terminal and ececute following commands
  * first of all make sure that you have all required dependencies:
   ``` 
      $ sudo apt-get install qt5-default
    
      $ sudo apt-get install qt5-qmake
   ```
   
   * build project in this way:
   ```
      $ qmake
   
      $ make
   ```
   * or this:
   ```
      $ mkdir build
   
      $ cd build
   
      $ qmake ../ProcessMemoryScanner.pro
   
      $ make
   ```
* after all just execute ```$ sudo ./ProcessMemoryScanner ``` in terminal

# Features:
* several supported types: *int, float, double, short, long*
* several search types: *equals to, less then, greater than, increased, decreased, changed, unchanged*

# To do:
* fix incomplete displayed process name in TaskWidget
* fix failure in 'big' processes  
* add opportunitie to search in certain memory regions (only in stack and heap for example) 
* bind progress bar with search event (yeap, it's just added to gui yet)
* add embedded hex editor to see all available memory regions
* make it crossplatform. Simply extend abstract classes and reimplement platform specific methods
