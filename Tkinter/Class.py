class Vehicle:
    lecenseCode = ""
    serialCode = ""
    def turnOnAirConditioner(self):
        print("Turn On : Air")

class Pickup(Vehicle):
    color = ""

class Car(Vehicle):
    pass;

class Van(Vehicle):
    pass;


pickup1 = Pickup()
pickup1.turnOnAirConditioner()
pickup1.color = "red"
