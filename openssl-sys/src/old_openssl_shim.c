#include <openssl/hmac.h>

#ifdef OLD_OPENSSL
// Copied from openssl crypto/hmac/hmac.c
int HMAC_CTX_copy(HMAC_CTX *dctx, HMAC_CTX *sctx)
     {
     if (!EVP_MD_CTX_copy(&dctx->i_ctx, &sctx->i_ctx))
         goto err;
     if (!EVP_MD_CTX_copy(&dctx->o_ctx, &sctx->o_ctx))
         goto err;
     if (!EVP_MD_CTX_copy(&dctx->md_ctx, &sctx->md_ctx))
         goto err;
     memcpy(dctx->key, sctx->key, HMAC_MAX_MD_CBLOCK);
     dctx->key_length = sctx->key_length;
     dctx->md = sctx->md;
     return 1;
     err:
     return 0;
     }

int HMAC_Init_ex_shim(HMAC_CTX *ctx, const void *key, int key_len, const EVP_MD *md, ENGINE *impl) {
    HMAC_Init_ex(ctx, key, key_len, md, impl);
    return 1;
}

int HMAC_Update_shim(HMAC_CTX *ctx, const unsigned char *data, int len) {
    HMAC_Update(ctx, data, len);
    return 1;
}

int HMAC_Final_shim(HMAC_CTX *ctx, unsigned char *md, unsigned int *len) {
    HMAC_Final(ctx, md, len);
    return 1;
}

#else /* OLD_OPENSSL */

int HMAC_Init_ex_shim(HMAC_CTX *ctx, const void *key, int key_len, const EVP_MD *md, ENGINE *impl) {
    return HMAC_Init_ex(ctx, key, key_len, md, impl);
}

int HMAC_Update_shim(HMAC_CTX *ctx, const unsigned char *data, int len) {
    return HMAC_Update(ctx, data, len);
}

int HMAC_Final_shim(HMAC_CTX *ctx, unsigned char *md, unsigned int *len) {
    return HMAC_Final(ctx, md, len);
}
#endif /* OLD_OPENSSL */
