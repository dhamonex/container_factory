# Container Factory #
A generic c++ 17 factory for filling containers with instances of objects.

**This is experimenting and work in progress at the moment**

## Motivation ##
Quite often it is necessary to fill a container with instances of objects of a common base class. The goal ist that this can be archieved by the following code
```c++
container_factory::factory<Base, SubclassA, SubclassB>( destinationContainer, <additional constructor arguments> );
```
