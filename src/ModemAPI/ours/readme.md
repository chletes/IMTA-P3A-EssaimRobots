# Modem API 

This API was forked from  the original API example from Marvelmind. 

The original API can be found downloading the software pack (SW) from Marvelmind's web site and then going to this path: `marvelmind_SW/marvelmind_SW_2021_09_29/Examples/c/2017_01_28_modem_C_example`.

## How the API works

* `main/main.c`: frontend - asks the user (desired action, beacon adress, command to send) - and leaves the rest to `modem/modem.c` (calls `startGetBeaconState()`). The normal execution is returned again to the fallback function `processBeaconStateReply()` after modem sending and receiving the data. 

![](../../../img/main.png)

* `modem/modem.c`: backend - process the request and the reply
    1. `startGetBeaconState()` plan the request (`planRequest()`). 
    2. `MarvelMindThread_()` process the request and calls `getBeaconState()`.
    3. `getBeaconState()` prepares (`prepareReadRequest()`)and sends (`sendRequestPacket()`) the request, and receives (`receiveAnswerPacket()` and `checkReceivedPacket()`) the reply. 
    4. `MarvelMindThread_()` calls `requestFinish()` that returns the execution to the fallback function (`processBeaconStateReply()`). 