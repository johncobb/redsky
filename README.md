![Aerospike](https://github.com/johncobb/redsky/blob/master/img/aerospike.png)

##  Redsky IoT/GPS/Telematics

## Table of contents
- [Overview](#overview)
- [Prerequisites](#prereq)
- [Examples](#examples)
- [References](#references)

<div id='overview'/>
Redsky is currently being developed to replace engenx machine to machine platform. This project started as an Automatic Vehicle Location (AVL) solution in 2008. The new stack will leverage Amazon Web Services (AWS) high performance infrastructure allowing for reduced cost and inscreased scalability.
<div id='prereq'/>

## Prerequisites:

 - Install Python
 - Install USB/Serial bus
 - Enfora MTU-4100
 - CalAmp (LMU-1230) (LMU-3035)
 - Amazon EC2 Instance with UDP port: 1721
 - Hologram SIM


 <div id='examples'/>

## Examples

### Start by running the server on the EC2 instance
```console
python python/server.py
```


### Test the server code by running the client

The client command will send the message Ground Control to Major Tom. The Amazon EC2 log should show the message from the client.
```console
python client.py
```
