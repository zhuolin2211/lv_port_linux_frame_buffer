#ifndef HTTP_H
#define HTTP_H

#include <curl/curl.h>
#include <string>
#include <vector>
using namespace std;
typedef struct
{
    string key;
    string value;
}par_group;
class http
{
public:
    http();
    ~http();
    static void Init_Http(void);
    string Http_Get(string url);
    int Http_Get(string url,FILE* file);
    string Http_Post(string &url,string par);

    static size_t receive_string_claaback(void *ptr, size_t size, size_t nmemb, void *stream);
    static size_t receive_file_claaback(void *ptr, size_t size, size_t nmemb, void *stream);

    void Http_Get_addParameter(string *url,vector<par_group> parameter);
    void Http_Post_addParameter(string &par,vector<par_group> parameter);
private:
    CURL *curl_handle;
};


#endif // HTTP_H
