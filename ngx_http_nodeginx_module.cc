#include "ngx_http_nodeginx_module.h"


// The nginx worker thread user must have permission to read the module.
#define NODE_MODULE_PATH "/tmp/handler.js"


static ngx_command_t ngx_http_nodeginx_commands[] = {
  {
    ngx_string("nodeginx"),
    NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
    ngx_http_nodeginx,
    0,
    0,
    NULL
  },
  ngx_null_command
};


ngx_module_t ngx_http_nodeginx_module = {
  NGX_MODULE_V1,
  &ngx_http_nodeginx_module_ctx,
  ngx_http_nodeginx_commands,
  NGX_HTTP_MODULE,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NGX_MODULE_V1_PADDING
};


ngx_int_t ngx_http_nodeginx_handler(ngx_http_request_t* req) {
  u_char ngx_greeting[] = "Welcome to nodeginx";
  u_char content_type[] = "text/html";
  ngx_buf_t* buf;
  ngx_chain_t out;

  // Working, but super hacky. Will crash the worker thread every other request
  // due to a failed assertion in V8. If Node were embedded more elegantly,
  // the request would be passed off to Node.
  int argc = 2;
  char* argv[2] = {
    (char*) "nodeginx",
    (char*) NODE_MODULE_PATH
  };
  node::Start(argc, argv);
  /////////

  req->headers_out.content_type.len = sizeof(content_type) - 1;
  req->headers_out.content_type.data = content_type;

  buf = (ngx_buf_t*) ngx_pcalloc(req->pool, sizeof(ngx_buf_t));
  out.buf = buf;
  out.next = NULL;

  buf->pos = ngx_greeting;
  buf->last = ngx_greeting + sizeof(ngx_greeting);
  buf->memory = 1;
  buf->last_buf = 1;

  req->headers_out.status = NGX_HTTP_OK;
  req->headers_out.content_length_n = sizeof(ngx_greeting);
  ngx_http_send_header(req);

  return ngx_http_output_filter(req, &out);
}


char* ngx_http_nodeginx(ngx_conf_t* cf, ngx_command_t* cmd, void* conf) {
  ngx_http_core_loc_conf_t* clcf;

  clcf = (ngx_http_core_loc_conf_t*) ngx_http_conf_get_module_loc_conf(cf,
                                                          ngx_http_core_module);
  clcf->handler = ngx_http_nodeginx_handler;

  return NGX_CONF_OK;
}
