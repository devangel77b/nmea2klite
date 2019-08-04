#ifndef NMEA2KLITE_H
#define NMEA2KLITE_H

#include "platform/SharedPtr.h"
#include "drivers/CAN.h"

#define NMEA2K_VERSION "14.3.0"
#define NMEA2K_BROADCAST 255

class PduHeader{
 public:
  PduHeader();
  PduHeader(unsigned char p, unsigned int pgn,
	    unsigned char sa,unsigned char da=NMEA2K_BROADCAST);  
  inline unsigned int id(){return _trans.id;}
  inline void set_id(unsigned int x){_trans.id = x;}
 private:
  union{
    unsigned int id;
    struct{
      unsigned char sa,
	ps,
	pf,
	dp : 1,
	r : 1,
	p : 3,
	unused : 3;
	} iso;
  } _trans; 
}; // class PduHeader

class PgnData{
 public:
  char *name;
  unsigned int pgn;  
  PgnData();
  unsigned char *data();
  unsigned char len();
}; // class PgnData (generic PGN data)

class Frame:public CANMessage{
 public:
  Frame();
  Frame(unsigned int id, const unsigned char *data, unsigned char len);
  Frame(unsigned int id, const char *data, unsigned char len); 
};

class Nmea2k:public CAN{
 public:
  Nmea2k(PinName rd, PinName td);
  int read(Frame &f, int handle = 0);
  int write(Frame f); 
};
 

#endif
