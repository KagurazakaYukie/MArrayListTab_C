#ifndef MARRAYLISTTAB_H
#define MARRAYLISTTAB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "MArrayList.h"
#include "MultitThreadMemoryManager.h"
#include "Init.h"

typedef struct MALT {
    MemoryInfo *mi;
    MArrayList *al, *mark, *markindex;
} MArrayListTab;

MArrayListTab *CreateMArrayListTab(MTMemoryManager *mm, MArrayList *arrayList);

MArrayListTab *MArrayListTabInit(MTMemoryManager *mm);

void MarrayListTabAddIndex(MTMemoryManager *mm,MArrayListTab *lt,void *m);

void MArrayListTabMark(MTMemoryManager *mm,MArrayListTab *listTab, DataSizeType index);

void *MArrayListTabGetIndex(MArrayListTab *listTab, DataSizeType index);

#endif
