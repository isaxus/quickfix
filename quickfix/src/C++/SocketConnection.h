/* -*- C++ -*- */

/****************************************************************************
** Copyright (c) 2001-2004 quickfixengine.org  All rights reserved.
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifndef FIX_SOCKETCONNECTION_H
#define FIX_SOCKETCONNECTION_H

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 4290 )
#endif

#include "Parser.h"
#include "Responder.h"

namespace FIX
{
class SocketAcceptor;
class SocketServer;
class SocketConnector;
class SocketInitiator;
class SocketMonitor;
class Session;
  class SessionID;

class SocketConnection : Responder
{
public:
  SocketConnection( int s, SocketMonitor* pMonitor );
  SocketConnection( SocketInitiator&, const SessionID&, int, SocketMonitor* );
  virtual ~SocketConnection() {}

  Session* getSession() const { return m_pSession; }
  bool read( SocketConnector& s );
  bool read( SocketAcceptor&, SocketServer& );
  void onTimeout();

private:
  bool readMessage( std::string& msg ) throw( RecvFailed );
  bool send( const std::string& );
  void disconnect();

  int m_socket;
  Parser m_parser;
  Session* m_pSession;
  SocketMonitor* m_pMonitor;
};
}

#endif //FIX_SOCKETCONNECTION_H