#include "tomahawk/collection.h"

#include <QMetaObject>
#include <QGenericArgument>

#include "tomahawk/playlist.h"
#include "dynamic/DynamicPlaylist.h"

using namespace Tomahawk;


Collection::Collection( const source_ptr& source, const QString& name, QObject* parent )
    : QObject( parent )
    , m_name( name )
    , m_lastmodified( 0 )
    , m_source( source )
{
//    qDebug() << Q_FUNC_INFO;
}


Collection::~Collection()
{
    qDebug() << Q_FUNC_INFO;
}


QString
Collection::name() const
{
    return m_name;
}

const 
source_ptr& Collection::source() const
{
    return m_source;
}

void
Collection::addPlaylist( const Tomahawk::playlist_ptr& p )
{
    qDebug() << Q_FUNC_INFO;
    QList<playlist_ptr> toadd;
    toadd << p;
    m_playlists.append( toadd );

    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.length();
    emit playlistsAdded( toadd );
}

void
Collection::addDynamicPlaylist( const Tomahawk::dynplaylist_ptr& p )
{
    qDebug() << Q_FUNC_INFO;
    QList<dynplaylist_ptr> toadd;
    toadd << p;
    m_dynplaylists.append( toadd );
    
    qDebug() << Q_FUNC_INFO << "Collection name" << name()
    << "from source id" << source()->id()
    << "numplaylists:" << m_playlists.length();
    emit dynamicPlaylistsAdded( toadd );
}


void
Collection::deletePlaylist( const Tomahawk::playlist_ptr& p )
{
    qDebug() << Q_FUNC_INFO;
    QList<playlist_ptr> todelete;
    todelete << p;
    m_playlists.removeAll( p );

    qDebug() << Q_FUNC_INFO << "Collection name" << name()
                            << "from source id" << source()->id()
                            << "numplaylists:" << m_playlists.length();
    emit playlistsDeleted( todelete );
}

void
Collection::deleteDynamicPlaylist( const Tomahawk::dynplaylist_ptr& p )
{
    qDebug() << Q_FUNC_INFO;
    QList<dynplaylist_ptr> todelete;
    todelete << p;
    m_dynplaylists.removeAll( p );
    
    qDebug() << Q_FUNC_INFO << "Collection name" << name()
    << "from source id" << source()->id()
    << "numplaylists:" << m_playlists.length();
    emit dynamicPlaylistsDeleted( todelete );
}


playlist_ptr
Collection::playlist( const QString& guid )
{
    foreach( const playlist_ptr& pp, m_playlists )
    {
        if( pp->guid() == guid )
            return pp;
    }
    
    // TODO do we really want to do this?
    foreach( const dynplaylist_ptr& pp, m_dynplaylists )
    {
        if( pp->guid() == guid )
            return pp.staticCast<Playlist>();
    }
    
    return playlist_ptr();
}


dynplaylist_ptr
Collection::dynamicPlaylist( const QString& guid )
{
    foreach( const dynplaylist_ptr& pp, m_dynplaylists )
    {
        if( pp->guid() == guid )
            return pp;
    }
    
    return dynplaylist_ptr();
}


void
Collection::setPlaylists( const QList<Tomahawk::playlist_ptr>& plists )
{
    qDebug() << Q_FUNC_INFO << plists.count();

    m_playlists.append( plists );
    emit playlistsAdded( plists );
}

void
Collection::setDynamicPlaylists( const QList< Tomahawk::dynplaylist_ptr >& plists )
{
    qDebug() << Q_FUNC_INFO << plists.count();
    
    m_dynplaylists.append( plists );
    emit dynamicPlaylistsAdded( plists );
}

void
Collection::setTracks( const QList<Tomahawk::query_ptr>& tracks, Tomahawk::collection_ptr collection )
{
    qDebug() << Q_FUNC_INFO << tracks.count() << collection->name();

    m_tracks << tracks;
    emit tracksAdded( tracks, collection );
}
