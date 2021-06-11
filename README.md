![42-lyon](https://user-images.githubusercontent.com/45235527/106354618-6ec65a00-62f3-11eb-8688-ba9e0f4e77de.jpg)

# Webserv

<img alt="Note" src="https://user-images.githubusercontent.com/45235527/96753610-698e7080-13d0-11eb-9461-d3351c9208d7.png" width="250" height="200" />

<strong>Description</strong>

This project is here to make you write your own HTTP server. You will
follow the real HTTP RFC and you will be able to test it with a real browser. HTTP is
one of the most used protocol on internet. Knowing its arcane will be useful, even if you
won’t be working on a website.

> *Contributors:<br>*
> -	   *<a href="https://github.com/nemu69">Nemuel Page Léonie</a> (<a href="https://profile.intra.42.fr/users/nepage-l">nepage-l</a>).<br>*
> -    *<a href="https://github.com/AcensJJ">Jean-Jacques Acens</a> (<a href="https://profile.intra.42.fr/users/jacens">jacens</a>).*

# Mandatory part

![Sujet](https://user-images.githubusercontent.com/45235527/107391358-e74dc780-6af8-11eb-8f84-b642d9a2495a.png)

You must write a HTTP server in C++ 98
- The C++ standard must be C++ 98. Your project must compile with it.
- It must be conditionnal compliant with the rfc 7230 to 7235 (http 1.1) but you need to implement only the following headers
    - Accept-Charsets
    - Accept-Language
    - Allow
    - Authorization
    - Content-Language
    - Content-Length
    - Content-Location
    - Content-Type
    - Date
    - Host
    - Last-Modified
    - Location
    - Referer
    - Retry-After
    - Server
    - Transfer-Encoding
    - User-Agent
    - WWW-Authenticate
- You can implement all the headers if you want to
- We will consider that nginx is HTTP 1.1 compliant and may be use to compare headers and answer behaviors
- It must be non blocking and use only 1 select for all the IO between the client and the server (listens includes).
- Select should check read and write at the same time.
- Your server should never block and client should be bounce properly if necessary
- You should never do a read operation or a write operation without going through select
- Checking the value of errno is strictly forbidden after a read or a write operation
- A request to your server should never hang forever
- You server should have default error pages if none are provided
- Your program should not leak and should never crash, (even when out of memory if all the initialisation is done)
- You can’t use fork for something else than CGI (like php or perl or ruby etc...)
- You can include and use everything in "iostream" "string" "vector" "list" "queue" "stack" "map" "algorithm"
- Your program should have a config file in argument or use a default path
- In this config file we should be able to:
    - choose the port and host of each "server"
    - setup the server_names or not
    - The first server for a host:port will be the default for this host:port (meaning it will answer to all request that doesn’t belong to an other server)
    - setup default error pages
    - limit client body size
    - setup routes with one or multiple of the following rules/configuration (routes wont be using regexp):
        - define a list of accepted HTTP Methods for the route
        - define a directory or a file from where the file should be search (for example if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is /tmp/www/pouic/toto/pouet)
        - turn on or off directory listing
        - default file to answer if the request is a directory
        - execute CGI based on certain file extension (for example .php)
            -You wonder what a CGI is go? https://en.wikipedia.org/wiki/Common_Gateway_Interface
            - Because you wont call the cgi directly use the full path as PATH_INFO
            - Just remember that for chunked request, your server need to unchunked it and the CGI will expect EOF as end of the body.
            - Same things for the output of the CGI. if no content_length is returned from the CGI, EOF will mean the end of the returned data.
            - Your program should set the following Meta-Variables
                - AUTH_TYPE
                - CONTENT_LENGTH
                - CONTENT_TYPE
                - GATEWAY_INTERFACE
                - PATH_INFO
                - PATH_TRANSLATED
                - QUERY_STRING
                - REMOTE_ADDR
                - REMOTE_IDENT
                - REMOTE_USER
                - REQUEST_METHOD
                - REQUEST_URI
                - SCRIPT_NAME
                - SERVER_NAME
                - SERVER_PORT
                - SERVER_PROTOCOL
                - SERVER_SOFTWARE
            - Your program should call the cgi with the file requested as first argument
            - the cgi should be run in the correct directory for relativ path file access
            - your server should work with php-cgi
        - make the route able to accept uploaded files and configure where it should be saved

You should provide some configuration files for evaluation
