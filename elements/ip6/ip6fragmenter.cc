/*
 * ip6fragmenter.{cc,hh} -- element fragments IP6 packets
 * Robert Morris
 *
 * Copyright (c) 1999 Massachusetts Institute of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Further elaboration of this license, including a DISCLAIMER OF ANY
 * WARRANTY, EXPRESS OR IMPLIED, is provided in the LICENSE file, which is
 * also accessible at http://www.pdos.lcs.mit.edu/click/license.html
 */

#include <click/config.h>
#include "ip6fragmenter.hh"
#include <click/click_ip6.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/glue.hh>

IP6Fragmenter::IP6Fragmenter()
  : _drops(0)
{
  MOD_INC_USE_COUNT;
  _fragments = 0;
  _mtu = 0;
  add_input();
  add_output();
}

IP6Fragmenter::~IP6Fragmenter()
{
  MOD_DEC_USE_COUNT;
}

void
IP6Fragmenter::notify_noutputs(int n)
{
  // allow 2 outputs -- then packet is pushed onto 2d output instead of
  // dropped
  set_noutputs(n < 2 ? 1 : 2);
}

IP6Fragmenter *
IP6Fragmenter::clone() const
{
  return new IP6Fragmenter;
}


int
IP6Fragmenter::configure(const Vector<String> &conf, ErrorHandler *errh)
{
  if (cp_va_parse(conf, this, errh,
                  cpUnsigned, "MTU", &_mtu,
		  0) < 0)
    return -1;
  return 0;
}

 /*
int
IP6Fragmenter::optcopy(click_ip6 *ip1, click_ip6 *ip2)
{
  int opts = (ip1->ip_hl << 2) - sizeof(click_ip6);
  u_char *base1 = (u_char *) (ip1 + 1);
  int i1, optlen;
  int i2 = 0;
  u_char *base2 = (u_char *) (ip2 + 1);

  for(i1 = 0; i1 < opts; i1 += optlen){
    int opt = base1[i1];
    if(opt == IPOPT_EOL)
      break;
    if(opt == IPOPT_NOP){
      optlen = 1;
    } else {
      optlen = base1[i1+1];
    }

    if(opt & 0x80){
    // copy it
      if(ip2){
        memcpy(base2 + i2, base1 + i1, optlen);
      }
      i2 += optlen;
    }
  }

  for( ; i2 & 3; i2++)
    if(ip2)
      base2[i2] = IPOPT_EOL;

  return(i2);
}

*/
void
IP6Fragmenter::fragment(Packet *)
{ }

/*
inline Packet *
IP6Fragmenter::smaction(Packet *p)
{
  if (p->length() <= _mtu)
    {
      //click_chatter("IP6Fragmenter: length is OK, <= %x \n", _mtu);
      return(p);
    }
  else 
    {
      click_chatter("IP6Fragmenter: length is not OK, > %x \n", _mtu); 
      if (noutputs() == 2)
	output(1).push(p);
      else
	p->kill();
      return 0; 
    }
}
*/

static String
IP6Fragmenter_read_drops(Element *xf, void *)
{
  IP6Fragmenter *f = (IP6Fragmenter *)xf;
  return String(f->drops()) + "\n";
}

static String
IP6Fragmenter_read_fragments(Element *xf, void *)
{
  IP6Fragmenter *f = (IP6Fragmenter *)xf;
  return String(f->fragments()) + "\n";
}

void
IP6Fragmenter::add_handlers()
{
  add_read_handler("drops", IP6Fragmenter_read_drops, 0);
  add_read_handler("fragments", IP6Fragmenter_read_fragments, 0);
}


void
IP6Fragmenter::push(int, Packet *p)
{
  // click_chatter("IP6Fragmenter::push, packet length is %x \n", p->length());
  if (p->length() <= _mtu)
    {
      // click_chatter("**********************1");
    output(0).push(p);
    }
  else
    {
      // click_chatter("**********************2");
      // output(0).push(p);
    }
}

//  Packet *
//  IP6Fragmenter::pull(int)
//  {
//    Packet *p = input(0).pull();
//    if(p)
//      {
//        //click_chatter("IP6Fragmenter::pull before smaction");
//        p = smaction(p);
//      }
//    else
//      {
//        //click_chatter(" IP6Fragmenter::pull, not have p"); 
//      }
//    return(p); 
//  }


EXPORT_ELEMENT(IP6Fragmenter)
