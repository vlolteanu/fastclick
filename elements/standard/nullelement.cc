/*
 * nullelement.{cc,hh} -- do-nothing element
 * Eddie Kohler
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
#include "nullelement.hh"

NullElement::NullElement()
  : Element(1, 1)
{
  MOD_INC_USE_COUNT;
}

NullElement::~NullElement()
{
  MOD_DEC_USE_COUNT;
}

Packet *
NullElement::simple_action(Packet *p)
{
  return p;
}

PushNullElement::PushNullElement()
  : Element(1, 1)
{
  MOD_INC_USE_COUNT;
}

PushNullElement::~PushNullElement()
{
  MOD_DEC_USE_COUNT;
}

void
PushNullElement::push(int, Packet *p)
{
  output(0).push(p);
}

PullNullElement::PullNullElement()
  : Element(1, 1)
{
  MOD_INC_USE_COUNT;
}

PullNullElement::~PullNullElement()
{
  MOD_DEC_USE_COUNT;
}

Packet *
PullNullElement::pull(int)
{
  return input(0).pull();
}

EXPORT_ELEMENT(NullElement)
EXPORT_ELEMENT(PushNullElement)
EXPORT_ELEMENT(PullNullElement)
ELEMENT_MT_SAFE(NullElement)
ELEMENT_MT_SAFE(PushNullElement)
ELEMENT_MT_SAFE(PullNullElement)
