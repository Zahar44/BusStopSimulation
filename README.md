# Bus stop simulation
# Configurations
For set up a simulation needed to config configuration file, address of this file is first argument from console.
In config file can be setted:
- speed of simulation;
- start hour;
- amount of bus stations;
- average human appearance period; 
- routes for buses;

To config some oprions simple needed to use key work and after "=" set a value, for exapmle:
```
speed = 500
```
Now speed of simualtion is 2 ticks in second.
For setting multiple values for variable should be used this syntax: 
```
Human chanse = [1,7,10,15]
```
Now avr appearance period for humans in morning is 1 tick, in noonday is 7 ticks and so on...
Configuration of routes:
```
Route13={[1,2,3], 3, 10}
```
There we have route #13 with way is 1->2->3->2->1, have 3 buses and avr delay between buses is 10 ticks

If confog file seted wrong will be used default settings!

# Simulation
Here some photos from simulation:

![image](https://user-images.githubusercontent.com/74359852/115146586-cc9b5000-a05f-11eb-8228-ba106375c06c.png)

![image](https://user-images.githubusercontent.com/74359852/115146602-da50d580-a05f-11eb-919f-d2cb219685ea.png)

In top section of the console setted information about curent status of simulation, belowe all bus stations with humans and buses. Inside of {} humans showed inforamtion about how log human wait for bus, it means that one number is one person. In {} of buses showed current amount of peoples in bus.  
