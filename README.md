onfig file we can run the component:

``` robotcontroller ```
##Controller for Robex, Robolab's classroom robot. 

Made by:

Ivan Barbecho Delgado

Juan Antonio García Ramiro

Victor Gonzalez Breña

This controller is created for Robex, the robot used in robotics subject at UEx.
Created with Kevelop and QT-Designer, using C++.


It've been made using component-oriented programming.
RCIS simulator it's needed in order to use it.


## Install guide

First, clone this repository to your chosen directory. Use

``` git clone ``` 

to do it.

Then cd the downloaded folder and use

``` cmake . ```

and 

``` make ```

to install it.

## Starting the component
To avoid changing the *config* file in the repository, we can copy it to the component's home directory, so changes will remain untouched by future git pulls:

    cd

``` <controller 's path> ```

    cp etc/config config
    
After editing the new config file we can run the component:

    bin/

```controller ```

    --Ice.Config=config
    
    
## Using the component

When the component is running, you'll see an interface:

In the top left corner you'll see a timer. Under it, there's information about linear and turning speed.

In the bottom left corner there's two buttons: the Start button makes the component work, and the Stop button stops it.

There's a white window too, where Robex route it's painted.
