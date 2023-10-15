#include <libwebsockets.h>

static int callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {

    return 0;
};



const struct lws_protocols protocols_ctrl[] = {
        /* first protocol must always be HTTP handler */

        {
            "http-only",    /* name */
            callback,  /* callback */
            0               /* per_session_data_size */
        },
        {
            "ctrl",    /* name */
            callback,  /* callback */
            0               /* per_session_data_size */
        },
        {
            NULL, NULL, 0   /* End of list */
        }


};

const struct lws_protocols protocols_p2p[] = {
        /* first protocol must always be HTTP handler */

        {
            "http-only",    /* name */
            callback,  /* callback */
            0               /* per_session_data_size */
        },
        {
            "p2p",    /* name */
            callback,  /* callback */
            0               /* per_session_data_size */
        },
        {
            NULL, NULL, 0   /* End of list */
        }


};

const struct lws_http_mount mount_ctrl_proto = {
        /* .mount_next */		NULL,		/* linked-list "next" */
        /* .mountpoint */		"/",		/* mountpoint URL */
        /* .origin */			"./ctrl",
        /* .def */			"",	/* default filename */
        /* .protocol */			"ctrl",
        /* .cgienv */			NULL,
        /* .extra_mimetypes */		NULL,
        /* .interpret */		NULL,
        /* .cgi_timeout */		0,
        /* .cache_max_age */		0,
        /* .auth_mask */		0,
        /* .cache_reusable */		0,
        /* .cache_revalidate */		0,
        /* .cache_intermediaries */	0,
        /* .origin_protocol */		LWSMPRO_CALLBACK,	/* use proto callback */
        /* .mountpoint_len */		1,		/* char count */
        /* .basic_auth_login_file */	NULL,
};

const struct lws_http_mount mount_p2p_proto = {
        /* .mount_next */		NULL,		/* linked-list "next" */
        /* .mountpoint */		"/",		/* mountpoint URL */
        /* .origin */			"./p2p",
        /* .def */			"",	/* default filename */
        /* .protocol */			"p2p",
        /* .cgienv */			NULL,
        /* .extra_mimetypes */		NULL,
        /* .interpret */		NULL,
        /* .cgi_timeout */		0,
        /* .cache_max_age */		0,
        /* .auth_mask */		0,
        /* .cache_reusable */		0,
        /* .cache_revalidate */		0,
        /* .cache_intermediaries */	0,
        /* .origin_protocol */		LWSMPRO_CALLBACK,	/* use proto callback */
        /* .mountpoint_len */		1,		/* char count */
        /* .basic_auth_login_file */	NULL,
};

int main() {
    struct lws_context_creation_info ctx_info;
    memset( &ctx_info, 0, sizeof(ctx_info) );
    ctx_info.options = LWS_SERVER_OPTION_EXPLICIT_VHOSTS|LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;
    ctx_info.gid = -1;
    ctx_info.uid = -1;


    struct lws_context *ctx = lws_create_context( &ctx_info );
    ctx_info.port = 8081;
    ctx_info.protocols = protocols_ctrl;
    ctx_info.mounts = &mount_ctrl_proto;
    ctx_info.vhost_name = "ctrl";

    if (!lws_create_vhost(ctx, &ctx_info)) {
        lwsl_err("Failed to create first vhost\n");
        return -1;
    }
    struct lws_context_creation_info ctx_info2;
    memset( &ctx_info2, 0, sizeof(ctx_info2) );
    ctx_info2.port = 8080;
    ctx_info2.protocols = protocols_p2p;
    ctx_info2.mounts = &mount_p2p_proto;
    ctx_info2.vhost_name = "p2p";

    if (!lws_create_vhost(ctx, &ctx_info2)) {
        lwsl_err("Failed to create second vhost\n");
        return -1;
    }
    while( 1 )
	{
		lws_service( ctx, 0 );
	}  

}