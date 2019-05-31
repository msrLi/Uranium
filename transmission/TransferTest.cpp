/**
 * @file main.cpp
 * @brief
 * @author  lenovo <xxx@lenovo.com>
 * @version 1.0.0
 * @date 2019-05-31
 */
/* Copyright(C) 2009-2019, Lenovo Inc.
 * All right reserved
 *
 */
#include <iostream>

#include "common.h"
#include "TransferInterface.h"
#include "FexTransfer.h"
#include "TransferFactory.h"


namespace  uranium
{

int __TransferMain(int argc, char **argv)
{
    TransferFactory *pFactory = TransferFactory::create();
    TRANSFER_BUFFER_T *pTranBuffer = NULL;
    int8_t           *pCmdBuf = NULL;
    TransferManager   *pTransManage = NULL;
    int32_t rc = 0;

    if (!ISNULL(pFactory)) {
        pTransManage = pFactory->createTransferObject(TRAN_MODE_FEX, TRAN_CLINET);
        if (ISNULL(pTransManage)) {
            rc = -1;
            printf("create failed!\n");
        }
    }

    if (SUCCEED(rc)) {
        pCmdBuf = (int8_t *)malloc(1024);
        if (ISNULL(pCmdBuf)) {
            rc = -1;
            printf("Out of  memory\n");
        }
    }
    if (SUCCEED(rc)) {
        pTranBuffer = pTransManage->createTransferBuffer(TRAN_MODE_FEX, pCmdBuf, 1024);
        if (ISNULL(pTranBuffer)) {
            rc = -1;
        }
    }

    if (SUCCEED(rc)) {
        memset(pCmdBuf, 0, 1024);
        sprintf((char *)pCmdBuf, "fex -l > /tmp/lhb.bin");
        rc = pTransManage->pullData(*pTranBuffer);
        if (SUCCEED(rc)) {
            std::cout << "get data length = " << pTranBuffer->length << "data=";
            printf("%s\n", (char*) pTranBuffer->buffer);

            std::cout << "file length = " << strlen((const char*)pCmdBuf) << std::endl;
            memset(pCmdBuf, 0, 1024);
            sprintf((char *)pCmdBuf, "fex -u /tmp/transfer_test");
            pTranBuffer->length = strlen((const char *)pCmdBuf);
            pTransManage->pushData(*pTranBuffer);
        } else {
            printf("Pull data failed!");
        }

    }

    if (!ISNULL(pTranBuffer)) {
        pTransManage->destoryTransferBuffer(pTranBuffer);
    }

    free(pCmdBuf);

    return rc;
}

};
