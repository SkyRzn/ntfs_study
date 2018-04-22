#include "vbr.h"
#include <endian.h>
#include <string.h>


vbr_t *create_vbr(void *mm)
{
	vbr_t *vbr = mm;

	if (memcmp(vbr->oem_id, OEM_ID, 8) != 0)
		return NULL;

	if (vbr->esm != htobe16(ESM))
		return NULL;

	return vbr;
}

