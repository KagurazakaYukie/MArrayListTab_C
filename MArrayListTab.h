#ifndef MARRAYLISTTAB_H
#define MARRAYLISTTAB_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "MArrayList.h"
#include "MultitThreadMemoryManager.h"
#include "Init.h"

typedef struct MALT {
    MemoryInfo *mi;
    MArrayList *al, *mark, *markindex;
} MArrayListTab;

MArrayListTab *MArrayListTabCreate(MTMemoryManager *mm, MArrayList *arrayList);

MArrayListTab *MArrayListTabInit(MTMemoryManager *mm);

void MarrayListTabAddIndex(MTMemoryManager *mm, MArrayListTab *lt, void *m);

void MArrayListTabMark(MTMemoryManager *mm, MArrayListTab *listTab, DataSizeType index);

void MArrayListTabMarks(MTMemoryManager *mm, MArrayListTab *listTab, unsigned long *index,unsigned long len);

MArrayListTab *MBUArrayListTabCreate(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayList *arrayList);

MArrayListTab *MBUArrayListTabInit(MTMemoryManager *mm, MemoryBigUnit *mbu);

void MBUarrayListTabAddIndex(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayListTab *lt, void *m);

void MBUArrayListTabMark(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayListTab *listTab, DataSizeType index);

void MBUArrayListTabMarks(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayListTab *listTab, unsigned long *index,unsigned long len);

void *MArrayListTabGetIndex(MArrayListTab *listTab, DataSizeType index);

unsigned long MArrayListTabSize(MArrayListTab *alt);

void MArrayListTabDestroy(MTMemoryManager *mm);

void MBUArrayListTabDestroy(MemoryBigUnit *mbu);

#endif
