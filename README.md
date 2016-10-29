![gecostacklogo](https://media.licdn.com/media/AAEAAQAAAAAAAALQAAAAJDI3NjViNjAxLTA5NDItNGJkMi05ZThlLThmM2VlODkyMmQwZA.png)

# Aimed for Online Games

**geconet** is a complete transport protocol stack on OSI layer 4(like TCP or Reliable-UDP).  
It is implemented in the user space with raw sockets and/or udp sockets(setup by users).  
It is specifically designed for datagram-like meassage trasport in online games.   
However, it is generic and may supersede TCP and Reliable-UDP in other applications as well.

## Why use geconet instead of TCP or Reliable UDP？
- **no head-of-line blocking**    
TCP imposes a strictly reliable and ording data transmittions. However, if a user data message  
is lost during transit, all subsequent user data messages are delayed until the lost messag   
has been retransmitted (so-called head-of-line blocking). Some applications do not require a   
strict ordering of reliable messages. E.g. the complicated MMORPG or MOBA games usually exchange   
unrelated game messages out-of-order.  

- **no stream-oriented data transfer**     
TCP is stream-oriented. This means that TCP treats data chunks transmitted by an application as   
an ordered stream of bytes(=octets in network speak). While this concept supports a wide range of   
applications (mesage-oriented like email, character-oriented like TELNET, stream-oriented vides),   
it is unsuilted in most applications because these exchange application level messages with message  
boundaries. **geconet** preserves apllication level message boundaries, thus liberationg applications   
from implementing a framing protocol on the top of the transport protocol for delineating messages.   
**geconet** simply maps application messages to chunks on the transmit path and back to application   
messages on the receive path.

- **multihoming**  

- **againest denial of service,man-in-the-middle and blind attacks** 

- **Instance methods and static methods**   
