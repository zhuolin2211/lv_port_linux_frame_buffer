#include "http.h"
#include <string>
http::http()
{
curl_handle=curl_easy_init();
}
http::~http()
{
    curl_easy_cleanup(curl_handle);
}
void http::Init_Http(void)
{
    curl_global_init(CURL_GLOBAL_ALL);
}
size_t http::receive_string_claaback(void *ptr, size_t size, size_t nmemb, void *stream)
{
    string *data=(string*)stream;
    data->append((char*)ptr,size*nmemb);
    return size*nmemb;
}
size_t http::receive_file_claaback(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}
string http::Http_Get(string url)
{
    string receive;
     /* set URL to get */
      curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, http::receive_string_claaback);
      curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&receive);
      int ret=curl_easy_perform(curl_handle);
      if(ret!=0)
      {
          receive.clear();
      }
      return receive;
}
int http::Http_Get(string url,FILE* file)
{
     /* set URL to get */
      curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, http::receive_file_claaback);
      curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)file);
      int ret=curl_easy_perform(curl_handle);
      return ret;
}
void http::Http_Get_addParameter(string *url,vector<par_group> parameter)
{
    url->append("?");
    for(size_t i=0;i<parameter.size();i++)
    {
              url->append(parameter.at(i).key+"="+parameter.at(i).value);
              if(i!=(parameter.size()-1))
              {
                  url->append("&");
              }        
    }

}

void http::Http_Post_addParameter(string &par,vector<par_group> parameter)
{
    if(parameter.size()>0)
    {
        for(vector<par_group>::iterator i= parameter.begin();i!=parameter.end();i++)
        {
        par.append((*i).key+"="+(*i).value);
        if(i-parameter.begin()!=parameter.size()-1)
        {
           par.append("&"); 
        }
        }
    }
}
string http::Http_Post(string &url,string par)
{   string receive;
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, par.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, http::receive_string_claaback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&receive);

    struct curl_slist *header=NULL;
    header=curl_slist_append(header,"Content-Type:application/json;charset=UTF-8");
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, header);
    int ret=curl_easy_perform(curl_handle);
    if(ret ==CURLE_OK )
    {
        return receive;
    }
    else{
        return "null";
    }
}
