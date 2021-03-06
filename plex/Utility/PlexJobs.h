//
//  PlexJobs.h
//  Plex Home Theater
//
//  Created by Tobias Hieta on 2013-08-14.
//
//

#ifndef __Plex_Home_Theater__PlexJobs__
#define __Plex_Home_Theater__PlexJobs__

#include "utils/Job.h"
#include "URL.h"
#include "filesystem/CurlFile.h"
#include "FileItem.h"
#include "guilib/GUIMessage.h"

////////////////////////////////////////////////////////////////////////////////////////
class CPlexHTTPFetchJob : public CJob
{
  public:
    CPlexHTTPFetchJob(const CURL &url) : CJob(), m_url(url) {};
  
    bool DoWork();
    virtual bool operator==(const CJob* job) const;
  
    XFILE::CCurlFile m_http;
    CStdString m_data;
    CURL m_url;
};

////////////////////////////////////////////////////////////////////////////////////////
class CPlexDirectoryFetchJob : public CJob
{
public:
  CPlexDirectoryFetchJob(const CURL &url) : CJob(), m_url(url) {}
  
  virtual bool operator==(const CJob* job) const
  {
    const CPlexDirectoryFetchJob *fjob = static_cast<const CPlexDirectoryFetchJob*>(job);
    if (fjob && fjob->m_url.Get() == m_url.Get())
      return true;
    return false;
  }
  
  virtual const char* GetType() const { return "plexdirectoryfetch"; }
  
  virtual bool DoWork();
  
  CFileItemList m_items;
  CURL m_url;
};

////////////////////////////////////////////////////////////////////////////////////////
class CPlexSectionFetchJob : public CPlexDirectoryFetchJob
{
public:
  CPlexSectionFetchJob(const CURL& url, int contentType) : CPlexDirectoryFetchJob(url), m_contentType(contentType) {}
  int m_contentType;
};

////////////////////////////////////////////////////////////////////////////////////////
class CPlexMediaServerClientJob : public CJob
{
public:
  CPlexMediaServerClientJob(CURL command, const std::string verb = "GET", const CGUIMessage &msg = CGUIMessage(0, 0, 0, 0), int error = 0) :
  m_url(command), m_verb(verb), m_msg(msg), m_errorMsg(error) {}
  
  virtual bool DoWork();
  
  CURL m_url;
  std::string m_verb;
  CStdString m_data;
  CGUIMessage m_msg;
  CStdString m_postData;
  int m_errorMsg;
  
  virtual bool operator==(const CJob* job) const
  {
    CPlexMediaServerClientJob *oJob = (CPlexMediaServerClientJob*)job;
    if (oJob->m_url.Get() == m_url.Get())
      return true;
    return false;
  }
};

////////////////////////////////////////////////////////////////////////////////////////
class CPlexVideoThumbLoaderJob : public CJob
{
public:
  CPlexVideoThumbLoaderJob(CFileItemPtr item) : m_item(item) {}

  virtual bool DoWork();

  virtual bool operator==(const CJob* job) const
  {
    CPlexVideoThumbLoaderJob *ljob = (CPlexVideoThumbLoaderJob*)job;
    return m_item == ljob->m_item;
  }

  CFileItemPtr m_item;
};

#endif /* defined(__Plex_Home_Theater__PlexJobs__) */
