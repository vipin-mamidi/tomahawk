#ifndef ZEROCONF_H
#define ZEROCONF_H

#include "sip/SipPlugin.h"
#include "tomahawkoauthtwitter.h"

#include "../sipdllmacro.h"

class SIPDLLEXPORT TwitterPlugin : public SipPlugin
{
    Q_OBJECT
    Q_INTERFACES( SipPlugin )

public:
    TwitterPlugin()
        : m_twitterAuth( 0 )
    {}

    virtual ~TwitterPlugin() {}

public slots:
    virtual bool connect( bool startup );

    void disconnect()
    {
    }

    void sendMsg( const QString& to, const QString& msg )
    {
    }

    void broadcastMsg( const QString &msg )
    {
    }

    void addContact( const QString &jid, const QString& msg = QString() )
    {
    }

private slots:
    void lanHostFound( const QString& host, int port, const QString& name, const QString& nodeid );

private:
    TomahawkOAuthTwitter *m_twitterAuth;
};

#endif
