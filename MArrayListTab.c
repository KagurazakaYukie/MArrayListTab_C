#include <stdlib.h>
#include <stdbool.h>
#include "MArrayListTab.h"
#include "Init.h"
#include "MArrayList.h"
#include "MultitThreadMemoryManager.h"

MArrayListTab *CreateMArrayListTab(MTMemoryManager *mm, MArrayList *arrayList) {
    MemoryInfo *mi = MTMemoryManagerCalloc(mm, sizeof(MArrayListTab));
    MArrayListTab *malt = (MArrayListTab *) mi->m;
    malt->mi = mi;
    malt->al = arrayList;
    malt->mark = MArrayListInit(mm);
    for (int i = 0; i < MArrayListSize(arrayList); ++i) {
        MArrayListAddIndex(mm, malt->mark, MTMemoryManagerCalloc(mm, sizeof(int)));
    }
    malt->markindex = MArrayListInit(mm);
    return malt;
}

MArrayListTab *MArrayListTabInit(MTMemoryManager *mm) {
    MemoryInfo *mi = MTMemoryManagerCalloc(mm, sizeof(MArrayListTab));
    MArrayListTab *malt = (MArrayListTab *) mi->m;
    malt->mi = mi;
    malt->al = MArrayListInit(mm);
    malt->mark = MArrayListInit(mm);
    malt->markindex = MArrayListInit(mm);
    return malt;
}

void MarrayListTabAddIndex(MTMemoryManager *mm, MArrayListTab *lt, void *m) {
    if (lt->markindex->length) {
        unsigned long i = *((unsigned long *) ((MemoryInfo *) lt->markindex->Element[lt->markindex->length - 1])->m)
        lt->al->Element[i] = m;
        *((int *) ((MemoryInfo *) listTab->mark->Element[i])->m) = 0;
        MTMemoryManagerFree(mm,(MemoryInfo *) lt->markindex->Element[lt->markindex->length - 1]));
        lt->markindex->length--;
    } else {
        MArrayListAddIndex(mm, lt->al, m);
        MArrayListAddIndex(mm, lt->mark, MTMemoryManagerCalloc(mm, sizeof(int)));
    }
}

void MArrayListTabMark(MTMemoryManager *mm, MArrayListTab *listTab, DataSizeType index) {
    *((int *) ((MemoryInfo *) listTab->mark->Element[index])->m) = 1;
    MemoryInfo *mi = MTMemoryManagerCalloc(mm, sizeof(unsigned long));
    *((unsigned long *) mi->m) = index;
    MArrayListAddIndex(mm, listTab->markindex, mi);
}

void *MArrayListTabGetIndex(MArrayListTab *listTab, DataSizeType index) {
    if (*((int *) ((MemoryInfo *) listTab->mark->Element[index])->m)) {
        return NULL;
    }
    return listTab->al->Element[index];
}