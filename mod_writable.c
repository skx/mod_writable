
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_main.h"
#include "http_protocol.h"
#include "http_request.h"
#include "util_script.h"
#include "http_connection.h"

#include "apr_strings.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>




static int mod_writable_check_access(request_rec *r)
{
	FILE *f;

	/* If we don't have a filename return */
	if (!r->filename )
		return DECLINED;

    /* If this is not a PHP file then return */
    if (strstr( r->filename, ".php" ) == NULL)
        return DECLINED;

    /* If the file is writable then abort */
	int rval = access (r->filename, W_OK);

	if (rval == 0) {
		ap_log_error(APLOG_MARK, APLOG_CRIT, 0, r->server, "Refusing to serve the writable file %s", r->filename );
		return HTTP_FORBIDDEN;
	}

	return DECLINED;
}


static void
mod_writable_register_hooks(apr_pool_t *p)
{
  ap_hook_check_access(mod_writable_check_access, NULL, NULL, APR_HOOK_FIRST, AP_AUTH_INTERNAL_PER_URI);

}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA mod_writable_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                       /* create per-dir    config structures */
    NULL,                       /* merge  per-dir    config structures */
    NULL,   /* create per-server config structures */
    NULL, /* merge  per-server config structures */
    NULL,        /* table of config file commands       */
    mod_writable_register_hooks        /* register hooks        */ };

