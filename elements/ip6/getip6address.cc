/*
 * getip6address.{cc,hh} -- element sets IP6 destination annotation from
 * packet header
 * Peilei Fan 
 *
 * Copyright (c) 1999-2000 Massachusetts Institute of Technology
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
#include "getip6address.hh"
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/click_ip6.h>

GetIP6Address::GetIP6Address()
  : Element(1, 1)
{
  MOD_INC_USE_COUNT;
}

GetIP6Address::~GetIP6Address()
{
  MOD_DEC_USE_COUNT;
}


int
GetIP6Address::configure(const Vector<String> &conf, ErrorHandler *errh)
{
   return cp_va_parse(conf, this, errh,
      cpUnsigned, "byte offset of IP6 address", &_offset,
       0);
}

Packet *
GetIP6Address::simple_action(Packet *p)
{
  
  IP6Address dst=IP6Address((unsigned char *)(p->data()+ _offset));
  p->set_dst_ip6_anno(dst); 
  return p;
}

 
EXPORT_ELEMENT(GetIP6Address)
