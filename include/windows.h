#ifndef __WINE_WINDOWS_H
#define __WINE_WINDOWS_H

#ifdef __cplusplus
extern "C" {
#endif

/* All the basic includes */
/* #include "excpt.h" */
#include "windef.h"
#include "winbase.h"
#include "wingdi.h"
#include "winuser.h"
#include "winnls.h"
#include "wincon.h"
#include "winver.h"
#include "winreg.h"
#include "winnetwk.h"

/* Not so essential ones */
#ifndef WIN32_LEAN_AND_MEAN

#include "cderr.h"
#include "dde.h"
#include "ddeml.h"
#include "dlgs.h"
#include "lzexpand.h"
#include "mmsystem.h"
/* #include "nb30.h" */
#include "rpc.h"
#include "shellapi.h"
/* #include "winperf.h" */

#include "winsock2.h"
/* #include "mswsock.h" */

#ifndef NOCRYPT
#include "wincrypt.h"
#endif /* !NOCRYPT */

#ifndef NOGDI
#include "commdlg.h"
#include "winspool.h"
#ifdef INC_OLE1
#include "ole.h"
#else
#include "ole2.h"
#endif
#endif /* !NOGDI */

#endif /* !WIN32_LEAN_AND_MEAN */

#ifdef INC_OLE2
#include "ole2.h"
#endif /* INC_OLE2 */

#ifndef NOSERVICE
#include "winsvc.h"
#endif /* !NOSERVICE */

#ifndef NOMCX
#include "mcx.h"
#endif /* !NOMCX */

#ifndef NOIMM
#include "imm.h"
#endif /* !NOIMM */


#if 0
  Where does this belong? Nobody uses this stuff anyway.
typedef struct {
	BYTE i;  /* much more .... */
} KANJISTRUCT;
typedef KANJISTRUCT *LPKANJISTRUCT;
typedef KANJISTRUCT *NPKANJISTRUCT;
typedef KANJISTRUCT *PKANJISTRUCT;

BOOL16      WINAPI CheckMenuRadioButton16(HMENU16,UINT16,UINT16,UINT16,BOOL16);
BOOL      WINAPI CheckMenuRadioButton(HMENU,UINT,UINT,UINT,BOOL);
WORD        WINAPI WOWHandle16(HANDLE,WOW_HANDLE_TYPE);

#endif /* 0 */

#ifdef __cplusplus
}
#endif

#endif  /* __WINE_WINDOWS_H */
