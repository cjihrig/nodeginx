#ifndef NODEGINX_H
#define NODEGINX_H

extern "C" {
  #include <ngx_config.h>
  #include <ngx_core.h>
  #include <ngx_http.h>
}

#include <stdio.h> // TODO: remove this

#include "node.h"
#include "uv.h"

char* ngx_http_nodeginx(ngx_conf_t* cf, ngx_command_t* cmd, void* conf);
ngx_int_t ngx_http_nodeginx_handler(ngx_http_request_t* r);


ngx_http_module_t ngx_http_nodeginx_module_ctx = {
  NULL, // preconfiguration
  NULL, // postconfiguration
  NULL, // create main configuration
  NULL, // init main configuration
  NULL, // create server configuration
  NULL, // merge server configuration
  NULL, // create location configuration
  NULL  // merge location configuration
};

#endif  // NODEGINX_H
